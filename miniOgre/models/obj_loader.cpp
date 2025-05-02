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

bool ObjLoader::loadMeshFromFile(
    std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh)
{
    Assimp::Importer importer;
    uint32_t flags = aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipWindingOrder;
  

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
            std::shared_ptr<Ogre::Material> mat = std::make_shared<Ogre::Material>(matName, false);
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
            };

            std::vector<TexResource> texResources =
            {
                {
                    aiTextureType_DIFFUSE,
                    DIFFUSE_TEXTURE
                },
                {
                    aiTextureType_HEIGHT,
                    NORMAL_TEXTURE
                },
                {
                    aiTextureType_SPECULAR,
                    SPECULAR_TEXTURE
                },
                {
                    aiTextureType_EMISSIVE,
                    EMISSIVE_TEXTURE
                },
                {
                    aiTextureType_OPACITY,
                    OPACITY_TEXTURE
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
                    mat->addTexture(shortname, &tp);
                }
            }
            
        }
    }

    
    if (scene->HasMeshes())
    {
        for (uint32_t i = 0; i < scene->mNumMeshes; i++)
        {
            
            aiMesh* sourceMesh = scene->mMeshes[i];
            SubMesh* subMesh = mesh->addSubMesh(false, false);

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
                vertex.TexC.y = sourceTexcoords[index].y;

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

            vertexData->addBindBuffer(0, sizeof(ObjVertex), numVertices);

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