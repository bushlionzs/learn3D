#pragma once
#include "model_loader.h"

//bin is a format of The-forge engine
class  BinLoader : public ModelLoader
{
public:
    BinLoader();
    ~BinLoader();

    std::shared_ptr<Ogre::Mesh> loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream);
};