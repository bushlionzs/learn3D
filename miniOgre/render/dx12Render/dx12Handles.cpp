#include <OgreHeader.h>
#include <OgreResourceManager.h>
#include "dx12Handles.h"
#include "dx12Helper.h"
#include "dx12Shader.h"
#include "dx12RayTracingShader.h"
#include "memoryAllocator.h"
#include "glslUtil.h"
#include "myutils.h"
#include "d3dutil.h"
#include "shaderManager.h"
#include "D3D12Mappings.h"

DX12BufferObject::DX12BufferObject(
    DescriptorHeapContext* context,
    BufferDesc& desc,
    DescriptorHeap* pHeap,
    bool cpu_to_gpu
   ):
    mCpuToGpu(cpu_to_gpu)
{
    mDescriptorHeapContext = context;
    mBufferObjectBinding = desc.mBindingType;
    mMemoryUsage = desc.mMemoryUsage;
    mDescriptorID = consume_descriptor_handles(pHeap, 1);
    mByteCount = desc.mSize;
    mStrideInBytes = desc.mStructStride;

    if (BufferObjectBinding_Uniform == mBufferObjectBinding)
    {
        mByteCount = d3dUtil::CalcConstantBufferByteSize(mByteCount);
    }
    
    ID3D12Device* dx12Device = DX12Helper::getSingleton().getDevice();
    auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    auto bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mByteCount);
    //D3D12_RESOURCE_STATE_COMMON
    D3D12_RESOURCE_STATES state = D3D12Mappings::util_to_dx12_resource_state(desc.mStartState);

    if (BufferObjectBinding_Storge == mBufferObjectBinding ||
        BufferObjectBinding_InDirectBuffer == mBufferObjectBinding)
    {
        bufferDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    }

    if (BufferObjectBinding_AccelerationStructure == mBufferObjectBinding)
    {
        bufferDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
        bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    }
    ThrowIfFailed(dx12Device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        state,
        nullptr,
        IID_PPV_ARGS(BufferGPU.GetAddressOf())));

    auto cpuHandle = descriptor_id_to_cpu_handle(pHeap, mDescriptorID);

    switch (mBufferObjectBinding)
    {
    case BufferObjectBinding_AccelerationStructure:
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Buffer.NumElements = mByteCount / 4;
        srvDesc.Buffer.StructureByteStride = 0;
        srvDesc.Buffer.Flags |= D3D12_BUFFER_SRV_FLAG_RAW;
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.RaytracingAccelerationStructure.Location = BufferGPU->GetGPUVirtualAddress();
        dx12Device->CreateShaderResourceView(nullptr, &srvDesc, cpuHandle);
    }
    break;
    case BufferObjectBinding_Vertex:
    case BufferObjectBinding_Index:
    case BufferObjectBinding_Buffer:
    
    {
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Buffer.NumElements = desc.mElementCount;
        srvDesc.Buffer.StructureByteStride = desc.mStructStride;
        srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
        if (desc.raw)
        {
            srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
            srvDesc.Buffer.NumElements = mByteCount / 4;
            srvDesc.Buffer.StructureByteStride = 0;
            srvDesc.Buffer.Flags |= D3D12_BUFFER_SRV_FLAG_RAW;
        }
        dx12Device->CreateShaderResourceView(BufferGPU.Get(), &srvDesc, cpuHandle);
    }
    break;
    case BufferObjectBinding_Storge:
    case BufferObjectBinding_InDirectBuffer:
    {
        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = DXGI_FORMAT_UNKNOWN;
        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        uavDesc.Buffer.NumElements = desc.mElementCount;
        uavDesc.Buffer.StructureByteStride = desc.mStructStride;
        uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
        if (desc.raw)
        {
            uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
            uavDesc.Buffer.NumElements = mByteCount / 4;
            uavDesc.Buffer.StructureByteStride = 0;
            uavDesc.Buffer.Flags |= D3D12_BUFFER_UAV_FLAG_RAW;
        }

        mDescriptorIDOfWrite = consume_descriptor_handles(pHeap, 1);

        auto writeCpuHandle = descriptor_id_to_cpu_handle(pHeap, mDescriptorIDOfWrite);
        dx12Device->CreateUnorderedAccessView(BufferGPU.Get(), 
            nullptr, &uavDesc, writeCpuHandle);
        
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Buffer.NumElements = desc.mElementCount;
        srvDesc.Buffer.StructureByteStride = desc.mStructStride;
        srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
        if (desc.raw)
        {
            srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
            srvDesc.Buffer.NumElements = mByteCount / 4;
            srvDesc.Buffer.StructureByteStride = 0;
            srvDesc.Buffer.Flags |= D3D12_BUFFER_SRV_FLAG_RAW;
        }

        dx12Device->CreateShaderResourceView(BufferGPU.Get(), &srvDesc, cpuHandle);
    }
        break;
    case BufferObjectBinding_Uniform:
    {
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation = BufferGPU->GetGPUVirtualAddress();
        cbvDesc.SizeInBytes = (UINT)mByteCount;
        dx12Device->CreateConstantBufferView(&cbvDesc, cpuHandle);
    }
    break;
    default:
        assert_invariant(false);
        break;
    }

    heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mByteCount);
    ThrowIfFailed(dx12Device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(BufferUploader.GetAddressOf())));
}

