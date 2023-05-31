#include "stdafx.h"
#include "SCCharSkill_Gather.h"


SCCharSkill_Gather::SCCharSkill_Gather():
	NetPacket(SC_CHAR_SKILL_GATHER)
{

}

SCCharSkill_Gather::~SCCharSkill_Gather()
{

}

bool SCCharSkill_Gather::process()
{
	/*KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjId);
	if (pObj == NULL) 
		return false;

	ObjectCmd	cmdTemp;
	cmdTemp.m_wID = OBJ_CMD_SKILL_CHARGE;
	cmdTemp.uParam[0] = GAME_TIME_PTR->GetTimeNow();
	cmdTemp.nParam[1] = mLogicCount;
	cmdTemp.nParam[2] = mSkillDataId;
	cmdTemp.nParam[3] = mTargetId;
	cmdTemp.fParam[4] = mTargetPos.m_fX;
	cmdTemp.fParam[5] = mTargetPos.m_fZ;
	cmdTemp.fParam[6] = mDir;
	cmdTemp.uParam[7] = mTotalTime;
	pObj->AddCommand(&cmdTemp);*/
	
	return true;
}

void SCCharSkill_Gather::setObjId(int32_t id)
{
	mObjId = id;
}

void SCCharSkill_Gather::setLogicCount(int32_t logicCount)
{
	mLogicCount = logicCount;
}

void SCCharSkill_Gather::setSkillDataId(int32_t id)
{
	mSkillDataId = id;
}

void SCCharSkill_Gather::setUserPosition(const GLPos* pos)
{
	mUserPosition = *pos;
}

void SCCharSkill_Gather::setTargetId(int32_t id)
{
	mTargetId = id;
}

void SCCharSkill_Gather::setTargetPosition(const GLPos* pos)
{
	mTargetPos = *pos;
}

void SCCharSkill_Gather::setDir(float dir)
{
	mDir = dir;
}

void SCCharSkill_Gather::setTotalTime(Time_t total)
{
	mTotalTime = total;
}


