#include "OgreHeader.h"
#include "VulkanFrame.h"

VulkanFrame::VulkanFrame(uint32_t index)
{
    mFrameIndex = index;
    mFrameCB = std::make_unique<VulkanUploadBuffer<FrameConstantBuffer>>(
        8,
        true
        );
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
