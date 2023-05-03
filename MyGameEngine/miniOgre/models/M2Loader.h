#pragma once
#include "M2Header.h"
namespace Ogre 
{
	class DataStream;
}

class M2Loader
{
public:
	M2Loader(const std::string& name);
	~M2Loader();
	bool loadModel();
private:
	void initStatic(Ogre::DataStream* stream);
	void initCommon(Ogre::DataStream* stream);
	bool isAnimated(Ogre::DataStream* stream);
	void setLOD(Ogre::DataStream* stream, int index);
	Ogre::Vector3 fixCoordSystem(Ogre::Vector3& v)
	{
		return Ogre::Vector3(v.x, v.z, -v.y);
	}
private:
	std::string mName;
	M2Header mHeader;

	M2ModelVertex* mOrigVertices;

	ModelType mModelType = MT_NORMAL;

	uint32_t nIndices = 0;

	uint16_t* indices = nullptr;

	std::vector<bool> showGeosets;
};