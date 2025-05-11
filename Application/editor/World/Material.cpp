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
#include "Material.h"
#include "World.h"
#include "ProgressTracker.h"


//====================================

//= NAMESPACES ===============
using namespace std;

//============================

namespace spartan
{
    namespace
    {
        const char* material_property_to_char_ptr(MaterialProperty material_property)
        {
            switch (material_property)
            {
                case MaterialProperty::Optimized:            return "optimized";
                case MaterialProperty::WorldHeight:     return "world_space_height";
                case MaterialProperty::Clearcoat:            return "clearcoat";
                case MaterialProperty::Clearcoat_Roughness:  return "clearcoat_roughness";
                case MaterialProperty::Anisotropic:          return "anisotropic";
                case MaterialProperty::AnisotropicRotation:  return "anisotropic_rotation";
                case MaterialProperty::Sheen:                return "sheen";
                case MaterialProperty::ColorR:               return "color_r";
                case MaterialProperty::ColorG:               return "color_g";
                case MaterialProperty::ColorB:               return "color_b";
                case MaterialProperty::ColorA:               return "color_a";
                case MaterialProperty::Ior:                  return "ior";
                case MaterialProperty::Roughness:            return "roughness";
                case MaterialProperty::Metalness:            return "metalness";
                case MaterialProperty::Normal:               return "normal";
                case MaterialProperty::Height:               return "height";
                case MaterialProperty::SubsurfaceScattering: return "subsurface_scattering";
                case MaterialProperty::TextureTilingX:       return "texture_tiling_x";
                case MaterialProperty::TextureTilingY:       return "texture_tiling_y";
                case MaterialProperty::TextureOffsetX:       return "texture_offset_x";
                case MaterialProperty::TextureOffsetY:       return "texture_offset_y";
                case MaterialProperty::IsTerrain:    return "texture_slope_based";
                case MaterialProperty::IsTree: return "vertex_animate_wind";
                case MaterialProperty::IsWater:   return "vertex_animate_water";
                case MaterialProperty::CullMode:             return "cull_mode";
                case MaterialProperty::Max:                  return "max";
                default:
                {
                    assert(false, "Unknown material property");
                    return nullptr;
                }
            }
        }
    }

    namespace texture_packing
    {
        void pack_occlusion_roughness_metalness_height(
            const vector<byte>& occlusion,
            const vector<byte>& roughness,
            const vector<byte>& metalness,
            const vector<byte>& height,
            const bool is_gltf,
            vector<byte>& output
        )
        {
            assert_invariant(
                occlusion.size() == roughness.size() &&
                roughness.size() == metalness.size() &&
                metalness.size() == height.size()
            );

            // just like gltf: occlusion, roughness and metalness as r, g, b channels respectively
            for (size_t i = 0; i < occlusion.size(); i += 4)
            {
                output[i + 0] = occlusion[i];
                output[i + 1] = roughness[i + (is_gltf ? 1 : 0)];
                output[i + 2] = metalness[i + (is_gltf ? 2 : 0)];
                output[i + 3] = height[i];
            }
        }

        void merge_alpha_mask_into_color_alpha(vector<byte>& albedo, vector<byte>& mask)
        {
            assert_invariant(albedo.size() == mask.size());
        
            for (size_t i = 0; i < albedo.size(); i += 4)
            {
                float alpha_albedo   = static_cast<float>(albedo[i + 3]) / 255.0f; // channel a
                float alpha_mask     = static_cast<float>(mask[i]) / 255.0f;       // channel r
                float alpha_combined = min(alpha_albedo, alpha_mask);

                albedo[i + 3] = static_cast<byte>(alpha_combined * 255.0f);
            }
        }
    }

    Material::Material()
    {
        m_textures.fill(nullptr);
        m_properties.fill(0.0f);

  
        SetProperty(MaterialProperty::ColorR,           1.0f);
        SetProperty(MaterialProperty::ColorG,           1.0f);
        SetProperty(MaterialProperty::ColorB,           1.0f);
        SetProperty(MaterialProperty::ColorA,           1.0f);
        SetProperty(MaterialProperty::Roughness,        1.0f);
        SetProperty(MaterialProperty::TextureTilingX,   1.0f);
        SetProperty(MaterialProperty::TextureTilingY,   1.0f);
        SetProperty(MaterialProperty::WorldHeight, 1.0f);
        SetProperty(MaterialProperty::Ior,              Material::EnumToIor(MaterialIor::Air));
    }

    std::string Material::GetObjectName()
    {
        return std::string();
    }

    void Material::LoadFromFile(const std::string& file_path)
    {
       
    }

    void Material::SaveToFile(const string& file_path)
    {
        
    }

