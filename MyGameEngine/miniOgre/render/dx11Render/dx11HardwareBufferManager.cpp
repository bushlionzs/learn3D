#include "OgreHeader.h"
#include "dx11HardwareBufferManager.h"
#include "dx11HardwareBuffer.h"


Dx11HardwareBufferManager::Dx11HardwareBufferManager(RenderSystem* engine)
    :HardwareBufferManager(engine)
{

}

Dx11HardwareBufferManager::~Dx11HardwareBufferManager()
{

}


std::shared_ptr<HardwareVertexBuffer>
Dx11HardwareBufferManager::createVertexBuffer(
    size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage)
{
    Dx11HardwareBuffer* impl = new Dx11HardwareBuffer(HardwareBuffer::VERTEX_BUFFER, vertexSize, numVerts,
        usage, (Dx11RenderSystem*)mRenderSystem, false);

    auto buf = std::make_shared<HardwareVertexBuffer>(vertexSize, numVerts, impl);
    return buf;
}

std::shared_ptr<HardwareIndexBuffer>
Dx11HardwareBufferManager::createIndexBuffer(
    size_t vertexSize,
    size_t numIndexes,
    HardwareBuffer::Usage usage
    ) 
{
    Dx11HardwareBuffer* impl = new Dx11HardwareBuffer(HardwareBuffer::INDEX_BUFFER, vertexSize, numIndexes,
        usage, (Dx11RenderSystem*)mRenderSystem, false);

    auto buf = std::make_shared<HardwareIndexBuffer>(impl);
    return buf;
}