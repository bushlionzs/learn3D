/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "OgreHeader.h"
#include "FEngine.h"
#include "ResourceAllocator.h"
#include <filament/DriverEnums.h>
#include <filament/Renderer.h>
#include <filament/Fence.h>
#include <filament/SwapChain.h>
#include <filament/FView.h>
#include <filament/FVertexBuffer.h>
#include <filament/FIndexBuffer.h>
#include <filament/FBufferObject.h>
#include <filament/FTexture.h>
#include <filament/RenderTarget.h>
#include <VulkanPlatform.h>
#include <utils/compiler.h>
#include <utils/debug.h>
#include <utils/Log.h>
#include <utils/Panic.h>
#include <utils/PrivateImplementation-impl.h>
#include <utils/Systrace.h>
#include <utils/ThreadUtils.h>

#include <algorithm>
#include <memory>



using namespace filament::math;
using namespace utils;

namespace filament {

    using namespace backend;

    struct Engine::BuilderDetails {
        Backend mBackend = Backend::DEFAULT;
        Platform* mPlatform = nullptr;
        Engine::Config mConfig;
        FeatureLevel mFeatureLevel = FeatureLevel::FEATURE_LEVEL_1;
        void* mSharedContext = nullptr;
        static Config validateConfig(const Config* pConfig) noexcept;
    };

    Engine* FEngine::create(Engine::Builder const& builder) {
        SYSTRACE_ENABLE();
        SYSTRACE_CALL();

        FEngine* instance = new FEngine(builder);

        // initialize all fields that need an instance of FEngine
        // (this cannot be done safely in the ctor)

        // Normally we launch a thread and create the context and Driver from there (see FEngine::loop).
        // In the single-threaded case, we do so in the here and now.
        if (!UTILS_HAS_THREADING) {
            Platform* platform = builder->mPlatform;
            void* const sharedContext = builder->mSharedContext;

            if (platform == nullptr) {
                platform = new VulkanPlatform();
                instance->mPlatform = platform;
                instance->mOwnPlatform = true;
            }
            if (platform == nullptr) {
                slog.e << "Selected backend not supported in this build." << io::endl;
                delete instance;
                return nullptr;
            }
            DriverConfig const driverConfig{
                .handleArenaSize = instance->getRequestedDriverHandleArenaSize() };
            instance->mDriver = platform->createDriver(sharedContext, driverConfig);

        }
        else {
            // start the driver thread
            instance->mDriverThread = std::thread(&FEngine::loop, instance);

            // wait for the driver to be ready
            instance->mDriverBarrier.await();

            if (UTILS_UNLIKELY(!instance->mDriver)) {
                // something went horribly wrong during driver initialization
                instance->mDriverThread.join();
                delete instance;
                return nullptr;
            }
        }

        // now we can initialize the largest part of the engine
        instance->init();

        if (!UTILS_HAS_THREADING) {
            instance->execute();
        }

        return instance;
    }

#if UTILS_HAS_THREADING

    void FEngine::create(Engine::Builder const& builder, Invocable<void(void*)>&& callback) {
        SYSTRACE_ENABLE();
        SYSTRACE_CALL();

        FEngine* instance = new FEngine(builder);

        // start the driver thread
        instance->mDriverThread = std::thread(&FEngine::loop, instance);

        // launch a thread to call the callback -- so it can't do any damage.
        std::thread callbackThread = std::thread([instance, callback = std::move(callback)]() {
            instance->mDriverBarrier.await();
            callback(instance);
            });

        // let the callback thread die on its own
        callbackThread.detach();
    }

    FEngine* FEngine::getEngine(void* token) {

        FEngine* instance = static_cast<FEngine*>(token);

        ASSERT_PRECONDITION(ThreadUtils::isThisThread(instance->mMainThreadId),
            "Engine::createAsync() and Engine::getEngine() must be called on the same thread.");

        // we use mResourceAllocator as a proxy for "am I already initialized"
        if (!instance->mResourceAllocator) {
            if (UTILS_UNLIKELY(!instance->mDriver)) {
                // something went horribly wrong during driver initialization
                instance->mDriverThread.join();
                delete instance;
                return nullptr;
            }

            // now we can initialize the largest part of the engine
            instance->init();
        }

        return instance;
    }

#endif

