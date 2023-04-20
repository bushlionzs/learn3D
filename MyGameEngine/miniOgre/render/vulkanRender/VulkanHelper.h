#pragma once


#include "OgreSingleton.h"
#include "VulkanCommon.h"


#define VULKAN_FRAME_RESOURCE_COUNT 3
#define VULKAN_TEXTURE_COUNT 4

struct SwapChainBuffer
{
    VkImage _image;
    VkImageView _view;
};

class VulkanRenderSystem;
class VulkanFrame;


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
        uint32_t width,
        uint32_t height,
        uint32_t face);

    VulkanDepthStencil createDepthStencil(uint32_t width, uint32_t height);

    VkFormat _getDepthFormat();
    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VkQueue _getCommandQueue();
    VkRenderPass _getRenderPass();
    VkPhysicalDevice _getPhysicalDevice();
    VkPipelineLayout _getPipelineLayout();
    VkCommandBuffer _getCurrentCommandBuffer();
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
    std::shared_ptr<ITexture>& getDefaultTexture();
private:
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
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
    VkPhysicalDeviceMemoryProperties mPhysicalMemoryProperties;
    VkDevice mVKDevice;


    VkDescriptorPool mDescriptorPool;
    VkDescriptorSet mDescriptorSet;
    VkDescriptorSetLayout mDescriptorSetLayout;
    VkPipelineLayout mPipelineLayout;

    VkPipelineCache mPipelineCache;
    VkQueue mGraphicsQueue;

    VkCommandPool mCommandPool;
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
};