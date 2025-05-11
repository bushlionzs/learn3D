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

//= INCLUDES ===============================
#include <OgreHeader.h>
#include "Renderer.h"
#include "Material.h"
#include "ThreadPool.h"
#include "../Profiling/Profiler.h"
#include "../World/Entity.h"
#include "../World/Components/Light.h"
#include "../World/Components/Camera.h"
#include "../World/Components/AudioSource.h"
//==========================================

//= NAMESPACES ===============
using namespace std;
using namespace spartan::math;
//============================

namespace spartan
{
  

    // misc
    bool wants_to_present                                         = false;
    uint32_t Renderer::m_resource_index                           = 0;
    atomic<bool> Renderer::m_initialized_resources                = false;
    bool Renderer::m_transparents_present                         = false;
    bool Renderer::m_bindless_samplers_dirty                      = true;
    bool Renderer::m_bindless_abbs_dirty                          = true;
    bool Renderer::m_bindless_materials_dirty                     = true;
    bool Renderer::m_bindless_lights_dirty                        = true;


    namespace
    {
 
        const uint8_t swap_chain_buffer_count = 2;

        // misc
        unordered_map<Renderer_Option, float> m_options;
        uint64_t frame_num                   = 0;
  
        const uint32_t resolution_shadow_min = 128;
        float near_plane                     = 0.0f;
        float far_plane                      = 1.0f;
        bool dirty_orthographic_projection   = true;

        void dynamic_resolution()
        {
        }
    }

    void Renderer::SetOption(Renderer_Option option, float value)
    {
        
        assert_invariant(false);
    }
    static unordered_map<Renderer_Option, float> options;
    void Renderer::SetOptions(const unordered_map<Renderer_Option, float>& options)
    {
        
    }

    unordered_map<Renderer_Option, float>& Renderer::GetOptions()
    {
        
        return m_options;
    }
    static Ogre::Vector3 mWind;
    const Ogre::Vector3& Renderer::GetWind()
    {
        return mWind;
    }

    void Renderer::SetWind(const Ogre::Vector3& wind)
    {
        mWind = wind;
    }

    const Ogre::Vector2& Renderer::GetResolutionRender()
    {
        static Ogre::Vector2 aa;
        return aa;
    }

    void Renderer::SetResolutionRender(uint32_t width, uint32_t height, bool recreate_resources)
    {

    }

    const Ogre::Vector2& Renderer::GetResolutionOutput()
    {
        static Ogre::Vector2 aa;
        return aa;
    }

    void Renderer::SetResolutionOutput(uint32_t width, uint32_t height, bool recreate_resources)
    {

    }
    array<shared_ptr<Ogre::OgreTexture>, static_cast<uint32_t>(Renderer_RenderTarget::max)> render_targets;
    std::array<std::shared_ptr<Ogre::OgreTexture>, static_cast<uint32_t>(Renderer_RenderTarget::max)>& Renderer::GetRenderTargets()
    {
        return render_targets;
    }

}