void DX12BufferObject::copyData(
    ID3D12GraphicsCommandList* cmdList,
    const char* data, 
    uint32_t size,
    uint32_t offset)
{
    void* mapData = lock(0, size);
    memcpy((char*)mapData + offset, data, size);
    unlock(cmdList);

    
}

D3D12_GPU_VIRTUAL_ADDRESS DX12BufferObject::getGPUVirtualAddress()
{    
    return  BufferGPU->GetGPUVirtualAddress();
}

void* DX12BufferObject::lock(uint32_t offset, uint32_t numBytes)
{
    BYTE* mappedData = nullptr;
    mRange.Begin = offset;
    mRange.End = offset + numBytes;

    if (mRange.End > mByteCount)
        mRange.End = mByteCount;
    BufferUploader->Map(0, &mRange, reinterpret_cast<void**>(&mappedData));
    return mappedData;
}

void DX12BufferObject::unlock(ID3D12GraphicsCommandList* cmdList)
{
    BufferUploader->Unmap(0, &mRange);
    uint32_t size = mRange.End - mRange.Begin;
    auto dstBarrier = CD3DX12_RESOURCE_BARRIER::Transition(BufferGPU.Get(),
        D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST);
    cmdList->ResourceBarrier(1, &dstBarrier);

    cmdList->CopyBufferRegion(
        BufferGPU.Get(), 0, BufferUploader.Get(), mRange.Begin, size);
    dstBarrier = CD3DX12_RESOURCE_BARRIER::Transition(BufferGPU.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    cmdList->ResourceBarrier(1, &dstBarrier);
}

DX12Program::DX12Program(const ShaderInfo& info, VertexDeclaration* decl)
{
    mProgramImpl = new DX12ProgramImpl(info, decl);
}

DX12RayTracingProgram::DX12RayTracingProgram(const RaytracingShaderInfo& shaderInfo)
{
    mProgramImpl = new DX12RayTracingProgramImpl(shaderInfo);
}

DX12ComputeProgram::DX12ComputeProgram(const ShaderInfo& info)
{
    mProgramImpl = new DX12ProgramImpl(info, nullptr);
}

DX12ComputeProgram::~DX12ComputeProgram()
{

}


DX12DescriptorSet::DX12DescriptorSet(DX12ProgramBase* program, uint32_t set)
    :mProgram(program),
    mSet(set)
{

}

DX12DescriptorSet::~DX12DescriptorSet()
{

}



DX12CommandBuffer::DX12CommandBuffer(ID3D12Device* device)
{
    ThrowIfFailed(device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&commandAllocator)));

    ThrowIfFailed(device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        commandAllocator,
        nullptr,
        IID_PPV_ARGS(&commandList)));

    commandList->Close();
}

DX12CommandBuffer::~DX12CommandBuffer()
{

}

void DX12CommandBuffer::beginComandBuffer()
{
    ThrowIfFailed(commandAllocator->Reset());
    ThrowIfFailed(commandList->Reset(commandAllocator, nullptr));
}

void DX12CommandBuffer::endCommandBuffer()
{
    ThrowIfFailed(commandList->Close());
}

void DX12CommandBuffer::clearCommandBuffer()
{

}

Dx12Shader::Dx12Shader()
{

}

Dx12Shader::~Dx12Shader()
{

}

DX12CommandQueue::DX12CommandQueue(ID3D12Device* device)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailed(device->CreateCommandQueue(&queueDesc,
        IID_PPV_ARGS(&mCommandQueue)));
}

DX12CommandQueue::~DX12CommandQueue()
{

}

void DX12CommandQueue::executeCommandLists(ID3D12GraphicsCommandList** cl, uint32_t cb_size)
{
    mCommandQueue->ExecuteCommandLists(cb_size, (ID3D12CommandList**)cl);
}

void DX12CommandQueue::signal(DX12Fence* fence)
{
    mCommandQueue->Signal(fence->get(), fence->getFenceValue());
}

void DX12CommandQueue::signal(DX12Semaphore* sp)
{
    mCommandQueue->Signal(sp->get(), sp->getFenceValue());
}

void DX12CommandQueue::wait(DX12Semaphore* sp)
{
    mCommandQueue->Wait(sp->get(), sp->getFenceValue());
}

DX12Fence::DX12Fence(ID3D12Device* device)
{
    HRESULT res = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(d3d_fence.GetAddressOf()));

    ThrowIfFailed(res);


    event_handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    ThrowIfFailed(event_handle == NULL);

    fence_value = 0;
}

DX12Fence::~DX12Fence()
{
    CloseHandle(event_handle);
}

void DX12Fence::wait()
{
    if (d3d_fence->GetCompletedValue() < fence_value)
    {
        d3d_fence->SetEventOnCompletion(fence_value, event_handle);
        WaitForSingleObject(event_handle, INFINITE);
    }
    
}

void DX12Fence::addFenceValue()
{
    fence_value++;
}

DX12Semaphore::DX12Semaphore(ID3D12Device* device)
{
    HRESULT res = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(d3d_fence.GetAddressOf()));

    ThrowIfFailed(res);

    fence_value = 0;
}

DX12Semaphore::~DX12Semaphore()
{

}

