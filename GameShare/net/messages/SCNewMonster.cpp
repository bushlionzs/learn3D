#include "stdafx.h"
#include "SCNewMonster.h"
//#include "game_world.h"
SCNewMonster::SCNewMonster()
	:NetPacket(SC_NEWMONSTER)
{

}

SCNewMonster::~SCNewMonster()
{

}


bool SCNewMonster::process()
{
	//if (OBJECT_MANAGER_PTR->GetMySelf() == nullptr)
	//{
	//	return false;
	//}

	//vector3			fvGamePos;
	//vector3			fvPlanPos = vector3(mPositionX, 0.0f, mPositionZ);
	//ENGINE_INTERFACE_PTR->PositionAxisTrans(GAT_GAME, fvPlanPos, GAT_SCENE, fvGamePos);

	//float fFaceDir = 0.0f;

	//KCharacter_NPC* pNPC = (KCharacter_NPC*)(OBJECT_MANAGER_PTR->FindServerObject(mObjID));


	//if (nullptr == pNPC)
	//{
	//	pNPC = OBJECT_MANAGER_PTR->NewPlayerNPC(mObjID);
	//	pNPC->SetDummyObjectFlag(FALSE);
	//	pNPC->Initialize(fvGamePos, vector3(0.f, mDir, 0.f));
	//	pNPC->SetServerGUID(mGUID);
	//}
	//else
	//{
	//	vector2	mapPos(fvGamePos.x, fvGamePos.z);
	//	pNPC->CalculateNodePos(mapPos);
	//	pNPC->SetFaceDir(fFaceDir);
	//	pNPC->Reset();
	//}
	//
	//OBJECT_MANAGER_PTR->Set_Update_NPC_InfoBoard(TRUE);
	//
	//pNPC->SetNpcType(NPC_TYPE_MONSTER);


	//KCharatcterBaseData* pCharacterData = pNPC->GetCharacterData();


	//printf("create monster :%s\n", mName.c_str());
	//pCharacterData->Set_Name(mName.c_str());

	//pCharacterData->Set_MoveSpeed(mMoveSpeed);

	//pCharacterData->Set_MountID(mHorseID);

	//pCharacterData->Set_MonstWeapon(mWeaponID);

	//pCharacterData->Set_RaceID(mRaceID);
	//pCharacterData->Set_HP(100);
	//pCharacterData->Set_HPPercent(100);

	//if (mCampID != -1)
	//{
	//	SCampData camp;
	//	camp.m_nCampID = mCampID;
	//	pCharacterData->Set_CampData(&camp);
	//}

	//vector2	mapPos(fvGamePos.x, fvGamePos.z);
	//pNPC->CalculateNodePos(mapPos);

	///* ÉèÖÃÐÝÏÐ×´Ì¬ */
	//ObjectCmd	cmdTemp;
	//cmdTemp.m_wID = OBJ_CMD_IDLE;
	//cmdTemp.fParam[0] = fvGamePos.x;
	//cmdTemp.fParam[1] = fvGamePos.z;
	//cmdTemp.bParam[2] = FALSE;
	//pNPC->AddCommand(&cmdTemp);

	//OBJECT_MANAGER_PTR->GetLoadQueue()->TryAddLoadTask
	//(
	//	mObjID,
	//	KObjectLoadQueue::OT_MONST
	//);


	
	return true;
}

void SCNewMonster::setObjID(uint32_t id)
{
	mObjID = id;
}

void SCNewMonster::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}

void SCNewMonster::setDir(float dir)
{
	mDir = dir;
}

void SCNewMonster::setSpeed(float speed)
{
	mMoveSpeed = speed;
}

void SCNewMonster::setHourseID(int32_t id)
{
	mHorseID = id;
}

void SCNewMonster::setWeaponID(int32_t id)
{
	mWeaponID = id;
}

void SCNewMonster::setMonsterType(int32_t type)
{
	mMonsterType = type;
}

void SCNewMonster::setGUID(uint32_t id)
{
	mGUID = id;
}

void SCNewMonster::setRaceID(int32_t id)
{
	mRaceID = id;
}

void SCNewMonster::setName(const char* name)
{
	mName = name;
}

void SCNewMonster::setCampID(int32_t id)
{
	mCampID = id;
}
