#include "stdafx.h"
#include "SCCharEquipment.h"
#include "server/server_manager.h"

SCCharEquipment::SCCharEquipment():
	NetPacket(SC_CHAR_EQUIPMENT)
{

}

SCCharEquipment::~SCCharEquipment()
{

}

bool SCCharEquipment::process()
{
	
	
	return true;
}

void SCCharEquipment::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCCharEquipment::setSceneId(int32_t id)
{
	mSceneId = id;
}

