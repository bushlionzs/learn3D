#pragma once

void createCryEngineMesh(const std::string& meshName);

void addCryEngineMaterial(const std::string& matName, const std::string& matFileName);

struct IStatObj;
struct IMaterial;
class GameCamera;
struct CryEngineContext
{
    Ogre::SceneManager* sceneManager;
    GameCamera* gameCamera;
    Ogre::SceneNode* root;
    std::string levelName;
    std::string projectName = "D:/CryEngine/Breeze/Breeze.cryproject";
    std::string terrainName;

    std::vector<IStatObj*>* pStatObjTable;
    std::vector<IMaterial*>* pMatTable;
};

void loadCryEngineLevel(CryEngineContext& context);

void updateCryEngineLevel(CryEngineContext& context);

