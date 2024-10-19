#include "OgreHeader.h"
#include "OgreRenderable.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include <OgreCamera.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreMaterial.h>
#include "OgreTextureUnit.h"

namespace Ogre {
    Renderable::Renderable()
    {
        mModel = Ogre::Matrix4::IDENTITY;

        mSortValue = 1000000;
    }

    Renderable::~Renderable()
    {
    }

    void Renderable::setMaterial(std::shared_ptr<Material> mat)
    {
        mMaterial = mat;

        VertexData* vd = getVertexData();
        VertexDeclaration* decl = vd->getVertexDeclaration();
        mMaterial->updateVertexDeclaration(decl);
    }

    uint64_t Renderable::getSortValue()
    {
        return 0;
    }

    const Ogre::Matrix4& Renderable::getModelMatrix()
    {
        return mModel;
    }

    Ogre::Vector3 getPosition()
    {
        return Ogre::Vector3(0.0f, 0.0f, 0.0f);
    }

    Ogre::OperationType Renderable::getPrimitiveTopology()
    {
        return OT_TRIANGLE_LIST;
    }

    void Renderable::createFrameResource()
    {
        auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
        mFrameResourceInfoList.resize(ogreConfig.swapBufferCount);
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        Material* mat = mMaterial.get();
        for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
        {
            FrameResourceInfo* resourceInfo = &mFrameResourceInfoList[i];
            Handle<HwBufferObject> objectBufferHandle =
                rs->createBufferObject(BufferObjectBinding::BufferObjectBinding_Uniform, BufferUsage::DYNAMIC,
                    sizeof(ObjectConstantBuffer));
            resourceInfo->modelObjectHandle = objectBufferHandle;

            Handle<HwBufferObject> matBufferHandle;
            if (mat->isPbr())
            {
                matBufferHandle =
                    rs->createBufferObject(BufferObjectBinding::BufferObjectBinding_Uniform, BufferUsage::DYNAMIC,
                        sizeof(PbrMaterialConstanceBuffer));
            }
            else
            {
                matBufferHandle =
                    rs->createBufferObject(BufferObjectBinding::BufferObjectBinding_Uniform,
                        BufferUsage::DYNAMIC, sizeof(GeneralMaterialConstantBuffer));
            }

            resourceInfo->matObjectHandle = matBufferHandle;

            Handle<HwProgram> programHandle = mat->getProgram();
            auto zeroLayoutHandle = rs->getDescriptorSetLayout(programHandle, 0);
            auto firstLayoutHandle = rs->getDescriptorSetLayout(programHandle, 1);
            resourceInfo->zeroShadowSet = rs->createDescriptorSet(zeroLayoutHandle);
            resourceInfo->zeroSet = rs->createDescriptorSet(zeroLayoutHandle);
            resourceInfo->firstSet = rs->createDescriptorSet(firstLayoutHandle);

            rs->updateDescriptorSetBuffer(resourceInfo->zeroSet, 0, &objectBufferHandle, 1);
            rs->updateDescriptorSetBuffer(resourceInfo->zeroSet, 2, &matBufferHandle, 1);

            rs->updateDescriptorSetBuffer(resourceInfo->zeroShadowSet, 0, &objectBufferHandle, 1);

            RawData* rawData = getSkinnedData();
            if (rawData)
            {
                resourceInfo->skinObjectHandle =
                    rs->createBufferObject(
                        BufferObjectBinding::BufferObjectBinding_Uniform,
                        BufferUsage::DYNAMIC,
                        sizeof(SkinnedConstantBuffer));

                rs->updateDescriptorSetBuffer(resourceInfo->zeroSet, 3,
                    &resourceInfo->skinObjectHandle, 1);

                rs->updateDescriptorSetBuffer(resourceInfo->zeroSet, 3,
                    &resourceInfo->skinObjectHandle, 1);
            }


            //update texture
            uint32_t index = 0;

            auto& texs = mat->getAllTexureUnit();

            if (mat->isPbr())
            {
                for (int32_t i = 0; i < texs.size(); i++)
                {
                    int32_t texIndex = -1;
                    switch (texs[i]->getTextureProperty()->_pbrType)
                    {
                    case TextureTypePbr_Albedo:
                        texIndex = 0;
                        break;
                    case TextureTypePbr_MetalRoughness:
                        texIndex = 4;
                        break;
                    case TextureTypePbr_NormalMap:
                        texIndex = 2;
                        break;
                    case TextureTypePbr_Emissive:
                        texIndex = 3;
                        break;
                    case TextureTypePbr_AmbientOcclusion:
                        texIndex = 1;
                        break;
                    }

                    assert(texIndex >= 0);
                    OgreTexture* tex = texs[i]->getRaw();
                    rs->updateDescriptorSetTexture(
                        resourceInfo->firstSet, texIndex, &tex, 1, false);
                }
            }
            else
            {
                for (int32_t i = 0; i < texs.size(); i++)
                {
                    if (texs[i]->getTextureProperty()->_texType == TEX_TYPE_CUBE_MAP)
                        continue;
                    OgreTexture* tex = texs[i]->getRaw();

                    rs->updateDescriptorSetTexture(
                        resourceInfo->firstSet, index, &tex, 1, false);
                    index++;
                }

                index = 4;
                for (int32_t i = 0; i < texs.size(); i++)
                {
                    if (texs[i]->getTextureProperty()->_texType != TEX_TYPE_CUBE_MAP)
                        continue;
                    OgreTexture* tex = texs[i]->getRaw();

                    rs->updateDescriptorSetTexture(
                        resourceInfo->firstSet, index, &tex, 1, false);
                }
            }
        }
    }

    void Renderable::updateFrameResource(uint32_t frameIndex)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        Material* mat = mMaterial.get();

        FrameResourceInfo& resourceInfo = mFrameResourceInfoList[frameIndex];

        static ObjectConstantBuffer objectBuffer;
        objectBuffer.world = mModel.transpose();
        rs->updateBufferObject(resourceInfo.modelObjectHandle,
            (const char*)&objectBuffer, sizeof(objectBuffer));

        if (mat->isPbr())
        {
            auto& matBuffer = mat->getPbrMatInfo();
            rs->updateBufferObject(resourceInfo.matObjectHandle,
                (const char*)&matBuffer, sizeof(matBuffer));
        }
        else
        {
            auto& matBuffer = mat->getMatInfo();
            rs->updateBufferObject(resourceInfo.matObjectHandle,
                (const char*)&matBuffer, sizeof(matBuffer));
        }

    }

    FrameResourceInfo* Renderable::getFrameResourceInfo(uint32_t frameIndex)
    {
        return &mFrameResourceInfoList[frameIndex];
    }
}