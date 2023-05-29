#pragma once
#include "dx11Common.h"
#include "OgreColourValue.h"
class Dx11RenderTarget
{
public:
	Dx11RenderTarget
	(
	);
	~Dx11RenderTarget();

	virtual void preRender() = 0;
	virtual ID3D11RenderTargetView* getRenderTargetView() const = 0;
	virtual ID3D11DepthStencilView* getDepthStencilView() const = 0;

	virtual void clearFrameBuffer(uint32_t buffers,
		const Ogre::ColourValue& colour,
		float depth, uint16_t stencil) = 0;
private:
};