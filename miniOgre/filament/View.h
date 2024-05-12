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

//! \file

#ifndef TNT_FILAMENT_VIEW_H
#define TNT_FILAMENT_VIEW_H


#include <filament/FilamentAPI.h>


#include <filament/DriverEnums.h>

#include <utils/compiler.h>
#include <utils/Entity.h>

#include <math/mathfwd.h>

namespace filament {

namespace backend {
class CallbackHandler;
} // namespace backend

class Camera;
class ColorGrading;
class MaterialInstance;
class RenderTarget;
class Scene;
class Viewport;

/**
 * A View encompasses all the state needed for rendering a Scene.
 *
 * Renderer::render() operates on View objects. These View objects specify important parameters
 * such as:
 *  - The Scene
 *  - The Camera
 *  - The Viewport
 *  - Some rendering parameters
 *
 * \note
 * View instances are heavy objects that internally cache a lot of data needed for rendering.
 * It is not advised for an application to use many View objects.
 *
 * For example, in a game, a View could be used for the main scene and another one for the
 * game's user interface. More View instances could be used for creating special effects (e.g.
 * a View is akin to a rendering pass).
 *
 *
 * @see Renderer, Scene, Camera, RenderTarget
 */
class UTILS_PUBLIC View : public FilamentAPI {
public:

    /**
     * Sets the View's name. Only useful for debugging.
     * @param name Pointer to the View's name. The string is copied.
     */
    void setName(const char* name) noexcept;

    /**
     * Returns the View's name
     *
     * @return a pointer owned by the View instance to the View's name.
     *
     * @attention Do *not* free the pointer or modify its content.
     */
    const char* getName() const noexcept;

    /**
     * Set this View instance's Scene.
     *
     * @param scene Associate the specified Scene to this View. A Scene can be associated to
     *              several View instances.\n
     *              \p scene can be nullptr to dissociate the currently set Scene
     *              from this View.\n
     *              The View doesn't take ownership of the Scene pointer (which
     *              acts as a reference).
     *
     * @note
     *  There is no reference-counting.
     *  Make sure to dissociate a Scene from all Views before destroying it.
     */
    void setScene(Scene* scene);

    /**
     * Returns the Scene currently associated with this View.
     * @return A pointer to the Scene associated to this View. nullptr if no Scene is set.
     */
    Scene* getScene() noexcept;

    /**
     * Returns the Scene currently associated with this View.
     * @return A pointer to the Scene associated to this View. nullptr if no Scene is set.
     */
    Scene const* getScene() const noexcept {
        return const_cast<View*>(this)->getScene();
    }

    /**
     * Specifies an offscreen render target to render into.
     *
     * By default, the view's associated render target is nullptr, which corresponds to the
     * SwapChain associated with the engine.
     *
     * A view with a custom render target cannot rely on Renderer::ClearOptions, which only apply
     * to the SwapChain. Such view can use a Skybox instead.
     *
     * @param renderTarget Render target associated with view, or nullptr for the swap chain.
     */
    void setRenderTarget(RenderTarget* renderTarget) noexcept;

    /**
     * Gets the offscreen render target associated with this view.
     *
     * Returns nullptr if the render target is the swap chain (which is default).
     *
     * @see setRenderTarget
     */
    RenderTarget* getRenderTarget() const noexcept;

    /**
     * Sets the rectangular region to render to.
     *
     * The viewport specifies where the content of the View (i.e. the Scene) is rendered in
     * the render target. The Render target is automatically clipped to the Viewport.
     *
     * @param viewport  The Viewport to render the Scene into. The Viewport is a value-type, it is
     *                  therefore copied. The parameter can be discarded after this call returns.
     */
    void setViewport(Viewport const& viewport) noexcept;

    /**
     * Returns the rectangular region that gets rendered to.
     * @return A constant reference to View's viewport.
     */
    Viewport const& getViewport() const noexcept;

    /**
     * Sets this View's Camera.
     *
     * @param camera    Associate the specified Camera to this View. A Camera can be associated to
     *                  several View instances.\n
     *                  \p camera can be nullptr to dissociate the currently set Camera from this
     *                  View.\n
     *                  The View doesn't take ownership of the Camera pointer (which
     *                  acts as a reference).
     *
     * @note
     *  There is no reference-counting.
     *  Make sure to dissociate a Camera from all Views before destroying it.
     */
    void setCamera(Camera* camera) noexcept;

