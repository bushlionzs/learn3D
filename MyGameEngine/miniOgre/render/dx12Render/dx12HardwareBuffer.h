#pragma once

#include "OgreHardwareVertexBuffer.h"
#include "dx12Common.h"

class Dx12RenderSystem;
class GraphicsCommandList;

class Dx12HardwareBuffer : public HardwareBuffer
{

public:
    Dx12HardwareBuffer(
        BufferType btype, 
        size_t vertexSize, 
        size_t numVerts, 
        HardwareBuffer::Usage usage);
    virtual ~Dx12HardwareBuffer();

    virtual void* lockimpl(size_t offset, size_t length, LockOptions options);
    virtual void unlock();

    void _copydataimpl(ID3D12GraphicsCommandList* cmdList, void* data, uint32_t size);

    virtual void bind(int32_t slot) const;

    void bind(ID3D12GraphicsCommandList* cmdList, int32_t slot);
private:
 

    int32_t mVertexSize;
    int32_t mNumVerts;
    BufferType mBufferType;

    std::string mMemBuffer;
    DXGI_FORMAT mIndexFormat;
    Microsoft::WRL::ComPtr<ID3D12Resource> BufferGPU = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> BufferUploader = nullptr;
};