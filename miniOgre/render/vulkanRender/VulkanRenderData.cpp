#include "OgreHeader.h"
#include "OgreHeader.h"
#include "VulkanRenderData.h"
#include "OgreCamera.h"
#include "VulkanRenderSystem.h"
#include "OgreMaterial.h"
#include "VulkanTexture.h"
#include "OgreTextureUnit.h"
#include "OgreRenderable.h"
#include "engine_struct.h"
#include "VulkanHelper.h"
#include "VulkanFrame.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreHardwareIndexBuffer.h"
#include "OgreRoot.h"
#include "VulkanHardwareBuffer.h"
#include "VulkanRaytracing.h"
#include "VulkanTools.h"
#include "VulkanMappings.h"
#include <vulkan/VulkanPipelineCache.h>
#include "shaderManager.h"
#include "OgreResourceManager.h"
#include <utils/JobSystem.h>



VulkanRenderableData::VulkanRenderableData(
    VulkanRenderSystemBase* engine,
    Ogre::Renderable* r,
    VulkanRayTracingContext* context)
    :RenderableData(r)
{
	mEngine = engine;
    mDevice = VulkanHelper::getSingleton()._getVkDevice();

    mRayTracingContext = context;
    buildInitData();
}

VulkanRenderableData::~VulkanRenderableData()
{

}

bool VulkanRenderableData::update(VulkanFrame* frame, utils::JobSystem::Job* job)
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

    updateImpl(frame);
    return true;
}

