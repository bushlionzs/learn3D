#include "OgreHeader.h"
#include "game_scene_manager.h"
#include "terrain_info.h"
#include "terrain_serializer.h"
#include "game_scene.h"
#include "GameTableManager.h"
#include "GameTableData.h"
#include "GameTableDefine.h"
#include "KTable.h"

template<> GameSceneManager* Ogre::Singleton<GameSceneManager>::msSingleton = 0;

GameSceneManager::GameSceneManager()
{

}

GameSceneManager::~GameSceneManager()
{

}

bool GameSceneManager::loadScene(int32_t sceneId)
{
	if (mSceneMap.count(sceneId))
	{
		return true;
	}

	const CGameTable* pSceneTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_SCENE_DEFINE);

	const _TABLE_SCENE_DEFINE* pSceneDef = 
		(const _TABLE_SCENE_DEFINE*)pSceneTable->GetFieldDataByFirstColumn(_TABLE_SCENE_DEFINE::SCENE_SERVER_ID_COLUMN, (table_int_t)sceneId);
	GameScene* scene = new GameScene(pSceneDef);
	mSceneMap[sceneId] = scene;

	scene->load();

	mActiveScene = scene;
	return true;
}

GameScene* GameSceneManager::GetActiveScene()
{
	return mActiveScene;
}