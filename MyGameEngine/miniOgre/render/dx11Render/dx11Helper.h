#pragma once

#include "OgreSingleton.h"
#include "dx11Common.h"
#include "OgreBlendMode.h"


class Dx11RenderSystem;


class DX11Helper : public Ogre::Singleton<DX11Helper>
{
public:
	DX11Helper(Dx11RenderSystem* rs);
	~DX11Helper();

	void _initialise();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void updateRenderState();

	void _setColourBlendState(const ColourBlendState& state);
	void _setDepthBufferWriteEnabled(bool enabled);
private:
	void buildStaticSample();
private:
	HWND m_hWnd;
	int32_t mWidth = 0;
	int32_t mHeight = 0;
	ID3D11Device* mDx11Device = nullptr;
	ID3D11DeviceContext* mDx11Context = nullptr;
	IDXGISwapChain* mSwapChain = nullptr;
	Dx11RenderSystem* mRenderSystem;


	D3D11_BLEND_DESC    mBlendDesc;
	bool                mBlendDescChanged;

	D3D11_RASTERIZER_DESC   mRasterizerDesc;
	bool                    mRasterizerDescChanged;

	UINT mStencilRef;
	D3D11_DEPTH_STENCIL_DESC    mDepthStencilDesc;
	bool                        mDepthStencilDescChanged;

	Microsoft::WRL::ComPtr<ID3D11BlendState> mBlendState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState;

	Microsoft::WRL::ComPtr<ID3D11BlendState> mBoundBlendState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mBoundRasterizer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mBoundDepthStencilState;

	std::vector<ID3D11SamplerState*> mSamplerStates;
};