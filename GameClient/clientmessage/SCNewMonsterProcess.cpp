#include "stdafx.h"
#include "SCNewMonster.h"
#include "KObjectManager.h"
#include "engine_manager.h"
#include "KNpc.h"
#include "data/GameDataCharacter.h"
#include "command/command.h"

//bool SCNewMonster::process()
//{
//	//KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
//
//	//if (pPlayer == nullptr)
//	//{
//	//	return false;
//	//}
//
//	Ogre::Vector3 fvGamePos;
//	Ogre::Vector3 fvPlanPos = Ogre::Vector3(mPositionX, 0.0f, mPositionZ);
//	EngineManager::getSingleton().positionAxisTrans(
//		GAT_GAME, fvPlanPos, GAT_SCENE, fvGamePos);
//
//	float fFaceDir = 0.0f;
//
//	KNpc* pNPC = (KNpc*)(KObjectManager::GetSingleton().getObject(mObjID));
//
//
//	if (nullptr == pNPC)
//	{
//		pNPC = (KNpc*)KObjectManager::GetSingleton().createNPC(mObjID);
//
//		pNPC->SetServerGUID(mGUID);
//	}
//
//	
//	
//
//
//	KCharatcterBaseData* pCharacterData = pNPC->GetCharacterData();
//
//
//	printf("create monster :%s\n", mName.c_str());
//
//	pCharacterData->Set_MountID(mHorseID);
//
//	pCharacterData->Set_MonstWeapon(mWeaponID);
//
//	pCharacterData->Set_RaceID(mRaceID);
//
//	pCharacterData->Set_Name(mName.c_str());
//
//	pCharacterData->Set_MoveSpeed(mMoveSpeed);
//
//	
//	pCharacterData->Set_HP(100);
//	pCharacterData->Set_HPPercent(100);
//
//	if (mCampID != -1)
//	{
//		SCampData camp;
//		camp.m_nCampID = mCampID;
//		pCharacterData->Set_CampData(&camp);
//	}
//
//	Ogre::Vector2	mapPos(fvGamePos.x, fvGamePos.z);
//	pNPC->calculateNodePos(mapPos, 0.0f);
//	pNPC->setDirection(fFaceDir);
//
//	/* ÉèÖÃÐÝÏÐ×´Ì¬ */
//	ObjectCmd	cmdTemp;
//	cmdTemp.m_wID = OBJ_CMD_IDLE;
//	cmdTemp.fParam[0] = fvGamePos.x;
//	cmdTemp.fParam[1] = fvGamePos.z;
//	cmdTemp.bParam[2] = FALSE;
//	pNPC->AddCommand(&cmdTemp);
//
//	return true;
//}