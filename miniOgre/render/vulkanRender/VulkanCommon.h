#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <optional>
#include "OgreHardwareVertexBuffer.h"
#include "engine_struct.h"
#include "VulkanInitializers.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


struct VulkanDepthStencil
{
    VkImage _image;
    VkDeviceMemory _mem;
    VkImageView _view;
};

class VulkanShader;
class VulkanRenderableData;


VkFormat getVKFormatFromType(VertexElementType type);