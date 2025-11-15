#include <OgreHeader.h>
#include "OgreRoot.h"
#include "OgreNode.h"
#include "OgreResourceManager.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreStringConverter.h"
#include "VulkanRenderSystemBase.h"
#include "VulkanWindow.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanMappings.h"
#include "VulkanTools.h"
#include "VulkanPipelineLayoutCache.h"
#include "VulkanPipelineCache.h"
#include "VulkanBuffer.h"
#include "VulkanLayoutCache.h"
#include "shaderManager.h"
#include "glslUtil.h"
#include "VulkanPlatformSwapChainImpl.h"
#include <vk_mem_alloc.h>
#define MAX_HANDLE_COUNT 256
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
    VmaAllocatorCreateInfo  allocatorInfo{
        .physicalDevice = physicalDevice,
        .device = device,
        .pVulkanFunctions = &funcs,
        .instance = instance,
    };
    VulkanSettings* settings = VulkanHelper::getSingleton().getVulkanSettings();
    if (settings->mRayPipelineSupported)
    {
        allocatorInfo.flags |= 
            VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR |
            VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
            VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    }
    
    vmaCreateAllocator(&allocatorInfo, &allocator);
    return allocator;
}

VulkanRenderSystemBase::VulkanRenderSystemBase()
    :
    mResourceAllocator(83886080, false)
{
    new VulkanHelper(this);
}

VulkanRenderSystemBase::~VulkanRenderSystemBase()
{

}

bool VulkanRenderSystemBase::engineInit(bool raytracing)
{
    mVulkanPlatform = new VulkanPlatform();


    VulkanHelper& helper = VulkanHelper::getSingleton();
    VulkanSettings* settings = helper.getVulkanSettings();
    settings->mRayPipelineSupported = raytracing;


    helper._initialise(mVulkanPlatform);

    auto device = mVulkanPlatform->getDevice();

    vkGetPhysicalDeviceProperties(mVulkanPlatform->getPhysicalDevice(), &physical_device_properties);

    {
        void* next_properties = nullptr;
        VkPhysicalDeviceFragmentShadingRatePropertiesKHR vrs_properties = {};
        VkPhysicalDeviceMultiviewProperties multiview_properties = {};
        VkPhysicalDeviceSubgroupProperties subgroup_properties = {};
        VkPhysicalDeviceSubgroupSizeControlProperties subgroup_size_control_properties = {};
        VkPhysicalDeviceProperties2 physical_device_properties_2 = {};

        const bool use_1_1_properties = physical_device_properties.apiVersion >= VK_API_VERSION_1_1;
        if (use_1_1_properties) {
            subgroup_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
            subgroup_properties.pNext = next_properties;
            next_properties = &subgroup_properties;

            subgroup_capabilities.size_control_is_supported = true;
            if (subgroup_capabilities.size_control_is_supported) {
                subgroup_size_control_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES;
                subgroup_size_control_properties.pNext = next_properties;
                next_properties = &subgroup_size_control_properties;
            }
        }

        if (true) {
            multiview_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
            multiview_properties.pNext = next_properties;
            next_properties = &multiview_properties;
        }

        

        physical_device_properties_2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        physical_device_properties_2.pNext = next_properties;
        vkGetPhysicalDeviceProperties2(mVulkanPlatform->getPhysicalDevice(), &physical_device_properties_2);

        subgroup_capabilities.size = subgroup_properties.subgroupSize;
        subgroup_capabilities.min_size = subgroup_properties.subgroupSize;
        subgroup_capabilities.max_size = subgroup_properties.subgroupSize;
        subgroup_capabilities.supported_stages = subgroup_properties.supportedStages;
        subgroup_capabilities.supported_operations = subgroup_properties.supportedOperations;
    }



    mAllocator = createAllocator(
        mVulkanPlatform->getInstance(), mVulkanPlatform->getPhysicalDevice(), device);
    
    auto queue = mVulkanPlatform->getGraphicsQueue();
    auto queueIndex = mVulkanPlatform->getGraphicsQueueIndex();

    mCommands = new VulkanCommands(device, queue, queueIndex, &mVulkanContext, &mResourceAllocator);
    mStagePool = new VulkanStagePool(mAllocator, mCommands);

    mPipelineCache = helper.getPipelineCache();
    mPipelineLayoutCache = helper.getPipelineLayoutCache();

    mVulkanSettings = helper.getVulkanSettings();
    mVulkanLayoutCache = new VulkanLayoutCache(device, &mResourceAllocator);
    mDescriptorInfinitePool = new DescriptorInfinitePool(device);

    VkDescriptorSetLayoutCreateInfo layoutCreateInfo = {};
    layoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    vkCreateDescriptorSetLayout(device, &layoutCreateInfo,
        nullptr,
        &pEmptyDescriptorSetLayout);
    VkDescriptorPoolSize descriptorPoolSizes[1] = { { VK_DESCRIPTOR_TYPE_SAMPLER, 1 } };
    VkDescriptorPoolCreateInfo poolCreateInfo = {};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolCreateInfo.pNext = NULL;
    poolCreateInfo.poolSizeCount = 1;
    poolCreateInfo.pPoolSizes = descriptorPoolSizes;
    poolCreateInfo.flags = 0;
    poolCreateInfo.maxSets = 1;
    vkCreateDescriptorPool(device, &poolCreateInfo, nullptr, &pEmptyDescriptorPool);

    VkDescriptorSetAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc_info.pNext = NULL;
    alloc_info.descriptorPool = pEmptyDescriptorPool;
    alloc_info.descriptorSetCount = 1;
    alloc_info.pSetLayouts = &pEmptyDescriptorSetLayout;
    vkAllocateDescriptorSets(device, &alloc_info, &pEmptyDescriptorSet);

    for (uint32_t i = 0; i < 2; i++)
    {
        mTransferContext[i].cbh = createCommandBuffer(QUEUE_TYPE_TRANSFER);
    }
    

    mFlushFence = createFence(true);
    return true;
}


Ogre::OgreTexture* VulkanRenderSystemBase::createManualTexture(
    const std::string& name,
    Ogre::TextureProperty* texProperty)
{
    auto tex = new VulkanTexture(name, mVulkanPlatform, mCommands, nullptr, texProperty);
    return tex;
}

void VulkanRenderSystemBase::ready()
{
    VulkanHelper::getSingleton().loadDefaultResources();
}

Ogre::RenderWindow* VulkanRenderSystemBase::createRenderWindow(
    const CreateWindowDesc& desc)
{
    uint64_t wnd = (uint64_t)StringConverter::parseSizeT(desc.windowHandle);

    uint32_t flags = 0;

    if (desc.srgb)
    {
        flags = backend::SWAP_CHAIN_CONFIG_SRGB_COLORSPACE;
    }

    mRenderWindow = new VulkanWindow(wnd, flags);
    return mRenderWindow;
}

Ogre::RenderTarget* VulkanRenderSystemBase::createRenderTarget(
    const String& name, 
    TextureProperty& texProperty)
{
    if (texProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
    }

    Ogre::VulkanRenderTarget* renderTarget = new Ogre::VulkanRenderTarget(
        name, mVulkanPlatform, mCommands, texProperty);
    return renderTarget;
}

void VulkanRenderSystemBase::clearRenderTarget(
    Ogre::RenderTarget* target, 
    const Ogre::Vector4& color,
    const Ogre::TextureSubresourceRange& subresources)
{
    clearRenderTexture(target->getTarget(), color, subresources, nullptr);
}

void VulkanRenderSystemBase::clearRenderTexture(
    OgreTexture* tex, 
    const Ogre::Vector4& color,
    const Ogre::TextureSubresourceRange& subresources,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
    )
{
    VkClearColorValue clearColor = { color.x, color.y, color.z, color.w };
    VkImageSubresourceRange subresourceRange = {};
    subresourceRange.aspectMask = VulkanMappings::getAspect(subresources.aspect);
    subresourceRange.baseMipLevel = subresources.base_mipmap;
    subresourceRange.levelCount = subresources.mipmap_count;
    subresourceRange.baseArrayLayer = subresources.base_layer;
    subresourceRange.layerCount = subresources.layer_count;
    VkCommandBuffer cmdBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();
    }

    VulkanTexture* vulkanTexture = (VulkanTexture*)tex;
    vkCmdClearColorImage(
        cmdBuffer,
        vulkanTexture->getVkImage(),
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        &clearColor,
        1,
        &subresourceRange
    );
}

void VulkanRenderSystemBase::frameStart()
{
    mTriangleCount = 0;
    mBatchCount = 0;
    mLastPipeline = VK_NULL_HANDLE;
    if (mCommandBuffer == nullptr)
    {
        mCommandBuffer = mCommands->get().buffer();
    }
    
    bool resized = false;

    VulkanSwapChain*  swapChain = mRenderWindow->getSwapChain();
    swapChain->acquire(resized);
}



void VulkanRenderSystemBase::frameEnd()
{
    mStagePool->gc();
    mCommandBuffer = nullptr;
}

void VulkanRenderSystemBase::setViewport(
    float x, float y, float width, float height, float minDepth, float maxDepth,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    VkViewport viewport{};
    viewport.x = 0.0;

    viewport.width = width;


    if (true)
    {
        viewport.height = -(float)height;
        viewport.y = height;
    }
    else
    {
        viewport.height = (float)height;
        viewport.y = 0;
    }
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;


    VkCommandBuffer cmdBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommandBuffer;
    }
    bluevk::vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
}

void VulkanRenderSystemBase::setScissor(
    uint32_t x, uint32_t y, uint32_t width, uint32_t height,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    VkRect2D scissor = vks::initializers::rect2D(width, height, x, y);

    VkCommandBuffer cmdBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommandBuffer;
    }
    bluevk::vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);
}

