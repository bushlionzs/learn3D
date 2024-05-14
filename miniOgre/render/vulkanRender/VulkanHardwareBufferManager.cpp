#include "OgreHeader.h"
#include "OgreHeader.h"
#include "VulkanHardwareBufferManager.h"
#include "VulkanHardwareBuffer.h"

VulkanHardwareBufferManager::VulkanHardwareBufferManager()
{

}

VulkanHardwareBufferManager::~VulkanHardwareBufferManager()
{

}

std::shared_ptr<HardwareVertexBuffer>
VulkanHardwareBufferManager::VulkanHardwareBufferManager::createVertexBuffer
(
    size_t vertexSize, 
    size_t numVerts, 
    HardwareBuffer::Usage usage)
{
    VulkanHardwareBuffer* impl = 
        new VulkanHardwareBuffer(
            HardwareBuffer::VERTEX_BUFFER, 
            vertexSize, 
            numVerts,
            usage 
            );

    auto buf = std::make_shared<HardwareVertexBuffer>(vertexSize, numVerts, impl);
    return buf;
}

std::shared_ptr<HardwareIndexBuffer>
VulkanHardwareBufferManager::createIndexBuffer(
    size_t vertexSize,
    size_t numIndexes,
    HardwareBuffer::Usage usage)
{
    VulkanHardwareBuffer* impl = 
        new VulkanHardwareBuffer(
            HardwareBuffer::INDEX_BUFFER, 
            vertexSize,
            numIndexes,
            usage
            );

    auto buf = std::make_shared<HardwareIndexBuffer>(impl);
    return buf;
}