    // these must be static because only a pointer is copied to the render stream
    // Note that these coordinates are specified in OpenGL clip space. Other backends can transform
    // these in the vertex shader as needed.
    static constexpr float4 sFullScreenTriangleVertices[3] = {
            { -1.0f, -1.0f, 1.0f, 1.0f },
            {  3.0f, -1.0f, 1.0f, 1.0f },
            { -1.0f,  3.0f, 1.0f, 1.0f }
    };

    // these must be static because only a pointer is copied to the render stream
    static const uint16_t sFullScreenTriangleIndices[3] = { 0, 1, 2 };

    FEngine::FEngine(Engine::Builder const& builder) :
        mActiveFeatureLevel(builder->mFeatureLevel),
        mPlatform(builder->mPlatform),
        mSharedGLContext(builder->mSharedContext),
        mEntityManager(EntityManager::get()),
        mCommandBufferQueue(
            builder->mConfig.minCommandBufferSizeMB* MiB,
            builder->mConfig.commandBufferSizeMB* MiB),
        mPerRenderPassAllocator(
            "FEngine::mPerRenderPassAllocator",
            builder->mConfig.perRenderPassArenaSizeMB* MiB),
        mHeapAllocator("FEngine::mHeapAllocator", AreaPolicy::NullArea{}),
        mJobSystem(getJobSystemThreadPoolSize(builder->mConfig)),
        mEngineEpoch(std::chrono::steady_clock::now()),
        mDriverBarrier(1),
        mMainThreadId(ThreadUtils::getThreadId()),
        mConfig(builder->mConfig)
    {
        // we're assuming we're on the main thread here.
        // (it may not be the case)
        mJobSystem.adopt();

        slog.i << "FEngine (" << sizeof(void*) * 8 << " bits) created at " << this << " "
            << "(threading is " << (UTILS_HAS_THREADING ? "enabled)" : "disabled)") << io::endl;
    }

    uint32_t FEngine::getJobSystemThreadPoolSize(Engine::Config const& config) noexcept {
        if (config.jobSystemThreadCount > 0) {
            return config.jobSystemThreadCount;
        }

        // 1 thread for the user, 1 thread for the backend
        int threadCount = (int)std::thread::hardware_concurrency() - 2;
        // make sure we have at least 1 thread though
        threadCount = std::max(1, threadCount);
        return threadCount;
    }

    /*
     * init() is called just after the driver thread is initialized. Driver commands are therefore
     * possible.
     */

    void FEngine::init() {
        SYSTRACE_CALL();

        // this must be first.
        assert_invariant(intptr_t(&mDriverApiStorage) % alignof(DriverApi) == 0);
        ::new(&mDriverApiStorage) DriverApi(*mDriver, mCommandBufferQueue.getCircularBuffer());

        DriverApi& driverApi = getDriverApi();

        mActiveFeatureLevel = std::min(mActiveFeatureLevel, driverApi.getFeatureLevel());

        slog.i << "Backend feature level: " << int(driverApi.getFeatureLevel()) << io::endl;
        slog.i << "FEngine feature level: " << int(mActiveFeatureLevel) << io::endl;


        mResourceAllocator = new ResourceAllocator(mConfig, driverApi);


        // initialize the dummy textures so that their contents are not undefined
        static const uint32_t zeroes[6] = { 0 };
        static const uint32_t ones = 0xffffffff;



        mDefaultRenderTarget = driverApi.createDefaultRenderTarget();
    }

    FEngine::~FEngine() noexcept {
        SYSTRACE_CALL();
        delete mResourceAllocator;
        delete mDriver;
    }

