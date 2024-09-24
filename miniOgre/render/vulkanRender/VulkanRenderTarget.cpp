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

	VkFramebuffer VulkanRenderTarget::getFrameBuffer(uint32_t index)
	{
		return mFramebuffer;
		//if (mFramebuffer == nullptr)
		//{
		//	VulkanHelper& helper = VulkanHelper::getSingleton();

		//	auto renderPass = helper._getRenderPass();
		//	VkImageView attachments[4] = {};
		//	const auto& settings = VulkanHelper::getSingleton().getVulkanSettings();

		//	auto device = helper._getVkDevice();
		//	if (settings.multiSampling)
		//	{
		//		// Check if device supports requested sample count for color and depth frame buffer
		//		//assert((deviceProperties.limits.framebufferColorSampleCounts >= sampleCount) && (deviceProperties.limits.framebufferDepthSampleCounts >= sampleCount));

		//		VkImageCreateInfo imageCI{};
		//		imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		//		imageCI.imageType = VK_IMAGE_TYPE_2D;
		//		imageCI.format = helper.getSwapChainImageFormat();
		//		imageCI.extent = { mWidth, mHeight, 1 };
		//		imageCI.mipLevels = 1;
		//		imageCI.arrayLayers = 1;
		//		imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		//		imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
		//		imageCI.samples = settings.sampleCount;
		//		imageCI.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		//		imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		//		VK_CHECK_RESULT(vkCreateImage(device, &imageCI, nullptr, &mMultisampleTarget.color.image));

		//		VkMemoryRequirements memReqs;
		//		vkGetImageMemoryRequirements(device, mMultisampleTarget.color.image, &memReqs);
		//		VkMemoryAllocateInfo memAllocInfo{};
		//		memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		//		memAllocInfo.allocationSize = memReqs.size;

		//		memAllocInfo.memoryTypeIndex = helper._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		//		vkAllocateMemory(device, &memAllocInfo, nullptr, &mMultisampleTarget.color.memory);
		//		vkBindImageMemory(device, mMultisampleTarget.color.image, mMultisampleTarget.color.memory, 0);

		//		// Create image view for the MSAA target
		//		VkImageViewCreateInfo imageViewCI{};
		//		imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		//		imageViewCI.image = mMultisampleTarget.color.image;
		//		imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
		//		imageViewCI.format = helper.getSwapChainImageFormat();
		//		imageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
		//		imageViewCI.components.g = VK_COMPONENT_SWIZZLE_G;
		//		imageViewCI.components.b = VK_COMPONENT_SWIZZLE_B;
		//		imageViewCI.components.a = VK_COMPONENT_SWIZZLE_A;
		//		imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		//		imageViewCI.subresourceRange.levelCount = 1;
		//		imageViewCI.subresourceRange.layerCount = 1;
		//		vkCreateImageView(device, &imageViewCI, nullptr, &mMultisampleTarget.color.view);

		//		// Depth target
		//		imageCI.imageType = VK_IMAGE_TYPE_2D;
		//		imageCI.format = helper._getDepthFormat();
		//		imageCI.extent = { mWidth, mHeight, 1 };
		//		imageCI.mipLevels = 1;
		//		imageCI.arrayLayers = 1;
		//		imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		//		imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
		//		imageCI.samples = settings.sampleCount;
		//		imageCI.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		//		imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		//		vkCreateImage(device, &imageCI, nullptr, &mMultisampleTarget.depth.image);

		//		vkGetImageMemoryRequirements(device, mMultisampleTarget.depth.image, &memReqs);
		//		memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		//		memAllocInfo.allocationSize = memReqs.size;
		//		memAllocInfo.memoryTypeIndex = helper._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		//		VK_CHECK_RESULT(vkAllocateMemory(device, &memAllocInfo, nullptr, &mMultisampleTarget.depth.memory));
		//		vkBindImageMemory(device, mMultisampleTarget.depth.image, mMultisampleTarget.depth.memory, 0);

		//		// Create image view for the MSAA target
		//		imageViewCI.image = mMultisampleTarget.depth.image;
		//		imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
		//		imageViewCI.format = helper._getDepthFormat();
		//		imageViewCI.components.r = VK_COMPONENT_SWIZZLE_R;
		//		imageViewCI.components.g = VK_COMPONENT_SWIZZLE_G;
		//		imageViewCI.components.b = VK_COMPONENT_SWIZZLE_B;
		//		imageViewCI.components.a = VK_COMPONENT_SWIZZLE_A;
		//		imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		//		imageViewCI.subresourceRange.levelCount = 1;
		//		imageViewCI.subresourceRange.layerCount = 1;
		//		VK_CHECK_RESULT(vkCreateImageView(device, &imageViewCI, nullptr, &mMultisampleTarget.depth.view));
		//	}

		//	if (settings.multiSampling)
		//	{
		//		attachments[0] = mMultisampleTarget.color.view;
		//		attachments[2] = mMultisampleTarget.depth.view;
		//		attachments[3] = mDepth->getVkImageView();
		//	}
		//	else {
		//		attachments[1] = mDepth->getVkImageView();
		//	}

		//	VkFramebufferCreateInfo frameBufferCreateInfo = {};
		//	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		//	frameBufferCreateInfo.pNext = NULL;
		//	frameBufferCreateInfo.renderPass = renderPass;
		//	frameBufferCreateInfo.attachmentCount = settings.multiSampling ? 4 : 2;
		//	frameBufferCreateInfo.pAttachments = attachments;
		//	frameBufferCreateInfo.width = mWidth;
		//	frameBufferCreateInfo.height = mHeight;
		//	frameBufferCreateInfo.layers = 1;


		//	if (settings.multiSampling)
		//	{
		//		attachments[1] = mTarget->getVkImageView();
		//	}
		//	else {
		//		attachments[0] = mTarget->getVkImageView();
		//	}

		//	VK_CHECK_RESULT(vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &mFramebuffer));
		//}

		return mFramebuffer;
	}
}