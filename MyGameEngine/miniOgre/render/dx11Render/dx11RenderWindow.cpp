#include "OgreHeader.h"
#include "dx11RenderWindow.h"
#include "OgreStringConverter.h"
#include "dx11RenderSystem.h"
#include "dx11Helper.h"

Dx11RenderWindow::Dx11RenderWindow(Dx11RenderSystem* rs)
{
	mWnd = 0;
	mRenderSystem = rs;
}

Dx11RenderWindow::~Dx11RenderWindow()
{

}

void Dx11RenderWindow::create(const String& name, unsigned int width, unsigned int height,
	bool fullScreen, const NameValuePairList* miscParams)
{
	auto itor = miscParams->find("externalWindowHandle");
	if (itor == miscParams->end())
	{
		OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "externalWindowHandle should be provided");
	}

	mWnd = (HWND)StringConverter::parseSizeT(itor->second);

	auto device = DX11Helper::getSingleton().getDevice();

	

	resize(width, height);
}


void Dx11RenderWindow::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferDesc.Width = mWidth;
	sd.BufferDesc.Height = mHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = 0;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = DX11_BACKBUFFER_COUNT;
	sd.OutputWindow = mWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	auto device = DX11Helper::getSingleton().getDevice();

	IDXGIDevice* dxgiDevice = 0;
	device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	auto hr = dxgiFactory->CreateSwapChain(device, &sd, mSwapChain.ReleaseAndGetAddressOf());

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);
}

void Dx11RenderWindow::createDepthStencil()
{

}

void Dx11RenderWindow::destroy()
{

}

void Dx11RenderWindow::resize(unsigned int width, unsigned int height)
{
	if (width == mWidth && height == mHeight)
	{
		return;
	}
	
	mWidth = width;
	mHeight = height;

	createSwapChain();

	auto device = DX11Helper::getSingleton().getDevice();
	auto deviceContext = DX11Helper::getSingleton().getDeviceContext();
	
	for (uint32_t i = 0; i < DX11_BACKBUFFER_COUNT; i++)
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
		mSwapChain->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));
		CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R8G8B8A8_UNORM);
		device->CreateRenderTargetView(pBackBuffer.Get(), 0, m_pRenderTargetViews[i].ReleaseAndGetAddressOf());
	}
	
	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mWidth;
	depthStencilDesc.Height = mHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	device->CreateTexture2D(&depthStencilDesc, 0, mDepthStencilBuffer.ReleaseAndGetAddressOf());
	device->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.ReleaseAndGetAddressOf());


	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mViewport.Width = static_cast<float>(mWidth);
	mViewport.Height = static_cast<float>(mHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

}

ID3D11RenderTargetView* Dx11RenderWindow::getRenderTargetView()const
{
	return m_pRenderTargetViews[mCurrFrameIndex].Get();
}

ID3D11DepthStencilView* Dx11RenderWindow::getDepthStencilView()const
{
	return mDepthStencilView.Get();
}


void Dx11RenderWindow::preRender()
{
	auto deviceContext = DX11Helper::getSingleton().getDeviceContext();
	deviceContext->RSSetViewports(1, &mViewport);

	auto renderTarget = getRenderTargetView();
	deviceContext->OMSetRenderTargets(1, &renderTarget, mDepthStencilView.Get());
}


void Dx11RenderWindow::present()
{
	mSwapChain->Present(0, 0);
	mCurrFrameIndex++;
	mCurrFrameIndex = (mCurrFrameIndex % DX11_BACKBUFFER_COUNT);
}


void Dx11RenderWindow::clearFrameBuffer(uint32_t buffers,
	const Ogre::ColourValue& colour,
	float depth, uint16_t stencil)
{
	auto context = DX11Helper::getSingleton().getDeviceContext();
	auto renderTargetView = getRenderTargetView();
	auto depthStencilView = getDepthStencilView();
	context->ClearRenderTargetView(renderTargetView, reinterpret_cast<const float*>(&colour));

	context->ClearDepthStencilView(depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Dx11RenderWindow::swapBuffers()
{
	auto context = DX11Helper::getSingleton().getDeviceContext();
	ID3D11RenderTargetView* output = nullptr;
	ID3D11ShaderResourceView* input = nullptr;
	context->OMSetRenderTargets(0, &output, nullptr);
	context->PSSetShaderResources(2, 1, &input);
}

void Dx11RenderWindow::copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer)
{

}

bool Dx11RenderWindow::requiresTextureFlipping() const
{
	return false;
}
