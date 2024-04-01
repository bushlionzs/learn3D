#include "OgreHeader.h"
#include "VulkanWindow.h"
#include "OgreStringConverter.h"
#include "VulkanHelper.h"
#include "VulkanWindow.h"
#include "VulkanRenderSystem.h"
#include "VulkanFrame.h"

VulkanWindow::VulkanWindow()
{
	mWidth = 0;
	mHeight = 0;
}

VulkanWindow::~VulkanWindow()
{

}

void VulkanWindow::create(const String& name, unsigned int width, unsigned int height,
	bool fullScreen, const NameValuePairList* miscParams)
{
	auto itor = miscParams->find("externalWindowHandle");
	if (itor == miscParams->end())
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "externalWindowHandle should be provided");
	}

	mWnd = (HWND)StringConverter::parseSizeT(itor->second);

    mSurface = VulkanHelper::getSingleton()._getSurface();

    mWidth = width;
    mHeight = height;

    setupDepthStencil();
    createFramebuffers();
    createSyncObjects();
    resize(width, height);
}

void VulkanWindow::destroy()
{

}

void VulkanWindow::resize(unsigned int width, unsigned int height)
{
	if (mWidth == width && mHeight == height)
	{
		return;
	}

    mWidth = width;
    mHeight = height;
}

void VulkanWindow::copyContentsToMemory(
    const Box& src,
    const PixelBox& dst,
    FrameBuffer buffer)
{

}

bool VulkanWindow::requiresTextureFlipping() const
{
    return false;
}

void VulkanWindow::start()
{
    mHaveRenderPass = false;
}
void VulkanWindow::preRender(VulkanFrame* frame, const ColourValue& colour)
{
    auto width = mWidth;
    auto height = mHeight;


    auto frame_index = frame->getFrameIndex();

    auto renderPass = VulkanHelper::getSingleton()._getRenderPass();



    auto framebuffer = getFrameBuffer(frame_index);

    VkCommandBufferInheritanceInfo inheritanceInfo = vks::initializers::commandBufferInheritanceInfo();
    inheritanceInfo.renderPass = renderPass;
    // Secondary command buffer also use the currently active framebuffer
    inheritanceInfo.framebuffer = framebuffer;



    VkCommandBufferBeginInfo commandBufferBeginInfo = vks::initializers::commandBufferBeginInfo();
    commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
    commandBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;
    VkViewport viewport = vks::initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
    VkRect2D scissor = vks::initializers::rect2D(width, height, 0, 0);

    VkClearValue clearValues[2];
    memcpy(clearValues[0].color.float32, colour.ptr(), sizeof(ColourValue));
    clearValues[1].depthStencil = { 1.0f, 0 };



    VkRenderPassBeginInfo renderPassBeginInfo =
        vks::initializers::renderPassBeginInfo();
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.renderArea.offset.x = 0;
    renderPassBeginInfo.renderArea.offset.y = 0;
    renderPassBeginInfo.renderArea.extent.width = width;
    renderPassBeginInfo.renderArea.extent.height = height;
    renderPassBeginInfo.clearValueCount = 2;
    renderPassBeginInfo.pClearValues = clearValues;
    renderPassBeginInfo.framebuffer = framebuffer;

    VkImageSubresourceRange subresourceRange = {};
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.layerCount = 1;

    static std::vector<VkCommandBuffer>  cmdlist;
    VulkanHelper::getSingleton().fillCommandBufferList(cmdlist, frame_index, true);


    for (int32_t i = 1; i < cmdlist.size(); i++)
    {
        auto* commandBuffer = cmdlist.at(i);

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    if (!mHaveRenderPass)
    {
        vkCmdSetViewport(cmdlist[0], 0, 1, &viewport);
        vkCmdSetScissor(cmdlist[0], 0, 1, &scissor);
        vkCmdBeginRenderPass(cmdlist[0], &renderPassBeginInfo,
            VK_SUBPASS_CONTENTS_INLINE);
        
        mHaveRenderPass = true;
    }
}

VkFramebuffer VulkanWindow::getFrameBuffer(uint32_t index)
{
    return mSwapChainFramebuffers[index];
}

uint32_t VulkanWindow::getTargetWidth()
{
    return getWidth();
}

uint32_t VulkanWindow::getTargetHeight()
{
    return getHeight();
}

VulkanFrame* VulkanWindow::getNextFrame()
{
    auto swapchain = VulkanHelper::getSingleton().getSwapchain();   
    auto device = VulkanHelper::getSingleton()._getVkDevice();

    uint32_t index = 0xffffffff;

    VkResult result = vkAcquireNextImageKHR(
        device,
        swapchain,
        std::numeric_limits<uint64_t>::max(),
        mImageAvailableSemaphore,
        VK_NULL_HANDLE,
        &index);
    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkAcquireNextImageKHR error");
    }
    


    auto frame =  VulkanHelper::getSingleton()._getFrame(index);

    auto fence = frame->getFence();

    auto result2 = vkGetFenceStatus(device, fence);
    result = vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkWaitForFences error");
    }

    result = vkResetFences(device, 1, &fence);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkResetFences error");
    }

    return frame;
}

