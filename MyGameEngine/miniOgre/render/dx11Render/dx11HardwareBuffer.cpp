#include "OgreHeader.h"
#include "dx11HardwareBuffer.h"
#include "dx11RenderSystem.h"
#include "dx11Helper.h"

Dx11HardwareBuffer::Dx11HardwareBuffer(BufferType btype, size_t vertexSize, size_t numVerts, HardwareBuffer::Usage usage,
    Dx11RenderSystem* rs, bool streamOut)
{
    mBufferType = btype;
    mVertexSize = vertexSize;
    mNumVerts = numVerts;
    mRenderSystem = rs;
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_DYNAMIC;
    vbd.ByteWidth = (UINT)(vertexSize* numVerts);
    
    if (btype == INDEX_BUFFER)
    {
        vbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    }
    else
    {
        vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    }
    vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = DX11Helper::getSingleton().getDevice()->CreateBuffer(&vbd, nullptr, &mVertexBuffer);

    if (FAILED(hr))
    {
        int32_t kk = 0;
    }
   
    if (btype == INDEX_BUFFER)
    {
        if (vertexSize == 4)
        {
            mIndexFormat = DXGI_FORMAT_R32_UINT;
        }
        else
        {
            mIndexFormat = DXGI_FORMAT_R16_UINT;
        }
    }
}

Dx11HardwareBuffer::~Dx11HardwareBuffer()
{

}

void* Dx11HardwareBuffer::lockimpl(
    size_t offset, size_t length, LockOptions options)
{
    D3D11_MAPPED_SUBRESOURCE mappedData;
    mappedData.pData = nullptr;
    HRESULT hr = DX11Helper::getSingleton().getDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
    return mappedData.pData;
}

void Dx11HardwareBuffer::unlock()
{
    DX11Helper::getSingleton().getDeviceContext()->Unmap(mVertexBuffer, 0);
}

void Dx11HardwareBuffer::bind(int32_t slot) const
{
    auto context = DX11Helper::getSingleton().getDeviceContext();
    if (mBufferType == INDEX_BUFFER)
    {
        context->IASetIndexBuffer(mVertexBuffer, mIndexFormat, 0);
    }
    else
    {
        UINT stride = mVertexSize;			// 跨越字节数
        UINT offset = 0;							// 起始偏移量
        context->IASetVertexBuffers(slot, 1, &mVertexBuffer, &stride, &offset);
    }
    
}