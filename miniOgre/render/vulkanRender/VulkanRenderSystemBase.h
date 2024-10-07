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
#include <VulkanContext.h>
#include <VulkanDescriptorSetManager.h>

class VertexDeclaration;
class VulkanGraphicsCommandList;
class VulkanFrame;
class VulkanWindow;
class VulkanPipelineCache;
class VulkanPipelineLayoutCache;
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

    virtual Handle<HwBufferObject> createBufferObject(
        BufferObjectBinding bindingType,
        BufferUsage usage,
        uint32_t byteCount) override;

    virtual void updateBufferObject(
        Handle<HwBufferObject> boh,
        const char* data, 
        uint32_t size) override;

    virtual Handle<HwDescriptorSetLayout> createDescriptorSetLayout(DescriptorSetLayout& info) override;
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(Handle<HwProgram> programHandle, uint32_t index) override;
    virtual Handle<HwDescriptorSet> createDescriptorSet(Handle<HwDescriptorSetLayout> dslh) override;
    virtual Handle<HwPipelineLayout> createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts) override;
    virtual Handle<HwProgram> createShaderProgram(
        const ShaderInfo& mShaderInfo, 
        VertexDeclaration* decl) override;
    virtual Handle<HwDescriptorSetLayout> getDescriptorSetLayout(Handle<HwComputeProgram>) override;
    virtual Handle<HwComputeProgram> createComputeProgram(const ShaderInfo& mShaderInfo) override;
    virtual Handle<HwPipeline> createPipeline(
        backend::RasterState& rasterState, 
        Handle<HwProgram>& program) override;

    virtual void bindDescriptorSet(
        Handle<HwDescriptorSet> dsh,
        uint8_t setIndex,
        backend::DescriptorSetOffsetArray&& offsets) override;
    virtual void updateDescriptorSetBuffer(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        backend::BufferObjectHandle boh,
        uint32_t offset,
        uint32_t size) override;
    virtual void updateDescriptorSetTexture(
        Handle<HwDescriptorSet> dsh,
        backend::descriptor_binding_t binding,
        OgreTexture* tex) override;
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

    std::vector<Ogre::Renderable*> mRenderList;


    VulkanPipelineCache* mPipelineCache = nullptr;
    VulkanPipelineLayoutCache* mPipelineLayoutCache = nullptr;
    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VulkanResourceAllocator mResourceAllocator;

    VulkanStagePool* mStagePool;
    VulkanCommands* mCommands;
    VulkanSwapChain* mSwapChain = nullptr;
    VulkanPlatform* mVulkanPlatform;
    VulkanContext mVulkanContext;
    VulkanDescriptorSetManager* mDescriptorSetManager;
};