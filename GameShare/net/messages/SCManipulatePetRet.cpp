#include "stdafx.h"
#include "SCManipulatePetRet.h"
#include "server/server_manager.h"

SCManipulatePetRet::SCManipulatePetRet():
	NetPacket(SC_MANIPULATE_PET_RESULT)
{

}

SCManipulatePetRet::~SCManipulatePetRet()
{

}

bool SCManipulatePetRet::process()
{
	
	
	return true;
}

void SCManipulatePetRet::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCManipulatePetRet::setSceneId(int32_t id)
{
	mSceneId = id;
}

void SCManipulatePetRet::setManipulateRet(int32_t ret)
{
	mHorseResult = ret;
}

