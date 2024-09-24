#pragma once
#include "VulkanCommon.h"
#include "OgreRenderTarget.h"
#include "OgreTexture.h"

class VulkanTexture;
namespace Ogre
{
	class VulkanRenderTarget: public Ogre::RenderTarget
	{
	public:
		VulkanRenderTarget(const String&name, TextureProperty& texProperty);
		VulkanRenderTarget(uint32_t width, uint32_t height, bool screen);
		~VulkanRenderTarget();

		virtual void preRender(const ColourValue& colour) override;
		virtual void postRender() override;

		VkImageView getImageView();
		VkImage getImage();

	private:
		VkFramebuffer getFrameBuffer(uint32_t index);
	private:
		VulkanTexture* mTarget = nullptr;
		VulkanTexture* mDepth = nullptr;
		VkFramebuffer mFramebuffer = nullptr;
		MultisampleTarget mMultisampleTarget;
		bool mScreen;
	};
}
