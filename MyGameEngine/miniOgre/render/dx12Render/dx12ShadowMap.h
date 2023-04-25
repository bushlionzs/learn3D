#pragma once
#include "d3dutil.h"
class Dx12TextureHandleManager;
class Dx12ShadowMap
{
public:
	Dx12ShadowMap(
		uint32_t width,
		uint32_t height);
	~Dx12ShadowMap();

	uint32_t width()const;
	uint32_t height()const;
	ID3D12Resource* resource();
	CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle() const;
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuSrvHandle()const;
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle()const;
	D3D12_VIEWPORT viewport()const;
	D3D12_RECT scissorRect()const;

	void buildDescriptors();
private:
	void buildResource();
private:
	ID3D12Device* md3dDevice = nullptr;
	Dx12TextureHandleManager* mDx12TextureHandleManager = nullptr;
	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;


	uint32_t mWidth;
	uint32_t mHeight;
	DXGI_FORMAT mFormat = DXGI_FORMAT_R24G8_TYPELESS;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuSrvHandle;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuSrvHandle;
	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuDsvHandle;
	Microsoft::WRL::ComPtr<ID3D12Resource> mShadowMap = nullptr;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;
};