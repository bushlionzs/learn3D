#pragma once
#include "VulkanCommon.h"
class VulkanFrame;
namespace Ogre
{
	class VulkanRenderTarget
	{
	public:
		VulkanRenderTarget
		(
		);
		~VulkanRenderTarget();

		virtual void preRender(VulkanFrame* frame, const ColourValue& colour) = 0;

		virtual bool offset() { return false; }

		virtual VkFramebuffer getFrameBuffer(uint32_t index) = 0;

		virtual uint32_t getTargetWidth() = 0;
		virtual uint32_t getTargetHeight() = 0;
	};
}
