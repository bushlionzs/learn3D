#include "OgreHeader.h"
#include "D3D12Mappings.h"

namespace Ogre {

    D3D12_BLEND D3D12Mappings::get(SceneBlendFactor sbf, bool forAlpha)
    {
        switch (sbf)
        {
        case SBF_ONE:                       return D3D12_BLEND_ONE;
        case SBF_ZERO:                      return D3D12_BLEND_ZERO;
        case SBF_DEST_COLOUR:               return forAlpha ? D3D12_BLEND_DEST_ALPHA : D3D12_BLEND_DEST_COLOR;
        case SBF_SOURCE_COLOUR:             return forAlpha ? D3D12_BLEND_SRC_ALPHA : D3D12_BLEND_SRC_COLOR;
        case SBF_ONE_MINUS_DEST_COLOUR:     return forAlpha ? D3D12_BLEND_INV_DEST_ALPHA : D3D12_BLEND_INV_DEST_COLOR;
        case SBF_ONE_MINUS_SOURCE_COLOUR:   return forAlpha ? D3D12_BLEND_INV_SRC_ALPHA : D3D12_BLEND_INV_SRC_COLOR;
        case SBF_DEST_ALPHA:                return D3D12_BLEND_DEST_ALPHA;
        case SBF_SOURCE_ALPHA:              return D3D12_BLEND_SRC_ALPHA;
        case SBF_ONE_MINUS_DEST_ALPHA:      return D3D12_BLEND_INV_DEST_ALPHA;
        case SBF_ONE_MINUS_SOURCE_ALPHA:    return D3D12_BLEND_INV_SRC_ALPHA;
        }
        return D3D12_BLEND_ZERO;
    }

    /// return a D3D11 equivalent for a Ogre SceneBlendOperation value
    D3D12_BLEND_OP D3D12Mappings::get(SceneBlendOperation sbo)
    {
        switch (sbo)
        {
        case SBO_ADD:
            return D3D12_BLEND_OP_ADD;
        case SBO_SUBTRACT:
            return D3D12_BLEND_OP_SUBTRACT;
        case SBO_REVERSE_SUBTRACT:
            return D3D12_BLEND_OP_REV_SUBTRACT;
        case SBO_MIN:
            return D3D12_BLEND_OP_MIN;
        case SBO_MAX:
            return D3D12_BLEND_OP_MAX;
        }
        return D3D12_BLEND_OP_ADD;
    }

    LPCSTR D3D12Mappings::getSemanticName(VertexElementSemantic sem)
    {
        // todo - add to ogre - POSITIONT and PSIZE ("Transformed vertex position" and "Point size")
        switch (sem)
        {
        case VES_BLEND_INDICES:
            return "BLENDINDICES";
        case VES_BLEND_WEIGHTS:
            return "BLENDWEIGHT";
        case VES_DIFFUSE:
            return "COLOR"; // NB index will differentiate
        case VES_SPECULAR:
            return "COLOR"; // NB index will differentiate
        case VES_NORMAL:
            return "NORMAL";
        case VES_POSITION:
            return "POSITION";
        case VES_TEXTURE_COORDINATES:
            return "TEXCOORD";
        case VES_BINORMAL:
            return "BINORMAL";
        case VES_TANGENT:
            return "TANGENT";
        }
        // to keep compiler happy
        return "";
    }

