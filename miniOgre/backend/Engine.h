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

#ifndef TNT_FILAMENT_DETAILS_ENGINE_H
#define TNT_FILAMENT_DETAILS_ENGINE_H

#include "EngineBase.h"
#include "downcast.h"
#include "ResourceList.h"
#include "Allocators.h"
#include "backend/RendererBase.h"
#include "backend/RenderTargetBase.h"
#include "backend/VertexBuffer.h"
#include "backend/BufferObject.h"
#include "backend/CommandBufferQueue.h"
#include "backend/CommandStream.h"
#include "backend/DriverApi.h"
#include "backend/HwVertexBufferInfoFactory.h"
#include "backend/Texture.h"
#include <utils/EntityManager.h>


#if FILAMENT_ENABLE_MATDBG
#include <matdbg/DebugServer.h>
#else
namespace filament {
    namespace matdbg {
        class DebugServer;
        using MaterialKey = uint32_t;
    } // namespace matdbg
} // namespace filament
#endif

#include <utils/compiler.h>
#include <utils/Allocator.h>
#include <utils/JobSystem.h>
#include <utils/CountDownLatch.h>

#include <chrono>
#include <memory>
#include <new>
#include <random>
#include <unordered_map>

namespace filament {

    class Renderer;

    namespace backend {
        class Driver;
        class Program;
    } // namespace driver

    class FFence;
    class FRenderer;
    class FScene;
    class FSwapChain;
    class FView;
    class FRenderTarget;
    class ResourceAllocator;
    class FVertexBuffer;
    class FBufferObject;
    /*
     * Concrete implementation of the Engine interface. This keeps track of all hardware resources
     * for a given context.
     */
    class FEngine : public Engine {
    public:

        inline void* operator new(std::size_t size) noexcept {
            return utils::aligned_alloc(size, alignof(FEngine));
        }

        inline void operator delete(void* p) noexcept {
            utils::aligned_free(p);
        }

        using DriverApi = backend::DriverApi;
        using clock = std::chrono::steady_clock;
        using Epoch = clock::time_point;
        using duration = clock::duration;

    public:
        static Engine* create(Builder const& builder);

#if UTILS_HAS_THREADING
        static void create(Builder const& builder, utils::Invocable<void(void* token)>&& callback);
        static FEngine* getEngine(void* token);
#endif

        static void destroy(FEngine* engine);

        ~FEngine() noexcept;

        backend::ShaderModel getShaderModel() const noexcept { return getDriver().getShaderModel(); }

        DriverApi& getDriverApi() noexcept {
            return *std::launder(reinterpret_cast<DriverApi*>(&mDriverApiStorage));
        }


        // the per-frame Area is used by all Renderer, so they must run in sequence and
        // have freed all allocated memory when done. If this needs to change in the future,
        // we'll simply have to use separate Areas (for instance).
        LinearAllocatorArena& getPerRenderPassAllocator() noexcept { return mPerRenderPassAllocator; }




        backend::Handle<backend::HwRenderPrimitive> getFullScreenRenderPrimitive() const noexcept {
            return mFullScreenTriangleRph;
        }


        FeatureLevel getSupportedFeatureLevel() const noexcept;

        FeatureLevel setActiveFeatureLevel(FeatureLevel featureLevel);

        FeatureLevel getActiveFeatureLevel() const noexcept {
            return mActiveFeatureLevel;
        }


        utils::EntityManager& getEntityManager() noexcept {
            return mEntityManager;
        }

        HeapAllocatorArena& getHeapAllocator() noexcept {
            return mHeapAllocator;
        }



        Platform* getPlatform() const noexcept {
            return mPlatform;
        }

        backend::ShaderLanguage getShaderLanguage() const noexcept {
                return backend::ShaderLanguage::SPIRV;
        }

        ResourceAllocator& getResourceAllocator() noexcept {
            assert_invariant(mResourceAllocator);
            return *mResourceAllocator;
        }

        void* streamAlloc(size_t size, size_t alignment) noexcept;

        Epoch getEngineEpoch() const { return mEngineEpoch; }
        duration getEngineTime() const noexcept {
            return clock::now() - getEngineEpoch();
        }

        backend::Handle<backend::HwRenderTarget> getDefaultRenderTarget() const noexcept {
            return mDefaultRenderTarget;
        }


        FBufferObject* createBufferObject(const BufferObject::Builder& builder) noexcept;
        FVertexBuffer* createVertexBuffer(const VertexBuffer::Builder& builder) noexcept;
        FRenderer* createRenderer() noexcept;
        FRenderTarget* createRenderTarget(const RenderTarget::Builder& builder) noexcept;
        FTexture* createTexture(const Texture::Builder& builder) noexcept;

        FFence* createFence() noexcept;
        FSwapChain* createSwapChain(void* nativeWindow, uint64_t flags) noexcept;
        FSwapChain* createSwapChain(uint32_t width, uint32_t height, uint64_t flags) noexcept;
        FView* createView() noexcept;

        void flushAndWait();

        // flush the current buffer
        void flush();

        // flush the current buffer based on some heuristics
        void flushIfNeeded() {
            auto counter = mFlushCounter + 1;
            if (UTILS_LIKELY(counter < 128)) {
                mFlushCounter = counter;
            }
            else {
                mFlushCounter = 0;
                flush();
            }
        }

        /**
         * Processes the platform's event queue when called from the platform's event-handling thread.
         * Returns false when called from any other thread.
         */
        bool pumpPlatformEvents() {
            return mPlatform->pumpEvents();
        }