void VulkanWindow::createFramebuffers()
{
    auto device = VulkanHelper::getSingleton()._getVkDevice();
    auto renderPass = VulkanHelper::getSingleton()._getRenderPass();
    VkImageView attachments[2];

    // Depth/Stencil attachment is the same for all frame buffers
    attachments[1] = mDepthStencil._view;

    VkFramebufferCreateInfo frameBufferCreateInfo = {};
    frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    frameBufferCreateInfo.pNext = NULL;
    frameBufferCreateInfo.renderPass = renderPass;
    frameBufferCreateInfo.attachmentCount = 2;
    frameBufferCreateInfo.pAttachments = attachments;
    frameBufferCreateInfo.width = mWidth;
    frameBufferCreateInfo.height = mHeight;
    frameBufferCreateInfo.layers = 1;

    auto swapchain = VulkanHelper::getSingleton().getSwapchainBuffer();
    mSwapChainFramebuffers.resize(swapchain.size());

    for (size_t i = 0; i < swapchain.size(); i++)
    {
        attachments[0] = swapchain[i]._view;

        if (vkCreateFramebuffer(device, &frameBufferCreateInfo, 
            nullptr, &mSwapChainFramebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void VulkanWindow::setupDepthStencil()
{
    mDepthStencil = VulkanHelper::getSingleton().createDepthStencil(
        getWidth(), getHeight());
}

void VulkanWindow::swapBuffers()
{
    mHaveRenderPass = false;
    auto currentFrame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
    
    auto frame_index = currentFrame->getFrameIndex();
    VulkanHelper::getSingleton()._endCommandBuffer(frame_index);
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;


    VkPipelineStageFlags waitDestStageMasks[2] = {
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
    };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &mImageAvailableSemaphore;

    static std::vector<VkCommandBuffer>  cmdlist;
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frame_index);
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    auto renderFinshedSemaphore = currentFrame->getFinishedSemaphore();
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &renderFinshedSemaphore;
    submitInfo.pWaitDstStageMask = waitDestStageMasks;

    auto queue = VulkanHelper::getSingleton()._getCommandQueue();
    auto fence = currentFrame->getFence();
    auto result = vkQueueSubmit(queue, 1, &submitInfo, fence);
    if(result!= VK_SUCCESS)
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

    presentInfo.pImageIndices = &currentFrame->getFrameIndex();

    result = vkQueuePresentKHR(queue, &presentInfo);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to present swap chain image!");
    }
}

void VulkanWindow::createSyncObjects()
{
    auto device = VulkanHelper::getSingleton()._getVkDevice();

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    fenceInfo.flags = 0;
    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mImageAvailableSemaphore) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}

