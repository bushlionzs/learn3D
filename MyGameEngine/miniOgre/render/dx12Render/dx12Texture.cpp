#include "OgreHeader.h"
#include "dx12Texture.h"
#include "OgreImage.h"
#include "dx12RenderSystem.h"
#include "OgreResourceManager.h"
#include "dx12TextureHandleManager.h"
#include "myutils.h"
#include "dx12Helper.h"
#include "dx12HardwarePixelBuffer.h"
#include "D3D12Mappings.h"
#include "dx12HardwareBuffer.h"
#include "OgreViewport.h"


Dx12Texture::Dx12Texture(
    const std::string& name, 
    Ogre::TextureProperty* texProperty, 
    Dx12RenderSystem* rs):ITexture(name, texProperty)
{
    mRenderSystem = rs;
}

Dx12Texture::~Dx12Texture()
{

}





void Dx12Texture::_createSurfaceList(void)
{
    // Create new list of surfaces
    mSurfaceList.clear();
    size_t depth = mTextureProperty._depth;

    for (size_t face = 0; face < mFace; ++face)
    {
        size_t width = mTextureProperty._width;
        size_t height = mTextureProperty._height;
        for (size_t mip = 0; mip <= mTextureProperty._numMipmaps; ++mip)
        {

            Dx12HardwarePixelBuffer* buffer;
            buffer = new Dx12HardwarePixelBuffer(
                this, // parentTexture
                mip,
                width,
                height,
                depth,
                face,
                mFormat,
                (HardwareBuffer::Usage)mUsage
            );

            mSurfaceList.push_back(HardwarePixelBufferPtr(buffer));

            if (width > 1) width /= 2;
            if (height > 1) height /= 2;
            if (depth > 1 && mTextureProperty._texType != TEX_TYPE_2D_ARRAY) depth /= 2;
        }
    }
}

void Dx12Texture::createInternalResourcesImpl(void)
{
    mFormat = D3D12Mappings::_getClosestSupportedPF(mFormat);

    mD3DFormat = D3D12Mappings::_getGammaFormat(D3D12Mappings::_getPF(mFormat), false);


    switch (mTextureProperty._texType)
    {
    case TEX_TYPE_2D:
    case TEX_TYPE_CUBE_MAP:
    case TEX_TYPE_2D_ARRAY:
        this->_create2DTex();
        break;
    default:
        this->freeInternalResources();
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "Unknown texture type", "D3D11Texture::createInternalResources");
    }

    _createSurfaceList();
    
}

void Dx12Texture::freeInternalResourcesImpl()
{
    mTex.Reset();
    mTexUpload.Reset();

}

void Dx12Texture::_create2DTex()
{
    ID3D12GraphicsCommandList* cmdList = DX12Helper::getSingleton().getCurrentCommandList();
    UINT numMips = mTextureProperty._numMipmaps + 1;

    D3D12_RESOURCE_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(D3D12_RESOURCE_DESC));
    texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    texDesc.Alignment = 0;
    texDesc.Width = mTextureProperty._width;
    texDesc.Height = mTextureProperty._height;
    texDesc.DepthOrArraySize = mFace;
    texDesc.MipLevels = numMips;
    texDesc.Format = mD3DFormat;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

    D3D12_RESOURCE_STATES states = D3D12_RESOURCE_STATE_COMMON;

    D3D12_CLEAR_VALUE* pvalue = nullptr;
    if (mUsage & TU_RENDERTARGET)
    {
        auto& backColor = mTextureProperty._backgroudColor;
        D3D12_CLEAR_VALUE ClearValue = {};
        ClearValue.Format = getDxFormat();
        memcpy(ClearValue.Color, &backColor, sizeof(float) * 4);
        pvalue = &ClearValue;
        texDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        states = D3D12_RESOURCE_STATE_GENERIC_READ;
        texDesc.SampleDesc.Count = 1;
    }
    else
    {
        texDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    }

    
    
    auto device = DX12Helper::getSingleton().getDevice();
    auto hr = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &texDesc,
        states,
        pvalue,
        IID_PPV_ARGS(&mTex)
    );

    if (FAILED(hr))
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "CreateCommittedResource failed!");
    }

    if (mUsage & TU_RENDERTARGET)
    {
        return;
    }

    const UINT num2DSubresources = texDesc.DepthOrArraySize * texDesc.MipLevels;
    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(mTex.Get(), 0, num2DSubresources);

    hr = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&mTexUpload));

    if (FAILED(hr))
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "CreateCommittedResource failed!");
    }
}

void Dx12Texture::postLoad()
{
    if (mUsage & TU_RENDERTARGET)
    {
        return;
    }


    updateTextureData();

   // generateMipmaps();

    DX12Helper::getSingleton()._submitCommandList();
}

