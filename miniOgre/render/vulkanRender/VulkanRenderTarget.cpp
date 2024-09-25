#include "OgreHeader.h"
#include "VulkanRenderTarget.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanRenderSystem.h"
#include "VulkanFrame.h"
#include "VulkanTools.h"

namespace Ogre
{

	VulkanRenderTarget::VulkanRenderTarget(const String& name, TextureProperty&texProperty)
	{
		mScreen = false;
		mName = name;
		mTarget = new VulkanTexture(name, &texProperty, nullptr);
		mTarget->load(nullptr);
		mWidth = mTarget->getWidth();
		mHeight = mTarget->getHeight();
	}

	VulkanRenderTarget::VulkanRenderTarget(uint32_t width, uint32_t height, bool screen)
	{
		mWidth = width;
		mHeight = height;
		mScreen = screen;
	}

	VulkanRenderTarget::~VulkanRenderTarget()
	{

	}

	void VulkanRenderTarget::preRender(const ColourValue& colour)
	{
		/*VulkanRenderSystem* rs = VulkanHelper::getSingleton()._getRenderSystem();
		auto width = mTarget->getWidth();
		auto height = mTarget->getHeight();
		auto* frame = rs->_getCurrentFrame();

		auto frame_index = frame->getFrameIndex();

		auto renderPass = VulkanHelper::getSingleton()._getRenderPass();
		auto framebuffer = getFrameBuffer(frame_index);

		VkViewport viewport = vks::initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
		VkRect2D scissor = vks::initializers::rect2D(width, height, 0, 0);

		VkClearValue clearValues[3];

		auto& settings = VulkanHelper::getSingleton().getVulkanSettings();
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



		VkRenderPassBeginInfo renderPassBeginInfo = vks::initializers::renderPassBeginInfo();
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent.width = width;
		renderPassBeginInfo.renderArea.extent.height = height;
		renderPassBeginInfo.clearValueCount = settings.multiSampling ? 3 : 2;
		renderPassBeginInfo.pClearValues = clearValues;
		renderPassBeginInfo.framebuffer = framebuffer;
		VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frame_index);


		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = 1;
		subresourceRange.layerCount = 1;
		vks::tools::setImageLayout(
			commandBuffer,
			mTarget->getVkImage(),
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			subresourceRange);

		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);*/
	}

	void VulkanRenderTarget::postRender()
	{
		auto currentFrame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
		VkCommandBuffer pCommandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(currentFrame->getFrameIndex());

		vkCmdEndRenderPass(pCommandBuffer);

		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = 1;
		subresourceRange.layerCount = 1;

		vks::tools::setImageLayout(
			pCommandBuffer,
			mTarget->getVkImage(),
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			subresourceRange);
	}

	VkImageView VulkanRenderTarget::getImageView()
	{
		if (mScreen)
		{
			VulkanFrame* frame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
			auto frameIndex = frame->getFrameIndex();

			auto swapchain = VulkanHelper::getSingleton().getSwapchainBuffer();

			return swapchain[frameIndex]._view;
		}
		else
		{
			return mTarget->getVkImageView();
		}
	}

	VkImage VulkanRenderTarget::getImage()
	{
		if (mScreen)
		{
			VulkanFrame* frame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
			auto frameIndex = frame->getFrameIndex();

			auto swapchain = VulkanHelper::getSingleton().getSwapchainBuffer();

			return swapchain[frameIndex]._image;
		}
		else
		{
			return mTarget->getVkImage();
		}
	}

	Ogre::OgreTexture* VulkanRenderTarget::getTarget()
	{
		return mTarget;
	}
}