    PixelFormat D3D12Mappings::_getClosestSupportedPF(PixelFormat ogrePF)
    {
        if (_getPF(ogrePF) != DXGI_FORMAT_UNKNOWN)
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

    /// utility method, convert Ogre pixel format to D3D11 pixel format
    DXGI_FORMAT D3D12Mappings::_getPF(PixelFormat ogrePF)
    {
        switch (ogrePF)
        {
        case PF_R8:             return DXGI_FORMAT_R8_UNORM;
        case PF_L16:            return DXGI_FORMAT_R16_UNORM;
        case PF_A8:             return DXGI_FORMAT_A8_UNORM;
        case PF_BYTE_LA:        return DXGI_FORMAT_UNKNOWN;
        case PF_R3G3B2:         return DXGI_FORMAT_UNKNOWN;
        case PF_A1R5G5B5:       return DXGI_FORMAT_UNKNOWN;
        case PF_R5G6B5:         return DXGI_FORMAT_UNKNOWN;
        case PF_A4R4G4B4:       return DXGI_FORMAT_UNKNOWN;
        case PF_R8G8B8:         return DXGI_FORMAT_UNKNOWN;
        case PF_A8R8G8B8:       return DXGI_FORMAT_B8G8R8A8_UNORM;
        case PF_A8B8G8R8:       return DXGI_FORMAT_R8G8B8A8_UNORM;
        case PF_X8R8G8B8:       return DXGI_FORMAT_B8G8R8X8_UNORM;
        case PF_X8B8G8R8:       return DXGI_FORMAT_UNKNOWN;
        case PF_A2B10G10R10:    return DXGI_FORMAT_R10G10B10A2_TYPELESS;
        case PF_A2R10G10B10:    return DXGI_FORMAT_UNKNOWN;
        case PF_R11G11B10_FLOAT:return DXGI_FORMAT_R11G11B10_FLOAT;
        case PF_FLOAT16_R:      return DXGI_FORMAT_R16_FLOAT;
        case PF_FLOAT16_GR:     return DXGI_FORMAT_R16G16_FLOAT;
        case PF_FLOAT16_RGBA:   return DXGI_FORMAT_R16G16B16A16_FLOAT;
        case PF_FLOAT32_R:      return DXGI_FORMAT_R32_FLOAT;
        case PF_FLOAT32_RGBA:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case PF_SHORT_RGBA:     return DXGI_FORMAT_R16G16B16A16_UNORM;
        case PF_DXT1:           return DXGI_FORMAT_BC1_UNORM;
        case PF_DXT2:           return DXGI_FORMAT_BC1_UNORM;
        case PF_DXT3:           return DXGI_FORMAT_BC2_UNORM;
        case PF_DXT4:           return DXGI_FORMAT_BC2_UNORM;
        case PF_DXT5:           return DXGI_FORMAT_BC3_UNORM;
        case PF_BC4_SNORM:      return DXGI_FORMAT_BC4_SNORM;
        case PF_BC4_UNORM:      return DXGI_FORMAT_BC4_UNORM;
        case PF_BC5_SNORM:      return DXGI_FORMAT_BC5_SNORM;
        case PF_BC5_UNORM:      return DXGI_FORMAT_BC5_UNORM;
        case PF_BC6H_UF16:      return DXGI_FORMAT_BC6H_UF16;
        case PF_BC6H_SF16:      return DXGI_FORMAT_BC6H_SF16;
        case PF_BC7_UNORM:      return DXGI_FORMAT_BC7_UNORM;
        case PF_R16G16_SINT:    return DXGI_FORMAT_R16G16_SINT;
        case PF_FLOAT32_GR:     return DXGI_FORMAT_R32G32_FLOAT;
        case PF_DEPTH16:        return DXGI_FORMAT_R32_TYPELESS;
        case PF_DEPTH32:        return DXGI_FORMAT_R32_TYPELESS;
        case PF_DEPTH32F:       return DXGI_FORMAT_R32_TYPELESS;
        case PF_DEPTH24_STENCIL8:     return DXGI_FORMAT_R24G8_TYPELESS;
        default:                return DXGI_FORMAT_UNKNOWN;
        }
    }
    /// utility method, optionally maps plain format to _SRGB counterparts
    DXGI_FORMAT D3D12Mappings::_getGammaFormat(DXGI_FORMAT format, bool appendSRGB)
    {
        if (appendSRGB)
        {
            switch (format)
            {
            case DXGI_FORMAT_R8G8B8A8_UNORM:       return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
            case DXGI_FORMAT_B8G8R8A8_UNORM:       return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
            case DXGI_FORMAT_B8G8R8X8_UNORM:       return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
            case DXGI_FORMAT_BC1_UNORM:            return DXGI_FORMAT_BC1_UNORM_SRGB;
            case DXGI_FORMAT_BC2_UNORM:            return DXGI_FORMAT_BC2_UNORM_SRGB;
            case DXGI_FORMAT_BC3_UNORM:            return DXGI_FORMAT_BC3_UNORM_SRGB;
            case DXGI_FORMAT_BC7_UNORM:            return DXGI_FORMAT_BC7_UNORM_SRGB;
            }
        }
        return format;
    }
}
