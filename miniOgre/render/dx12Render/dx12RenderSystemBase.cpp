#include "OgreHeader.h"
#include "dx12RenderSystemBase.h"
#define USE_PIX
#if defined(USE_PIX)
#include "ForgeConfig.h"
#include <winpixeventruntime/pix3.h>
#endif 
#include "OgreMoveObject.h"
#include "OgreMaterial.h"
#include "OgreRenderable.h"
#include "OgreTextureUnit.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreCamera.h"
#include "OgreViewport.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreStringConverter.h"
#include "OgreResourceManager.h"
#include "dx12Shader.h"
#include "dx12Texture.h"
#include "dx12Handles.h"
#include "dx12RenderTarget.h"
#include "dx12Commands.h"
#include "dx12RenderWindow.h"
#include "dx12Helper.h"
#include "D3D12Mappings.h"
#include "d3dutil.h"
#include "dx12SwapChain.h"
#include "memoryAllocator.h"

extern "C" void SetObjectName(ID3D12Object* pObject, const char* pName);

#define CALC_SUBRESOURCE_INDEX(MipSlice, ArraySlice, PlaneSlice, MipLevels, ArraySize) \
    ((MipSlice) + ((ArraySlice) * (MipLevels)) + ((PlaneSlice) * (MipLevels) * (ArraySize)))


Dx12RenderSystemBase::Dx12RenderSystemBase()
    :mResourceAllocator(83886080, false)
{
	mRenderSystemName = "Directx12";
    mRenderType = EngineType_Dx12;
}


Dx12RenderSystemBase::~Dx12RenderSystemBase()
{

}



bool Dx12RenderSystemBase::engineInit()
{
	RenderSystem::engineInit();

	auto helper = new DX12Helper(this);
	helper->createBaseInfo();
    mDevice = helper->getDevice();
    mCommands = new DX12Commands(mDevice);
    mCommands = nullptr;
    mMemoryAllocator = new DxMemoryAllocator(mDevice);


    mDescriptorHeapContext = helper->getHeapContext();

    D3D12_COMMAND_SIGNATURE_DESC desc = {};
    D3D12_INDIRECT_ARGUMENT_DESC arg = {};
    arg.Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED;
    desc.NumArgumentDescs = 1;
    desc.pArgumentDescs = &arg;
    desc.ByteStride = sizeof(IndirectDrawIndexArguments);
    auto hr = mDevice->CreateCommandSignature(
        &desc, NULL, IID_PPV_ARGS(&mDrawIndexCommandSignature));

    mCommandBuffer = createCommandBuffer(QUEUE_TYPE_GRAPHICS);

    beginDefaultCommandList();
    
    mCommandFence = createFence(true);

    mTextureListen = new Dx12TextureListen;
	return true;
}

void Dx12RenderSystemBase::ready()
{
}

Ogre::RenderWindow* Dx12RenderSystemBase::createRenderWindow(
    const CreateWindowDesc& desc)
{
    uint64_t wnd = (uint64_t)StringConverter::parseSizeT(desc.windowHandle);
    uint64_t flags = 0;
    if (desc.srgb)
    {
        flags = SWAP_CHAIN_CONFIG_SRGB_COLORSPACE;
    }
    mRenderWindow = new Dx12RenderWindow(wnd, flags);
    return mRenderWindow;
}

Ogre::RenderTarget* Dx12RenderSystemBase::createRenderTarget(
    const String& name,
    TextureProperty& texProperty)
{
    D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

    DxDescriptorID targetId = -1;
    if (texProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
    }
    else if (texProperty._tex_usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
    {
    }
    else if (texProperty._tex_usage.has_flag(TEXTURE_USAGE_CAN_UPDATE_BIT))
    {
    }
    else
    {
        assert_invariant(false);
    }

    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    Dx12RenderTarget* renderTarget = new Dx12RenderTarget(name, cb, &texProperty);


    return renderTarget;
}

void Dx12RenderSystemBase::clearRenderTarget(
    Ogre::RenderTarget* target, const Ogre::Vector4& color)
{
    ID3D12GraphicsCommandList* cl = mCommands->get();
    Dx12Texture* tex = (Dx12Texture*)target->getTarget();
    DxDescriptorID targetId = tex->getTargetDescriptorId();
    auto cpuHandle = descriptor_id_to_cpu_handle(
        mDescriptorHeapContext->mCPUDescriptorHeaps[0], targetId);
    auto uavGpuHandle = descriptor_id_to_gpu_handle(
        mDescriptorHeapContext->mCPUDescriptorHeaps[0], targetId);
    cl->ClearUnorderedAccessViewFloat(uavGpuHandle, cpuHandle, 
        tex->getResource(), color.ptr(), 0, nullptr);
}

void Dx12RenderSystemBase::frameStart()
{
    /*bool reized = false;
    mSwapChain->acquire(reized);

    auto* cl = mCommands->get();
    ID3D12DescriptorHeap* heaps[] = 
    { 
        mDescriptorHeapContext->mCbvSrvUavHeaps[0]->pHeap,
        mDescriptorHeapContext->pSamplerHeaps[0]->pHeap
    };
    cl->SetDescriptorHeaps(2, heaps);

    mLastPipelineState = nullptr;*/

    this->beginDefaultCommandList();
}

void Dx12RenderSystemBase::frameEnd()
{
}

void Dx12RenderSystemBase::present()
{
    //mSwapChain->present();
}

void Dx12RenderSystemBase::copyImage(
    Handle<HwCommandBuffer>cbh,
    Ogre::RenderTarget* dst,
    Ogre::RenderTarget* src,
    ImageCopyDesc& desc)
{
    Dx12Texture* dstTexture = (Dx12Texture*)dst->getTarget();
    Dx12Texture* srcTexture  = (Dx12Texture*)src->getTarget();

    copyImage(cbh, dstTexture, srcTexture, desc);
}

void Dx12RenderSystemBase::copyImage(
    Handle<HwCommandBuffer>cbh,
    OgreTexture* dst,
    OgreTexture* src,
    ImageCopyDesc& desc)
{
    auto width = desc.extent.width;
    auto height = desc.extent.height;
    auto depth = desc.extent.depth;
    ID3D12GraphicsCommandList* cl = nullptr;
    if (cbh)
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
        cl = cb->get();
    }
    else
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
        cl = cb->get();
    }

    Dx12Texture* srcTexture = (Dx12Texture*)src;
    Dx12Texture* dstTexture = (Dx12Texture*)dst;

    D3D12_TEXTURE_COPY_LOCATION srcLocation = {};
    srcLocation.pResource = srcTexture->getResource();
    srcLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    srcLocation.SubresourceIndex = D3D12CalcSubresource(
        desc.srcSubresource.mipLevel, 0, 0, 1, 1);

    D3D12_TEXTURE_COPY_LOCATION dstLocation = {};
    dstLocation.pResource = dstTexture->getResource();
    dstLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;

    // 设置SubresourceIndex为目标CubeMap的特定面
    // CubeMap面的索引顺序是：+X, -X, +Y, -Y, +Z, -Z
    uint32_t MipLevels = static_cast<UINT>(floor(log2(std::max(dstTexture->getWidth(), dstTexture->getHeight())))) + 1;
    UINT dstSubresource = D3D12CalcSubresource(
        desc.dstSubresource.mipLevel,
        desc.dstSubresource.baseArrayLayer, 0, MipLevels, 1);
    dstLocation.SubresourceIndex = dstSubresource;

    // 执行拷贝
    CD3DX12_BOX srcBox(0, 0, width, height); // 定义源纹理的矩形区域
    cl->CopyTextureRegion(&dstLocation, 0, 0, 0, &srcLocation, &srcBox);
}

