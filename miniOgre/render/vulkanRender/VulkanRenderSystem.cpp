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
#include <vulkan/VulkanPipelineCache.h>

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
    new VulkanHelper(this, wnd);

    mRenderList.reserve(3000);
    
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    RenderSystem::engineInit();
    
    VulkanHelper& helper = VulkanHelper::getSingleton();
    helper._initialise();

    enki::TaskSchedulerConfig config;
    config.numTaskThreadsToCreate = VULKAN_COMMAND_THREAD;
    mTaskScheduler.Initialize(config);

    mPipelineCache = helper.getPipelineCache();

    return true;
}


void VulkanRenderSystem::frameStart()
{ 
    mTriangleCount = 0;
    mBatchCount = 0;

    mCurrentVulkanFrame = getNextFrame();

    VulkanHelper::getSingleton()._resetCommandBuffer(mCurrentVulkanFrame->getFrameIndex());

    static std::vector<VkCommandBuffer>  cmdlist;
    VulkanHelper::getSingleton().fillCommandBufferList(cmdlist, mCurrentVulkanFrame->getFrameIndex(), true);

    VkCommandBufferBeginInfo cmdBeginInfo{};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.pNext = NULL;
    cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    cmdBeginInfo.pInheritanceInfo = NULL;

    //auto framebuffer = mRenderWindow->getFrameBuffer(mCurrentVulkanFrame->getFrameIndex());
    //auto renderPass = VulkanHelper::getSingleton()._getRenderPass();
    //VkCommandBufferInheritanceInfo inheritanceInfo = vks::initializers::commandBufferInheritanceInfo();
    //inheritanceInfo.renderPass = renderPass;
    //// Secondary command buffer also use the currently active framebuffer
    //inheritanceInfo.framebuffer = framebuffer;



    //VkCommandBufferBeginInfo secondBufferBeginInfo = vks::initializers::commandBufferBeginInfo();
    //secondBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
    //secondBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;


    auto result = vkBeginCommandBuffer(cmdlist[0], &cmdBeginInfo);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("vkBeginCommandBuffer failed");
    }
#ifdef MULTITHREAD
    for (int32_t i = 1; i < cmdlist.size(); i++)
    {
        auto* commandBuffer = cmdlist.at(i);
        auto result = vkBeginCommandBuffer(commandBuffer, &secondBufferBeginInfo);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("vkBeginCommandBuffer failed");
        }
    }
#endif
}

void VulkanRenderSystem::frameEnd()
{
    mFrameNumber++;
}

void VulkanRenderSystem::beginRenderPass(
    RenderPassInfo& renderPassInfo)
{

    auto frameIndex = mCurrentVulkanFrame->getFrameIndex();
    VkCommandBuffer cmdBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frameIndex);

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
    VkCommandBuffer cmdBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frameIndex);

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

void VulkanRenderSystem::present()
{
    auto frameIndex = mCurrentVulkanFrame->getFrameIndex();
    VulkanHelper::getSingleton()._endCommandBuffer(frameIndex);
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;


    VkPipelineStageFlags waitDestStageMasks[2] = {
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
    };

    auto imageAvailableSemaphore = mCurrentVulkanFrame->getImageAvailableSemaphore();
    auto renderFinshedSemaphore = mCurrentVulkanFrame->getFinishedSemaphore();

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &imageAvailableSemaphore;

    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frameIndex);
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;


    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &renderFinshedSemaphore;
    submitInfo.pWaitDstStageMask = waitDestStageMasks;

    auto queue = VulkanHelper::getSingleton()._getCommandQueue();
    auto fence = mCurrentVulkanFrame->getFence();
    auto result = vkQueueSubmit(queue, 1, &submitInfo, fence);
    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to submit draw command buffer!");
    }

    auto device = VulkanHelper::getSingleton()._getVkDevice();

    //vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);




    auto swapchain = VulkanHelper::getSingleton().getSwapchain();

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = NULL;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &renderFinshedSemaphore;

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &swapchain;

    presentInfo.pImageIndices = &mImageIndex;

    result = vkQueuePresentKHR(queue, &presentInfo);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to present swap chain image!");
    }

    mFrameIndex++;

    mFrameIndex %= VULKAN_FRAME_RESOURCE_COUNT;


}


Ogre::RenderWindow* VulkanRenderSystem::createRenderWindow(
    const String& name, unsigned int width, unsigned int height,
    const NameValuePairList* miscParams)
{
    mRenderWindow = new VulkanWindow();

    mRenderWindow->create(name, width, height, false, miscParams);

    return mRenderWindow;
}

