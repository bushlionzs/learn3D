#include "OgreHeader.h"
#include "VulkanHardwarePixelBuffer.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "OgreStringConverter.h"
#include "VulkanRenderTexture.h"
#include "VulkanRenderSystem.h"

VulkanHardwarePixelBuffer::VulkanHardwarePixelBuffer(
	VulkanTexture* parentTexture,
	UINT mipLevel,
	size_t width,
	size_t height,
	size_t depth,
	UINT face,
	PixelFormat format,
	HardwareBuffer::Usage usage)
	:HardwarePixelBuffer(width, height, depth, format, usage, false, false),
	mParentTexture(parentTexture),
	mFace(face),
	mMipLevel(mipLevel)
{
	mUsage = usage;

	if (mUsage & Ogre::TU_RENDERTARGET)
	{
		// Create render target for each slice
		mSliceTRT.reserve(mDepth);
		for (size_t zoffset = 0; zoffset < mDepth; ++zoffset)
		{
			String name;
			name = "rtt/" + StringConverter::toString((size_t)this) + "/" + parentTexture->getName();

			RenderTexture* trt = new VulkanRenderTexture(name, this, zoffset);
			mSliceTRT.push_back(trt);
			VulkanHelper::getSingleton()._getRenderSystem()->attachRenderTarget(*trt);
		}
	}

	mSizeInBytes = PixelUtil::getMemorySize(width, height, depth, format);
	
}

VulkanHardwarePixelBuffer::~VulkanHardwarePixelBuffer()
{

}

void VulkanHardwarePixelBuffer::blitFromMemory(const PixelBox& src, const Box& dst)
{
	Vector3i srcSize(src.getWidth(), src.getHeight(), src.getDepth());
	Vector3i dstSize(dst.getWidth(), dst.getHeight(), dst.getDepth());
	if (srcSize != dstSize)
	{
		OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
			"Vulkan device cannot copy a subresource - source and dest size are not the same and they have to be the same in Vulkan.",
			"VulkanHardwarePixelBuffer::blitFromMemory");
	}

	void* data = mParentTexture->getVulkanBuffer(mFace, mMipLevel);
	PixelBox dstBox = PixelBox(src.getWidth(), src.getHeight(),
		src.getDepth(), mFormat, data);
	PixelUtil::bulkPixelConversion(src, dstBox);
}

void VulkanHardwarePixelBuffer::blitToMemory(
	const Box& srcBox, const PixelBox& dst)
{

}

void* VulkanHardwarePixelBuffer::lockimpl(
	size_t offset, size_t length, LockOptions options)
{
	return mParentTexture->getVulkanBuffer(mFace, mMipLevel);
}

void VulkanHardwarePixelBuffer::unlock()
{
	
}

void VulkanHardwarePixelBuffer::uploadData()
{
}