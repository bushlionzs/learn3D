#pragma once
#include "shader.h"
#include "VulkanUploadBuffer.h"
#include "VulkanObjectPool.h"
#include "renderHelper.h"
#include "glslUtil.h"
#include <utils/JobSystem.h>
#include <DriverEnums.h>
#include <vulkan/VulkanPipelineCache.h>
#include <utils/StructureOfArrays.h>

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

	bool update(VulkanFrame* frame, utils::JobSystem::Job* job);
	void updateImpl(VulkanFrame* frame);
	void render(VulkanFrame* frame, VkCommandBuffer cb, VulkanPipelineCache* pipelineCache);

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
private:
	VulkanRenderSystemBase* mEngine;
	VkDevice mDevice;
	std::vector<VulkanFrameRenderableData> _frameRenderableData;
	
	std::vector<VkVertexInputBindingDescription> vertexInputBindings;
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
	bool mUpdate = false;

	VkShaderModule mVertexShader = VK_NULL_HANDLE;
	VkShaderModule mFragShader = VK_NULL_HANDLE;


	filament::backend::VulkanPipelineCache::RasterState mRasterState;

	GeometryNode mGeometryNode;

	VulkanRayTracingContext* mRayTracingContext;

	VkAccelerationStructureGeometryKHR mGeometry;

	VkAccelerationStructureBuildRangeInfoKHR mBuildRangeInfo;

	int32_t mGeometrySlot = -1;

	bool mRayTracingUpdate = false;
};