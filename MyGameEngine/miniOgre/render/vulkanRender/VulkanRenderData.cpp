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

VulkanRenderableData::VulkanRenderableData(VulkanRenderSystem* engine)
{
	mEngine = engine;
    mDevice = VulkanHelper::getSingleton()._getVkDevice();
	buildInitData();
}

VulkanRenderableData::~VulkanRenderableData()
{

}


void VulkanRenderableData::buildMaterial(Material* mat)
{

}

void VulkanRenderableData::updateData(VulkanPass* pass)
{
    auto cam = mEngine->_getCamera();
    const Ogre::Matrix4& view = cam->getViewMatrix();
    const Ogre::Matrix4& proj = cam->getProjectMatrix();
    const Ogre::Matrix4& model = pass->mRenderable->getModelMatrix();
    mObjectConstantBuffer.world = model.transpose();
    mObjectConstantBuffer.invWorld = mObjectConstantBuffer.world.inverse();
    mObjectConstantBuffer.worldViewProj = mObjectConstantBuffer.world * view * proj;

    VulkanObjectPool::getSingleton().updateObject(
        mObjectDesc, (const char*)&mObjectConstantBuffer, sizeof(mObjectConstantBuffer));

    RawData* rd = pass->mRenderable->getShaderConstantData(2);
    if (rd)
    {
        if (mSkinnedDesc._vkObjectIndex == 0)
        {
            mSkinnedDesc = VulkanObjectPool::getSingleton().allocObject(VulkanObject_SkinnedCB);
        }
        VulkanObjectPool::getSingleton().updateObject(mSkinnedDesc, rd->mData, rd->mDataSize);
    }

    if (pass->mMaterial->getTextureUnitCount())
    {
        auto unit = pass->mMaterial->getTextureUnit(0);
        mMaterialConstantBuffer.TexTransform =
            unit->getTextureTransform().transpose();
    }

    VulkanObjectPool::getSingleton().updateObject(
        mMaterialDesc, (const char*)&mMaterialConstantBuffer, sizeof(mMaterialConstantBuffer));
}


void VulkanRenderableData::updateDescriptorSet(VulkanPass* pass)
{
    updateData(pass);

    auto texs = pass->mMaterial->getAllTexureUnit();

    std::vector<VkDescriptorImageInfo> textureDescriptors;

    std::vector<VkDescriptorImageInfo> textureDescriptors3d;

    textureDescriptors.reserve(VULKAN_TEXTURE_COUNT);

    
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
    if (start< VULKAN_TEXTURE_COUNT)
    {
        auto default = VulkanHelper::getSingleton().getDefaultTexture();
        VulkanTexture* tex = (VulkanTexture*)default.get();
        for (int32_t i = start; i < VULKAN_TEXTURE_COUNT; i++)
        {
            textureDescriptors.emplace_back();
            VkDescriptorImageInfo& textureDescriptor = textureDescriptors.back();
            textureDescriptor.imageView = tex->getImageView();
            textureDescriptor.sampler = tex->getSampler();
            textureDescriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
    }
    
    VkDescriptorBufferInfo bufferDescriptor = {};

    auto objectCBInfo = VulkanObjectPool::getSingleton().getObjectInfo(mObjectDesc);

    bufferDescriptor.buffer = objectCBInfo._vulkanBuffer;
    bufferDescriptor.offset = objectCBInfo._offset;
    bufferDescriptor.range = sizeof(ObjectConstantBuffer);

    VkDescriptorBufferInfo materialDescriptor = {};
    auto materialInfo = VulkanObjectPool::getSingleton().getObjectInfo(mMaterialDesc);
    materialDescriptor.buffer = materialInfo._vulkanBuffer;
    materialDescriptor.offset = materialInfo._offset;
    materialDescriptor.range = sizeof(MaterialConstantBuffer);

    auto& frameCB = mEngine->_getCurrentFrame()->getFrameCB();

    VkDescriptorBufferInfo frameDescriptor = {};
    frameDescriptor.buffer = frameCB->getVKBuffer();
    frameDescriptor.offset = 0;
    frameDescriptor.range = VK_WHOLE_SIZE;

    
    

    std::vector<VkWriteDescriptorSet> writeDescriptorSets =
    {
        // Binding 0 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            0,
            &bufferDescriptor),
        // Binding 1 : Vertex shader uniform buffer
        vks::initializers::writeDescriptorSet(
            mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            1,
            &frameDescriptor),
        //Bind 2:
        vks::initializers::writeDescriptorSet(
            mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            2,
            &materialDescriptor),
        // Binding 4 : Fragment shader texture sampler
        vks::initializers::writeDescriptorSet(
            mDescriptorSet,
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,		 
            4,												
            textureDescriptors.data(),
            std::min((uint32_t)VULKAN_TEXTURE_COUNT, (uint32_t)textureDescriptors.size()))
    };

    if (mSkinnedDesc._vkObjectIndex > 0)
    {
        auto skinnedInfo = VulkanObjectPool::getSingleton().getObjectInfo(mSkinnedDesc);
        VkDescriptorBufferInfo skinDescriptor = {};
        skinDescriptor.buffer = skinnedInfo._vulkanBuffer;
        skinDescriptor.offset = skinnedInfo._offset;
        skinDescriptor.range = sizeof(SkinnedConstantBuffer);

        // Binding 5 : Vertex shader uniform buffer
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            mDescriptorSet,
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            5,
            &skinDescriptor));
    }

    if (!textureDescriptors3d.empty())
    {
        writeDescriptorSets.push_back(vks::initializers::writeDescriptorSet(
            mDescriptorSet,
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


VkDescriptorSet VulkanRenderableData::getDescriptorSet()
{
    return mDescriptorSet;
}

VkPipelineLayout  VulkanRenderableData::getPipelineLayout()
{
    return VulkanHelper::getSingleton()._getPipelineLayout();
}

void VulkanRenderableData::buildInitData()
{
    mObjectDesc = VulkanObjectPool::getSingleton().allocObject(VulkanObject_ObjectCB);
    mMaterialDesc = VulkanObjectPool::getSingleton().allocObject(VulkanObject_MaterialCB);
    mSkinnedDesc._vkObjectType = VulkanObject_SkinnedCB;

    auto descriptorPool = VulkanHelper::getSingleton()._getDescriptorPool();
    auto descriptorSetLayout = VulkanHelper::getSingleton()._getDescriptorSetLayout();

    VkDescriptorSetAllocateInfo allocInfo =
        vks::initializers::descriptorSetAllocateInfo(
            descriptorPool,
            &descriptorSetLayout,
            1);

    if (vkAllocateDescriptorSets(mDevice, &allocInfo, &mDescriptorSet) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate descriptor set!");
    }
}

