#include "OgreHeader.h"
#include "VulkanRenderSystem.h"
#include "VulkanTexture.h"
#include "OgreRenderable.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "VulkanRenderData.h"
#include "OgreMaterial.h"
#include "OgreHardwareIndexBuffer.h"
#include "VulkanHardwareBufferManager.h"
#include "OgreCamera.h"
#include "VulkanTools.h"
#include "VulkanObjectPool.h"
#include "VulkanHelper.h"
#include "VulkanFrame.h"
#include "VulkanWindow.h"
#include "OgreViewport.h"
#include "OgreTextureManager.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreNode.h"
#include "OgreMath.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreMeshManager.h"
#include "OgreResourceManager.h"
#include "VulkanRenderTarget.h"
#include "VulkanMappings.h"
#include <VulkanPipelineCache.h>

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

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

VulkanRenderSystem::VulkanRenderSystem(HWND wnd)
{
    bluevk::initialize();

    mRenderSystemName = "Vulkan";
    mRenderType = EngineType_Vulkan;
    new VulkanHelper(this);

    mRenderList.reserve(3000);
    
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    RenderSystem::engineInit();
    mVulkanPlatform = new VulkanPlatform();
    

    VulkanHelper& helper = VulkanHelper::getSingleton();
    helper._initialise(mVulkanPlatform);
   
    auto device = mVulkanPlatform->getDevice();
    mAllocator = createAllocator(
        mVulkanPlatform->getInstance(), mVulkanPlatform->getPhysicalDevice(), device);

    
    auto queue = mVulkanPlatform->getGraphicsQueue();
    auto queueIndex = mVulkanPlatform->getGraphicsQueueIndex();

    mCommands = new VulkanCommands(device, queue, queueIndex, &mVulkanContext, &mResourceAllocator);

    
    mPipelineCache = helper.getPipelineCache();

    return true;
}


void VulkanRenderSystem::frameStart()
{ 
    mTriangleCount = 0;
    mBatchCount = 0;
    mCommands->get();
    bool resized = false;
    mSwapChain->acquire(resized);
    mCurrentVulkanFrame = VulkanHelper::getSingleton()._getFrame(mFrameIndex);
}

void VulkanRenderSystem::present()
{
    mSwapChain->present();
    mFrameIndex++;
    mFrameIndex %= VULKAN_FRAME_RESOURCE_COUNT;
}

void VulkanRenderSystem::frameEnd()
{
    mStagePool.gc();
    mFrameNumber++;
}