    /**
     * Returns the Camera currently associated with this View.
     * @return A reference to the Camera associated to this View.
     */
    Camera& getCamera() noexcept;

    /**
     * Returns the Camera currently associated with this View.
     * @return A reference to the Camera associated to this View.
     */
    Camera const& getCamera() const noexcept {
        return const_cast<View*>(this)->getCamera();
    }

    

    /**
     * Sets which layers are visible.
     *
     * Renderable objects can have one or several layers associated to them. Layers are
     * represented with an 8-bits bitmask, where each bit corresponds to a layer.
     *
     * This call sets which of those layers are visible. Renderables in invisible layers won't be
     * rendered.
     *
     * @param select    a bitmask specifying which layer to set or clear using \p values.
     * @param values    a bitmask where each bit sets the visibility of the corresponding layer
     *                  (1: visible, 0: invisible), only layers in \p select are affected.
     *
     * @see RenderableManager::setLayerMask().
     *
     * @note By default only layer 0 (bitmask 0x01) is visible.
     * @note This is a convenient way to quickly show or hide sets of Renderable objects.
     */
    void setVisibleLayers(uint8_t select, uint8_t values) noexcept;

    /**
     * Helper function to enable or disable a visibility layer.
     * @param layer     layer between 0 and 7 to enable or disable
     * @param enabled   true to enable the layer, false to disable it
     * @see RenderableManager::setVisibleLayers()
     */
    inline void setLayerEnabled(size_t layer, bool enabled) noexcept {
        const uint8_t mask = 1u << layer;
        setVisibleLayers(mask, enabled ? mask : 0);
    }

    /**
     * Get the visible layers.
     *
     * @see View::setVisibleLayers()
     */
    uint8_t getVisibleLayers() const noexcept;

    /**
     * Enables or disables shadow mapping. Enabled by default.
     *
     * @param enabled true enables shadow mapping, false disables it.
     *
     * @see LightManager::Builder::castShadows(),
     *      RenderableManager::Builder::receiveShadows(),
     *      RenderableManager::Builder::castShadows(),
     */
    void setShadowingEnabled(bool enabled) noexcept;

    /**
     * @return whether shadowing is enabled
     */
    bool isShadowingEnabled() const noexcept;

    /**
     * Enables or disables screen space refraction. Enabled by default.
     *
     * @param enabled true enables screen space refraction, false disables it.
     */
    void setScreenSpaceRefractionEnabled(bool enabled) noexcept;

    /**
     * @return whether screen space refraction is enabled
     */
    bool isScreenSpaceRefractionEnabled() const noexcept;

    /**
     * Sets how many samples are to be used for MSAA in the post-process stage.
     * Default is 1 and disables MSAA.
     *
     * @param count number of samples to use for multi-sampled anti-aliasing.\n
     *              0: treated as 1
     *              1: no anti-aliasing
     *              n: sample count. Effective sample could be different depending on the
     *                 GPU capabilities.
     *
     * @note Anti-aliasing can also be performed in the post-processing stage, generally at lower
     *       cost. See setAntialiasing.
     *
     * @see setAntialiasing
     * @deprecated use setMultiSampleAntiAliasingOptions instead
     */
    UTILS_DEPRECATED
    void setSampleCount(uint8_t count = 1) noexcept;

    /**
     * Returns the sample count set by setSampleCount(). Effective sample count could be different.
     * A value of 0 or 1 means MSAA is disabled.
     *
     * @return value set by setSampleCount().
     * @deprecated use getMultiSampleAntiAliasingOptions instead
     */
    UTILS_DEPRECATED
    uint8_t getSampleCount() const noexcept;

   

    

