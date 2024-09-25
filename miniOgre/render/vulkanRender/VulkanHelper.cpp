#include "OgreHeader.h"
#include "VulkanHelper.h"
#include "VulkanRenderSystem.h"
#include "VulkanTools.h"
#include "VulkanFrame.h"
#include "OgreTextureManager.h"
#include "VulkanHardwareBufferManager.h"
#include "VulkanBuffer.h"
#include "VulkanMappings.h"



template<> VulkanHelper* Ogre::Singleton<VulkanHelper>::msSingleton = 0;

static const std::vector<const char*> validationLayers = 
{
    "VK_LAYER_KHRONOS_validation"
};



static std::vector<const char*> getRequiredExtensions()
{
    std::vector<const char*> instanceExtensions = {
        "VK_KHR_surface", 
        "VK_KHR_win32_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME };

    return instanceExtensions;
}

VulkanHelper::VulkanHelper(VulkanRenderSystemBase* rs, HWND wnd)
{
    mVulkanRenderSystem = rs;
    mWnd = wnd;

    RECT rt;
    ::GetWindowRect(wnd, &rt);

    mWidth = rt.right - rt.left;
    mHeight = rt.bottom - rt.top;

    new VulkanHardwareBufferManager();
}

VulkanHelper::~VulkanHelper()
{

}

static  std::vector<const char*> deviceExtensions =
{
    VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
    VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
    VK_KHR_SPIRV_1_4_EXTENSION_NAME,
    VK_KHR_MAINTENANCE3_EXTENSION_NAME,
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME,
    VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME,
    VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME
};

//static const std::vector<const char*> deviceExtensions =
//{
//    VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
//    VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
//    VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
//    VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
//    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
//    VK_KHR_SPIRV_1_4_EXTENSION_NAME,
//    VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
//    VK_KHR_MAINTENANCE3_EXTENSION_NAME,
//    VK_KHR_SWAPCHAIN_EXTENSION_NAME
//};
void VulkanHelper::_initialise(VulkanPlatform* platform)
{
    this->mSettings.rayTraceing = false;

    if (mSettings.rayTraceing)
    {
        deviceExtensions.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
        deviceExtensions.push_back(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);
    }
    mPlatform = platform;
    createInstance();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createCommandPool();
    createDescriptorPool();
    setupSwapChain();
    createCommandBuffer();
    createPipelineCache();
    setupDescriptorSetLayout();
    createSamples();
    
}

void VulkanHelper::_createBuffer(
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer& buffer,
    VkDeviceMemory& bufferMemory)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mVKDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mVKDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex =
        _findMemoryType(
            memRequirements.memoryTypeBits,
            properties);
    VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
    if (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
        allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
        allocInfo.pNext = &allocFlagsInfo;
    }
    if (vkAllocateMemory(mVKDevice, &allocInfo, 
        nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(mVKDevice, buffer, bufferMemory, 0);
}


VkResult VulkanHelper::createBuffer(
    VkBufferUsageFlags usageFlags,
    VkMemoryPropertyFlags memoryPropertyFlags,
    VulkanBuffer* buffer,
    VkDeviceSize size,
    void* data)
{
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usageFlags;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mVKDevice, &bufferInfo, nullptr, &buffer->buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mVKDevice, buffer->buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex =
        _findMemoryType(
            memRequirements.memoryTypeBits,
            memoryPropertyFlags);
    VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
    if (usageFlags & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
        allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
        allocInfo.pNext = &allocFlagsInfo;
    }
    if (vkAllocateMemory(mVKDevice, &allocInfo,
        nullptr, &buffer->memory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    buffer->usageFlags = usageFlags;
    buffer->memoryPropertyFlags = memoryPropertyFlags;
    buffer->device = mVKDevice;
    buffer->setupDescriptor();

    if (data)
    {
        VK_CHECK_RESULT(buffer->map());
        memcpy(buffer->mapped, data, size);
        if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
            buffer->flush();

        buffer->unmap();
    }

    return buffer->bind();
}

VkDevice VulkanHelper::_getVkDevice()
{
    return mVKDevice;
}

VkInstance VulkanHelper::_getVKInstance()
{
    return mVKInstance;
}

VkPhysicalDeviceProperties& VulkanHelper::_getVkPhysicalDeviceProperties()
{
    return mPhysicalDeviceProperties;
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT types, const VkDebugUtilsMessengerCallbackDataEXT* cbdata,
    void* pUserData) {
    if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        std::cout << "VULKAN ERROR: (" << cbdata->pMessageIdName << ") " << cbdata->pMessage
            << std::endl;
    }
    else {
        // TODO: emit best practices warnings about aggressive pipeline barriers.
        if (strstr(cbdata->pMessage, "ALL_GRAPHICS_BIT")
            || strstr(cbdata->pMessage, "ALL_COMMANDS_BIT")) {
            return VK_FALSE;
        }
        std::cout << "VULKAN WARNING: (" << cbdata->pMessageIdName << ") " << cbdata->pMessage
            << std::endl;
    }
 
    return VK_FALSE;
}

void VulkanHelper::createInstance()
{
    if (mEnableValidationLayers &&
        !checkValidationLayerSupport())
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    //mEnableValidationLayers = false;
    if (mEnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();


        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }


    

    if (vkCreateInstance(&createInfo, nullptr, &mVKInstance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    VkDebugUtilsMessengerCreateInfoEXT const debugInfo = {
                .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                .pNext = nullptr,
                .flags = 0,
                .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                   | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                               | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
                .pfnUserCallback = debugUtilsCallback,
    };

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mVKInstance, "vkCreateDebugUtilsMessengerEXT");
    auto result = func(mVKInstance, &debugInfo, 0, &mDebugMessenger);
}

bool VulkanHelper::isDeviceSuitable(VkPhysicalDevice device)
{
    return true;
}

SwapChainSupportDetails VulkanHelper::querySwapChainSupport(
    VkPhysicalDevice device)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device,
        mSurface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device,
        mSurface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device,
            mSurface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device,
        mSurface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            device, mSurface, &presentModeCount,
            details.presentModes.data());
    }

    return details;
}

const std::vector<SwapChainBuffer>& VulkanHelper::getSwapchainBuffer()
{
    return mSwapChainbuffers;
}

VkSwapchainKHR VulkanHelper::getSwapchain()
{
    return mSwapChain;
}

void VulkanHelper::loadDefaultResources()
{
    mDefaultTexture = TextureManager::getSingleton().load("white1x1.dds", nullptr);
    mDefaultTexture->load(nullptr);
}

std::shared_ptr<OgreTexture>& VulkanHelper::getDefaultTexture()
{
    return mDefaultTexture;
}

bool VulkanHelper::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr,
        &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr,
        &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(),
        deviceExtensions.end());

    for (const auto& extension : availableExtensions) {

        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

void VulkanHelper::updateQueueFamilies(VkPhysicalDevice device)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount == 0) {
            continue;
        }

        if ((queueFamily.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) == (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT))
        {
            main_queue_index = i;
            break;
        }


        i++;
    }

}

