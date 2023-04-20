#pragma once
#include "dx12Common.h"
#include "UploadBuffer.h"
class Dx12Frame
{
public:
	Dx12Frame();
	~Dx12Frame();
	void _initialise(uint32_t index);
	UploadBuffer<FrameConstantBuffer>* getCameraFrameData(Ogre::Camera* cam);
	uint64_t getFrameIndex();
	uint64_t getFence();
	void setFence(uint64_t fence);
	ID3D12GraphicsCommandList* getCommandList();
	void closeCommandList();
	void resetCommandList();
	void submitCommandList();
private:
	std::unordered_map<Ogre::Camera*, std::shared_ptr<UploadBuffer<FrameConstantBuffer>>> mCamaraDataMap;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
	uint64_t mFence;
	uint64_t mFrameIndex;
};