    /**
     * Sets this View's color grading transforms.
     *
     * @param colorGrading Associate the specified ColorGrading to this View. A ColorGrading can be
     *                     associated to several View instances.\n
     *                     \p colorGrading can be nullptr to dissociate the currently set
     *                     ColorGrading from this View. Doing so will revert to the use of the
     *                     default color grading transforms.\n
     *                     The View doesn't take ownership of the ColorGrading pointer (which
     *                     acts as a reference).
     *
     * @note
     *  There is no reference-counting.
     *  Make sure to dissociate a ColorGrading from all Views before destroying it.
     */
    void setColorGrading(ColorGrading* colorGrading) noexcept;

    /**
     * Returns the color grading transforms currently associated to this view.
     * @return A pointer to the ColorGrading associated to this View.
     */
    const ColorGrading* getColorGrading() const noexcept;

   

    /**
     * Sets options relative to dynamic lighting for this view.
     *
     * @param zLightNear Distance from the camera where the lights are expected to shine.
     *                   This parameter can affect performance and is useful because depending
     *                   on the scene, lights that shine close to the camera may not be
     *                   visible -- in this case, using a larger value can improve performance.
     *                   e.g. when standing and looking straight, several meters of the ground
     *                   isn't visible and if lights are expected to shine there, there is no
     *                   point using a short zLightNear. (Default 5m).
     *
     * @param zLightFar Distance from the camera after which lights are not expected to be visible.
     *                  Similarly to zLightNear, setting this value properly can improve
     *                  performance. (Default 100m).
     *
     *
     * Together zLightNear and zLightFar must be chosen so that the visible influence of lights
     * is spread between these two values.
     *
     */
    void setDynamicLightingOptions(float zLightNear, float zLightFar) noexcept;

    

    /**
     * Enables or disables post processing. Enabled by default.
     *
     * Post-processing includes:
     *  - Depth-of-field
     *  - Bloom
     *  - Vignetting
     *  - Temporal Anti-aliasing (TAA)
     *  - Color grading & gamma encoding
     *  - Dithering
     *  - FXAA
     *  - Dynamic scaling
     *
     * Disabling post-processing forgoes color correctness as well as some anti-aliasing techniques
     * and should only be used for debugging, UI overlays or when using custom render targets
     * (see RenderTarget).
     *
     * @param enabled true enables post processing, false disables it.
     *
     * @see setBloomOptions, setColorGrading, setAntiAliasing, setDithering, setSampleCount
     */
    void setPostProcessingEnabled(bool enabled) noexcept;

    //! Returns true if post-processing is enabled. See setPostProcessingEnabled() for more info.
    bool isPostProcessingEnabled() const noexcept;

    /**
     * Inverts the winding order of front faces. By default front faces use a counter-clockwise
     * winding order. When the winding order is inverted, front faces are faces with a clockwise
     * winding order.
     *
     * Changing the winding order will directly affect the culling mode in materials
     * (see Material::getCullingMode()).
     *
     * Inverting the winding order of front faces is useful when rendering mirrored reflections
     * (water, mirror surfaces, front camera in AR, etc.).
     *
     * @param inverted True to invert front faces, false otherwise.
     */
    void setFrontFaceWindingInverted(bool inverted) noexcept;

    /**
     * Returns true if the winding order of front faces is inverted.
     * See setFrontFaceWindingInverted() for more information.
     */
    bool isFrontFaceWindingInverted() const noexcept;

    /**
     * Enables use of the stencil buffer.
     *
     * The stencil buffer is an 8-bit, per-fragment unsigned integer stored alongside the depth
     * buffer. The stencil buffer is cleared at the beginning of a frame and discarded after the
     * color pass.
     *
     * Each fragment's stencil value is set during rasterization by specifying stencil operations on
     * a Material. The stencil buffer can be used as a mask for later rendering by setting a
     * Material's stencil comparison function and reference value. Fragments that don't pass the
     * stencil test are then discarded.
     *
     * If post-processing is disabled, then the SwapChain must have the CONFIG_HAS_STENCIL_BUFFER
     * flag set in order to use the stencil buffer.
     *
     * A renderable's priority (see RenderableManager::setPriority) is useful to control the order
     * in which primitives are drawn.
     *
     * @param enabled True to enable the stencil buffer, false disables it (default)
     */
    void setStencilBufferEnabled(bool enabled) noexcept;

    /**
     * Returns true if the stencil buffer is enabled.
     * See setStencilBufferEnabled() for more information.
     */
    bool isStencilBufferEnabled() const noexcept;

    

