#pragma once
#include "VulkanCommon.h"
class VulkanRenderTarget
{
public:
	VulkanRenderTarget
	(
	);
	~VulkanRenderTarget();

	virtual void preRender(VkCommandBuffer commandBuffer) = 0;

	virtual VkFramebuffer getFrameBuffer(uint32_t index) = 0;

	virtual uint32_t getTargetWidth() = 0;
	virtual uint32_t getTargetHeight() = 0;
};