#pragma once
#include "model_loader.h"

class  ObjLoader : public ModelLoader
{
public:
    ObjLoader();
    ~ObjLoader();

    virtual bool loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh) override;
};