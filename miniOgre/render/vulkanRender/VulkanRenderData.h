#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "renderHelper.h"
#include <utils/JobSystem.h>

class VulkanRenderSystem;

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
	VulkanRenderableData(VulkanRenderSystem* engine, Ogre::Renderable* r);
	~VulkanRenderableData();

	bool update(VulkanFrame* frame, utils::JobSystem::Job* job);
	void updateImpl(VulkanFrame* frame);
	void render(VulkanFrame* frame, VkCommandBuffer cb);

	//VkPipelineLayout  getPipelineLayout();
private:
	
	void buildInitData();
private:
	VulkanRenderSystem* mEngine;
	VkDevice mDevice;
	std::vector<VulkanFrameRenderableData> _frameRenderableData;
	

	bool mUpdate = false;
};