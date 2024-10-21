#include "OgreHeader.h"
#include "VulkanRenderSystem.h"
#include "OgreRenderable.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreMaterial.h"
#include "OgreRoot.h"
#include "VulkanRenderTarget.h"
#include "VulkanMappings.h"
#include <VulkanPipelineCache.h>
#include <VulkanHandles.h>
#include <VulkanPipelineLayoutCache.h>
#include "VulkanTexture.h"
#include "VulkanTools.h"
#include "VulkanHelper.h"
#include "VulkanWindow.h"



VulkanRenderSystem::VulkanRenderSystem(HWND wnd)
{
    bluevk::initialize();

    mRenderSystemName = "Vulkan";
    mRenderType = EngineType_Vulkan;
    

    mRenderList.reserve(3000);
    
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    VulkanRenderSystemBase::engineInit();
    

    return true;
}


void VulkanRenderSystem::frameStart()
{ 
    mTriangleCount = 0;
    mBatchCount = 0;
    mLastPipeline = VK_NULL_HANDLE;
    mCommandBuffer = mCommands->get().buffer();
    bool resized = false;
    mSwapChain->acquire(resized);
}

void VulkanRenderSystem::present()
{
    mSwapChain->present();
}

void VulkanRenderSystem::frameEnd()
{
    mStagePool->gc();
}

void VulkanRenderSystem::beginRenderPass(
    RenderPassInfo& renderPassInfo)
{
    VkCommandBuffer cmdBuffer = mCommands->get().buffer();

    mCurrentVKImage = nullptr;
    mCurrentRenderPassInfo = renderPassInfo;
  
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


void VulkanRenderSystem::bindPipeline(
    Handle<HwProgram> programHandle,
    Handle<HwPipeline> pipelineHandle,
    Handle<HwDescriptorSet>* descSets,
    uint32_t setCount)
{
    VulkanProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanProgram*>(programHandle);
    VkCommandBuffer commandBuffer = mCommands->get().buffer();
    VulkanPipeline* vulkanPipeline = mResourceAllocator.handle_cast<VulkanPipeline*>(pipelineHandle);

    auto pipeline = vulkanPipeline->getPipeline();

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    auto pipelineLayout = vulkanProgram->getVulkanPipelineLayout();

    VkDescriptorSet descriptorSet[4];
   
    for (auto i = 0; i < setCount; i++)
    {
        if (descSets[i])
        {
            VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(descSets[i]);
            descriptorSet[i] = set->vkSet;
        }
        else
        {
            descriptorSet[i] =  pEmptyDescriptorSet;
        }
    }

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout, 0, setCount, &descriptorSet[0], 0, nullptr);
}

void VulkanRenderSystem::drawIndexed(
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    uint32_t vertexOffset,
    uint32_t firstInstance)
{
    auto cmdBuffer = mCommands->get().buffer();
    vkCmdDrawIndexed(cmdBuffer, indexCount, instanceCount,
        firstIndex, vertexOffset, firstInstance);

    incrTriangleCount(indexCount / 3);

    incrBatchCount(1);
}

void VulkanRenderSystem::drawIndexedIndirect(
    Handle<HwBufferObject> drawBuffer,
    uint32_t offset,
    uint32_t drawCount,
    uint32_t stride
)
{
    auto cmdBuffer = mCommands->get().buffer();
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(drawBuffer);
    VkBuffer vkBuf = vulkanBufferObject->buffer.getGpuBuffer();
    vkCmdDrawIndexedIndirect(cmdBuffer, vkBuf, offset, drawCount, stride);
}

void VulkanRenderSystem::beginComputePass(ComputePassInfo& computePassInfo)
{
    VulkanComputeProgram* program = mResourceAllocator.handle_cast<VulkanComputeProgram*>(computePassInfo.programHandle);

    auto pipeline = program->getPipeline();
    auto pipelineLayout = program->getPipelineLayout();
    VkCommandBuffer commandBuffer = mCommands->get().buffer();

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);

    VkDescriptorSet descriptorSet[4];
    uint32_t index = 0;
    for (auto& ds : computePassInfo.descSets)
    {
        VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(ds);
        descriptorSet[index] = set->vkSet;
        index++;
    }

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
        pipelineLayout, 0, index, &descriptorSet[0], 0, nullptr);
    
    

    vkCmdDispatch(commandBuffer,
        computePassInfo.computeGroup._x, computePassInfo.computeGroup._y, computePassInfo.computeGroup._z);

}

void VulkanRenderSystem::endComputePass()
{

}









