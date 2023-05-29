#pragma once

#include "dx11Common.h"
#include "dx11Helper.h"
template<typename T>
class Dx11UploadBuffer
{
public:
    Dx11UploadBuffer(UINT elementCount, bool isConstantBuffer) :
        mIsConstantBuffer(isConstantBuffer)
    {
        D3D11_BUFFER_DESC cbd;
        ZeroMemory(&cbd, sizeof(cbd));
        cbd.Usage = D3D11_USAGE_DYNAMIC;
        cbd.ByteWidth = sizeof(T) * elementCount;
        cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        auto device = DX11Helper::getSingleton().getDevice();
        auto hr = device->CreateBuffer(&cbd, nullptr, &mConstantBuffer);
        if (FAILED(hr))
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to CreateBuffer using directx11!");
        }
    }

    ~Dx11UploadBuffer()
    {
    }

    ID3D11Buffer* Resource()const
    {
        return mConstantBuffer;
    }

    void CopyData(int elementIndex, const T& data)
    {
        auto context = DX11Helper::getSingleton().getDeviceContext();
        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = nullptr;
        context->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
        char* mapdata = (char*)mappedData.pData;
        memcpy(&mapdata[elementIndex* sizeof(T)], &data, sizeof(T));
        context->Unmap(mConstantBuffer, 0);
    }

    void CopyData(const char* data, uint32_t size)
    {
        auto context = DX11Helper::getSingleton().getDeviceContext();
        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = nullptr;
        context->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
        char* mapdata = (char*)mappedData.pData;
        memcpy(mapdata, data, size);
        context->Unmap(mConstantBuffer, 0);
    }

private:
    ID3D11Buffer* mConstantBuffer = nullptr;

    UINT mElementByteSize = 0;
    bool mIsConstantBuffer = false;
};