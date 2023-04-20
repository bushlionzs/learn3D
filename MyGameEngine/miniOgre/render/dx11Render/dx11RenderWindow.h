#pragma once

#include "OgreRenderWindow.h"
#include "dx11Common.h"
#include "dx11RenderTarget.h"
class Dx11RenderSystem;

class Dx11RenderWindow : public Ogre::RenderWindow, public Dx11RenderTarget
{
public:
	Dx11RenderWindow(Dx11RenderSystem* rs);
	~Dx11RenderWindow();

	virtual void create(const String& name, unsigned int width, unsigned int height,
		bool fullScreen, const NameValuePairList* miscParams);

	virtual void destroy();

	virtual void resize(unsigned int width, unsigned int height);

	virtual void copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer = FB_AUTO);

	virtual bool requiresTextureFlipping() const;
	void swapBuffers();
	virtual ID3D11RenderTargetView* getRenderTargetView() const;
	virtual ID3D11DepthStencilView* getDepthStencilView() const;

	virtual void preRender();

	virtual bool useMsaa();

	void present();
private:
	void createSwapChain();
	void createDepthStencil();
private:
	HWND mWnd;
	Dx11RenderSystem* mRenderSystem;
	static const uint32_t mSwapChainBufferCount = 2;
	IDXGISwapChain* mSwapChain = nullptr;
	ID3D11Texture2D* mBackBuffer = nullptr;
	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	ID3D11RenderTargetView* mRenderTargetView = nullptr;
	ID3D11DepthStencilView* mDepthStencilView = nullptr;

	D3D11_VIEWPORT mViewport;

	uint32_t mCurrBackBufferIndex = 0;
};