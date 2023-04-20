#pragma once
#include "VulkanCommon.h"
#include "VulkanUploadbuffer.h"
#include "shader.h"


class VulkanFrame
{
public:
	VulkanFrame(uint32_t index);
	~VulkanFrame();
	VkCommandBuffer getVkCommandBuffer();

	void updateFrameConstantBuffer(
		const FrameConstantBuffer& data,
		uint32_t index = 0);

	uint32_t& getFrameIndex();

	void updateFrameBuffer(VkCommandBuffer cb);

	std::unique_ptr<VulkanUploadBuffer<FrameConstantBuffer>>&
		getFrameCB()
	{
		return mFrameCB;
	}
private:
	uint32_t mFrameIndex;
	VkCommandBuffer mPrimaryCommandBuffer;
	std::unique_ptr<VulkanUploadBuffer<FrameConstantBuffer>>  mFrameCB;
};