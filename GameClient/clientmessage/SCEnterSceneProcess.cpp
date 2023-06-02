#include "OgreHeader.h"
#include "SCEnterMap.h"
#include "game_scene_manager.h"
#include "engine_manager.h"


bool SCEnterMap::process()
{
	GameSceneManager::getSingletonPtr()->loadScene(mSceneId);

	Ogre::Vector3 mPosition;
	mPosition.x = mPositionX;
	mPosition.y = 0;
	mPosition.z = mPositionZ;

	EngineManager::getSingleton().setMyPosition(mPosition);

	/*bool bResult = SCENE_MANAGER_PTR->EnterScene(mSceneId, mSceneId);

	Ogre::Vector3 mPosition;
	mPosition.x = mPositionX;
	mPosition.y = 0;
	mPosition.z = mPositionZ;

	ENGINE_INTERFACE_PTR->GetOrphigineSystem()->setLocalPlayerPos(mPosition, nullptr);

	GameWorld::GetSingletonPtr()->createMyself(mObjectID, mGUID, mPositionX, mPositionZ);

	COMMAND_SYS_PTR->AddCommand(GCD_PLAYER_ENTER_WORLD, 0);*/

	return true;
}