void VulkanRenderSystemBase::beginRenderPass(
    RenderPassInfo& renderPassInfo)
{
    VkCommandBuffer cmdBuffer;
    if (renderPassInfo.cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(renderPassInfo.cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();
    }

    VkRenderingAttachmentInfo colorAttachments[MAX_RENDER_TARGET_ATTACHMENTS] = {};
    VkRenderingAttachmentInfo depthAttachment = {};

    for (auto i = 0; i < renderPassInfo.renderTargetCount; i++)
    {
        colorAttachments[i].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        colorAttachments[i].pNext = NULL;
        colorAttachments[i].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        colorAttachments[i].loadOp = VulkanMappings::getVkAttachmentLoadOp(renderPassInfo.renderLoadAction);
        colorAttachments[i].storeOp = VulkanMappings::getVkAttachmentStoreOp(renderPassInfo.renderStoreAction);
        
        VulkanTexture* vulkanTexture = nullptr;
        if (renderPassInfo.renderTargets[i].isTexture)
        {
            vulkanTexture = (VulkanTexture*)renderPassInfo.renderTargets[i].target.texture;
        }
        else
        {
            Ogre::VulkanRenderTarget* rt = (Ogre::VulkanRenderTarget*)renderPassInfo.renderTargets[i].target.renderTarget;
            vulkanTexture = (VulkanTexture*)rt->getTarget();
        }
        

        vks::tools::insertImageMemoryBarrier(
            cmdBuffer,
            vulkanTexture->getVkImage(),
            0,
            VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        colorAttachments[i].imageView = vulkanTexture->getVkImageView();
        const ClearValue* clearValue = &renderPassInfo.renderTargets[i].clearColour;
        colorAttachments[i].clearValue.color = { { clearValue->r, clearValue->g, clearValue->b, clearValue->a } };
    }

    bool hasDepth = renderPassInfo.depthTarget.target.depthStencil != nullptr;

    if (hasDepth)
    {
        depthAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        depthAttachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        depthAttachment.loadOp = VulkanMappings::getVkAttachmentLoadOp(renderPassInfo.depthLoadAction);
        depthAttachment.storeOp = VulkanMappings::getVkAttachmentStoreOp(renderPassInfo.depthStoreAction);

        VkImageView imageView = nullptr;
        if (renderPassInfo.depthTarget.isTexture)
        {
            VulkanTexture* depth = (VulkanTexture*)renderPassInfo.depthTarget.target.texture;
            imageView = depth->getVkImageViewEx(renderPassInfo.depthTarget.depthIndex);
        }
        else
        {
            Ogre::VulkanRenderTarget* rt = (Ogre::VulkanRenderTarget*)renderPassInfo.depthTarget.target.depthStencil;
            imageView = rt->getImageView(renderPassInfo.depthTarget.depthIndex);
        }
        
        depthAttachment.imageView = imageView;


        const ClearValue* clearValue = &renderPassInfo.depthTarget.clearValue;
        depthAttachment.clearValue.depthStencil = { clearValue->depth, clearValue->stencil };

    }

    VkRect2D renderArea = {};
    renderArea.offset.x = 0;
    renderArea.offset.y = 0;
    uint32_t layerCount = 0;
    if (renderPassInfo.renderTargetCount)
    {
        VulkanTexture* vulkanTexture = nullptr;
        if (renderPassInfo.renderTargets[0].isTexture)
        {
            vulkanTexture = (VulkanTexture*)renderPassInfo.renderTargets[0].target.texture;
        }
        else
        {
            Ogre::VulkanRenderTarget* rt = (Ogre::VulkanRenderTarget*)renderPassInfo.renderTargets[0].target.renderTarget;
            vulkanTexture = (VulkanTexture*)rt->getTarget();
        }
        renderArea.extent.width = vulkanTexture->getWidth();
        renderArea.extent.height = vulkanTexture->getHeight();
        layerCount = 1;
    }
    else if (hasDepth)
    {
        uint32_t width = 0;
        uint32_t height = 0;
        if (renderPassInfo.depthTarget.isTexture)
        {
            width = renderPassInfo.depthTarget.target.texture->getWidth();
            height = renderPassInfo.depthTarget.target.texture->getHeight();
        }
        else
        {
            width = renderPassInfo.depthTarget.target.depthStencil->getWidth();
            height = renderPassInfo.depthTarget.target.depthStencil->getHeight();
        }
        renderArea.extent.width = width;
        renderArea.extent.height = height;
        layerCount = 1;
    }
    else
    {
        renderArea.extent.width = renderPassInfo.extent[0];
        renderArea.extent.height = renderPassInfo.extent[1];
        layerCount = 1;
    }

    VkRenderingInfoKHR renderingInfo = {};
    renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
    renderingInfo.pColorAttachments = colorAttachments;
    renderingInfo.colorAttachmentCount = renderPassInfo.renderTargetCount;
    renderingInfo.pDepthAttachment = hasDepth ? &depthAttachment : nullptr;
    renderingInfo.pStencilAttachment = nullptr;
    renderingInfo.renderArea = renderArea;
    renderingInfo.layerCount = layerCount;


    bluevk::vkCmdBeginRenderingKHR(cmdBuffer, &renderingInfo);

    if (renderPassInfo.viewport)
    {
        auto width = renderArea.extent.width;
        auto height = renderArea.extent.height;
        VkViewport viewport{};
        viewport.x = 0.0;
        
        viewport.width = width;
        

        if (renderPassInfo.flipY)
        {
            viewport.height = -(float)height;
            viewport.y = height;
        }
        else
        {
            viewport.height = (float)height;
            viewport.y = 0;
        }
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor = vks::initializers::rect2D(width, height, 0, 0);

        bluevk::vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
        bluevk::vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);
    }
}

void VulkanRenderSystemBase::endRenderPass(RenderPassInfo& renderPassInfo)
{
    VkCommandBuffer cmdBuffer;
    if (renderPassInfo.cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(renderPassInfo.cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();
    }
    bluevk::vkCmdEndRenderingKHR(cmdBuffer);
}


void VulkanRenderSystemBase::bindPipeline(
    Handle<HwPipeline> pipelineHandle)
{
    
    VkCommandBuffer commandBuffer = mCommands->get().buffer();
    VulkanPipeline* vulkanPipeline = mResourceAllocator.handle_cast<VulkanPipeline*>(pipelineHandle);
    VulkanShaderProgram* vulkanProgram = (VulkanShaderProgram*)vulkanPipeline->getProgram();
    auto pipeline = vulkanPipeline->getPipeline();
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);    
}

void VulkanRenderSystemBase::bindDescriptorSets(
    filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle,
    const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
    uint32_t setCount)
{
    VkCommandBuffer commandBuffer = mCommands->get().buffer();
    VulkanPipeline* vulkanPipeline = mResourceAllocator.handle_cast<VulkanPipeline*>(pipelineHandle);
    VulkanShaderProgram* vulkanProgram = (VulkanShaderProgram*)vulkanPipeline->getProgram();
    auto pipelineLayout = vulkanProgram->getVulkanPipelineLayout();
    for (uint32_t i = 0; i < setCount; i++)
    {
        if (!descSets[i])
            continue;
        VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(descSets[i]);
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
            pipelineLayout, set->mSet, 1, &set->vkSet, 0, nullptr);
    }
}

void VulkanRenderSystemBase::draw(uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    if (cbh)
    {
        VulkanCommandBuffer2* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        vkCmdDraw(vulkanBufferObject->commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    else
    {
        vkCmdDraw(mCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    
    incrTriangleCount(vertexCount / 3);
    incrBatchCount(1);
}

void VulkanRenderSystemBase::drawIndexed(
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    uint32_t vertexOffset,
    uint32_t firstInstance,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    if (cbh)
    {
        VulkanCommandBuffer2* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        vkCmdDrawIndexed(vulkanBufferObject->commandBuffer, indexCount, instanceCount,
            firstIndex, vertexOffset, firstInstance);
    }
    else
    {
        vkCmdDrawIndexed(mCommandBuffer, indexCount, instanceCount,
            firstIndex, vertexOffset, firstInstance);
    }
    

    incrTriangleCount(indexCount / 3);

    incrBatchCount(1);
}

void VulkanRenderSystemBase::drawIndexedIndirect(
    Handle<HwBufferObject> drawBuffer,
    uint32_t offset,
    uint32_t drawCount,
    uint32_t stride,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
)
{
    VkCommandBuffer cmdBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuffer = vulkanBufferObject->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();
    }
   
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(drawBuffer);
    VkBuffer vkBuf = vulkanBufferObject->buffer.getGpuBuffer();
    vkCmdDrawIndexedIndirect(cmdBuffer, vkBuf, offset, drawCount, stride);
}

void VulkanRenderSystemBase::bindComputePipeline(
    Handle<HwComputeProgram> pipelineHandle,
    Handle<HwCommandBuffer> cbh,
    const Handle<HwDescriptorSet>* descSets,
    uint32_t setCount)
{
    VulkanComputeProgram* program = mResourceAllocator.handle_cast<VulkanComputeProgram*>(pipelineHandle);
    VulkanCommandBuffer2* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    auto pipeline = program->getPipeline();
    auto pipelineLayout = program->getPipelineLayout();

    vkCmdBindPipeline(vulkanBufferObject->commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);

    VkDescriptorSet descriptorSet[4];
    uint32_t index = 0;
    for (uint32_t i = 0; i < setCount; i++)
    {
        VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(descSets[i]);
        descriptorSet[index] = set->vkSet;
        index++;
    }

    vkCmdBindDescriptorSets(vulkanBufferObject->commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
        pipelineLayout, 0, index, &descriptorSet[0], 0, nullptr);
}

void VulkanRenderSystemBase::dispatchComputeShader(int32_t x, int32_t y, int32_t z, 
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        vkCmdDispatch(cb->commandBuffer, x, y, z);
    }
    else
    {
        vkCmdDispatch(mCommandBuffer, x, y, z);
    }
    
}


void VulkanRenderSystemBase::present()
{
    VulkanSwapChain* swapChain = mRenderWindow->getSwapChain();
    swapChain->present();
}

void VulkanRenderSystemBase::copyImage(
    Handle<HwCommandBuffer> cbh,
    Ogre::RenderTarget* dst,
    Ogre::RenderTarget* src,
    ImageCopyDesc& desc)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    auto cl = cb->commandBuffer;
    VkImageCopy copyRegion{};
    copyRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    copyRegion.srcSubresource.baseArrayLayer = desc.srcSubresource.baseArrayLayer;
    copyRegion.srcSubresource.layerCount = desc.srcSubresource.layerCount;
    copyRegion.srcSubresource.mipLevel = desc.srcSubresource.mipLevel;

    copyRegion.srcOffset = { 0, 0, 0 };
    copyRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    copyRegion.dstSubresource.baseArrayLayer = desc.dstSubresource.baseArrayLayer;
    copyRegion.dstSubresource.layerCount = desc.dstSubresource.layerCount;
    copyRegion.dstSubresource.mipLevel = desc.dstSubresource.mipLevel;
    copyRegion.dstOffset = { 0, 0, 0 };
    copyRegion.extent.width = desc.extent.width;
    copyRegion.extent.height = desc.extent.height;
    copyRegion.extent.depth = desc.extent.depth;
    VulkanTexture* srcImage = (VulkanTexture*)src->getTarget();
    VulkanTexture* dstImage = (VulkanTexture*)dst->getTarget();
    vkCmdCopyImage(cl, srcImage->getVkImage(),
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        dstImage->getVkImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1, &copyRegion);
}

void VulkanRenderSystemBase::copyBuffer(
    Handle<HwBufferObject> src,
    uint32_t srcOffset,
    Handle<HwBufferObject> dst,
    uint32_t dstOffset,
    uint32_t size,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
)
{
    VkBuffer dstBuffer = mResourceAllocator.handle_cast<VulkanBufferObject*>(dst)->buffer.getGpuBuffer();
    VkBuffer srcBuffer = mResourceAllocator.handle_cast<VulkanBufferObject*>(src)->buffer.getGpuBuffer();

    VkBufferCopy copyRegion = {};
    copyRegion.srcOffset = srcOffset;
    copyRegion.dstOffset = dstOffset;
    copyRegion.size = size;   

    VkCommandBuffer cmdBuf = mCommandBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuf = cb->commandBuffer;
    }

    vkCmdCopyBuffer(cmdBuf, srcBuffer, dstBuffer, 1, &copyRegion);
}

