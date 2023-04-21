#pragma once
#include "dx12Common.h"
#include "OgreColourValue.h"
class Dx12RenderTarget
{
public:
	Dx12RenderTarget
	(
	);
	~Dx12RenderTarget();

	virtual void preRender(ID3D12GraphicsCommandList* cl) = 0;
	virtual ID3D12Resource* getCurrentBackBuffer()const = 0;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const = 0;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const = 0;

	virtual D3D12_RESOURCE_STATES getResourceStates() = 0;

	virtual bool useMsaa() 
	{
		return false;
	}

	virtual void clearFrameBuffer(uint32_t buffers,
		const Ogre::ColourValue& colour,
		float depth, uint16_t stencil) = 0;
private:
};