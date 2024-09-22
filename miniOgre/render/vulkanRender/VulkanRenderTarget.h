#pragma once
#include "VulkanCommon.h"
#include "OgreRenderTarget.h"

class VulkanFrame;
namespace Ogre
{
	class VulkanRenderTarget: public Ogre::RenderTarget
	{
	public:
		VulkanRenderTarget
		(
		);
		~VulkanRenderTarget();

		virtual void preRender(VulkanFrame* frame, const ColourValue& colour)
		{
			int kk = 0;
		}

		virtual bool offset() { return false; }

		virtual VkFramebuffer getFrameBuffer(uint32_t index) = 0;

		virtual uint32_t getTargetWidth() = 0;
		virtual uint32_t getTargetHeight() = 0;
	};
}
