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
    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
};

struct MultisampleTarget 
{
    struct {
        VkImage image;
        VkImageView view;
        VkDeviceMemory memory;
    } color;
    struct {
        VkImage image;
        VkImageView view;
        VkDeviceMemory memory;
    } depth;
};

class VulkanShader;
class VulkanRenderableData;


VkFormat getVKFormatFromType(VertexElementType type);

