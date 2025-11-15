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

Ogre::OgreTexture* RenderSystem::createManualTexture(
    const std::string& name,
    Ogre::TextureProperty* texProperty)
{
    assert_invariant(false);
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

filament::backend::Handle<filament::backend::HwBufferObject> RenderSystem::createBufferObject(
    BufferDesc& desc)
{
    assert_invariant(false);
    return filament::backend::Handle<filament::backend::HwBufferObject>();
}

void RenderSystem::updateBufferObject(
    filament::backend::Handle<filament::backend::HwBufferObject> boh,
    const char* data, 
    uint32_t size,
    uint32_t offset,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
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

filament::backend::Handle<filament::backend::HwFence> RenderSystem::createFence(bool signaled)
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

filament::backend::Handle<filament::backend::HwCommandBuffer> RenderSystem::createCommandBuffer(Ogre::QueueType)
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

filament::backend::Handle<filament::backend::HwCommandQueue> RenderSystem::createCommandQueue(Ogre::QueueType type, uint32_t queueIndex)
{
    assert_invariant(false);
    return Handle<HwCommandQueue>();
}


filament::backend::Handle<filament::backend::HwSwapChain> RenderSystem::createSwapChain(Ogre::RenderWindow* renderWindow)
{
    assert_invariant(false);
    return Handle<HwSwapChain>();
}

void RenderSystem::swapChainResize(
    filament::backend::Handle<filament::backend::HwCommandQueue>,
    filament::backend::Handle<filament::backend::HwSwapChain> sc)
{
    assert_invariant(false);
}

void RenderSystem::swapChainAcquire(
    filament::backend::Handle<filament::backend::HwCommandQueue> cqh,
    Handle<HwSwapChain> sch, SwapChainInfo& scInfo)
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

filament::backend::Handle<filament::backend::HwPipeline> RenderSystem::createComputePipeline(
    filament::backend::Handle<filament::backend::HwShader>& shader
)
{
    assert_invariant(false);
    return Handle<HwPipeline>();
}

Handle<HwDescriptorSet> RenderSystem::createDescriptorSet(
    Handle<HwShader> programHandle,
    uint32_t set)
{
    assert_invariant(false);
    return Handle<HwDescriptorSet>();
}

void RenderSystem::copyBufferToTexture(
    Handle<HwCommandBuffer> cbh,
    Handle<HwBufferObject> boh,
    Ogre::OgreTexture* tex,
    Ogre::ImageCopyBufferDesc& desc
)
{
    assert_invariant(false);
}

void RenderSystem::executeAndPresent(
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
    assert_invariant(false);
}

void RenderSystem::clearRenderTexture(
    Ogre::OgreTexture*, 
    const Ogre::Vector4& color,
    const Ogre::TextureSubresourceRange& subresources,
    filament::backend::Handle<filament::backend::HwCommandBuffer>* cbh)
{
    assert_invariant(false);
}

void RenderSystem::updatePushConstants(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwShader> sh,
    uint32_t offset,
    const char* data,
    uint32_t size)
{
    assert_invariant(false);
}

void RenderSystem::bindVertexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    uint32_t binding_count,
    const filament::backend::Handle<filament::backend::HwBufferObject>* bufHandle,
    const uint64_t* p_offsets)
{
    assert_invariant(false);
}

void RenderSystem::bindIndexBuffer(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwBufferObject> bufHandle,
    uint32_t indexSize,
    uint32_t offset)
{
    assert_invariant(false);
}

void RenderSystem::bindPipeline(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwPipeline> pipelineHandle)
{
    assert_invariant(false);
}

void RenderSystem::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwShader> sh,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    assert_invariant(false);
}

void RenderSystem::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwProgram> ph,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    assert_invariant(false);
}

void RenderSystem::bindDescriptorSet(
    filament::backend::Handle<filament::backend::HwCommandBuffer> cbh,
    filament::backend::Handle<filament::backend::HwRaytracingProgram> ph,
    filament::backend::Handle<filament::backend::HwDescriptorSet>dsh)
{
    assert_invariant(false);
}

uint64_t RenderSystem::limit_get(Ogre::Limit limit)
{
    assert_invariant(false);
    return 0;
}

RenderSystem::TransferContext* RenderSystem::getTransferContext()
{
    assert_invariant(false);
    return nullptr;
}