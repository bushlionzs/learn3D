#pragma once

#include "OgreRenderWindow.h"
#include "VulkanRenderTarget.h"



class VulkanFrame;

class VulkanWindow : public Ogre::RenderWindow,
	public VulkanRenderTarget
{
public:
	VulkanWindow();
	~VulkanWindow();

	virtual void create(const String& name, unsigned int width, unsigned int height,
		bool fullScreen, const NameValuePairList* miscParams);

	virtual void destroy();

	virtual void resize(unsigned int width, unsigned int height);

	virtual void copyContentsToMemory(const Box& src, const PixelBox& dst, FrameBuffer buffer = FB_AUTO);

	virtual bool requiresTextureFlipping() const;

	virtual void preRender(VulkanFrame* frame, const ColourValue& colour);

	void start();
	VkFramebuffer getFrameBuffer(uint32_t index);

	virtual uint32_t getTargetWidth();
	virtual uint32_t getTargetHeight();

	VulkanFrame* getNextFrame();
private:
	void createFramebuffers();
	void setupDepthStencil();
	void createSyncObjects();
	virtual void swapBuffers() override;
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
private:

	const int SwapChainBufferCount = 3;
	VkSurfaceKHR mSurface;
	
	HWND mWnd;

	VulkanDepthStencil mDepthStencil;

	
	std::vector<VkFramebuffer> mSwapChainFramebuffers;
	VkSemaphore mImageAvailableSemaphore;
	

	uint32_t mFrameIndex = 0;

	bool mHaveRenderPass = false;
};