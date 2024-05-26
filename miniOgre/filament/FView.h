/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_DETAILS_VIEW_H
#define TNT_FILAMENT_DETAILS_VIEW_H

#include <filament/View.h>
#include <filament/Viewport.h>
#include <filament/RendererBase.h>

#include "downcast.h"

#include "Allocators.h"


#include <filament/DriverApi.h>
#include <filament/FRenderTarget.h>
#include <filament/Handle.h>

#include <utils/compiler.h>
#include <utils/Allocator.h>
#include <utils/StructureOfArrays.h>
#include <utils/Range.h>
#include <utils/Slice.h>

#include <math/scalar.h>
#include <math/mat4.h>

namespace utils {
class JobSystem;
} // namespace utils;

// Avoid warnings for using the deprecated APIs.
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning push
#pragma warning disable : 4996
#endif

namespace filament {

class FEngine;
class FMaterialInstance;
class FRenderer;
class FScene;

// ------------------------------------------------------------------------------------------------

class FView : public View {
public:
    using Range = utils::Range<uint32_t>;

    explicit FView(FEngine& engine);
    ~FView() noexcept;

    void terminate(FEngine& engine);



    void setScene(FScene* scene) { mScene = scene; }
    FScene const* getScene() const noexcept { return mScene; }
    FScene* getScene() noexcept { return mScene; }



    void setViewport(filament::Viewport const& viewport) noexcept;
    filament::Viewport const& getViewport() const noexcept {
        return mViewport;
    }

    bool getClearTargetColor() const noexcept {
        // don't clear the color buffer if we have a skybox
        return !isSkyboxVisible();
    }
    bool isSkyboxVisible() const noexcept;

    void setFrustumCullingEnabled(bool culling) noexcept { mCulling = culling; }
    bool isFrustumCullingEnabled() const noexcept { return mCulling; }

    void setFrontFaceWindingInverted(bool inverted) noexcept { mFrontFaceWindingInverted = inverted; }
    bool isFrontFaceWindingInverted() const noexcept { return mFrontFaceWindingInverted; }


    void setVisibleLayers(uint8_t select, uint8_t values) noexcept;
    uint8_t getVisibleLayers() const noexcept {
        return mVisibleLayers;
    }

    void setName(const char* name) noexcept {
        mName = utils::CString(name);
    }

    // returns the view's name. The pointer is owned by View.
    const char* getName() const noexcept {
        return mName.c_str_safe();
    }

    void prepareUpscaler(math::float2 scale) const noexcept;


    void prepareViewport(
            const filament::Viewport& physicalViewport,
            const filament::Viewport& logicalViewport) const noexcept;

    

   
    void prepareStructure(backend::Handle<backend::HwTexture> structure) const noexcept;
    void prepareShadow(backend::Handle<backend::HwTexture> structure) const noexcept;
    void prepareShadowMapping(bool highPrecision) const noexcept;

    void cleanupRenderPasses() const noexcept;
    void commitUniforms(backend::DriverApi& driver, const char* data, uint32_t byteCount) const noexcept;
    void commitFroxels(backend::DriverApi& driverApi) const noexcept;



    bool hasDirectionalLight() const noexcept { return mHasDirectionalLight; }
    bool hasDynamicLighting() const noexcept { return mHasDynamicLighting; }
    bool hasShadowing() const noexcept { return mHasShadowing; }
    bool needsShadowMap() const noexcept { return mNeedsShadowMap; }


    bool hasPicking() const noexcept { return mActivePickingQueriesList != nullptr; }




    void setShadowingEnabled(bool enabled) noexcept { mShadowingEnabled = enabled; }

    bool isShadowingEnabled() const noexcept { return mShadowingEnabled; }

    void setScreenSpaceRefractionEnabled(bool enabled) noexcept { mScreenSpaceRefractionEnabled = enabled; }

    bool isScreenSpaceRefractionEnabled() const noexcept { return mScreenSpaceRefractionEnabled; }


    void setStencilBufferEnabled(bool enabled) noexcept { mStencilBufferEnabled = enabled; }

    bool isStencilBufferEnabled() const noexcept { return mStencilBufferEnabled; }




    void setRenderTarget(FRenderTarget* renderTarget) noexcept {

        mRenderTarget = renderTarget;
    }

    FRenderTarget* getRenderTarget() const noexcept {
        return mRenderTarget;
    }


    


    bool hasPostProcessPass() const noexcept {
        return mHasPostProcessPass;
    }



    void setDynamicLightingOptions(float zLightNear, float zLightFar) noexcept
    {

    }

    void setPostProcessingEnabled(bool enabled) noexcept {
        mHasPostProcessPass = enabled;
    }

    

