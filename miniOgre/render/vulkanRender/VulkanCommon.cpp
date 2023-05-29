#include "OgreHeader.h"
#include "VulkanCommon.h"


VkFormat getVKFormatFromType(VertexElementType type)
{
    switch (type)
    {
    case VET_FLOAT2:
        return VK_FORMAT_R32G32_SFLOAT;
        break;
    case VET_FLOAT3:
        return VK_FORMAT_R32G32B32_SFLOAT;
        break;
    case VET_FLOAT4:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
        break;
    case VET_UINT4:
        return VK_FORMAT_R32G32B32A32_UINT;
        break;
    case VET_UBYTE4_NORM:
        return VK_FORMAT_R8G8B8A8_UNORM;
        break;
    default:
        assert(false);
        break;
    }

    return VK_FORMAT_R32G32_SFLOAT;
}