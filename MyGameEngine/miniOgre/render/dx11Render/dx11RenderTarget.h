#pragma once
#include "dx11Common.h"
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

	virtual bool useMsaa() 
	{
		return false;
	}
private:
};