Ogre::RenderTarget* VulkanRenderSystem::createRenderTarget(
    const String& name, 
    uint32_t width, 
    uint32_t height, 
    Ogre::PixelFormat format, 
    uint32_t textureUsage)
{
    TextureProperty texProperty;
    texProperty._width = width;
    texProperty._height = height;
    texProperty._tex_usage = textureUsage;
    texProperty._tex_format = format;
    texProperty._need_mipmap = false;
    
    Ogre::VulkanRenderTarget* renderTarget = new Ogre::VulkanRenderTarget(name, texProperty);
    return renderTarget;
}

void VulkanRenderSystem::update(Renderable* r)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

    rd->update(mCurrentVulkanFrame, mCurrentRenderPassInfo, nullptr);
}

void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
    rd->update(mCurrentVulkanFrame, mCurrentRenderPassInfo, nullptr);
    rd->render(mCurrentVulkanFrame, commandBuffer, mPipelineCache, mCurrentRenderPassInfo);
}

using fn_on_got_tracker_info = std::function<void(uint32_t)>;

struct ParallelTaskSet : public enki::IPinnedTask
{
    void update(int32_t start, int32_t end, VulkanFrame* frame, std::vector<Ogre::Renderable*>* objs)
    {
        _start = start;
        _end = end;
        _frame = frame;
        _objs = objs;
    }

    ParallelTaskSet(uint32_t tdx):IPinnedTask(tdx)
    {

    }
    virtual void Execute() 
    { 
        auto tdx = threadNum;
        std::vector<Ogre::Renderable*>& objs = *_objs;
        for (int32_t i = _start; i < _end; i++)
        {
            Ogre::Renderable* r = objs[i];
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(tdx, _frame->getFrameIndex());
            //rd->render(_frame, commandBuffer, nullptr, mCurrentRenderPassInfo);//zhousha
        }
    }

    int32_t _start;
    int32_t _end;
    std::vector<Ogre::Renderable*>* _objs;
    VulkanFrame* _frame;
};

void VulkanRenderSystem::multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread)
{
    multithread = false;

    mRenderList.clear();
    
    for (auto r : objs)
    {
        VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
        if (rd->update(mCurrentVulkanFrame, mCurrentRenderPassInfo, nullptr))
        {
            mRenderList.push_back(r);
        }
    }

    if (mRenderList.empty())
    {
        return;
    }

    uint32_t size = (uint32_t)mRenderList.size();

    if(false)
    {
        for (auto r : mRenderList)
        {
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
            // VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(3, mCurrentVulkanFrame->getFrameIndex());
            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
            rd->render(mCurrentVulkanFrame, commandBuffer, mPipelineCache, mCurrentRenderPassInfo);
        }
        return;
    }
    if (!multithread)
    {
        for (auto r : mRenderList)
        {
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
            //VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(3, mCurrentVulkanFrame->getFrameIndex());
            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
            rd->render(mCurrentVulkanFrame, commandBuffer, mPipelineCache, mCurrentRenderPassInfo);
        }
        return;
    }

    uint32_t every = size / VULKAN_COMMAND_THREAD;

    uint32_t left = size - every * VULKAN_COMMAND_THREAD;

    int32 start = 0;
    int32 end = 0;
    VulkanFrame* frame = mCurrentVulkanFrame;

    

    static std::vector<ParallelTaskSet*> tasklist;
    if (tasklist.empty())
    {
        tasklist.resize(VULKAN_COMMAND_THREAD);
        for (int32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
        {
            tasklist[i] = new ParallelTaskSet(i);
        }
    }

    
    for (int32_t i = 0; i < VULKAN_COMMAND_THREAD - 1; i++)
    {
        end = start + every;
        if (end > start)
        {
            ParallelTaskSet* task = tasklist[i];
            task->update(start, end, mCurrentVulkanFrame, &objs);
            mTaskScheduler.AddPinnedTask(task);
        }
        
        start = end;
    }

    ParallelTaskSet* task = tasklist[VULKAN_COMMAND_THREAD - 1];
    end = start + every + left;
    task->update(start, end, mCurrentVulkanFrame, &objs);
    mTaskScheduler.AddPinnedTask(task);

    mTaskScheduler.RunPinnedTasks();

    for (int32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
    {
        mTaskScheduler.WaitforTask(tasklist[i]);
    }
}








