#include "stdafx.h"
#include "SCCooldownUpdate.h"

SCCooldownUpdate::SCCooldownUpdate():
	NetPacket(SC_COOLDOWN_UPDATE)
{

}

SCCooldownUpdate::~SCCooldownUpdate()
{

}

bool SCCooldownUpdate::process()
{
	return true;
}

void SCCooldownUpdate::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCCooldownUpdate::setSceneId(int32_t id)
{
	mSceneId = id;
}

