#pragma once

#include "OgreHardwarePixelBuffer.h"
#include "d3dutil.h"
class Dx12Texture;

class Dx12HardwarePixelBuffer : public Ogre::HardwarePixelBuffer
{
public:
	Dx12HardwarePixelBuffer(
		Dx12Texture* parentTexture,
		UINT mipLevel,
		size_t width, 
		size_t height, 
		size_t depth, 
		UINT face, 
		PixelFormat format, 
		HardwareBuffer::Usage usage);
	~Dx12HardwarePixelBuffer();

	virtual void blitFromMemory(const PixelBox& src, const Box& dstBox);
	virtual void blitToMemory(const Box& srcBox, const PixelBox& dst);
	virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
	virtual void unlock();

	Dx12Texture* getParentTexture() const 
	{
		return mParentTexture;
	}

	ID3D12Resource* getGpuBuffer() const
	{
		return mBufferGPU.Get();
	}

	void uploadData();
private:
	Dx12Texture* mParentTexture;

	const uint32_t mFace;
	const uint32_t mMipLevel;

	String mBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> mBufferGPU = nullptr;
};