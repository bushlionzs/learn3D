#include "stdafx.h"
#include "SCTargetListAndHitFlags.h"

SCTargetListAndHitFlags::SCTargetListAndHitFlags()
	:NetPacket(SC_TARGETLIST_HITFLAGS)
{

}

SCTargetListAndHitFlags::~SCTargetListAndHitFlags()
{

}

bool SCTargetListAndHitFlags::process()
{
	/*KObject* pObj = (KObject*)(OBJECT_MANAGER_PTR->FindServerObject(mObjId));
	if (pObj == NULL)
		return false;


	ObjID_t dwTargetIDList[MAX_SKILL_TARGET_NUM] = { 0 };

	ObjectCmd cmdTemp;
	cmdTemp.m_wID = OBJ_CMD_SKILL_SEND;
	cmdTemp.uParam[0] = GAME_TIME_PTR->GetTimeNow();
	cmdTemp.nParam[1] = mLogicCount;
	cmdTemp.nParam[2] = mSkillId;
	cmdTemp.nParam[3] = mTargetList.size();
	cmdTemp.fParam[4] = 0.0f;
	cmdTemp.fParam[5] = 0.0f;
	cmdTemp.fParam[6] = 0.0f;
	cmdTemp.pParam[7] = NULL;

	if (!mTargetList.empty())
	{
		for (int32 i = 0; i < mTargetList.size(); ++i)
			dwTargetIDList[i] = mTargetList[i];
		cmdTemp.pParam[7] = (void*)&dwTargetIDList;
	}

	pObj->AddCommand(&cmdTemp);


	const vector3& pos = pObj->GetPosition();

	float deltax = pos.x - mPositionX;
	float deltaz = pos.z - mPositionZ;*/

	return true;
}

void SCTargetListAndHitFlags::setObjId(int32_t id)
{
	mObjId = id;
}

void SCTargetListAndHitFlags::setObjPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}

void SCTargetListAndHitFlags::setLogicCout(int32_t logicCount)
{
	mLogicCount = logicCount;
}

void SCTargetListAndHitFlags::setSkillId(int32_t skillId)
{
	mSkillId = skillId;
}

void SCTargetListAndHitFlags::addTargetId(int32_t targetId)
{
	mTargetList.push_back(targetId);
}