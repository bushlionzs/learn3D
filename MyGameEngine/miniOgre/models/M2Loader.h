#pragma once
#include "M2Header.h"
#include "model_loader.h"
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

	std::vector<uint16_t> indices;

	std::vector<bool> showGeosets;

	std::vector<uint32_t> texturetypes;
	std::vector<std::string> texnames;

	Ogre::Mesh* pMesh;
};