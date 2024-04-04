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

void VulkanRenderTexture::preRender(VulkanFrame* frame, const ColourValue& colour)
{
	auto width = getTargetWidth();
	auto height = getTargetHeight();
	

	auto frame_index = frame->getFrameIndex();


	auto renderPass = VulkanHelper::getSingleton()._getRenderPass();

	

	auto framebuffer = getFrameBuffer(frame_index);

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


	/*VkCommandBuffer copyCmd = VulkanHelper::getSingleton().createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
	 vks::tools::setImageLayout(
		 copyCmd,
			mParentTexture->getImage(),
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		 VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });*/

	VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frame_index);
	
	
	VkImageSubresourceRange subresourceRange = {};
	subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subresourceRange.baseMipLevel = 0;
	subresourceRange.levelCount = 1;
	subresourceRange.layerCount = 1;
	vks::tools::setImageLayout(
		commandBuffer,
		mParentTexture->getImage(),
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		subresourceRange);

	vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
	
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
		attachments[1] = mDepthStencil.view;

		
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