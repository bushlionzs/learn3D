#pragma once

#include "OgreRenderWindow.h"
#include "VulkanRenderTarget.h"
#include "VulkanSwapChain.h"


class VulkanFrame;


class VulkanWindow : public Ogre::RenderWindow
{
public:
	VulkanWindow(uint64_t wndHandle, uint64_t flags);
	~VulkanWindow();

	virtual void create(VulkanSwapChain* swapChain);
	virtual Ogre::PixelFormat getColorFormat();
	virtual Ogre::RenderTarget* getColorTarget();
	virtual Ogre::RenderTarget* getDepthTarget();

	uint64_t getWndHandle()
	{
		return mWndHandle;
	}

	uint64_t getFlags()
	{
		return mFlags;
	}

	VulkanSwapChain* getSwapChain()
	{
		return mSwapChain;
	}
private:
	VulkanSwapChain* mSwapChain;

	Ogre::VulkanRenderTarget* mDepthTarget;

	Ogre::VulkanRenderTarget* mColorTarget;

	uint64_t mWndHandle;
	uint64_t mFlags;
};