#include "OgreHeader.h"
#include "VulkanFrame.h"

VulkanFrame::VulkanFrame(uint32_t frame_index)
{
    mFrameIndex = frame_index;
    mFrameCB = std::make_unique<VulkanUploadBuffer<FrameConstantBuffer>>(
        8,
        true
        );
    _vulkanObjectPool.init(VulkanHelper::getSingleton()._getRenderSystem());
}

VulkanFrame::~VulkanFrame()
{

}


void VulkanFrame::updateFrameConstantBuffer(
    const FrameConstantBuffer& data,
    ICamera* cam)
{
    int32_t const_index = -1;
    auto itor = mCameraMap.find(cam);
    if (itor != mCameraMap.end())
    {
        const_index = itor->second;
    }
    else
    {
        const_index = mFreeIndex++;
        mCameraMap[cam] = const_index;
    }
    mFrameCB->CopyData(const_index, data);
}

uint32_t VulkanFrame::getFrameIndex()
{
    return mFrameIndex;
}

void VulkanFrame::updateFrameDescriptor(VkDescriptorBufferInfo& frameDescriptor, ICamera* cam)
{
    int32_t index = 0;
    auto itor = mCameraMap.find(cam);
    if (itor == mCameraMap.end())
    {
        assert(false);
    }
    else
    {
        index = itor->second;
    }
    frameDescriptor.buffer = mFrameCB->getVKBuffer();
    frameDescriptor.offset = mFrameCB->getObjectSize() * index;
    frameDescriptor.range = mFrameCB->getObjectSize();
}
