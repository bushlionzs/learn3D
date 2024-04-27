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

#include "backend/Renderer.h"

#include "backend/CommandStream.h"
#include "ResourceAllocator.h"

#include "backend/Engine.h"
#include "backend/Fence.h"

#include "backend/SwapChain.h"

#include "backend/View.h"

#include <backend/Renderer.h>

#include <backend/PixelBufferDescriptor.h>

#include "fg/FrameGraph.h"
#include "fg/FrameGraphId.h"
#include "fg/FrameGraphResources.h"

#include <utils/compiler.h>
#include <utils/JobSystem.h>
#include <utils/Panic.h>
#include <utils/Systrace.h>
#include <utils/vector.h>
#include <utils/debug.h>

// this helps visualize what dynamic-scaling is doing
#define DEBUG_DYNAMIC_SCALING false

using namespace filament::math;
using namespace utils;

namespace filament {

using namespace backend;

FRenderer::FRenderer(FEngine& engine) :
        mEngine(engine),
        mRenderTargetHandle(engine.getDefaultRenderTarget()),
        mHdrTranslucent(TextureFormat::RGBA16F),
        mHdrQualityMedium(TextureFormat::R11F_G11F_B10F),
        mHdrQualityHigh(TextureFormat::RGB16F),
        mIsRGB8Supported(false),
        mUserEpoch(engine.getEngineEpoch()),
        mPerRenderPassArena(engine.getPerRenderPassAllocator())
{
    DriverApi& driver = engine.getDriverApi();

    mIsRGB8Supported = driver.isRenderTargetFormatSupported(TextureFormat::RGB8);

    // our default HDR translucent format, fallback to LDR if not supported by the backend
    if (!driver.isRenderTargetFormatSupported(TextureFormat::RGBA16F)) {
        // this will clip all HDR data, but we don't have a choice
        mHdrTranslucent = TextureFormat::RGBA8;
    }

    // our default opaque low/medium quality HDR format, fallback to LDR if not supported
    if (!driver.isRenderTargetFormatSupported(mHdrQualityMedium)) {
        // this will clip all HDR data, but we don't have a choice
        mHdrQualityMedium = TextureFormat::RGB8;
    }

    // our default opaque high quality HDR format, fallback to RGBA, then medium, then LDR
    // if not supported
    if (!driver.isRenderTargetFormatSupported(mHdrQualityHigh)) {
        mHdrQualityHigh = TextureFormat::RGBA16F;
    }
    if (!driver.isRenderTargetFormatSupported(mHdrQualityHigh)) {
        mHdrQualityHigh = TextureFormat::R11F_G11F_B10F;
    }
    if (!driver.isRenderTargetFormatSupported(mHdrQualityHigh)) {
        // this will clip all HDR data, but we don't have a choice
        mHdrQualityHigh = TextureFormat::RGB8;
    }
}

FRenderer::~FRenderer() noexcept {

}

void FRenderer::terminate(FEngine& engine) {
    // Here we would cleanly free resources we've allocated, or we own, in particular we would
    // shut down threads if we created any.
    DriverApi& driver = engine.getDriverApi();

    // Before we can destroy this Renderer's resources, we must make sure
    // that all pending commands have been executed (as they could reference data in this
    // instance, e.g. Fences, Callbacks, etc...)
    if (UTILS_HAS_THREADING) {
        Fence::waitAndDestroy(engine.createFence());
    } else {
        // In single threaded mode, allow recently-created objects (e.g. no-op fences in Skipper)
        // to initialize themselves, otherwise the engine tries to destroy invalid handles.
        engine.execute();
    }

}

void FRenderer::resetUserTime() {
    mUserEpoch = std::chrono::steady_clock::now();
}

TextureFormat FRenderer::getHdrFormat(const FView& view, bool translucent) const noexcept {
    return mHdrQualityHigh;
}

TextureFormat FRenderer::getLdrFormat(bool translucent) const noexcept {
    return (translucent || !mIsRGB8Supported) ? TextureFormat::RGBA8 : TextureFormat::RGB8;
}

std::pair<Handle<HwRenderTarget>, TargetBufferFlags>
        FRenderer::getRenderTarget(FView const& view) const noexcept {
    Handle<HwRenderTarget> outTarget = view.getRenderTargetHandle();
    TargetBufferFlags outAttachmentMask = view.getRenderTargetAttachmentMask();
    if (!outTarget) {
        outTarget = mRenderTargetHandle;
        outAttachmentMask = TargetBufferFlags::COLOR0 | TargetBufferFlags::DEPTH;
    }
    return { outTarget, outAttachmentMask };
}

backend::TargetBufferFlags FRenderer::getClearFlags() const noexcept {
    return (mClearOptions.clear ? TargetBufferFlags::COLOR : TargetBufferFlags::NONE)
           | TargetBufferFlags::DEPTH_AND_STENCIL;
}

void FRenderer::initializeClearFlags() noexcept {
    // We always discard and clear the depth+stencil buffers -- we don't allow sharing these
    // across views (clear implies discard)
    mDiscardStartFlags = ((mClearOptions.discard || mClearOptions.clear) ?
                          TargetBufferFlags::COLOR : TargetBufferFlags::NONE)
                         | TargetBufferFlags::DEPTH_AND_STENCIL;

    mClearFlags = getClearFlags();
}

void FRenderer::setPresentationTime(int64_t monotonic_clock_ns) {
    FEngine::DriverApi& driver = mEngine.getDriverApi();
    driver.setPresentationTime(monotonic_clock_ns);
}

bool FRenderer::beginFrame(FSwapChain* swapChain, uint64_t vsyncSteadyClockTimeNano) {
    assert_invariant(swapChain);

    SYSTRACE_CALL();

    // get the timestamp as soon as possible
    using namespace std::chrono;
    const steady_clock::time_point now{ steady_clock::now() };
    const steady_clock::time_point userVsync{ steady_clock::duration(vsyncSteadyClockTimeNano) };
    const time_point<steady_clock> appVsync(vsyncSteadyClockTimeNano ? userVsync : now);

    mFrameId++;
    mViewRenderedCount = 0;

    SYSTRACE_FRAME_ID(mFrameId);

    FEngine& engine = mEngine;
    FEngine::DriverApi& driver = engine.getDriverApi();

    // start a frame capture, if requested.
    if (UTILS_UNLIKELY(engine.debug.renderer.doFrameCapture)) {
        driver.startCapture();
    }

    // latch the frame time
    std::chrono::duration<double> const time(appVsync - mUserEpoch);
    float const h = float(time.count());
    float const l = float(time.count() - h);
    mShaderUserTime = { h, l, 0, 0 };

    mPreviousRenderTargets.clear();

    mBeginFrameInternal = {};

    mSwapChain = swapChain;
    swapChain->makeCurrent(driver);

    // NOTE: this makes synchronous calls to the driver
    driver.updateStreams(&driver);

    // Gives the backend a chance to execute periodic tasks. This must be called before
    // the frame skipper.
    driver.tick();

    /*
    * From this point, we can't do any more work in beginFrame() because the user could choose
    * to ignore the return value and render the frame anyway -- which is perfectly fine.
    * The remaining work will be done when the first render() call is made.
    */
    auto beginFrameInternal = [this, appVsync]() {
        FEngine& engine = mEngine;
        FEngine::DriverApi& driver = engine.getDriverApi();

        driver.beginFrame(appVsync.time_since_epoch().count(), mFrameId);

        // This need to occur after the backend beginFrame() because some backends need to start
        // a command buffer before creating a fence.



        // ask the engine to do what it needs to (e.g. updates light buffer, materials...)
        engine.prepare();
    };



    // however, if we return false, the user is allowed to ignore us and render a frame anyway,
    // so we need to delay this work until that happens.
    mBeginFrameInternal = beginFrameInternal;

    // we need to flush in this case, to make sure the tick() call is executed at some point
    engine.flush();

    return false;
}

void FRenderer::endFrame() {
    SYSTRACE_CALL();

    if (UTILS_UNLIKELY(mBeginFrameInternal)) {
        mBeginFrameInternal();
        mBeginFrameInternal = {};
    }

    FEngine& engine = mEngine;
    FEngine::DriverApi& driver = engine.getDriverApi();

    if (UTILS_HAS_THREADING) {
        // on debug builds this helps to catch cases where we're writing to
        // the buffer form another thread, which is currently not allowed.
        driver.debugThreading();
    }

    if (mSwapChain) {
        mSwapChain->commit(driver);
        mSwapChain = nullptr;
    }



    driver.endFrame(mFrameId);

    // gives the backend a chance to execute periodic tasks
    driver.tick();

    // stop the frame capture, if one was requested
    if (UTILS_UNLIKELY(engine.debug.renderer.doFrameCapture)) {
        driver.stopCapture();
        engine.debug.renderer.doFrameCapture = false;
    }

    // do this before engine.flush()
    engine.getResourceAllocator().gc();

    // Run the component managers' GC in parallel
    // WARNING: while doing this we can't access any component manager
    auto& js = engine.getJobSystem();

    auto *job = js.runAndRetain(jobs::createJob(js, nullptr, &FEngine::gc, &engine)); // gc all managers

    engine.flush();     // flush command stream

    // make sure we're done with the gcs
    js.waitAndRelease(job);
}

void FRenderer::readPixels(uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height,
        PixelBufferDescriptor&& buffer) {

}

void FRenderer::readPixels(FRenderTarget* renderTarget,
        uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height,
        backend::PixelBufferDescriptor&& buffer) {
 
}

void FRenderer::copyFrame(FSwapChain* dstSwapChain, filament::Viewport const& dstViewport,
        filament::Viewport const& srcViewport, CopyFrameFlag flags) {
    SYSTRACE_CALL();

    assert_invariant(mSwapChain);
    assert_invariant(dstSwapChain);
    FEngine& engine = mEngine;
    FEngine::DriverApi& driver = engine.getDriverApi();

    // Set the current swap chain as the read surface, and the destination
    // swap chain as the draw surface so that blitting between default render
    // targets results in a frame copy from the current frame to the
    // destination.
    driver.makeCurrent(dstSwapChain->getHwHandle(), mSwapChain->getHwHandle());

    RenderPassParams params = {};
    // Clear color to black if the CLEAR flag is set.
    if (flags & CLEAR) {
        params.clearColor = {0.f, 0.f, 0.f, 1.f};
        params.flags.clear = TargetBufferFlags::COLOR;
        params.flags.discardStart = TargetBufferFlags::ALL;
        params.flags.discardEnd = TargetBufferFlags::NONE;
        params.viewport.left = 0;
        params.viewport.bottom = 0;
        params.viewport.width = std::numeric_limits<uint32_t>::max();
        params.viewport.height = std::numeric_limits<uint32_t>::max();
    }
    driver.beginRenderPass(mRenderTargetHandle, params);

    // Verify that the source swap chain is readable.
    assert_invariant(mSwapChain->isReadable());
    driver.blit(TargetBufferFlags::COLOR,
            mRenderTargetHandle, dstViewport, mRenderTargetHandle, srcViewport, SamplerMagFilter::LINEAR);
    if (flags & SET_PRESENTATION_TIME) {
        // TODO: Implement this properly, see https://github.com/google/filament/issues/633
    }

    driver.endRenderPass();

    if (flags & COMMIT) {
        dstSwapChain->commit(driver);
    }

    // Reset the context and read/draw surface to the current surface so that
    // frame rendering can continue or complete.
    mSwapChain->makeCurrent(driver);
}

void FRenderer::renderStandaloneView(FView const* view) {
    SYSTRACE_CALL();

    using namespace std::chrono;

    ASSERT_PRECONDITION(view->getRenderTarget(),
            "View \"%s\" must have a RenderTarget associated", view->getName());

    if (UTILS_LIKELY(view->getScene())) {
        mPreviousRenderTargets.clear();
        mFrameId++;

        // ask the engine to do what it needs to (e.g. updates light buffer, materials...)
        FEngine& engine = mEngine;
        engine.prepare();

        FEngine::DriverApi& driver = engine.getDriverApi();
        driver.beginFrame(steady_clock::now().time_since_epoch().count(), mFrameId);

        renderInternal(view);

        driver.endFrame(mFrameId);
    }
}

void FRenderer::render(FView const* view) {
    SYSTRACE_CALL();

    assert_invariant(mSwapChain);

    if (UTILS_UNLIKELY(mBeginFrameInternal)) {
        // this should not happen, the user should not call render() if we returned false from
        // beginFrame(). But because this is allowed, we handle it gracefully.
        mBeginFrameInternal();
        mBeginFrameInternal = {};
    }

    if (UTILS_LIKELY(view && view->getScene())) {
        if (mViewRenderedCount) {
            // this is a good place to kick the GPU, since we've rendered a View before,
            // and we're about to render another one.
            mEngine.getDriverApi().flush();
        }
        renderInternal(view);
        mViewRenderedCount++;
    }
}

void FRenderer::renderInternal(FView const* view) {
    // per-renderpass data
    ArenaScope rootArena(mPerRenderPassArena);

    FEngine& engine = mEngine;
    JobSystem& js = engine.getJobSystem();

    // create a root job so no other job can escape
    auto *rootJob = js.setRootJob(js.createJob());

    // execute the render pass
    renderJob(rootArena, const_cast<FView&>(*view));

    // make sure to flush the command buffer
    engine.flush();

    // and wait for all jobs to finish as a safety (this should be a no-op)
    js.runAndWait(rootJob);
}

void FRenderer::renderJob(ArenaScope& arena, FView& view) {
    FEngine& engine = mEngine;
    JobSystem& js = engine.getJobSystem();
    FEngine::DriverApi& driver = engine.getDriverApi();


    // DEBUG: driver commands must all happen from the same thread. Enforce that on debug builds.
    driver.debugThreading();

    const bool hasPostProcess = view.hasPostProcessPass();
    bool hasScreenSpaceRefraction = false;
    bool hasColorGrading = hasPostProcess;

    
    



    

   

    /*
     * Frame graph
     */

    FrameGraph fg(engine.getResourceAllocator());
    auto& blackboard = fg.getBlackboard();

    fg.compile();

    fg.export_graphviz(slog.d, view.getName());

    fg.execute(driver);

    // save the current history entry and destroy the oldest entry
    view.commitFrameHistory(engine);

    //recordHighWatermark(commandArena.getListener().getHighWatermark());
}

} // namespace filament
