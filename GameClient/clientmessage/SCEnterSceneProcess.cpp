#include "stdafx.h"
#include "SCEnterMap.h"
#include "game_scene_manager.h"
#include "engine_manager.h"
#include "KObjectManager.h"
#include "kplayer.h"

bool SCEnterMap::process()
{
	GameSceneManager::getSingletonPtr()->loadScene(mSceneId);

	Ogre::Vector3 mPosition;
	mPosition.x = mPositionX;
	mPosition.y = 0;
	mPosition.z = mPositionZ;


	KPlayer* pPlayer = (KPlayer*)KObjectManager::GetSingleton().createPlayer(mObjectID);
	pPlayer->setPosition(mPosition);
	return true;
}