void VulkanRenderableData::updateImpl(VulkanFrame* frame)
{
    auto mat = _r->getMaterial().get();
    
    auto cam = mEngine->_getCamera();
    const Ogre::Matrix4& view = cam->getViewMatrix();
    const Ogre::Matrix4& proj = cam->getProjectMatrix();
    const Ogre::Matrix4& model = _r->getModelMatrix();

    VulkanObjectPool& pool = frame->getObjectPool();
    auto& current = _frameRenderableData[frame->getFrameIndex()];
    current.mObjectConstantBuffer.world =  model.transpose();
    current.mObjectConstantBuffer.worldViewProj = (proj * view * model).transpose();

    pool.updateObject(
        current.mObjectDesc, (const char*)&current.mObjectConstantBuffer, sizeof(current.mObjectConstantBuffer));

    RawData* rd = _r->getSkinnedData(2);
    if (rd)
    {
        if (current.mSkinnedDesc._vkObjectIndex == 0)
        {
            current.mSkinnedDesc = pool.allocObject(VulkanObject_SkinnedCB);
        }
        pool.updateObject(current.mSkinnedDesc, rd->mData, rd->mDataSize);
    }

    if (mat->getTextureUnitCount())
    {
        auto unit = mat->getTextureUnit(0);
        current.mMaterialConstantBuffer.TexTransform =
            unit->getTextureTransform().transpose();
    }

    if (mat->isPbr())
    {
        auto& matInfo = mat->getMatInfo();
        pool.updateObject(current.mPBRMaterialDesc, (const char*)&matInfo, sizeof(matInfo));
    }
    else
    {
        pool.updateObject(
            current.mMaterialDesc,
            (const char*)&current.mMaterialConstantBuffer,
            sizeof(current.mMaterialConstantBuffer));
    }


    VkDescriptorBufferInfo frameDescriptor = {};
    mEngine->_getCurrentFrame()->updateFrameDescriptor(frameDescriptor, cam);

    if (mat->isChanged())
    {
        mat->setChanged(false);

        for (uint32_t i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
        {
            auto& current = _frameRenderableData[i];
            current.mDescriptorSetUpdate = false;
        }
    }

    if (current.mDescriptorSetUpdate)
    {
        return;
    }

    current.mDescriptorSetUpdate = true;

    auto texs = mat->getAllTexureUnit();

    std::vector<VkDescriptorImageInfo> textureDescriptors;

    std::vector<VkDescriptorImageInfo> textureDescriptors3d;

    uint32_t tex_count = 9;


    textureDescriptors.reserve(tex_count);

    if (mat->isPbr())
    {
        auto texs = mat->getAllTexureUnit();
        textureDescriptors.resize(tex_count);
        for (int32_t i = 0; i < texs.size(); i++)
        {
            VulkanTexture* tex = (VulkanTexture*)texs[i]->getRaw();
            TextureProperty* tp = texs[i]->getTextureProperty();
            uint32_t index = tp->_pbrType - TextureTypePbr_Albedo;
            VkDescriptorImageInfo& textureDescriptor = textureDescriptors[index];

            textureDescriptor.imageView = tex->getVkImageView();
            textureDescriptor.sampler = tex->getSampler();
            textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }

        auto defaultTex = VulkanHelper::getSingleton().getDefaultTexture();
        VulkanTexture* tex = (VulkanTexture*)defaultTex.get();
        for (int32_t i = 0; i < textureDescriptors.size(); i++)
        {
            VkDescriptorImageInfo& textureDescriptor = textureDescriptors[i];
            if (textureDescriptor.imageView == nullptr)
            {
                textureDescriptor.imageView = tex->getVkImageView();
                textureDescriptor.sampler = tex->getSampler();
                textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            }
        }

    }
    else
    {
        for (int32_t i = 0; i < texs.size(); i++)
        {
            if (texs[i]->getTextureProperty()->_texType == TEX_TYPE_CUBE_MAP)
                continue;
            VulkanTexture* tex = (VulkanTexture*)texs[i]->getRaw();

            textureDescriptors.emplace_back();
            VkDescriptorImageInfo& textureDescriptor = textureDescriptors.back();
            textureDescriptor.imageView = tex->getVkImageView();
            textureDescriptor.sampler = tex->getSampler();
            textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }

        for (int32_t i = 0; i < texs.size(); i++)
        {
            if (texs[i]->getTextureProperty()->_texType != TEX_TYPE_CUBE_MAP)
                continue;
            VulkanTexture* tex = (VulkanTexture*)texs[i]->getRaw();

            textureDescriptors3d.emplace_back();
            VkDescriptorImageInfo& textureDescriptor = textureDescriptors3d.back();
            textureDescriptor.imageView = tex->getVkImageView();
            textureDescriptor.sampler = tex->getSampler();
            textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
    }




    VkDescriptorBufferInfo bufferDescriptor = {};

    auto objectCBInfo = pool.getObjectInfo(current.mObjectDesc);

    bufferDescriptor.buffer = objectCBInfo._vulkanBuffer;
    bufferDescriptor.offset = objectCBInfo._offset;
    bufferDescriptor.range = sizeof(ObjectConstantBuffer);

    VkDescriptorBufferInfo materialDescriptor = {};
    VulkanBufferInfo materialInfo;
    if (mat->isPbr())
    {
        materialInfo = pool.getObjectInfo(current.mPBRMaterialDesc);
    }
    else
    {
        materialInfo = pool.getObjectInfo(current.mMaterialDesc);
    }

    materialDescriptor.buffer = materialInfo._vulkanBuffer;
    materialDescriptor.offset = materialInfo._offset;
    materialDescriptor.range = sizeof(MaterialConstantBuffer);

    auto descriptorSet = current.mDescriptorSet;
    bool pbr = mat->isPbr();
    auto descriptorSetSampler = pbr?current.mDescriptorSetSamplerPbr:current.mDescriptorSetSampler;

    std::vector<VkWriteDescriptorSet> writeDescriptorSets =
    {
        // Binding 0 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            descriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            0,
            &bufferDescriptor),
        // Binding 1 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            descriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            1,
            &frameDescriptor),
        //Bind 2:
        vks::initializers::writeDescriptorSet(
            descriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            2,
            &materialDescriptor)
    };

    if (!textureDescriptors.empty())
    {
        auto descriptor = textureDescriptors.data();

        for (uint32_t i = 0; i < textureDescriptors.size(); i++)
        {
            writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
                descriptorSetSampler,
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                i,
                descriptor + i,
                1));
        }
        
    }

    if (current.mSkinnedDesc._vkObjectIndex > 0)
    {
        auto skinnedInfo = pool.getObjectInfo(current.mSkinnedDesc);
        VkDescriptorBufferInfo skinDescriptor = {};
        skinDescriptor.buffer = skinnedInfo._vulkanBuffer;
        skinDescriptor.offset = skinnedInfo._offset;
        skinDescriptor.range = sizeof(SkinnedConstantBuffer);

        // Binding 3 : Vertex shader uniform buffer
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            descriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            3,
            &skinDescriptor));
    }

    if (!textureDescriptors3d.empty())
    {
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            descriptorSetSampler,
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            3,
            textureDescriptors3d.data(),
            textureDescriptors3d.size()));
    }

    vkUpdateDescriptorSets(
        mDevice,
        static_cast<uint32_t>(writeDescriptorSets.size()),
        writeDescriptorSets.data(), 0, nullptr);
}

