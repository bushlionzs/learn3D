#pragma once


#include "OgreSingleton.h"
#include "OgreCommon.h"
#include "VulkanCommon.h"
#include "VulkanContext.h"
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

    VkDevice getDevcie()
    {
        return mVKDevice;
    }
    VkPhysicalDeviceProperties& _getVkPhysicalDeviceProperties();
    VkPhysicalDeviceFeatures& _getVkPhysicalDeviceFeatures()
    {
        return mDeviceFeatures;
    }
    VkFormat _getDepthFormat();
    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VkPipelineLayout _getPipelineLayout(bool pbr);
    VmaAllocator getVmaAllocator();
    VulkanResourceAllocator* getVulkanResourceAllocator();

    VulkanFrame* _getFrame(uint32_t index);
    VkDescriptorPool _getDescriptorPool();
    VkDescriptorSetLayout _getDescriptorSetLayout(VulkanLayoutIndex index);
    VulkanRenderSystemBase* _getRenderSystem()
    {
        return mVulkanRenderSystem;
    }
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
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool checkValidationLayerSupport();
    void createDescriptorPool();
    void setupDescriptorSetLayout();
    void createSamples();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes);
    //debug
    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
private:
    VulkanRenderSystemBase* mVulkanRenderSystem;
    bool mEnableValidationLayers;

    VkDevice mVKDevice;
    VkInstance mVKInstance;


    VulkanPlatform* mPlatform;
    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
    VkPhysicalDeviceFeatures mDeviceFeatures;
    VkPhysicalDeviceMemoryProperties mPhysicalMemoryProperties;
 


    VkDescriptorPool mDescriptorPool;
    std::array<VkDescriptorSetLayout,2> mDescriptorSetLayout;
    VkDescriptorSetLayout mPbrDescriptorSetLayout;
    VkPipelineLayout mPipelineLayout;
    VkPipelineLayout mPipelineLayoutPbr;

    VkFormat mSwapChainImageFormat;
    VkColorSpaceKHR mColorSpace;

    

    VkFormat mDepthFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;

    std::vector<VulkanFrame*> mFrameList;



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
    std::array<descset::DescriptorSetLayout, 2> mLayouts;
    VulkanSettings mSettings;

    void* deviceCreatepNextChain = nullptr;
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};
    // Enabled features and properties
    VkPhysicalDeviceBufferDeviceAddressFeatures enabledBufferDeviceAddresFeatures{};
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR enabledRayTracingPipelineFeatures{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR enabledAccelerationStructureFeatures{};
};