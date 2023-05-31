#include "stdafx.h"
#include "SCAbilityAction.h"

SCAbilityAction::SCAbilityAction():
	NetPacket(SC_MESSAGE_ABILITY_ACTION)
{

}

SCAbilityAction::~SCAbilityAction()
{

}

bool SCAbilityAction::process()
{
	/*KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectId);
	if (pObj == NULL)
	{
		return false;
	}

	if (mBeginEnd == SCAbilityAction::ABILITY_BEGIN)
	{
		ObjectCmd	cmdTemp;
		cmdTemp.m_wID = OBJ_CMD_ABILITY;
		cmdTemp.uParam[0] = GAME_TIME_PTR->GetTimeNow();
		cmdTemp.nParam[1] = mLogicCount;
		cmdTemp.nParam[2] = mAbilityId;
		cmdTemp.nParam[3] = mPrescriptionId;
		cmdTemp.nParam[4] = mTargetId;
		pObj->AddCommand(&cmdTemp);
	}*/
	
	return true;
}

void SCAbilityAction::setObjID(int32_t id)
{
	mObjectId = id;
}

void SCAbilityAction::setLogicCount(int32_t id)
{
	mLogicCount = id;
}

void SCAbilityAction::setAbilityId(int32_t id)
{
	mAbilityId = id;
}

void SCAbilityAction::setPrescriptionId(int32_t id)
{
	mPrescriptionId = id;
}

void SCAbilityAction::setTargetId(int32_t id)
{
	mTargetId = id;
}

void SCAbilityAction::setBeginOrEnd(int32_t value)
{
	mBeginEnd = value;
}
