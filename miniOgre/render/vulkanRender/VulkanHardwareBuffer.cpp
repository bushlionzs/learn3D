#include "OgreHeader.h"
#include "VulkanHardwareBuffer.h"
#include "VulkanRenderSystem.h"
#include "VulkanHelper.h"

VulkanHardwareBuffer::VulkanHardwareBuffer(
    BufferType btype,
    size_t vertexSize,
    size_t numVerts,
    HardwareBuffer::Usage usage,
    VulkanRenderSystem* engine)
{
    mEngine = engine;
    mBufferType = btype;
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = vertexSize * numVerts;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    VkBufferUsageFlags flags = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if (mBufferType == INDEX_BUFFER)
    {
        flags = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        if (vertexSize == 2)
        {
            mVkIndexType = VK_INDEX_TYPE_UINT16;
        }
        else
        {
            mVkIndexType = VK_INDEX_TYPE_UINT32;
        }
    }

    mVertexSize = vertexSize;
    mNumVerts = numVerts;
    VulkanHelper::getSingleton()._createBuffer(
        vertexSize * numVerts,
        flags,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        mVkBuffer,
        mVertexBufferMemory
    );
    mSizeInBytes = vertexSize * numVerts;
}

VulkanHardwareBuffer::~VulkanHardwareBuffer()
{

}

void* VulkanHardwareBuffer::lockimpl(size_t offset, size_t length, LockOptions options)
{
    auto device = VulkanHelper::getSingleton()._getVkDevice();
    void* gpudata;
    vkMapMemory(device, mVertexBufferMemory, offset, length, 0, &gpudata);
    return gpudata;
}

void VulkanHardwareBuffer::unlock()
{
    auto device = VulkanHelper::getSingleton()._getVkDevice();
    vkUnmapMemory(device, mVertexBufferMemory);
}

void VulkanHardwareBuffer::bind(int32_t slot, void* cb) const
{
    VkCommandBuffer commandbuffer = (VkCommandBuffer)cb;
    if (mBufferType == VERTEX_BUFFER)
    {
        VkDeviceSize offsets[1] = { 0 };
        vkCmdBindVertexBuffers(commandbuffer, slot, 1, &mVkBuffer, offsets);
    }
    else
    {
        vkCmdBindIndexBuffer(commandbuffer, mVkBuffer, 0, mVkIndexType);
    }
}