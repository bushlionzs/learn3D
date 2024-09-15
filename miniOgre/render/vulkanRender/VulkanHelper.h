#pragma once


#include "OgreSingleton.h"
#include "VulkanCommon.h"
#include "OgreCommon.h"
#include <filament/vulkan/VulkanPlatform.h>

using namespace filament::backend;

#define VULKAN_FRAME_RESOURCE_COUNT 3
#define VULKAN_TEXTURE_COUNT 6
#define VULKAN_COMMAND_THREAD 4


struct SwapChainBuffer
{
    VkImage _image;
    VkImageView _view;
};

struct VulkanSettings {
    bool validation = false;
    bool fullscreen = false;
    bool vsync = false;
    bool multiSampling = true;
    bool rayTraceing = true;
    VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_4_BIT;
    VulkanSettings()
    {
        multiSampling = false;

        if (!multiSampling)
        {
            sampleCount = VK_SAMPLE_COUNT_1_BIT;
        }
    }
};

class VulkanRenderSystem;
class VulkanFrame;
class VulkanTexture;
class VulkanBuffer;
struct CommandHelper
{
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;
};

// Holds data for a ray tracing scratch buffer that is used as a temporary storage
struct RayTracingScratchBuffer
{
    uint64_t deviceAddress = 0;
    VkBuffer handle = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
};

// Ray tracing acceleration structure
struct AccelerationStructure {
    VkAccelerationStructureKHR handle;
    uint64_t deviceAddress = 0;
    VkDeviceMemory memory;
    VkBuffer buffer;
};


enum VulkanLayoutIndex
{
    VulkanLayoutIndex_Data = 0,
    VulkanLayoutIndex_Unlit = 1,
    VulkanLayoutIndex_Pbr = 2
};

class VulkanHelper : public Ogre::Singleton<VulkanHelper>
{
public:
	VulkanHelper(VulkanRenderSystem* rs, HWND wnd);
	~VulkanHelper();

    void _initialise(VulkanPlatform* platform);
    void _createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer& buffer,
        VkDeviceMemory& bufferMemory);
    VkResult createBuffer(
        VkBufferUsageFlags usageFlags,
        VkMemoryPropertyFlags memoryPropertyFlags,
        VulkanBuffer* buffer,
        VkDeviceSize size,
        void* data);

    VkDevice _getVkDevice();
    VkInstance _getVKInstance();
    VkPhysicalDeviceProperties& _getVkPhysicalDeviceProperties();
    VkPhysicalDeviceFeatures& _getVkPhysicalDeviceFeatures()
    {
        return mDeviceFeatures;
    }
    VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(
        VkImage image,
        VkFormat format,
        VkImageLayout oldLayout,
        VkImageLayout newLayout);
    void insertImageMemoryBarrier(
        VkCommandBuffer cmdbuffer,
        VkImage image,
        VkAccessFlags srcAccessMask,
        VkAccessFlags dstAccessMask,
        VkImageLayout oldImageLayout,
        VkImageLayout newImageLayout,
        VkPipelineStageFlags srcStageMask,
        VkPipelineStageFlags dstStageMask,
        VkImageSubresourceRange subresourceRange);

    VulkanDepthStencil createDepthStencil(uint32_t width, uint32_t height);

    VkFormat _getDepthFormat();
    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VkQueue _getCommandQueue();
    VkRenderPass _getRenderPass();
    VkPhysicalDevice _getPhysicalDevice();
    VkPipelineLayout _getPipelineLayout(bool pbr);
    VkPipelineCache getPipelineCache();
    void _resetCommandBuffer(uint32_t frame_index);
    void _endCommandBuffer(uint32_t frame_index);
    VkCommandBuffer getMainCommandBuffer(uint32_t frame_index);
    VkCommandBuffer _getThreadCommandBuffer(uint32_t tdx, uint32_t frame_index);
    void fillCommandBufferList(
        std::vector<VkCommandBuffer>& cmdlist, 
        uint32_t frame_index,
        bool have_main = true);
    VulkanFrame* _getFrame(uint32_t index);
    VkDescriptorPool _getDescriptorPool();
    VkDescriptorSetLayout _getDescriptorSetLayout(VulkanLayoutIndex index);
    VkSurfaceKHR _getSurface();
    VulkanRenderSystem* _getRenderSystem()
    {
        return mVulkanRenderSystem;
    }
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    const std::vector<SwapChainBuffer>& getSwapchainBuffer();
    VkSwapchainKHR getSwapchain();
    VkFormat getSwapChainImageFormat()
    {
        return mSwapChainImageFormat;
    }
    void loadDefaultResources();

    VkSampler getSampler(Ogre::TextureAddressingMode mode);
    VkSampler getSampler(const filament::backend::SamplerParams& samplerParams);
    std::shared_ptr<OgreTexture>& getDefaultTexture();

    bool haveRayTracing()
    {
        return mSettings.rayTraceing;
    }

    const VulkanSettings& getVulkanSettings()
    {
        return mSettings;
    }
