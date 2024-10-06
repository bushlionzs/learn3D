#include "OgreHeader.h"
#include <utils/JobSystem.h>
#include "engine_struct.h"
#include "VulkanRenderData.h"
#include "OgreCamera.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "OgreRenderable.h"
#include "shaderManager.h"
#include "OgreResourceManager.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreHardwareIndexBuffer.h"
#include "OgreRoot.h"
#include "VulkanRenderSystemBase.h"
#include "VulkanHardwareBuffer.h"
#include "VulkanTools.h"
#include "VulkanMappings.h"
#include "VulkanPipelineLayoutCache.h"
#include "VulkanLayoutCache.h"
#include "VulkanTexture.h"
#include "VulkanFrame.h"





VulkanRenderableData::VulkanRenderableData(
    VulkanPlatform* platform,
    VulkanCommands* commands,
    Ogre::Renderable* r)
    :RenderableData(r)
{
    mEngine = (VulkanRenderSystemBase*)Ogre::Root::getSingleton().getRenderSystem();
    mCommands = commands;
    mDevice = platform->getDevice();

    mVertexShaderInfo.shaderType = Ogre::ShaderType::VertexShader;
    mVertexShaderInfo.shaderModule = VK_NULL_HANDLE;
    mVertexShaderInfo.uboMask = 1 | 2 | 4 | 8;
    mVertexShaderInfo.samplerMask = 1 | 2 | 4 | 8 | 16;
    mFragShaderInfo.shaderType = Ogre::ShaderType::PixelShader;
    mFragShaderInfo.shaderModule = VK_NULL_HANDLE;
    mFragShaderInfo.uboMask = 1 | 2 | 4 | 8;
    mFragShaderInfo.samplerMask = 1 | 2 | 4 | 8 | 16;

    buildInitData();
}

VulkanRenderableData::~VulkanRenderableData()
{

}

bool VulkanRenderableData::update(
    const RenderPassInfo& passInfo,
    utils::JobSystem::Job* job)
{
    
    auto mat = _r->getMaterial().get();
    
    if (!mat->isLoaded())
    {
         mat->load(nullptr);
    }

    buildPipelineData(mat);
    

    if (VulkanHelper::getSingleton().haveRayTracing())
    {
        return true;
    }

    updateImpl(passInfo);
    return true;
}

void VulkanRenderableData::updateImpl(const RenderPassInfo& passInfo)
{
    auto frameNumber = Ogre::Root::getSingleton().getCurrentFrame();
    auto frameIndex = frameNumber % VULKAN_FRAME_RESOURCE_COUNT;
    auto mat = _r->getMaterial().get();
    
    auto cam = passInfo.cam;
    const Ogre::Matrix4& view = cam->getViewMatrix();
    const Ogre::Matrix4& proj = cam->getProjectMatrix();
    const Ogre::Matrix4& model = _r->getModelMatrix();
    VulkanFrame* frame = VulkanHelper::getSingleton()._getFrame(frameIndex);
    VulkanObjectPool& pool = frame->getObjectPool();
    VulkanFrameRenderableData* current = nullptr;
    if (passInfo.shadowPass)
    {
        current = &mFrameRenderableData[frameIndex];
    }
    else
    {
        current = &mFrameRenderableData[frameIndex];
    }
    
    /*current->mObjectConstantBuffer.world =  model.transpose();
    current->mObjectConstantBuffer.worldViewProj = (proj * view * model).transpose();

    pool.updateObject(
        current->mObjectDesc, 
        (const char*)&current->mObjectConstantBuffer,
        sizeof(current->mObjectConstantBuffer));

    RawData* rd = _r->getSkinnedData(2);
    if (rd)
    {
        if (current->mSkinnedDesc._vkObjectIndex == 0)
        {
            current->mSkinnedDesc = pool.allocObject(VulkanObject_SkinnedCB);
        }
        pool.updateObject(current->mSkinnedDesc, rd->mData, rd->mDataSize);
    }

    if (mat->getTextureUnitCount())
    {
        auto unit = mat->getTextureUnit(0);
        current->mMaterialConstantBuffer.TexTransform =
            unit->getTextureTransform().transpose();
    }

    if (mat->isPbr())
    {
        auto& matInfo = mat->getMatInfo();
        pool.updateObject(current->mPBRMaterialDesc, (const char*)&matInfo, sizeof(matInfo));
    }
    else
    {
        pool.updateObject(
            current->mMaterialDesc,
            (const char*)&current->mMaterialConstantBuffer,
            sizeof(current->mMaterialConstantBuffer));
    }*/


    VkDescriptorBufferInfo frameDescriptor = {};
    frame->updateFrameDescriptor(frameDescriptor, cam);

    

   
}

