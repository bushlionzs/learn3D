#include "OgreHeader.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreRenderTarget.h"
#include "OgreViewport.h"

RenderSystem::RenderSystem()
{
    
}

RenderSystem::~RenderSystem()
{

}

bool RenderSystem::engineInit(bool raytracing)
{
    return false;
}


class DummyDriver : public Driver
{
public:
    virtual void purge() noexcept
    {

    }

    virtual ShaderModel getShaderModel()const noexcept
    {
        return ShaderModel::DESKTOP;
    }

    virtual Dispatcher getDispatcher()const noexcept
    {
        static Dispatcher dispatcher;
        return dispatcher;
    }

    virtual void debugCommandBegin(CommandStream* cmds,
        bool synchronous, const char* methodName) noexcept
    {

    }

    virtual void debugCommandEnd(CommandStream* cmds,
        bool synchronous, const char* methodName) noexcept
    {

    }


};

OgreTexture* RenderSystem::createTextureFromFile(
    const std::string& name,
    Ogre::TextureProperty* texProperty)
{
    return nullptr;
}

Ogre::OgreTexture* RenderSystem::createManualTexture(
    const std::string& name,
    Ogre::TextureProperty* texProperty)
{
    return nullptr;
}

Ogre::RenderTarget* RenderSystem::createRenderTarget(
    const String& name, 
    TextureProperty& texProperty)
{
    return nullptr;
}


void RenderSystem::beginRenderPass(RenderPassInfo& renderPassInfo)
{

}

void RenderSystem::endRenderPass(RenderPassInfo& renderPassInfo)
{

}

void RenderSystem::present()
{

}

Handle<HwBufferObject> RenderSystem::createBufferObject(
    BufferDesc& desc)
{
    assert_invariant(false);
    return Handle<HwBufferObject>();
}

void RenderSystem::updateBufferObject(
    Handle<HwBufferObject> boh, 
    const char* data, 
    uint32_t size,
    uint32_t offset)
{
    assert_invariant(false);
}

void RenderSystem::clearBufferObject(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh
)
{
    assert_invariant(false);
}

Handle<HwDescriptorSet> RenderSystem::createDescriptorSet(
    Handle<HwProgram> programHandle,
    uint32_t set)
{
    assert_invariant(false);
    return Handle<HwDescriptorSet>();
}

Handle<HwDescriptorSet> RenderSystem::createDescriptorSet(
    Handle<HwComputeProgram> programHandle,
    uint32_t set)
{
    assert_invariant(false);
    return Handle<HwDescriptorSet>();
}

Handle<HwDescriptorSet> RenderSystem::createDescriptorSet(
    Handle<HwRaytracingProgram> programHandle,
    uint32_t set)
{
    assert_invariant(false);
    return Handle<HwDescriptorSet>();
}

Handle<HwPipelineLayout> RenderSystem::createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts)
{
    assert_invariant(false);
    return Handle<HwPipelineLayout>();
}

Handle<HwProgram> RenderSystem::createShaderProgram(const ShaderInfo& mShaderInfo, VertexDeclaration* decl)
{
    assert_invariant(false);
    return Handle<HwProgram>();
}

Handle<HwRaytracingProgram> RenderSystem::createRaytracingProgram(
    const RaytracingShaderInfo& mShaderInfo)
{
    assert_invariant(false);
    return Handle<HwRaytracingProgram>();
}

Handle<HwSampler> RenderSystem::createTextureSampler(filament::backend::SamplerParams& samplerParams)
{
    assert_invariant(false);
    return Handle<HwSampler>();
}

Handle<HwComputeProgram> RenderSystem::createComputeProgram(const ShaderInfo& shaderInfo)
{
    assert_invariant(false);
    return Handle<HwComputeProgram>();
}

Handle<HwPipeline> RenderSystem::createPipeline(
    backend::RasterState& rasterState,
    Handle<HwProgram>& program)
{
    assert_invariant(false);
    return Handle<HwPipeline>();
}

filament::backend::Handle<filament::backend::HwFence> RenderSystem::createFence()
{
    assert_invariant(false);
    return Handle<HwFence>();
}

void RenderSystem::waitFence(filament::backend::Handle<filament::backend::HwFence> fh)
{
    assert_invariant(false);
}

filament::backend::Handle<filament::backend::HwSemaphore> RenderSystem::createSemaphore()
{
    assert_invariant(false);
    return Handle<HwSemaphore>();
}

filament::backend::Handle<filament::backend::HwCommandBuffer> RenderSystem::createCommandBuffer(uint32_t queueFamilyIndex)
{
    assert_invariant(false);
    return Handle<HwCommandBuffer>();
}

void RenderSystem::beginCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    assert_invariant(false);
}

void RenderSystem::endCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    assert_invariant(false);
}

void RenderSystem::clearCommandBuffer(filament::backend::Handle<filament::backend::HwCommandBuffer> cbh)
{
    assert_invariant(false);
}

filament::backend::Handle<filament::backend::HwCommandQueue> RenderSystem::createCommandQueue(uint32_t familyIndex, uint32_t queueIndex)
{
    assert_invariant(false);
    return Handle<HwCommandQueue>();
}


filament::backend::Handle<filament::backend::HwSwapChain> RenderSystem::createSwapChain()
{
    assert_invariant(false);
    return Handle<HwSwapChain>();
}

void RenderSystem::swapChainAcquire(Handle<HwSwapChain> sch, SwapChainInfo& scInfo)
{
    assert_invariant(false);
}

Handle<HwShader> RenderSystem::createShader(Ogre::ShaderDesc& desc)
{
    assert_invariant(false);
    return Handle<HwShader>();
}

Handle<HwPipeline> RenderSystem::createPipeline(
    Ogre::PipelineCreateInfo& pipelineCreateInfo,
    filament::backend::Handle<filament::backend::HwShader>& shader
)
{
    assert_invariant(false);
    return Handle<HwPipeline>();
}



