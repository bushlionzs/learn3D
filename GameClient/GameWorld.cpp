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
#include "GameMouseCursor.h"
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
	

	if (KRR_SUCCEED != GetActionSetData()->Initialize("ActionSet/"))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to load action table");
		return false;
	}
	g_nProcess = 9;
	


	mGameCamera->setDistance(1200.0f);
	mGameCamera->setHeight(200.0f);

	InputManager::getSingleton().addListener(this);

	

	NOTICE_LOG("load world successfully.")
	return true;
}

void GameWorld::update(float delta)
{
	KObjectManager::GetSingleton().update(delta);
}

void GameWorld::injectMouseWheel(int _absz)
{
   
}

void GameWorld::injectMouseCursor()
{
	CGameMouseCursor::GetSingleton().OnCursor();
}

void GameWorld::injectMouseMove(int _absx, int _absy, int _absz)
{
	KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
	if (nullptr == pPlayer)
	{
		return;
	}
	/*_absx = 166;
	_absy = 351;*/
	Ogre::Vector3 fvMouseHitPlan;
	KObject* pSelectObj = (KObject*)KObjectManager::GetSingleton().GetMouseOverObject(_absx, _absy, fvMouseHitPlan);

	if (pSelectObj != mLastSelectObj)
	{
		if (pSelectObj == nullptr)
		{
			CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Normal);
		}
		else
		{
			CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Speak);
		}

		mLastSelectObj = pSelectObj;
	}
}

void GameWorld::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (CEGUIManager::getSingleton().isMouseInGUI())
	{
		return;
	}
	if (_id == OIS::MB_Left)
	{
		if (!mPlayer)
		{
			mPlayer = KObjectManager::GetSingleton().getMySelf();
		}

		if(mPlayer)
			mPlayer->injectMousePress(_absx, _absy, _id);
	}

	if (_id == OIS::MB_Right)
	{
		auto scene = GameSceneManager::getSingleton().GetActiveScene();

		std::vector<Orphigine::ActorPtr> objects;
		scene->getIntersectObject(_absx, _absy, objects);
		if (!objects.empty())
		{
			int kk = 0;
		}
	}
}

void GameWorld::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{

}

void GameWorld::injectKeyPress(KeyCode _key, uint32_t _text)
{
	mPlayer->input(_key);

	GameInput::GetSingleton().input(_key);
}

void GameWorld::injectKeyRelease(KeyCode _key)
{
    
}