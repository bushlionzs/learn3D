#include "OgreHeader.h"
#include "VulkanRenderTexture.h"
#include "VulkanHardwarePixelBuffer.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanFrame.h"
#include "VulkanRenderSystem.h"
#include "VulkanTools.h"

VulkanRenderTexture::VulkanRenderTexture(
	const String& name,
	VulkanHardwarePixelBuffer* buffer,
	uint32_t zoffset)
	:RenderTexture(buffer, zoffset)
{
	mParentTexture = buffer->getParentTexture();

	mFramebuffer = nullptr;
}

VulkanRenderTexture::~VulkanRenderTexture()
{

}

void VulkanRenderTexture::copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer)
{

}

bool VulkanRenderTexture::requiresTextureFlipping() const
{
	return false;
}

void VulkanRenderTexture::preRender(VkCommandBuffer commandBuffer)
{
	auto currentFrame = VulkanHelper::getSingleton()._getRenderSystem()->_getCurrentFrame();
	VkCommandBuffer pCommandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(currentFrame->getFrameIndex());
	VkViewport viewport = vks::initializers::viewport((float)mWidth, (float)mHeight, 0.0f, 1.0f);

	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor = vks::initializers::rect2D(mWidth, mHeight, 0, 0);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = 1;
	subresourceRange.layerCount = 1;

	vks::tools::setImageLayout(
		pCommandBuffer,
		mParentTexture->getImage(),
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		subresourceRange);
}

void VulkanRenderTexture::swapBuffers()
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
		mParentTexture->getImage(),
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		subresourceRange);
}

VkFramebuffer VulkanRenderTexture::getFrameBuffer(uint32_t index)
{
	if (mFramebuffer == nullptr)
	{

		mDepthStencil = VulkanHelper::getSingleton().createDepthStencil(
			mParentTexture->getWidth(), mParentTexture->getHeight()
		);
		VkImageView attachments[2];
		attachments[0] = mParentTexture->getImageView();
		attachments[1] = mDepthStencil._view;

		
		auto renderPass = VulkanHelper::getSingleton()._getRenderPass();
		VkFramebufferCreateInfo framebufferCreateInfo = {};
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass = renderPass;
		framebufferCreateInfo.attachmentCount = 2;
		framebufferCreateInfo.pAttachments = attachments;
		framebufferCreateInfo.width = mParentTexture->getWidth();
		framebufferCreateInfo.height = mParentTexture->getHeight();
		framebufferCreateInfo.layers = 1;

		auto device = VulkanHelper::getSingleton()._getVkDevice();
		vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &mFramebuffer);
	}
	
	return mFramebuffer;
}

uint32_t VulkanRenderTexture::getTargetWidth()
{
	return mBuffer->getWidth();
}

uint32_t VulkanRenderTexture::getTargetHeight()
{
	return mBuffer->getHeight();
}