    void FEngine::shutdown() {
        SYSTRACE_CALL();

        // by construction this should never be nullptr
        assert_invariant(mResourceAllocator);

        ASSERT_PRECONDITION(ThreadUtils::isThisThread(mMainThreadId),
            "Engine::shutdown() called from the wrong thread!");

#ifndef NDEBUG
        // print out some statistics about this run
        size_t const wm = mCommandBufferQueue.getHighWatermark();
        size_t const wmpct = wm / (getCommandBufferSize() / 100);
        slog.d << "CircularBuffer: High watermark "
            << wm / 1024 << " KiB (" << wmpct << "%)" << io::endl;
#endif

        DriverApi& driver = getDriverApi();

        /*
         * Destroy our own state first
         */


        mResourceAllocator->terminate();


        driver.destroyRenderTarget(mDefaultRenderTarget);

        /*
         * Shutdown the backend...
         */

         // There might be commands added by the `terminate()` calls, so we need to flush all commands
         // up to this point. After flushCommandBuffer() is called, all pending commands are guaranteed
         // to be executed before the driver thread exits.
        flushCommandBuffer(mCommandBufferQueue);

        // now wait for all pending commands to be executed and the thread to exit
        mCommandBufferQueue.requestExit();
        if (!UTILS_HAS_THREADING) {
            execute();
            getDriverApi().terminate();
        }
        else {
            mDriverThread.join();
            // Driver::terminate() has been called here.
        }

        // Finally, call user callbacks that might have been scheduled.
        // These callbacks CANNOT call driver APIs.
        getDriver().purge();

        // and destroy the CommandStream
        std::destroy_at(std::launder(reinterpret_cast<DriverApi*>(&mDriverApiStorage)));

        /*
         * Terminate the JobSystem...
         */

         // detach this thread from the JobSystem
        mJobSystem.emancipate();
    }

    void FEngine::prepare() {
        SYSTRACE_CALL();
        // prepare() is called once per Renderer frame. Ideally we would upload the content of
        // UBOs that are visible only. It's not such a big issue because the actual upload() is
        // skipped if the UBO hasn't changed. Still we could have a lot of these.
        FEngine::DriverApi& driver = getDriverApi();
    }

    void FEngine::gc() {
        // Note: this runs in a Job
        auto& em = mEntityManager;
    }

    void FEngine::flush() {
        // flush the command buffer
        flushCommandBuffer(mCommandBufferQueue);
    }

    void FEngine::flushAndWait() {

#if defined(__ANDROID__)

        // first make sure we've not terminated filament
        ASSERT_PRECONDITION(!mCommandBufferQueue.isExitRequested(),
            "calling Engine::flushAndWait() after Engine::shutdown()!");

#endif

        // enqueue finish command -- this will stall in the driver until the GPU is done
        getDriverApi().finish();

        // finally, execute callbacks that might have been scheduled
        getDriver().purge();
    }

    // -----------------------------------------------------------------------------------------------
    // Render thread / command queue
    // -----------------------------------------------------------------------------------------------

    int FEngine::loop() {
        if (mPlatform == nullptr) {
            mPlatform = new VulkanPlatform();
            mOwnPlatform = true;
            slog.i << "FEngine resolved backend: Vulkan"  << io::endl;
            if (mPlatform == nullptr) {
                slog.e << "Selected backend not supported in this build." << io::endl;
                mDriverBarrier.latch();
                return 0;
            }
        }

#if FILAMENT_ENABLE_MATDBG
#ifdef __ANDROID__
        const char* portString = "8081";
#else
        const char* portString = getenv("FILAMENT_MATDBG_PORT");
#endif
        if (portString != nullptr) {
            const int port = atoi(portString);
            debug.server = new matdbg::DebugServer(mBackend, port);

            // Sometimes the server can fail to spin up (e.g. if the above port is already in use).
            // When this occurs, carry onward, developers can look at civetweb.txt for details.
            if (!debug.server->isReady()) {
                delete debug.server;
                debug.server = nullptr;
            }
            else {
                debug.server->setEditCallback(FMaterial::onEditCallback);
                debug.server->setQueryCallback(FMaterial::onQueryCallback);
            }
        }
#endif

        JobSystem::setThreadName("FEngine::loop");
        JobSystem::setThreadPriority(JobSystem::Priority::DISPLAY);

        DriverConfig const driverConfig{
                .handleArenaSize = getRequestedDriverHandleArenaSize(),
                .textureUseAfterFreePoolSize = mConfig.textureUseAfterFreePoolSize
        };
        mDriver = mPlatform->createDriver(mSharedGLContext, driverConfig);

        mDriverBarrier.latch();
        if (UTILS_UNLIKELY(!mDriver)) {
            // if we get here, it's because the driver couldn't be initialized and the problem has
            // been logged.
            return 0;
        }

        uint32_t const id = std::thread::hardware_concurrency() - 1;
        while (true) {

            if (!execute()) {
                break;
            }
        }

        // terminate() is a synchronous API
        getDriverApi().terminate();
        return 0;
    }

