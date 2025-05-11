/*
Copyright(c) 2016-2025 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ====================
#include <unordered_map>
#include <atomic>
//===============================

namespace spartan
{
    enum class Renderer_Option : uint32_t
    {
        Aabb,
        PickingRay,
        Grid,
        TransformHandle,
        SelectionOutline,
        Lights,
        PerformanceMetrics,
        Physics,
        Wireframe,
        Bloom,
        Fog,
        ScreenSpaceAmbientOcclusion,
        ScreenSpaceShadows,
        ScreenSpaceReflections,
        GlobalIllumination,
        MotionBlur,
        DepthOfField,
        FilmGrain,
        ChromaticAberration,
        Anisotropy,
        ShadowResolution,
        Antialiasing,
        Tonemapping,
        Upsampling,
        Sharpness,
        Hdr,
        WhitePoint,
        Gamma,
        Vsync,
        VariableRateShading,
        ResolutionScale,
        DynamicResolution,
        Max
    };

    enum class Renderer_Antialiasing : uint32_t
    {
        Disabled,
        Fxaa,
        Taa,
        TaaFxaa
    };

    enum class Renderer_Upsampling : uint32_t
    {
        Linear,
        Fsr3
    };

    enum class Renderer_RenderTarget : uint8_t
    {
        gbuffer_color,
        gbuffer_normal,
        gbuffer_material,
        gbuffer_velocity,
        gbuffer_depth,
        gbuffer_depth_occluders,
        gbuffer_depth_occluders_hiz,
        gbuffer_depth_output,
        brdf_specular_lut,
        light_diffuse,
        light_diffuse_gi,
        light_specular,
        light_specular_gi,
        light_shadow,
        light_volumetric,
        frame_render,
        frame_output,
        frame_output_2,
        source_gi,
        source_refraction,
        ssao,
        ssr,
        sss,
        skysphere,
        bloom,
        blur,
        outline,
        shading_rate,
        max
    };
    class Material;
    class Entity;
    class Camera;
    class Light;
    class Renderable;
    namespace math
    {
        class BoundingBox;
        class Frustum;
    }

    class Renderer
    {
    public:
        // core
        static void Initialize();
        static void Shutdown();
        static void Tick();

        // options
        template<typename T>
        static T GetOption(const Renderer_Option option) { return static_cast<T>(GetOptions()[option]); }
        static void SetOption(Renderer_Option option, float value);
        static std::unordered_map<Renderer_Option, float>& GetOptions();
        static void SetOptions(const std::unordered_map<Renderer_Option, float>& options);

        

        

        // wind
        static const Ogre::Vector3& GetWind();
        static void SetWind(const Ogre::Vector3& wind);

  

        // resolution render
        static const Ogre::Vector2& GetResolutionRender();
        static void SetResolutionRender(uint32_t width, uint32_t height, bool recreate_resources = true);

        // resolution output
        static const Ogre::Vector2& GetResolutionOutput();
        static void SetResolutionOutput(uint32_t width, uint32_t height, bool recreate_resources = true);

        static std::array<std::shared_ptr<Ogre::OgreTexture>, static_cast<uint32_t>(Renderer_RenderTarget::max)>& GetRenderTargets();

    private:
    

    
        // misc

        static uint32_t m_resource_index;
        static std::atomic<bool> m_initialized_resources;
        static std::mutex m_mutex_renderables;
        static uint32_t m_draw_call_count;
        static bool m_transparents_present;

        // bindless
        static bool m_bindless_samplers_dirty;
        static bool m_bindless_abbs_dirty;
        static bool m_bindless_materials_dirty;
        static bool m_bindless_lights_dirty;

        
    };
}
