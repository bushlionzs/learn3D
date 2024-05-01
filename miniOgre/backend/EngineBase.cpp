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

#include <backend/Engine.h>
#include <backend/SwapChain.h>
#include <backend/DriverEnums.h>
#include <backend/Renderer.h>
#include <backend/view.h>
#include <utils/compiler.h>
#include <utils/Panic.h>
#include <utils/JobSystem.h>
#include <utils/EntityManager.h>

using namespace utils;

namespace filament {

using namespace math;
using namespace backend;


void Engine::destroy(Engine* engine) {
    
}

#if UTILS_HAS_THREADING
Engine* Engine::getEngine(void* token) {
    return nullptr;
}
#endif

void Engine::destroy(Engine** pEngine) {

}

// -----------------------------------------------------------------------------------------------
// Resource management
// -----------------------------------------------------------------------------------------------




Renderer* Engine::createRenderer() noexcept {
    return downcast(this)->createRenderer();
}

View* Engine::createView() noexcept {
    return downcast(this)->createView();
}

Scene* Engine::createScene() noexcept {
    return nullptr;
}

Camera* Engine::createCamera(Entity entity) noexcept {
    return nullptr;
}

Camera* Engine::getCameraComponent(utils::Entity entity) noexcept {
    return nullptr;
}

void Engine::destroyCameraComponent(utils::Entity entity) noexcept {
    
}

Fence* Engine::createFence() noexcept {
    return nullptr;
}

SwapChain* Engine::createSwapChain(void* nativeWindow, uint64_t flags) noexcept {
    return downcast(this)->createSwapChain(nativeWindow, flags);
}

SwapChain* Engine::createSwapChain(uint32_t width, uint32_t height, uint64_t flags) noexcept {
    return nullptr;
}

bool Engine::destroy(const BufferObject* p) {
    return true;
}

bool Engine::destroy(const VertexBuffer* p) {
    return true;
}

bool Engine::destroy(const IndexBuffer* p) {
    return true;
}

bool Engine::destroy(const SkinningBuffer* p) {
    return true;
}

bool Engine::destroy(const MorphTargetBuffer* p) {
    return true;
}

bool Engine::destroy(const IndirectLight* p) {
    return true;
}

bool Engine::destroy(const Material* p) {
    return true;
}

bool Engine::destroy(const MaterialInstance* p) {
    return true;
}

bool Engine::destroy(const Renderer* p) {
    return true;
}

bool Engine::destroy(const View* p) {
    return true;
}

bool Engine::destroy(const Scene* p) {
    return true;
}

bool Engine::destroy(const Skybox* p) {
    return true;
}


bool Engine::destroy(const Stream* p) {
    return true;
}

bool Engine::destroy(const Texture* p) {
    return true;
}

bool Engine::destroy(const RenderTarget* p) {
    return true;
}

bool Engine::destroy(const Fence* p) {
    return true;
}

bool Engine::destroy(const SwapChain* p) {
    return true;
}

bool Engine::destroy(const InstanceBuffer* p) {
    return true;
}

void Engine::destroy(Entity e) {
   
}

bool Engine::isValid(const BufferObject* p) {
    return false;
}
bool Engine::isValid(const VertexBuffer* p) {
    return false;
}
bool Engine::isValid(const Fence* p) {
    return false;
}
bool Engine::isValid(const IndexBuffer* p) {
    return false;
}
bool Engine::isValid(const SkinningBuffer* p) {
    return false;
}
bool Engine::isValid(const MorphTargetBuffer* p) {
    return false;
}
bool Engine::isValid(const IndirectLight* p) {
    return false;
}
bool Engine::isValid(const Material* p) {
    return false;
}
bool Engine::isValid(const Renderer* p) {
    return false;
}
bool Engine::isValid(const Scene* p) {
    return false;
}
bool Engine::isValid(const Skybox* p) {
    return false;
}

bool Engine::isValid(const SwapChain* p) {
    return false;
}
bool Engine::isValid(const Stream* p) {
    return false;
}
bool Engine::isValid(const Texture* p) {
    return false;
}
bool Engine::isValid(const RenderTarget* p) {
    return false;
}
bool Engine::isValid(const View* p) {
    return false;
}
bool Engine::isValid(const InstanceBuffer* p) {
    return false;
}

void Engine::flushAndWait() {
    downcast(this)->flushAndWait();
}

void Engine::flush() {
    downcast(this)->flush();
}

utils::EntityManager& Engine::getEntityManager() noexcept {
    return utils::EntityManager::get();
}


Platform* Engine::getPlatform() const noexcept
{
    return nullptr;
}

void* Engine::streamAlloc(size_t size, size_t alignment) noexcept {
    return nullptr;
}

// The external-facing execute does a flush, and is meant only for single-threaded environments.
// It also discards the boolean return value, which would otherwise indicate a thread exit.
void Engine::execute() {
    
}

utils::JobSystem& Engine::getJobSystem() noexcept {
    static utils::JobSystem js(6,1);
    return js;
}


void Engine::pumpMessageQueues() {
    
}



#if defined(__EMSCRIPTEN__)
void Engine::resetBackendState() noexcept {
    downcast(this)->resetBackendState();
}
#endif

} // namespace filament
