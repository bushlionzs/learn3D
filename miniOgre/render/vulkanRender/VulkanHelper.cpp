#include "OgreHeader.h"
#include "OgreTextureManager.h"
#include "OgreResourceManager.h"
#include "glslUtil.h"
#include "VulkanHelper.h"
#include "VulkanRenderSystem.h"
#include "VulkanTools.h"
#include "VulkanFrame.h"
#include "VulkanHardwareBufferManager.h"
#include "VulkanBuffer.h"
#include "VulkanMappings.h"
#include "VulkanLayoutCache.h"
#include "VulkanPipelineCache.h"
#include "VulkanPipelineLayoutCache.h"
#include "shaderManager.h"


static VmaAllocator createAllocator(VkInstance instance, VkPhysicalDevice physicalDevice,
    VkDevice device) {
    VmaAllocator allocator;
    VmaVulkanFunctions const funcs{
#if VMA_DYNAMIC_VULKAN_FUNCTIONS
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
#else
        .vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties,
        .vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties,
        .vkAllocateMemory = vkAllocateMemory,
        .vkFreeMemory = vkFreeMemory,
        .vkMapMemory = vkMapMemory,
        .vkUnmapMemory = vkUnmapMemory,
        .vkFlushMappedMemoryRanges = vkFlushMappedMemoryRanges,
        .vkInvalidateMappedMemoryRanges = vkInvalidateMappedMemoryRanges,
        .vkBindBufferMemory = vkBindBufferMemory,
        .vkBindImageMemory = vkBindImageMemory,
        .vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements,
        .vkGetImageMemoryRequirements = vkGetImageMemoryRequirements,
        .vkCreateBuffer = vkCreateBuffer,
        .vkDestroyBuffer = vkDestroyBuffer,
        .vkCreateImage = vkCreateImage,
        .vkDestroyImage = vkDestroyImage,
        .vkCmdCopyBuffer = vkCmdCopyBuffer,
        .vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2KHR,
        .vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2KHR
#endif
    };
    VmaAllocatorCreateInfo const allocatorInfo{
        .physicalDevice = physicalDevice,
        .device = device,
        .pVulkanFunctions = &funcs,
        .instance = instance,
    };
    vmaCreateAllocator(&allocatorInfo, &allocator);
    return allocator;
}


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

VulkanHelper::VulkanHelper(VulkanRenderSystemBase* rs)
    :mResourceAllocator(8388608, false)
{
    mVulkanRenderSystem = rs;

 
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

void VulkanHelper::_initialise(VulkanPlatform* platform)
{
    this->mSettings.rayTraceing = false;
    mPlatform = platform;

    if (mSettings.rayTraceing)
    {
        deviceExtensions.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
        deviceExtensions.push_back(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);
    }
   

    Platform::DriverConfig config;

    mPlatform->createDriver(nullptr, config);

    mVKInstance = mPlatform->getInstance();
    mPhysicalDevice = mPlatform->getPhysicalDevice();
    vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mDeviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mPhysicalMemoryProperties);
    mVKDevice = mPlatform->getDevice();

    
    createCommandPool();
    createDescriptorPool();
    setupDescriptorSetLayout();
    createSamples();

    mFrameList.resize(VULKAN_FRAME_RESOURCE_COUNT);

    for (int32_t i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {
        mFrameList[i] = new VulkanFrame(i);
    }
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


VkPhysicalDeviceProperties& VulkanHelper::_getVkPhysicalDeviceProperties()
{
    return mPhysicalDeviceProperties;
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
    //beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
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

    auto queue = mPlatform->getGraphicsQueue();

    auto result = vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkQueueSubmit!");
    }
    vkQueueWaitIdle(queue);
}


void VulkanHelper::createCommandPool()
{
    VkCommandPoolCreateInfo cmdPoolInfo = {};


    cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.queueFamilyIndex = mPlatform->getGraphicsQueueIndex();
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
                3),
            // Binding 4 : Fragment shader image sampler
            vks::initializers::descriptorSetLayoutBinding(
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                VK_SHADER_STAGE_FRAGMENT_BIT,
                4)
            
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

    mAllocator = createAllocator(mVKInstance, mPhysicalDevice, mVKDevice);

    mLayoutCache = new VulkanLayoutCache(mVKDevice, &mResourceAllocator);

    mPipelineCache = new VulkanPipelineCache(mVKDevice, mAllocator);

    mPipelineLayoutCache = new VulkanPipelineLayoutCache(mVKDevice, &mResourceAllocator);
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


VkPipelineLayout VulkanHelper::_getPipelineLayout(bool pbr)
{
    if (pbr)
    {
        return mPipelineLayoutPbr;
    }
    
    return mPipelineLayout;
}


VulkanFrame* VulkanHelper::_getFrame(uint32_t index)
{
    return mFrameList[index];
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

