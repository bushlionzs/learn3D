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

//= INCLUDES =========================
#include <OgreHeader.h>
#include "Settings.h"
#include "SDLWindow.h"
#include "Renderer.h"
#include <string>
#include <vector>
#include <mutex>
//====================================

//= NAMESPACES ================
using namespace std;
//=============================

namespace spartan
{
    namespace
    {
        bool m_has_loaded_user_settings = false;
        std::string file_path = "spartan.xml";
        mutex mutex_register;

        const char* renderer_option_to_string(const Renderer_Option option)
        {
            switch (option)
            {
            case Renderer_Option::Aabb:                        return "Aabb";
            case Renderer_Option::PickingRay:                  return "PickingRay";
            case Renderer_Option::Grid:                        return "Grid";
            case Renderer_Option::TransformHandle:             return "TransformHandle";
            case Renderer_Option::SelectionOutline:            return "SelectionOutline";
            case Renderer_Option::Lights:                      return "Lights";
            case Renderer_Option::PerformanceMetrics:          return "PerformanceMetrics";
            case Renderer_Option::Physics:                     return "Physics";
            case Renderer_Option::Wireframe:                   return "Wireframe";
            case Renderer_Option::Bloom:                       return "Bloom";
            case Renderer_Option::Fog:                         return "Fog";
            case Renderer_Option::ScreenSpaceAmbientOcclusion: return "ScreenSpaceAmbientOcclusion";
            case Renderer_Option::ScreenSpaceShadows:          return "ScreenSpaceShadows";
            case Renderer_Option::ScreenSpaceReflections:      return "ScreenSpaceReflections";
            case Renderer_Option::GlobalIllumination:          return "GlobalIllumination";
            case Renderer_Option::MotionBlur:                  return "MotionBlur";
            case Renderer_Option::DepthOfField:                return "DepthOfField";
            case Renderer_Option::FilmGrain:                   return "FilmGrain";
            case Renderer_Option::ChromaticAberration:         return "ChromaticAberration";
            case Renderer_Option::Anisotropy:                  return "Anisotropy";
            case Renderer_Option::ShadowResolution:            return "ShadowResolution";
            case Renderer_Option::WhitePoint:                  return "WhitePoint";
            case Renderer_Option::Antialiasing:                return "Antialiasing";
            case Renderer_Option::Tonemapping:                 return "Tonemapping";
            case Renderer_Option::Upsampling:                  return "Upsampling";
            case Renderer_Option::Sharpness:                   return "Sharpness";
            case Renderer_Option::Hdr:                         return "Hdr";
            case Renderer_Option::Gamma:                       return "Gamma";
            case Renderer_Option::Vsync:                       return "Vsync";
            case Renderer_Option::VariableRateShading:         return "VariableRateShading";
            case Renderer_Option::ResolutionScale:             return "ResolutionScale";
            case Renderer_Option::DynamicResolution:           return "DynamicResolution";
            default:
            {
                assert_invariant(false);
                return "";
            }
            }
        }

        void save()
        {

        }

        void load()
        {

            m_has_loaded_user_settings = true;
        }
    }

    void Settings::Initialize()
    {
       
    }
    
    void Settings::Shutdown()
    {
        save();
    }
    std::vector<third_party_lib> 
        m_third_party_libs;
    void Settings::RegisterThirdPartyLib(const string& name, const string& version, const string& url)
    {
        lock_guard<mutex> lock(mutex_register);

        m_third_party_libs.emplace_back(name, version, url);

        // maintain alphabetical order
        sort(m_third_party_libs.begin(), m_third_party_libs.end(),
            [](const third_party_lib& a, const third_party_lib& b)
            {
                return a.name < b.name;
            }
        );
    }

    const vector<third_party_lib>& Settings::GetThirdPartyLibs()
    {
        return m_third_party_libs;
    }

    bool Settings::HasLoadedUserSettingsFromFile()
    {
        return m_has_loaded_user_settings;
    }
}