void Dx12RenderSystemBase::setViewport(
    float x, float y, float width, float height, float minDepth, float maxDepth,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    D3D12_VIEWPORT viewport;
    
    viewport.TopLeftX = x;
    viewport.TopLeftY = y;
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MinDepth = minDepth;
    viewport.MaxDepth = maxDepth;
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
        
    auto* cl = cb->get();
    cl->RSSetViewports(1, &viewport);
}

void Dx12RenderSystemBase::setScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    D3D12_RECT scissorRect;
    scissorRect = { (LONG)x, (LONG)y, (LONG)width, (LONG)height };
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    auto* cl = cb->get();
    cl->RSSetScissorRects(1, &scissorRect);
}
void Dx12RenderSystemBase::beginRenderPass(RenderPassInfo& renderPassInfo)
{
    DX12CommandBuffer* cb = nullptr;
    if (renderPassInfo.cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(renderPassInfo.cbh);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    auto* cl = cb->get();
    uint32_t width = 0;
    uint32_t height = 0;

    bool hasColor = false;
    float* ptr = (float*)&renderPassInfo.renderTargets->clearColour;
    D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle[8];
    for (auto i = 0; i < renderPassInfo.renderTargetCount; i++)
    {
        Dx12RenderTarget* colorTarget = (Dx12RenderTarget*)renderPassInfo.renderTargets[i].target.renderTarget;
        auto* tex = colorTarget->getTarget();
        DxDescriptorID srcid = tex->getTargetDescriptorId();
        DescriptorHeap* heap = mDescriptorHeapContext->mCPUDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_RTV];
        auto cpuHandle = descriptor_id_to_cpu_handle(heap, srcid);
        renderTargetHandle[i] = cpuHandle;
        cl->ClearRenderTargetView(cpuHandle, ptr, 0, nullptr);
        hasColor = true;
    }
    bool hasDepth = false;
    D3D12_CPU_DESCRIPTOR_HANDLE depthHandle;
    if (renderPassInfo.depthTarget.target.depthStencil)
    {
        Dx12RenderTarget* depthTarget = (Dx12RenderTarget*)renderPassInfo.depthTarget.target.depthStencil;
        auto* tex = depthTarget->getTarget();
        DxDescriptorID srcid = tex->getTargetDescriptorId();
        srcid += renderPassInfo.depthTarget.depthIndex;
        depthHandle = descriptor_id_to_cpu_handle(mDescriptorHeapContext->mCPUDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_DSV], srcid);
        cl->ClearDepthStencilView(depthHandle, D3D12_CLEAR_FLAG_DEPTH,
            renderPassInfo.depthTarget.clearValue.depth, renderPassInfo.depthTarget.clearValue.stencil, 0, nullptr);

        hasDepth = true;
    }

    if (hasColor)
    {
        Dx12RenderTarget* colorTarget = (Dx12RenderTarget*)renderPassInfo.renderTargets[0].target.renderTarget;
        width = colorTarget->getWidth();
        height = colorTarget->getHeight();
    }
    else if (hasDepth)
    {
        Dx12RenderTarget* depthTarget = (Dx12RenderTarget*)renderPassInfo.depthTarget.target.depthStencil;
        width = depthTarget->getWidth();
        height = depthTarget->getHeight();
    }
    else
    {
        width = renderPassInfo.extent[0];
        height = renderPassInfo.extent[1];
    }

    cl->OMSetRenderTargets(renderPassInfo.renderTargetCount, renderTargetHandle, 
        FALSE, hasDepth?&depthHandle:NULL);

    /*if (renderPassInfo.viewport)
    {
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        scissorRect = { 0, 0, (LONG)width, (LONG)height };
        cl->RSSetViewports(1, &viewport);
        cl->RSSetScissorRects(1, &scissorRect);
    }*/
    
}

void Dx12RenderSystemBase::endRenderPass(RenderPassInfo& renderPassInfo)
{
}

void Dx12RenderSystemBase::bindPipeline(
    Handle<HwPipeline> pipelineHandle,
    const Handle<HwDescriptorSet>* descSets,
    uint32_t setCount)
{
    DX12Pipeline* dx12Pipeline = mResourceAllocator.handle_cast<DX12Pipeline*>(pipelineHandle);
    ID3D12PipelineState* pso = dx12Pipeline->getPipeline();
    DX12ProgramImpl* dx12ProgramImpl = dx12Pipeline->getProgram();
    ID3D12GraphicsCommandList* cl = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer)->get();
    auto rootSignature = dx12ProgramImpl->getRootSignature();
    cl->SetGraphicsRootSignature(rootSignature);
    //if (mLastPipelineState != pso)
    {
        
        cl->SetPipelineState(pso);
        mLastPipelineState = pso;
    }
    
    cl->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    for (uint32_t i = 0; i < setCount; i++)
    {
        if (!descSets[i])
            continue;
        DX12DescriptorSet* dset = mResourceAllocator.handle_cast<DX12DescriptorSet*>(descSets[i]);
        const std::vector<const DescriptorInfo*>& descriptorInfos = dset->getDescriptorInfos();
        auto cbvSrvUavHandle = dset->getCbvSrvUavHandle();
        
        for (auto descriptorInfo : descriptorInfos)
        {
            if (descriptorInfo->mType == D3D_SIT_SAMPLER)
            {
                auto samplerHandle = dset->getSamplerHandle(descriptorInfo->mSetIndex);
                auto gpuHandle = descriptor_id_to_gpu_handle(
                    mDescriptorHeapContext->pSamplerHeaps[0], samplerHandle);
                cl->SetGraphicsRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
            }
            else
            {
                auto gpuHandle = descriptor_id_to_gpu_handle(
                    mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV], cbvSrvUavHandle + descriptorInfo->mSetIndex);
                cl->SetGraphicsRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
            }
            
        }
    }
}

