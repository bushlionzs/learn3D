#include "OgreHeader.h"
#include "dx11ShadowMap.h"
#include "dx11Helper.h"

Dx11ShadowMap::Dx11ShadowMap(uint32_t width, uint32_t height)
{
	mWidth = width;
	mHeight = height;
}

Dx11ShadowMap::~Dx11ShadowMap()
{

}

void Dx11ShadowMap::buildResource()
{
	D3D11_TEXTURE2D_DESC depthTextureDesc;
	ZeroMemory(&depthTextureDesc, sizeof(depthTextureDesc));
	depthTextureDesc.Width = mWidth;
	depthTextureDesc.Height = mHeight;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.MiscFlags = 0;
	auto device = DX11Helper::getSingleton().getDevice();

	auto hr = device->CreateTexture2D(&depthTextureDesc,
		0, mDepthTexture.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateTexture2D failed!");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(mDepthTexture.Get(),
		&depthStencilViewDesc, mDepthStencilView.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "CreateTexture2D failed!");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC depthShaderResourceViewDesc;
	ZeroMemory(&depthShaderResourceViewDesc, sizeof(depthShaderResourceViewDesc));
	depthShaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	depthShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	depthShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	depthShaderResourceViewDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(mDepthTexture.Get(),
		&depthShaderResourceViewDesc,
		mTextureView.ReleaseAndGetAddressOf()
	);
}

void Dx11ShadowMap::checkTextureData()
{
	/*D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));
	auto context = DX11Helper::getSingleton().getDeviceContext();
	auto hr = context->Map(mDepthTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	char* data = (char*)mappedResource.pData;
	context->Unmap(mDepthTexture.Get(), 0);*/
}