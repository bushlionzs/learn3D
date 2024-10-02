#pragma once
#include "VulkanCommon.h"
#include "VulkanUploadbuffer.h"
#include "shader.h"
#include "renderHelper.h"
#include "VulkanObjectPool.h"

class VulkanFrame: public RenderFrame
{
public:
	VulkanFrame(uint32_t frame_index);
	~VulkanFrame();

	void updateFrameConstantBuffer(
		const FrameConstantBuffer& data,
		ICamera* cam);

	uint32_t getFrameIndex();
	void updateFrameDescriptor(VkDescriptorBufferInfo& frameDescriptor, ICamera* cam);

	VulkanObjectPool& getObjectPool()
	{
		return _vulkanObjectPool;
	}
private:
	uint32_t mFrameIndex;
	std::unique_ptr<VulkanUploadBuffer<FrameConstantBuffer>>  mFrameCB;
	VulkanObjectPool _vulkanObjectPool;

	std::unordered_map<ICamera*, int32_t> mCameraMap;

	uint32_t mFreeIndex = 0;
};