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

//= INCLUDES ========================
#include <OgreHeader.h>
#include "Light.h"
#include "Camera.h"
#include "../World.h"
#include "../Entity.h"
#include "Renderer.h"
//===================================

//= NAMESPACES ===============
using namespace spartan::math;
using namespace std;
//============================

namespace spartan
{
    namespace
    {
        float get_sensible_range(const LightType type)
        {
            if (type == LightType::Directional)
            {
                return numeric_limits<float>::max();
            }
            else if (type == LightType::Point)
            {
                return 15.0f;
            }
            else if (type == LightType::Spot)
            {
                return 15.0f;
            }

            return 0.0f;
        }

        Ogre::ColourValue get_sensible_color(const LightType type)
        {
            if (type == LightType::Directional)
            {
                return Ogre::ColourValue::White;
            }
            else if (type == LightType::Point)
            {
                return Ogre::ColourValue::White;
            }
            else if (type == LightType::Spot)
            {
                return Ogre::ColourValue::White;
            }

            return Ogre::ColourValue::White;
        }

        const float near_plane   = 0.05f;
        const float depth_range  = 2000.0f; // beyond that, screen space shadows are enough
        float shadow_extent_near = 0.0f;
        float shadow_extent_far  = 0.0f;
        void update_shadow_extents()
        {
            
        }
    }

    Light::Light(Entity* entity) : Component(entity)
    {
       
        SetColor(get_sensible_color(m_light_type));
        SetIntensity(LightIntensity::bulb_500_watt);
        SetRange(get_sensible_range(m_light_type));
        SetFlag(LightFlags::Shadows);
        SetFlag(LightFlags::ShadowsScreenSpace);
        SetFlag(LightFlags::DayNightCycle);
        SetFlag(LightFlags::ShadowDirty);
    }

    void Light::OnTick()
    {
        // update matrices
        bool update_matrices = false;
        if (GetEntity()->GetTimeSinceLastTransform() <= 0.1f)
        {
            update_matrices = true;
        }

        if (m_light_type == LightType::Directional)
        {
            // the directional light follows the camera, and emulates day and night cycle, so we just always update
            update_matrices = true;

            // day night cycle
            if (GetFlag(LightFlags::DayNightCycle))
            {
                
            }
        }

        if (update_matrices)
        {
            UpdateMatrices();
        }

        // create shadow maps
        {
           
        }
    }

    void Light::Serialize(FileStream* stream)
    {
       
    }

    void Light::Deserialize(FileStream* stream)
    {
       
    }

    void Light::SetFlag(const LightFlags flag, const bool enable)
    {
        bool enabled      = false;
        bool disabled     = false;
        bool flag_present = m_flags & flag;

        if (enable && !flag_present)
        {
            m_flags |= static_cast<uint32_t>(flag);
            enabled  = true;
        }
        else if (!enable && flag_present)
        {
            m_flags  &= ~static_cast<uint32_t>(flag);
            disabled  = true;
        }

        if (enabled || disabled)
        {
            if (disabled)
            {
                // if the shadows have been disabled, disable properties which rely on them
                if (flag & LightFlags::Shadows)
                {
                    m_flags &= ~static_cast<uint32_t>(LightFlags::ShadowsScreenSpace);
                    m_flags &= ~static_cast<uint32_t>(LightFlags::ShadowsTransparent);
                    m_flags &= ~static_cast<uint32_t>(LightFlags::Volumetric);
                }
            }


        }
    }

    void Light::SetLightType(LightType type)
    {
        if (m_light_type == type)
            return;

        m_light_type = type;

        SetColor(get_sensible_color(m_light_type));
        SetRange(get_sensible_range(m_light_type));

        UpdateMatrices();
        World::Resolve();
    }

    void Light::SetTemperature(const float temperature_kelvin)
    {
       
    }

    void Light::SetColor(const Ogre::ColourValue& rgb)
    {
        m_color_rgb = rgb;

       
    }

    void Light::SetIntensity(const LightIntensity intensity)
    {
        m_intensity = intensity;

        if (intensity == LightIntensity::bulb_stadium)
        {
            m_intensity_lumens_lux = 200000.0f;
        }
        else if (intensity == LightIntensity::bulb_500_watt)
        {
            m_intensity_lumens_lux = 8500.0f;
        }
        else if (intensity == LightIntensity::bulb_150_watt)
        {
            m_intensity_lumens_lux = 2600.0f;
        }
        else if (intensity == LightIntensity::bulb_100_watt)
        {
            m_intensity_lumens_lux = 1600.0f;
        }
        else if (intensity == LightIntensity::bulb_60_watt)
        {
            m_intensity_lumens_lux = 800.0f;
        }
        else if (intensity == LightIntensity::bulb_25_watt)
        {
            m_intensity_lumens_lux = 200.0f;
        }
        else if (intensity == LightIntensity::bulb_flashlight)
        {
            m_intensity_lumens_lux = 100.0f;
        }
        else // black hole
        {
            m_intensity_lumens_lux = 0.0f;
        }


    }

    void Light::SetIntensity(const float lumens)
    {
        m_intensity_lumens_lux = lumens;
        m_intensity            = LightIntensity::custom;

    }

    float Light::GetIntensityWatt() const
    {
        // ideal luminous efficacy at 555nm in lm/w
        const float luminous_efficacy = 683.0f;
        float intensity               = m_intensity_lumens_lux;
        
        if (m_light_type == LightType::Directional)
        {
            // assume the intensity is in lux (lm/m^2)
            // converting lux to W/m^2 using a reference area of 1 m^2
            intensity = m_intensity_lumens_lux / luminous_efficacy;
        } else
        {
            intensity = m_intensity_lumens_lux / luminous_efficacy;
        }
        
        return intensity;
    }


    void Light::SetRange(float range)
    {
        range = clamp(range, 0.0f, numeric_limits<float>::max());
        if (range == m_range)
            return;

        m_range = range;
        UpdateMatrices();
    }

    void Light::SetAngle(float angle)
    {
       
    }

    void Light::UpdateMatrices()
    {
        ComputeViewMatrix();
        ComputeProjectionMatrix();
        SetFlag(LightFlags::ShadowDirty);

    }

    void Light::ComputeViewMatrix()
    {
        
    }
    
    void Light::ComputeProjectionMatrix()
    {
        
    }

    bool Light::IsInViewFrustum(Renderable* renderable, const uint32_t array_index, const uint32_t instance_group_index) const
    {
            return false; 
    }
}  