void VulkanRenderableData::render(VulkanFrame* frame, VkCommandBuffer cb, VulkanPipelineCache* pipelineCache)
{
    auto mat = _r->getMaterial().get();
    pipelineCache->bindRenderPass(nullptr, 0);
    pipelineCache->bindProgram(mVertexShader, mFragShader);
    pipelineCache->bindRasterState(mRasterState);
    pipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    bool pbr = mat->isPbr();
    auto pipelineLayout = VulkanHelper::getSingleton()._getPipelineLayout(pbr);
    pipelineCache->bindLayout(pipelineLayout);

    pipelineCache->bindVertexArray(
        attributeDescriptions.data(), 
        attributeDescriptions.size(), 
        vertexInputBindings.data(), 
        vertexInputBindings.size());

    pipelineCache->bindPipeline(cb);
    //draw object

    VertexData* vertexData = _r->getVertexData();
    IndexData* indexData = _r->getIndexData();
    vertexData->bind(cb);
    VulkanFrameRenderableData& current = _frameRenderableData[frame->getFrameIndex()];
    
    VkDescriptorSet ds[2] = {current.mDescriptorSet, pbr?current.mDescriptorSetSamplerPbr :current.mDescriptorSetSampler};

    
    vkCmdBindDescriptorSets(
        cb,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout, 0, 2, &ds[0], 0, nullptr);

    

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

    if (mRayTracingUpdate)
    {
        const Ogre::Matrix4& m = _r->getModelMatrix();
        mRayTracingContext->updateTransform(mGeometrySlot, m);
        return false;
    }

    mRayTracingUpdate = true;
    if (mRayTracingContext)
    {
        VertexData* vb = _r->getVertexData();
        IndexData* ib = _r->getIndexData();
        HardwareVertexBuffer* vertexBuffer = (HardwareVertexBuffer*)vb->getBuffer(0);

        VulkanHardwareBuffer* vulkanBuffer = (VulkanHardwareBuffer*)vertexBuffer->getHardwareBuffer();
        VulkanHardwareBuffer* vulkanIndexBuffer = (VulkanHardwareBuffer*)ib->mIndexBuffer->getHardwareBuffer();
        mGeometryNode.vertexBufferDeviceAddress.deviceAddress = vks::tools::getBufferDeviceAddress(mDevice, vulkanBuffer->getVKBuffer());// +primitive->firstVertex * sizeof(vkglTF::Vertex);
        mGeometryNode.indexBufferDeviceAddress.deviceAddress = vks::tools::getBufferDeviceAddress(mDevice, vulkanIndexBuffer->getVKBuffer())
            + ib->mIndexStart * ib->mIndexBuffer->getIndexSize();
        mGeometrySlot = mRayTracingContext->allocGeometrySlot(mGeometryNode);
        mGeometryNode.transformBufferDeviceAddress.deviceAddress =
            vks::tools::getBufferDeviceAddress(mDevice, mRayTracingContext->getTransformBuffer())
            + mGeometrySlot * sizeof(VkTransformMatrixKHR);

        mGeometry = {};
        mGeometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
        mGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
        mGeometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
        mGeometry.geometry.triangles.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
        mGeometry.geometry.triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
        mGeometry.geometry.triangles.vertexData = mGeometryNode.vertexBufferDeviceAddress;
        mGeometry.geometry.triangles.maxVertex = vb->getVertexCount();
        mGeometry.geometry.triangles.vertexStride = vb->getVertexSize(0);
        mGeometry.geometry.triangles.indexType = ib->mIndexBuffer->getIndexSize() == 4 ? VK_INDEX_TYPE_UINT32 : VK_INDEX_TYPE_UINT16;
        mGeometry.geometry.triangles.indexData = mGeometryNode.indexBufferDeviceAddress;
        mGeometry.geometry.triangles.transformData = mGeometryNode.transformBufferDeviceAddress;

        auto mat = _r->getMaterial().get();
        auto texs = mat->getAllTexureUnit();

        for (int32_t i = 0; i < texs.size(); i++)
        {
            VulkanTexture* tex = (VulkanTexture*)texs[i]->getRaw();

            int32_t slot = tex->getSlot();

            if (slot == -1)
            {
                slot = mRayTracingContext->allocTextureSlot(tex);
            }

            mGeometryNode.textureIndex[i] = slot;

        }



        VkTransformMatrixKHR tmp;

        mBuildRangeInfo.firstVertex = vb->getVertexStart();
        mBuildRangeInfo.primitiveOffset = 0;
        mBuildRangeInfo.primitiveCount = ib->mIndexCount / 3;
        mBuildRangeInfo.transformOffset = 0;

        const Ogre::Matrix4& m = _r->getModelMatrix();
        mRayTracingContext->updateTransform(mGeometrySlot, m);
    }

    return true;
}

