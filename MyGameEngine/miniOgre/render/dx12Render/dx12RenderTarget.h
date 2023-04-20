#pragma once
#include "d3dutil.h"
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
private:
};