void Dx12RenderSystemBase::drawIndexed(
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    uint32_t vertexOffset,
    uint32_t firstInstance,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    ID3D12GraphicsCommandList* cl = cb->get();
    cl->DrawIndexedInstanced(
        indexCount,
        1, firstIndex, vertexOffset, firstInstance);
}

void Dx12RenderSystemBase::draw(
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    ID3D12GraphicsCommandList* cl = cb->get();
    cl->DrawInstanced(vertexCount, instanceCount, firstVertex, firstInstance);
}

void Dx12RenderSystemBase::drawIndexedIndirect(
    Handle<HwBufferObject> drawBuffer,
    uint32_t offset,
    uint32_t drawCount,
    uint32_t stride,
    Handle<HwCommandBuffer>* cbh
)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    ID3D12GraphicsCommandList* cl = cb->get();

    DX12BufferObject* bufferObject =
        mResourceAllocator.handle_cast<DX12BufferObject*>(drawBuffer);
    cl->ExecuteIndirect(mDrawIndexCommandSignature, drawCount, bufferObject->getResource(), offset, NULL, 0);
}

void Dx12RenderSystemBase::bindComputePipeline(
    Handle<HwComputeProgram> pipelineHandle,
    Handle<HwCommandBuffer> cbh,
    const Handle<HwDescriptorSet>* descSets,
    uint32_t setCount)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    ID3D12GraphicsCommandList* cl = cb->get();

    DX12ComputeProgram* program =
        mResourceAllocator.handle_cast<DX12ComputeProgram*>(pipelineHandle);

    cl->SetPipelineState(program->getPSO());
    cl->SetComputeRootSignature(program->getProgramImpl()->getRootSignature());
    for (uint32_t i = 0; i < setCount; i++)
    {
        DX12DescriptorSet* dset = mResourceAllocator.handle_cast<DX12DescriptorSet*>(descSets[i]);
        std::vector<const DescriptorInfo*> descriptorInfos = dset->getDescriptorInfos();
        auto cbvSrvUavHandle = dset->getCbvSrvUavHandle();

        for (auto descriptorInfo : descriptorInfos)
        {
            if (descriptorInfo->mType == D3D_SIT_SAMPLER)
            {
                auto samplerHandle = dset->getSamplerHandle(descriptorInfo->mSetIndex);
                auto gpuHandle = descriptor_id_to_gpu_handle(
                    mDescriptorHeapContext->pSamplerHeaps[0], samplerHandle);
                cl->SetComputeRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
            }
            else
            {
                auto gpuHandle = descriptor_id_to_gpu_handle(
                    mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV], cbvSrvUavHandle + descriptorInfo->mSetIndex);
                cl->SetComputeRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
                int kk = 0;
            }
        }
    }
}

void Dx12RenderSystemBase::dispatchComputeShader(int32_t x, int32_t y, int32_t z, Handle<HwCommandBuffer>* cbh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
    ID3D12GraphicsCommandList* cl = cb->get();
    cl->Dispatch(x, y, z);
}

void Dx12RenderSystemBase::pushGroupMarker(Handle<HwCommandBuffer> cbh, const char* maker, const Ogre::Vector3i& color)
{
#if defined(USE_PIX)
    
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    ID3D12GraphicsCommandList* cl = cb->get();
    PIXBeginEvent(cl, PIX_COLOR((BYTE)(color.x), (BYTE)(color.y), (BYTE)color.z), maker);
#endif
}
void Dx12RenderSystemBase::popGroupMarker(Handle<HwCommandBuffer> cbh)
{
#if defined(USE_PIX)
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    ID3D12GraphicsCommandList* cl = cb->get();
    PIXEndEvent(cl);
#endif
}

void Dx12RenderSystemBase::bindVertexBuffer(
    Handle<HwBufferObject> bufHandle, 
    uint32_t binding,
    uint32_t vertexSize)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(bufHandle);
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    auto* cl = cb->get();

    D3D12_VERTEX_BUFFER_VIEW vbv;
    vbv.BufferLocation = bo->getGPUVirtualAddress();
    vbv.StrideInBytes = vertexSize;
    vbv.SizeInBytes = bo->getByteCount();
    cl->IASetVertexBuffers(binding, 1, &vbv);
}

void Dx12RenderSystemBase::bindIndexBuffer(
    Handle<HwBufferObject> bufHandle, 
    uint32_t indexSize,
    uint32_t offset) 
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(bufHandle);
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    auto* cl = cb->get();
    D3D12_INDEX_BUFFER_VIEW ibv;
    ibv.BufferLocation = bo->getGPUVirtualAddress();
    ibv.Format = indexSize==2? DXGI_FORMAT_R16_UINT: DXGI_FORMAT_R32_UINT;
    ibv.SizeInBytes = bo->getByteCount();
    cl->IASetIndexBuffer(&ibv);
}

void* Dx12RenderSystemBase::lockBuffer(
    Handle<HwBufferObject> boh, uint32_t offset, uint32_t numBytes)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    return bo->lock(offset, numBytes);
}

void Dx12RenderSystemBase::unlockBuffer(Handle<HwBufferObject> boh)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);

    auto* cmdList = mCommands->get();
    bo->unlock(cmdList);
}


Handle<HwBufferObject> Dx12RenderSystemBase::createBufferObject(
    BufferDesc& desc)
{
    Handle<HwBufferObject> boh = mResourceAllocator.allocHandle<DX12BufferObject>();

    DescriptorHeap* pHeap = mDescriptorHeapContext->mCPUDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV];
    bool cpu_to_gpu = desc.mMemoryUsage == RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
    DX12BufferObject* bufferObject = mResourceAllocator.construct<DX12BufferObject>(
        boh, mDescriptorHeapContext, desc, pHeap, cpu_to_gpu);

    ID3D12Resource* resource = bufferObject->getResource();
    SetObjectName(resource, desc.pName);
    return boh;
}

void Dx12RenderSystemBase::updateBufferObject(
    Handle<HwBufferObject> boh,
    const char* data,
    uint32_t size,
    uint32_t offset,
    Handle<HwCommandBuffer>* cbh)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    

    ID3D12GraphicsCommandList* cmdList = nullptr;
   
    if (cbh)
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(*cbh);
        cmdList = cb->get();
    }
    else
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
        cmdList = cb->get();
    }
    

    bo->copyData(cmdList, data, size, offset);
}


bool Dx12RenderSystemBase::getBufferInfo(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    Ogre::BufferDesc& desc)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    desc.mSize = bo->getByteCount();
    return true;
}