void VulkanRenderableData::buildInitData()
{
    if (!_frameRenderableData.empty())
    {
        return;
    }
    auto descriptorPool = VulkanHelper::getSingleton()._getDescriptorPool();
    auto descriptorSetLayout = VulkanHelper::getSingleton()._getDescriptorSetLayout(VulkanLayoutIndex_Data);

    VkDescriptorSetAllocateInfo allocInfo =
        vks::initializers::descriptorSetAllocateInfo(
            descriptorPool,
            &descriptorSetLayout,
            1);

    auto descriptorSetLayoutSampler = VulkanHelper::getSingleton()._getDescriptorSetLayout(VulkanLayoutIndex_Unlit);

    VkDescriptorSetAllocateInfo allocInfoSampler =
        vks::initializers::descriptorSetAllocateInfo(
            descriptorPool,
            &descriptorSetLayoutSampler,
            1);

    auto descriptorSetLayoutSamplerPbr = VulkanHelper::getSingleton()._getDescriptorSetLayout(VulkanLayoutIndex_Pbr);
    VkDescriptorSetAllocateInfo allocInfoSamplerPbr =
        vks::initializers::descriptorSetAllocateInfo(
            descriptorPool,
            &descriptorSetLayoutSamplerPbr,
            1);

    _frameRenderableData.resize(VULKAN_FRAME_RESOURCE_COUNT);

    for (uint32_t i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {
        VulkanFrameRenderableData& current = _frameRenderableData[i];

        VulkanFrame* frame = VulkanHelper::getSingleton()._getFrame(i);

        VulkanObjectPool& pool = frame->getObjectPool();
        current.mObjectDesc = pool.allocObject(VulkanObject_ObjectCB);
        current.mMaterialDesc = pool.allocObject(VulkanObject_MaterialCB);
        current.mPBRMaterialDesc = pool.allocObject(VulkanObject_PBRMaterialCB);
        current.mSkinnedDesc._vkObjectType = VulkanObject_SkinnedCB;

        auto result = vkAllocateDescriptorSets(mDevice, &allocInfo, &current.mDescriptorSet);
        if(result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate descriptor set!");
        }
        
        result = vkAllocateDescriptorSets(mDevice, &allocInfoSampler, &current.mDescriptorSetSampler);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate descriptor set!");
        }

        result = vkAllocateDescriptorSets(mDevice, &allocInfoSamplerPbr, &current.mDescriptorSetSamplerPbr);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate descriptor set!");
        }
    }
}