void VulkanRenderSystemBase::copyBufferToTexture(
    Handle<HwCommandBuffer> cbh,
    Handle<HwBufferObject> boh,
    Ogre::OgreTexture* tex,
    Ogre::ImageCopyBufferDesc& desc
)
{
    VulkanBufferObject* vbo = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh);
    if (vbo->byteCount == 32)
    {
        int kk = 0;
    }
    VkBuffer srcBuffer = vbo->buffer.getGpuBuffer();
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    
    VulkanTexture* vulkanTexture = (VulkanTexture*)tex;
    VkImageLayout vkImageLayout = VulkanMappings::getImageLayout(desc.textureLayout);

    VkBufferImageCopy vkImageCopy{};
    vkImageCopy.bufferOffset = desc.bufferOffset;
    vkImageCopy.imageOffset.x = desc.textureOffset.x;
    vkImageCopy.imageOffset.y = desc.textureOffset.y;
    vkImageCopy.imageOffset.z = desc.textureOffset.z;
    vkImageCopy.imageExtent.width = desc.textureRegionSize.x;
    vkImageCopy.imageExtent.height = desc.textureRegionSize.y;
    vkImageCopy.imageExtent.depth = desc.textureRegionSize.z;
    vkImageCopy.imageSubresource.aspectMask = desc.textureSubresources.aspectMask;
    vkImageCopy.imageSubresource.mipLevel = desc.textureSubresources.mipLevel;
    vkImageCopy.imageSubresource.baseArrayLayer = desc.textureSubresources.baseArrayLayer;
    vkImageCopy.imageSubresource.layerCount = desc.textureSubresources.layerCount;
    vkCmdCopyBufferToImage(cb->commandBuffer, srcBuffer,
        vulkanTexture->getVkImage(), vkImageLayout, 1, &vkImageCopy);

}

void VulkanRenderSystemBase::pushGroupMarker(Handle<HwCommandBuffer> cbh, const char* maker, const Ogre::Vector3i& color)
{
    if (mVulkanSettings->mDebugUtilsExtension)
    {
        VkDebugUtilsLabelEXT markerInfo = {};
        markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
        markerInfo.color[0] = 1.0f;
        markerInfo.color[1] = 1.0f;
        markerInfo.color[2] = 0.0f;
        markerInfo.color[3] = 1.0f;
        markerInfo.pLabelName = maker;
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
        vkCmdBeginDebugUtilsLabelEXT(cb->commandBuffer, &markerInfo);
    }
    
}

void VulkanRenderSystemBase::popGroupMarker(Handle<HwCommandBuffer> cbh)
{
    if (mVulkanSettings->mDebugUtilsExtension)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
        vkCmdEndDebugUtilsLabelEXT(cb->commandBuffer);
    }
}

void VulkanRenderSystemBase::getFamilyInfo(FamilyInfo& desc)
{
    desc.graphicsQueueFamilyIndex = mVulkanPlatform->getGraphicsQueueFamilyIndex();
    desc.transferQueueFamilyIndex = mVulkanPlatform->getTransferQueueFamilyIndex();
    desc.transferQueueCount = mVulkanPlatform->getTransferQueueCount();
}

uint8_t* VulkanRenderSystemBase::bufferMap(Handle<HwBufferObject> bufHandle)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);
    return (uint8_t*)vulkanBufferObject->buffer.lock(0, INT_MAX);
}

void VulkanRenderSystemBase::bufferUnmap(Handle<HwBufferObject> bufHandle, Handle<HwCommandBuffer> cbh)
{
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
        VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);
        vulkanBufferObject->buffer.unlock(cb->commandBuffer);
    }
    else
    {
        VulkanCommandBuffer& cb =  mCommands->get();
        VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);
        vulkanBufferObject->buffer.unlock(cb.buffer());
    }
}

void VulkanRenderSystemBase::bindVertexBuffer(
    Handle<HwBufferObject> bufferHandle, 
    uint32_t binding,
    uint32_t vertexSize)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufferHandle);

    VkDeviceSize offsets[1] = { 0 };
    auto cmdBuffer = mCommands->get().buffer();

    VkBuffer vkBuffer = vulkanBufferObject->buffer.getGpuBuffer();
    vkCmdBindVertexBuffers(cmdBuffer, binding, 1, &vkBuffer, offsets);

}

void VulkanRenderSystemBase::bindIndexBuffer(
    Handle<HwBufferObject> bufferHandle, 
    uint32_t indexSize,
    uint32_t offset)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufferHandle);
    auto cmdBuffer = mCommands->get().buffer();

    VkBuffer vkBuffer = vulkanBufferObject->buffer.getGpuBuffer();

    vkCmdBindIndexBuffer(cmdBuffer, vkBuffer, offset, indexSize==2? VK_INDEX_TYPE_UINT16: VK_INDEX_TYPE_UINT32);
}

Handle<HwBufferObject> VulkanRenderSystemBase::createBufferObject(
    BufferDesc& desc)
{
    Handle<HwBufferObject> boh =  mResourceAllocator.allocHandle<VulkanBufferObject>();

    VulkanBufferObject* bufferObject = mResourceAllocator.construct<VulkanBufferObject>(boh, mAllocator,
        *mStagePool, desc);

    /*vks::tools::set_object_name(mVulkanPlatform->getDevice(),
        OBJECT_TYPE_BUFFER,
        (uint64_t)bufferObject->buffer.getGpuBuffer(), desc.pName);*/
    bufferObject->buffer.setBufferName(mVulkanPlatform->getDevice(), desc.pName);
    
    
    return boh;
}

void VulkanRenderSystemBase::updateBufferObject(
    Handle<HwBufferObject> boh,
    const char* data,
    uint32_t size,
    uint32_t offset,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    VkCommandBuffer cmdBuffer;
    if (cbh)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*cbh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();

    }
    VulkanBufferObject* bo = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh);
    bo->buffer.loadFromCpu(cmdBuffer, data, offset, size);
}

bool VulkanRenderSystemBase::getBufferInfo(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    Ogre::BufferDesc& desc)
{
    VulkanBufferObject* bo = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh);
    desc.mSize = bo->buffer.getBufferBytes();
    return true;
}

void VulkanRenderSystemBase::clearBufferObject(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
)
{
    VulkanBufferObject* bo = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh);

    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);

    bo->buffer.clearBuffer(cb->commandBuffer);

}

bool VulkanRenderSystemBase::getBufferObject(Handle<HwBufferObject> boh,
    char* data,
    uint32_t size,
    uint32_t offset)
{
    assert_invariant(false);
    return true;
}
static std::set< VulkanShaderProgram*> aa;
Handle<HwDescriptorSet> VulkanRenderSystemBase::createDescriptorSet(
    Handle<HwProgram> programHandle,
    uint32_t set)
{
    VulkanShaderProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanShaderProgram*>(programHandle);
    const char* name = vulkanProgram->name.c_str();
    
    Handle<HwDescriptorSetLayout> layoutHandle = vulkanProgram->getLayout(set);

    if (!layoutHandle)
    {
        return Handle <HwDescriptorSet>();
    }

    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<VulkanDescriptorSet>();
    VulkanDescriptorSetLayout* layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
    VkDescriptorSet vkSet = mDescriptorInfinitePool->obtainSet(layout);
    VulkanDescriptorSet* vulkanDescSet = mResourceAllocator.construct<VulkanDescriptorSet>(dsh, &mResourceAllocator, vkSet, set);
    vulkanDescSet->updateVulkanProgram(vulkanProgram);
    vulkanDescSet->updateName(name);
    return dsh;
}

