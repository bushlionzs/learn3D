#include "OgreHeader.h"
#include "VulkanFrame.h"

VulkanFrame::VulkanFrame(uint32_t frame_index)
{
    mFrameIndex = frame_index;
    mFrameCB = std::make_unique<VulkanUploadBuffer<FrameConstantBuffer>>(
        8,
        true
        );

    auto device = VulkanHelper::getSingleton()._getVkDevice();

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    if (
        vkCreateFence(device, &fenceInfo, nullptr, &mFlightFence) != VK_SUCCESS ||
        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &mRenderFinishedSemaphore) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }

    auto result = vkGetFenceStatus(device, mFlightFence);

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

uint32_t& VulkanFrame::getFrameIndex()
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
    frameDescriptor.range = VK_WHOLE_SIZE;
}
