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
#include <VulkanPipelineLayoutCache.h>
#include <shaderManager.h>


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
    mCommands->get();
    bool resized = false;
    mSwapChain->acquire(resized);
}

void VulkanRenderSystem::present()
{
    mSwapChain->present();
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

void VulkanRenderSystem::beginComputePass(ComputePassInfo& computePassInfo)
{
    VulkanPipelineLayoutCache::PipelineLayoutKey layoutKey;
    VulkanDescriptorSetLayout* first = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(
        computePassInfo.pipelineLayout.setLayout[0]);
    layoutKey[0] = first->getVkLayout();
    layoutKey[1] = VK_NULL_HANDLE;
    auto pipelineLayoutCache = VulkanHelper::getSingleton().getPipelineLayoutCache();
    auto pipelineLayout = pipelineLayoutCache->getLayout(layoutKey);

    auto pipeline = VulkanHelper::getSingleton().createComputePipeline(computePassInfo.shaderName, pipelineLayout);
    VkCommandBuffer commandBuffer = mCommands->get().buffer();

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);

    
    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(computePassInfo.ds);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
        pipelineLayout, 0, 1, &set->vkSet, 0, nullptr);

    vkCmdDispatch(commandBuffer,
        computePassInfo.computeGroup._x, computePassInfo.computeGroup._y, computePassInfo.computeGroup._z);

}

void VulkanRenderSystem::endComputePass()
{

}


void VulkanRenderSystem::update(Renderable* r)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

    rd->update(mCurrentRenderPassInfo, nullptr);
}

void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    



}


void VulkanRenderSystem::multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread)
{
    auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
    VkCommandBuffer cmdBuffer = mCommands->get().buffer();
    ObjectConstantBuffer objectConstantBuffer;
    for (auto r : mRenderList)
    {
        Ogre::Material* mat = r->getMaterial().get();
        Handle<HwPipeline> pipeline = mat->getPipeline();
        Handle<HwProgram> program = mat->getProgram();
        VulkanPipeline* vulkanPineline = mResourceAllocator.handle_cast<VulkanPipeline*>(pipeline);
        VulkanProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanProgram*>(program);
        VertexData* vertexData = r->getVertexData();
        IndexData* indexData = r->getIndexData();
        vertexData->bind(cmdBuffer);

        FrameResourceInfo* resourceInfo = mat->getFrameResourceInfo(frameIndex);
        const Ogre::Matrix4& model = r->getModelMatrix();
        objectConstantBuffer.world = model.transpose();

        updateBufferObject(resourceInfo->modelObjectHandle, 
            (const char*) & objectConstantBuffer, sizeof(objectConstantBuffer));
        updateDescriptorSetBuffer(resourceInfo->uboSet, 1, 
            mCurrentRenderPassInfo.frameDataHandle, 0, mCurrentRenderPassInfo.frameDataSize);
        VulkanDescriptorSet* ubo = 
            mResourceAllocator.handle_cast<VulkanDescriptorSet*>(resourceInfo->uboSet);
        VulkanDescriptorSet* sampler = 
            mResourceAllocator.handle_cast<VulkanDescriptorSet*>(resourceInfo->samplerSet);
        VkDescriptorSet ds[2] = {ubo->vkSet,  sampler->vkSet};

        vkCmdBindDescriptorSets(
            cmdBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            vulkanProgram->getVulkanPipelineLayout(), 0, 2, &ds[0], 0, nullptr);

        if (indexData)
        {
            indexData->getIndexBuffer()->bind(cmdBuffer);
            IndexDataView* view = r->getIndexView();
            vkCmdDrawIndexed(cmdBuffer, view->mIndexCount, 1,
                view->mIndexLocation, view->mBaseVertexLocation, 0);

            incrTriangleCount(view->mIndexCount / 3);
        }
        else
        {
            RawDataView* view = r->getRawDataView();
            if (view == nullptr)
            {
                vkCmdDraw(cmdBuffer, vertexData->getVertexCount(), 1, 0, 0);
                incrTriangleCount(vertexData->getVertexCount() / 3);
            }
            else
            {
                vkCmdDraw(cmdBuffer, view->mVertexCount, 1, view->mVertexStart, 0);
                incrTriangleCount(view->mVertexCount / 3);
            }

        }

        incrBatchCount(1);
    }

}