Handle<HwDescriptorSet> VulkanRenderSystemBase::createDescriptorSet(
    Handle<HwComputeProgram> programHandle,
    uint32_t set)
{
    VulkanComputeProgram* program = mResourceAllocator.handle_cast<VulkanComputeProgram*>(programHandle);
    auto layoutHandle =  program->getSetLayoutHandle(set);

    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<VulkanDescriptorSet>();
    VulkanDescriptorSetLayout* layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
    VkDescriptorSet vkSet = mDescriptorInfinitePool->obtainSet(layout);
    VulkanDescriptorSet* vulkanDescSet = mResourceAllocator.construct<VulkanDescriptorSet>(dsh, &mResourceAllocator, vkSet, set);
    vulkanDescSet->updateVulkanProgram(program);
    return dsh;
}

Handle<HwPipelineLayout> VulkanRenderSystemBase::createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts)
{
    Handle<HwPipelineLayout> plo = mResourceAllocator.allocHandle<VulkanPipelineLayout>();
    uint32_t index = 0;

    VulkanPipelineLayoutCache::PipelineLayoutKey key;
    for (auto& layoutHandle : layouts)
    {
        auto layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
        VkDescriptorSetLayout vkLayout = layout->getVkLayout();
        key.setLayout[index] = vkLayout;
        index++;
    }
    VkPipelineLayout vulkanPipelineLayout = mPipelineLayoutCache->getLayout(key);
    VulkanPipelineLayout* pipeLayout = mResourceAllocator.construct<VulkanPipelineLayout>(plo, vulkanPipelineLayout);
    return plo;
}

Handle<HwProgram> VulkanRenderSystemBase::createShaderProgram(const ShaderInfo& shaderInfo, VertexDeclaration* decl)
{
    Handle<HwProgram> program = mResourceAllocator.allocHandle<VulkanShaderProgram>();
    VulkanShaderProgram* vulkanProgram = mResourceAllocator.construct<VulkanShaderProgram>(program, shaderInfo.shaderName);

    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan, shaderInfo.technique);
    vulkanProgram->updateEntryFunc(
        privateInfo->vertexShaderEntryPoint.c_str(),
        privateInfo->geometryShaderEntryPoint.c_str(),
        privateInfo->fragShaderEntryPoint.c_str());

    auto res = ResourceManager::getSingleton().getResourceInfo(privateInfo->vertexShaderName);

    VulkanShaderInfo vulkanShaderInfo;

    String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
    VkShaderModuleInfo moduleInfo;
    moduleInfo.shaderType = Ogre::VertexShader;
    glslCompileShader(
        res->_fullname,
        *vertexContent,
        privateInfo->vertexShaderEntryPoint,
        shaderInfo.shaderMacros,
        nullptr,
        moduleInfo);

    vulkanShaderInfo.vertexSpv.swap(moduleInfo.spv);
    vulkanShaderInfo.vertexShaderModule = moduleInfo.shaderModule;

    res = ResourceManager::getSingleton().getResourceInfo(privateInfo->geometryShaderName);
    if (res)
    {
        String* content = ShaderManager::getSingleton().getShaderContent(privateInfo->geometryShaderName);
        VkShaderModuleInfo moduleInfo;
        moduleInfo.shaderType = Ogre::GeometryShader;
        glslCompileShader(
            res->_fullname,
            *content,
            privateInfo->geometryShaderEntryPoint,
            shaderInfo.shaderMacros,
            nullptr,
            moduleInfo);

        vulkanShaderInfo.geometrySpv.swap(moduleInfo.spv);
        vulkanShaderInfo.geometryShaderModule = moduleInfo.shaderModule;
    }
    res = ResourceManager::getSingleton().getResourceInfo(privateInfo->fragShaderName);

    if (res)
    {
        String* content = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);
        VkShaderModuleInfo moduleInfo;
        moduleInfo.shaderType = Ogre::PixelShader;

        glslCompileShader(
            res->_fullname,
            *content,
            privateInfo->fragShaderEntryPoint,
            shaderInfo.shaderMacros,
            nullptr,
            moduleInfo);
        
        vulkanShaderInfo.fragSpv.swap(moduleInfo.spv);
        vulkanShaderInfo.fragShaderModule = moduleInfo.shaderModule;
    }
    
    vulkanShaderInfo.resourceAllocator = &mResourceAllocator;
    vulkanShaderInfo.pipelineLayoutCache = mPipelineLayoutCache;
    vulkanShaderInfo.vulkanLayoutCache = mVulkanLayoutCache;

    vulkanProgram->updateShaderInfo(vulkanShaderInfo);
    vulkanProgram->parseVertexInfo(decl);

    return program;
}


Handle<HwSampler> VulkanRenderSystemBase::createTextureSampler(filament::backend::SamplerParams& samplerParams)
{
    Handle<HwSampler> samplerHandle = mResourceAllocator.allocHandle<HwSampler>();

    VulkanTextureSampler* sampler = mResourceAllocator.construct<VulkanTextureSampler>(samplerHandle, samplerParams);

    return samplerHandle;
}

Handle<HwComputeProgram> VulkanRenderSystemBase::createComputeProgram(const ShaderInfo& shaderInfo)
{
    Handle<HwComputeProgram> program = mResourceAllocator.allocHandle<VulkanComputeProgram>();
    VulkanComputeProgram* vulkanProgram = mResourceAllocator.construct<VulkanComputeProgram>(program, shaderInfo.shaderName);


    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);

    auto res = ResourceManager::getSingleton().getResourceInfo(privateInfo->computeShaderName);
    
    assert_invariant(res);

    String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->computeShaderName);
    VkShaderModuleInfo moduleInfo;
    moduleInfo.shaderType = Ogre::ComputeShader;
    glslCompileShader(
        res->_fullname,
        *vertexContent,
        privateInfo->computeShaderEntryPoint,
        shaderInfo.shaderMacros,
        nullptr,
        moduleInfo);

    VulkanComputeShaderInfo vulkanShaderInfo;
    vulkanShaderInfo.computeShaderEntryPoint = privateInfo->computeShaderEntryPoint.c_str();
    vulkanShaderInfo.computeShaderModule = moduleInfo.shaderModule;
    vulkanShaderInfo.computeSpv.swap(moduleInfo.spv);
    vulkanShaderInfo.device = mVulkanPlatform->getDevice();
    vulkanShaderInfo.resourceAllocator = &mResourceAllocator;
    vulkanProgram->upateShaderInfo(vulkanShaderInfo);
    
    return program;
}

Handle<HwPipeline> VulkanRenderSystemBase::createPipeline(
    backend::RasterState& rasterState,
    Handle<HwProgram>& program)
{
    Handle<HwPipeline> pipelineHandle = mResourceAllocator.allocHandle<VulkanPipeline>();
    
    VulkanShaderProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanShaderProgram*>(program);
    VkPipelineLayout pipelineLayout = vulkanProgram->getVulkanPipelineLayout();
    VulkanPipelineCache::RasterState vulkanRasterState;
    vulkanRasterState.cullMode = getCullMode(rasterState.culling);
    vulkanRasterState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    vulkanRasterState.depthBiasEnable = VK_FALSE;


    vulkanRasterState.blendEnable = rasterState.hasBlending();
    
    vulkanRasterState.depthWriteEnable = rasterState.depthWrite;
    vulkanRasterState.depthTestEnable = rasterState.depthTest;

    

    vulkanRasterState.colorWriteMask = 0xf;
    vulkanRasterState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    vulkanRasterState.colorTargetCount = rasterState.renderTargetCount;
    vulkanRasterState.depthCompareOp = VulkanMappings::getCompareFunction(rasterState.depthFunc);
    vulkanRasterState.depthBiasConstantFactor = rasterState.depthBiasConstantFactor;
    vulkanRasterState.depthBiasSlopeFactor = rasterState.depthBiasSlopeFactor;
    vulkanRasterState.depthBiasEnable = rasterState.depthBiasConstantFactor > 0.1f;
    std::vector<VkVertexInputBindingDescription>& vertexInputBindings =
        vulkanProgram->getVertexInputBindings();
    std::vector<VkVertexInputAttributeDescription>& attributeDescriptions =
        vulkanProgram->getAttributeDescriptions();

    VulkanPipelineCache::VulkanTargetInfo targetInfo[8];
    memset(targetInfo, 0, sizeof(VulkanPipelineCache::VulkanTargetInfo) * 8);
    for (uint32_t i = 0; i < rasterState.renderTargetCount; i++)
    {
        PixelFormat format = (PixelFormat)rasterState.pixelFormat[i];
        if (format == PF_UNKNOWN)
        {
            format = mRenderWindow->getColorFormat();
        }

        VkFormat vkFormat = VulkanMappings::_getPF(format);
        targetInfo[i].colorFormat = vkFormat;
        targetInfo[i].blendEnable = vulkanRasterState.blendEnable;
        if (vulkanRasterState.blendEnable)
        {
            targetInfo[i].srcColorBlendFactor = getBlendFactor(rasterState.blendFunctionSrcRGB);
            targetInfo[i].dstColorBlendFactor = getBlendFactor(rasterState.blendFunctionDstRGB);
            targetInfo[i].srcAlphaBlendFactor = getBlendFactor(rasterState.blendFunctionSrcAlpha);
            targetInfo[i].dstAlphaBlendFactor = getBlendFactor(rasterState.blendFunctionDstAlpha);
            targetInfo[i].colorBlendOp = (Ogre::BlendOperation)rasterState.blendEquationRGB;
            targetInfo[i].alphaBlendOp = (Ogre::BlendOperation)rasterState.blendEquationAlpha;
        }
    }
    
    
    
    mPipelineCache->bindTargetInfo(targetInfo, rasterState.renderTargetCount, VK_FORMAT_D32_SFLOAT);
    mPipelineCache->bindProgram(
        vulkanProgram->getVertexShader(), 
        vulkanProgram->getGeometryShader(), 
        vulkanProgram->getFragmentShader());
    mPipelineCache->bindRasterState(vulkanRasterState);
    mPipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    mPipelineCache->bindLayout(pipelineLayout);
    mPipelineCache->bindVertexArray(
        attributeDescriptions.data(),
        attributeDescriptions.size(),
        vertexInputBindings.data(),
        vertexInputBindings.size());
    mPipelineCache->updateEntryFunc(
        vulkanProgram->getVertexShaderFuncName(),
        vulkanProgram->getGeomtryShaderFuncName(),
        vulkanProgram->getFragShaderFuncName());
    VkPipeline pipeline = mPipelineCache->getPipeline();

    VulkanPipeline* vulkanPipeline = mResourceAllocator.construct<VulkanPipeline>(
        pipelineHandle, pipeline, vulkanProgram);
    return pipelineHandle;
}

