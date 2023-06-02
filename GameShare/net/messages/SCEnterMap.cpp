#include "stdafx.h"
#include "SCEnterMap.h"

//#include "game_world.h"
//#include "game_camera.h"
SCEnterMap::SCEnterMap():
	NetPacket(SC_ENTER_MAP)
{

}

SCEnterMap::~SCEnterMap()
{

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