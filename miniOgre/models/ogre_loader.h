#pragma once
#include "model_loader.h"
class OgreMeshSerializerImpl;

class  OgreMeshVersionData
{
public:
    std::string mVersion;
    OgreMeshSerializerImpl* impl;

    OgreMeshVersionData(const std::string& version, OgreMeshSerializerImpl* _impl)
        : mVersion(version), impl(_impl) {}

    ~OgreMeshVersionData() {}

};

class OgreMeshLoader : public ModelLoader
{
    const unsigned short HEADER_CHUNK_ID = 0x1000;
public:
    OgreMeshLoader();
	~OgreMeshLoader();

	virtual std::shared_ptr<Ogre::Mesh> loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream);
private:
    std::vector<OgreMeshVersionData*> mVersionData;
};