    void FEngine::flushCommandBuffer(CommandBufferQueue& commandQueue) {
        getDriver().purge();
        commandQueue.flush();
    }

    // -----------------------------------------------------------------------------------------------
    // Resource management
    // -----------------------------------------------------------------------------------------------

    /*
     * Object created from a Builder
     */
    template<typename T, typename ... ARGS>
    inline T* FEngine::create(ResourceList<T>& list,
        typename T::Builder const& builder, ARGS&& ... args) noexcept {
        T* p = mHeapAllocator.make<T>(*this, builder, std::forward<ARGS>(args)...);
        if (UTILS_UNLIKELY(p)) { // this should never happen
            list.insert(p);
        }
        return p;
    }

    FBufferObject* FEngine::createBufferObject(const BufferObject::Builder& builder) noexcept
    {
        return create(mBufferObjects, builder);
    }

    FVertexBuffer* FEngine::createVertexBuffer(const VertexBuffer::Builder& builder) noexcept
    {
        return create(mVertexBuffers, builder);
    }

    FIndexBuffer* FEngine::createIndexBuffer(const IndexBuffer::Builder& builder) noexcept
    {
        return create(mIndexBuffers, builder);
    }
    

    /*
     * Special cases
     */

    FRenderer* FEngine::createRenderer() noexcept {
        FRenderer* p = mHeapAllocator.make<FRenderer>(*this);
        if (p) {
            mRenderers.insert(p);
        }
        return p;
    }

    FRenderTarget* FEngine::createRenderTarget(const RenderTarget::Builder& builder) noexcept
    {
        return create(mTargets, builder);
    }

    FTexture* FEngine::createTexture(const Texture::Builder& builder) noexcept
    {
        return create(mTextures, builder);
    }

    FFence* FEngine::createFence() noexcept {
        FFence* p = mHeapAllocator.make<FFence>(*this);
        if (p) {
            std::lock_guard const guard(mFenceListLock);
            mFences.insert(p);
        }
        return p;
    }

    FSwapChain* FEngine::createSwapChain(void* nativeWindow, uint64_t flags) noexcept {
        if (UTILS_UNLIKELY(flags & backend::SWAP_CHAIN_CONFIG_APPLE_CVPIXELBUFFER)) {
            // If this flag is set, then the nativeWindow is a CVPixelBufferRef.
            // The call to setupExternalImage is synchronous, and allows the driver to take ownership of
            // the buffer on this thread.
            // For non-Metal backends, this is a no-op.
            getDriverApi().setupExternalImage(nativeWindow);
        }
        FSwapChain* p = mHeapAllocator.make<FSwapChain>(*this, nativeWindow, flags);
        if (p) {
            mSwapChains.insert(p);
        }
        return p;
    }

    FSwapChain* FEngine::createSwapChain(uint32_t width, uint32_t height, uint64_t flags) noexcept {
        FSwapChain* p = mHeapAllocator.make<FSwapChain>(*this, width, height, flags);
        if (p) {
            mSwapChains.insert(p);
        }
        return p;
    }

    FView* FEngine::createView() noexcept {
        FView* p = mHeapAllocator.make<FView>(*this);
        if (p) {
            mViews.insert(p);
        }
        return p;
    }

    void* FEngine::streamAlloc(size_t size, size_t alignment) noexcept {
        // we allow this only for small allocations
        if (size > 65536) {
            return nullptr;
        }
        return getDriverApi().allocate(size, alignment);
    }

    bool FEngine::execute() {
        // wait until we get command buffers to be executed (or thread exit requested)
        auto buffers = mCommandBufferQueue.waitForCommands();
        if (UTILS_UNLIKELY(buffers.empty())) {
            return false;
        }

        // execute all command buffers
        auto& driver = getDriverApi();
        for (auto& item : buffers) {
            if (UTILS_LIKELY(item.begin)) {
                driver.execute(item.begin);
                mCommandBufferQueue.releaseBuffer(item);
            }
        }

        return true;
    }

    void FEngine::destroy(FEngine* engine) {
        if (engine) {
            engine->shutdown();
            delete engine;
        }
    }


