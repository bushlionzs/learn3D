#include "OgreHeader.h"
#include "OgreHeader.h"
#include "VulkanRenderData.h"
#include "OgreCamera.h"
#include "VulkanRenderSystem.h"
#include "OgreMaterial.h"
#include "VulkanTexture.h"
#include "VulkanShader.h"
#include "OgreTextureUnit.h"
#include "OgreRenderable.h"
#include "engine_struct.h"
#include "VulkanHelper.h"
#include "VulkanFrame.h"
#include "vertex_data.h"
#include "index_data.h"
#include "vertex_declaration.h"
#include "OgreHardwareIndexBuffer.h"
#include "OgreRoot.h"
#include <utils/JobSystem.h>

VulkanRenderableData::VulkanRenderableData(VulkanRenderSystem* engine, Ogre::Renderable* r)
    :RenderableData(r)
{
	mEngine = engine;
    mDevice = VulkanHelper::getSingleton()._getVkDevice();
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
        if (mat->isLoading())
        {
            return false;
        }
        if (job)
        {
            utils::JobSystem* js = Ogre::Root::getSingleton().getJobSystem();
            utils::JobSystem::Job* sub = utils::jobs::createJob(*js, job, [mat] {
                mat->load(nullptr);
                }
            );
            
            
            mat->setLoading(true);
            

            js->runAndRetain(sub);
            return false;
        }
        else
        {
            mat->load(nullptr);
        }
    }

    updateImpl(frame);
    return true;
}

void VulkanRenderableData::updateImpl(VulkanFrame* frame)
{
    auto mat = _r->getMaterial().get();
    VulkanShader* shader = (VulkanShader*)mat->getShader().get();
    shader->getVKPipeline(_r);

    auto cam = mEngine->_getCamera();
    const Ogre::Matrix4& view = cam->getViewMatrix();
    const Ogre::Matrix4& proj = cam->getProjectMatrix();
    const Ogre::Matrix4& model = _r->getModelMatrix();

    VulkanObjectPool& pool = frame->getObjectPool();
    auto& current = _frameRenderableData[frame->getFrameIndex()];
    current.mObjectConstantBuffer.world = model.transpose();
    current.mObjectConstantBuffer.projector = _r->getProjectorMatrix();
    current.mObjectConstantBuffer.worldViewProj = current.mObjectConstantBuffer.world * view * proj;

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

    uint32_t tex_count = VULKAN_TEXTURE_COUNT;


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

            textureDescriptor.imageView = tex->getImageView();
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
                textureDescriptor.imageView = tex->getImageView();
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
            textureDescriptor.imageView = tex->getImageView();
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
            textureDescriptor.imageView = tex->getImageView();
            textureDescriptor.sampler = tex->getSampler();
            textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }

        int32_t start = textureDescriptors.size();
        if (start < tex_count)
        {
            auto defaultTex = VulkanHelper::getSingleton().getDefaultTexture();
            VulkanTexture* tex = (VulkanTexture*)defaultTex.get();
            for (int32_t i = start; i < tex_count; i++)
            {
                textureDescriptors.emplace_back();
                VkDescriptorImageInfo& textureDescriptor = textureDescriptors.back();
                textureDescriptor.imageView = tex->getImageView();
                textureDescriptor.sampler = tex->getSampler();
                textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            }
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

    std::vector<VkWriteDescriptorSet> writeDescriptorSets =
    {
        // Binding 0 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            0,
            &bufferDescriptor),
        // Binding 1 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            1,
            &frameDescriptor),
        //Bind 2:
        vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            2,
            &materialDescriptor),
        // Binding 4 : Fragment shader texture sampler
        vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            4,
            textureDescriptors.data(),
            std::min((uint32_t)VULKAN_TEXTURE_COUNT, (uint32_t)textureDescriptors.size()))
    };

    if (current.mSkinnedDesc._vkObjectIndex > 0)
    {
        auto skinnedInfo = pool.getObjectInfo(current.mSkinnedDesc);
        VkDescriptorBufferInfo skinDescriptor = {};
        skinDescriptor.buffer = skinnedInfo._vulkanBuffer;
        skinDescriptor.offset = skinnedInfo._offset;
        skinDescriptor.range = sizeof(SkinnedConstantBuffer);

        // Binding 5 : Vertex shader uniform buffer
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            5,
            &skinDescriptor));
    }

    if (!textureDescriptors3d.empty())
    {
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            current.mDescriptorSet,
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

void VulkanRenderableData::render(VulkanFrame* frame, VkCommandBuffer cb)
{
    auto mat = _r->getMaterial().get();

    const std::shared_ptr<Shader>& shader = mat->getShader();

    VulkanShader* vShader = (VulkanShader*)shader.get();
    //bind pipeline
    VkPipeline pipeline = vShader->getVKPipeline(_r);

    vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    //draw object

    VertexData* vertexData = _r->getVertexData();
    IndexData* indexData = _r->getIndexData();
    vertexData->bind(cb);
    VulkanFrameRenderableData& current = _frameRenderableData[frame->getFrameIndex()];
    
    auto pipelineLayout = VulkanHelper::getSingleton()._getPipelineLayout();
    vkCmdBindDescriptorSets(
        cb,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout, 0, 1, &current.mDescriptorSet, 0, NULL);

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
            vkCmdDraw(cb, vertexData->vertexCount, 1, 0, 0);
            mEngine->incrTriangleCount(vertexData->vertexCount / 3);
        }
        else
        {
            vkCmdDraw(cb, view->mVertexCount, 1, view->mVertexStart, 0);
            mEngine->incrTriangleCount(view->mVertexCount / 3);
        }
        
    }

    mEngine->incrBatchCount(1);
}




//VkPipelineLayout  VulkanRenderableData::getPipelineLayout()
//{
//    return VulkanHelper::getSingleton()._getPipelineLayout();
//}

void VulkanRenderableData::buildInitData()
{
    auto descriptorPool = VulkanHelper::getSingleton()._getDescriptorPool();
    auto descriptorSetLayout = VulkanHelper::getSingleton()._getDescriptorSetLayout();

    VkDescriptorSetAllocateInfo allocInfo =
        vks::initializers::descriptorSetAllocateInfo(
            descriptorPool,
            &descriptorSetLayout,
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
        
    }
    

    

    
}

