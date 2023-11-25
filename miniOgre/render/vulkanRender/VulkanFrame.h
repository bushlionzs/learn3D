#pragma once
#include "VulkanCommon.h"
#include "VulkanUploadbuffer.h"
#include "shader.h"
#include "renderHelper.h"
#include "VulkanObjectPool.h"

class VulkanFrame: public RenderFrame
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

	VkFence getFence()
	{
		return mFlightFence;
	}

	VkSemaphore getFinishedSemaphore()
	{
		return mRenderFinishedSemaphore;
	}

	VulkanObjectPool& getObjectPool()
	{
		return _vulkanObjectPool;
	}
private:
	uint32_t mFrameIndex;
	VkCommandBuffer mPrimaryCommandBuffer;
	std::unique_ptr<VulkanUploadBuffer<FrameConstantBuffer>>  mFrameCB;

	
	VkFence mFlightFence;
	VkSemaphore mRenderFinishedSemaphore;

	VulkanObjectPool _vulkanObjectPool;
};