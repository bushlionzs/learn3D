#pragma once


#include "OgreSingleton.h"
#include "OgreCommon.h"
#include "VulkanCommon.h"
#include "VulkanResourceAllocator.h"



class VulkanRenderSystemBase;
class VulkanFrame;
class VulkanTexture;
class VulkanBuffer;
class VulkanLayoutCache;
class VulkanPipelineCache;
class VulkanPipelineLayoutCache;


struct CommandHelper
{
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;
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
	VulkanHelper(VulkanRenderSystemBase* rs, HWND wnd);
	~VulkanHelper();

    void _initialise();
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
    
    VkFormat _getDepthFormat();
    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VkQueue _getCommandQueue();
    VkPhysicalDevice _getPhysicalDevice();
    VkPipelineLayout _getPipelineLayout(bool pbr);
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
    VulkanRenderSystemBase* _getRenderSystem()
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
    VkSampler getSampler(const filament::backend::SamplerParams& samplerParams);
    std::shared_ptr<OgreTexture>& getDefaultTexture();

    bool haveRayTracing()
    {
        return mSettings.rayTraceing;
    }

     VulkanSettings& getVulkanSettings()
    {
        return mSettings;
    }

     VulkanPipelineCache* getPipelineCache()
     {
         return mPipelineCache;
     }

     VulkanPipelineLayoutCache* getPipelineLayoutCache()
     {
         return mPipelineLayoutCache;
     }

     VulkanLayoutCache* getLayoutCache()
     {
         return mLayoutCache;
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
    void createSwapChain();
    void createCommandBuffer();
    void createSyncObjects();
    void setupDescriptorSetLayout();
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
private:
    VulkanRenderSystemBase* mVulkanRenderSystem;
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
    VkQueue mGraphicsQueue;

    uint32_t main_queue_index = UINT_MAX;

    VkCommandPool mCommandPool[VULKAN_FRAME_RESOURCE_COUNT];
    VkCommandPool mSingleCommandPool;
    VkCommandBuffer mMainCommandBuffer[VULKAN_FRAME_RESOURCE_COUNT];
    std::vector<CommandHelper> mCommandPools;

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

    VkPhysicalDeviceDynamicRenderingFeaturesKHR enabledDynamicRenderingFeaturesKHR{};

    //default texture

    std::shared_ptr<OgreTexture> mDefaultTexture;

    std::vector<VkSampler> mSamplers;
    tsl::robin_map<SamplerParams, VkSampler, SamplerParams::Hasher, SamplerParams::EqualTo> mSamplersCache;

    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VulkanResourceAllocator mResourceAllocator;
    VulkanLayoutCache* mLayoutCache;
    VulkanPipelineLayoutCache* mPipelineLayoutCache = nullptr;
    VulkanPipelineCache* mPipelineCache = nullptr;
    std::array<DescriptorSetLayout, 2> mLayouts;
    VulkanSettings mSettings;

    void* deviceCreatepNextChain = nullptr;
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};
    // Enabled features and properties
    VkPhysicalDeviceBufferDeviceAddressFeatures enabledBufferDeviceAddresFeatures{};
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR enabledRayTracingPipelineFeatures{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR enabledAccelerationStructureFeatures{};


};