void Dx12RenderSystemBase::clearBufferObject(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    uint32_t size = bo->getByteCount();
    void* data = bo->lock(0, size);
    memset(data, 0, size);
    bo->unlock(cb->get());
}

uint8_t* Dx12RenderSystemBase::bufferMap(Handle<HwBufferObject> boh)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    uint32_t size = bo->getByteCount();
    void* data = bo->lock(0, size);
    return (uint8_t*)data;
}

void Dx12RenderSystemBase::bufferUnmap(Handle<HwBufferObject> boh, Handle<HwCommandBuffer> cbh)
{
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    ID3D12GraphicsCommandList* cl;
    if (cbh)
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
        cl = cb->get();
    }
    else
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
        cl = cb->get();
    }
    bo->unlock(cl);
}

bool Dx12RenderSystemBase::getBufferObject(filament::backend::Handle<filament::backend::HwBufferObject> boh,
    char* data,
    uint32_t size,
    uint32_t offset)
{
    assert_invariant(false);
    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
    uint32_t byteCount = bo->getByteCount();
    assert_invariant(offset + size <= byteCount);
    const char* src = (const char*)bo->lock(0, size);
    memcpy(data, src + offset, size);
    return true;
}

Handle<HwDescriptorSetLayout> Dx12RenderSystemBase::getDescriptorSetLayout(
    Handle<HwProgram> programHandle, uint32_t set)
{
    return Handle<HwDescriptorSetLayout>();
}


Handle<HwPipelineLayout> Dx12RenderSystemBase::createPipelineLayout(
    std::array<Handle<HwDescriptorSetLayout>, 4>& layouts)
{
    return Handle<HwPipelineLayout>();
}

Handle<HwProgram> Dx12RenderSystemBase::createShaderProgram(
    const ShaderInfo& shaderInfo, VertexDeclaration* decl)
{
    Handle<HwProgram> programHandle = mResourceAllocator.allocHandle<DX12Program>();

    DX12Program* program = mResourceAllocator.construct<DX12Program>(programHandle,
        shaderInfo, decl);

    return programHandle;
}


Handle<HwSampler> Dx12RenderSystemBase::createTextureSampler(
    filament::backend::SamplerParams& samplerParams)
{
    Handle<HwSampler> samplerHandle = mResourceAllocator.allocHandle<DX12Sampler>();
    DxDescriptorID id = DX12Helper::getSingleton().getSampler(samplerParams);
    DX12Sampler* sampler = mResourceAllocator.construct<DX12Sampler>(samplerHandle, id);
    return samplerHandle;
}

Handle<HwComputeProgram> Dx12RenderSystemBase::createComputeProgram(
    const ShaderInfo& shaderInfo)
{
    Handle<HwComputeProgram> program = mResourceAllocator.allocHandle<DX12ComputeProgram>();
    DX12ComputeProgram* computeProgram = mResourceAllocator.construct<DX12ComputeProgram>(program, shaderInfo);
    DX12ProgramImpl* pImpl = computeProgram->getProgramImpl();
    D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.pRootSignature = pImpl->getRootSignature();
    const std::string* blob = pImpl->getComputeBlob();
    psoDesc.CS = { reinterpret_cast<const BYTE*>(blob->c_str()), blob->size()};
    ID3D12PipelineState* pipelineState;
    auto hr = mDevice->CreateComputePipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));
    assert_invariant(hr == S_OK);
    computeProgram->updatePSO(pipelineState);
    return program;
}

Handle<HwDescriptorSet> Dx12RenderSystemBase::createDescriptorSet(
    Handle<HwComputeProgram> programHandle,
    uint32_t set)
{
    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<DX12DescriptorSet>();
    DX12ComputeProgram* computeProgram = 
        mResourceAllocator.handle_cast<DX12ComputeProgram*>(programHandle);

    DX12ProgramImpl* programImpl = computeProgram->getProgramImpl();
    DX12DescriptorSet* dx12DescSet = mResourceAllocator.construct<DX12DescriptorSet>(
        dsh, programImpl, set);

    uint32_t cbvSrvUavDescCount = programImpl->getCbvSrvUavDescCount(set);

    DxDescriptorID cbvSrvUavHandle = consume_descriptor_handles(mDescriptorHeapContext->mCbvSrvUavHeaps[0], cbvSrvUavDescCount);
    dx12DescSet->updateCbvSrvUavHandle(cbvSrvUavHandle, cbvSrvUavDescCount);
    return dsh;
}

Handle<HwPipeline> Dx12RenderSystemBase::createPipeline(
    backend::RasterState& rasterState,
    Handle<HwProgram>& program
)
{
    Handle<HwPipeline> pipelineHandle = mResourceAllocator.allocHandle<DX12Pipeline>();
    DX12Program* dx12Program = mResourceAllocator.handle_cast<DX12Program*>(program);
    DX12ProgramImpl* dx12ProgramImpl = dx12Program->getProgramImpl();
    DX12Pipeline* dx12Pipeline = mResourceAllocator.construct<DX12Pipeline>(pipelineHandle, dx12ProgramImpl);
    
    DX12PipelineCache::RasterState dx12RasterState;

    dx12RasterState.cullMode = D3D12Mappings::getCullMode(rasterState.culling);
    dx12RasterState.frontFace = rasterState.inverseFrontFaces;
    dx12RasterState.depthBiasEnable = FALSE;
    
    dx12RasterState.blendEnable = rasterState.hasBlending();

    dx12RasterState.depthWriteEnable = rasterState.depthWrite?TRUE:FALSE;
    dx12RasterState.depthTestEnable = rasterState.depthTest;
    dx12RasterState.srcColorBlendFactor = D3D12Mappings::getBlendFactor((Ogre::BlendFunction)rasterState.blendFunctionSrcRGB);
    dx12RasterState.dstColorBlendFactor = D3D12Mappings::getBlendFactor((Ogre::BlendFunction)rasterState.blendFunctionDstRGB);
    dx12RasterState.srcAlphaBlendFactor = D3D12Mappings::getBlendFactor((Ogre::BlendFunction)rasterState.blendFunctionSrcAlpha);
    dx12RasterState.dstAlphaBlendFactor = D3D12Mappings::getBlendFactor((Ogre::BlendFunction)rasterState.blendFunctionDstAlpha);
    dx12RasterState.colorBlendOp = D3D12Mappings::getBlendOp((Ogre::BlendOperation)rasterState.blendEquationRGB);
    dx12RasterState.alphaBlendOp = D3D12Mappings::getBlendOp((Ogre::BlendOperation)rasterState.blendEquationAlpha);

    dx12RasterState.colorWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    dx12RasterState.rasterizationSamples = DX12Helper::getSingleton().hasMsaa() ? 4 : 1;
    dx12RasterState.colorTargetCount = rasterState.renderTargetCount;
    dx12RasterState.depthCompareOp = D3D12Mappings::getComparisonFunc(rasterState.depthFunc);
    dx12RasterState.depthBiasSlopeFactor = 0.0f;
    dx12RasterState.depthBias = 0.0f;

    DXGI_FORMAT colorFormat[8] = {};
    for (uint32_t i = 0; i < rasterState.renderTargetCount; i++)
    {
        PixelFormat format = (PixelFormat)rasterState.pixelFormat[i];
        if (format == PF_UNKNOWN)
        {
            format = mRenderWindow->getColorFormat();
        }

        colorFormat[i] = D3D12Mappings::_getPF(format);
    }
    
    mDX12PipelineCache.bindFormat(colorFormat, DXGI_FORMAT_D32_FLOAT);

    const std::string* vsCode = dx12ProgramImpl->getVsBlob();
    const std::string* gsCode = dx12ProgramImpl->getGsBlob();
    const std::string* psCode = dx12ProgramImpl->getPsBlob();
    mDX12PipelineCache.bindProgram(
        vsCode,
        gsCode,
        psCode);
    mDX12PipelineCache.bindRasterState(dx12RasterState);
    mDX12PipelineCache.bindPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);

    auto* rootSignature = dx12ProgramImpl->getRootSignature();
    mDX12PipelineCache.bindLayout(rootSignature);

    const auto& inputList = dx12ProgramImpl->getInputDesc();
    auto inputListSize = inputList.size();
    mDX12PipelineCache.bindVertexArray(inputList.data(), inputListSize);
    
    ID3D12PipelineState* pipeline = mDX12PipelineCache.getPipeline();
    dx12Pipeline->updatePipeline(pipeline);

    return pipelineHandle;
}

