#pragma once

#include "OgreHardwareVertexBuffer.h"
#include <d3d11_1.h>

class Dx11RenderSystem;

class Dx11HardwareBuffer : public HardwareBuffer
{

public:
    Dx11HardwareBuffer(BufferType btype, size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage,
        Dx11RenderSystem* rs, bool streamOut);
    virtual ~Dx11HardwareBuffer();

    virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
    virtual void unlock();
    virtual void bind(int32_t slot, void* cb) const;
private:
    Dx11RenderSystem* mRenderSystem;
    ID3D11Buffer* mVertexBuffer = nullptr;
    int32_t mNumVerts;
    BufferType mBufferType;
    DXGI_FORMAT mIndexFormat;
};