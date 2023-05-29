#pragma once
#include "d3dutil.h"
#include <unordered_set>
class Dx12TextureHandleManager
{
public:
	Dx12TextureHandleManager(ID3D12Device* device);

	int32_t allocStartIndex(int32_t hCount = 1);

	CD3DX12_CPU_DESCRIPTOR_HANDLE getCpuHandleByIndex(int32_t index);
	CD3DX12_GPU_DESCRIPTOR_HANDLE getGpuHandleByIndex(int32_t index);

	const std::vector<ID3D12DescriptorHeap*>& getHeaps()
	{
		return mHeaps;
	}
private:
	ID3D12Device* mDx12Device;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;
	std::unordered_set<int32_t> mHandleContainer;
	uint32_t mContainerCount = 100;
	uint32_t mFreeIndex = 0;
	uint32_t mCbvSrvUavDescriptorSize;

	std::vector<ID3D12DescriptorHeap*> mHeaps;
};