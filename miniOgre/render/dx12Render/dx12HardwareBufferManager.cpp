#include "OgreHeader.h"
#include "dx12HardwareBufferManager.h"
#include "dx12HardwareBuffer.h"

Dx12HardwareBufferManager::Dx12HardwareBufferManager(RenderSystem* engine)
    :HardwareBufferManager(engine)
{

}

Dx12HardwareBufferManager::~Dx12HardwareBufferManager()
{

}

std::shared_ptr<HardwareVertexBuffer>
Dx12HardwareBufferManager::createVertexBuffer(size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage)
{
    Dx12HardwareBuffer* impl = new Dx12HardwareBuffer(HardwareBuffer::VERTEX_BUFFER, vertexSize, numVerts,
        usage);

    auto buf = std::make_shared<HardwareVertexBuffer>(vertexSize, numVerts, impl);
    return buf;
}


std::shared_ptr<HardwareIndexBuffer>
Dx12HardwareBufferManager::createIndexBuffer(
    size_t vertexSize,
    size_t numIndexes,
    HardwareBuffer::Usage usage)
{
    Dx12HardwareBuffer* impl = new Dx12HardwareBuffer(HardwareBuffer::INDEX_BUFFER, vertexSize, numIndexes,
        usage);

    auto buf = std::make_shared<HardwareIndexBuffer>(impl);
    return buf;
}