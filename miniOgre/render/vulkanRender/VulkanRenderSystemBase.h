#pragma once
#include "VulkanCommon.h"
#include "renderSystem.h"
#include "SHADER.H"
#include <VulkanStagePool.h>
#include <VulkanHandles.h>
#include <VulkanResourceAllocator.h>
#include <VulkanResources.h>
#include <VulkanCommands.h>
#include <VulkanSwapChain.h>
#include <VulkanPlatform.h>
#include <VulkanDescriptorPool.h>
#include <VulkanContext.h>

class VertexDeclaration;
class VulkanGraphicsCommandList;
class VulkanFrame;
class VulkanWindow;
class VulkanPipelineCache;
class VulkanPipelineLayoutCache;
class VulkanLayoutCache;
class Ogre::ICamera;

class VulkanRenderSystemBase: public RenderSystem
{
public:
	VulkanRenderSystemBase();
	~VulkanRenderSystemBase();
public:
    virtual bool engineInit(bool raytracing) override;

    virtual OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);
    virtual Ogre::OgreTexture* createManualTexture(
        const std::string& name,
        Ogre::TextureProperty* texProperty)override;
    virtual void ready();
    virtual Ogre::RenderWindow* createRenderWindow(
        const CreateWindowDesc& desc) override;

    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, 
        TextureProperty& texProperty) override;
    virtual void clearRenderTarget(Ogre::RenderTarget*, const Ogre::Vector4& color) override;
    virtual void clearRenderTexture(OgreTexture*, const Ogre::Vector4& color)override;
    virtual void frameStart() override;
    virtual void frameEnd() override;
    virtual void setViewport(float x, float y, float width, float height, float minDepth, float maxDepth);
    virtual void setScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    virtual void beginRenderPass(RenderPassInfo& renderPassInfo) override;
    virtual void endRenderPass(RenderPassInfo& renderPassInfo) override;
    virtual void bindPipeline(
        Handle<HwPipeline> pipelineHandle,
        const Handle<HwDescriptorSet>* descSets,
        uint32_t setCount) override;
    virtual void draw(uint32_t vertexCount,
        uint32_t instanceCount,
        uint32_t firstVertex,
        uint32_t firstInstance,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
    ) override;
    virtual void drawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        uint32_t vertexOffset,
        uint32_t firstInstance,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh);
    virtual void drawIndexedIndirect(
        Handle<HwBufferObject> drawBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
    );

    void bindComputePipeline(
        Handle<HwComputeProgram> pipelineHandle,
        const Handle<HwDescriptorSet>* descSets,
        uint32_t setCount);

    void dispatchComputeShader(int32_t x, int32_t y, int32_t z);

    virtual void present() override;

    virtual void copyImage(
        Ogre::RenderTarget* dst,
        Ogre::RenderTarget* src,
        ImageCopyDesc& desc) override;

    virtual void copyImage(
        Ogre::OgreTexture* dst,
        Ogre::OgreTexture* src,
        Ogre::ImageCopyDesc& desc) override;

    virtual void copyBuffer(
        Handle<HwBufferObject> src,
        uint32_t srcOffset,
        Handle<HwBufferObject> dst,
        uint32_t dstOffset,
        uint32_t size,
        filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh
    ) override;
