#include "OgreHeader.h"
#include "dx12RenderTargetHelper.h"
#include "dx12Helper.h"

Dx12RenderTargetHelper::Dx12RenderTargetHelper()
{
	
}

Dx12RenderTargetHelper::~Dx12RenderTargetHelper()
{

}

void Dx12RenderTargetHelper::createResource(
	uint32_t width,
	uint32_t height,
	const ColourValue& color,
	bool useMsaa)
{
	mWidth = width;
	mHeight = height;
	mColorValue = color;
	mUseMsaa = useMsaa;

	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc = {};
	rtvDescriptorHeapDesc.NumDescriptors = 1;
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	auto device = DX12Helper::getSingleton().getDevice();

	ThrowIfFailed(device->CreateDescriptorHeap(&rtvDescriptorHeapDesc,
		IID_PPV_ARGS(mRTVDescriptorHeap.ReleaseAndGetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvDescriptorHeapDesc = {};
	dsvDescriptorHeapDesc.NumDescriptors = 1;
	dsvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	ThrowIfFailed(device->CreateDescriptorHeap(&dsvDescriptorHeapDesc,
		IID_PPV_ARGS(mDSVDescriptorHeap.ReleaseAndGetAddressOf())));

	D3D12_RESOURCE_DESC msaaRTDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DX12Helper::getSingleton().getBackBufferFormat(),
		mWidth,
		mHeight,
		1, // This render target view has only one texture.
		1, // Use a single mipmap level
		mUseMsaa?4:1
	);
	msaaRTDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	
	D3D12_CLEAR_VALUE msaaOptimizedClearValue = {};
	msaaOptimizedClearValue.Format = 
		DX12Helper::getSingleton().getBackBufferFormat();
	auto backColor = mColorValue;
	memcpy(msaaOptimizedClearValue.Color, &backColor, sizeof(float) * 4);

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);

	
	ThrowIfFailed(device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&msaaRTDesc,
		D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
		&msaaOptimizedClearValue,
		IID_PPV_ARGS(mRenderTarget.ReleaseAndGetAddressOf())
	));

	//mRenderTarget->SetName(L"MSAA Render Target");


	auto viewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	if (mUseMsaa)
	{
		viewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
	}
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DX12Helper::getSingleton().getBackBufferFormat();
	rtvDesc.ViewDimension = viewDimension;

	device->CreateRenderTargetView(
		mRenderTarget.Get(), &rtvDesc,
		mRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	// Create an MSAA depth stencil view.
	D3D12_RESOURCE_DESC depthStencilDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DX12Helper::getSingleton().getDepthStencilFormat(),
		mWidth,
		mHeight,
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		mUseMsaa ? 4 : 1
	);
	depthStencilDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format = DX12Helper::getSingleton().getDepthStencilFormat();
	depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	ThrowIfFailed(device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthOptimizedClearValue,
		IID_PPV_ARGS(mDepthStencil.ReleaseAndGetAddressOf())
	));

	auto depthViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	if (mUseMsaa)
	{
		depthViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DX12Helper::getSingleton().getDepthStencilFormat();
	dsvDesc.ViewDimension = depthViewDimension;

	device->CreateDepthStencilView(
		mDepthStencil.Get(), &dsvDesc,
		mDSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}

ID3D12Resource* Dx12RenderTargetHelper::getRenderTarget()
{
	return mRenderTarget.Get();
}

ID3D12Resource* Dx12RenderTargetHelper::getDepthStencil()
{
	return mDepthStencil.Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE Dx12RenderTargetHelper::getRtvCpuHandle()
{
	return mRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE Dx12RenderTargetHelper::getDsvCpuHandle()
{
	return mDSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
}