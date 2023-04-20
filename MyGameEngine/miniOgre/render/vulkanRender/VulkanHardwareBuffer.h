#pragma once
#include "OgreHardwareBuffer.h"
#include "VulkanCommon.h"
class VulkanRenderSystem;

class VulkanHardwareBuffer : public HardwareBuffer
{

public:
    VulkanHardwareBuffer(
        BufferType btype, 
        size_t vertexSize, 
        size_t numVerts, 
        HardwareBuffer::Usage usage,
        VulkanRenderSystem* engine);
    virtual ~VulkanHardwareBuffer();

    virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
    virtual void unlock();

    virtual void bind(int32_t slot) const;
private:
    VulkanRenderSystem* mEngine;

    int32_t mVertexSize;
    int32_t mNumVerts;
    BufferType mBufferType;

    VkBuffer mVkBuffer;
    VkDeviceMemory mVertexBufferMemory;
    VkMemoryRequirements mMemRequirements;
    VkPhysicalDeviceMemoryProperties mMemProperties;

    VkIndexType mVkIndexType;
};