#pragma once

#include "model_loader.h"
#include <DirectXMath.h>
class AnimationTrack;


class M3dLoader: public ModelLoader
{
public:
    struct M3dVertex
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT3 Normal;
        DirectX::XMFLOAT2 TexC;
    };
    struct M3dSkinnedVertex
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT3 Normal;
       // DirectX::XMFLOAT3 TangentU;
        DirectX::XMFLOAT2 TexC;
        DirectX::XMFLOAT3 BoneWeights;
        uint32_t BoneIndices[4];
    };

    struct M3dSubset
    {
        UINT Id = -1;
        UINT VertexStart = 0;
        UINT VertexCount = 0;
        UINT FaceStart = 0;
        UINT FaceCount = 0;
    };

    struct M3dMaterial
    {
        std::string Name;

        Ogre::Vector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
        Ogre::Vector3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
        float Roughness = 0.8f;
        bool AlphaClip = false;

        std::string MaterialTypeName;
        std::string DiffuseMapName;
        std::string NormalMapName;
    };
public:
	M3dLoader();
	~M3dLoader();

    virtual std::shared_ptr<Ogre::Mesh> loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream);
	std::shared_ptr<Ogre::Mesh> loadM3dFromMemory(const char* data, uint32_t size);

private:
private:
	void ReadMaterials(
        std::stringstream& fin,
        uint32_t numMaterials, 
        std::vector<M3dMaterial>& mats);
	void ReadSubsetTable(
        std::stringstream& fin,
        uint32_t numSubsets, 
        std::vector<M3dSubset>& subsets);

	void ReadSkinnedVertices(
        std::stringstream& fin,
        uint32_t numVertices, 
        std::vector<M3dSkinnedVertex>& vertices);
	void ReadTriangles(
        std::stringstream& fin,
        uint32_t numTriangles, 
        std::vector<uint32_t>& indices);
	void ReadBoneOffsets(
        std::stringstream& fin,
        uint32_t numBones, 
        std::vector<DirectX::XMFLOAT4X4>& boneOffsets
    );
	void ReadBoneHierarchy(
        std::stringstream& fin,
        uint32_t numBones, 
        std::vector<int>& boneIndexToParentIndex);
	void ReadAnimationClips(
        std::stringstream& fin,
        uint32_t numBones,
        uint32_t numAnimationClips,
        Ogre::Skeleton* skeleton);
	void ReadBoneKeyframes(
        std::stringstream& fin,
        uint32_t numBones,
        AnimationTrack* track);
};