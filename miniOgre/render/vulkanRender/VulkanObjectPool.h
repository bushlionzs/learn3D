#pragma once

#include "OgreSingleton.h"
#include "VulkanUploadbuffer.h"
#include "shader.h"

enum VulkanObjectType
{
	VulkanObject_ObjectCB = 0,
	VulkanObject_MaterialCB = 1,
	VulkanObject_SkinnedCB = 2
};

struct VulkanObjectDesc
{
	VulkanObjectType _vkObjectType;
	uint32_t _vkObjectIndex = 0;
};

struct VulkanBufferInfo
{
	VkBuffer _vulkanBuffer;
	uint32_t _offset;
};

class VulkanRenderSystem;

class VulkanObjectPool
{
public:
	VulkanObjectPool();
	~VulkanObjectPool();

	void init(VulkanRenderSystem* vkrs);

	VulkanObjectDesc allocObject(VulkanObjectType vkType);
	void releaseObject(VulkanObjectDesc& desc);

	VulkanBufferInfo getObjectInfo(VulkanObjectDesc& desc);
	void updateObject(const VulkanObjectDesc& desc, const char* data, uint32_t size);
private:
	std::unique_ptr<VulkanUploadBuffer<ObjectConstantBuffer>>  mObjectCB;
	std::unique_ptr<VulkanUploadBuffer<MaterialConstantBuffer>>  mMaterialCB;
	std::unique_ptr<VulkanUploadBuffer<SkinnedConstantBuffer>> mSkinnedCB;

	std::unordered_set<int32_t> mObjectIndexSet;
	std::unordered_set<int32_t> mMaterialIndexSet;
	std::unordered_set<int32_t> mSkinnedCBSet;

	uint32_t mObjectCountMax = 10000;
	uint32_t mMaterialCountMax = 10000;
	uint32_t mSkinnedCountMax = 2000;
};