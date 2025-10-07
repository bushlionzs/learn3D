#pragma once

#include "OgreRenderWindow.h"

class DX12SwapChain;
class Dx12RenderTarget;
class Dx12RenderWindow : public Ogre::RenderWindow
{
public:
	Dx12RenderWindow(uint64_t wndHandle, uint64_t flags);
	~Dx12RenderWindow();

	uint64_t getWndHandle()
	{
		return mWndHandle;
	}

	uint64_t getFlags()
	{
		return mFlags;
	}

	void setSwapChain(DX12SwapChain* swapChain);
	virtual Ogre::PixelFormat getColorFormat();
	virtual Ogre::RenderTarget* getColorTarget();
	virtual Ogre::RenderTarget* getDepthTarget();
private:
	DX12SwapChain* mSwapChain;
	Dx12RenderTarget* mColorTarget;
	Dx12RenderTarget* mDepthTarget;

	uint64_t mWndHandle;
	uint64_t mFlags;
};