void VulkanRenderSystemBase::updateDescriptorSet(
    Handle<HwDescriptorSet> dsh,
    uint32_t count,
    const DescriptorData* pParams
)
{
    if (0 == count)
    {
        return;
    }
    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);
    VulkanProgram* vulkanProgram = set->getVulkanProgram();
    VkDescriptorImageInfo imageInfos[MAX_HANDLE_COUNT * 4];
    VkDescriptorImageInfo samplerInfos[MAX_HANDLE_COUNT];
    VkDescriptorBufferInfo bufferInfos[MAX_HANDLE_COUNT];
    VkWriteDescriptorSetAccelerationStructureKHR writeSetKHR = {};
    uint32_t imageCount = 0;
    uint32_t bufferCount = 0;
    uint32_t samplerCount = 0;
    VkWriteDescriptorSet  descriptorWrite[32];
    uint32_t write_index = 0;
    for (uint32_t i = 0; i < count; i++)
    {
        const DescriptorData* pParam = pParams + i;
        const VKDescriptorInfo* descriptroInfo = vulkanProgram->getDescriptor(pParam, set->mSet);
        if (descriptroInfo == nullptr)
        {
            assert_invariant(descriptroInfo);
            continue;
        }
           
        
        const uint32_t       arrayCount = std::max(1U, pParam->mCount);

        
        switch (descriptroInfo->layoutBinding.descriptorType)
        {
        case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
        {
            VulkanAccelerationStructure* as = (VulkanAccelerationStructure*)pParam->pAS;
            writeSetKHR.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
            writeSetKHR.pNext = NULL;
            writeSetKHR.accelerationStructureCount = 1;
            writeSetKHR.pAccelerationStructures = &as->mAccelerationStructure;
            descriptorWrite[write_index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite[write_index].dstSet = set->vkSet;
            descriptorWrite[write_index].dstBinding = descriptroInfo->layoutBinding.binding;
            descriptorWrite[write_index].pNext = &writeSetKHR;
            descriptorWrite[write_index].dstArrayElement = 0;
            descriptorWrite[write_index].descriptorCount = 1;
            descriptorWrite[write_index].descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
            write_index++;
        }
        break;
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
        {
            VkDescriptorType type = descriptroInfo->layoutBinding.descriptorType;
            VkImageLayout layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            if (type == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
            {
                layout = VK_IMAGE_LAYOUT_GENERAL;
            }
            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                uint32_t index = arr + imageCount;
                imageInfos[index].imageLayout = layout;
                VulkanTexture* vulkanTexture = (VulkanTexture*)pParam->ppTextures[arr];
                if (nullptr == vulkanTexture)
                {
                    imageInfos[index].imageView = VK_NULL_HANDLE;
                    imageInfos[index].sampler = VK_NULL_HANDLE;
                }
                else
                {
                    imageInfos[index].imageView = vulkanTexture->getVkImageView();
                    if (type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                    {
                        imageInfos[index].sampler = vulkanTexture->getSampler();
                    }
                }
                
            }
            descriptorWrite[write_index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite[write_index].pNext = nullptr;
            descriptorWrite[write_index].dstSet = set->vkSet;
            descriptorWrite[write_index].dstBinding = descriptroInfo->layoutBinding.binding;
            descriptorWrite[write_index].descriptorCount = arrayCount;
            descriptorWrite[write_index].descriptorType = type;
            descriptorWrite[write_index].dstArrayElement = 0;
            descriptorWrite[write_index].pImageInfo = &imageInfos[imageCount];
            write_index++;
            imageCount += arrayCount;
        }

        break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
        {
            VkDescriptorType type = descriptroInfo->layoutBinding.descriptorType;

            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                uint32_t index = arr + bufferCount;
                if (pParam->descriptorType == DESCRIPTOR_TYPE_BUFFER_VIEW)
                {
                    VulkanBufferObject* vbo = mResourceAllocator.handle_cast<VulkanBufferObject*>(pParam->pBufferView[arr].buffer);
                    bufferInfos[index].offset = pParam->pBufferView[arr].offset;

                    if (bufferInfos[index].offset == 80)
                    {
                        int kk = 0;
                    }
                    bufferInfos[index].range = VK_WHOLE_SIZE;
                    bufferInfos[index].buffer = vbo->buffer.getGpuBuffer();
                }
                else
                {
                    VulkanBufferObject* vbo = mResourceAllocator.handle_cast<VulkanBufferObject*>(pParam->ppBuffers[arr]);
                    bufferInfos[index].offset = 0;
                    bufferInfos[index].range = VK_WHOLE_SIZE;
                    bufferInfos[index].buffer = vbo->buffer.getGpuBuffer();
                }
                
            }

            descriptorWrite[write_index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite[write_index].pNext = nullptr;
            descriptorWrite[write_index].dstSet = set->vkSet;
            descriptorWrite[write_index].dstBinding = descriptroInfo->layoutBinding.binding;
            descriptorWrite[write_index].descriptorCount = arrayCount;
            descriptorWrite[write_index].descriptorType = type;
            descriptorWrite[write_index].dstArrayElement = 0;
            descriptorWrite[write_index].pBufferInfo = &bufferInfos[bufferCount];
            write_index++;
            bufferCount += arrayCount;
        }
        break;
        
        case VK_DESCRIPTOR_TYPE_SAMPLER:
        {
            VkDescriptorType type = descriptroInfo->layoutBinding.descriptorType;
            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                uint32_t index = arr + samplerCount;

                VkSampler sampler = VK_NULL_HANDLE;

                if (pParam->descriptorType == DESCRIPTOR_TYPE_SAMPLER)
                {
                    auto sh = pParam->ppSamplers[arr];
                    VulkanTextureSampler* vulkanSampler =
                        mResourceAllocator.handle_cast<VulkanTextureSampler*>(sh);
                    sampler = vulkanSampler->getSampler();
                }
                else
                {
                    VulkanTexture* vulkanTexture = (VulkanTexture*)pParam->ppTextures[arr];

                    sampler = vulkanTexture->getSampler();

                    if (sampler == nullptr)
                    {
                        int kk = 0;
                    }
                }
                

                samplerInfos[index].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                samplerInfos[index].imageView = VK_NULL_HANDLE;
                samplerInfos[index].sampler = sampler;
            }
            descriptorWrite[write_index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite[write_index].pNext = nullptr;
            descriptorWrite[write_index].dstSet = set->vkSet;
            descriptorWrite[write_index].dstBinding = descriptroInfo->layoutBinding.binding;
            descriptorWrite[write_index].descriptorCount = arrayCount;
            descriptorWrite[write_index].descriptorType = type;
            descriptorWrite[write_index].dstArrayElement = 0;
            descriptorWrite[write_index].pImageInfo = &samplerInfos[samplerCount];
            write_index++;
            samplerCount += arrayCount;
        }
        break;
        default:
            assert_invariant(false);
         break;
        }
    }

    bluevk::vkUpdateDescriptorSets(
        mVulkanPlatform->getDevice(),
        write_index,
        descriptorWrite, 0, nullptr);
    
}

void VulkanRenderSystemBase::resourceBarrier(
    uint32_t numBufferBarriers,
    BufferBarrier* pBufferBarriers,
    uint32_t numTextureBarriers,
    TextureBarrier* pTextureBarriers,
    uint32_t numRtBarriers,
    RenderTargetBarrier* pRtBarriers,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* dsh,
    QueueType queueType
)
{
    VkCommandBuffer cmdBuffer;
    if (dsh)
    {

        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(*dsh);
        cmdBuffer = cb->commandBuffer;
    }
    else
    {
        cmdBuffer = mCommands->get().buffer();
    }
    
    vks::tools::resourceBarrier(
        numBufferBarriers, pBufferBarriers,
        numTextureBarriers, pTextureBarriers,
        numRtBarriers, pRtBarriers,
        queueType,
        mVulkanPlatform->getGraphicsQueueFamilyIndex(),
        cmdBuffer
    );
}



void VulkanRenderSystemBase::beginDefaultCommandList()
{
    mCommandBuffer = mCommands->get().buffer();
}

void VulkanRenderSystemBase::flushDefaultCommandList(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    bool waitCmd)
{
    mCommands->flush(waitCmd);
    mCommandBuffer = nullptr;
}

void VulkanRenderSystemBase::flushCmd(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    bool waitCmd)
{
    VulkanCommandQueue* queue = mResourceAllocator.handle_cast<VulkanCommandQueue*>(cqh);

    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    VkCommandBuffer cl = cb->commandBuffer;
    VulkanFence* fence = mResourceAllocator.handle_cast<VulkanFence*>(mFlushFence);
    vkResetFences(mVulkanPlatform->getDevice(), 1, &fence->vkFence);
    VkPipelineStageFlags waitDestStageMasks[2] = {
                VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
    };
    VkSubmitInfo submitInfo{
                .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                .waitSemaphoreCount = 0,
                .pWaitSemaphores = nullptr,
                .pWaitDstStageMask = waitDestStageMasks,
                .commandBufferCount = 1,
                .pCommandBuffers = &cl,
                .signalSemaphoreCount = 0,
                .pSignalSemaphores = nullptr,
    };

    VkResult result = vkQueueSubmit(queue->vkQueue, 1, &submitInfo, fence->vkFence);

    if (waitCmd)
    {
        VkFence currentFence = fence->vkFence;
        VkResult result = vkWaitForFences(mVulkanPlatform->getDevice(), 1, &currentFence, VK_TRUE, UINT64_MAX);
        assert_invariant(result == VK_SUCCESS);
    }
}

void VulkanRenderSystemBase::destroyBufferObject(Handle<HwBufferObject> bufHandle)
{
    VulkanBufferObject* bo = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);

    mResourceAllocator.destruct<VulkanBufferObject>(bufHandle);
}

uint32_t VulkanRenderSystemBase::getAlignmentSize(BufferObjectBinding bufferType)
{
    //todo
    switch (bufferType)
    {
    case BufferObjectBinding_Uniform:
        return 256;
        break;
    case BufferObjectBinding_Storge:
        return 16;
    default:
        assert_invariant(false);
        break;
    }
    return 16;
}

Handle<HwFence> VulkanRenderSystemBase::createFence(bool signaled)
{
    Handle<HwFence> fh = mResourceAllocator.allocHandle<VulkanFence>();

    VulkanFence* fence = mResourceAllocator.construct<VulkanFence>(fh, mVulkanPlatform->getDevice(), signaled);

    return fh;
}

void VulkanRenderSystemBase::waitFence(Handle<HwFence> fh)
{
    VulkanFence* fence = mResourceAllocator.handle_cast<VulkanFence*>(fh);
    auto device = mVulkanPlatform->getDevice();
    auto vkFence = fence->vkFence;
    
    VkResult err = vkWaitForFences(device, 1, &vkFence, VK_TRUE, UINT64_MAX);
    assert_invariant(err == VK_SUCCESS);
    

    err = vkResetFences(device, 1, &vkFence);
    assert_invariant(err == VK_SUCCESS);
}

Handle<HwSemaphore> VulkanRenderSystemBase::createSemaphore()
{
    Handle<HwSemaphore> sh = mResourceAllocator.allocHandle<HwSemaphore>();

    VulkanSemaphore* semaphore = mResourceAllocator.construct<VulkanSemaphore>(sh, mVulkanPlatform->getDevice());

    return sh;
}

Handle<HwCommandBuffer> VulkanRenderSystemBase::createCommandBuffer(Ogre::QueueType type)
{
    Handle<HwCommandBuffer> cbh = mResourceAllocator.allocHandle<HwCommandBuffer>();
    uint32_t familyIndex = 0;
    switch (type)
    {
    case QueueType::QUEUE_TYPE_GRAPHICS:
        familyIndex = mVulkanPlatform->getGraphicsQueueFamilyIndex();
        break;
    case QueueType::QUEUE_TYPE_TRANSFER:
        familyIndex = mVulkanPlatform->getTransferQueueFamilyIndex();
        break;
    default:
        assert_invariant(false);
    }
    
    VulkanCommandBuffer2* cb = mResourceAllocator.construct<VulkanCommandBuffer2>(
        cbh, &mResourceAllocator, mVulkanPlatform->getDevice(), familyIndex);

    return cbh;
}

void VulkanRenderSystemBase::beginCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);

    const VkCommandBufferBeginInfo binfo{
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    
    vkBeginCommandBuffer(cb->commandBuffer, &binfo);
}

