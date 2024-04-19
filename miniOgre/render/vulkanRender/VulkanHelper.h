#pragma once


#include "OgreSingleton.h"
#include "VulkanCommon.h"
#include "OgreCommon.h"


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
    VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_4_BIT;
};

class VulkanRenderSystem;
class VulkanFrame;
class VulkanTexture;

struct CommandHelper
{
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;
};
class VulkanHelper : public Ogre::Singleton<VulkanHelper>
{
public:
	VulkanHelper(VulkanRenderSystem* rs, HWND wnd);
	~VulkanHelper();

    void _initialise();
    void _createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer& buffer,
        VkDeviceMemory& bufferMemory);

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
    void copyBuffer(
        VkBuffer srcBuffer,
        VkBuffer dstBuffer,
        VkDeviceSize size);
    void transitionImageLayout(
        VkImage image,
        VkFormat format,
        VkImageLayout oldLayout,
        VkImageLayout newLayout);
    void copyBufferToImage(
        VkBuffer buffer,
        VkImage image,
        ITexture* tex);
    void generateMipmaps(VulkanTexture* tex);

    VulkanDepthStencil createDepthStencil(uint32_t width, uint32_t height);

    VkFormat _getDepthFormat();
    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VkQueue _getCommandQueue();
    VkQueue _getTransferQueue();
    void waitTransferQueue();
    VkRenderPass _getRenderPass();
    VkPhysicalDevice _getPhysicalDevice();
    VkPipelineLayout _getPipelineLayout();
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
    VkDescriptorSetLayout _getDescriptorSetLayout();
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
    std::shared_ptr<ITexture>& getDefaultTexture();

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
    VkDevice mVKDevice;


    VkDescriptorPool mDescriptorPool;
    VkDescriptorSet mDescriptorSet;
    VkDescriptorSetLayout mDescriptorSetLayout;
    VkPipelineLayout mPipelineLayout;

    VkPipelineCache mPipelineCache;
    VkQueue mGraphicsQueue;
    VkQueue mTransferQueue;

    uint32_t main_queue_index = UINT_MAX;
    uint32_t transfer_queue_index = UINT_MAX;

    VkCommandPool mCommandPool[VULKAN_FRAME_RESOURCE_COUNT];
    VkCommandPool mTransferCommandPool;
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

    std::shared_ptr<ITexture> mDefaultTexture;

    std::vector<VkSampler> mSamplers;

    VulkanSettings mSettings;

    //
    VkCommandBuffer mResourceCommandBuffer = VK_NULL_HANDLE;
};