Handle<HwDescriptorSet> Dx12RenderSystemBase::createDescriptorSet(
    Handle<HwProgram> programHandle,
    uint32_t set)
{
    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<DX12DescriptorSet>();

    DX12Program* dx12Program = mResourceAllocator.handle_cast<DX12Program*>(programHandle);
    DX12ProgramImpl* dx12ProgramImpl = dx12Program->getProgramImpl();

    DX12DescriptorSet* dx12DescSet = mResourceAllocator.construct<DX12DescriptorSet>(dsh, dx12ProgramImpl, set);

    uint32_t cbvSrvUavDescCount = dx12ProgramImpl->getCbvSrvUavDescCount(set);

    DxDescriptorID cbvSrvUavHandle = consume_descriptor_handles(mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV], cbvSrvUavDescCount);
    dx12DescSet->updateCbvSrvUavHandle(cbvSrvUavHandle, cbvSrvUavDescCount);
    return dsh;
}

void Dx12RenderSystemBase::updateDescriptorSet(
    Handle<HwDescriptorSet> dsh,
    uint32_t count,
    const DescriptorData* pParams
)
{
    DX12DescriptorSet* dx12DescSet = mResourceAllocator.handle_cast<DX12DescriptorSet*>(dsh);

    DX12ProgramBase* dx12ProgramImpl = dx12DescSet->getProgram();

    DxDescriptorID cbvSrvUavHandle = dx12DescSet->getCbvSrvUavHandle();
    for (auto i = 0; i < count; i++)
    {
        const DescriptorData* pParam = pParams + i;
        const DescriptorInfo* descriptroInfo = dx12ProgramImpl->getDescriptor(pParam->pName);
        if (descriptroInfo == nullptr)
        {
            //assert_invariant(false);
            continue;
        }

        dx12DescSet->addDescriptroInfo(descriptroInfo);
        assert_invariant(descriptroInfo);
        const uint32_t       arrayCount = std::max(1U, pParam->mCount);

        switch (descriptroInfo->mType)
        {
        case D3D_SIT_RTACCELERATIONSTRUCTURE:
        {
            DX12AccelerationStructure* as = (DX12AccelerationStructure*)pParam->pAS;
            DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(as->asBufferHandle);
            DxDescriptorID id = bo->getDescriptorID(false);
            d3dUtil::copy_descriptor_handle(
                mDescriptorHeapContext->mCPUDescriptorHeaps[0],
                id,
                mDescriptorHeapContext->mCbvSrvUavHeaps[0],
                cbvSrvUavHandle + descriptroInfo->mSetIndex);
        }
        break;
        case D3D_SIT_TEXTURE:
        case D3D_SIT_UAV_RWTYPED:
        {
            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                Dx12Texture* dx12Texture = (Dx12Texture*)pParam->ppTextures[arr];
                DxDescriptorID id;
                if (pParam->descriptorType == DESCRIPTOR_TYPE_RW_TEXTURE)
                {
                    id = dx12Texture->getTargetDescriptorId() + pParam->mLevel;
                }
                else
                {
                    id = dx12Texture->getDescriptorId();
                }

                d3dUtil::copy_descriptor_handle(
                    mDescriptorHeapContext->mCPUDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV],
                    id,
                    mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV],
                    cbvSrvUavHandle + descriptroInfo->mSetIndex + arr
                );

                int kk = 0;
            }
        }  
        break;
        case D3D_SIT_CBUFFER:
        case D3D_SIT_UAV_RWSTRUCTURED:
        case D3D_SIT_BYTEADDRESS:
        case D3D_SIT_STRUCTURED:
        case D3D_SIT_UAV_RWBYTEADDRESS:
        
        {
            bool write = pParam->descriptorType == DESCRIPTOR_TYPE_RW_BUFFER;

            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                auto& boh = pParam->ppBuffers[arr];
                DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(boh);
                DxDescriptorID srcId = bo->getDescriptorID(write);

                DescriptorHeap* heap = mDescriptorHeapContext->mCPUDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV];
                DescriptorHeap* dstHeap = mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV];
                d3dUtil::copy_descriptor_handle(
                    heap,
                    srcId,
                    dstHeap,
                    cbvSrvUavHandle + descriptroInfo->mSetIndex + arr
                );
            }
        }
            break;
        case D3D_SIT_SAMPLER:
        {
            assert_invariant(arrayCount == 1);
            
            for (uint32_t arr = 0; arr < arrayCount; ++arr)
            {
                if (pParam->descriptorType == DESCRIPTOR_TYPE_SAMPLER)
                {
                    DX12Sampler* sampler = mResourceAllocator.handle_cast<DX12Sampler*>(pParam->ppSamplers[arr]);
                    DxDescriptorID srcId = sampler->getDescriptorID();
                    dx12DescSet->updateSamplerHandle(descriptroInfo->mSetIndex, srcId);
                }
                else
                {
                    Dx12Texture* dx12Texture = (Dx12Texture*)pParam->ppTextures[arr];

                    DxDescriptorID srcId = dx12Texture->getSamplerDescriptorID();

                    dx12DescSet->updateSamplerHandle(descriptroInfo->mSetIndex, srcId);
                }
                
                
            }
        }
            break;
        default:
            assert_invariant(false);
            break;
        }
        
    }
}