    Range const& getVisibleRenderables() const noexcept {
        return mVisibleRenderables;
    }

    Range const& getVisibleDirectionalShadowCasters() const noexcept {
        return mVisibleDirectionalShadowCasters;
    }

    Range const& getVisibleSpotShadowCasters() const noexcept {
        return mSpotLightShadowCasters;
    }




    backend::Handle<backend::HwRenderTarget> getRenderTargetHandle() const noexcept {
        backend::Handle<backend::HwRenderTarget> kEmptyHandle;
        return mRenderTarget == nullptr ? kEmptyHandle : mRenderTarget->getHwHandle();
    }

    backend::TargetBufferFlags getRenderTargetAttachmentMask() const noexcept {
        if (mRenderTarget == nullptr) {
            return backend::TargetBufferFlags::NONE;
        } else {
            return mRenderTarget->getAttachmentMask();
        }
    }


    // Clean-up the oldest frame and save the current frame information.
    // This is typically called after all operations for this View's rendering are complete.
    // (e.g.: after the FrameGraph execution).
    void commitFrameHistory(FEngine& engine) noexcept;

    // create the picking query
    View::PickingQuery& pick(uint32_t x, uint32_t y, backend::CallbackHandler* handler,
            View::PickingQueryResultCallback callback) noexcept;

    void executePickingQueries(backend::DriverApi& driver,
            backend::RenderTargetHandle handle, float scale) noexcept;

    void setMaterialGlobal(uint32_t index, math::float4 const& value);

    math::float4 getMaterialGlobal(uint32_t index) const;

    utils::Entity getFogEntity() const noexcept {
        return mFogEntity;
    }

private:

    struct FPickingQuery : public PickingQuery {
    private:
        FPickingQuery(uint32_t x, uint32_t y,
                backend::CallbackHandler* handler,
                View::PickingQueryResultCallback callback) noexcept
                : PickingQuery{}, x(x), y(y), handler(handler), callback(callback) {}
        ~FPickingQuery() noexcept = default;
    public:
        // TODO: use a small pool
        static FPickingQuery* get(uint32_t x, uint32_t y, backend::CallbackHandler* handler,
                View::PickingQueryResultCallback callback) noexcept {
            return new FPickingQuery(x, y, handler, callback);
        }
        static void put(FPickingQuery* pQuery) noexcept {
            delete pQuery;
        }
        mutable FPickingQuery* next = nullptr;
        // picking query parameters
        uint32_t const x;
        uint32_t const y;
        backend::CallbackHandler* const handler;
        View::PickingQueryResultCallback const callback;
        // picking query result
        PickingQueryResult result;
    };

    

    // Clean-up the whole history, free all resources. This is typically called when the View is
    // being terminated.
    void drainFrameHistory(FEngine& engine) noexcept;

    // we don't inline this one, because the function is quite large and there is not much to
    // gain from inlining.
    

    // these are accessed in the render loop, keep together
    backend::Handle<backend::HwBufferObject> mLightUbh;
    backend::Handle<backend::HwBufferObject> mRenderableUbh;

    mutable backend::BufferObjectHandle mFrameHandle;
    FScene* mScene = nullptr;
    

    

    filament::Viewport mViewport;

    bool mCulling = true;
    bool mFrontFaceWindingInverted = false;

    FRenderTarget* mRenderTarget = nullptr;

    uint8_t mVisibleLayers = 0x1;

    bool mShadowingEnabled = true;
    bool mScreenSpaceRefractionEnabled = true;
    bool mHasPostProcessPass = true;
    bool mStencilBufferEnabled = false;


    utils::Entity mFogEntity{};
    bool mIsStereoSupported : 1;

    math::float2 mScale = 1.0f;
    bool mIsDynamicResolutionSupported = false;


    FPickingQuery* mActivePickingQueriesList = nullptr;

    utils::CString mName;

    // the following values are set by prepare()
    Range mVisibleRenderables;
    Range mVisibleDirectionalShadowCasters;
    Range mSpotLightShadowCasters;
    uint32_t mRenderableUBOSize = 0;
    mutable bool mHasDirectionalLight = false;
    mutable bool mHasDynamicLighting = false;
    mutable bool mHasShadowing = false;
    mutable bool mNeedsShadowMap = false;


    std::array<math::float4, 4> mMaterialGlobals = {{
                                                            { 0, 0, 0, 1 },
                                                            { 0, 0, 0, 1 },
                                                            { 0, 0, 0, 1 },
                                                            { 0, 0, 0, 1 },
                                                    }};


};

FILAMENT_DOWNCAST(View)

} // namespace filament

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(_MSC_VER)
#pragma warning pop
#endif

#endif // TNT_FILAMENT_DETAILS_VIEW_H