void VulkanRenderableData::render(
    VkCommandBuffer cb, 
    VulkanPipelineCache* pipelineCache,
    const RenderPassInfo& passInfo)
{
    auto frameNumber = Ogre::Root::getSingleton().getCurrentFrame();
    auto frameIndex = frameNumber % VULKAN_FRAME_RESOURCE_COUNT;

    auto mat = _r->getMaterial().get();
    bindPipeline(cb, pipelineCache, passInfo.shadowPass);
    

    VertexData* vertexData = _r->getVertexData();
    IndexData* indexData = _r->getIndexData();
    vertexData->bind(cb);
    VulkanFrameRenderableData* current = nullptr;
    if (passInfo.shadowPass)
    {
        current = &mFrameRenderableData[frameIndex];
    }
    else
    {
        current = &mFrameRenderableData[frameIndex];
    }

    bool pbr = mat->isPbr();
    VkDescriptorSet ds[2] = 
    {
       /* current->mDescriptorSet, 
        pbr?current->mDescriptorSetSamplerPbr :current->mDescriptorSetSampler*/
    };

    

    vkCmdBindDescriptorSets(
        cb,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        mPipelineLayout, 0, 2, &ds[0], 0, nullptr);

    //draw object

    if (indexData)
    {
        indexData->getIndexBuffer()->bind(cb);
        IndexDataView* view = _r->getIndexView();
        vkCmdDrawIndexed(cb, view->mIndexCount, 1,
            view->mIndexLocation, view->mBaseVertexLocation, 0);

        mEngine->incrTriangleCount(view->mIndexCount / 3);
    }
    else
    {
        RawDataView* view = _r->getRawDataView();
        if (view == nullptr)
        {
            vkCmdDraw(cb, vertexData->getVertexCount(), 1, 0, 0);
            mEngine->incrTriangleCount(vertexData->getVertexCount() / 3);
        }
        else
        {
            vkCmdDraw(cb, view->mVertexCount, 1, view->mVertexStart, 0);
            mEngine->incrTriangleCount(view->mVertexCount / 3);
        }
        
    }

    mEngine->incrBatchCount(1);
}


bool VulkanRenderableData::updateRayTracingData()
{
    return true;
}

void VulkanRenderableData::buildInitData()
{
    buildLayout();

    Ogre::Material* mat = _r->getMaterial().get();

    buildPipelineData(mat);

    mFrameRenderableData.resize(VULKAN_FRAME_RESOURCE_COUNT);

    RenderSystem* rs = VulkanHelper::getSingleton()._getRenderSystem();
    for (auto i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {
        VulkanFrameRenderableData& current = mFrameRenderableData[i];
        current.uboShadowSet = rs->createDescriptorSet(mUBOLayout);
        current.uboSet = rs->createDescriptorSet(mUBOLayout);
        current.samplerSet = rs->createDescriptorSet(mSamplerLayout);
    }
}

void VulkanRenderableData::parseInputBindingDescription(
    VertexDeclaration* decl,
    std::vector<GlslInputDesc>& inputDesc)
{
    mVertexInputBindings.clear();
    for (uint32_t binding = 0; binding < 10; binding++)
    {
        int32_t stride = decl->getVertexSize(binding);

        if (stride <= 0)
            continue;
        mVertexInputBindings.emplace_back();
        mVertexInputBindings.back().binding = binding;
        mVertexInputBindings.back().stride = stride;
        mVertexInputBindings.back().inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
}

void VulkanRenderableData::parseAttributeDescriptions(
    VertexDeclaration* vd,
    std::vector<GlslInputDesc>& inputDesc)
{
    mAttributeDescriptions.resize(inputDesc.size());
    int32_t i = 0;

    for (auto& input : inputDesc)
    {
        bool find = false;

        auto& elementlist = vd->getElementList();
        for (auto elem : elementlist)
        {
            if (input._name == VulkanMappings::getSemanticName(elem.getSemantic()) &&
                input._index == elem.getIndex())
            {
                mAttributeDescriptions[i].binding = elem.getSource();
                mAttributeDescriptions[i].location = input._location;
                mAttributeDescriptions[i].format = getVKFormatFromType(elem.getType());
                mAttributeDescriptions[i].offset = elem.getOffset();
                i++;
                find = true;
                break;
            }
        }


        if (!find)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "can not find input param");
        }
    }
}