void Dx12RenderSystemBase::resourceBarrier(
    uint32_t numBufferBarriers, BufferBarrier* pBufferBarriers, 
    uint32_t numTextureBarriers, TextureBarrier* pTextureBarriers, 
    uint32_t numRtBarriers, RenderTargetBarrier* pRtBarriers,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* dsh,
    Ogre::QueueType queueType
)
{
    D3D12_RESOURCE_BARRIER* barriers =
        (D3D12_RESOURCE_BARRIER*)alloca((numBufferBarriers + numTextureBarriers + numRtBarriers) * sizeof(D3D12_RESOURCE_BARRIER));
    uint32_t transitionCount = 0;

    for (uint32_t i = 0; i < numBufferBarriers; ++i)
    {
        BufferBarrier* pTransBarrier = &pBufferBarriers[i];
        D3D12_RESOURCE_BARRIER* pBarrier = &barriers[transitionCount];

        DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(pTransBarrier->buffer);

        auto memoryUsage = bo->getMemoryUsage();
        auto bufferObjectType = bo->getBufferObjectBinding();
        // Only transition GPU visible resources.
        // Note: General CPU_TO_GPU resources have to stay in generic read state. They are created in upload heap.
        // There is one corner case: CPU_TO_GPU resources with UAV usage can have state transition. And they are created in custom heap.
        if (memoryUsage == RESOURCE_MEMORY_USAGE_GPU_ONLY || memoryUsage == RESOURCE_MEMORY_USAGE_GPU_TO_CPU ||
            (memoryUsage == RESOURCE_MEMORY_USAGE_CPU_TO_GPU && (bufferObjectType & BufferObjectBinding_Storge)))
        {
            // if (!(pBuffer->mCurrentState & pTransBarrier->mNewState) && pBuffer->mCurrentState != pTransBarrier->mNewState)
            if (RESOURCE_STATE_UNORDERED_ACCESS == pTransBarrier->mCurrentState &&
                RESOURCE_STATE_UNORDERED_ACCESS == pTransBarrier->mNewState)
            {
                pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                pBarrier->UAV.pResource = bo->getResource();
                ++transitionCount;
            }
            else if ((RESOURCE_STATE_ACCELERATION_STRUCTURE_WRITE & pTransBarrier->mCurrentState) &&
                (RESOURCE_STATE_ACCELERATION_STRUCTURE_READ & pTransBarrier->mNewState))
            {
                pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                pBarrier->UAV.pResource = bo->getResource();
                ++transitionCount;
            }
            else
            {
                pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                if (pTransBarrier->mBeginOnly)
                {
                    pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY;
                }
                else if (pTransBarrier->mEndOnly)
                {
                    pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY;
                }
                pBarrier->Transition.pResource = bo->getResource();
                pBarrier->Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                pBarrier->Transition.StateBefore = D3D12Mappings::util_to_dx12_resource_state(pTransBarrier->mCurrentState);
                pBarrier->Transition.StateAfter = D3D12Mappings::util_to_dx12_resource_state(pTransBarrier->mNewState);

                ++transitionCount;
            }
        }
    }

    for (uint32_t i = 0; i < numTextureBarriers; ++i)
    {
        TextureBarrier* pTrans = &pTextureBarriers[i];
        D3D12_RESOURCE_BARRIER* pBarrier = &barriers[transitionCount];
        Dx12Texture* pTexture = (Dx12Texture*)pTrans->pTexture;

        auto texMipLevel = pTexture->getMipLevel();

        if (RESOURCE_STATE_UNORDERED_ACCESS == pTrans->mCurrentState && RESOURCE_STATE_UNORDERED_ACCESS == pTrans->mNewState)
        {
            pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
            pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            pBarrier->UAV.pResource = pTexture->getResource();
            ++transitionCount;
        }
        else
        {
            pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            if (pTrans->mBeginOnly)
            {
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY;
            }
            else if (pTrans->mEndOnly)
            {
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY;
            }
            pBarrier->Transition.pResource = pTexture->getResource();
            pBarrier->Transition.Subresource = pTrans->mSubresourceBarrier
                ? CALC_SUBRESOURCE_INDEX(pTrans->mMipLevel, pTrans->mArrayLayer, 0, texMipLevel, 1)
                : D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            if (pTrans->mAcquire)
                pBarrier->Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
            else
                pBarrier->Transition.StateBefore = D3D12Mappings::util_to_dx12_resource_state(pTrans->mCurrentState);

            if (pTrans->mRelease)
                pBarrier->Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
            else
                pBarrier->Transition.StateAfter = D3D12Mappings::util_to_dx12_resource_state(pTrans->mNewState);

            ++transitionCount;
        }
    }

    for (uint32_t i = 0; i < numRtBarriers; ++i)
    {
        RenderTargetBarrier* pTrans = &pRtBarriers[i];
        D3D12_RESOURCE_BARRIER* pBarrier = &barriers[transitionCount];
        Dx12Texture* pTexture = (Dx12Texture*)pTrans->pRenderTarget->getTarget();
        auto texMipLevel = pTexture->getMipLevel();
        if (RESOURCE_STATE_UNORDERED_ACCESS == pTrans->mCurrentState && RESOURCE_STATE_UNORDERED_ACCESS == pTrans->mNewState)
        {
            pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
            pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            pBarrier->UAV.pResource = pTexture->getResource();
            ++transitionCount;
        }
        else
        {
            pBarrier->Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            if (pTrans->mBeginOnly)
            {
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY;
            }
            else if (pTrans->mEndOnly)
            {
                pBarrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY;
            }
            pBarrier->Transition.pResource = pTexture->getResource();
            pBarrier->Transition.Subresource = pTrans->mSubresourceBarrier
                ? CALC_SUBRESOURCE_INDEX(pTrans->mMipLevel, pTrans->mArrayLayer, 0, texMipLevel, 1)
                : D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            if (pTrans->mAcquire)
                pBarrier->Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
            else
                pBarrier->Transition.StateBefore = D3D12Mappings::util_to_dx12_resource_state(pTrans->mCurrentState);

            if (pTrans->mRelease)
                pBarrier->Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
            else
                pBarrier->Transition.StateAfter = D3D12Mappings::util_to_dx12_resource_state(pTrans->mNewState);

            ++transitionCount;
        }
    }

    if (transitionCount)
    {
        DX12CommandBuffer* cb = nullptr;
        if (dsh)
        {
            cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(*dsh);
        }
        else
        {
            cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
        }
        auto* cl = cb->get();
        cl->ResourceBarrier(transitionCount, barriers);
    }
}