void VulkanRenderSystemBase::endCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    vkEndCommandBuffer(cb->commandBuffer);
}

void VulkanRenderSystemBase::clearCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    //vkClearCommandBuffer(cb->commandBuffer);
}

Handle<HwCommandQueue> VulkanRenderSystemBase::createCommandQueue(Ogre::QueueType type, uint32_t queueIndex)
{
    Handle<HwCommandQueue> cqh = mResourceAllocator.allocHandle<HwCommandQueue>();

    VkQueue queue = VK_NULL_HANDLE;

    if (type == QUEUE_TYPE_GRAPHICS)
    {
        queue = mVulkanPlatform->getGraphicsQueue();
    }
    else if (type == QUEUE_TYPE_TRANSFER)
    {
        queue = mVulkanPlatform->getTransferQueue(queueIndex + 1);
    }
    else
    {
        assert_invariant(false);
    }

    VulkanCommandQueue* cq = mResourceAllocator.construct<VulkanCommandQueue>(
        cqh, queue);
    return cqh;
}

Handle<HwSwapChain> VulkanRenderSystemBase::createSwapChain(Ogre::RenderWindow* renderWindow)
{
    VulkanWindow* vulkanWindow = (VulkanWindow*)renderWindow;
    Handle<HwSwapChain> sch = mResourceAllocator.allocHandle<VulkanSwapChain>();
    void* wnd = (void*)vulkanWindow->getWndHandle();
    VkExtent2D extent;
    extent.width = 0;
    extent.height = 0;

    uint32_t flags = vulkanWindow->getFlags();


    VulkanSwapChain* swapChain = mResourceAllocator.construct<VulkanSwapChain>(
        sch, mVulkanPlatform, mVulkanContext, mAllocator, mCommands,
        &mResourceAllocator, *mStagePool, wnd, flags, extent);

    vulkanWindow->create(swapChain);

    return sch;
}

void VulkanRenderSystemBase::swapChainAcquire(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    filament::backend::Handle<filament::backend::HwSwapChain> sch,
    SwapChainInfo& scInfo)
{
    VulkanCommandQueue* queue = mResourceAllocator.handle_cast<VulkanCommandQueue*>(cqh);
    VulkanSwapChain* swapChain = mResourceAllocator.handle_cast<VulkanSwapChain*>(sch);
    VulkanPlatform::ImageSyncData imageSyncData;
    swapChain->acquire(imageSyncData);
    scInfo.imageIndex = imageSyncData.imageIndex;
    assert_invariant(scInfo.imageIndex < 3);
    scInfo.color = swapChain->getCurrentColor();
    scInfo.depth = swapChain->getDepth();
    queue->imageIndex = imageSyncData.imageIndex;
    queue->imageReadySemaphore = imageSyncData.imageReadySemaphore;
}

void VulkanRenderSystemBase::swapChainResize(
    Handle<HwCommandQueue> cqh,
    Handle<HwSwapChain> sch)
{
    VulkanCommandQueue* queue = mResourceAllocator.handle_cast<VulkanCommandQueue*>(cqh);
    VulkanSwapChain* swapChain = mResourceAllocator.handle_cast<VulkanSwapChain*>(sch);
}

Handle<HwShader> VulkanRenderSystemBase::createShader(Ogre::ShaderDesc& desc)
{
    if (desc.name == "SceneForwardClusteredShaderRD:0")
    {
        int kk = 0;
    }
    Handle<HwShader> sh = mResourceAllocator.allocHandle<HwShader>();

    VulkanShader* cq = mResourceAllocator.construct<VulkanShader>(sh);
    auto device = mVulkanPlatform->getDevice();
    if (desc.computeBin.empty())
    {
        VulkanShaderProgram* shaderProgram = new VulkanShaderProgram(desc.name);
        cq->shaderProgram = shaderProgram;
        
        VulkanShaderInfo shaderInfo;
        shaderInfo.vertexShaderModule = vks::tools::loadShaderMemory(desc.vertexBin, device);
        shaderInfo.vertexSpv = desc.vertexBin;

        shaderInfo.fragShaderModule = vks::tools::loadShaderMemory(desc.fragBin, device);
        shaderInfo.fragSpv = desc.fragBin;
        
        shaderInfo.resourceAllocator = &mResourceAllocator;
        shaderInfo.pipelineLayoutCache = mPipelineLayoutCache;
        shaderInfo.vulkanLayoutCache = mVulkanLayoutCache;
        shaderInfo.decl = desc.decl;
        shaderProgram->updateShaderInfo(shaderInfo);
    }
    else
    {
        VulkanComputeProgram* computeProgram = new VulkanComputeProgram(desc.name);
        cq->computeProgram = computeProgram;

        VulkanComputeShaderInfo shaderInfo;
        shaderInfo.computeShaderEntryPoint = "main";
        shaderInfo.computeShaderModule = vks::tools::loadShaderMemory(desc.computeBin, device);
        shaderInfo.computeSpv = desc.computeBin;
        shaderInfo.device = device;
        shaderInfo.resourceAllocator = &mResourceAllocator;
        computeProgram->upateShaderInfo(shaderInfo);
    }
    return sh;
}