    bool FEngine::destroy(const FFence* p)
    {
        return true;
    }

    Engine::FeatureLevel FEngine::getSupportedFeatureLevel() const noexcept {
        FEngine::DriverApi& driver = const_cast<FEngine*>(this)->getDriverApi();
        return driver.getFeatureLevel();
    }

    Engine::FeatureLevel FEngine::setActiveFeatureLevel(FeatureLevel featureLevel) {
        ASSERT_PRECONDITION(featureLevel <= getSupportedFeatureLevel(),
            "Feature level %u not supported", (unsigned)featureLevel);
        ASSERT_PRECONDITION(mActiveFeatureLevel >= FeatureLevel::FEATURE_LEVEL_1,
            "Cannot adjust feature level beyond 0 at runtime");
        return (mActiveFeatureLevel = std::max(mActiveFeatureLevel, featureLevel));
    }

#if defined(__EMSCRIPTEN__)
    void FEngine::resetBackendState() noexcept {
        getDriverApi().resetState();
    }
#endif

    // ------------------------------------------------------------------------------------------------

    Engine::Builder::Builder() noexcept = default;
    Engine::Builder::~Builder() noexcept = default;
    Engine::Builder::Builder(Engine::Builder const& rhs) noexcept = default;
    Engine::Builder::Builder(Engine::Builder&& rhs) noexcept = default;
    Engine::Builder& Engine::Builder::operator=(Engine::Builder const& rhs) noexcept = default;
    Engine::Builder& Engine::Builder::operator=(Engine::Builder&& rhs) noexcept = default;


    Engine::Builder& Engine::Builder::platform(Platform* platform) noexcept {
        mImpl->mPlatform = platform;
        return *this;
    }

    Engine::Builder& Engine::Builder::config(Engine::Config const* config) noexcept {
        mImpl->mConfig = BuilderDetails::validateConfig(config);
        return *this;
    }

    Engine::Builder& Engine::Builder::featureLevel(FeatureLevel featureLevel) noexcept {
        mImpl->mFeatureLevel = featureLevel;
        return *this;
    }

    Engine::Builder& Engine::Builder::sharedContext(void* sharedContext) noexcept {
        mImpl->mSharedContext = sharedContext;
        return *this;
    }

#if UTILS_HAS_THREADING

    void Engine::Builder::build(Invocable<void(void*)>&& callback) const {
        FEngine::create(*this, std::move(callback));
    }

#endif

    Engine* Engine::Builder::build() const {
        return FEngine::create(*this);
    }

    Engine::Config Engine::BuilderDetails::validateConfig(const Config* const pConfig) noexcept {
        // Rule of thumb: perRenderPassArenaMB must be roughly 1 MB larger than perFrameCommandsMB
        constexpr uint32_t COMMAND_ARENA_OVERHEAD = 1;
        constexpr uint32_t CONCURRENT_FRAME_COUNT = 3;

        Config config;
        if (!pConfig) {
            return config;
        }

        // make sure to copy all the fields
        config = *pConfig;

        // Use at least the defaults set by the build system
        config.minCommandBufferSizeMB = std::max(
            config.minCommandBufferSizeMB,
            (uint32_t)FILAMENT_MIN_COMMAND_BUFFERS_SIZE_IN_MB);

        config.perFrameCommandsSizeMB = std::max(
            config.perFrameCommandsSizeMB,
            (uint32_t)FILAMENT_PER_FRAME_COMMANDS_SIZE_IN_MB);

        config.perRenderPassArenaSizeMB = std::max(
            config.perRenderPassArenaSizeMB,
            (uint32_t)FILAMENT_PER_RENDER_PASS_ARENA_SIZE_IN_MB);

        config.commandBufferSizeMB = std::max(
            config.commandBufferSizeMB,
            config.minCommandBufferSizeMB * CONCURRENT_FRAME_COUNT);

        // Enforce pre-render-pass arena rule-of-thumb
        config.perRenderPassArenaSizeMB = std::max(
            config.perRenderPassArenaSizeMB,
            config.perFrameCommandsSizeMB + COMMAND_ARENA_OVERHEAD);

        // This value gets validated during driver creation, so pass it through
        config.driverHandleArenaSizeMB = config.driverHandleArenaSizeMB;

        return config;
    }

} // namespace filament