protected:
    virtual void pushGroupMarker(const char* maker, const Ogre::Vector3i& color)override;
    virtual void popGroupMarker();
    virtual void getFamilyInfo(FamilyInfo& desc)override;
    virtual void* bufferMap(Handle<HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes);
    virtual void bufferUnmap(Handle<HwBufferObject> bufHandle);
    virtual void bindVertexBuffer(
        Handle<HwBufferObject> bufHandle, 
        uint32_t binding,
        uint32_t offset);
    virtual void bindIndexBuffer(
        Handle<HwBufferObject>, 
        uint32_t indexSize,
        uint32_t offset) override;
    virtual Handle<HwBufferObject> createBufferObject(
        BufferDesc& desc) override;

    virtual void updateBufferObject(
        Handle<HwBufferObject> boh,
        const char* data, 
        uint32_t size,
        uint32_t offset) override;
    virtual bool getBufferInfo(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        Ogre::BufferDesc& desc)override;

    virtual void clearBufferObject(
        filament::backend::Handle<filament::backend::HwBufferObject> boh,
        filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
    )override;
    bool getBufferObject(Handle<HwBufferObject> boh,
        const char* data,
        uint32_t size,
        uint32_t offset) override;
    virtual Handle<HwDescriptorSet> createDescriptorSet(
        Handle<HwProgram> programHandle,
        uint32_t set) override;
    virtual Handle<HwDescriptorSet> createDescriptorSet(
        Handle<HwComputeProgram> programHandle,
        uint32_t set) override;
    virtual Handle<HwPipelineLayout> createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts) override;
    virtual Handle<HwProgram> createShaderProgram(
        const ShaderInfo& mShaderInfo, 
        VertexDeclaration* decl) override;
    virtual void updatePushConstants(
        Handle<HwProgram> program,
        uint32_t offset,
        const char* data,
        uint32_t size);
    virtual Handle<HwSampler> createTextureSampler(filament::backend::SamplerParams& samplerParams);
    virtual Handle<HwComputeProgram> createComputeProgram(const ShaderInfo& mShaderInfo) override;
    virtual Handle<HwPipeline> createPipeline(
        backend::RasterState& rasterState, 
        Handle<HwProgram>& program) override;
    
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
        QueueType queueType = QUEUE_TYPE_GRAPHICS
    )  override;
    virtual void beginCmd();
    virtual void flushCmd(bool waitCmd);


    virtual void destroyBufferObject(Handle<HwBufferObject> bufHandle);

    virtual uint32_t getAlignmentSize(BufferObjectBinding bufferType);

    virtual Handle<HwFence> createFence() override;
    virtual void waitFence(Handle<HwFence> fh) override;

    virtual Handle<HwSemaphore> createSemaphore()override;
    virtual Handle<HwCommandBuffer> createCommandBuffer(uint32_t queueFamilyIndex) override;
    virtual void beginCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh) override;
    virtual void endCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh) override;
    virtual void clearCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh) override;
    virtual Handle<HwCommandQueue> createCommandQueue(uint32_t familyIndex, uint32_t queueIndex)override;

    virtual Handle<HwSwapChain> createSwapChain() override;
    virtual void swapChainAcquire(
        filament::backend::Handle<filament::backend::HwSwapChain> sch,
        SwapChainInfo& scInfo) override;

    virtual Handle<HwShader> createShader(Ogre::ShaderDesc& desc) override;

    virtual Handle<HwPipeline> createPipeline(
        Ogre::PipelineCreateInfo& pipelineCreateInfo,
        Handle<HwShader>& shader
    )override;
protected:
    void bingingUpdate(
        vks::tools::BingdingInfo& bindingMap,
        vks::tools::BingdingInfo& results,
        VkShaderStageFlagBits flagBits);
protected:
    VulkanWindow* mRenderWindow;
    VkCommandBuffer mCommandBuffer = VK_NULL_HANDLE;


    VkDescriptorPool       pEmptyDescriptorPool;
    VkDescriptorSetLayout  pEmptyDescriptorSetLayout;
    VkDescriptorSet        pEmptyDescriptorSet;


    VulkanPipelineCache* mPipelineCache = nullptr;
    VulkanPipelineLayoutCache* mPipelineLayoutCache = nullptr;
    VulkanLayoutCache* mVulkanLayoutCache = nullptr;
    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VulkanResourceAllocator mResourceAllocator;
    VulkanStagePool* mStagePool;
    VulkanCommands* mCommands;
    VulkanSwapChain* mSwapChain = nullptr;
    VulkanPlatform* mVulkanPlatform;
    DescriptorInfinitePool* mDescriptorInfinitePool = nullptr;
    VulkanContext mVulkanContext;

    VulkanSettings* mVulkanSettings;

    VkPipeline mLastPipeline;
};