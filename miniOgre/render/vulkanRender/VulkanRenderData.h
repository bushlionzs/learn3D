#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "renderHelper.h"

class VulkanRenderSystem;

class VulkanFrameRenderableData
{
public:
	VulkanObjectDesc mObjectDesc;
	VulkanObjectDesc mMaterialDesc;
	VulkanObjectDesc mSkinnedDesc;

	ObjectConstantBuffer mObjectConstantBuffer;
	MaterialConstantBuffer mMaterialConstantBuffer;
	VkDescriptorSet mDescriptorSet;
	bool mDescriptorSetUpdate = false;

public:
	void _initialise();
};

class VulkanRenderableData: public RenderableData
{
public:
	VulkanRenderableData(VulkanRenderSystem* engine, Ogre::Renderable* r);
	~VulkanRenderableData();

	void update(VulkanFrame* frame, VkCommandBuffer cb);
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