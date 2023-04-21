#include "OgreHeader.h"
#include "dx11HardwarePixelBuffer.h"
#include "texture.h"
#include "OgreStringConverter.h"
#include "dx11Texture.h"
#include "dx11RenderSystem.h"
#include "dx11Helper.h"
#include "dx11RenderTexture.h"

Dx11HardwarePixelBuffer::Dx11HardwarePixelBuffer(
	Dx11Texture* parentTexture,
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

			RenderTexture* trt = new Dx11RenderTexture(name, this, zoffset);
			mSliceTRT.push_back(trt);
			DX11Helper::getSingleton().getRenderSystem()->attachRenderTarget(*trt);
		}
	}
}

Dx11HardwarePixelBuffer::~Dx11HardwarePixelBuffer()
{

}

void Dx11HardwarePixelBuffer::blitFromMemory(const PixelBox& src, const Box& dst)
{
    Vector3i srcSize(src.getWidth(), src.getHeight(), src.getDepth());
    Vector3i dstSize(dst.getWidth(), dst.getHeight(), dst.getDepth());
    if (srcSize != dstSize)
    {
        OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
            "D3D12 device cannot copy a subresource - source and dest size are not the same and they have to be the same in DX12.",
            "D3D12HardwarePixelBuffer::blitFromMemory");
    }

	if (src.format != mFormat)
	{
		std::vector<uint8> buffer;
		buffer.resize(PixelUtil::getMemorySize(src.getWidth(), src.getHeight(), src.getDepth(), mFormat));
		PixelBox converted = PixelBox(src.getWidth(), src.getHeight(), src.getDepth(), mFormat, buffer.data());
		PixelUtil::bulkPixelConversion(src, converted);
		blitFromMemory(converted, dst); // recursive call
		return;
	}

	D3D11_BOX dstBox = getSubresourceBox(dst);
	UINT dstSubresource = getSubresourceIndex(dst.front);
	UINT srcRowPitch = PixelUtil::getMemorySize(src.getWidth(), 1, 1, src.format);
	UINT srcDepthPitch = PixelUtil::getMemorySize(src.getWidth(), src.getHeight(), 1, src.format); // H * rowPitch is invalid for compressed formats

	auto deviceContext = DX11Helper::getSingleton().getDeviceContext();
	deviceContext->UpdateSubresource(
		mParentTexture->getTextureResource(), dstSubresource, &dstBox,
		src.getTopLeftFrontPixelPtr(), srcRowPitch, srcDepthPitch);
	_genMipmaps();
}

void Dx11HardwarePixelBuffer::blitToMemory(const Box& srcBox, const PixelBox& dst)
{
    assert(false);
}

void* Dx11HardwarePixelBuffer::lockimpl(size_t offset, size_t length, LockOptions options)
{
	return nullptr;
}

void Dx11HardwarePixelBuffer::unlock()
{

}

D3D11_BOX Dx11HardwarePixelBuffer::getSubresourceBox(const Box& inBox) const
{
	// Ogre index Tex2DArray using Z component of the box, but Direct3D expect 
	// this index to be in subresource, and Z component should be sanitized
	bool is2DArray = (mParentTexture->getTextureType() == TEX_TYPE_2D_ARRAY);

	D3D11_BOX res;
	res.left = static_cast<UINT>(inBox.left);
	res.top = static_cast<UINT>(inBox.top);
	res.front = is2DArray ? 0 : static_cast<UINT>(inBox.front);
	res.right = static_cast<UINT>(inBox.right);
	res.bottom = static_cast<UINT>(inBox.bottom);
	res.back = is2DArray ? 1 : static_cast<UINT>(inBox.back);
	return res;
}

UINT Dx11HardwarePixelBuffer::getSubresourceIndex(size_t box_front) const
{
	switch (mParentTexture->getTextureType())
	{
	case TEX_TYPE_CUBE_MAP: 
		return D3D11CalcSubresource(
			mMipLevel, mFace, mParentTexture->getNumMipmaps() + 1);
	case TEX_TYPE_2D_ARRAY: 
		return D3D11CalcSubresource(mMipLevel, box_front, mParentTexture->getNumMipmaps() + 1);
	}
	return mMipLevel;
}

void Dx11HardwarePixelBuffer::_genMipmaps()
{
	if (mParentTexture->hasAutoMipMapGenerationEnabled())
	{
		ID3D11ShaderResourceView* pShaderResourceView = mParentTexture->getResourceView();
		ID3D11DeviceContext* context = DX11Helper::getSingleton().getDeviceContext();
		context->GenerateMips(pShaderResourceView);
	}
}