    void Material::SetTexture(const MaterialTextureType texture_type, Ogre::OgreTexture* texture, const uint8_t slot)
    {
        // validate slot range
        assert_invariant(slot < slots_per_texture_type);
    
        // calculate the actual array index based on texture type and slot
        uint32_t array_index = (static_cast<uint32_t>(texture_type) * slots_per_texture_type) + slot;

        if (texture)
        {
            m_textures[array_index] = texture;
        }
        else
        {
            m_textures[array_index] = nullptr;
        }

        // set the correct multiplier
        float multiplier = texture != nullptr;
        if (texture_type == MaterialTextureType::Roughness)
        {
            SetProperty(MaterialProperty::Roughness, multiplier);
        }
        else if (texture_type == MaterialTextureType::Metalness)
        {
            SetProperty(MaterialProperty::Metalness, multiplier);
        }
        else if (texture_type == MaterialTextureType::Normal)
        {
            SetProperty(MaterialProperty::Normal, multiplier);
        }
        else if (texture_type == MaterialTextureType::Height)
        {
            SetProperty(MaterialProperty::Height, multiplier);
        }


    }

    void Material::SetTexture(const MaterialTextureType texture_type, shared_ptr<Ogre::OgreTexture> texture, const uint8_t slot)
    {
        SetTexture(texture_type, texture.get(), slot);
    }

    void Material::SetTexture(const MaterialTextureType texture_type, const string& file_path, const uint8_t slot)
    {
       
    }
 
    bool Material::HasTextureOfType(const string& path) const
    {
        

        return false;
    }

    bool Material::HasTextureOfType(const MaterialTextureType texture_type) const
    {
        for (uint32_t slot = 0; slot < slots_per_texture_type; slot++)
        {
            if (m_textures[static_cast<uint32_t>(texture_type) * slots_per_texture_type + slot] != nullptr)
                return true; 
        }
    
        return false;
    }

    string Material::GetTexturePathByType(const MaterialTextureType texture_type, const uint8_t slot)
    {
        if (!HasTextureOfType(texture_type))
            return "";

        return "";
    }

    vector<string> Material::GetTexturePaths()
    {
        vector<string> paths;
        

        return paths;
    }

    Ogre::OgreTexture* Material::GetTexture(const MaterialTextureType texture_type, const uint8_t slot)
    {
        assert_invariant(slot < slots_per_texture_type);
        return m_textures[(static_cast<uint32_t>(texture_type) * slots_per_texture_type) + slot];
    }

    void Material::PrepareForGpu()
    {
        
    }

    uint32_t Material::GetUsedSlotCount() const
    {
        // array to track highest used slot for each texture type
        uint32_t max_used_slot[static_cast<size_t>(MaterialTextureType::Max)] = { 0 };
    
        // iterate through each texture type
        for (size_t type = 0; type < static_cast<size_t>(MaterialTextureType::Max); type++)
        {
            // check each slot for this type
            for (uint32_t slot = 0; slot < slots_per_texture_type; ++slot)
            {
                // calculate array index using the helper function
                uint32_t index = (static_cast<uint32_t>(type) * slots_per_texture_type) + slot;
                
                // if this slot has a texture, update the max used slot for this type
                if (m_textures[index])
                {
                    max_used_slot[type] = slot + 1; // +1 because we want count, not index
                }
            }
        }
    
        // return the maximum used slot count across all texture types (minimum of 1)
        return max<uint32_t>(*max_element(begin(max_used_slot), end(max_used_slot)), 1);
    }

    void Material::SetProperty(const MaterialProperty property_type, float value)
    {
       
    }

    void Material::SetColor(const Ogre::ColourValue& color)
    {
        SetProperty(MaterialProperty::ColorR, color.r);
        SetProperty(MaterialProperty::ColorG, color.g);
        SetProperty(MaterialProperty::ColorB, color.b);
        SetProperty(MaterialProperty::ColorA, color.a);
    }

    bool Material::IsAlphaTested()
    {
        return false;
    }

    float Material::EnumToIor(const MaterialIor ior)
    {
        switch (ior)
        {
            case MaterialIor::Air:      return 1.0f;
            case MaterialIor::Water:    return 1.33f;
            case MaterialIor::Eyes:     return 1.38f;
            case MaterialIor::Glass:    return 1.52f;
            case MaterialIor::Sapphire: return 1.76f;
            case MaterialIor::Diamond:  return 2.42f;
            default:                    return 1.0f;
        }
    }

    MaterialIor Material::IorToEnum(const float ior)
    {
        const float epsilon = 0.001f;

        if (std::abs(ior - 1.0f)  < epsilon) return MaterialIor::Air;
        if (std::abs(ior - 1.33f) < epsilon) return MaterialIor::Water;
        if (std::abs(ior - 1.38f) < epsilon) return MaterialIor::Eyes;
        if (std::abs(ior - 1.52f) < epsilon) return MaterialIor::Glass;
        if (std::abs(ior - 1.76f) < epsilon) return MaterialIor::Sapphire;
        if (std::abs(ior - 2.42f) < epsilon) return MaterialIor::Diamond;

        return MaterialIor::Air;
    }
}
