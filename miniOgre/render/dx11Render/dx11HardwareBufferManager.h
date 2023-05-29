#pragma once

#include "OgreHardwareBufferManager.h"

class Dx11HardwareBufferManager : public HardwareBufferManager
{
public:
    Dx11HardwareBufferManager(RenderSystem* engine);
    virtual ~Dx11HardwareBufferManager();
    virtual std::shared_ptr<HardwareVertexBuffer>
        createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage);

    virtual std::shared_ptr<HardwareIndexBuffer>
        createIndexBuffer(
            size_t vertexSize,
            size_t numIndexes,
            HardwareBuffer::Usage usage);
};