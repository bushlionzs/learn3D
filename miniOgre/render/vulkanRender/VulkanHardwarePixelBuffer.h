#pragma once

#include "OgreHardwarePixelBuffer.h"
#include "OgreCommon.h"

class VulkanTexture;

class VulkanHardwarePixelBuffer : public Ogre::HardwarePixelBuffer
{
public:
	VulkanHardwarePixelBuffer(
		VulkanTexture* parentTexture,
		UINT mipLevel,
		size_t width,
		size_t height,
		size_t depth,
		UINT face,
		PixelFormat format,
		HardwareBuffer::Usage usage);
	~VulkanHardwarePixelBuffer();

	virtual void blitFromMemory(const PixelBox& src, const Box& dstBox);
	virtual void blitToMemory(const Box& srcBox, const PixelBox& dst);
	virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
	virtual void unlock();

	VulkanTexture* getParentTexture()
	{
		return mParentTexture;
	}

	void uploadData();

private:
	VulkanTexture* mParentTexture;

	const uint32_t mFace;
	const uint32_t mMipLevel;
};