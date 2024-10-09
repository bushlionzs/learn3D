#include "OgreHeader.h"
#include "m3d_loader.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreSkeleton.h"
#include "OgreAnimation.h"
#include "OgreBone.h"
#include "animation_track.h"
#include "keyframe.h"
#include "OgreMaterialManager.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreMatrix4.h"
#include "OgreHardwareBufferManager.h"
#include "OgreDataStream.h"

class AnimationClip;

M3dLoader::M3dLoader()
{

}

M3dLoader::~M3dLoader()
{

}


std::shared_ptr<Mesh> M3dLoader::loadMeshFromFile(std::shared_ptr<DataStream>& stream)
{
	uint32_t size = stream->getStreamLength();

	std::string content;
	content.resize(size);

	char* data = (char*)content.c_str();
	stream->read(data, size);

	std::stringstream fin(content);

	UINT numMaterials = 0;
	UINT numVertices = 0;
	UINT numTriangles = 0;
	UINT numBones = 0;
	UINT numAnimationClips = 0;

	std::string ignore;

	
	fin >> ignore; // file header text
	fin >> ignore >> numMaterials;
	fin >> ignore >> numVertices;
	fin >> ignore >> numTriangles;
	fin >> ignore >> numBones;
	fin >> ignore >> numAnimationClips;

	std::vector<M3dMaterial> mats;
	std::vector<M3dSubset> subsets;
	std::vector<uint32_t> indices;
	std::vector<M3dSkinnedVertex> vertices_;

	std::vector<DirectX::XMFLOAT4X4> boneOffsets;
	std::vector<int> boneIndexToParentIndex;

	std::shared_ptr<Skeleton> skeleton = std::make_shared<Skeleton>(stream->getName());
	std::unordered_map<std::string, AnimationClip*> animations;

	ReadMaterials(fin, numMaterials, mats);
	ReadSubsetTable(fin, numMaterials, subsets);
	ReadSkinnedVertices(fin, numVertices, vertices_);
	ReadTriangles(fin, numTriangles, indices);
	ReadBoneOffsets(fin, numBones, boneOffsets);
	ReadBoneHierarchy(fin, numBones, boneIndexToParentIndex);
	ReadAnimationClips(fin, numBones, numAnimationClips, skeleton.get());
	

	std::vector<M3dVertex> vertices(numVertices);


	bool use_assign = true;

	Mesh* pMesh = new Mesh(stream->getName());

	if (use_assign)
	{
		for (int32_t i = 0; i < numVertices; i++)
		{
			vertices[i].Pos = vertices_[i].Pos;
			vertices[i].Normal = vertices_[i].Normal;
			vertices[i].TexC = vertices_[i].TexC;
		}

		VertexBoneAssignment assign;
		for (int32_t i = 0; i < numVertices; i++)
		{
			assign.vertexIndex = i;
			assign.boneIndex = vertices_[i].BoneIndices[0];
			assign.weight = vertices_[i].BoneWeights.x;
			pMesh->addBoneAssignment(assign);

			assign.boneIndex = vertices_[i].BoneIndices[1];
			assign.weight = vertices_[i].BoneWeights.y;
			pMesh->addBoneAssignment(assign);

			assign.boneIndex = vertices_[i].BoneIndices[2];
			assign.weight = vertices_[i].BoneWeights.z;
			pMesh->addBoneAssignment(assign);

			assign.boneIndex = vertices_[i].BoneIndices[3];
			assign.weight = 0;
			pMesh->addBoneAssignment(assign);
		}
	}
	

	pMesh->applySkeleton(skeleton);

	VertexData* vd = pMesh->getVertexData();
	vd->setVertexCount(vertices.size());

	auto vertexSize = 0;
	if (use_assign)
	{
		vertexSize = sizeof(M3dVertex);
	}
	else
	{
		vertexSize = sizeof(M3dSkinnedVertex);
	}

	vd->addBindBuffer(0, vertexSize, vertices_.size());
	vd->writeBindBufferData(0, (const char*)vertices_.data(), vertices_.size() * vertexSize);
	
	

	IndexData* indexData = pMesh->getIndexData();
	indexData->createBuffer(4, indices.size());
	indexData->writeData((const char*)indices.data(), 4 * indices.size());



	if (use_assign)
	{
		vd->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
		vd->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
		//declaration->addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
		vd->addElement(0, 0, 24, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	}
	else
	{
		vd->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
		vd->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
		//declaration->addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
		vd->addElement(0, 0, 24, VET_FLOAT2, VES_TEXTURE_COORDINATES);


		vd->addElement(0, 0, 32, VET_FLOAT3, VES_BLEND_WEIGHTS);
		vd->addElement(0, 0, 44, VET_UINT4, VES_BLEND_INDICES);
	}
	

	ShaderInfo si;
	for (auto& mat : mats)
	{
		std::shared_ptr<Material> m = MaterialManager::getSingletonPtr()->create(mat.Name);
		m->addTexture(mat.DiffuseMapName);
		m->setFresnelR0(mat.FresnelR0);
		m->setRoughness(mat.Roughness);
		m->setDiffuseAlbedo(mat.DiffuseAlbedo);
		si.shaderName = "basic";
		si.shaderMacros.push_back(std::pair<std::string,std::string>("SKINNED","1"));
		m->addShader(si);
	}

	for (int32_t i = 0; i < subsets.size(); i++)
	{
		SubMesh* sub = pMesh->addSubMesh(true, true);

		std::shared_ptr<Material> m = MaterialManager::getSingletonPtr()->getByName(mats[i].Name);
		sub->setMaterial(m);
		sub->addIndexs(subsets[i].FaceCount * 3, subsets[i].FaceStart * 3, 0);
	}

	std::string bonename;
	DirectX::XMMATRIX matrix;

	

	for (int32_t i = 0; i < numBones; i++)
	{
		bonename = "Bone" + std::to_string(i);
		skeleton->createBone(bonename, i);
	}

	for (int32_t i = 0; i < numBones; i++)
	{
		Bone* parent = skeleton->getBone(boneIndexToParentIndex[i]);
		if (parent)
		{
			Bone* bone = skeleton->getBone(i);
			bone->updateParent(parent);
		}
	}

	Ogre::Vector3 scale, translate;
	Ogre::Quaternion rotate;
	for (int32_t i = 0; i < numBones; i++)
	{
		Bone* bone = skeleton->getBone(i);
		matrix = DirectX::XMLoadFloat4x4(&boneOffsets[i]);
		
		Bone* parent = bone->getParent();

		Ogre::Matrix4 m(&boneOffsets[i].m[0][0]);

		m = m.transpose();
		m.decomposition(translate, scale, rotate);

		if (!parent)
		{
			/*bone->setPosition(translate);
			bone->setOrientation(rotate);
			bone->setScale(scale);*/
		}
		else
		{
			/*Ogre::Vector3 localTranslate = parent->convertWorldToLocalPosition(translate);
			Ogre::Quaternion localRotate = parent->convertWorldToLocalOrientation(rotate);
			Ogre::Vector3 localScale = parent->_getDerivedScale() / scale;


			bone->setPosition(localTranslate);
			bone->setOrientation(localRotate);
			bone->setScale(localScale);*/

			bone->setPosition(translate);
			bone->setOrientation(rotate);
			bone->setScale(scale);
		}
		
		

		bone->setInverseBindMatrix(m);
	}

	int32_t boneCount = skeleton->getNumBones();
	Animation* ani = skeleton->getAnimation("Take1");
	for (int32_t i = 0; i < boneCount; i++)
	{
		AnimationTrack* track = ani->getAnimationTrack(i);

		int32_t frameCount = track->getNumKeyFrames();

		Bone* bone = skeleton->getBone(i);
		for (int32_t j = 0; j < frameCount; j++)
		{
			KeyFrame* frame = track->getNodeKeyFrame(j);

			frame->setRotation(bone->getQuaternion().Inverse() * frame->getRotationQuat());

			frame->setTranslate(bone->getPosition() - frame->getTranslation());
			frame->setScale(frame->getScale() / bone->getScale());
		}
	}

	skeleton->setBindingPose();
	return std::shared_ptr<Mesh>(pMesh);
}

std::shared_ptr<Mesh> M3dLoader::loadM3dFromMemory(const char* data, uint32_t size)
{
	return std::shared_ptr<Mesh>();
}

void M3dLoader::ReadMaterials(
	std::stringstream& fin,
	uint32_t numMaterials, 
	std::vector<M3dMaterial>& mats)
{
	std::string ignore;
	mats.resize(numMaterials);

	std::string diffuseMapName;
	std::string normalMapName;

	fin >> ignore; // materials header text
	for (UINT i = 0; i < numMaterials; ++i)
	{
		fin >> ignore >> mats[i].Name;
		fin >> ignore >> mats[i].DiffuseAlbedo.x >> mats[i].DiffuseAlbedo.y >> mats[i].DiffuseAlbedo.z;
		fin >> ignore >> mats[i].FresnelR0.x >> mats[i].FresnelR0.y >> mats[i].FresnelR0.z;
		fin >> ignore >> mats[i].Roughness;
		fin >> ignore >> mats[i].AlphaClip;
		fin >> ignore >> mats[i].MaterialTypeName;
		fin >> ignore >> mats[i].DiffuseMapName;
		fin >> ignore >> mats[i].NormalMapName;
	}
}

void M3dLoader::ReadSubsetTable(
	std::stringstream& fin,
	uint32_t numSubsets, 
	std::vector<M3dSubset>& subsets)
{
	std::string ignore;
	subsets.resize(numSubsets);

	fin >> ignore; // subset header text
	for (uint32_t i = 0; i < numSubsets; ++i)
	{
		fin >> ignore >> subsets[i].Id;
		fin >> ignore >> subsets[i].VertexStart;
		fin >> ignore >> subsets[i].VertexCount;
		fin >> ignore >> subsets[i].FaceStart;
		fin >> ignore >> subsets[i].FaceCount;
	}
}

void M3dLoader::ReadSkinnedVertices(
	std::stringstream& fin,
	uint32_t numVertices, 
	std::vector<M3dSkinnedVertex>& vertices)
{
	std::string ignore;
	vertices.resize(numVertices);

	fin >> ignore; // vertices header text
	int boneIndices[4];
	float weights[4];

	DirectX::XMFLOAT3 TangentU;
	for (uint32_t i = 0; i < numVertices; ++i)
	{
		float blah;
		fin >> ignore >> vertices[i].Pos.x >> vertices[i].Pos.y >> vertices[i].Pos.z;
		//fin >> ignore >> vertices[i].TangentU.x >> vertices[i].TangentU.y >> vertices[i].TangentU.z >> blah /*vertices[i].TangentU.w*/;
		fin >> ignore >> TangentU.x >> TangentU.y >> TangentU.z >> blah;
		fin >> ignore >> vertices[i].Normal.x >> vertices[i].Normal.y >> vertices[i].Normal.z;
		fin >> ignore >> vertices[i].TexC.x >> vertices[i].TexC.y;
		fin >> ignore >> weights[0] >> weights[1] >> weights[2] >> weights[3];
		fin >> ignore >> boneIndices[0] >> boneIndices[1] >> boneIndices[2] >> boneIndices[3];

		vertices[i].BoneWeights.x = weights[0];
		vertices[i].BoneWeights.y = weights[1];
		vertices[i].BoneWeights.z = weights[2];

		vertices[i].BoneIndices[0] = (BYTE)boneIndices[0];
		vertices[i].BoneIndices[1] = (BYTE)boneIndices[1];
		vertices[i].BoneIndices[2] = (BYTE)boneIndices[2];
		vertices[i].BoneIndices[3] = (BYTE)boneIndices[3];
	}
}

void M3dLoader::ReadTriangles(
	std::stringstream& fin,
	uint32_t numTriangles, 
	std::vector<uint32_t>& indices)
{
	std::string ignore;
	indices.resize(numTriangles * 3);

	fin >> ignore; // triangles header text
	for (UINT i = 0; i < numTriangles; ++i)
	{
		fin >> indices[i * 3 + 0] >> indices[i * 3 + 1] >> indices[i * 3 + 2];
	}
}

void M3dLoader::ReadBoneOffsets(
	std::stringstream& fin,
	uint32_t numBones, 
	std::vector<DirectX::XMFLOAT4X4>& boneOffsets)
{
	std::string ignore;
	boneOffsets.resize(numBones);

	fin >> ignore; // BoneOffsets header text
	for (uint32_t i = 0; i < numBones; ++i)
	{
		fin >> ignore >>
			boneOffsets[i](0, 0) >> boneOffsets[i](0, 1) >> boneOffsets[i](0, 2) >> boneOffsets[i](0, 3) >>
			boneOffsets[i](1, 0) >> boneOffsets[i](1, 1) >> boneOffsets[i](1, 2) >> boneOffsets[i](1, 3) >>
			boneOffsets[i](2, 0) >> boneOffsets[i](2, 1) >> boneOffsets[i](2, 2) >> boneOffsets[i](2, 3) >>
			boneOffsets[i](3, 0) >> boneOffsets[i](3, 1) >> boneOffsets[i](3, 2) >> boneOffsets[i](3, 3);
	}
}

void M3dLoader::ReadBoneHierarchy(
	std::stringstream& fin,
	uint32_t numBones, 
	std::vector<int>& boneIndexToParentIndex)
{
	std::string ignore;
	boneIndexToParentIndex.resize(numBones);

	fin >> ignore; // BoneHierarchy header text
	for (uint32_t i = 0; i < numBones; ++i)
	{
		fin >> ignore >> boneIndexToParentIndex[i];
	}
}

void M3dLoader::ReadAnimationClips(
	std::stringstream& fin,
	uint32_t numBones,
	uint32_t numAnimationClips,
	Skeleton* skeleton)
{
	std::string ignore;
	fin >> ignore; // AnimationClips header text
	for (UINT clipIndex = 0; clipIndex < numAnimationClips; ++clipIndex)
	{
		std::string clipName;
		fin >> ignore >> clipName;
		fin >> ignore; // {
		Animation* ani = skeleton->createAnimation(clipName, 0.0f);
	

		for (UINT boneIndex = 0; boneIndex < numBones; ++boneIndex)
		{
			AnimationTrack* track = ani->createNodeTrack(boneIndex, nullptr);
			ReadBoneKeyframes(fin, numBones, track);
		}
		fin >> ignore; // }
	}
}

void M3dLoader::ReadBoneKeyframes(
	std::stringstream& fin,
	uint32_t numBones,
	AnimationTrack* track)
{
	std::string ignore;
	UINT numKeyframes = 0;
	fin >> ignore >> ignore >> numKeyframes;
	fin >> ignore; // {

	for (UINT i = 0; i < numKeyframes; ++i)
	{
		Real t = 0.0f;
		DirectX::XMFLOAT3 p(0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT3 s(1.0f, 1.0f, 1.0f);
		DirectX::XMFLOAT4 q(0.0f, 0.0f, 0.0f, 1.0f);
		fin >> ignore >> t;
		fin >> ignore >> p.x >> p.y >> p.z;
		fin >> ignore >> s.x >> s.y >> s.z;
		fin >> ignore >> q.x >> q.y >> q.z >> q.w;

		KeyFrame* frame = track->createKeyFrame(t);
		frame->setTranslation(p);
		frame->setScale(s);
		frame->setRotation(q);
	}

	fin >> ignore; // }
}