#pragma once

#include "OgreRenderWindow.h"
#include "VulkanRenderTarget.h"



class VulkanFrame;


class VulkanWindow : public Ogre::RenderWindow
{
public:
	VulkanWindow();
	~VulkanWindow();

	virtual void create(const String& name, unsigned int width, unsigned int height,
		bool fullScreen, const NameValuePairList* miscParams);

	

	virtual void destroy();

	virtual void resize(unsigned int width, unsigned int height);

	virtual Ogre::RenderTarget* getColorTarget();
	virtual Ogre::RenderTarget* getDepthTarget();

	virtual bool requiresTextureFlipping() const;

	virtual void preRender(const ColourValue& colour);
	virtual void postRender();
	void start();
	VkFramebuffer getFrameBuffer(uint32_t index);


	VulkanFrame* getNextFrame();
private:
	void createFramebuffers();
	void createSyncObjects();
	virtual void swapBuffers();
private:

	const int SwapChainBufferCount = 3;
	VkSurfaceKHR mSurface;
	
	HWND mWnd;

	VulkanDepthStencil mDepthStencil;

	
	std::vector<VkFramebuffer> mSwapChainFramebuffers;
	

	uint32_t mFrameIndex = 0;
	uint32_t mImageIndex = 0;

	bool mHaveRenderPass = false;

	MultisampleTarget mMultisampleTarget;


	Ogre::VulkanRenderTarget* mDepthTarget;

	Ogre::VulkanRenderTarget* mColorTarget;
};