void VulkanRenderableData::buildPipelineData(Ogre::Material* mat)
{
    bool change = false;
    if (mVertexShaderInfo.shaderModule == nullptr)
    {
        change = true;
        const auto& shaderInfo = mat->getShaderInfo();
        Ogre::ShaderPrivateInfo* privateInfo =
            ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);
        String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
        auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);

        if (res == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to find shader!");
        }

        glslCompileShader(
            res->_fullname,
            *vertexContent,
            privateInfo->vertexShaderEntryPoint,
            shaderInfo.shaderMacros,
            mVertexShaderInfo);


        VertexDeclaration* decl = _r->getVertexData()->getVertexDeclaration();
        parseInputBindingDescription(decl, mVertexShaderInfo.inputDesc);
        parseAttributeDescriptions(decl, mVertexShaderInfo.inputDesc);
    }
    

    
    if (mFragShaderInfo.shaderModule == nullptr)
    {
        change = true;
        const auto& shaderInfo = mat->getShaderInfo();
        Ogre::ShaderPrivateInfo* privateInfo =
            ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);
        String* fragContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);

        auto res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
        glslCompileShader(
            res->_fullname,
            *fragContent,
            privateInfo->fragShaderEntryPoint,
            shaderInfo.shaderMacros,
            mFragShaderInfo);
    }

    if (!change)
    {
        return;
    }


    auto findLocation = [&](const VertexElement& elem) -> int32_t
        {
            for (auto& input : mVertexShaderInfo.inputDesc)
            {
                if (input._name == VulkanMappings::getSemanticName(elem.getSemantic()) &&
                    input._index == elem.getIndex())
                {
                    return input._location;
                }
            }
            assert(false);
            return -1;
        };
    


    mRasterState.cullMode = VK_CULL_MODE_NONE;
    mRasterState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    mRasterState.depthBiasEnable = VK_FALSE;

    auto blendState = mat->getBlendState();
    mRasterState.blendEnable = blendState.blendingEnabled();
    mRasterState.depthWriteEnable = mat->isWriteDepth();
    mRasterState.alphaToCoverageEnable = VK_FALSE;
    if (mRasterState.blendEnable)
    {
        mRasterState.srcColorBlendFactor = VulkanMappings::get(blendState.sourceFactor, false);
        mRasterState.dstColorBlendFactor = VulkanMappings::get(blendState.destFactor, false);
        mRasterState.srcAlphaBlendFactor = VulkanMappings::get(blendState.sourceFactorAlpha, true);
        mRasterState.dstAlphaBlendFactor = VulkanMappings::get(blendState.destFactorAlpha, true);
        mRasterState.colorBlendOp = BlendEquation::ADD;
        mRasterState.alphaBlendOp = BlendEquation::ADD;
    }
    else
    {
        mRasterState.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        mRasterState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        mRasterState.colorBlendOp = BlendEquation::ADD;
        mRasterState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        mRasterState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        mRasterState.alphaBlendOp = BlendEquation::ADD;
    }
    mRasterState.colorWriteMask = 0xf;
    mRasterState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    mRasterState.colorTargetCount = 1;
    mRasterState.depthCompareOp = SamplerCompareFunc::LE;
    mRasterState.depthBiasConstantFactor = 0.0f;
    mRasterState.depthBiasSlopeFactor = 0.0f;
}

