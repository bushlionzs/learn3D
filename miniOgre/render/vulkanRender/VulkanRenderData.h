#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "renderHelper.h"
#include <utils/JobSystem.h>

class VulkanRenderSystem;
class VulkanRayTracingContext;

class VulkanFrameRenderableData
{
public:
	VulkanObjectDesc mObjectDesc;
	VulkanObjectDesc mMaterialDesc;
	VulkanObjectDesc mPBRMaterialDesc;
	VulkanObjectDesc mSkinnedDesc;

	ObjectConstantBuffer mObjectConstantBuffer;
	MaterialConstantBuffer mMaterialConstantBuffer;
	PbrMaterialConstanceBuffer mPBRMaterialConstantBuffer;
	VkDescriptorSet mDescriptorSet;
	VkDescriptorSet mDescriptorSetSampler;
	bool mDescriptorSetUpdate = false;

};





class VulkanRenderableData: public RenderableData
{
public:
	VulkanRenderableData(VulkanRenderSystem* engine, Ogre::Renderable* r, VulkanRayTracingContext* context);
	~VulkanRenderableData();

	bool update(VulkanFrame* frame, utils::JobSystem::Job* job);
	void updateImpl(VulkanFrame* frame);
	void render(VulkanFrame* frame, VkCommandBuffer cb);

	int32_t getTransformSlot()
	{
		return mTransformSlot;
	}

	int32_t getGeometrySlot()
	{
		return mGeometrySlot;
	}

	GeometryNode& getGeometryNode()
	{
		return mGeometryNode;
	}

	VkAccelerationStructureGeometryKHR& getGeometryKHR()
	{
		return mGeometry;
	}

	VkAccelerationStructureBuildRangeInfoKHR& getBuildRangeInfo()
	{
		return mBuildRangeInfo;
	}

private:
	
	void buildInitData();
private:
	VulkanRenderSystem* mEngine;
	VkDevice mDevice;
	std::vector<VulkanFrameRenderableData> _frameRenderableData;
	

	bool mUpdate = false;

	GeometryNode mGeometryNode;

	VulkanRayTracingContext* mRayTracingContext;

	VkAccelerationStructureGeometryKHR mGeometry;

	VkAccelerationStructureBuildRangeInfoKHR mBuildRangeInfo;

	int32_t mTransformSlot = -1;
	int32_t mGeometrySlot = -1;
};