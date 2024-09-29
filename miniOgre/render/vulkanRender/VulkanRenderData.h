#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "renderHelper.h"
#include "glslUtil.h"
#include <utils/JobSystem.h>
#include <DriverEnums.h>


class VulkanRenderSystem;
class VulkanRayTracingContext;
class VertexDeclaration;

namespace filament::backend
{
	class VulkanPipelineCache;
}

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
	VulkanRenderableData(VulkanRenderSystemBase* engine, Ogre::Renderable* r, VulkanRayTracingContext* context);
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


	filament::backend::VulkanPipelineCache::RasterState mRasterState;

	std::vector<DescriptorSetLayoutBindingInfo> mUBOLayoutInfo;
	std::vector<DescriptorSetLayoutBindingInfo> mSamplerLayoutInfo;
	std::array <VkDescriptorSetLayout, 2> mLayouts;
	VkPipelineLayout mPipelineLayout;

	GeometryNode mGeometryNode;

	VulkanRayTracingContext* mRayTracingContext;

	VkAccelerationStructureGeometryKHR mGeometry;

	VkAccelerationStructureBuildRangeInfoKHR mBuildRangeInfo;

	int32_t mGeometrySlot = -1;

	bool mRayTracingUpdate = false;

	uint64_t mLastFrame = 0xffffffff;
};