void VulkanRenderSystem::beginRenderPass(
    RenderPassInfo& renderPassInfo)
{
    VkCommandBuffer cmdBuffer = mCommands->get().buffer();

    mCurrentVKImage = nullptr;
    mCurrentRenderPassInfo = renderPassInfo;

    if (!renderPassInfo.shadowPass)
    {
        mFrameConstantBuffer.ShadowTransform = renderPassInfo.lightViewProj;
    }
    updateMainPassCB(mCurrentRenderPassInfo.cam);
  
    VkRenderingAttachmentInfo colorAttachments[MAX_RENDER_TARGET_ATTACHMENTS] = {};
    VkRenderingAttachmentInfo depthAttachment = {};

    for (auto i = 0; i < renderPassInfo.renderTargetCount; i++)
    {
        colorAttachments[i].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        colorAttachments[i].pNext = NULL;
        colorAttachments[i].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        colorAttachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachments[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        Ogre::VulkanRenderTarget* rt = (Ogre::VulkanRenderTarget*)renderPassInfo.renderTargets[i].renderTarget;
        mCurrentVKImage = rt->getImage();

        vks::tools::insertImageMemoryBarrier(
            cmdBuffer,
            rt->getImage(),
            0,
            VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        colorAttachments[i].imageView = rt->getImageView();
        const ClearValue* clearValue = &renderPassInfo.renderTargets[i].clearColour;
        colorAttachments[i].clearValue.color = { { clearValue->r, clearValue->g, clearValue->b, clearValue->a } };
    }

    bool hasDepth = true;

    if (hasDepth)
    {
        depthAttachment.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
        depthAttachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

        Ogre::VulkanRenderTarget* rt = (Ogre::VulkanRenderTarget*)renderPassInfo.depthTarget.depthStencil;
        depthAttachment.imageView = rt->getImageView();

        if (renderPassInfo.shadowPass)
        {
            mCurrentVKImage = rt->getImage();
        }
        vks::tools::insertImageMemoryBarrier(
            cmdBuffer,
            rt->getImage(),
            0,
            VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            VkImageSubresourceRange{ VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT, 0, 1, 0, 1 });

        const ClearValue* clearValue = &renderPassInfo.depthTarget.clearValue;
        depthAttachment.clearValue.depthStencil = { clearValue->depth, clearValue->stencil };

    }

    VkRect2D renderArea = {};
    renderArea.offset.x = 0;
    renderArea.offset.y = 0;
    uint32_t layerCount = 0;
    if (renderPassInfo.renderTargetCount)
    {
        renderArea.extent.width = renderPassInfo.renderTargets[0].renderTarget->getWidth();
        renderArea.extent.height = renderPassInfo.renderTargets[0].renderTarget->getHeight();
        layerCount = 1;
    }
    else if (hasDepth)
    {
        renderArea.extent.width = renderPassInfo.depthTarget.depthStencil->getWidth();
        renderArea.extent.height = renderPassInfo.depthTarget.depthStencil->getHeight();
        layerCount = 1;
    }
    else
    {
        assert(false);
    }

    VkRenderingInfoKHR renderingInfo = {};
    renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
    renderingInfo.pColorAttachments = colorAttachments;
    renderingInfo.colorAttachmentCount = renderPassInfo.renderTargetCount;
    renderingInfo.pDepthAttachment = hasDepth ? &depthAttachment : nullptr;
    renderingInfo.pStencilAttachment = hasDepth ? &depthAttachment : nullptr;
    renderingInfo.renderArea = renderArea;
    renderingInfo.layerCount = layerCount;

  
    bluevk::vkCmdBeginRenderingKHR(cmdBuffer, &renderingInfo);

    auto width = renderArea.extent.width;
    auto height = renderArea.extent.height;
    VkViewport viewport = vks::initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
    VkRect2D scissor = vks::initializers::rect2D(width, height, 0, 0);

    bluevk::vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
    bluevk::vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);
}

void VulkanRenderSystem::endRenderPass()
{
    auto frameIndex = mCurrentVulkanFrame->getFrameIndex();
    VkCommandBuffer cmdBuffer = mCommands->get().buffer();

    vkCmdEndRenderingKHR(cmdBuffer);

    if (mCurrentVKImage)
    {
        if (mCurrentRenderPassInfo.shadowPass)
        {
            VkImageSubresourceRange subresourceRange = {};
            subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
            subresourceRange.baseMipLevel = 0;
            subresourceRange.levelCount = 1;
            subresourceRange.layerCount = 1;

            vks::tools::setImageLayout(
                cmdBuffer,
                mCurrentVKImage,
                VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                subresourceRange);
            
        }
        else
        {
            vks::tools::insertImageMemoryBarrier(
                cmdBuffer,
                mCurrentVKImage,
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                0,
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
        }
        
    }
    

    
}


void VulkanRenderSystem::update(Renderable* r)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

    rd->update(mCurrentRenderPassInfo, nullptr);
}

void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
    VkCommandBuffer commandBuffer = mCommands->get().buffer();
    rd->update(mCurrentRenderPassInfo, nullptr);
    rd->render(commandBuffer, mPipelineCache, mCurrentRenderPassInfo);
}


void VulkanRenderSystem::multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread)
{
    multithread = false;

    mRenderList.clear();
    
    for (auto r : objs)
    {
        VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
        if (rd->update(mCurrentRenderPassInfo, nullptr))
        {
            mRenderList.push_back(r);
        }
    }

    if (mRenderList.empty())
    {
        return;
    }

    uint32_t size = (uint32_t)mRenderList.size();

    
    for (auto r : mRenderList)
    {
        VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
        VkCommandBuffer commandBuffer = mCommands->get().buffer();
        rd->render(commandBuffer, mPipelineCache, mCurrentRenderPassInfo);
    }

}








