#include "OgreHeader.h"
#include "VulkanMappings.h"

namespace Ogre {

    VkBlendFactor VulkanMappings::get(SceneBlendFactor sbf, bool forAlpha)
    {
        switch (sbf)
        {
        case SBF_ONE:                       
            return VK_BLEND_FACTOR_ONE;
        case SBF_ZERO:                      
            return VK_BLEND_FACTOR_ZERO;
        case SBF_DEST_COLOUR:               
            return forAlpha ? VK_BLEND_FACTOR_DST_ALPHA : VK_BLEND_FACTOR_DST_COLOR;
        case SBF_SOURCE_COLOUR:             
            return forAlpha ? VK_BLEND_FACTOR_SRC_ALPHA : VK_BLEND_FACTOR_SRC_COLOR;
        case SBF_ONE_MINUS_DEST_COLOUR:     
            return forAlpha ? VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA : VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
        case SBF_ONE_MINUS_SOURCE_COLOUR:   
            return forAlpha ? VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA : VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
        case SBF_DEST_ALPHA:                
            return VK_BLEND_FACTOR_DST_ALPHA;
        case SBF_SOURCE_ALPHA:              
            return VK_BLEND_FACTOR_SRC_ALPHA;
        case SBF_ONE_MINUS_DEST_ALPHA:      
            return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
        case SBF_ONE_MINUS_SOURCE_ALPHA:    
            return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        }
        return VK_BLEND_FACTOR_ZERO;
    }

    /// return a D3D11 equivalent for a Ogre SceneBlendOperation value
    VkBlendOp VulkanMappings::get(SceneBlendOperation sbo)
    {
        switch (sbo)
        {
        case SBO_ADD:
            return VK_BLEND_OP_ADD;
        case SBO_SUBTRACT:
            return VK_BLEND_OP_SUBTRACT;
        case SBO_REVERSE_SUBTRACT:
            return VK_BLEND_OP_REVERSE_SUBTRACT;
        case SBO_MIN:
            return VK_BLEND_OP_MIN;
        case SBO_MAX:
            return VK_BLEND_OP_MAX;
        }
        return VK_BLEND_OP_ADD;
    }

    LPCSTR VulkanMappings::getSemanticName(VertexElementSemantic sem)
    {
        // todo - add to ogre - POSITIONT and PSIZE ("Transformed vertex position" and "Point size")
        switch (sem)
        {
        case VES_BLEND_INDICES:
            return "bone_indices";
        case VES_BLEND_WEIGHTS:
            return "bone_weights";
        case VES_DIFFUSE:
            return "color_diffuse"; // NB index will differentiate
        case VES_SPECULAR:
            return "color_specular"; // NB index will differentiate
        case VES_NORMAL:
            return "normal";
        case VES_POSITION:
            return "position";
        case VES_TEXTURE_COORDINATES:
            return "texcoord";
        case VES_BINORMAL:
            return "binormal";
        case VES_TANGENT:
            return "tangent";
        }
        // to keep compiler happy
        return "";
    }

    PixelFormat VulkanMappings::_getClosestSupportedPF(PixelFormat ogrePF)
    {
        if (_getPF(ogrePF) != VK_FORMAT_UNDEFINED)
        {
            return ogrePF;
        }
        switch (ogrePF)
        {
        case PF_R8G8B8:
            return PF_X8R8G8B8;
        case PF_FLOAT16_RGB:
            return PF_FLOAT16_RGBA;
        case PF_FLOAT32_RGB:
            return PF_FLOAT32_RGBA;
        case PF_DEPTH16:
            return PF_L16;
        case PF_DEPTH24_STENCIL8:
        case PF_DEPTH32:
        case PF_DEPTH32F:
            return PF_FLOAT32_R;
        case PF_UNKNOWN:
        default:
            return PF_A8B8G8R8;
        }
    }

    VkFormat VulkanMappings::_getPF(PixelFormat ogrePF)
    {
        switch (ogrePF)
        {
        case PF_R8:             return VK_FORMAT_R8_UNORM;
        case PF_L16:            return VK_FORMAT_R16_UNORM;
        case PF_A8:             return VK_FORMAT_R8_UNORM;
        case PF_BYTE_LA:        return VK_FORMAT_UNDEFINED;
        case PF_R3G3B2:         return VK_FORMAT_UNDEFINED;
        case PF_A1R5G5B5:       return VK_FORMAT_UNDEFINED;
        case PF_R5G6B5:         return VK_FORMAT_UNDEFINED;
        case PF_A4R4G4B4:       return VK_FORMAT_UNDEFINED;
        case PF_R8G8B8:         return VK_FORMAT_UNDEFINED;
        case PF_A8R8G8B8:       return VK_FORMAT_B8G8R8A8_UNORM;
        case PF_A8B8G8R8:       return VK_FORMAT_R8G8B8A8_UNORM;
        case PF_X8R8G8B8:       return VK_FORMAT_B8G8R8A8_UNORM;
        case PF_X8B8G8R8:       return VK_FORMAT_UNDEFINED;
        case PF_A2B10G10R10:    return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
        case PF_A2R10G10B10:    return VK_FORMAT_UNDEFINED;
        case PF_R11G11B10_FLOAT:return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
        case PF_FLOAT16_R:      return VK_FORMAT_R16_SFLOAT;
        case PF_FLOAT16_GR:     return VK_FORMAT_R16G16_SFLOAT;
        case PF_FLOAT16_RGBA:   return VK_FORMAT_R16G16B16A16_SFLOAT;
        case PF_FLOAT32_R:      return VK_FORMAT_R32_SFLOAT;
        case PF_FLOAT32_RGBA:   return VK_FORMAT_R32G32B32A32_SFLOAT;
        case PF_SHORT_RGBA:     return VK_FORMAT_R16G16B16A16_UNORM;
        case PF_DXT1:           return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case PF_DXT2:           return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case PF_DXT3:           return VK_FORMAT_BC2_UNORM_BLOCK;
        case PF_DXT4:           return VK_FORMAT_BC2_UNORM_BLOCK;
        case PF_DXT5:           return VK_FORMAT_BC3_UNORM_BLOCK;
        case PF_BC4_SNORM:      return VK_FORMAT_BC4_UNORM_BLOCK;
        case PF_BC4_UNORM:      return VK_FORMAT_BC4_UNORM_BLOCK;
        case PF_BC5_SNORM:      return VK_FORMAT_BC5_UNORM_BLOCK;
        case PF_BC5_UNORM:      return VK_FORMAT_BC5_UNORM_BLOCK;
        case PF_BC6H_UF16:      return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case PF_BC7_UNORM:      return VK_FORMAT_BC7_UNORM_BLOCK;
        case PF_R16G16_SINT:    return VK_FORMAT_R16G16_SINT;
        case PF_FLOAT32_GR:     return VK_FORMAT_R32G32_SFLOAT;
        case PF_DEPTH16:        return VK_FORMAT_R32_UINT;
        case PF_DEPTH32:        return VK_FORMAT_R32_UINT;
        case PF_DEPTH32F:       return VK_FORMAT_R32_UINT;
        case PF_DEPTH24_STENCIL8:     return VK_FORMAT_D24_UNORM_S8_UINT;
        default:                return VK_FORMAT_UNDEFINED;
        }
    }

    VkFormat VulkanMappings::_getGammaFormat(VkFormat format, bool appendSRGB)
    {
        return format;
    }
}
