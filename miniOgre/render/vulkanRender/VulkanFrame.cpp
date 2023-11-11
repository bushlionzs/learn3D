#include "OgreHeader.h"
#include "VulkanFrame.h"

VulkanFrame::VulkanFrame(uint32_t index)
{
    mFrameIndex = index;
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
}

VulkanFrame::~VulkanFrame()
{

}

VkCommandBuffer VulkanFrame::getVkCommandBuffer()
{
	return mPrimaryCommandBuffer;
}

void VulkanFrame::updateFrameConstantBuffer(
    const FrameConstantBuffer& data,
    uint32_t index)
{
    mFrameCB->CopyData(index, data);
}

uint32_t& VulkanFrame::getFrameIndex()
{
    return mFrameIndex;
}

void VulkanFrame::updateFrameBuffer(VkCommandBuffer cb)
{
    mPrimaryCommandBuffer = cb;
}
