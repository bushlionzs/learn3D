#pragma once

#include "OgreRenderTexture.h"
#include "OgreRenderTarget.h"
#include "VulkanRenderTarget.h"
class VulkanHardwarePixelBuffer;
class VulkanRenderSystem;
class VulkanTexture;

class VulkanRenderTexture : public Ogre::RenderTexture,
	public VulkanRenderTarget
{
public:
	VulkanRenderTexture(
		const String& name,
		VulkanHardwarePixelBuffer* buffer,
		uint32_t zoffset);
	~VulkanRenderTexture();

	virtual void copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer = FB_AUTO);

	virtual bool requiresTextureFlipping() const;

	virtual void preRender(VulkanFrame* frame, const ColourValue& colour);

	virtual bool offset() { return true; }

	virtual void swapBuffers();
	virtual VkFramebuffer getFrameBuffer(uint32_t index);
	virtual uint32_t getTargetWidth();
	virtual uint32_t getTargetHeight();

private:
	VulkanTexture* mParentTexture;

	VkFramebuffer mFramebuffer;

	VulkanDepthStencil mDepthStencil;
};