#pragma once
//#include <vulkan/vulkan.h>
//#include <vulkan/vulkan_beta.h>
//#include <vulkan/vulkan_win32.h>
#include <optional>
#include "OgreHardwareVertexBuffer.h"
#include "engine_struct.h"
#include <bluevk/BlueVK.h>
#include "VulkanInitializers.hpp"

#include <vk_mem_alloc.h>

using namespace bluevk;
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

struct VulkanImage
{
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkImage image = VK_NULL_HANDLE;
    VkImageView view = VK_NULL_HANDLE;
    VkFormat format;
};

struct GeometryNode {
    VkDeviceOrHostAddressConstKHR vertexBufferDeviceAddress;
    VkDeviceOrHostAddressConstKHR indexBufferDeviceAddress;
    VkDeviceOrHostAddressConstKHR transformBufferDeviceAddress;
    int32_t textureIndexBaseColor;
    int32_t textureIndexOcclusion;
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

