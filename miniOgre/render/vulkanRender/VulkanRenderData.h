#pragma once
#include <utils/JobSystem.h>
#include "shader.h"
#include "renderHelper.h"
#include "glslUtil.h"
#include <DriverEnums.h>
#include "VulkanPipelineCache.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "VulkanCommands.h"
#include "VulkanPlatform.h"

class VulkanRenderSystemBase;
class VulkanRayTracingContext;
class VertexDeclaration;


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
	VkDescriptorSet mDescriptorSetSamplerPbr;
	bool mDescriptorSetUpdate = false;
};





class VulkanRenderableData: public RenderableData
{
public:
	VulkanRenderableData(
		VulkanPlatform* platform, 
		VulkanCommands* commands, 
		Ogre::Renderable* r);
	~VulkanRenderableData();

	bool update(
		VulkanFrame* frame,
		const RenderPassInfo& passInfo,
		utils::JobSystem::Job* job);
	void updateImpl(VulkanFrame* frame, const RenderPassInfo& passInfo);
	void render(
		VulkanFrame* frame, 
		VkCommandBuffer cb, 
		VulkanPipelineCache* pipelineCache,
		const RenderPassInfo& passInfo);

	bool updateRayTracingData();

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
	void parseInputBindingDescription(
		VertexDeclaration* decl,
		std::vector<GlslInputDesc>& inputDesc);
	void parseAttributeDescriptions(
		VertexDeclaration* decl,
		std::vector<GlslInputDesc>& inputDesc);
	void buildInitData();
	void buildPipelineData(Ogre::Material* mat);
	void bindPipeline(
		VkCommandBuffer cb, 
		VulkanPipelineCache* pipelineCache,
		bool shadow = false);
	void buildLayout();
private:
	VulkanRenderSystemBase* mEngine;
	VkDevice mDevice;
	std::vector<VulkanFrameRenderableData> _frameRenderableData;
	std::vector<VulkanFrameRenderableData> _frameRenderableShadowData;
	
	std::vector<VkVertexInputBindingDescription> mVertexInputBindings;
	std::vector<VkVertexInputAttributeDescription> mAttributeDescriptions;
	bool mUpdate = false;

	VkShaderModuleInfo mVertexShaderInfo;
	VkShaderModuleInfo mFragShaderInfo;


	VulkanPipelineCache::RasterState mRasterState;

	descset::DescriptorSetLayout mUBOLayoutInfo;
	descset::DescriptorSetLayout mSamplerLayoutInfo;
	std::array <VkDescriptorSetLayout, 2> mLayouts;
	VkPipelineLayout mPipelineLayout;

	GeometryNode mGeometryNode;

	VulkanRayTracingContext* mRayTracingContext;

	VkAccelerationStructureGeometryKHR mGeometry;

	VkAccelerationStructureBuildRangeInfoKHR mBuildRangeInfo;

	int32_t mGeometrySlot = -1;

	bool mRayTracingUpdate = false;

	uint64_t mLastFrame = 0xffffffff;

	VulkanCommands* mCommands;
};