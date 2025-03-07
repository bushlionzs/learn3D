#pragma once
#include <functional>
#include "shader.h"
#include "engine_struct.h"
#include "OgreTexture.h"
#include "rayTracing.h"

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
    RenderSystem();
    ~RenderSystem();
    virtual bool engineInit(bool raytracing = false);
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual Ogre::OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);
    virtual Ogre::OgreTexture* createManualTexture(
        const std::string&name,
        Ogre::TextureProperty* texProperty);
    virtual Ogre::RenderWindow* createRenderWindow(
        const Ogre::CreateWindowDesc& desc) = 0;

    virtual Ogre::RenderTarget* createRenderTarget(
        const std::string& name,
        Ogre::TextureProperty& texProperty);
    virtual void clearRenderTarget(Ogre::RenderTarget*, const Ogre::Vector4& color) {}
    virtual void clearRenderTexture(Ogre::OgreTexture*, const Ogre::Vector4& color) {}
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
    virtual void setViewport(float x, float y, float width, float height, float minDepth, float maxDepth) {}
    virtual void setScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {}
    virtual void beginRenderPass(
        RenderPassInfo& renderPassInfo);
    virtual void endRenderPass(RenderPassInfo& renderPassInfo);

    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount)
    {
    }

    virtual void bindPipeline(
        filament::backend::Handle<filament::backend::HwRaytracingProgram> programHandle,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount
    ) {
    }

    virtual void traceRay(
        filament::backend::Handle<filament::backend::HwRaytracingProgram> programHandle,
        uint32_t width, uint32_t height, uint32_t depth
    ) {}

    virtual void copyImage(
        Ogre::RenderTarget* dst,
        Ogre::RenderTarget* src,
        Ogre::ImageCopyDesc& desc) {
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
        uint32_t size
    ) {}
    virtual void drawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t firstInstance)
    {
    }

    virtual void draw(uint32_t vertexCount, uint32_t firstVertex)
    {

    }
    virtual void drawIndexedIndirect(
        filament::backend::Handle<filament::backend::HwBufferObject> drawBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride
    ) 
    {
    }

    virtual void bindComputePipeline(
        filament::backend::Handle<filament::backend::HwComputeProgram> pipelineHandle,
        const filament::backend::Handle<filament::backend::HwDescriptorSet>* descSets,
        uint32_t setCount)
    {
    }

    virtual void dispatchComputeShader(int32_t x, int32_t y, int32_t z) {}

    virtual void beginComputePass(
        ComputePassInfo& computePassInfo);
    virtual void endComputePass();

    virtual void dispatchComputeShader();
    virtual void present();

    virtual void pushGroupMarker(const char* maker, const Ogre::Vector3i& color = Ogre::Vector3i(0,0,0)) {}
    virtual void popGroupMarker() {}
    virtual void bindVertexBuffer(
        filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
        uint32_t binding,
        uint32_t vertexSize) {}
    virtual void bindIndexBuffer(filament::backend::Handle<filament::backend::HwBufferObject> bufHandle, uint32_t indexSize) {}
    virtual void* lockBuffer(filament::backend::Handle<filament::backend::HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes) { return nullptr; }
    virtual void unlockBuffer(filament::backend::Handle<filament::backend::HwBufferObject> bufHandle) {}
    /*virtual Handle<HwBufferObject> createBufferObject(
        BufferObjectBinding bindingType,
        ResourceMemoryUsage memoryUsage,
        uint32_t bufferCreationFlags,
        uint32_t byteCount,
        const char* debugName = nullptr);*/
    virtual filament::backend::Handle<filament::backend::HwBufferObject> createBufferObject(
        Ogre::BufferDesc& desc);
    virtual void updateBufferObject(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        const char* data, 
        uint32_t size,
        uint32_t offset = 0);
    virtual bool getBufferObject(filament::backend::Handle<filament::backend::HwBufferObject> boh,
        const char* data,
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
    virtual void updatePushConstants(
        filament::backend::Handle<filament::backend::HwProgram> program,
        uint32_t offset, 
        const char* data,
        uint32_t size) {}
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
        ) {}
    virtual void resourceBarrier(
        uint32_t numBufferBarriers, 
        Ogre::BufferBarrier* pBufferBarriers,
        uint32_t textureBarrierCount, 
        Ogre::TextureBarrier* pTextureBarriers,
        uint32_t numRtBarriers, 
        Ogre::RenderTargetBarrier* pRtBarriers,
        Ogre::QueueType queueType = Ogre::QUEUE_TYPE_GRAPHICS
    ) {}


    virtual void beginCmd() {}
    virtual void flushCmd(bool waitCmd) {}
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
protected:
	
    uint32_t mBatchCount = 0;
    uint32_t mTriangleCount = 0;
    uint32_t mLoadResCount = 0;


    std::string mRenderSystemName;
    uint32_t mRenderType;
    
    
};