bool VulkanHelper::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (auto layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

void VulkanHelper::createSurface()
{
    bluevk::bindInstance(mVKInstance);
    if (mPlatform)
    {
        return;
    }
    
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = mWnd;
    createInfo.hinstance = GetModuleHandle(nullptr);

    

    if (vkCreateWin32SurfaceKHR(mVKInstance, &createInfo, nullptr, &mSurface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }

    
}

void VulkanHelper::pickPhysicalDevice()
{
    if (mPlatform)
    {
        mPhysicalDevice = mPlatform->getPhysicalDevice();
    }
    else
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(mVKInstance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(mVKInstance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                mPhysicalDevice = device;
                break;
            }
        }

        if (mPhysicalDevice == VK_NULL_HANDLE)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to find a suitable GPU!");
        }
    }
    


    vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mDeviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mPhysicalMemoryProperties);
}

void VulkanHelper::createLogicalDevice()
{
    if (mPlatform)
    {
        mVKDevice = mPlatform->getDevice();
        mGraphicsQueue = mPlatform->getGraphicsQueue();
    }
    else
    {
        updateQueueFamilies(mPhysicalDevice);

        const float queue_priority[] = { 1.0f };
        VkDeviceQueueCreateInfo queue_info[2] = {};

        VkDeviceQueueCreateInfo& main_queue = queue_info[0];
        main_queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        main_queue.queueFamilyIndex = main_queue_index;
        main_queue.queueCount = 1;
        main_queue.pQueuePriorities = queue_priority;

       
        deviceFeatures.shaderInt64 = VK_TRUE;
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = queue_info;

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if(mSettings.rayTraceing)
        {
            enabledBufferDeviceAddresFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
            enabledBufferDeviceAddresFeatures.bufferDeviceAddress = VK_TRUE;

            enabledRayTracingPipelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
            enabledRayTracingPipelineFeatures.rayTracingPipeline = VK_TRUE;
            enabledRayTracingPipelineFeatures.pNext = &enabledBufferDeviceAddresFeatures;

            enabledAccelerationStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
            enabledAccelerationStructureFeatures.accelerationStructure = VK_TRUE;
            enabledAccelerationStructureFeatures.pNext = &enabledRayTracingPipelineFeatures;

            physicalDeviceDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
            physicalDeviceDescriptorIndexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
            physicalDeviceDescriptorIndexingFeatures.runtimeDescriptorArray = VK_TRUE;
            physicalDeviceDescriptorIndexingFeatures.descriptorBindingVariableDescriptorCount = VK_TRUE;
            physicalDeviceDescriptorIndexingFeatures.pNext = &enabledAccelerationStructureFeatures;

            deviceCreatepNextChain = &physicalDeviceDescriptorIndexingFeatures;
        }
        else
        {
            enabledDynamicRenderingFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR;
            enabledDynamicRenderingFeaturesKHR.dynamicRendering = VK_TRUE;
            deviceCreatepNextChain = &enabledDynamicRenderingFeaturesKHR;
        }
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};

        if (deviceCreatepNextChain)
        {
            physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
            physicalDeviceFeatures2.features = deviceFeatures;
            physicalDeviceFeatures2.pNext = deviceCreatepNextChain;
            createInfo.pEnabledFeatures = nullptr;
            createInfo.pNext = &physicalDeviceFeatures2;
        }
        mEnableValidationLayers = false;
        if (mEnableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(mPhysicalDevice, &createInfo, nullptr, &mVKDevice) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(mVKDevice, main_queue_index, 0, &mGraphicsQueue);

    }

    
    
}

