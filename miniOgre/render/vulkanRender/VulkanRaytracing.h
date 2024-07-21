#pragma once

#include "VulkanCommon.h"
#include "VulkanUploadbuffer.h"

class VulkanTexture;



class VulkanRayTracingContext
{
public:
	struct ScratchBuffer
	{
		uint64_t deviceAddress = 0;
		VkBuffer handle = VK_NULL_HANDLE;
		VkDeviceMemory memory = VK_NULL_HANDLE;
	};

	// Holds information for a storage image that the ray tracing shaders output to
	struct StorageImage {
		VkDeviceMemory memory = VK_NULL_HANDLE;
		VkImage image = VK_NULL_HANDLE;
		VkImageView view = VK_NULL_HANDLE;
		VkFormat format;
	} storageImage;
public:
	void init();
	int32_t allocGeometrySlot(GeometryNode& geometry);
	int32_t allocTransformSlot(VkTransformMatrixKHR& transform);
	int32_t allocTextureSlot(VulkanTexture* texture);
	VkBuffer getTransformBuffer();

	void updateRayTracing(std::vector<Ogre::Renderable*>& renderList);
private:
	ScratchBuffer createScratchBuffer(VkDeviceSize size);
	void deleteScratchBuffer(VulkanRayTracingContext::ScratchBuffer& scratchBuffer);
	void createAccelerationStructureBuffer(
		AccelerationStructure& accelerationStructure,
		VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);
	void deleteAccelerationStructure(AccelerationStructure& accelerationStructure);
	void createBottomLevelAccelerationStructure(std::vector<Ogre::Renderable*>& renderList);
	void createTopLevelAccelerationStructure();
	void createStorageImage();
	void createUniformBuffer();
	void createRayTracingPipeline();
	void createShaderBindingTables();
	void createDescriptorSets();
	void buildCommandBuffers();
private:
	uint32_t mMaxCount = 10000;

	std::vector<VkTransformMatrixKHR> mTransformMatrices;
	VulkanUploadBuffer<VkTransformMatrixKHR>* mVulkanTransformBuffer;
	
	std::vector<GeometryNode> mGeometryNodes;
	std::vector<VkAccelerationStructureBuildRangeInfoKHR> mBuildRangeInfos;
	std::vector<VkAccelerationStructureBuildRangeInfoKHR*> mBuildRangePointerInfos;
	VulkanUploadBuffer<GeometryNode>* mVulkanGeometryBuffer;
	std::vector<VkAccelerationStructureGeometryKHR> mGeometries;
	std::vector<uint32_t> maxPrimitiveCounts;
	
	
	VkPhysicalDeviceRayTracingPipelinePropertiesKHR  mRayTracingPipelineProperties{};
	VkPhysicalDeviceAccelerationStructureFeaturesKHR mAccelerationStructureFeatures{};
	AccelerationStructure mBottomLevelAS{};
	AccelerationStructure mTopLevelAS{};

	StorageImage mStorageImage;

	std::vector<VulkanTexture*> mTextures;
	bool mChange = true;
	VkDevice mVKDevice;

	VkPipeline pipeline{ VK_NULL_HANDLE };
	VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
	VkDescriptorSet descriptorSet{ VK_NULL_HANDLE };
	VkDescriptorSetLayout descriptorSetLayout{ VK_NULL_HANDLE };

	std::vector<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups{};
};