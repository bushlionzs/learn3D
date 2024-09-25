#pragma once
#include "OgreHardwareBufferManager.h"

class VulkanHardwareBufferManager : public Ogre::HardwareBufferManager
{
public:
    VulkanHardwareBufferManager();
    virtual ~VulkanHardwareBufferManager();

    virtual std::shared_ptr<HardwareVertexBuffer>
        createVertexBuffer(
            size_t vertexSize, 
            size_t numVerts, 
            HardwareBuffer::Usage usage);

    virtual std::shared_ptr<HardwareIndexBuffer>
        createIndexBuffer(
            size_t vertexSize,
            size_t numIndexes,
            HardwareBuffer::Usage usage);
};