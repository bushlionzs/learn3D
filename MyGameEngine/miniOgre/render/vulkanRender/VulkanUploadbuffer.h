#pragma once
#include "VulkanHelper.h"

template<typename T>
class VulkanUploadBuffer
{
public:
    VulkanUploadBuffer(
        uint32_t elementCount, 
        bool isConstantBuffer) :
        mElementCount(elementCount),
        mIsConstantBuffer(isConstantBuffer)
    {

        mObjectSize = sizeof(T);
        
        auto& vkDeviceProperties = VulkanHelper::getSingleton()._getVkPhysicalDeviceProperties();

        int32_t left = mObjectSize % vkDeviceProperties.limits.minUniformBufferOffsetAlignment;
        mObjectSize -= left;
        
        if (left > 0)
        {
            mObjectSize += (int32_t)vkDeviceProperties.limits.minUniformBufferOffsetAlignment;
        }
        VulkanHelper::getSingleton()._createBuffer(
            mObjectSize * elementCount,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            mUniformBuffer,
            mUniformBufferMemory
        );

        mDevice = VulkanHelper::getSingleton()._getVkDevice();
        vkMapMemory(
            mDevice,
            mUniformBufferMemory, 
            0, 
            VK_WHOLE_SIZE, 
            0, (void**)&mMappedData);
    }

    ~VulkanUploadBuffer()
    {
        vkUnmapMemory(mDevice, mUniformBufferMemory);
    }

    void CopyData(int elementIndex, const T& data)
    {
        memcpy(&mMappedData[elementIndex * mObjectSize], &data, sizeof(T));
    }

    void CopyData(int elementIndex, const char* data, uint32_t size)
    {
        memcpy(&mMappedData[elementIndex * mObjectSize], data, size);
    }

    VkBuffer getVKBuffer()
    {
        return mUniformBuffer;
    }

    uint32_t getObjectSize()
    {
        return mObjectSize;
    }
private:
    bool mIsConstantBuffer;
    uint32_t mElementCount;
    VkBuffer mUniformBuffer;
    VkDeviceMemory mUniformBufferMemory;
    VkDevice mDevice;
    char* mMappedData = nullptr;

    int32_t mObjectSize = 0;
};