        void prepare();
        void gc();

        using ShaderContent = utils::FixedCapacityVector<uint8_t>;

        ShaderContent& getVertexShaderContent() const noexcept {
            return mVertexShaderContent;
        }

        ShaderContent& getFragmentShaderContent() const noexcept {
            return mFragmentShaderContent;
        }


        bool execute();

        utils::JobSystem& getJobSystem() noexcept {
            return mJobSystem;
        }

        std::default_random_engine& getRandomEngine() {
            return mRandomEngine;
        }

        void pumpMessageQueues() const {
            getDriver().purge();
        }

        void setAutomaticInstancingEnabled(bool enable) noexcept {
            // instancing is not allowed at feature level 0
            if (hasFeatureLevel(FeatureLevel::FEATURE_LEVEL_1)) {
                mAutomaticInstancingEnabled = enable;
            }
        }

        bool isAutomaticInstancingEnabled() const noexcept {
            return mAutomaticInstancingEnabled;
        }

        HwVertexBufferInfoFactory& getVertexBufferInfoFactory() noexcept {
            return mHwVertexBufferInfoFactory;
        }

        static constexpr const size_t MiB = 1024u * 1024u;
        size_t getMinCommandBufferSize() const noexcept { return mConfig.minCommandBufferSizeMB * MiB; }
        size_t getCommandBufferSize() const noexcept { return mConfig.commandBufferSizeMB * MiB; }
        size_t getPerFrameCommandsSize() const noexcept { return mConfig.perFrameCommandsSizeMB * MiB; }
        size_t getPerRenderPassArenaSize() const noexcept { return mConfig.perRenderPassArenaSizeMB * MiB; }
        size_t getRequestedDriverHandleArenaSize() const noexcept { return mConfig.driverHandleArenaSizeMB * MiB; }
        Config const& getConfig() const noexcept { return mConfig; }

        bool hasFeatureLevel(backend::FeatureLevel neededFeatureLevel) const noexcept {
            return FEngine::getActiveFeatureLevel() >= neededFeatureLevel;
        }


        bool destroy(const FFence* p);
#if defined(__EMSCRIPTEN__)
        void resetBackendState() noexcept;
#endif

    private:
        explicit FEngine(Engine::Builder const& builder);
        void init();
        void shutdown();

        int loop();
        void flushCommandBuffer(backend::CommandBufferQueue& commandBufferQueue);

        backend::Driver& getDriver() const noexcept { return *mDriver; }


        backend::Driver* mDriver = nullptr;
        backend::Handle<backend::HwRenderTarget> mDefaultRenderTarget;

        FeatureLevel mActiveFeatureLevel = FeatureLevel::FEATURE_LEVEL_1;
        Platform* mPlatform = nullptr;
        bool mOwnPlatform = false;
        bool mAutomaticInstancingEnabled = false;
        void* mSharedGLContext = nullptr;
        backend::Handle<backend::HwRenderPrimitive> mFullScreenTriangleRph;



        utils::EntityManager& mEntityManager;

        ResourceAllocator* mResourceAllocator = nullptr;
        HwVertexBufferInfoFactory mHwVertexBufferInfoFactory;

        std::thread mDriverThread;
        backend::CommandBufferQueue mCommandBufferQueue;
        std::aligned_storage<sizeof(DriverApi), alignof(DriverApi)>::type mDriverApiStorage;
        static_assert(sizeof(mDriverApiStorage) >= sizeof(DriverApi));

        uint32_t mFlushCounter = 0;

        LinearAllocatorArena mPerRenderPassAllocator;
        HeapAllocatorArena mHeapAllocator;

        utils::JobSystem mJobSystem;
        static uint32_t getJobSystemThreadPoolSize(Engine::Config const& config) noexcept;

        std::default_random_engine mRandomEngine;

        Epoch mEngineEpoch;

        ResourceList<FRenderer> mRenderers{ "Renderer" };
        ResourceList<FSwapChain> mSwapChains{ "SwapChain" };
        ResourceList<FFence> mFences{ "Fence" };
        ResourceList<FView> mViews{ "View" };

        utils::Mutex mFenceListLock;

        mutable utils::CountDownLatch mDriverBarrier;

        mutable ShaderContent mVertexShaderContent;
        mutable ShaderContent mFragmentShaderContent;

        std::thread::id mMainThreadId{};

        // Creation parameters
        Config mConfig;

    public:
        // these are the debug properties used by FDebug. They're accessed directly by modules who need them.
        struct {
            struct {
                bool debug_directional_shadowmap = false;
                bool far_uses_shadowcasters = true;
                bool focus_shadowcasters = true;
                bool visualize_cascades = false;
                bool tightly_bound_scene = true;
                float dzn = -1.0f;
                float dzf = 1.0f;
            } shadowmap;
            struct {
                bool camera_at_origin = true;
                struct {
                    float kp = 0.0f;
                    float ki = 0.0f;
                    float kd = 0.0f;
                } pid;
            } view;
            struct {
                // When set to true, the backend will attempt to capture the next frame and write the
                // capture to file. At the moment, only supported by the Metal backend.
                bool doFrameCapture = false;
                bool disable_buffer_padding = false;
            } renderer;
            struct {
                bool debug_froxel_visualization = false;
            } lighting;
            matdbg::DebugServer* server = nullptr;
        } debug;
    };

    FILAMENT_DOWNCAST(Engine)

} // namespace filament

#endif // TNT_FILAMENT_DETAILS_ENGINE_H
