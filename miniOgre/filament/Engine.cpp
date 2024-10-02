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


#include <filament/Engine.h>
#include <filament/DriverEnums.h>
#include <utils/compiler.h>
#include <utils/Panic.h>
#include <utils/Entity.h>
#include <utils/EntityManager.h>
#include <stddef.h>
#include <stdint.h>

using namespace utils;

namespace filament {

    namespace backend {
        class Platform;
    }

    using namespace math;
    using namespace backend;

    void Engine::destroy(Engine* engine) {
       
    }

#if UTILS_HAS_THREADING
    Engine* Engine::getEngine(void* token) {
        return FEngine::getEngine(token);
    }
#endif

    void Engine::destroy(Engine** pEngine) {
        
    }

 

    Platform* Engine::getPlatform() const noexcept {
        return nullptr;
    }

    Renderer* Engine::createRenderer() noexcept {
        return nullptr;
    }

    View* Engine::createView() noexcept {
        return nullptr;
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
        return nullptr;
    }

    SwapChain* Engine::createSwapChain(uint32_t width, uint32_t height, uint64_t flags) noexcept {
        return nullptr;
    }

    bool Engine::destroy(const BufferObject* p) {
        return false;
    }

    bool Engine::destroy(const VertexBuffer* p) {
        return false;
    }

    bool Engine::destroy(const IndexBuffer* p) {
        return false;
    }

    bool Engine::destroy(const SkinningBuffer* p) {
        return false;
    }

    bool Engine::destroy(const MorphTargetBuffer* p) {
        return false;
    }

    bool Engine::destroy(const IndirectLight* p) {
        return false;
    }

    bool Engine::destroy(const Material* p) {
        return false;
    }

    bool Engine::destroy(const MaterialInstance* p) {
        return false;
    }

    bool Engine::destroy(const Renderer* p) {
        return false;
    }

    bool Engine::destroy(const View* p) {
        return false;
    }

    bool Engine::destroy(const Scene* p) {
        return false;
    }

    bool Engine::destroy(const Skybox* p) {
        return false;
    }

    bool Engine::destroy(const ColorGrading* p) {
        return false;
    }

    bool Engine::destroy(const Stream* p) {
        return false;
    }

    bool Engine::destroy(const Texture* p) {
        return false;
    }

    bool Engine::destroy(const RenderTarget* p) {
        return false;
    }

    bool Engine::destroy(const Fence* p) {
        return false;
    }

    bool Engine::destroy(const SwapChain* p) {
        return false;
    }

    bool Engine::destroy(const InstanceBuffer* p) {
        return false;
    }

    void Engine::destroy(Entity e) {
        
    }

    bool Engine::isValid(const BufferObject* p) const {
        return true;
    }
    bool Engine::isValid(const VertexBuffer* p) const {
        return true;
    }
    bool Engine::isValid(const Fence* p) const {
        return true;
    }
    bool Engine::isValid(const IndexBuffer* p) const {
        return true;
    }
    bool Engine::isValid(const SkinningBuffer* p) const {
        return true;
    }
    bool Engine::isValid(const MorphTargetBuffer* p) const {
        return true;
    }
    bool Engine::isValid(const IndirectLight* p) const {
        return true;
    }
    bool Engine::isValid(const Material* p) const {
        return true;
    }
    bool Engine::isValid(const Material* m, const MaterialInstance* p) const {
        return true;
    }
    bool Engine::isValidExpensive(const MaterialInstance* p) const {
        return true;
    }
    bool Engine::isValid(const Renderer* p) const {
        return true;
    }
    bool Engine::isValid(const Scene* p) const {
        return true;
    }
    bool Engine::isValid(const Skybox* p) const {
        return true;
    }
    bool Engine::isValid(const ColorGrading* p) const {
        return true;
    }
    bool Engine::isValid(const SwapChain* p) const {
        return true;
    }
    bool Engine::isValid(const Stream* p) const {
        return true;
    }
    bool Engine::isValid(const Texture* p) const {
        return true;
    }
    bool Engine::isValid(const RenderTarget* p) const {
        return true;
    }
    bool Engine::isValid(const View* p) const {
        return true;
    }
    bool Engine::isValid(const InstanceBuffer* p) const {
        return true;
    }

    void Engine::flushAndWait() {

    }

    void Engine::flush() {

    }

    utils::EntityManager& Engine::getEntityManager() noexcept {
        return utils::EntityManager::get();
    }

   
    void Engine::enableAccurateTranslations() noexcept {
       
    }

    void* Engine::streamAlloc(size_t size, size_t alignment) noexcept {
        return nullptr;
    }

    // The external-facing execute does a flush, and is meant only for single-threaded environments.
    // It also discards the boolean return value, which would otherwise indicate a thread exit.
    void Engine::execute() {
        ASSERT_PRECONDITION(!UTILS_HAS_THREADING, "Execute is meant for single-threaded platforms.");
        
    }


    bool Engine::isPaused() const noexcept {
        ASSERT_PRECONDITION(UTILS_HAS_THREADING, "Pause is meant for multi-threaded platforms.");
        return false;
    }

    void Engine::setPaused(bool paused) {
        ASSERT_PRECONDITION(UTILS_HAS_THREADING, "Pause is meant for multi-threaded platforms.");

    }

    

    void Engine::pumpMessageQueues() {
        
    }

    void Engine::setAutomaticInstancingEnabled(bool enable) noexcept {
        
    }

    bool Engine::isAutomaticInstancingEnabled() const noexcept {
        return false;
    }

    FeatureLevel Engine::getSupportedFeatureLevel() const noexcept {
        return FeatureLevel::FEATURE_LEVEL_0;
    }

    FeatureLevel Engine::setActiveFeatureLevel(FeatureLevel featureLevel) {
        return FeatureLevel::FEATURE_LEVEL_0;
    }

    FeatureLevel Engine::getActiveFeatureLevel() const noexcept {
        return FeatureLevel::FEATURE_LEVEL_0;
    }

    size_t Engine::getMaxAutomaticInstances() const noexcept {
        return 0;
    }

    const Engine::Config& Engine::getConfig() const noexcept {
        static Engine::Config dummy;
        return dummy;
    }

    bool Engine::isStereoSupported(StereoscopicType stereoscopicType) const noexcept {
        return false;
    }

    size_t Engine::getMaxStereoscopicEyes() noexcept {
        return 0;
    }

#if defined(__EMSCRIPTEN__)
    void Engine::resetBackendState() noexcept {
        downcast(this)->resetBackendState();
    }
#endif

} // namespace filament
