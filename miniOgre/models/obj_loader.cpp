#include "OgreHeader.h"
#include "obj_loader.h"
#include "OgreMesh.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "shader.h"
#include "OgreMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string_util.h>
#include <path_utils.h>

ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}

struct ObjVertex
{
    Ogre::Vector3 Pos;
    Ogre::Vector3 Normal;
    Ogre::Vector3 tangent;
    Ogre::Vector3 bitangent;
    Ogre::Vector2 TexC;
};

Ogre::Vector3 calPosition(std::vector<ObjVertex>& vertexList)
{
    Ogre::Vector3 center = Ogre::Vector3::ZERO;

    for (auto& vertex : vertexList)
    {
        center += vertex.Pos;
    }

    center /= vertexList.size();

    Ogre::Vector3 translate = -center;
    for (auto& vertex : vertexList)
    {
        vertex.Pos += translate;
    }

    return center;
}

bool ObjLoader::loadMeshFromFile(
    std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh)
{
    Assimp::Importer importer;
    uint32_t flags = aiProcessPreset_TargetRealtime_Fast | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder;
  

    const std::string& name = stream->getName();
    const aiScene* scene = importer.ReadFile(name, flags);

    assert_invariant(scene != nullptr);
    aiMaterial** sourceMaterials = scene->mMaterials;

    std::vector<Ogre::MaterialPtr> mats;
    mats.reserve(scene->mNumMaterials);
    if (scene->HasMaterials())
    {
        aiString name;
        Ogre::TextureProperty tp;
        for (uint32_t i = 0; i < scene->mNumMaterials; i++)
        {
            aiMaterial* sourceMat = sourceMaterials[i];

            
            aiString name;
            sourceMat->Get(AI_MATKEY_NAME, name);

            std::string matName = name.C_Str();
            std::shared_ptr<Ogre::Material> mat = std::make_shared<Ogre::Material>(matName, true);
            mats.push_back(mat);

            aiColor3D color;
            if (AI_SUCCESS == sourceMat->Get(AI_MATKEY_COLOR_DIFFUSE, color))
            {
                mat->setDiffuseColor(Ogre::Vector3(color.r, color.g, color.b));
            }


            if (AI_SUCCESS == sourceMat->Get(AI_MATKEY_COLOR_SPECULAR, color))
            {
                mat->setSpecularColor(Ogre::Vector3(color.r, color.g, color.b));
            }

            if (AI_SUCCESS == sourceMat->Get(AI_MATKEY_COLOR_EMISSIVE, color))
            {
                mat->setEmissiveColor(Ogre::Vector3(color.r, color.g, color.b));
            }
            float val;
            if (AI_SUCCESS == sourceMat->Get(AI_MATKEY_SHININESS, val))
            {
                mat->setShininess(val);
            }

            if (AI_SUCCESS == sourceMat->Get(AI_MATKEY_OPACITY, val))
            {
                mat->setOpacity(val);
            }

            ShaderInfo shaderInfo;
            shaderInfo.shaderName = "basic";
            mat->addShader(shaderInfo);
            struct TexResource
            {
                aiTextureType textureType;
                const char* textureTypeName;
                TextureTypePbr pbrType;
            };

            std::vector<TexResource> texResources =
            {
                {
                    aiTextureType_DIFFUSE,
                    DIFFUSE_TEXTURE,
                    TextureTypePbr_Diffuse
                },
                {
                    aiTextureType_HEIGHT,
                    NORMAL_TEXTURE,
                    TextureTypePbr_NormalMap
                },
                {
                    aiTextureType_SPECULAR,
                    SPECULAR_TEXTURE,
                    TextureTypePbr_Specular
                },
                {
                    aiTextureType_EMISSIVE,
                    EMISSIVE_TEXTURE,
                    TextureTypePbr_Emissive
                },
                {
                    aiTextureType_OPACITY,
                    OPACITY_TEXTURE,
                    TextureTypePbr_Opacity
                },
            };

            for (uint32_t j = 0; j < 5; j++)
            {
                TexResource& texResource = texResources[j];
                uint32_t textureCount = sourceMat->GetTextureCount(texResource.textureType);
                if (textureCount > 0)
                {
                    if (textureCount > 1)
                    {
                        assert_invariant(false);
                    }
                    aiReturn ret = sourceMat->GetTexture(texResource.textureType, (unsigned int)0, &name);
                    assert(ret == aiReturn_SUCCESS);
                    std::string shortname = CommonUtils::getShortFilename(name.C_Str());
                    tp.textureTypeName = texResource.textureTypeName;
                    tp._pbrType = texResource.pbrType;
                    if (tp._pbrType == TextureTypePbr_Diffuse)
                    {
                        tp._samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
                        tp._samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
                        tp._samplerParams.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
                        tp._samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
                        tp._samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
                        tp._samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
                        tp._samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
                        tp._samplerParams.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_NEVER;
                        tp._samplerParams.anisotropyLog2 = 4;
                        tp._samplerParams.useComparison = 0;
                        tp._samplerParams.maxLod = 1000;
                        tp._samplerParams.padding2 = 0;
                    }
                    mat->addTexture(shortname, &tp);
                }
            }
            
        }
    }

    
    if (scene->HasMeshes())
    {
        scene->mRootNode;
        const aiMatrix4x4& transform = scene->mRootNode->mTransformation;
        aiVector3t<float> scale;
        aiVector3t<float> pos;
        aiQuaterniont<float> rotation;
        transform.Decompose(scale, rotation, pos);

        Ogre::Vector3 mPosition(pos.x, pos.y, pos.z);
        Ogre::Vector3 mScale(scale.x, scale.y, scale.z);
        Ogre::Quaternion mQuat(rotation.w, rotation.x, rotation.y, rotation.z);
        for (uint32_t i = 0; i < scene->mNumMeshes; i++)
        {
            
            aiMesh* sourceMesh = scene->mMeshes[i];
            SubMesh* subMesh = mesh->addSubMesh(false, false);
            
            subMesh->setScale(mScale);
            subMesh->setRotate(mQuat);
            uint32_t numVertices = sourceMesh->mNumVertices;

            std::vector<ObjVertex> vertexList;
            vertexList.resize(numVertices);

            aiVector3D* sourceVertices = sourceMesh->mVertices;
            aiVector3D* sourceNormals = sourceMesh->mNormals;
            aiVector3D* sourceTexcoords = sourceMesh->mTextureCoords[0];
            aiColor4D* sourceColors = sourceMesh->mColors[0];
            aiVector3D* tangents = sourceMesh->mTangents;
            aiVector3D* bitangents = sourceMesh->mBitangents;
            for (uint32_t index = 0; index < numVertices; index++)
            {
                ObjVertex& vertex = vertexList.at(index);
             
                vertex.Pos.x = sourceVertices[index].x;
                vertex.Pos.y = sourceVertices[index].y; 
                vertex.Pos.z = sourceVertices[index].z;

      

                vertex.Normal.x = sourceNormals[index].x;
                vertex.Normal.y = sourceNormals[index].y; 
                vertex.Normal.z = sourceNormals[index].z;

                vertex.TexC.x = sourceTexcoords[index].x;
                vertex.TexC.y = 1 - sourceTexcoords[index].y;

                vertex.tangent = { tangents[index].x, tangents[index].y, tangents[index].z };

                vertex.bitangent = { bitangents[index].x, bitangents[index].y, bitangents[index].z };
            }

            //update verteices
            VertexData* vertexData = subMesh->getVertexData();
            
            vertexData->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
            vertexData->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
            vertexData->addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
            vertexData->addElement(0, 0, 36, VET_FLOAT3, VES_BINORMAL);
            vertexData->addElement(0, 0, 48, VET_FLOAT2, VES_TEXTURE_COORDINATES);

            vertexData->createBindBuffer(0, sizeof(ObjVertex), numVertices);
            if (false)
            {
                Ogre::Vector3 center = calPosition(vertexList);
                center += mPosition;
                subMesh->setPosition(center);
            }
            
            vertexData->writeBindBufferData(0, (const  char*)vertexList.data(), sizeof(ObjVertex) * numVertices);
            //update index
            std::vector<uint32_t> indexs;
            
            uint32_t faces = sourceMesh->mNumFaces;
            indexs.reserve(faces * 3);
            for (uint32_t face = 0; face < faces; face++)
            {
                aiFace& sourceFace = sourceMesh->mFaces[face];

                for (uint32_t j = 0; j < sourceFace.mNumIndices; j++)
                {
                    indexs.push_back(sourceFace.mIndices[j]);
                }

                if (sourceFace.mNumIndices != 3)
                {
                    assert_invariant(false);
                }
            }

            IndexData* indexData = subMesh->getIndexData();
            indexData->createBuffer(4, indexs.size());
            indexData->writeData((const char*)indexs.data(), 4 * indexs.size());

          

            subMesh->addIndexs(indexs.size(), 0, 0);
            //update material
            

            subMesh->setMaterial(mats[sourceMesh->mMaterialIndex]);
          
        }
    }

    return true;
}