void Dx12RenderSystemBase::beginDefaultCommandList()
{
    if (mCommandBufferOpen)
    {
        return;
    }

    mCommandBufferOpen = true;
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    auto* cl = cb->get();
    cb->beginComandBuffer();
    ID3D12DescriptorHeap* heaps[] =
    {
        mDescriptorHeapContext->mCbvSrvUavHeaps[0]->pHeap,
        mDescriptorHeapContext->pSamplerHeaps[0]->pHeap
    };
    cl->SetDescriptorHeaps(2, heaps);
    
}

void Dx12RenderSystemBase::flushDefaultCommandList(Handle<HwCommandQueue> cqh, bool waitCmd)
{
    if (!mCommandBufferOpen)
        return;
    DX12CommandQueue* cq = mResourceAllocator.handle_cast<DX12CommandQueue*>(cqh);
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    ID3D12GraphicsCommandList*  cl = cb->get();
    cb->endCommandBuffer();
    cq->executeCommandLists(&cl, 1);
    if (waitCmd)
    {
        DX12Fence* fence = mResourceAllocator.handle_cast<DX12Fence*>(mCommandFence);
        fence->addFenceValue();
        cq->signal(fence);
        fence->wait();
    }

    mCommandBufferOpen = false;
}

void Dx12RenderSystemBase::flushCmd(
    Handle<HwCommandQueue> cqh,
    Handle<HwCommandBuffer> cbh,
    bool waitCmd)
{
    DX12CommandQueue* cq = mResourceAllocator.handle_cast<DX12CommandQueue*>(cqh);
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    ID3D12GraphicsCommandList* cl = cb->get();
    cq->executeCommandLists(&cl, 1);
    if (waitCmd)
    {
        DX12Fence* fence = mResourceAllocator.handle_cast<DX12Fence*>(mCommandFence);
        fence->addFenceValue();
        cq->signal(fence);
        fence->wait();
    }
}

Handle<HwFence> Dx12RenderSystemBase::createFence(bool signaled)
{
    Handle<HwFence> fh = mResourceAllocator.allocHandle<DX12Fence>();

    DX12Fence* fence = mResourceAllocator.construct<DX12Fence>(fh, mDevice);
    return fh;
}

void Dx12RenderSystemBase::waitFence(Handle<HwFence> fh)
{
    DX12Fence* fence = mResourceAllocator.handle_cast<DX12Fence*>(fh);
    fence->wait();
}


Handle<HwSemaphore> Dx12RenderSystemBase::createSemaphore()
{
    Handle<HwSemaphore> sh = mResourceAllocator.allocHandle<DX12Semaphore>();

    DX12Semaphore*  sem = mResourceAllocator.construct<DX12Semaphore>(sh, mDevice);
    return sh;
}

Handle<HwCommandBuffer> Dx12RenderSystemBase::createCommandBuffer(Ogre::QueueType type)
{
    Handle<HwCommandBuffer> cbh = mResourceAllocator.allocHandle<DX12CommandBuffer>();

    DX12CommandBuffer* cb = mResourceAllocator.construct<DX12CommandBuffer>(cbh, mDevice);
    return cbh;
}

void Dx12RenderSystemBase::beginCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);

    cb->beginComandBuffer();

    ID3D12DescriptorHeap* heaps[] =
    {
        mDescriptorHeapContext->mCbvSrvUavHeaps[0]->pHeap,
        mDescriptorHeapContext->pSamplerHeaps[0]->pHeap
    };

    auto cl = cb->get();
    cl->SetDescriptorHeaps(2, heaps);
}

void Dx12RenderSystemBase::endCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    cb->endCommandBuffer();
}

void Dx12RenderSystemBase::clearCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    cb->clearCommandBuffer();
}

Handle<HwCommandQueue> Dx12RenderSystemBase::createCommandQueue(Ogre::QueueType type, uint32_t queueIndex)
{
    Handle<HwCommandQueue> cqh = mResourceAllocator.allocHandle<DX12CommandQueue>();

    DX12CommandQueue* cq = mResourceAllocator.construct<DX12CommandQueue>(cqh, mDevice);

    return cqh;
}

Handle<HwSwapChain> Dx12RenderSystemBase::createSwapChain(Ogre::RenderWindow* renderWindow)
{
    Dx12RenderWindow* dx12Window = (Dx12RenderWindow*)renderWindow;
    HWND handle = (HWND)dx12Window->getWndHandle();
    uint64_t flags = dx12Window->getFlags();
    Handle<HwSwapChain> sch = mResourceAllocator.allocHandle<DX12SwapChain>();


    DX12SwapChain* sc = mResourceAllocator.construct<DX12SwapChain>(sch, handle, flags);
    dx12Window->setSwapChain(sc);
    return sch;
}

void Dx12RenderSystemBase::swapChainResize(Handle<HwCommandQueue> cqh, Handle<HwSwapChain> sch)
{
    DX12CommandQueue* cq = mResourceAllocator.handle_cast<DX12CommandQueue*>(cqh);
    DX12SwapChain* sc = mResourceAllocator.handle_cast<DX12SwapChain*>(sch);
    sc->resize(cq);
}

void Dx12RenderSystemBase::swapChainAcquire(
    Handle<HwCommandQueue> cqh,
    Handle<HwSwapChain> sch,
    SwapChainInfo& scInfo)
{
    DX12CommandQueue* cq = mResourceAllocator.handle_cast<DX12CommandQueue*>(cqh);
    DX12SwapChain* sc = mResourceAllocator.handle_cast<DX12SwapChain*>(sch);

    bool resized = false;
    sc->acquire(resized);
    scInfo.color = sc->getCurrentColor();
    scInfo.depth = sc->getDepthTexture();
    scInfo.imageIndex = sc->getImageIndex();
}

Handle<HwShader> Dx12RenderSystemBase::createShader(Ogre::ShaderDesc& desc)
{
    Handle<HwShader> sh = mResourceAllocator.allocHandle<Dx12Shader>();

    Dx12Shader* shader = mResourceAllocator.construct<Dx12Shader>(sh);

    assert_invariant(false);
    return sh;
}


Handle<HwPipeline> Dx12RenderSystemBase::createPipeline(
    Ogre::PipelineCreateInfo& pipelineCreateInfo,
    Handle<HwShader>& shader
)
{
    Handle<HwPipeline> ph = mResourceAllocator.allocHandle<HwPipeline>();
    assert_invariant(false);
    return ph;
}

