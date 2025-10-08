#pragma once

#include "renderSystem.h"
#include "d3dutil.h"
#include "dx12Common.h"
#include "dx12ResourceAllocator.h"
#include "dx12PipelineCache.h"


class Dx12GraphicsCommandList;
class Dx12RenderTarget;
class Dx12Texture;
class Dx12RenderWindow;
class DX12Commands;
class DX12SwapChain;
class Dx12TextureListen;
class DxMemoryAllocator;

class Dx12RenderSystemBase : public RenderSystem
{
public:
    Dx12RenderSystemBase();
    ~Dx12RenderSystemBase();

    virtual bool engineInit();
    virtual void ready();
    virtual Ogre::RenderWindow* createRenderWindow(
        const CreateWindowDesc& desc) override;
    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name,
        TextureProperty& texProperty) override;
    virtual void clearRenderTarget(
        Ogre::RenderTarget* target, const Ogre::Vector4& color);
    virtual void frameStart();
    virtual void frameEnd();
    virtual void present();
    virtual void copyImage(
        Ogre::RenderTarget* dst,
        Ogre::RenderTarget* src,
        ImageCopyDesc& desc);
    void copyImage(
        Dx12Texture* dst,
        Dx12Texture* src,
        ImageCopyDesc& desc
    );

    virtual void setViewport(
        float x, float y, float width, float height, float minDepth, float maxDepth,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh) override;
    virtual void setScissor(
        uint32_t x, uint32_t y, uint32_t width, uint32_t height,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh) override;
    virtual void beginRenderPass(
        RenderPassInfo& renderPassInfo);
    virtual void endRenderPass(RenderPassInfo& renderPassInfo);

    virtual void bindPipeline(
        Handle<HwPipeline> pipelineHandle,
        const Handle<HwDescriptorSet>* descSets,
        uint32_t setCount);

    virtual void drawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t firstInstance,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh) override;

    virtual void draw(uint32_t vertexCount,
        uint32_t instanceCount,
        uint32_t firstVertex,
        uint32_t firstInstance,
        Handle<HwCommandBuffer>* cbh)override;
    virtual void drawIndexedIndirect(
        Handle<HwBufferObject> drawBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride,
        Handle<HwCommandBuffer>* cbh
    )override;
    virtual void bindComputePipeline(
        Handle<HwComputeProgram> pipelineHandle,
        Handle<HwCommandBuffer> cbh,
        const Handle<HwDescriptorSet>* descSets,
        uint32_t setCount)override;

    virtual void dispatchComputeShader(int32_t x, int32_t y, int32_t z, Handle<HwCommandBuffer>* cbh) override;

    virtual void pushGroupMarker(const char* maker, const Ogre::Vector3i& color = Ogre::Vector3i(0, 0, 0));
    virtual void popGroupMarker();

    virtual void bindVertexBuffer(
        Handle<HwBufferObject> bufHandle, 
        uint32_t binding,
        uint32_t vertexSize);
    virtual void bindIndexBuffer(
        Handle<HwBufferObject> bufHandle, 
        uint32_t indexSize,
        uint32_t offset)override;
    virtual void* lockBuffer(Handle<HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes);
    virtual void unlockBuffer(Handle<HwBufferObject> bufHandle);
    virtual Handle<HwBufferObject> createBufferObject(
        BufferDesc& desc) override;
    virtual void updateBufferObject(
        Handle<HwBufferObject> boh,
        const char* data,
        uint32_t size,
        uint32_t offset,
        Handle<HwCommandBuffer>* cbh) override;
    virtual bool getBufferInfo(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        Ogre::BufferDesc& desc) override;
    virtual void clearBufferObject(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
    )override;

    virtual uint8_t* bufferMap(filament::backend::Handle<filament::backend::HwBufferObject> boh) override;

    virtual void bufferUnmap(filament::backend::Handle<filament::backend::HwBufferObject> boh) override;

    virtual bool getBufferObject(filament::backend::Handle<filament::backend::HwBufferObject> boh,
        const char* data,
        uint32_t size,
        uint32_t offset);
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(Handle<HwProgram> programHandle, uint32_t set);
    virtual Handle<HwDescriptorSet> createDescriptorSet(
        Handle<HwProgram> programHandle,
        uint32_t set);
    
    virtual Handle<HwPipelineLayout> createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts);
    virtual Handle<HwProgram> createShaderProgram(const ShaderInfo& mShaderInfo, VertexDeclaration* decl);
    
    virtual Handle<HwSampler> createTextureSampler(filament::backend::SamplerParams& samplerParams);
    virtual Handle<HwComputeProgram> createComputeProgram(const ShaderInfo& shaderInfo);
    virtual Handle<HwDescriptorSet> createDescriptorSet(
        Handle<HwComputeProgram> programHandle,
        uint32_t set);
    virtual Handle<HwPipeline> createPipeline(
        backend::RasterState& rasterState,
        Handle<HwProgram>& program
    );

    virtual void updateDescriptorSet(
        Handle<HwDescriptorSet> dsh,
        uint32_t count,
        const DescriptorData* pParams
    );
    virtual void resourceBarrier(
        uint32_t numBufferBarriers,
        BufferBarrier* pBufferBarriers,
        uint32_t textureBarrierCount,
        TextureBarrier* pTextureBarriers,
        uint32_t numRtBarriers,
        RenderTargetBarrier* pRtBarriers,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* dsh,
        Ogre::QueueType queueType = QUEUE_TYPE_GRAPHICS
    )override;


    virtual void beginCmd();
    virtual void flushCmd(Handle<HwCommandQueue>  cqh, bool waitCmd);

    virtual Handle<HwFence> createFence(bool signaled) override;
    virtual void waitFence(Handle<HwFence> fh) override;

    virtual Handle<HwSemaphore> createSemaphore()override;
    virtual Handle<HwCommandBuffer> createCommandBuffer(Ogre::QueueType type) override;
    virtual void beginCommandBuffer(Handle<HwCommandBuffer> cbh) override;
    virtual void endCommandBuffer(Handle<HwCommandBuffer> cbh) override;
    virtual void clearCommandBuffer(Handle<HwCommandBuffer> cbh) override;
    virtual Handle<HwCommandQueue> createCommandQueue(Ogre::QueueType type, uint32_t queueIndex)override;

    virtual Handle<HwSwapChain> createSwapChain(Ogre::RenderWindow* renderWindow) override;
    virtual void swapChainResize(Handle<HwCommandQueue>, Handle<HwSwapChain> sc)override;
    virtual void swapChainAcquire(
        Handle<HwCommandQueue> cqh,
        Handle<HwSwapChain> sch,
        SwapChainInfo& scInfo) override;

    virtual Handle<HwShader> createShader(Ogre::ShaderDesc& desc) override;

    virtual Handle<HwPipeline> createPipeline(
        Ogre::PipelineCreateInfo& pipelineCreateInfo,
        Handle<HwShader>& shader
    )override;
    virtual filament::backend::Handle<filament::backend::HwPipeline> createComputePipeline(
        filament::backend::Handle<filament::backend::HwShader>& shader
    )override;
    virtual Handle<HwDescriptorSet> createDescriptorSet(
        Handle<HwShader> programHandle,
        uint32_t set)override;
    virtual void executeAndPresent(
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
    )override;


    virtual void bindVertexBuffer(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        uint32_t binding_count,
        const filament::backend::Handle<filament::backend::HwBufferObject>* bufHandle,
        const uint64_t* p_offsets)override;
    virtual void bindIndexBuffer(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
        uint32_t indexSize,
        uint32_t offset)override;
    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle)override;

    virtual void bindDescriptorSet(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwShader> sh,
        filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)override;
    void bindDescriptorSet(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwProgram> ph,
        filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)override;
protected:
    Dx12ResourceAllocator mResourceAllocator;
    DX12Commands* mCommands;

    DX12PipelineCache mDX12PipelineCache;

    Dx12RenderWindow* mRenderWindow;
    DX12SwapChain* mSwapChain;
    ID3D12Device* mDevice;

    DxMemoryAllocator* mMemoryAllocator;

    DescriptorHeapContext* mDescriptorHeapContext;
    bool mSetDescriptorHeaps;

    ID3D12CommandSignature* mDrawIndexCommandSignature = nullptr;

    ID3D12PipelineState* mLastPipelineState = nullptr;

    Handle<HwCommandBuffer> mCommandBuffer;
    filament::backend::Handle<filament::backend::HwFence> mCommandFence;

    Dx12TextureListen* mTextureListen;
};