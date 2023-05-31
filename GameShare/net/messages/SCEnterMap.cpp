#include "stdafx.h"
#include "SCEnterMap.h"
//#include "scene/GameSceneManager.h"
//#include "game_world.h"
//#include "game_camera.h"
SCEnterMap::SCEnterMap():
	NetPacket(SC_ENTER_MAP)
{

}

SCEnterMap::~SCEnterMap()
{

}

bool SCEnterMap::process()
{
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

void SCEnterMap::setActorID(int32_t objId, int32_t serverGuid)
{
	mObjectID = objId;
	mGUID = serverGuid;
}

void SCEnterMap::setSceneId(int32_t id)
{
	mSceneId = id;
}

void SCEnterMap::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}