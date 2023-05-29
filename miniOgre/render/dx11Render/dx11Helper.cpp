#include "OgreHeader.h"
#include "dx11Helper.h"
#include "dx11RenderSystem.h"
#include "OgreD3D11Mappings.h"

template<> DX11Helper* Ogre::Singleton<DX11Helper>::msSingleton = 0;

DX11Helper::DX11Helper(Dx11RenderSystem* rs)
{
	mRenderSystem = rs;
}

DX11Helper::~DX11Helper()
{

}

void DX11Helper::_initialise()
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&mDx11Device,
		&featureLevel,
		&mDx11Context);

	if (FAILED(hr))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "D3D11CreateDevice failed!");
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "D3D_FEATURE_LEVEL_11_0 failed!");
	}

	UINT      m4xMsaaQuality;
	mDx11Device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);


	ZeroMemory(&mRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	mRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	mRasterizerDesc.CullMode = D3D11_CULL_BACK;
	mRasterizerDesc.FrontCounterClockwise = true;
	mRasterizerDesc.DepthClipEnable = true;
	mRasterizerDescChanged = true;

	ZeroMemory(&mBlendDesc, sizeof(D3D11_BLEND_DESC));
	mBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	mBlendDescChanged = true;

	ZeroMemory(&mDepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	mDepthStencilDescChanged = true;
	mDepthStencilDesc.DepthEnable = true;
	mDepthStencilDesc.StencilEnable = false;
	mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	mDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	buildStaticSample();

	updateRenderState();
}


void DX11Helper::buildStaticSample()
{
	ID3D11SamplerState* samplerStatePointWrap;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));

	auto comFunc = D3D11_COMPARISON_GREATER_EQUAL;
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStatePointWrap);
	//
	ID3D11SamplerState* samplerStatePointClamp;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStatePointClamp);
	//
	ID3D11SamplerState* samplerStateLinearWrap;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStateLinearWrap);
	//
	ID3D11SamplerState* samplerStateLinearClamp;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStateLinearClamp);
	//
	ID3D11SamplerState* samplerStateAnisotropicWrap;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStateAnisotropicWrap);
	//
	ID3D11SamplerState* samplerStateAnisotropicClamp;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = comFunc;
	sampDesc.MaxAnisotropy = 4;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStateAnisotropicClamp);

	ID3D11SamplerState* samplerStateShadow;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	sampDesc.MaxAnisotropy = 16;
	sampDesc.MinLOD = 0.0f;
	sampDesc.MaxLOD = 0.0f;
	sampDesc.BorderColor[0] = 1.0f;
	sampDesc.BorderColor[1] = 1.0f;
	sampDesc.BorderColor[2] = 1.0f;
	sampDesc.BorderColor[3] = 1.0f;
	mDx11Device->CreateSamplerState(&sampDesc, &samplerStateShadow);

	mSamplerStates =
	{
		samplerStatePointWrap,
		samplerStatePointClamp,
		samplerStateLinearWrap,
		samplerStateLinearClamp,
		samplerStateAnisotropicWrap,
		samplerStateAnisotropicClamp,
		samplerStateShadow
	};

	mDx11Context->PSSetSamplers(0, mSamplerStates.size(), mSamplerStates.data());
}

ID3D11Device* DX11Helper::getDevice()
{
	return mDx11Device;
}

ID3D11DeviceContext* DX11Helper::getDeviceContext()
{
	return mDx11Context;
}

void DX11Helper::updateRenderState()
{
	if (mBlendDescChanged)
	{
		mBlendDescChanged = false;
		mDx11Device->CreateBlendState(&mBlendDesc, 
			mBlendState.ReleaseAndGetAddressOf());
	}
	else
	{
		mBlendState = mBoundBlendState;
	}

	if (mRasterizerDescChanged)
	{
		mRasterizerDescChanged = false;
		mDx11Device->CreateRasterizerState(&mRasterizerDesc,
			mRasterizerState.ReleaseAndGetAddressOf());
	}
	else
	{
		mRasterizerState = mBoundRasterizer;
	}

	if (mDepthStencilDescChanged)
	{
		mDepthStencilDescChanged = false;
		mDx11Device->CreateDepthStencilState(&mDepthStencilDesc,
			mDepthStencilState.ReleaseAndGetAddressOf());
	}
	else
	{
		mDepthStencilState = mBoundDepthStencilState;
	}

	if (mBoundBlendState != mBlendState)
	{
		mBoundBlendState = mBlendState;
		mDx11Context->OMSetBlendState(mBoundBlendState.Get(), 0, 0xffffffff);
	}

	if (mBoundRasterizer != mRasterizerState)
	{
		mBoundRasterizer = mRasterizerState;
		mDx11Context->RSSetState(mBoundRasterizer.Get());
	}

	if (mDepthStencilState != mBoundDepthStencilState)
	{
		mBoundDepthStencilState = mDepthStencilState;
		mDx11Context->OMSetDepthStencilState(mBoundDepthStencilState.Get(), mStencilRef);
	}
}

void DX11Helper::_setColourBlendState(const ColourBlendState& state)
{
	if (state.blendingEnabled())
	{
		mBlendDesc.RenderTarget[0].BlendEnable = TRUE;
		mBlendDesc.RenderTarget[0].SrcBlend = D3D11Mappings::get(state.sourceFactor, false);
		mBlendDesc.RenderTarget[0].DestBlend = D3D11Mappings::get(state.destFactor, false);
		mBlendDesc.RenderTarget[0].BlendOp = D3D11Mappings::get(state.operation);
		mBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11Mappings::get(state.sourceFactorAlpha, true);
		mBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11Mappings::get(state.destFactorAlpha, true);
		mBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11Mappings::get(state.alphaOperation);
		mBlendDesc.AlphaToCoverageEnable = false;

		mBlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;
	}
	else
	{
		if (!mBlendDesc.RenderTarget[0].BlendEnable)
		{
			return;
		}
		mBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	}

	mBlendDescChanged = true;
}

void DX11Helper::_setDepthBufferWriteEnabled(bool enabled)
{
	if (enabled)
	{
		if (mDepthStencilDesc.DepthWriteMask == D3D11_DEPTH_WRITE_MASK_ALL)
		{
			return;
		}
		mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	}
	else
	{
		if (mDepthStencilDesc.DepthWriteMask == D3D11_DEPTH_WRITE_MASK_ZERO)
		{
			return;
		}
		mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	}
	mDepthStencilDescChanged = true;
}

void DX11Helper::_setCullingMode(Ogre::CullingMode mode)
{
	D3D11_CULL_MODE d3dmode = D3D11Mappings::get(mode);

	if (d3dmode != mRasterizerDesc.CullMode)
	{
		mRasterizerDesc.CullMode = d3dmode;
		mRasterizerDescChanged = true;
	}
}