void VulkanRenderableData::parseInputBindingDescription(
    VertexDeclaration* decl,
    std::vector<GlslInputDesc>& inputDesc)
{
    vertexInputBindings.clear();
    for (uint32_t binding = 0; binding < 10; binding++)
    {
        int32_t stride = decl->getVertexSize(binding);

        if (stride <= 0)
            continue;
        vertexInputBindings.emplace_back();
        vertexInputBindings.back().binding = binding;
        vertexInputBindings.back().stride = stride;
        vertexInputBindings.back().inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
}

void VulkanRenderableData::parseAttributeDescriptions(
    VertexDeclaration* vd,
    std::vector<GlslInputDesc>& inputDesc)
{
    attributeDescriptions.resize(inputDesc.size());
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
                attributeDescriptions[i].binding = elem.getSource();
                attributeDescriptions[i].location = input._location;
                attributeDescriptions[i].format = getVKFormatFromType(elem.getType());
                attributeDescriptions[i].offset = elem.getOffset();
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
    const auto& shaderInfo = mat->getShaderInfo();
    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);

    std::vector<GlslInputDesc> inputDesc;

    if (mVertexShader == VK_NULL_HANDLE)
    {
        String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
        auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);

        if (res == nullptr)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to find shader!");
        }

        mVertexShader = glslCompileVertexShader(
            res->_fullname,
            *vertexContent,
            privateInfo->vertexShaderEntryPoint,
            shaderInfo.shaderMacros,
            inputDesc);

        VertexDeclaration* decl = _r->getVertexData()->getVertexDeclaration();
        parseInputBindingDescription(decl, inputDesc);
        parseAttributeDescriptions(decl, inputDesc);
    }
    
    
    if (mFragShader == VK_NULL_HANDLE)
    {
        String* fragContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);

        auto res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
        mFragShader = glslCompileFragShader(
            res->_fullname,
            *fragContent,
            privateInfo->fragShaderEntryPoint,
            shaderInfo.shaderMacros);
    }


    auto findLocation = [&inputDesc](const VertexElement& elem) -> int32_t
        {
            for (auto& input : inputDesc)
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

    struct RasterState {
        VkCullModeFlags       cullMode : 2;
        VkFrontFace           frontFace : 2;
        VkBool32              depthBiasEnable : 1;
        VkBool32              blendEnable : 1;
        VkBool32              depthWriteEnable : 1;
        VkBool32              alphaToCoverageEnable : 1;
        VkBlendFactor         srcColorBlendFactor : 5; // offset = 1 byte
        VkBlendFactor         dstColorBlendFactor : 5;
        VkBlendFactor         srcAlphaBlendFactor : 5;
        VkBlendFactor         dstAlphaBlendFactor : 5;
        VkColorComponentFlags colorWriteMask : 4;
        uint8_t               rasterizationSamples;    // offset = 4 bytes
        uint8_t               colorTargetCount;        // offset = 5 bytes
        BlendEquation         colorBlendOp : 4;        // offset = 6 bytes
        BlendEquation         alphaBlendOp : 4;
        SamplerCompareFunc    depthCompareOp;          // offset = 7 bytes
        float                 depthBiasConstantFactor; // offset = 8 bytes
        float                 depthBiasSlopeFactor;    // offset = 12 bytes
    };
    mRasterState.colorWriteMask = 0xf;
    mRasterState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    mRasterState.colorTargetCount = 1;
    mRasterState.depthCompareOp = SamplerCompareFunc::LE;
    mRasterState.depthBiasConstantFactor = 0.0f;
    mRasterState.depthBiasSlopeFactor = 0.0f;
}


