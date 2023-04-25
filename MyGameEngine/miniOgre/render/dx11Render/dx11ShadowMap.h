#pragma once
#include "dx11Common.h"
class Dx11ShadowMap
{
public:
public:
	Dx11ShadowMap(
		uint32_t width,
		uint32_t height);
	~Dx11ShadowMap();

	void buildResource();

	ID3D11DepthStencilView* getDepthStencilView()
	{
		return mDepthStencilView.Get();
	}

	ID3D11ShaderResourceView* getResource()
	{
		return mTextureView.Get();
	}

	void checkTextureData();
private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTextureView;
	uint32_t mWidth;
	uint32_t mHeight;
};