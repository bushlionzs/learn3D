#include "OgreHeader.h"
#include "dx12Frame.h"
#include "dx12Helper.h"

Dx12Frame::Dx12Frame()
{

}

Dx12Frame::~Dx12Frame()
{

}

void Dx12Frame::_initialise(uint32_t index)
{
	ID3D12Device* device = DX12Helper::getSingleton().getDevice();

	mFence = 0;
	mFrameIndex = index;
	ThrowIfFailed(device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(mDirectCmdListAlloc.GetAddressOf())));

	ThrowIfFailed(device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc.Get(),
		nullptr,
		IID_PPV_ARGS(mCommandList.GetAddressOf())));
}

UploadBuffer<FrameConstantBuffer>* Dx12Frame::getCameraFrameData(Ogre::Camera* cam)
{
	auto itor = mCamaraDataMap.find(cam);
	if(itor != mCamaraDataMap.end())
	{
		return itor->second.get();
	}

	auto device = DX12Helper::getSingleton().getDevice();
	auto tmp = std::make_shared< UploadBuffer<FrameConstantBuffer>>(device, 1, true);
	mCamaraDataMap[cam] = tmp;

	return tmp.get();
}

uint64_t Dx12Frame::getFrameIndex()
{
	return mFrameIndex;
}

uint64_t Dx12Frame::getFence()
{
	return mFence;
}

void Dx12Frame::setFence(uint64_t fence)
{
	mFence = fence;
}

ID3D12GraphicsCommandList* Dx12Frame::getCommandList()
{
	return mCommandList.Get();
}

void Dx12Frame::closeCommandList()
{
	mCommandList->Close();
}

void Dx12Frame::resetCommandList()
{
	mDirectCmdListAlloc->Reset();
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
}

void Dx12Frame::submitCommandList()
{
	mCommandList->Close();
	DX12Helper::getSingleton().executeCommand(mCommandList.Get());
	DX12Helper::getSingleton().FlushCommandQueue();
}
