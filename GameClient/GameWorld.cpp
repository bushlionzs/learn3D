#include "stdafx.h"
#include "GameWorld.h"
#include "game_scene_manager.h"
#include "engine_manager.h"
#include "game_camera.h"
#include "InputManager.h"
#include "GameTableManager.h"
#include "ActionSetManager.h"
#include "kplayer.h"
#include "game_scene.h"
#include "KObjectManager.h"
#include "KItemManager.h"
#include "GameInput.h"
#include "UIManager.h"
#include "data/GameDataManager.h"
#include "DirectlyEffectMgr.h"
#include "KTable.h"
#include <CEGUIManager.h>

GameWorld::GameWorld(GameCamera* gameCamera)
{
	mGameCamera = gameCamera;
	mPlayer = nullptr;
	new KObjectManager;
	new KItemManager;
	new GameInput;
	new UIManager;
	new GameDataManager;
}

GameWorld::~GameWorld()
{

}

bool GameWorld::gameWorldInit()
{
	NOTICE_LOG("begin to load world.")
	
	new CDBActionSet;

	if (!GAME_TABLE_MANAGER_PTR)
	{
		new CGameTableManager;
		if (KRR_SUCCEED != GAME_TABLE_MANAGER_PTR->Initialize())
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to load game table");
			return false;
		}
	}
	
	GameDataManager::GetSingleton().Initialize();

	if (KRR_SUCCEED != GetActionSetData()->Initialize("ActionSet/"))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to load action table");
		return false;
	}
	g_nProcess = 9;
	


	mGameCamera->setDistance(1200.0f);
	mGameCamera->setHeight(200.0f);

	mGameInput = new GameInput;

	mGameInput->init();
	

	NOTICE_LOG("load world successfully.")
	return true;
}

void GameWorld::update(float delta)
{
	KObjectManager::GetSingleton().update(delta);
}
