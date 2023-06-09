#pragma once
#include "OgreSingleton.h"

class GameScene;

class GameSceneManager : public Ogre::Singleton<GameSceneManager>
{
public:
	GameSceneManager();
	~GameSceneManager();

	bool loadScene(int32_t sceneId);

	GameScene* GetActiveScene();
private:
	std::map<int32_t, GameScene*> mSceneMap;
	GameScene* mActiveScene;
};

