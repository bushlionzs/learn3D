#include "stdafx.h"
#include "SCCharStopAction.h"
#include "server/server_manager.h"

SCCharStopAction::SCCharStopAction():
	NetPacket(SC_CHAR_STOP_ACTION)
{

}

SCCharStopAction::~SCCharStopAction()
{

}

bool SCCharStopAction::process()
{
	KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectId);
	if (pObj == NULL) return MP_CONTINUE;

	ObjectCmd	cmdTemp;
	cmdTemp.m_wID = OBJ_CMD_STOP_ACTION;
	cmdTemp.nParam[0] = mLogicCount;
	cmdTemp.uParam[1] = mStopTime;
	pObj->AddCommand(&cmdTemp);
	
	return true;
}

void SCCharStopAction::setObjectId(int32_t id)
{
	mObjectId = id;
}


void SCCharStopAction::setLogicCount(int32_t logicCount)
{
	mLogicCount = logicCount;
}

void SCCharStopAction::setStopTime(Time_t stopTime)
{
	mStopTime = stopTime;
}

