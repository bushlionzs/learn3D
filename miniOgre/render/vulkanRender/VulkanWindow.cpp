#include "OgreHeader.h"
#include "VulkanWindow.h"
#include "OgreStringConverter.h"
#include "VulkanHelper.h"
#include "VulkanWindow.h"
#include "VulkanRenderSystem.h"
#include "VulkanFrame.h"
#include "VulkanTools.h"

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
    resize(width, height);
}

void VulkanWindow::destroy()
{

}

void VulkanWindow::resize(unsigned int width, unsigned int height)
{
    mWidth = width;
    mHeight = height;
    createFramebuffers();
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

    const auto& settings = VulkanHelper::getSingleton().getVulkanSettings();

    VkClearValue clearValues[3];

    if (settings.multiSampling)
    {
        memcpy(clearValues[0].color.float32, colour.ptr(), sizeof(ColourValue));
        memcpy(clearValues[1].color.float32, colour.ptr(), sizeof(ColourValue));
        clearValues[2].depthStencil = { 1.0f, 0 };
    }
    else
    {
        memcpy(clearValues[0].color.float32, colour.ptr(), sizeof(ColourValue));
        clearValues[1].depthStencil = { 1.0f, 0 };
    }
    



    VkRenderPassBeginInfo renderPassBeginInfo =
        vks::initializers::renderPassBeginInfo();
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.renderArea.offset.x = 0;
    renderPassBeginInfo.renderArea.offset.y = 0;
    renderPassBeginInfo.renderArea.extent.width = width;
    renderPassBeginInfo.renderArea.extent.height = height;
    renderPassBeginInfo.clearValueCount = settings.multiSampling?3:2;
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
        vkCmdBeginRenderPass(cmdlist[0], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        
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

    auto frame = VulkanHelper::getSingleton()._getFrame(mFrameIndex);

    auto fence = frame->getFence();

    VkResult result = vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkWaitForFences error");
    }

    result = vkResetFences(device, 1, &fence);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkResetFences error");
    }

    auto imageAvailableSemaphore = frame->getImageAvailableSemaphore();
    result = vkAcquireNextImageKHR(
        device,
        swapchain,
        std::numeric_limits<uint64_t>::max(),
        imageAvailableSemaphore,
        VK_NULL_HANDLE,
        &mImageIndex);
    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "vkAcquireNextImageKHR error");
    }
    

    return frame;
}