void VulkanRenderableData::bindPipeline(
    VkCommandBuffer cb, 
    VulkanPipelineCache* pipelineCache,
    bool shadow)
{
    if (shadow)
    {

        auto mat = _r->getMaterial().get();
        pipelineCache->bindRenderPass(nullptr, 0);
        
        pipelineCache->bindProgram(mVertexShaderInfo.shaderModule, nullptr);
        
        pipelineCache->bindRasterState(mRasterState);
        pipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
        auto pipelineLayout = VulkanHelper::getSingleton()._getPipelineLayout(false);
        pipelineCache->bindLayout(pipelineLayout);
        pipelineCache->bindVertexArray(
            mAttributeDescriptions.data(),
            mAttributeDescriptions.size(),
            mVertexInputBindings.data(),
            mVertexInputBindings.size());

        pipelineCache->bindPipeline(cb);
    }
    else
    {
        auto mat = _r->getMaterial().get();
        pipelineCache->bindRenderPass(nullptr, 0);
        pipelineCache->bindProgram(mVertexShaderInfo.shaderModule, mFragShaderInfo.shaderModule);
        pipelineCache->bindRasterState(mRasterState);
        pipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
        pipelineCache->bindLayout(mPipelineLayout);

        pipelineCache->bindVertexArray(
            mAttributeDescriptions.data(),
            mAttributeDescriptions.size(),
            mVertexInputBindings.data(),
            mVertexInputBindings.size());

        pipelineCache->bindPipeline(cb);
    }
}

void VulkanRenderableData::buildLayout()
{
    DescriptorSetLayoutBinding binding;

    mUBOLayoutInfo.bindings.reserve(10);

    for (auto i = 0; i < 16; i++)
    {
        bool hasVertex = (mVertexShaderInfo.uboMask & (1uLL << i)) != 0;
        bool hasFragment = (mFragShaderInfo.uboMask & (1uLL << i)) != 0;

        if (!hasVertex && !hasFragment)
            continue;
        binding.binding = i;
       
        binding.flags = DescriptorFlags::NONE;
        binding.count = 0;
        binding.type = DescriptorType::UNIFORM_BUFFER;
        if (hasVertex)
        {
            binding.stageFlags = ShaderStageFlags::VERTEX;
        }

        if (hasFragment)
        {
            binding.stageFlags = static_cast<ShaderStageFlags>(
                binding.stageFlags | ShaderStageFlags::FRAGMENT);
        }
        
        mUBOLayoutInfo.bindings.push_back(binding);
    }

    mSamplerLayoutInfo.bindings.reserve(10);

    for (auto i = 0; i < 32; i++)
    {
        bool hasVertex = (mVertexShaderInfo.samplerMask & (1uLL << i)) != 0;
        bool hasFragment = (mFragShaderInfo.samplerMask & (1uLL << i)) != 0;
        if (!hasVertex && !hasFragment)
            continue;
        binding.binding = i;
        binding.flags = DescriptorFlags::NONE;
        binding.count = 0;
        binding.type = DescriptorType::SAMPLER;
        if (hasVertex)
        {
            binding.stageFlags = ShaderStageFlags::VERTEX;
        }

        if (hasFragment)
        {
            binding.stageFlags = static_cast<ShaderStageFlags>(
                binding.stageFlags | ShaderStageFlags::FRAGMENT);
        }

        mSamplerLayoutInfo.bindings.push_back(binding);
    }

    auto* layoutCache = VulkanHelper::getSingleton().getLayoutCache();

    mLayouts[0] = layoutCache->getLayout(mUBOLayoutInfo);
    mLayouts[1] = layoutCache->getLayout(mSamplerLayoutInfo);

    auto* pipelineLayoutCahce = VulkanHelper::getSingleton().getPipelineLayoutCache();
    mPipelineLayout = pipelineLayoutCahce->getLayout(mLayouts);

}