Handle<HwPipeline> VulkanRenderSystemBase::createPipeline(
    Ogre::PipelineCreateInfo& pipelineCreateInfo,
    Handle<HwShader>& shader
)
{
    Handle<HwPipeline> ph = mResourceAllocator.allocHandle<HwPipeline>();
    VulkanShader* vulkanShader = mResourceAllocator.handle_cast<VulkanShader*>(shader);

    VulkanShaderProgram* vulkanProgram = vulkanShader->shaderProgram;
    VkPipelineLayout pipelineLayout = vulkanProgram->getVulkanPipelineLayout();
    VulkanPipelineCache::RasterState vulkanRasterState;
    
    RasterizationStateInfo& rasterizationState = pipelineCreateInfo.rasterizationState;
    DepthStencilStateInfo& depthStencilState = pipelineCreateInfo.depthStencilState;
    ColorBlendStateInfo& colorBlendState = pipelineCreateInfo.colorBlendState;
    RenderTargetInfo& renderTarget = pipelineCreateInfo.renderTarget;
    //depth
    vulkanRasterState.depthBiasEnable = rasterizationState.depthBiasEnable;
    vulkanRasterState.depthWriteEnable = depthStencilState.depthWriteEnable;
    vulkanRasterState.depthTestEnable = depthStencilState.depthTestEnable;
    vulkanRasterState.depthCompareOp = depthStencilState.depthCompareOp;
    vulkanRasterState.depthBiasConstantFactor = rasterizationState.depthBiasConstantFactor;
    vulkanRasterState.depthBiasSlopeFactor = rasterizationState.depthBiasSlopeFactor;

    //blend
 
   
    VulkanPipelineCache::VulkanTargetInfo targetInfo[8];
    memset(targetInfo, 0, sizeof(VulkanPipelineCache::VulkanTargetInfo) * 8);

    for (uint32_t i = 0; i < renderTarget.renderTargetCount; i++)
    {
        PixelFormat format = (PixelFormat)renderTarget.pixelFormat[i];
        if (format == PF_UNKNOWN)
        {
            format = mRenderWindow->getColorFormat();
        }

        VkFormat vkFormat = VulkanMappings::_getPF(format);
        if (vkFormat == VK_FORMAT_UNDEFINED)
        {
            int kk = 0;
        }
        targetInfo[i].colorFormat = vkFormat;
        targetInfo[i].blendEnable = colorBlendState.attachments[i].enable_blend;
        if (targetInfo[i].blendEnable)
        {
            targetInfo[i].srcColorBlendFactor = VulkanMappings::getBlendFactor(colorBlendState.attachments[i].blendFunctionSrcRGB);
            targetInfo[i].dstColorBlendFactor = VulkanMappings::getBlendFactor(colorBlendState.attachments[i].blendFunctionDstRGB);
            targetInfo[i].srcAlphaBlendFactor = VulkanMappings::getBlendFactor(colorBlendState.attachments[i].blendFunctionSrcAlpha);
            targetInfo[i].dstAlphaBlendFactor = VulkanMappings::getBlendFactor(colorBlendState.attachments[i].blendFunctionDstAlpha);
            targetInfo[i].colorBlendOp = (Ogre::BlendOperation)colorBlendState.attachments[i].blendEquationRGB;
            targetInfo[i].alphaBlendOp = (Ogre::BlendOperation)colorBlendState.attachments[i].blendEquationAlpha;
        }
    }
    mPipelineCache->bindTargetInfo(targetInfo, renderTarget.renderTargetCount, VK_FORMAT_D32_SFLOAT);
    
    
    vulkanRasterState.cullMode = VulkanMappings::getCullMode(pipelineCreateInfo.rasterizationState.cullMode);
    vulkanRasterState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    vulkanRasterState.colorWriteMask = 0xf;
    vulkanRasterState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    vulkanRasterState.colorTargetCount = renderTarget.renderTargetCount;
    
    vulkanProgram->parseVertexInfo(pipelineCreateInfo.decl);

    std::vector<VkVertexInputBindingDescription>& vertexInputBindings =
        vulkanProgram->getVertexInputBindings();
    std::vector<VkVertexInputAttributeDescription>& attributeDescriptions =
        vulkanProgram->getAttributeDescriptions();

    mPipelineCache->bindProgram(
        vulkanProgram->getVertexShader(),
        vulkanProgram->getGeometryShader(),
        vulkanProgram->getFragmentShader());
    mPipelineCache->bindRasterState(vulkanRasterState);
    mPipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    mPipelineCache->bindLayout(pipelineLayout);
    mPipelineCache->bindVertexArray(
        attributeDescriptions.data(),
        attributeDescriptions.size(),
        vertexInputBindings.data(),
        vertexInputBindings.size());
    mPipelineCache->updateEntryFunc(
        vulkanProgram->getVertexShaderFuncName(),
        vulkanProgram->getGeomtryShaderFuncName(),
        vulkanProgram->getFragShaderFuncName());
    VkPipeline pipeline = mPipelineCache->getPipeline();

    VulkanPipeline* vulkanPipeline = mResourceAllocator.construct<VulkanPipeline>(
        ph, pipeline, vulkanProgram);
    return ph;
}

filament::backend::Handle<filament::backend::HwPipeline> VulkanRenderSystemBase::createComputePipeline(
    filament::backend::Handle<filament::backend::HwShader>& shader
)
{
    Handle<HwPipeline> ph = mResourceAllocator.allocHandle<HwPipeline>();
    VulkanShader* vulkanShader = mResourceAllocator.handle_cast<VulkanShader*>(shader);
    VulkanComputeProgram* computeProgram = vulkanShader->computeProgram;
    VkPipeline pipeline = computeProgram->getPipeline();
    VulkanPipeline* vulkanPipeline = mResourceAllocator.construct<VulkanPipeline>(
        ph, pipeline, computeProgram);
    return ph;
}
Handle<HwDescriptorSet> VulkanRenderSystemBase::createDescriptorSet(
    Handle<HwShader> programHandle,
    uint32_t set)
{
    VulkanShader* shader = mResourceAllocator.handle_cast<VulkanShader*>(programHandle);

    if (shader->shaderProgram)
    {
        VulkanShaderProgram* vulkanProgram = shader->shaderProgram;
        const char* name = vulkanProgram->name.c_str();

        Handle<HwDescriptorSetLayout> layoutHandle = vulkanProgram->getLayout(set);

        if (!layoutHandle)
        {
            return Handle <HwDescriptorSet>();
        }

        Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<VulkanDescriptorSet>();
        VulkanDescriptorSetLayout* layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
        VkDescriptorSet vkSet = mDescriptorInfinitePool->obtainSet(layout);
        VulkanDescriptorSet* vulkanDescSet = mResourceAllocator.construct<VulkanDescriptorSet>(dsh, &mResourceAllocator, vkSet, set);
        vulkanDescSet->updateVulkanProgram(vulkanProgram);
        vulkanDescSet->updateName(name);
        return dsh;
    }
    else
    {
        VulkanComputeProgram* program = shader->computeProgram;
        auto layoutHandle = program->getSetLayoutHandle(set);

        Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<VulkanDescriptorSet>();
        VulkanDescriptorSetLayout* layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
        VkDescriptorSet vkSet = mDescriptorInfinitePool->obtainSet(layout);
        VulkanDescriptorSet* vulkanDescSet = mResourceAllocator.construct<VulkanDescriptorSet>(dsh, &mResourceAllocator, vkSet, set);
        vulkanDescSet->updateVulkanProgram(program);
        return dsh;
    }
}

void VulkanRenderSystemBase::executeAndPresent(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    filament::backend::Handle<filament::backend::HwSemaphore>* wait_sph,
    uint32_t wait_sp_size,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh,
    uint32_t cb_size,
    filament::backend::Handle<filament::backend::HwSemaphore>* cmd_sph,
    uint32_t cmd_sp_size,
    filament::backend::Handle<filament::backend::HwFence> fh,
    filament::backend::Handle<filament::backend::HwSwapChain>* sch,
    uint32_t sc_size
)
{
    VulkanCommandQueue* queue = mResourceAllocator.handle_cast<VulkanCommandQueue*>(cqh);
    VulkanFence* fence = mResourceAllocator.handle_cast<VulkanFence*>(fh);
    VkPipelineStageFlags waitDestStageMasks[2] = {
                VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
    };
    std::vector<VkSemaphore> wait_semaphores;
    wait_semaphores.reserve(wait_sp_size+1);

    for (uint32_t i = 0; i < wait_sp_size; i++)
    {
        VulkanSemaphore* semaphore = mResourceAllocator.handle_cast<VulkanSemaphore*>(wait_sph[i]);
        wait_semaphores.push_back(semaphore->semaphore);
    }

    if (queue->imageReadySemaphore)
    {
        wait_semaphores.push_back(queue->imageReadySemaphore);
    }

    std::vector<VkCommandBuffer> command_buffers;
    command_buffers.resize(cb_size);

    if (cb_size == 0)
    {
        int kk = 0;
    }
    for (uint32_t i = 0; i < cb_size; i++)
    {
        VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh[i]);
        command_buffers[i] = cb->commandBuffer;
    }
    std::vector<VkSemaphore> signal_semaphores;
    signal_semaphores.reserve(cmd_sp_size + 1);
    
    for (uint32_t i = 0; i < cmd_sp_size; i++)
    {
        VulkanSemaphore* semaphore = mResourceAllocator.handle_cast<VulkanSemaphore*>(cmd_sph[i]);
        signal_semaphores.push_back(semaphore->semaphore);
    }

    VkSemaphore finished = VK_NULL_HANDLE;
    if (sc_size)
    {
        finished = queue->getSemaphore();
        signal_semaphores.push_back(finished);
        queue->updateIndex();
    }
    
    VkSubmitInfo submitInfo{
                .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                .waitSemaphoreCount = (uint32_t)wait_semaphores.size(),
                .pWaitSemaphores = wait_semaphores.data(),
                .pWaitDstStageMask = waitDestStageMasks,
                .commandBufferCount = cb_size,
                .pCommandBuffers = command_buffers.data(),
                .signalSemaphoreCount = (uint32_t)signal_semaphores.size(),
                .pSignalSemaphores = signal_semaphores.data(),
    };

    auto vkFence = fence->vkFence;

    VkResult result = vkQueueSubmit(queue->vkQueue, 1, &submitInfo, vkFence);
    assert_invariant(result == VK_SUCCESS);

    if (sc_size)
    {
        VulkanSwapChain* swapChain = mResourceAllocator.handle_cast<VulkanSwapChain*>(*sch);
        VulkanPlatformSurfaceSwapChain* impl = (VulkanPlatformSurfaceSwapChain*)swapChain->swapChain;
        VkSwapchainKHR vulkanSwapChain = impl->getSwapChain();
        uint32_t currentIndex = queue->imageIndex;
        VkSemaphore finishedDrawing = finished;
        VkPresentInfoKHR presentInfo{
                .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                .waitSemaphoreCount = (uint32_t)signal_semaphores.size(),
                .pWaitSemaphores = signal_semaphores.data(),
                .swapchainCount = 1,
                .pSwapchains = &vulkanSwapChain,
                .pImageIndices = &currentIndex,
        };
        VkResult result = vkQueuePresentKHR(queue->vkQueue, &presentInfo);
        assert_invariant(result == VK_SUCCESS);
        swapChain->update(false);
    }
    
}