Handle<HwPipeline> Dx12RenderSystemBase::createComputePipeline(
    Handle<HwShader>& shader
)
{
    Handle<HwPipeline> ph = mResourceAllocator.allocHandle<HwPipeline>();
    assert_invariant(false);
    return ph;
}

Handle<HwDescriptorSet> Dx12RenderSystemBase::createDescriptorSet(
    Handle<HwShader> programHandle,
    uint32_t set)
{

    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<DX12DescriptorSet>();

    Dx12Shader* dx12Shader = mResourceAllocator.handle_cast<Dx12Shader*>(programHandle);
    DX12ProgramImpl* dx12ProgramImpl = dx12Shader->getProgramImpl();

    DX12DescriptorSet* dx12DescSet = mResourceAllocator.construct<DX12DescriptorSet>(dsh, dx12ProgramImpl, set);

    uint32_t cbvSrvUavDescCount = dx12ProgramImpl->getCbvSrvUavDescCount(set);

    DxDescriptorID cbvSrvUavHandle = consume_descriptor_handles(mDescriptorHeapContext->mCbvSrvUavHeaps[0], cbvSrvUavDescCount);
    dx12DescSet->updateCbvSrvUavHandle(cbvSrvUavHandle, cbvSrvUavDescCount);
    return dsh;
}

void Dx12RenderSystemBase::executeAndPresent(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    filament::backend::Handle<filament::backend::HwSemaphore>* wait_sph,
    uint32_t wait_sp_size,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh,
    uint32_t cb_size,
    filament::backend::Handle<filament::backend::HwSemaphore>* cmd_sph,
    uint32_t cmd_sp_size,
    filament::backend::Handle<filament::backend::HwFence> fh,
    filament::backend::Handle<filament::backend::HwSwapChain>* sch,
    uint32_t sc_size
)
{
    DX12CommandQueue* cq = mResourceAllocator.handle_cast<DX12CommandQueue*>(cqh);

    for (uint32_t i = 0; i < wait_sp_size; i++)
    {
        DX12Semaphore* sp = mResourceAllocator.handle_cast<DX12Semaphore*>(wait_sph[0]);
        cq->wait(sp);
    }
    

    DX12Fence* fence = mResourceAllocator.handle_cast<DX12Fence*>(fh);
    DX12SwapChain* sc = mResourceAllocator.handle_cast<DX12SwapChain*>(sch[0]);


    std::vector< ID3D12GraphicsCommandList*> command_lists;
    for (uint32_t i = 0; i < cb_size; i++)
    {
        DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh[0]);
        command_lists.push_back(cb->get());
    }

    cq->executeCommandLists(command_lists.data(), cb_size);
    
    for (uint32_t i = 0; i < cmd_sp_size; i++)
    {
        DX12Semaphore* sp = mResourceAllocator.handle_cast<DX12Semaphore*>(cmd_sph[0]);
        sp->addFenceValue();
        cq->signal(sp);
    }

    sc->present(cq, fence, command_lists.data(), cb_size);
    
}

void Dx12RenderSystemBase::bindVertexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    uint32_t binding_count,
    const filament::backend::Handle<filament::backend::HwBufferObject>* bufHandle,
    const uint64_t* p_offsets)
{
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    

    auto* cl = cb->get();

    for (int i = 0; i < binding_count; i++)
    {
        DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(bufHandle[i]);

        D3D12_VERTEX_BUFFER_VIEW vbv;
        vbv.BufferLocation = bo->getGPUVirtualAddress();
        vbv.StrideInBytes = bo->getStride();
        vbv.SizeInBytes = bo->getByteCount();
        cl->IASetVertexBuffers(0, 1, &vbv);
    }
   
}

void Dx12RenderSystemBase::bindIndexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
    uint32_t indexSize,
    uint32_t offset)
{
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }

    DX12BufferObject* bo = mResourceAllocator.handle_cast<DX12BufferObject*>(bufHandle);

    auto* cl = cb->get();
    D3D12_INDEX_BUFFER_VIEW ibv;
    ibv.BufferLocation = bo->getGPUVirtualAddress();
    ibv.Format = indexSize == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
    ibv.SizeInBytes = bo->getByteCount();
    cl->IASetIndexBuffer(&ibv);

}

void Dx12RenderSystemBase::bindPipeline(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle)
{
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    

    DX12Pipeline* pipeline = mResourceAllocator.handle_cast<DX12Pipeline*>(pipelineHandle);

    DX12ProgramImpl* dx12ProgramImpl = pipeline->getProgram();

    ID3D12PipelineState* pso = pipeline->getPipeline();


    auto rootSignature = dx12ProgramImpl->getRootSignature();
    auto* cl = cb->get();
    cl->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    cl->SetGraphicsRootSignature(rootSignature);
    cl->SetPipelineState(pso);
    mLastPipelineState = pso;
}

void Dx12RenderSystemBase::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwShader> sh,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    DX12CommandBuffer* cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    assert_invariant(false);
}

void Dx12RenderSystemBase::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwProgram> ph,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    DX12CommandBuffer* cb = nullptr;
    if (cbh)
    {
        cb= mResourceAllocator.handle_cast<DX12CommandBuffer*>(cbh);
    }
    else
    {
        cb = mResourceAllocator.handle_cast<DX12CommandBuffer*>(mCommandBuffer);
    }
    
    auto cl = cb->get();
    DX12Program* program = mResourceAllocator.handle_cast<DX12Program*>(ph);
    DX12DescriptorSet* dset = mResourceAllocator.handle_cast<DX12DescriptorSet*>(dsh);

    const std::vector<const DescriptorInfo*>& descriptorInfos = dset->getDescriptorInfos();
    if (descriptorInfos.empty())
        return;
    auto cbvSrvUavHandle = dset->getCbvSrvUavHandle();

    for (auto descriptorInfo : descriptorInfos)
    {
        if (descriptorInfo->mType == D3D_SIT_SAMPLER)
        {
            auto samplerHandle = dset->getSamplerHandle(descriptorInfo->mSetIndex);
            auto gpuHandle = descriptor_id_to_gpu_handle(
                mDescriptorHeapContext->pSamplerHeaps[0], samplerHandle);
            cl->SetGraphicsRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
        }
        else
        {
            auto gpuHandle = descriptor_id_to_gpu_handle(
                mDescriptorHeapContext->mCbvSrvUavHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV], cbvSrvUavHandle + descriptorInfo->mSetIndex);
            cl->SetGraphicsRootDescriptorTable(descriptorInfo->mRootIndex, gpuHandle);
        }

    }
}


