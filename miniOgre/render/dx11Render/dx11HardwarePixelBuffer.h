#pragma once
#include "dx11Common.h"
#include "OgreHardwarePixelBuffer.h"

class Dx11Texture;

class Dx11HardwarePixelBuffer : public Ogre::HardwarePixelBuffer
{
public:
	Dx11HardwarePixelBuffer(
		Dx11Texture* parentTexture,
		UINT mipLevel,
		size_t width, 
		size_t height, 
		size_t depth, 
		UINT face, 
		PixelFormat format, 
		HardwareBuffer::Usage usage);
	~Dx11HardwarePixelBuffer();

	virtual void blitFromMemory(const PixelBox& src, const Box& dstBox);
	virtual void blitToMemory(const Box& srcBox, const PixelBox& dst);
	virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
	virtual void unlock();

	Dx11Texture* getParentTexture()
	{
		return mParentTexture;
	}

	D3D11_BOX getSubresourceBox(const Box& inBox) const;
	UINT getSubresourceIndex(size_t box_front) const;
private:
	void _genMipmaps();
	void createStagingBuffer();
	void _map(
		ID3D11Resource* res,
		D3D11_MAP flags,
		PixelBox& box);
	void _unmap(ID3D11Resource* res);
private:
	Dx11Texture* mParentTexture;

	const uint32_t mFace;
	const uint32_t mMipLevel;

	Microsoft::WRL::ComPtr<ID3D11Resource> mStagingBuffer;

};