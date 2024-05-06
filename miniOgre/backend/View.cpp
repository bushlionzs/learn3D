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

#include "backend/View.h"


#include "ResourceAllocator.h"

#include "backend/Engine.h"

#include "backend/RenderTarget.h"
#include "backend/Renderer.h"


#include <utils/Profiler.h>
#include <utils/Slice.h>
#include <utils/Systrace.h>
#include <utils/debug.h>
#include <utils/Zip2Iterator.h>

#include <math/scalar.h>
#include <math/fast.h>

#include <memory>

using namespace utils;

namespace filament {

using namespace backend;
using namespace math;

static constexpr float PID_CONTROLLER_Ki = 0.002f;
static constexpr float PID_CONTROLLER_Kd = 0.0f;

FView::FView(FEngine& engine)
        :
          mFogEntity(engine.getEntityManager().create()),
          mIsStereoSupported(engine.getDriverApi().isStereoSupported(engine.getConfig().stereoscopicType))
{
    DriverApi& driver = engine.getDriverApi();

    mIsDynamicResolutionSupported = driver.isFrameTimeSupported();

}

FView::~FView() noexcept = default;

void FView::terminate(FEngine& engine) {
    // Here we would cleanly free resources we've allocated, or we own (currently none).

    while (mActivePickingQueriesList) {
        FPickingQuery* const pQuery = mActivePickingQueriesList;
        mActivePickingQueriesList = pQuery->next;
        pQuery->callback(pQuery->result, pQuery);
        FPickingQuery::put(pQuery);
    }

    DriverApi& driver = engine.getDriverApi();
    driver.destroyBufferObject(mLightUbh);
    driver.destroyBufferObject(mRenderableUbh);
    drainFrameHistory(engine);


    engine.getEntityManager().destroy(mFogEntity);
}

void FView::setViewport(filament::Viewport const& viewport) noexcept {
    // catch the cases were user had an underflow and didn't catch it.
    assert((int32_t)viewport.width > 0);
    assert((int32_t)viewport.height > 0);
    mViewport = viewport;
}





void FView::setVisibleLayers(uint8_t select, uint8_t values) noexcept {
    mVisibleLayers = (mVisibleLayers & ~select) | (values & select);
}



void FView::prepareViewport(
    const filament::Viewport& physicalViewport,
    const filament::Viewport& logicalViewport) const noexcept
{
}


void FView::commitUniforms(backend::DriverApi& driver) const noexcept
{

}





void FView::executePickingQueries(backend::DriverApi& driver,
        backend::RenderTargetHandle handle, float scale) noexcept {

    while (mActivePickingQueriesList) {
        FPickingQuery* const pQuery = mActivePickingQueriesList;
        mActivePickingQueriesList = pQuery->next;

        // adjust for dynamic resolution and structure buffer scale
        const uint32_t x = uint32_t(float(pQuery->x) * (scale * mScale.x));
        const uint32_t y = uint32_t(float(pQuery->y) * (scale * mScale.y));

        if (UTILS_UNLIKELY(driver.getFeatureLevel() == FeatureLevel::FEATURE_LEVEL_0)) {
            driver.readPixels(handle, x, y, 1, 1, {
                    &pQuery->result.reserved1, 4u, // 4
                    backend::PixelDataFormat::RGBA, backend::PixelDataType::UBYTE,
                    pQuery->handler, [](void*, size_t, void* user) {
                        FPickingQuery* pQuery = static_cast<FPickingQuery*>(user);
                        uint8_t const* const p =
                                reinterpret_cast<uint8_t const *>(&pQuery->result.reserved1);
                        uint32_t const r = p[0];
                        uint32_t const g = p[1];
                        uint32_t const b = p[2];
                        uint32_t const a = p[3];
                        int32_t const identity = int32_t(a << 16u | (b << 8u) | g);
                        float const depth = float(r) / 255.0f;
                        pQuery->result.renderable = Entity::import(identity);
                        pQuery->result.depth = depth;
                        pQuery->result.fragCoords = {
                                pQuery->x, pQuery->y, float(1.0 - depth) };
                        pQuery->callback(pQuery->result, pQuery);
                        FPickingQuery::put(pQuery);
                    }, pQuery
            });
        } else {
            driver.readPixels(handle, x, y, 1, 1, {
                    &pQuery->result.renderable, 4u * 4u, // 4*float
                    backend::PixelDataFormat::RG, backend::PixelDataType::FLOAT,
                    pQuery->handler, [](void*, size_t, void* user) {
                        FPickingQuery* const pQuery = static_cast<FPickingQuery*>(user);
                        // pQuery->result.renderable already contains the right value!
                        pQuery->result.fragCoords = {
                                pQuery->x, pQuery->y, float(1.0 - pQuery->result.depth) };
                        pQuery->callback(pQuery->result, pQuery);
                        FPickingQuery::put(pQuery);
                    }, pQuery
            });
        }
    }
}


void FView::commitFrameHistory(FEngine& engine) noexcept
{

}

void FView::drainFrameHistory(FEngine& engine) noexcept
{

}

View::PickingQuery& FView::pick(uint32_t x, uint32_t y, backend::CallbackHandler* handler,
        View::PickingQueryResultCallback callback) noexcept {
    FPickingQuery* pQuery = FPickingQuery::get(x, y, handler, callback);
    pQuery->next = mActivePickingQueriesList;
    mActivePickingQueriesList = pQuery;
    return *pQuery;
}


void FView::setMaterialGlobal(uint32_t index, float4 const& value) {
    ASSERT_PRECONDITION(index < 4, "material global variable index (%u) out of range", +index);
    mMaterialGlobals[index] = value;
}

math::float4 FView::getMaterialGlobal(uint32_t index) const {
    ASSERT_PRECONDITION(index < 4, "material global variable index (%u) out of range", +index);
    return mMaterialGlobals[index];
}

} // namespace filament