    // for debugging...

    //! debugging: allows to entirely disable frustum culling. (culling enabled by default).
    void setFrustumCullingEnabled(bool culling) noexcept;

    //! debugging: returns whether frustum culling is enabled.
    bool isFrustumCullingEnabled() const noexcept;

    //! debugging: sets the Camera used for rendering. It may be different from the culling camera.
    void setDebugCamera(Camera* camera) noexcept;

    //! debugging: returns a Camera from the point of view of *the* dominant directional light used for shadowing.
    Camera const* getDirectionalLightCamera() const noexcept;


    /** Result of a picking query */
    struct PickingQueryResult {
        utils::Entity renderable{};     //! RenderableManager Entity at the queried coordinates
        float depth{};                  //! Depth buffer value (1 (near plane) to 0 (infinity))
        uint32_t reserved1{};
        uint32_t reserved2{};
        /**
         * screen space coordinates in GL convention, this can be used to compute the view or
         * world space position of the picking hit. For e.g.:
         *   clip_space_position  = (fragCoords.xy / viewport.wh, fragCoords.z) * 2.0 - 1.0
         *   view_space_position  = inverse(projection) * clip_space_position
         *   world_space_position = model * view_space_position
         *
         * The viewport, projection and model matrices can be obtained from Camera. Because
         * pick() has some latency, it might be more accurate to obtain these values at the
         * time the View::pick() call is made.
         *
         * Note: if the Engine is running at FEATURE_LEVEL_0, the precision or `depth` and
         *       `fragCoords.z` is only 8-bits.
         */
        math::float3 fragCoords;        //! screen space coordinates in GL convention
    };

    /** User data for PickingQueryResultCallback */
    struct PickingQuery {
        // note: this is enough to store a std::function<> -- just saying...
        void* storage[4];
    };

    /** callback type used for picking queries. */
    using PickingQueryResultCallback = void(*)(PickingQueryResult const& result, PickingQuery* pq);

    /**
     * Helper for creating a picking query from Foo::method, by pointer.
     * e.g.: pick<Foo, &Foo::bar>(x, y, &foo);
     *
     * @tparam T        Class of the method to call (e.g.: Foo)
     * @tparam method   Method to call on T (e.g.: &Foo::bar)
     * @param x         Horizontal coordinate to query in the viewport with origin on the left.
     * @param y         Vertical coordinate to query on the viewport with origin at the bottom.
     * @param instance  A pointer to an instance of T
     * @param handler   Handler to dispatch the callback or nullptr for the default handler.
     */
    template<typename T, void(T::*method)(PickingQueryResult const&)>
    void pick(uint32_t x, uint32_t y, T* instance, backend::CallbackHandler* handler = nullptr) noexcept {
        PickingQuery& query = pick(x, y, [](PickingQueryResult const& result, PickingQuery* pq) {
            void* user = pq->storage;
            (*static_cast<T**>(user)->*method)(result);
        }, handler);
        query.storage[0] = instance;
    }

    /**
     * Helper for creating a picking query from Foo::method, by copy for a small object
     * e.g.: pick<Foo, &Foo::bar>(x, y, foo);
     *
     * @tparam T        Class of the method to call (e.g.: Foo)
     * @tparam method   Method to call on T (e.g.: &Foo::bar)
     * @param x         Horizontal coordinate to query in the viewport with origin on the left.
     * @param y         Vertical coordinate to query on the viewport with origin at the bottom.
     * @param instance  An instance of T
     * @param handler   Handler to dispatch the callback or nullptr for the default handler.
     */
    template<typename T, void(T::*method)(PickingQueryResult const&)>
    void pick(uint32_t x, uint32_t y, T instance, backend::CallbackHandler* handler = nullptr) noexcept {
        static_assert(sizeof(instance) <= sizeof(PickingQuery::storage), "user data too large");
        PickingQuery& query = pick(x, y, [](PickingQueryResult const& result, PickingQuery* pq) {
            void* user = pq->storage;
            T* that = static_cast<T*>(user);
            (that->*method)(result);
            that->~T();
        }, handler);
        new(query.storage) T(std::move(instance));
    }

