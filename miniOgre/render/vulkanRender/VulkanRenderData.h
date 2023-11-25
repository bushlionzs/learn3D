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

public:
	void _initialise();
};

class VulkanRenderableData: public RenderableData
{
public:
	VulkanRenderableData(VulkanRenderSystem* engine, Ogre::Renderable* r);
	~VulkanRenderableData();

	void update(VulkanFrame* frame);
	void render(VulkanFrame* frame);

	//VkPipelineLayout  getPipelineLayout();
private:

	void buildInitData();
private:
	VulkanRenderSystem* mEngine;
	VkDevice mDevice;
	std::vector<VulkanFrameRenderableData> _frameRenderableData;
	

	bool mUpdate = false;
};