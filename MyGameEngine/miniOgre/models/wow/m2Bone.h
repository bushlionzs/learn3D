#pragma once
#include "animated.h"
#include "M2Header.h"


class Model;


class M2Bone {
public:
	Animated<Ogre::Vector3> trans;
	//Animated<Quaternion> rot;
	Animated<Quaternion, PACK_QUATERNION, Quat16ToQuat32> rot;
	Animated<Ogre::Vector3> scale;

	Ogre::Vector3 pivot, transPivot;
	int16 parent;

	bool billboard;

	ModelBoneDef boneDef;

	bool calc;

	void initV3(DataStream* m2stream,
		ModelBoneDef* mb,
		std::vector<std::shared_ptr<DataStream>>& animfiles,
		std::vector<uint32_t>& globalSequences);
};

