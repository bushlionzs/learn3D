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

#include "backend/FView.h"

namespace filament {

void View::setScene(Scene* scene) {
    
}

Scene* View::getScene() noexcept {
    return nullptr;
}


void View::setCamera(Camera* camera) noexcept {
    
}



void View::setViewport(filament::Viewport const& viewport) noexcept {
    downcast(this)->setViewport(viewport);
}

filament::Viewport const& View::getViewport() const noexcept {
    return downcast(this)->getViewport();
}

void View::setFrustumCullingEnabled(bool culling) noexcept {
    downcast(this)->setFrustumCullingEnabled(culling);
}

bool View::isFrustumCullingEnabled() const noexcept {
    return downcast(this)->isFrustumCullingEnabled();
}



void View::setVisibleLayers(uint8_t select, uint8_t values) noexcept {
    downcast(this)->setVisibleLayers(select, values);
}

void View::setName(const char* name) noexcept {
    downcast(this)->setName(name);
}

const char* View::getName() const noexcept {
    return downcast(this)->getName();
}

Camera const* View::getDirectionalLightCamera() const noexcept {
    return downcast(this)->getDirectionalLightCamera();
}

void View::setShadowingEnabled(bool enabled) noexcept {
    downcast(this)->setShadowingEnabled(enabled);
}

void View::setRenderTarget(RenderTarget* renderTarget) noexcept {
    downcast(this)->setRenderTarget(downcast(renderTarget));
}

RenderTarget* View::getRenderTarget() const noexcept {
    return downcast(this)->getRenderTarget();
}

void View::setSampleCount(uint8_t count) noexcept {
    downcast(this)->setSampleCount(count);
}

uint8_t View::getSampleCount() const noexcept {
    return downcast(this)->getSampleCount();
}


















void View::setFrontFaceWindingInverted(bool inverted) noexcept {
    downcast(this)->setFrontFaceWindingInverted(inverted);
}

bool View::isFrontFaceWindingInverted() const noexcept {
    return downcast(this)->isFrontFaceWindingInverted();
}

void View::setDynamicLightingOptions(float zLightNear, float zLightFar) noexcept {
    downcast(this)->setDynamicLightingOptions(zLightNear, zLightFar);
}







uint8_t View::getVisibleLayers() const noexcept {
  return downcast(this)->getVisibleLayers();
}

bool View::isShadowingEnabled() const noexcept {
    return downcast(this)->isShadowingEnabled();
}

void View::setScreenSpaceRefractionEnabled(bool enabled) noexcept {
    downcast(this)->setScreenSpaceRefractionEnabled(enabled);
}

bool View::isScreenSpaceRefractionEnabled() const noexcept {
    return downcast(this)->isScreenSpaceRefractionEnabled();
}

void View::setStencilBufferEnabled(bool enabled) noexcept {
    downcast(this)->setStencilBufferEnabled(enabled);
}

bool View::isStencilBufferEnabled() const noexcept {
    return downcast(this)->isStencilBufferEnabled();
}



View::PickingQuery& View::pick(uint32_t x, uint32_t y, backend::CallbackHandler* handler,
        View::PickingQueryResultCallback callback) noexcept {
    return downcast(this)->pick(x, y, handler, callback);
}

void View::setMaterialGlobal(uint32_t index, math::float4 const& value) {
    downcast(this)->setMaterialGlobal(index, value);
}

math::float4 View::getMaterialGlobal(uint32_t index) const {
    return downcast(this)->getMaterialGlobal(index);
}

utils::Entity View::getFogEntity() const noexcept {
    return downcast(this)->getFogEntity();
}

} // namespace filament