void VulkanRenderSystemBase::updatePushConstants(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwShader> sh,
    uint32_t offset,
    const char* data,
    uint32_t size)
{
   
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);

    VulkanShader* shader = mResourceAllocator.handle_cast<VulkanShader*>(sh);
    VkPipelineLayout layout;
    if (shader->shaderProgram)
    {
        layout = shader->shaderProgram->getVulkanPipelineLayout();
        vkCmdPushConstants(
            cb->commandBuffer,
            layout,
            VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT,
            offset, size, data);
    }
    else
    {
        layout = shader->computeProgram->getPipelineLayout();
        vkCmdPushConstants(
            cb->commandBuffer,
            layout,
            VK_SHADER_STAGE_COMPUTE_BIT,
            offset, size, data);
    }

    
}


void VulkanRenderSystemBase::bindVertexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    uint32_t binding_count,
    const filament::backend::Handle<filament::backend::HwBufferObject>* bufHandle,
    const uint64_t* p_offsets)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);

    VkBuffer buffers[16];
    assert_invariant(binding_count <= 16);

    for (uint32_t i = 0; i < binding_count; i++)
    {
        VulkanBufferObject* vb = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle[i]);
        buffers[i] = vb->buffer.getGpuBuffer();
    }
    if (p_offsets)
    {
        vkCmdBindVertexBuffers(cb->commandBuffer, 0, binding_count, buffers, p_offsets);
    }
    else
    {
        VkDeviceSize offsets[10] = { 0 };
        vkCmdBindVertexBuffers(cb->commandBuffer, 0, binding_count, buffers, offsets);
    }
}

void VulkanRenderSystemBase::bindIndexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
    uint32_t indexSize,
    uint32_t offset)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    VulkanBufferObject* vb = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);

    vkCmdBindIndexBuffer(cb->commandBuffer, vb->buffer.getGpuBuffer(), offset, indexSize == 2 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32);
}

void VulkanRenderSystemBase::bindPipeline(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwPipeline> ph)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    VulkanPipeline* pipeline = mResourceAllocator.handle_cast<VulkanPipeline*>(ph);
    auto bindPoint = pipeline->getProgram()->getPipelineBindPoint();
    vkCmdBindPipeline(cb->commandBuffer, bindPoint, pipeline->getPipeline());
}

void VulkanRenderSystemBase::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwShader> sh,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    VulkanShader* shader = mResourceAllocator.handle_cast<VulkanShader*>(sh);

    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);
    if (shader->shaderProgram)
    {
        auto pipelineLayout = shader->shaderProgram->getVulkanPipelineLayout();
        vkCmdBindDescriptorSets(cb->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
            pipelineLayout, set->mSet, 1, &set->vkSet, 0, nullptr);
    }
    else
    {
        auto pipelineLayout = shader->computeProgram->getPipelineLayout();
        vkCmdBindDescriptorSets(cb->commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
            pipelineLayout, set->mSet, 1, &set->vkSet, 0, nullptr);
    }
}


void VulkanRenderSystemBase::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwProgram> ph,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    VulkanCommandBuffer2* cb = mResourceAllocator.handle_cast<VulkanCommandBuffer2*>(cbh);
    VulkanShaderProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanShaderProgram*>(ph);

    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);

    auto pipelineLayout = vulkanProgram->getVulkanPipelineLayout();
    vkCmdBindDescriptorSets(cb->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout, set->mSet, 1, &set->vkSet, 0, nullptr);
}

uint64_t VulkanRenderSystemBase::limit_get(Ogre::Limit limit)
{
    const VkPhysicalDeviceLimits& limits = physical_device_properties.limits;
    switch (limit) {
    case LIMIT_MAX_BOUND_UNIFORM_SETS:
        return limits.maxBoundDescriptorSets;
    case LIMIT_MAX_FRAMEBUFFER_COLOR_ATTACHMENTS:
        return limits.maxColorAttachments;
    case LIMIT_MAX_TEXTURES_PER_UNIFORM_SET:
        return limits.maxDescriptorSetSampledImages;
    case LIMIT_MAX_SAMPLERS_PER_UNIFORM_SET:
        return limits.maxDescriptorSetSamplers;
    case LIMIT_MAX_STORAGE_BUFFERS_PER_UNIFORM_SET:
        return limits.maxDescriptorSetStorageBuffers;
    case LIMIT_MAX_STORAGE_IMAGES_PER_UNIFORM_SET:
        return limits.maxDescriptorSetStorageImages;
    case LIMIT_MAX_UNIFORM_BUFFERS_PER_UNIFORM_SET:
        return limits.maxDescriptorSetUniformBuffers;
    case LIMIT_MAX_DRAW_INDEXED_INDEX:
        return limits.maxDrawIndexedIndexValue;
    case LIMIT_MAX_FRAMEBUFFER_HEIGHT:
        return limits.maxFramebufferHeight;
    case LIMIT_MAX_FRAMEBUFFER_WIDTH:
        return limits.maxFramebufferWidth;
    case LIMIT_MAX_TEXTURE_ARRAY_LAYERS:
        return limits.maxImageArrayLayers;
    case LIMIT_MAX_TEXTURE_SIZE_1D:
        return limits.maxImageDimension1D;
    case LIMIT_MAX_TEXTURE_SIZE_2D:
        return limits.maxImageDimension2D;
    case LIMIT_MAX_TEXTURE_SIZE_3D:
        return limits.maxImageDimension3D;
    case LIMIT_MAX_TEXTURE_SIZE_CUBE:
        return limits.maxImageDimensionCube;
    case LIMIT_MAX_TEXTURES_PER_SHADER_STAGE:
        return limits.maxPerStageDescriptorSampledImages;
    case LIMIT_MAX_SAMPLERS_PER_SHADER_STAGE:
        return limits.maxPerStageDescriptorSamplers;
    case LIMIT_MAX_STORAGE_BUFFERS_PER_SHADER_STAGE:
        return limits.maxPerStageDescriptorStorageBuffers;
    case LIMIT_MAX_STORAGE_IMAGES_PER_SHADER_STAGE:
        return limits.maxPerStageDescriptorStorageImages;
    case LIMIT_MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE:
        return limits.maxPerStageDescriptorUniformBuffers;
    case LIMIT_MAX_PUSH_CONSTANT_SIZE:
        return limits.maxPushConstantsSize;
    case LIMIT_MAX_UNIFORM_BUFFER_SIZE:
        return limits.maxUniformBufferRange;
    case LIMIT_MAX_VERTEX_INPUT_ATTRIBUTE_OFFSET:
        return limits.maxVertexInputAttributeOffset;
    case LIMIT_MAX_VERTEX_INPUT_ATTRIBUTES:
        return limits.maxVertexInputAttributes;
    case LIMIT_MAX_VERTEX_INPUT_BINDINGS:
        return limits.maxVertexInputBindings;
    case LIMIT_MAX_VERTEX_INPUT_BINDING_STRIDE:
        return limits.maxVertexInputBindingStride;
    case LIMIT_MIN_UNIFORM_BUFFER_OFFSET_ALIGNMENT:
        return limits.minUniformBufferOffsetAlignment;
    case LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_X:
        return limits.maxComputeWorkGroupCount[0];
    case LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_Y:
        return limits.maxComputeWorkGroupCount[1];
    case LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_Z:
        return limits.maxComputeWorkGroupCount[2];
    case LIMIT_MAX_COMPUTE_WORKGROUP_INVOCATIONS:
        return limits.maxComputeWorkGroupInvocations;
    case LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_X:
        return limits.maxComputeWorkGroupSize[0];
    case LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_Y:
        return limits.maxComputeWorkGroupSize[1];
    case LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_Z:
        return limits.maxComputeWorkGroupSize[2];
    case LIMIT_MAX_VIEWPORT_DIMENSIONS_X:
        return limits.maxViewportDimensions[0];
    case LIMIT_MAX_VIEWPORT_DIMENSIONS_Y:
        return limits.maxViewportDimensions[1];
    case LIMIT_SUBGROUP_SIZE:
        return subgroup_capabilities.size;
    case LIMIT_SUBGROUP_MIN_SIZE:
        return subgroup_capabilities.min_size;
    case LIMIT_SUBGROUP_MAX_SIZE:
        return subgroup_capabilities.max_size;
    default:
        assert_invariant(false);
        return 0;
    }
}

RenderSystem::TransferContext* VulkanRenderSystemBase::getTransferContext()
{
    uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
    return &mTransferContext[frameIndex];
}

void VulkanRenderSystemBase::bingingUpdate(
    vks::tools::BingdingInfo& bindingMap,
    vks::tools::BingdingInfo& results,
    VkShaderStageFlagBits flagBits)
{
    auto findLayout = [](
        std::vector<VKDescriptorInfo>& bindingList,
        VKDescriptorInfo binding)
        {
            for (auto i = 0; i < bindingList.size(); i++)
            {
                if (bindingList.at(i).layoutBinding.binding == binding.layoutBinding.binding)
                {
                    return i;
                }
            }
            return -1;
        };
    for (auto& pair : results)
    {
        auto& bingdingList = bindingMap[pair.first];
        for (auto& layoutBingding : pair.second)
        {
            auto i = findLayout(bingdingList, layoutBingding);
            if (i >= 0)
            {
                bingdingList[i].layoutBinding.stageFlags |= flagBits;
            }
            else
            {
                bingdingList.push_back(layoutBingding);
            }
        }
    }
}