void VulkanWindow::createFramebuffers()
{
    VulkanHelper& helper = VulkanHelper::getSingleton();
    auto device = helper._getVkDevice();
    auto renderPass = helper._getRenderPass();
    VkImageView attachments[4];
    const auto& settings = helper.getVulkanSettings();

    mDepthStencil = helper.createDepthStencil(mWidth, mHeight);

    if (settings.multiSampling)
    {
        // Check if device supports requested sample count for color and depth frame buffer
        //assert((deviceProperties.limits.framebufferColorSampleCounts >= sampleCount) && (deviceProperties.limits.framebufferDepthSampleCounts >= sampleCount));

        VkImageCreateInfo imageCI{};
        imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCI.imageType = VK_IMAGE_TYPE_2D;
        imageCI.format = helper.getSwapChainImageFormat();
        imageCI.extent = { mWidth, mHeight, 1};
        imageCI.mipLevels = 1;
        imageCI.arrayLayers = 1;
        imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageCI.samples = settings.sampleCount;
        imageCI.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VK_CHECK_RESULT(vkCreateImage(device, &imageCI, nullptr, &mMultisampleTarget.color.image));

        VkMemoryRequirements memReqs;
        vkGetImageMemoryRequirements(device, mMultisampleTarget.color.image, &memReqs);
        VkMemoryAllocateInfo memAllocInfo{};
        memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAllocInfo.allocationSize = memReqs.size;

        memAllocInfo.memoryTypeIndex = helper._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        vkAllocateMemory(device, &memAllocInfo, nullptr, &mMultisampleTarget.color.memory);
        vkBindImageMemory(device, mMultisampleTarget.color.image, mMultisampleTarget.color.memory, 0);

        // Create image view for the MSAA target
        VkImageViewCreateInfo imageViewCI{};
        imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCI.image = mMultisampleTarget.color.image;
        imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCI.format = helper.getSwapChainImageFormat();
        imageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
        imageViewCI.components.g = VK_COMPONENT_SWIZZLE_G;
        imageViewCI.components.b = VK_COMPONENT_SWIZZLE_B;
        imageViewCI.components.a = VK_COMPONENT_SWIZZLE_A;
        imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewCI.subresourceRange.levelCount = 1;
        imageViewCI.subresourceRange.layerCount = 1;
        vkCreateImageView(device, &imageViewCI, nullptr, &mMultisampleTarget.color.view);

        // Depth target
        imageCI.imageType = VK_IMAGE_TYPE_2D;
        imageCI.format = helper._getDepthFormat();
        imageCI.extent = { mWidth, mHeight, 1 };
        imageCI.mipLevels = 1;
        imageCI.arrayLayers = 1;
        imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageCI.samples = settings.sampleCount;
        imageCI.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        vkCreateImage(device, &imageCI, nullptr, &mMultisampleTarget.depth.image);

        vkGetImageMemoryRequirements(device, mMultisampleTarget.depth.image, &memReqs);
        memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAllocInfo.allocationSize = memReqs.size;
        memAllocInfo.memoryTypeIndex = helper._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        VK_CHECK_RESULT(vkAllocateMemory(device, &memAllocInfo, nullptr, &mMultisampleTarget.depth.memory));
        vkBindImageMemory(device, mMultisampleTarget.depth.image, mMultisampleTarget.depth.memory, 0);

        // Create image view for the MSAA target
        imageViewCI.image = mMultisampleTarget.depth.image;
        imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCI.format = helper._getDepthFormat();
        imageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
        imageViewCI.components.g = VK_COMPONENT_SWIZZLE_G;
        imageViewCI.components.b = VK_COMPONENT_SWIZZLE_B;
        imageViewCI.components.a = VK_COMPONENT_SWIZZLE_A;
        imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
        imageViewCI.subresourceRange.levelCount = 1;
        imageViewCI.subresourceRange.layerCount = 1;
        VK_CHECK_RESULT(vkCreateImageView(device, &imageViewCI, nullptr, &mMultisampleTarget.depth.view));
    }

    if (settings.multiSampling) 
    {
        attachments[0] = mMultisampleTarget.color.view;
        attachments[2] = mMultisampleTarget.depth.view;
        attachments[3] = mDepthStencil.view;
    }
    else {
        attachments[1] = mDepthStencil.view;
    }


    VkFramebufferCreateInfo frameBufferCreateInfo = {};
    frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    frameBufferCreateInfo.pNext = NULL;
    frameBufferCreateInfo.renderPass = renderPass;
    frameBufferCreateInfo.attachmentCount = settings.multiSampling ? 4 : 2;
    frameBufferCreateInfo.pAttachments = attachments;
    frameBufferCreateInfo.width = mWidth;
    frameBufferCreateInfo.height = mHeight;
    frameBufferCreateInfo.layers = 1;

    auto swapchain = VulkanHelper::getSingleton().getSwapchainBuffer();
    mSwapChainFramebuffers.resize(swapchain.size());

    for (size_t i = 0; i < swapchain.size(); i++)
    {
        if (settings.multiSampling)
        {
            attachments[1] = swapchain[i]._view;
        }
        else {
            attachments[0] = swapchain[i]._view;
        }

        VK_CHECK_RESULT(vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &mSwapChainFramebuffers[i]));
    }
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

    auto imageAvailableSemaphore = currentFrame->getImageAvailableSemaphore();
    auto renderFinshedSemaphore = currentFrame->getFinishedSemaphore();

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &imageAvailableSemaphore;

    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frame_index);
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    
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

    presentInfo.pImageIndices = &mImageIndex;

    result = vkQueuePresentKHR(queue, &presentInfo);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to present swap chain image!");
    }

    mFrameIndex++;

    mFrameIndex %= VULKAN_FRAME_RESOURCE_COUNT;
}

void VulkanWindow::createSyncObjects()
{
}