void VulkanHelper::createCommandPool()
{
    updateQueueFamilies(mPhysicalDevice);
    VkCommandPoolCreateInfo cmdPoolInfo = {};
    cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.queueFamilyIndex = main_queue_index;
    cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    
    
    for (int32_t i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {
        if (vkCreateCommandPool(mVKDevice, &cmdPoolInfo, nullptr, &mCommandPool[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create command pool!");
        }

        VkCommandBufferAllocateInfo cmdBufAllocateInfo =
            vks::initializers::commandBufferAllocateInfo(
                mCommandPool[i],
                VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                1);

        vkAllocateCommandBuffers(mVKDevice, &cmdBufAllocateInfo, &mMainCommandBuffer[i]);
    }

    
#ifdef MULTI_RENDER
    mCommandPools.resize(VULKAN_COMMAND_THREAD * VULKAN_FRAME_RESOURCE_COUNT);

    for (uint32_t i = 0; i < mCommandPools.size(); i++)
    {
        if (vkCreateCommandPool(mVKDevice, &cmdPoolInfo, nullptr, &mCommandPools[i]._commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create command pool!");
        }
        
        VkCommandBufferAllocateInfo cmdBufAllocateInfo =
            vks::initializers::commandBufferAllocateInfo(
                mCommandPools[i]._commandPool,
                VK_COMMAND_BUFFER_LEVEL_SECONDARY,
                1);
        vkAllocateCommandBuffers(mVKDevice, &cmdBufAllocateInfo, &mCommandPools[i]._commandBuffer);
    }
#endif

    

    cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.queueFamilyIndex = main_queue_index;
    cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    
    if (vkCreateCommandPool(mVKDevice, &cmdPoolInfo, nullptr, &mSingleCommandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

void VulkanHelper::createDescriptorPool()
{
    // Example uses one ubo and one image sampler
    std::vector<VkDescriptorPoolSize> poolSizes =
    {
        vks::initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 20000),
        vks::initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 10000)
    };

    VkDescriptorPoolCreateInfo descriptorPoolInfo =
        vks::initializers::descriptorPoolCreateInfo(
            static_cast<uint32_t>(poolSizes.size()),
            poolSizes.data(),
            40000);

    if (vkCreateDescriptorPool(mVKDevice, &descriptorPoolInfo, nullptr, &mDescriptorPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to vkCreateDescriptorPool!");
    }
}

void VulkanHelper::setupSwapChain()
{
    if (mPlatform)
    {
        return;
    }
    VkSwapchainKHR oldSwapchain = mSwapChain;


    // Get physical device surface properties and formats
    VkSurfaceCapabilitiesKHR surfCaps;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice,
        mSurface, &surfCaps) != VK_SUCCESS)
    {
        throw std::runtime_error("vkGetPhysicalDeviceSurfaceCapabilitiesKHR failed!");
    }

    // Get available present modes
    uint32_t presentModeCount;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice,
        mSurface, &presentModeCount, NULL) != VK_SUCCESS)
    {
        throw std::runtime_error("vkGetPhysicalDeviceSurfacePresentModesKHR failed!");
    }
    assert(presentModeCount > 0);

    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        mPhysicalDevice,
        mSurface,
        &presentModeCount,
        presentModes.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("vkGetPhysicalDeviceSurfacePresentModesKHR failed!");
    }

    VkExtent2D swapchainExtent = {};
    // If width (and height) equals the special value 0xFFFFFFFF, the size of the surface will be set by the swapchain
    if (surfCaps.currentExtent.width == (uint32_t)-1)
    {
        // If the surface size is undefined, the size is set to
        // the size of the images requested.
        swapchainExtent.width = mWidth;
        swapchainExtent.height = mHeight;
    }
    else
    {
        // If the surface size is defined, the swap chain size must match
        swapchainExtent = surfCaps.currentExtent;
    }

    VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
    bool vsync = false;
    if (!vsync)
    {
        for (size_t i = 0; i < presentModeCount; i++)
        {
            if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
                break;
            }
            if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)
            {
                swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
            }
        }
    }

    swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;

    uint32_t desiredNumberOfSwapchainImages = surfCaps.minImageCount + 1;

    if ((surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCaps.maxImageCount))
    {
        desiredNumberOfSwapchainImages = surfCaps.maxImageCount;
    }

    // Find the transformation of the surface
    VkSurfaceTransformFlagsKHR preTransform;
    if (surfCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
    {
        // We prefer a non-rotated transform
        preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    }
    else
    {
        preTransform = surfCaps.currentTransform;
    }

    // Find a supported composite alpha format (not all devices support alpha opaque)
    VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    // Simply select the first composite alpha format available
    std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };
    for (auto& compositeAlphaFlag : compositeAlphaFlags) {
        if (surfCaps.supportedCompositeAlpha & compositeAlphaFlag) {
            compositeAlpha = compositeAlphaFlag;
            break;
        };
    }
    SwapChainSupportDetails swapChainSupport =
        VulkanHelper::getSingleton().querySwapChainSupport(mPhysicalDevice);
    auto surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);

    mSwapChainImageFormat = surfaceFormat.format;
    mColorSpace = surfaceFormat.colorSpace;

    VkSwapchainCreateInfoKHR swapchainCI = {};
    swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCI.surface = mSurface;
    swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
    swapchainCI.imageFormat = mSwapChainImageFormat;
    swapchainCI.imageColorSpace = mColorSpace;
    swapchainCI.imageExtent = { swapchainExtent.width, swapchainExtent.height };
    swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCI.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
    swapchainCI.imageArrayLayers = 1;
    swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainCI.queueFamilyIndexCount = 0;
    swapchainCI.presentMode = swapchainPresentMode;
    // Setting oldSwapChain to the saved handle of the previous swapchain aids in resource reuse and makes sure that we can still present already acquired images
    swapchainCI.oldSwapchain = oldSwapchain;
    // Setting clipped to VK_TRUE allows the implementation to discard rendering outside of the surface area
    swapchainCI.clipped = VK_TRUE;
    swapchainCI.compositeAlpha = compositeAlpha;

    // Enable transfer source on swap chain images if supported
    if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
        swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    }

    // Enable transfer destination on swap chain images if supported
    if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
        swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    auto device = VulkanHelper::getSingleton()._getVkDevice();

    vkCreateSwapchainKHR(device, &swapchainCI, nullptr, &mSwapChain);

    // If an existing swap chain is re-created, destroy the old swap chain
    // This also cleans up all the presentable images
    if (oldSwapchain != VK_NULL_HANDLE)
    {
        for (uint32_t i = 0; i < desiredNumberOfSwapchainImages; i++)
        {
            vkDestroyImageView(device, mSwapChainbuffers[i]._view, nullptr);
        }
        vkDestroySwapchainKHR(device, oldSwapchain, nullptr);
    }
    vkGetSwapchainImagesKHR(device, mSwapChain, &desiredNumberOfSwapchainImages, NULL);

    // Get the swap chain images
    std::vector<VkImage> images;
    images.resize(desiredNumberOfSwapchainImages);
    vkGetSwapchainImagesKHR(device, mSwapChain, &desiredNumberOfSwapchainImages, images.data());



    /////////// 
    mSwapChainbuffers.resize(desiredNumberOfSwapchainImages);
    for (uint32_t i = 0; i < desiredNumberOfSwapchainImages; i++)
    {
        VkImageViewCreateInfo colorAttachmentView = {};
        colorAttachmentView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        colorAttachmentView.pNext = NULL;
        colorAttachmentView.format = mSwapChainImageFormat;
        colorAttachmentView.components = {
            VK_COMPONENT_SWIZZLE_R,
            VK_COMPONENT_SWIZZLE_G,
            VK_COMPONENT_SWIZZLE_B,
            VK_COMPONENT_SWIZZLE_A
        };
        colorAttachmentView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        colorAttachmentView.subresourceRange.baseMipLevel = 0;
        colorAttachmentView.subresourceRange.levelCount = 1;
        colorAttachmentView.subresourceRange.baseArrayLayer = 0;
        colorAttachmentView.subresourceRange.layerCount = 1;
        colorAttachmentView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        colorAttachmentView.flags = 0;

        mSwapChainbuffers[i]._image = images[i];

        colorAttachmentView.image = mSwapChainbuffers[i]._image;

        if (vkCreateImageView(device, &colorAttachmentView,
            nullptr, &mSwapChainbuffers[i]._view) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void VulkanHelper::createCommandBuffer()
{
    mFrameList.resize(VULKAN_FRAME_RESOURCE_COUNT);

    for (int32_t i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {

        mFrameList[i] = new VulkanFrame(i);
    }
}

void VulkanHelper::createSyncObjects()
{
    
}


void VulkanHelper::createPipelineCache()
{
    VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {};
    pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    vkCreatePipelineCache(mVKDevice, &pipelineCacheCreateInfo,
        nullptr, &mPipelineCache);
}

void VulkanHelper::setupDescriptorSetLayout()
{
    {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings =
        {
            // Binding 0 : Vertex shader uniform buffer
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                VK_SHADER_STAGE_VERTEX_BIT,
                0),
            // Binding 1 :  Vertex shader uniform buffer
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                1),
            // Binding 2 :  Vertex shader uniform buffer
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                2),
            // Binding 3 :  Vertex shader uniform buffer
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                VK_SHADER_STAGE_VERTEX_BIT,
                3)
            
        };

        VkDescriptorSetLayoutCreateInfo descriptorLayout =
            vks::initializers::descriptorSetLayoutCreateInfo(
                setLayoutBindings.data(),
                static_cast<uint32_t>(setLayoutBindings.size()));
        vkCreateDescriptorSetLayout(mVKDevice, &descriptorLayout,
            nullptr, &mDescriptorSetLayout[0]);
    }
    
    {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings =
        {
            // Binding 0 : Fragment shader image sampler
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                0),
            // Binding 1 : Fragment shader image sampler
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                1),
            // Binding 2 : Fragment shader image sampler
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                2),
            // Binding 3 : Fragment shader image sampler
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                3)
            
        };

        VkDescriptorSetLayoutCreateInfo descriptorLayout =
            vks::initializers::descriptorSetLayoutCreateInfo(
                setLayoutBindings.data(),
                static_cast<uint32_t>(setLayoutBindings.size()));
        vkCreateDescriptorSetLayout(mVKDevice, &descriptorLayout,
            nullptr, &mDescriptorSetLayout[1]);

        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindingsPbr =
        {
            // Binding 0 : albedo_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                0),
            // Binding 1 : normal_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                1),
            // Binding 2 : ao_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                2),
            // Binding 3 : metal_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                3),
            // Binding 4 : roughness_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                4),
            // Binding 5 : emissive_pbr
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                5)
            ,
            // Binding 6 : brdflut
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                6)
            ,
            // Binding 7 : irradiance
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                7)
            ,
            // Binding 8 : prefiltered
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                8)

        };

        auto descriptorLayoutPbr =
            vks::initializers::descriptorSetLayoutCreateInfo(
                setLayoutBindingsPbr.data(),
                static_cast<uint32_t>(setLayoutBindingsPbr.size()));
        vkCreateDescriptorSetLayout(mVKDevice, &descriptorLayoutPbr,
            nullptr, &mPbrDescriptorSetLayout);
    }
    


    VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo =
        vks::initializers::pipelineLayoutCreateInfo(
            mDescriptorSetLayout.data(),
            2);
    /*VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.size = sizeof(Ogre::Matrix4) * 2;
    pPipelineLayoutCreateInfo.pushConstantRangeCount = 1;
    pPipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;*/
    if (vkCreatePipelineLayout(mVKDevice, &pPipelineLayoutCreateInfo,
        nullptr, &mPipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkDescriptorSetLayout tmp[2];
    tmp[0] = mDescriptorSetLayout[0];
    tmp[1] = mPbrDescriptorSetLayout;
    pPipelineLayoutCreateInfo =
        vks::initializers::pipelineLayoutCreateInfo(
            &tmp[0],
            2);

    if (vkCreatePipelineLayout(mVKDevice, &pPipelineLayoutCreateInfo,
        nullptr, &mPipelineLayoutPbr) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}


void VulkanHelper::createSamples()
{

    VkSampler samplerStatePointWrap;
    VkSampler samplerStatePointClamp;
    VkSampler samplerStateLinearWrap;
    VkSampler samplerStateLinearClamp;
    VkSampler samplerStateAnisotropicWrap;
    VkSampler samplerStateAnisotropicClamp;

    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.magFilter = VK_FILTER_NEAREST;
    samplerInfo.minFilter = VK_FILTER_NEAREST;

    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    samplerInfo.maxAnisotropy = 1.0;
    samplerInfo.maxLod = (float)FLT_MAX;
    samplerInfo.maxAnisotropy = 8.0f;
    samplerInfo.anisotropyEnable = VK_TRUE;


    if (vkCreateSampler(mVKDevice, &samplerInfo, nullptr, &samplerStateAnisotropicWrap) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture sampler!");
    }
    samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 1.0f;
    samplerInfo.maxAnisotropy = 1.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;

    if (vkCreateSampler(mVKDevice, &samplerInfo, nullptr, &samplerStateAnisotropicClamp) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture sampler!");
    }
    mSamplers = { samplerStateAnisotropicWrap, samplerStateAnisotropicClamp};

}

VkSampler VulkanHelper::getSampler(Ogre::TextureAddressingMode mode)
{
    if (mode == TAM_CLAMP)
    {
        return mSamplers[1];
    }
    return mSamplers[0];
}

VkSampler VulkanHelper::getSampler(const filament::backend::SamplerParams& params)
{
    auto iter = mSamplersCache.find(params);
    if (UTILS_LIKELY(iter != mSamplersCache.end())) {
        //return iter->second;
    }
    VkSamplerCreateInfo samplerInfo{
            .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            .magFilter = VulkanMappings::getFilter(params.filterMag),
            .minFilter = VulkanMappings::getFilter(params.filterMin),
            .mipmapMode = VulkanMappings::getMipmapMode(params.filterMin),
            .addressModeU = VulkanMappings::getWrapMode(params.wrapS),
            .addressModeV = VulkanMappings::getWrapMode(params.wrapT),
            .addressModeW = VulkanMappings::getWrapMode(params.wrapR),
            .anisotropyEnable = params.anisotropyLog2 == 0 ? VK_FALSE : VK_TRUE,
            .maxAnisotropy = params.anisotropyLog2 == 0?0.0f:(float)(1u << params.anisotropyLog2),
            .compareEnable = VulkanMappings::getCompareEnable(params.compareMode),
            .compareOp = VulkanMappings::getCompareOp(params.compareFunc),
            .minLod = 0.0f,
            .maxLod = VulkanMappings::getMaxLod(params.filterMin),
            .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
            .unnormalizedCoordinates = VK_FALSE
    };

    VkSampler sampler;
    VkResult error = vkCreateSampler(mVKDevice, &samplerInfo, VKALLOC, &sampler);
    mSamplersCache.insert({ params, sampler });
    return sampler;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VkSurfaceFormatKHR VulkanHelper::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (auto&& surfaceFormat : availableFormats)
    {
        if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB)
        {
            return surfaceFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanHelper::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    for (const auto& availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanHelper::chooseSwapExtent(
    const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    }
    else
    {
        VkExtent2D actualExtent =
        {
            static_cast<uint32_t>(mWidth),
            static_cast<uint32_t>(mHeight)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void VulkanHelper::populateDebugMessengerCreateInfo(
    VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}


VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void VulkanHelper::setupDebugMessenger()
{
    if (!mEnableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(mVKInstance, 
        &createInfo, nullptr, &mDebugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}


void VulkanHelper::createBottomLevelAccelerationStructure()
{
}

void VulkanHelper::createTopLevelAccelerationStructure()
{
}

void VulkanHelper::createStorageImage()
{
}

void VulkanHelper::createShaderBindingTable()
{
}

VkCommandBuffer VulkanHelper::createCommandBuffer(VkCommandBufferLevel level, bool begin)
{
    VkCommandBufferAllocateInfo cmdBufAllocateInfo = vks::initializers::commandBufferAllocateInfo(mCommandPool[0], level, 1);
    VkCommandBuffer cmdBuffer;
    VK_CHECK_RESULT(vkAllocateCommandBuffers(mVKDevice, &cmdBufAllocateInfo, &cmdBuffer));
    // If requested, also start recording for the new command buffer
    if (begin)
    {
        VkCommandBufferBeginInfo cmdBufInfo = vks::initializers::commandBufferBeginInfo();
        VK_CHECK_RESULT(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));
    }
    return cmdBuffer;
}

VkCommandBuffer VulkanHelper::beginSingleTimeCommands()
{
    VkCommandBuffer commandBuffer;

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mSingleCommandPool;
    
   // 
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(mVKDevice, &allocInfo, &commandBuffer);


    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}


void VulkanHelper::endSingleTimeCommands(VkCommandBuffer commandBuffer)
{
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

  
    auto result = vkQueueSubmit(mGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkQueueSubmit!");
    }
    vkQueueWaitIdle(mGraphicsQueue);

    
}

void VulkanHelper::transitionImageLayout(
    VkImage image,
    VkFormat format,
    VkImageLayout oldLayout,
    VkImageLayout newLayout)
{
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkImageMemoryBarrier barrier = {};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    endSingleTimeCommands(commandBuffer);
}

void VulkanHelper::insertImageMemoryBarrier(
    VkCommandBuffer cmdbuffer,
    VkImage image,
    VkAccessFlags srcAccessMask,
    VkAccessFlags dstAccessMask,
    VkImageLayout oldImageLayout,
    VkImageLayout newImageLayout,
    VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask,
    VkImageSubresourceRange subresourceRange)
{
    VkImageMemoryBarrier imageMemoryBarrier = vks::initializers::imageMemoryBarrier();
    imageMemoryBarrier.srcAccessMask = srcAccessMask;
    imageMemoryBarrier.dstAccessMask = dstAccessMask;
    imageMemoryBarrier.oldLayout = oldImageLayout;
    imageMemoryBarrier.newLayout = newImageLayout;
    imageMemoryBarrier.image = image;
    imageMemoryBarrier.subresourceRange = subresourceRange;

    vkCmdPipelineBarrier(
        cmdbuffer,
        srcStageMask,
        dstStageMask,
        0,
        0, nullptr,
        0, nullptr,
        1, &imageMemoryBarrier);
}


VulkanDepthStencil VulkanHelper::createDepthStencil(uint32_t width, uint32_t height)
{
    VulkanDepthStencil dummy;

    VkImageCreateInfo imageCI{};
    imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCI.imageType = VK_IMAGE_TYPE_2D;
    imageCI.format = mDepthFormat;
    imageCI.extent = { (uint32_t)width, (uint32_t)height, 1 };
    imageCI.mipLevels = 1;
    imageCI.arrayLayers = 1;
    imageCI.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageCI.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    imageCI.flags = 0;

    if (vkCreateImage(mVKDevice, &imageCI, nullptr, &dummy.image) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to vkCreateImage!");
    }
    VkMemoryRequirements memReqs{};
    vkGetImageMemoryRequirements(mVKDevice, dummy.image, &memReqs);

    VkMemoryAllocateInfo memAllloc{};
    memAllloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllloc.allocationSize = memReqs.size;
    memAllloc.memoryTypeIndex = _findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(mVKDevice, &memAllloc, nullptr, &dummy.memory);
    vkBindImageMemory(mVKDevice, dummy.image, dummy.memory, 0);

    VkImageViewCreateInfo depthStencilView{};
    depthStencilView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depthStencilView.image = dummy.image;
    depthStencilView.format = mDepthFormat;
    depthStencilView.subresourceRange.baseMipLevel = 0;
    depthStencilView.subresourceRange.levelCount = 1;
    depthStencilView.subresourceRange.baseArrayLayer = 0;
    depthStencilView.subresourceRange.layerCount = 1;
    depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;


    if (vkCreateImageView(mVKDevice, &depthStencilView,nullptr, &dummy.view) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to vkCreateImageView!");
    }

    return dummy;
}

VkFormat VulkanHelper::_getDepthFormat()
{
    return mDepthFormat;
}

int32_t VulkanHelper::_findMemoryType(
    uint32_t typeFilter,
    VkMemoryPropertyFlags properties)
{
    for (uint32_t i = 0; i < mPhysicalMemoryProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) &&
            (mPhysicalMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    return -1;
}

VkQueue VulkanHelper::_getCommandQueue()
{
    return mGraphicsQueue;
}

VkPhysicalDevice VulkanHelper::_getPhysicalDevice()
{
    return mPhysicalDevice;
}

VkPipelineLayout VulkanHelper::_getPipelineLayout(bool pbr)
{
    if (pbr)
    {
        return mPipelineLayoutPbr;
    }
    
    return mPipelineLayout;
}

VkPipelineCache VulkanHelper::getPipelineCache()
{
    return mPipelineCache;
}

VulkanFrame* VulkanHelper::_getFrame(uint32_t index)
{
    return mFrameList[index];
}

void VulkanHelper::_resetCommandBuffer(uint32_t frame_index)
{
    if (vkResetCommandBuffer(mMainCommandBuffer[frame_index], 0) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkResetCommandBuffer!");
    }
}

void VulkanHelper::_endCommandBuffer(uint32_t frame_index)
{
#ifdef MULTI_RENDER
    std::vector<VkCommandBuffer> commandBuffers;
    commandBuffers.reserve(VULKAN_COMMAND_THREAD);
    for (uint32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
    {
        uint32_t start = frame_index * VULKAN_COMMAND_THREAD + i;
        VkCommandBuffer pCommandBuffer = mCommandPools[start]._commandBuffer;
        if (vkEndCommandBuffer(pCommandBuffer) != VK_SUCCESS)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkEndCommandBuffer!");
        }
        commandBuffers.push_back(pCommandBuffer);
    }

    vkCmdExecuteCommands(mMainCommandBuffer[frame_index], commandBuffers.size(), commandBuffers.data());
#endif
    if (!mSettings.rayTraceing)
    {
        //vkCmdEndRenderPass(mMainCommandBuffer[frame_index]);
    }
    
    if (vkEndCommandBuffer(mMainCommandBuffer[frame_index]) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkEndCommandBuffer!");
    }
}

void VulkanHelper::fillCommandBufferList(
    std::vector<VkCommandBuffer>& cmdlist, 
    uint32_t frame_index,
    bool have_main)
{
    cmdlist.clear();
    if(have_main)
        cmdlist.push_back(mMainCommandBuffer[frame_index]);
#ifdef MULTI_RENDER
    for (uint32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
    {
        uint32_t start = frame_index * VULKAN_COMMAND_THREAD + i;
        cmdlist.push_back(mCommandPools[start]._commandBuffer);
    }
#endif
}

VkCommandBuffer VulkanHelper::getMainCommandBuffer(uint32_t frame_index)
{
    return mMainCommandBuffer[frame_index];
}

VkCommandBuffer VulkanHelper::_getThreadCommandBuffer(uint32_t tdx, uint32_t frame_index)
{
    uint32_t start = frame_index * VULKAN_COMMAND_THREAD + tdx;
    return mCommandPools[start]._commandBuffer;
}

VkDescriptorPool VulkanHelper::_getDescriptorPool()
{
    return mDescriptorPool;
}

VkDescriptorSetLayout VulkanHelper::_getDescriptorSetLayout(VulkanLayoutIndex index)
{
    switch (index)
    {
    case VulkanLayoutIndex_Data:
        return mDescriptorSetLayout[0];
    case VulkanLayoutIndex_Unlit:
        return mDescriptorSetLayout[1];
    case VulkanLayoutIndex_Pbr:
        return mPbrDescriptorSetLayout;
    default:
        assert(false);
        return VK_NULL_HANDLE;
    }
}

VkSurfaceKHR VulkanHelper::_getSurface()
{
    return mSurface;
}

