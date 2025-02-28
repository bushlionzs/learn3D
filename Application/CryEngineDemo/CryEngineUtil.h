#pragma once

void createCryEngineMesh(const std::string& meshName);

void addCryEngineMaterial(const std::string& matName, const std::string& matFileName);


struct CryEngineContext
{
    Ogre::SceneManager* sceneManager;
    std::string levelName;
    std::string projectName = "D:/CryEngine/ThirdPerson/Game.cryproject";
};

void loadCryEngineLevel(struct CryEngineContext& context);

