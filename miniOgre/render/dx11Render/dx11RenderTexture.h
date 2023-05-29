#pragma once

#include "OgreRenderTexture.h"
#include "OgreRenderTarget.h"
#include "dx11RenderTarget.h"

class Dx11HardwarePixelBuffer;
class Dx11Texture;

class Dx11RenderTexture : public Ogre::RenderTexture, public Dx11RenderTarget
{
public:
	Dx11RenderTexture(
		const String& name,
		Dx11HardwarePixelBuffer* buffer,
		uint32_t zoffset);
	~Dx11RenderTexture();

	void rebind(Dx11HardwarePixelBuffer* buffer);
	virtual void copyContentsToMemory(
		const Box& src, 
		const PixelBox& dst, 
		FrameBuffer buffer = FB_AUTO);

	virtual bool requiresTextureFlipping() const;

	virtual void preRender();

	virtual void swapBuffers();

	virtual ID3D11RenderTargetView* getRenderTargetView() const ;
	virtual ID3D11DepthStencilView* getDepthStencilView() const;

	virtual void clearFrameBuffer(uint32_t buffers,
		const Ogre::ColourValue& colour,
		float depth, uint16_t stencil);
private:
	D3D11_VIEWPORT mViewport;
	Dx11Texture* mParentTexture;

	ID3D11RenderTargetView* mRenderTargetView = nullptr;
	ID3D11DepthStencilView* mDepthStencilView = nullptr;
	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
};