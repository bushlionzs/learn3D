#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"

class VulkanRenderSystem;
class VulkanRenderableData
{
public:
	VulkanRenderableData(VulkanRenderSystem* engine);
	~VulkanRenderableData();

	void buildMaterial(Material* mat);
	
	void updateDescriptorSet(VulkanPass* pass);

	VkDescriptorSet getDescriptorSet();
	VkPipelineLayout  getPipelineLayout();
private:
	void updateData(VulkanPass* pass);
	void buildInitData();
private:
	VulkanRenderSystem* mEngine;
	VkDevice mDevice;

	VulkanObjectDesc mObjectDesc;
	VulkanObjectDesc mMaterialDesc;
	VulkanObjectDesc mSkinnedDesc;

	ObjectConstantBuffer mObjectConstantBuffer;
	MaterialConstantBuffer mMaterialConstantBuffer;
	VkDescriptorSet mDescriptorSet;

	bool mUpdate = false;
};