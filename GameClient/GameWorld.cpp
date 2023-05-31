#include "OgreHeader.h"
#include "GameWorld.h"
#include "game_scene_manager.h"
#include "engine_manager.h"
#include "game_camera.h"
#include "InputManager.h"
#include "GameTableManager.h"
#include "ActionSetManager.h"
#include "kplayer.h"
#include "game_scene.h"

GameWorld::GameWorld(GameCamera* gameCamera)
{
	mGameCamera = gameCamera;
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
	mPlayer = new KPlayer();
	mPlayer->setRaceId(1);

	GameSceneManager::getSingletonPtr()->loadScene(87);


	mGameCamera->setDistance(1200.0f);
	mGameCamera->setHeight(200.0f);

	

	
	Ogre::Vector3 mPosition;
	mPosition.x = 174;
	mPosition.y = 0;
	mPosition.z = 47;


	mPlayer->setPosition(mPosition);

	InputManager::getSingleton().addListener(this);


	NOTICE_LOG("load world successfully.")
	return true;
}

void GameWorld::update(float delta)
{
	mPlayer->update(delta);
}

void GameWorld::injectMouseWheel(int _absz)
{
   
}
void GameWorld::injectMouseMove(int _absx, int _absy, int _absz)
{
    
}

void GameWorld::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (_id == OIS::MB_Left)
	{
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
}

void GameWorld::injectKeyRelease(KeyCode _key)
{
    
}