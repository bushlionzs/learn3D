#include "OgreHeader.h"
#include "dx11RenderTexture.h"
#include "dx11HardwarePixelBuffer.h"
#include "dx11Helper.h"
#include "dx11Texture.h"

Dx11RenderTexture::Dx11RenderTexture(
	const String& name,
	Dx11HardwarePixelBuffer* buffer,
	uint32_t zoffset)
	:RenderTexture(buffer, zoffset)
{
	mViewport = { 0.0f, 0.0f, (float)mWidth, (float)mHeight, 0.0f, 1.0f };
	rebind(buffer);
}

Dx11RenderTexture::~Dx11RenderTexture()
{

}

void Dx11RenderTexture::rebind(Dx11HardwarePixelBuffer* buffer)
{
	mBuffer = buffer;
	mWidth = mBuffer->getWidth();
	mHeight = mBuffer->getHeight();

	mParentTexture = buffer->getParentTexture();

	auto device = DX11Helper::getSingleton().getDevice();

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	rtvDesc.Format = mParentTexture->getD3dFormat();
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	auto hr = device->CreateRenderTargetView(
		mParentTexture->getTexture(), &rtvDesc, &mRenderTargetView);

	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateRenderTargetView failed!");
	}

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mWidth;
	depthStencilDesc.Height = mHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateTexture2D failed!");
	}

	hr = device->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView);
	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateTexture2D failed!");
	}
}

void Dx11RenderTexture::copyContentsToMemory(
	const Box& src,
	const PixelBox& dst,
	FrameBuffer buffer)
{

}

bool Dx11RenderTexture::requiresTextureFlipping() const
{
	return false;
}

void Dx11RenderTexture::preRender()
{
	auto deviceContext = DX11Helper::getSingleton().getDeviceContext();
	deviceContext->RSSetViewports(1, &mViewport);
	
}

void Dx11RenderTexture::swapBuffers()
{
	auto context = DX11Helper::getSingleton().getDeviceContext();
	ID3D11RenderTargetView* pRTV = nullptr;
	context->OMSetRenderTargets(1, &pRTV, nullptr);
}

ID3D11RenderTargetView* Dx11RenderTexture::getRenderTargetView() const
{
	return mRenderTargetView;
}

ID3D11DepthStencilView* Dx11RenderTexture::getDepthStencilView() const
{
	return mDepthStencilView;
}

void Dx11RenderTexture::clearFrameBuffer(uint32_t buffers,
	const Ogre::ColourValue& colour,
	float depth, uint16_t stencil)
{
	auto context = DX11Helper::getSingleton().getDeviceContext();
	auto renderTargetView = getRenderTargetView();
	auto depthStencilView = getDepthStencilView();
	
	context->ClearRenderTargetView(renderTargetView, colour.ptr());

	context->ClearDepthStencilView(depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

}