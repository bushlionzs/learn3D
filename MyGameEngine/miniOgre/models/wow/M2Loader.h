#pragma once
#include "M2Header.h"
#include "model_loader.h"
#include "m2Bone.h"
namespace Ogre 
{
	class DataStream;
}

class M2Loader: public ModelLoader
{
public:
	M2Loader();
	~M2Loader();
	virtual std::shared_ptr<Ogre::Mesh> loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream);
private:
	void initCommon(Ogre::DataStream* stream);
	void initAnimated(Ogre::DataStream* stream);
	bool isAnimated(Ogre::DataStream* stream);
	void setLOD(Ogre::DataStream* stream, int index);

	bool hasAnimation(size_t animIdx) const;
	Ogre::Vector3 getBoneParentTrans(int n) const;
private:
	std::string mName;
	M2Header mHeader;
	int gameVersion = VERSION_WOTLK;
	M2ModelVertex* mOrigVertices;

	ModelType mModelType = MT_NORMAL;

	uint32_t nIndices = 0;

	std::vector<uint16_t> indices;

	std::vector<bool> showGeosets;

	std::vector<uint32_t> texturetypes;
	std::vector<std::string> texnames;

	Ogre::Mesh* mMesh = nullptr;

	bool animGeometry, animTextures, animBones;
	bool animated;
	bool ind;
	std::vector<ModelAnimation> mAnimations;

	std::vector<std::string> mAnimNamefiles;

	int16 keyBoneLookup[BONE_MAX];

	std::vector<uint32_t> globalSequences;

	std::vector<M2Bone> bones;
	Skeleton* mSkeleton = nullptr;
};