    /**
     * Helper for creating a picking query from a small functor
     * e.g.: pick(x, y, [](PickingQueryResult const& result){});
     *
     * @param x         Horizontal coordinate to query in the viewport with origin on the left.
     * @param y         Vertical coordinate to query on the viewport with origin at the bottom.
     * @param functor   A functor, typically a lambda function.
     * @param handler   Handler to dispatch the callback or nullptr for the default handler.
     */
    template<typename T>
    void pick(uint32_t x, uint32_t y, T functor, backend::CallbackHandler* handler = nullptr) noexcept {
        static_assert(sizeof(functor) <= sizeof(PickingQuery::storage), "functor too large");
        PickingQuery& query = pick(x, y, handler,
                (PickingQueryResultCallback)[](PickingQueryResult const& result, PickingQuery* pq) {
            void* user = pq->storage;
            T& that = *static_cast<T*>(user);
            that(result);
            that.~T();
        });
        new(query.storage) T(std::move(functor));
    }

    /**
     * Creates a picking query. Multiple queries can be created (e.g.: multi-touch).
     * Picking queries are all executed when Renderer::render() is called on this View.
     * The provided callback is guaranteed to be called at some point in the future.
     *
     * Typically it takes a couple frames to receive the result of a picking query.
     *
     * @param x         Horizontal coordinate to query in the viewport with origin on the left.
     * @param y         Vertical coordinate to query on the viewport with origin at the bottom.
     * @param callback  User callback, called when the picking query result is available.
     * @param handler   Handler to dispatch the callback or nullptr for the default handler.
     * @return          A reference to a PickingQuery structure, which can be used to store up to
     *                  8*sizeof(void*) bytes of user data. This user data is later accessible
     *                  in the PickingQueryResultCallback callback 3rd parameter.
     */
    PickingQuery& pick(uint32_t x, uint32_t y, backend::CallbackHandler* handler,
            PickingQueryResultCallback callback) noexcept;

    /**
     * Set the value of material global variables. There are up-to four such variable each of
     * type float4. These variables can be read in a user Material with
     * `getMaterialGlobal{0|1|2|3}()`. All variable start with a default value of { 0, 0, 0, 1 }
     *
     * @param index index of the variable to set between 0 and 3.
     * @param value new value for the variable.
     * @see getMaterialGlobal
     */
    void setMaterialGlobal(uint32_t index, math::float4 const& value);

    /**
     * Get the value of the material global variables.
     * All variable start with a default value of { 0, 0, 0, 1 }
     *
     * @param index index of the variable to set between 0 and 3.
     * @return current value of the variable.
     * @see setMaterialGlobal
     */
    math::float4 getMaterialGlobal(uint32_t index) const;

    /**
     * Get an Entity representing the large scale fog object.
     * This entity is always inherited by the View's Scene.
     *
     * It is for example possible to create a TransformManager component with this
     * Entity and apply a transformation globally on the fog.
     *
     * @return an Entity representing the large scale fog object.
     */
    utils::Entity getFogEntity() const noexcept;

    /**
     * List of available ambient occlusion techniques
     * @deprecated use AmbientOcclusionOptions::enabled instead
     */
    enum class UTILS_DEPRECATED AmbientOcclusion : uint8_t {
        NONE = 0,       //!< No Ambient Occlusion
        SSAO = 1        //!< Basic, sampling SSAO
    };

    /**
     * Activates or deactivates ambient occlusion.
     * @deprecated use setAmbientOcclusionOptions() instead
     * @see setAmbientOcclusionOptions
     *
     * @param ambientOcclusion Type of ambient occlusion to use.
     */
    UTILS_DEPRECATED
    void setAmbientOcclusion(AmbientOcclusion ambientOcclusion) noexcept;

    /**
     * Queries the type of ambient occlusion active for this View.
     * @deprecated use getAmbientOcclusionOptions() instead
     * @see getAmbientOcclusionOptions
     *
     * @return ambient occlusion type.
     */
    UTILS_DEPRECATED
    AmbientOcclusion getAmbientOcclusion() const noexcept;

protected:
    // prevent heap allocation
    ~View() = default;
};

} // namespace filament

#endif // TNT_FILAMENT_VIEW_H
