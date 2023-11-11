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

void VulkanWindow::preRender(VkCommandBuffer commandBuffer)
{
    VkViewport viewport = vks::initializers::viewport((float)mWidth, (float)mHeight, 0.0f, 1.0f);

    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor = vks::initializers::rect2D(mWidth, mHeight, 0, 0);
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
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
    auto currentFrame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
    VkCommandBuffer pCommandBuffer = currentFrame->getVkCommandBuffer();
    vkCmdEndRenderPass(pCommandBuffer);
    if (vkEndCommandBuffer(pCommandBuffer) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkBeginCommandBuffer!");
    }
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;


    VkPipelineStageFlags waitDestStageMasks[2] = {
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
    };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &mImageAvailableSemaphore;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &pCommandBuffer;

    auto renderFinshedSemaphore = currentFrame->getFinishedSemaphore();
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &renderFinshedSemaphore;
    submitInfo.pWaitDstStageMask = waitDestStageMasks;

    auto queue = VulkanHelper::getSingleton()._getCommandQueue();

    auto result = vkQueueSubmit(queue, 1, &submitInfo, currentFrame->getFence());
    if(result!= VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to submit draw command buffer!");
    }

    auto device = VulkanHelper::getSingleton()._getVkDevice();
    

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

