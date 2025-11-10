#pragma once
#include <functional>
#include "shader.h"
#include "engine_struct.h"
#include "OgreTexture.h"
#include "rayTracing.h"
#include "OgreCommon.h"

class GraphicsCommandList;
class RenderableData;
class VertexDeclaration;
struct RenderPassInfo;
struct ComputePassInfo;
struct ShaderInfo;
struct RaytracingShaderInfo;

namespace Ogre
{
    class RenderWindow;
}

class RenderSystem
{
public:
    struct TransferContext
    {
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh;
    };
    RenderSystem();
    ~RenderSystem();
    virtual bool engineInit(bool raytracing = false);
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual Ogre::OgreTexture* createManualTexture(
        const std::string&name,
        Ogre::TextureProperty* texProperty);
    virtual Ogre::RenderWindow* createRenderWindow(
        const Ogre::CreateWindowDesc& desc) = 0;

    virtual Ogre::RenderTarget* createRenderTarget(
        const std::string& name,
        Ogre::TextureProperty& texProperty);
    virtual void clearRenderTarget(
        Ogre::RenderTarget*, 
        const Ogre::Vector4& color,
        const Ogre::TextureSubresourceRange& subresources) {}
    
    virtual void ready() {}

    virtual const std::string& getRenderSystemName()
    {
        return mRenderSystemName;
    }

    void incrTriangleCount(uint32_t count)
    {
        mTriangleCount += count;
    }
    uint32_t getTriangleCount()
    {
        return mTriangleCount;
    }

    void incrBatchCount(uint32_t count)
    {
        mBatchCount += count;
    }

