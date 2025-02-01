#pragma once
#include "model_loader.h"

//bin is a format of The-forge engine
class  BinLoader : public ModelLoader
{
public:
    BinLoader();
    ~BinLoader();

    virtual bool loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh)override;
};