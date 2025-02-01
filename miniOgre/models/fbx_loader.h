#pragma once
#include "model_loader.h"

class  FbxLoader : public ModelLoader
{
public:
    FbxLoader();
    ~FbxLoader();

    virtual bool loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh) override;
};