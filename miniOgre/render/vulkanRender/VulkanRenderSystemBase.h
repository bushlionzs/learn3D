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
    bool engineInit();

    virtual OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);
    virtual void ready();
    virtual RenderableData* createRenderableData(Ogre::Renderable* r);
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) override;

    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, 
        uint32_t width, 
        uint32_t height, 
        Ogre::PixelFormat format, 
        uint32_t usage) override;
    //
    ICamera* _getCamera();
protected:
    void updateMainPassCB(ICamera* camera);

    virtual Ogre::OgreTexture* generateCubeMap(
        const std::string& name,
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format,
        int32_t dim,
        CubeType type);
    virtual Ogre::OgreTexture* generateBRDFLUT(const std::string& name);

    virtual FrameConstantBuffer* getFrameConstantBuffer()
    {
        return &mFrameConstantBuffer;
    }

    virtual void pushGroupMarker(const char* maker);
    virtual void popGroupMarker();
    virtual void* lockBuffer(Handle<HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes);
    virtual void unlockBuffer(Handle<HwBufferObject> bufHandle);
    virtual void bindVertexBuffer(Handle<HwBufferObject> bufHandle, uint32_t binding);
    virtual void bindIndexBuffer(Handle<HwBufferObject>, uint32_t indexSize);
    virtual Handle<HwBufferObject> createBufferObject(
        uint32_t bindingType,
        BufferUsage usage,
        uint32_t byteCount,
        const char* debugName) override;

    virtual void updateBufferObject(
        Handle<HwBufferObject> boh,
        const char* data, 
        uint32_t size) override;

    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(Handle<HwProgram> programHandle, uint32_t index) override;
    virtual Handle<HwDescriptorSet> createDescriptorSet(Handle<HwDescriptorSetLayout> dslh) override;
    virtual Handle<HwPipelineLayout> createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts) override;
    virtual Handle<HwProgram> createShaderProgram(
        const ShaderInfo& mShaderInfo, 
        VertexDeclaration* decl) override;
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(
        Handle<HwComputeProgram> programHandle, 
        uint32_t set) override;
    virtual Handle<HwSampler> createTextureSampler(filament::backend::SamplerParams& samplerParams);
    virtual Handle<HwComputeProgram> createComputeProgram(const ShaderInfo& mShaderInfo) override;
    virtual Handle<HwPipeline> createPipeline(
        backend::RasterState& rasterState, 
        Handle<HwProgram>& program) override;
    virtual void updateDescriptorSetBuffer(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        backend::BufferObjectHandle* boh,
        uint32_t handleCount) override;
    virtual void updateDescriptorSetTexture(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        OgreTexture** tex,
        uint32_t count,
        bool onlyImage) override;
    virtual void updateDescriptorSetSampler(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        Handle<HwSampler> samplerHandle) override;
    virtual void updateDescriptorSetSampler(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        OgreTexture* tex) override;

    virtual void resourceBarrier(
        uint32_t numBufferBarriers,
        BufferBarrier* pBufferBarriers
    )  override;
private:
    void parseInputBindingDescription(
        VertexDeclaration* decl,
        std::vector<GlslInputDesc>& inputDesc,
        std::vector<VkVertexInputBindingDescription>& vertexInputBindings);
    void parseAttributeDescriptions(
        VertexDeclaration* vd,
        std::vector<GlslInputDesc>& inputDesc,
        std::vector<VkVertexInputAttributeDescription>& attributeDescriptions);
protected:
    RenderPassInfo mCurrentRenderPassInfo;

    FrameConstantBuffer mFrameConstantBuffer;
    VulkanWindow* mRenderWindow;

    VkImage mCurrentVKImage;

    VkCommandBuffer mCommandBuffer = VK_NULL_HANDLE;

    std::vector<Ogre::Renderable*> mRenderList;

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
};