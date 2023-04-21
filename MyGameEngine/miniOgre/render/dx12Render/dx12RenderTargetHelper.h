#pragma once
#include "dx12Common.h"
#include "OgreColourValue.h"
class Dx12RenderTargetHelper
{
public:
	Dx12RenderTargetHelper();
	~Dx12RenderTargetHelper();
	void createResource(uint32_t width,
		uint32_t height,
		const ColourValue& color,
		bool useMsaa);

	ID3D12Resource* getRenderTarget();
	ID3D12Resource* getDepthStencil();

	D3D12_CPU_DESCRIPTOR_HANDLE getRtvCpuHandle();
	D3D12_CPU_DESCRIPTOR_HANDLE getDsvCpuHandle();
private:
	Microsoft::WRL::ComPtr<ID3D12Resource>          mRenderTarget;
	Microsoft::WRL::ComPtr<ID3D12Resource>          mDepthStencil;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    mRTVDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    mDSVDescriptorHeap;
	uint32_t mWidth;
	uint32_t mHeight;

	ColourValue mColorValue;
	bool mUseMsaa;
};