void Dx12Texture::generateMipmaps()
{
    auto mipLevels = mTex->GetDesc().MipLevels;

    auto device = DX12Helper::getSingleton().getDevice();


    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = mipLevels;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRtvHeap));


    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
    UINT rtvSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    rtvHandle.Offset(rtvSize);
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = mD3DFormat;
    rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    rtvDesc.Texture2D.PlaneSlice = 0;
    for (UINT i = 1; i < mipLevels; ++i)
    {
        rtvDesc.Texture2D.MipSlice = i;
        device->CreateRenderTargetView(mTex.Get(), &rtvDesc, rtvHandle);
        rtvHandle.Offset(rtvSize);
    }

    
    ID3D12GraphicsCommandList* cl = DX12Helper::getSingleton().getMipmapCommandList();
    
   
   /* for (UINT i = 1; i < mipLevels; ++i)
    {
        cl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mTex.Get(),
            D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET, i));

        CD3DX12_CPU_DESCRIPTOR_HANDLE mipRtvHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart(), i, rtvSize);
        cl->ClearRenderTargetView(mipRtvHandle, DirectX::Colors::Gold, 0, nullptr);
    }*/

    auto mgr = DX12Helper::getSingleton().getDx12RenderSystem()->getTextureHandleManager();
    if (mTexStartIndex < 0)
    {
        mTexStartIndex = mgr->allocStartIndex(10);
    }
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    srvDesc.Format = mTex->GetDesc().Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = mipLevels;
    auto handle = mgr->getCpuHandleByIndex(mTexStartIndex);
    device->CreateShaderResourceView(mTex.Get(), &srvDesc, handle);


    std::vector<ID3D12DescriptorHeap*> dhs = mgr->getHeaps();
    cl->SetDescriptorHeaps(dhs.size(), dhs.data());
    cl->SetGraphicsRootSignature(DX12Helper::getSingleton().getMipmapRootSignature());
    cl->SetPipelineState(DX12Helper::getSingleton().getMipmapPipelineState());
    auto vertexbuffer = DX12Helper::getSingleton().getMipmapVetexBuffer();
    vertexbuffer->bind(cl, 0);
    auto cb = DX12Helper::getSingleton().getMipmapFrameCB();
    D3D12_GPU_VIRTUAL_ADDRESS frameAddress = cb->Resource()->GetGPUVirtualAddress();
    cl->SetGraphicsRootConstantBufferView(1, frameAddress);
    int width = getWidth();
    int height = getHeight();

    
    for (UINT i = 1; i < mipLevels; ++i)
    {
        width = 256;
        height = 256;
        D3D12_VIEWPORT mViewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };
        D3D12_RECT mScissorRect = { 0, 0, (int)width, (int)height };
        cl->RSSetViewports(1, &mViewport);
        cl->RSSetScissorRects(1, &mScissorRect);
        cl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mTex.Get(),
            D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET, i));
        
        CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle = mgr->getGpuHandleByIndex(mTexStartIndex);
        cl->SetGraphicsRootDescriptorTable(0, gpuHandle);
        cl->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        CD3DX12_CPU_DESCRIPTOR_HANDLE mipRtvHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart(), i, rtvSize);
        cl->OMSetRenderTargets(1, &mipRtvHandle, FALSE, nullptr);
        cl->ClearRenderTargetView(mipRtvHandle, DirectX::Colors::Gold, 0, nullptr);
        cl->DrawInstanced(6, 1, 0, 0);

        cl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mTex.Get(),
            D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, i));

       }

}

void Dx12Texture::updateTextureData()
{
    if (mSurfaceList.empty())
    {
        return;
    }
    std::vector<D3D12_SUBRESOURCE_DATA> subResourceData;
    subResourceData.resize(mSurfaceList.size());

    int32_t bytes = 4;
    for (auto i = 0; i < mSurfaceList.size(); i++)
    {
        HardwareBufferLockGuard lock(mSurfaceList[i].get());
        subResourceData[i].pData = lock.data();
        subResourceData[i].RowPitch = bytes * mSurfaceList[i]->getWidth();
        subResourceData[i].SlicePitch =
            mSurfaceList[i]->getWidth() * mSurfaceList[i]->getHeight() * bytes;
    }

    ID3D12GraphicsCommandList* cmdList = DX12Helper::getSingleton().getCurrentCommandList();

    UpdateSubresources(
        cmdList,
        mTex.Get(),
        mTexUpload.Get(),
        0,
        0,
        mSurfaceList.size(),
        subResourceData.data());

}

void Dx12Texture::buildDescriptorHeaps(int32_t handleIndex)
{
    auto device = DX12Helper::getSingleton().getDevice();
    if (!mCreate)
    {
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = mTex->GetDesc().MipLevels;
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        ThrowIfFailed(device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        if (this->isCubeTexture())
        {
            srvDesc.Format = mTex->GetDesc().Format;
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
            srvDesc.TextureCube.MostDetailedMip = 0;
            srvDesc.TextureCube.MipLevels = mTex->GetDesc().MipLevels;
            srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
        }
        else
        {
            srvDesc.Format = mTex->GetDesc().Format;
            if (mUsage & TU_RENDERTARGET)
            {
                srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
            }
            else
            {
                srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            }
            
            srvDesc.Texture2D.MostDetailedMip = 0;
            srvDesc.Texture2D.MipLevels = mTex->GetDesc().MipLevels;
        }

        mDescriptorHandle = mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
        device->CreateShaderResourceView(mTex.Get(), &srvDesc, mDescriptorHandle);

        mCreate = true;
    }
    Dx12TextureHandleManager* mgr = mRenderSystem->getTextureHandleManager();
    auto dstHandle = mgr->getCpuHandleByIndex(handleIndex);
    device->CopyDescriptorsSimple(1, dstHandle, mDescriptorHandle,
        D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void Dx12Texture::createRenderTarget()
{
    
}