private:
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    void updateQueueFamilies(VkPhysicalDevice device);
    bool checkValidationLayerSupport();
    void createInstance();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();
    void createDescriptorPool();
    void setupSwapChain();
    void createCommandBuffer();
    void createSyncObjects();
    void createPipelineCache();
    void setupDescriptorSetLayout();
    void createRenderPass();
    void createSamples();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(
        const VkSurfaceCapabilitiesKHR& capabilities);
    //debug
    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();

    void createBottomLevelAccelerationStructure();
    void createTopLevelAccelerationStructure();
    void createStorageImage();
    void createShaderBindingTable();
private:
	VulkanRenderSystem* mVulkanRenderSystem;
    bool mEnableValidationLayers;

    VkInstance mVKInstance;
    VkSurfaceKHR mSurface;
    HWND mWnd;
    uint32_t mWidth;
    uint32_t mHeight;

    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
    VkPhysicalDeviceFeatures mDeviceFeatures;
    VkPhysicalDeviceMemoryProperties mPhysicalMemoryProperties;
    VkDevice mVKDevice = VK_NULL_HANDLE;


    VkDescriptorPool mDescriptorPool;
    std::array<VkDescriptorSetLayout,2> mDescriptorSetLayout;
    VkDescriptorSetLayout mPbrDescriptorSetLayout;
    VkPipelineLayout mPipelineLayout;
    VkPipelineLayout mPipelineLayoutPbr;

    VkPipelineCache mPipelineCache;
    VkQueue mGraphicsQueue;

    uint32_t main_queue_index = UINT_MAX;

    VkCommandPool mCommandPool[VULKAN_FRAME_RESOURCE_COUNT];
    VkCommandPool mSingleCommandPool;
    VkCommandBuffer mMainCommandBuffer[VULKAN_FRAME_RESOURCE_COUNT];
    std::vector<CommandHelper> mCommandPools;

    VkRenderPass mRenderPass;
    VkFormat mSwapChainImageFormat;
    VkColorSpaceKHR mColorSpace;

    

    VkFormat mDepthFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;

    std::vector<VulkanFrame*> mFrameList;


    VkSwapchainKHR mSwapChain = VK_NULL_HANDLE;
    VkSwapchainKHR mOldSwapChain = VK_NULL_HANDLE;
    VkExtent2D mSwapChainExtent;
    std::vector<SwapChainBuffer> mSwapChainbuffers;
    //
    VkDebugUtilsMessengerEXT mDebugMessenger;

    //default texture

    std::shared_ptr<OgreTexture> mDefaultTexture;

    std::vector<VkSampler> mSamplers;
    tsl::robin_map<SamplerParams, VkSampler, SamplerParams::Hasher, SamplerParams::EqualTo> mSamplersCache;

    VulkanSettings mSettings;

    //
    VkCommandBuffer mResourceCommandBuffer = VK_NULL_HANDLE;

    VulkanPlatform* mPlatform;

    void* deviceCreatepNextChain = nullptr;
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};
    // Enabled features and properties
    VkPhysicalDeviceBufferDeviceAddressFeatures enabledBufferDeviceAddresFeatures{};
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR enabledRayTracingPipelineFeatures{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR enabledAccelerationStructureFeatures{};
};