    uint32_t getBatchCount()
    {
        return mBatchCount;
    }
    virtual void setViewport(
        float x, float y, float width, float height, float minDepth, float maxDepth,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh) {}
    virtual void setScissor(
        uint32_t x, uint32_t y, uint32_t width, uint32_t height,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh) {}
    virtual void beginRenderPass(
        RenderPassInfo& renderPassInfo);
    virtual void endRenderPass(RenderPassInfo& renderPassInfo);

    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle)
    {
        assert_invariant(false);
    }

    virtual void bindDescriptorSets(
        filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount)
    {
        assert_invariant(false);
    }

    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwRaytracingProgram> programHandle,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount
    ) 
    {
        assert_invariant(false);
    }

    virtual void traceRay(
        filament::backend::Handle<filament::backend::HwRaytracingProgram> programHandle,
        uint32_t width, uint32_t height, uint32_t depth
    ) {}

    virtual void copyImage(
        filament::backend::Handle<filament::backend::HwCommandBuffer>cbh,
        Ogre::RenderTarget* dst,
        Ogre::RenderTarget* src,
        Ogre::ImageCopyDesc& desc)
    {
        assert_invariant(false);
    }

    virtual void copyImage(
        Ogre::OgreTexture* dst,
        Ogre::OgreTexture* src,
        Ogre::ImageCopyDesc& desc) 
    {
        assert_invariant(false);
    }

    virtual void copyImageToBuffer(
        Ogre::OgreTexture* image,
        filament::backend::Handle<filament::backend::HwBufferObject> bufferHandle,
        Ogre::Extent3D extent
    ) {
        assert_invariant(false);
    }
    virtual void copyBuffer(
        filament::backend::Handle<filament::backend::HwBufferObject> src,
        uint32_t srcOffset,
        filament::backend::Handle<filament::backend::HwBufferObject> dst,
        uint32_t dstOffset,
        uint32_t size,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
    ) 
    {
        assert_invariant(false);
    }
    virtual void drawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t firstInstance,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh = nullptr)
    {
        assert_invariant(false);
    }

    virtual void draw(
        uint32_t vertexCount, 
        uint32_t instanceCount , 
        uint32_t firstVertex,
        uint32_t firstInstance,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh = nullptr
        )
    {
        assert_invariant(false);
    }
    virtual void drawIndexedIndirect(
        filament::backend::Handle<filament::backend::HwBufferObject> drawBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh = nullptr
    ) 
    {
        assert_invariant(false);
    }

    virtual void bindComputePipeline(
        filament::backend::Handle<filament::backend::HwComputeProgram> pipelineHandle,
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount)
    {
        assert_invariant(false);
    }

    virtual void dispatchComputeShader(int32_t x, int32_t y, int32_t z, 
        filament::backend::Handle<filament::backend::HwCommandBuffer>*)
    {
        assert_invariant(false);
    }


    virtual void present();

    virtual void pushGroupMarker(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh, const char* maker, const Ogre::Vector3i& color = Ogre::Vector3i(0,0,0))
    {
        assert_invariant(false);
    }
    virtual void popGroupMarker(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
    {
        assert_invariant(false);
    }

    virtual void getFamilyInfo(Ogre::FamilyInfo& desc)
    {
        assert_invariant(false);
    }
    /*virtual void bindVertexBuffer(
        filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
        uint32_t binding,
        uint32_t vertexSize) 
    {
        assert_invariant(false);
    }
    

    virtual void bindIndexBuffer(
        filament::backend::Handle<filament::backend::HwBufferObject> bufHandle, 
        uint32_t indexSize,
        uint32_t offset) 
    {
        assert_invariant(false);
    }*/

    virtual filament::backend::Handle<filament::backend::HwBufferObject> createBufferObject(
        Ogre::BufferDesc& desc);
    virtual void updateBufferObject(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        const char* data, 
        uint32_t size,
        uint32_t offset = 0,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh = nullptr);
    virtual bool getBufferInfo(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        Ogre::BufferDesc& desc)
    {
        assert_invariant(false);
        return false;
    }

    virtual void clearBufferObject(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
    );

    virtual uint8_t* bufferMap(filament::backend::Handle<filament::backend::HwBufferObject> boh)
    {
        assert_invariant(false);
        return nullptr;
    }

    virtual void bufferUnmap(filament::backend::Handle<filament::backend::HwBufferObject> boh,
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
    {
        assert_invariant(false);
    }

    virtual bool getBufferObject(filament::backend::Handle<filament::backend::HwBufferObject> boh,
        char* data,
        uint32_t size,
        uint32_t offset = 0) {
        return false;
    }
    virtual filament::backend::Handle<filament::backend::HwDescriptorSet> createDescriptorSet(
        filament::backend::Handle<filament::backend::HwProgram> programHandle,
        uint32_t set);
    virtual filament::backend::Handle<filament::backend::HwDescriptorSet> createDescriptorSet(
        filament::backend::Handle<filament::backend::HwComputeProgram> programHandle,
        uint32_t set);
    virtual filament::backend::Handle<filament::backend::HwDescriptorSet> createDescriptorSet(
        filament::backend::Handle<filament::backend::HwRaytracingProgram> programHandle,
        uint32_t set);
    virtual filament::backend::Handle<filament::backend::HwPipelineLayout> createPipelineLayout(std::array<filament::backend::Handle<filament::backend::HwDescriptorSetLayout>, 4>& layouts);
    virtual filament::backend::Handle<filament::backend::HwProgram> createShaderProgram(const ShaderInfo& mShaderInfo, VertexDeclaration* decl);
    virtual filament::backend::Handle<filament::backend::HwRaytracingProgram> createRaytracingProgram(const RaytracingShaderInfo& mShaderInfo);
    virtual filament::backend::Handle<filament::backend::HwSampler> createTextureSampler(filament::backend::SamplerParams& samplerParams);
    virtual filament::backend::Handle<filament::backend::HwComputeProgram> createComputeProgram(const ShaderInfo& shaderInfo);
    virtual filament::backend::Handle<filament::backend::HwPipeline> createPipeline(
        filament::backend::RasterState& rasterState,
        filament::backend::Handle<filament::backend::HwProgram>& program
        );

    virtual void updateDescriptorSet(
        filament::backend::Handle<filament::backend::HwDescriptorSet> dsh,
        uint32_t count, 
        const Ogre::DescriptorData* pParams
        ) 
    {
        assert_invariant(false);
    }
    virtual void resourceBarrier(
        uint32_t numBufferBarriers, 
        Ogre::BufferBarrier* pBufferBarriers,
        uint32_t textureBarrierCount, 
        Ogre::TextureBarrier* pTextureBarriers,
        uint32_t numRtBarriers, 
        Ogre::RenderTargetBarrier* pRtBarriers,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* dsh,
        Ogre::QueueType queueType = Ogre::QUEUE_TYPE_GRAPHICS
    ) 
    {
        assert_invariant(false);
    }


    virtual void beginCmd()
    {
        assert_invariant(false);
    }
    virtual void flushCmd(filament::backend::Handle<filament::backend::HwCommandQueue> cqh, bool waitCmd)
    {
        assert_invariant(false);
    }

    virtual void flushCmd(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh, 
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        bool waitCmd)
    {
        assert_invariant(false);
    }
    //raytracing

    virtual void addAccelerationStructure(
        const Ogre::AccelerationStructureDesc* pDesc,
        Ogre::AccelerationStructure** ppAccelerationStructure) {
        assert_invariant(false);
    }

    virtual void buildAccelerationStructure(Ogre::RaytracingBuildASDesc* pDesc) {
        assert_invariant(false);
    }

    virtual void removeAccelerationStructureScratch(
        Ogre::AccelerationStructure* pAccelerationStructure) {}

    virtual uint64_t getBufferDeviceAddress(filament::backend::Handle<filament::backend::HwBufferObject> bufHandle)
    {
        return 0;
    }
    //destroy
    virtual void destroyBufferObject(filament::backend::Handle<filament::backend::HwBufferObject> bufHandle) {}

    virtual uint32_t getAlignmentSize(Ogre::BufferObjectBinding bufferType) { return 0; }

    //

    virtual filament::backend::Handle<filament::backend::HwFence> createFence(bool signaled);
    virtual void waitFence(filament::backend::Handle<filament::backend::HwFence> fh);

    virtual filament::backend::Handle<filament::backend::HwSemaphore> createSemaphore();
    virtual filament::backend::Handle<filament::backend::HwCommandBuffer> createCommandBuffer(Ogre::QueueType);
    virtual void beginCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh);
    virtual void endCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh);
    virtual void clearCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh);
    virtual filament::backend::Handle<filament::backend::HwCommandQueue> createCommandQueue(
        Ogre::QueueType, uint32_t queueIndex);
    virtual filament::backend::Handle<filament::backend::HwSwapChain> createSwapChain(Ogre::RenderWindow* renderWindow);
    virtual void swapChainResize(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
        filament::backend::Handle<filament::backend::HwSwapChain> sch);
    virtual void swapChainAcquire(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
        filament::backend::Handle<filament::backend::HwSwapChain> sch,
        Ogre::SwapChainInfo& scInfo);
    virtual filament::backend::Handle<filament::backend::HwShader> createShader(Ogre::ShaderDesc& desc);
    virtual filament::backend::Handle<filament::backend::HwPipeline> createPipeline(
        Ogre::PipelineCreateInfo& pipelineCreateInfo,
        filament::backend::Handle<filament::backend::HwShader>& shader
    );
    virtual filament::backend::Handle<filament::backend::HwPipeline> createComputePipeline(
        filament::backend::Handle<filament::backend::HwShader>& shader
    );
    virtual filament::backend::Handle<filament::backend::HwDescriptorSet> createDescriptorSet(
        filament::backend::Handle<filament::backend::HwShader> programHandle,
        uint32_t set);

    virtual void copyBufferToTexture(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwBufferObject> boh, 
        Ogre::OgreTexture* tex,
        Ogre::ImageCopyBufferDesc& desc
    );

    virtual void executeAndPresent(
        filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
        filament::backend::Handle<filament::backend::HwSemaphore> *wait_sph,
        uint32_t wait_sp_size,
        filament::backend::Handle<filament::backend::HwCommandBuffer>*cbh,
        uint32_t cb_size,
        filament::backend::Handle<filament::backend::HwSemaphore>* cmd_sph,
        uint32_t cmd_sp_size,
        filament::backend::Handle<filament::backend::HwFence> fh,
        filament::backend::Handle<filament::backend::HwSwapChain>* sch,
        uint32_t sc_size
    );

    virtual void clearRenderTexture(
        Ogre::OgreTexture*, 
        const Ogre::Vector4& color,
        const Ogre::TextureSubresourceRange& subresources,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh);

    virtual void updatePushConstants(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwShader> sh,
        uint32_t offset,
        const char* data,
        uint32_t size);

    virtual void bindVertexBuffer(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        uint32_t binding_count,
        const filament::backend::Handle<filament::backend::HwBufferObject>* bufHandle,
        const uint64_t* p_offsets);

    virtual void bindIndexBuffer(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
        uint32_t indexSize,
        uint32_t offset);

    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle);

    virtual void bindDescriptorSet(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwShader> sh,
        filament::backend::Handle<filament::backend::HwDescriptorSet>dsh);

    virtual void bindDescriptorSet(
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
        filament::backend::Handle<filament::backend::HwProgram> ph,
        filament::backend::Handle<filament::backend::HwDescriptorSet>dsh);

    virtual uint64_t limit_get(Ogre::Limit limit);

    virtual TransferContext* getTransferContext();
protected:
	
    uint32_t mBatchCount = 0;
    uint32_t mTriangleCount = 0;
    uint32_t mLoadResCount = 0;


    std::string mRenderSystemName;
    uint32_t mRenderType;
    
    
};
