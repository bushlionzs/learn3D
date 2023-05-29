#pragma once

#include "OgreHardwareBufferManager.h"


class Dx12HardwareBufferManager : public Ogre::HardwareBufferManager
{
public:
    Dx12HardwareBufferManager(RenderSystem* engine);
    virtual ~Dx12HardwareBufferManager();

    virtual std::shared_ptr<HardwareVertexBuffer>
        createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage);

    virtual std::shared_ptr<HardwareIndexBuffer>
        createIndexBuffer(
            size_t vertexSize,
            size_t numIndexes,
            HardwareBuffer::Usage usage);
};