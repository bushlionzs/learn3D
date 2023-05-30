#include "stdafx.h"
#include "HorseAttrCalculater.h"
#include "gameobject/Player.h"
#include "item/Item_Interface.h"
#include "TabDefine.h"
#include "map/game_map.h"
#include "Share/TAB/TabDefine_Map_Pet.h"
#include "server_settting.h"
#include "Archive/PlayerDB.h"


const int32	iIncPoint = 1;

using namespace Messages;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

HorseAttrCalculater::HorseAttrCalculater()
{
	m_nIndex = -1;
	m_pPetDB = NULL;
	m_pOwner = NULL;
	m_LastHeartBeatTick = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
HorseAttrCalculater::~HorseAttrCalculater()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!IsActive())
	{
		return;
	}

	HappinessHeartBeat(uTime);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::OnExpChange(uint32 iExp, BOOL bAccumulate, BOOL bLvupMsg, BOOL bRelateHappiness)
{
	__GUARD__ if(!IsActive()) return FALSE;

	if(GetLevel() >= PET_LEVEL_NUM)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bExpChanged = FALSE;
	uint32	nCurExp = GetExp();
	uint32	nOldExp = nCurExp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0xffffffff == nCurExp) return bExpChanged;

	if(!bAccumulate)
	{
		if(!IsCanLevelup()) return FALSE;
	}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//XCDetailAttrib_Pet	msgPetAttr;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//msgPetAttr.SetGUID(&m_pPetDB->m_GUID);
	//msgPetAttr.SetIndex(m_pOwner->GetHorseIndexByGUID(m_pPetDB->m_GUID));

	if(bRelateHappiness) iExp = GetRealExpByHappiness(iExp);
	

	if(0xffffffff - nCurExp < iExp)
	{
		nCurExp = 0xffffffff;
	}
	else
	{
		nCurExp += iExp;
	}

	if(nCurExp != nOldExp)
	{
		SetExp(GetCheckedValue(nCurExp));
		bExpChanged = TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bLevelUp = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsCanLevelup())
	{
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~*/
		BOOL	bOverMaxLevel;
		/*~~~~~~~~~~~~~~~~~~*/

		bLevelUp = DoLevelUpWhenExpChange(bOverMaxLevel);
		if(bLevelUp)
		{
			if( TRUE == bLvupMsg)
			{
                /*XCHorseLevelUp	msgLevelUp;

                msgLevelUp.SetOnwerObjId(m_pOwner->GetID());
                msgLevelUp.SetHorseLevel(GetLevel());
                m_pOwner->GetMap()->BroadCast(&msgLevelUp, m_pOwner, TRUE);*/
			}// if
			m_pOwner->OnEvent_PetChanged(m_pPetDB->m_nDataID);

			if(bOverMaxLevel)
			{
				///*~~~~~~~~~~~~~~~~~~~~~~~~*/
				//XCManipulatePetRet	msg;
				///*~~~~~~~~~~~~~~~~~~~~~~~~*/

				//msg.SetManipulateRet(XCManipulatePetRet::OPT_HORSE_RET_HORSE_HIGH_LEVEL_THAN_OWNER);
				//m_pOwner->GetConnector()->SendPacket(&msg);
			}
		}
	}

	if(bLevelUp || bExpChanged)
	{
		/*if(GetExp() != nOldExp)
		{
			msgPetAttr.SetExp(m_pPetDB->m_nExp);
		}

		if(bLevelUp)
		{
			msgPetAttr.SetLevel(m_pPetDB->m_nLevel);
			msgPetAttr.SetRemainPoint(m_pPetDB->m_nRemainPoint);
			msgPetAttr.SetHappiness(m_pPetDB->m_byHappiness);
		}

		m_pOwner->GetConnector()->SendPacket(&msgPetAttr);*/
	}

	return bExpChanged;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::SetHappiness(int32 iHappiness, BOOL bRefreshToClient)
{
	sItemInterface.SetHappiness(m_pOwner->GetPetContain(), m_nIndex, iHappiness);
	if(bRefreshToClient)
	{
		///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//XCDetailAttrib_Pet	msgPetAttr;
		///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		//msgPetAttr.SetGUID(&m_pPetDB->m_GUID);
		//msgPetAttr.SetIndex(m_pOwner->GetHorseIndexByGUID(m_pPetDB->m_GUID));
		//msgPetAttr.SetHappiness(m_pPetDB->m_byHappiness);
		//m_pOwner->GetConnector()->SendPacket(&msgPetAttr);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::DecHappiness(int32 iDecNum, BOOL bKillByMonster)
{
	__GUARD__ if(!IsActive())
	{
		return;
	}

	if(bKillByMonster)
		iDecNum += m_pOwner->GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE_PLUS);
	else
		iDecNum += m_pOwner->GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE);
	if(0 > iDecNum)
	{
		iDecNum = 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHappiness = m_pPetDB->m_byHappiness;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iDecNum >= iHappiness)
	{
		iHappiness = 0;
	}
	else
	{
		iHappiness -= iDecNum;
	}

	SetHappiness(iHappiness, TRUE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::IsActive()
{
	__GUARD__ if(m_pPetDB == NULL)
	{
		return FALSE;
	}

	if(m_pOwner == NULL)
	{
		return FALSE;
	}

	if(m_nIndex < 0 || m_nIndex > PLAYER_PET_MAX_COUNT)
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::LevelUp()
{
	__GUARD__ sItemInterface.SetLevel(m_pOwner->GetPetContain(), m_nIndex, m_pPetDB->m_nLevel + 1);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iValue = GetCheckedValue(m_pPetDB->m_nRemainPoint + g_Config.m_ConfigInfo.m_RemainPointOnLevelup);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sItemInterface.SetRemainPoint(m_pOwner->GetPetContain(), m_nIndex, iValue);

	SetHappiness(100, FALSE);

	m_pOwner->MarkLevelOneAttrDirtyFlagAndSendAttrMsg();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::SetExp(uint32 iExp)
{
	__GUARD__ sItemInterface.SetExp(m_pOwner->GetPetContain(), m_nIndex, iExp);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 HorseAttrCalculater::GetLevel(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPetDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pPetDB->m_nLevel;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 HorseAttrCalculater::GetExp()
{
	return m_pPetDB->m_nExp;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::SkillRealization(_HORSE_DB *pPetDB, GameMap *pMap)
{
	__GUARD__ if(NULL == pPetDB || NULL == pMap) return;

	if(pPetDB->m_nLevel > 60) return;

	/*~~~~~~~~~~~~~~*/
	int32	iSlot = 0;
	/*~~~~~~~~~~~~~~*/

	for(; iSlot < PET_MAX_SKILL_COUNT; ++iSlot)
	{
		if(pPetDB->m_SkillList[iSlot].m_nSkillID == INVALID_ID)
		{
			break;
		}
	}

	if(iSlot >= PET_MAX_SKILL_COUNT) return;

	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	iSkillCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		if(pPetDB->m_SkillList[i].m_nSkillID != INVALID_ID)
		{
			++iSkillCount;
		}
	}

	_HORSE_ATTR_TBL* horseTable = DataManager::GetSingletonPtr()->getHorseAttrTable();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRealID = horseTable->m_aHorseTbl[pPetDB->m_nDataID].m_iRealizationID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	_HORSE_SKILL_TBL* horseSkillTable = DataManager::GetSingletonPtr()->getHorseSkillTable();
	if(iSkillCount >= horseSkillTable->m_aHorseSkillRealizationTbl[iRealID].m_iSkillSlotCount)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRealRate = horseSkillTable->m_aSkillRealRateForSlot[iSlot];
	int32	iRand = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRand > iRealRate)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRandCount = horseSkillTable->m_aHorseSkillRealizationTbl[iRealID].m_oSkillSlot[iSlot].m_iSkillCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRandCount <= 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iSkillIndexInSlot = iRand % iRandCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iSkillIndexInSlot >= iRandCount)
	{
		iSkillIndexInSlot -= 1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRealizationSkillID = horseSkillTable->m_aHorseSkillRealizationTbl[iRealID].m_oSkillSlot[iSlot].
		m_aSkillSlot[iSkillIndexInSlot];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iRealizationSkillID != INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseSkill	oPetSkill;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	oPetSkill.m_nSkillID = iRealizationSkillID;
	oPetSkill.m_bCanUse = TRUE;
	pPetDB->m_SkillList[iSlot] = oPetSkill;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::HappinessHeartBeat(uint32 uTime)
{
	__GUARD__ if(!IsActive()) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	oldLastTick = m_LastHeartBeatTick;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_LastHeartBeatTick = uTime;

	if(0 == oldLastTick)
	{
		return;
	}

	if(oldLastTick > uTime)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	passtime = uTime - oldLastTick;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_pPetDB->m_uHappinessLeftTime > passtime)
	{
		m_pPetDB->m_uHappinessLeftTime -= passtime;
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHappiness = m_pPetDB->m_byHappiness - g_Config.m_ConfigInfo.m_PetHappinessPoint;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHappiness < 0)
	{
		iHappiness = 0;
	}

	SetHappiness(iHappiness, TRUE);

	m_pPetDB->m_uHappinessLeftTime = g_Config.m_ConfigInfo.m_PetHappinessInterval * 1000;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 HorseAttrCalculater::GetRealExpByHappiness(uint32 iExp)
{
	__GUARD__ if(m_pPetDB->m_byHappiness < g_Config.m_ConfigInfo.m_HorseCallUpHappiness)
	{
		iExp = (uint32) (iExp * 0.5f + 0.5f);
	}
	else if(m_pPetDB->m_byHappiness < g_Config.m_ConfigInfo.m_PetHappinessDecExp)
	{
		iExp = (uint32) (iExp * 0.8f + 0.5f);
	}

	return iExp;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::IsCanLevelup()
{
	__GUARD__ if(!IsActive())
	{
		return FALSE;
	}

	if(m_pPetDB->m_nLevel >= PET_LEVEL_NUM)
	{
		return FALSE;
	}

	if(m_pPetDB->m_nLevel - m_pOwner->GetLevel() >= g_Config.m_ConfigInfo.m_HorseCallupLevelThanPlayer)
	{
		return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 HorseAttrCalculater::GetCheckedValue(uint32 iValue)
{
	__GUARD__ if(iValue >= 0xffffffff)
	{
		iValue = 0xffffffff;
	}

	if(0 > iValue)
	{
		iValue = 0;
	}

	return iValue;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseAttrCalculater::SetChangeFade(int32 iMountID)
{
	__GUARD__ if(!IsActive())
	{
		return;
	}

	m_pOwner->SetMountID(iMountID);
	m_pOwner->SetMountModelID(iMountID);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::DoLevelUpWhenExpChange(BOOL &bOverMaxLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	bOverMaxLevel = FALSE;
	BOOL		bLevelup = FALSE;
	uint32		nCurExp = GetExp();
	uint32		nOldExp = nCurExp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SHorseLevelupTab* mHorseLevelupTable = DataManager::GetSingletonPtr()->getHorseLevelupTable();
	while(1)
	{
		if(!IsCanLevelup())
		{
			bOverMaxLevel = TRUE;
			break;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nNeedExp = mHorseLevelupTable->GetExp(GetLevel());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nCurExp < nNeedExp)
		{
			break;
		}

		LevelUp();
		nCurExp -= nNeedExp;
		bLevelup = TRUE;
	}

	if(nOldExp != nCurExp)
	{
		SetExp(GetCheckedValue(nCurExp));
	}

	return bLevelup;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_nIndex = -1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pPetDB = NULL;
	m_AttrBackUp.Clear();
	m_LastHeartBeatTick = 0;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::AttachHorse(_HORSE_DB *pPetDB)
{
	__GUARD__ if(NULL == m_pOwner) return FALSE;

	if(NULL == pPetDB)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	index = m_pOwner->GetHorseIndexByGUID(pPetDB->m_GUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(index < 0 || index >= PLAYER_PET_MAX_COUNT)
	{
		return FALSE;
	}

	m_nIndex = index;
	m_pPetDB = pPetDB;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::AttachHorse(SHorseGuid horseGUID)
{
	__GUARD__ if(NULL == m_pOwner) return FALSE;

	if(horseGUID.IsNull())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	index = m_pOwner->GetHorseIndexByGUID(horseGUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(index < 0 || index >= PLAYER_PET_MAX_COUNT)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB *pPetDB = m_pOwner->GetHorseDB(index);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pPetDB)
	{
		return FALSE;
	}

	m_nIndex = index;
	m_pPetDB = pPetDB;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseAttrCalculater::ResetCallUpHorse(BOOL bNewCallUp)
{
	__GUARD__ if(NULL == m_pOwner) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseGuid	curPetGUID = m_pOwner->GetDB()->GetCurrentPetGUID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!curPetGUID.IsNull())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = m_pOwner->GetHorseItem(curPetGUID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pItem == NULL)
		{
			/*~~~~~~~~~~~~~~~~~~~~~*/
			SHorseGuid	oPetGUID;
			/*~~~~~~~~~~~~~~~~~~~~~*/

			m_pOwner->GetDB()->SetCurrentPetGUID(oPetGUID);
			m_pOwner->SetMountModelID(-1);

			QLogSystem::QUICK_LOG
				(
					QUICK_LOG_PET,
					"(Horse DB error)ResetCallUpHorse. humanid:%d, petid:%d / %d",
					m_pOwner->GetID(),
					curPetGUID.m_uHighSection,
					curPetGUID.m_uLowSection
				);
		}
	}

	if(!AttachHorse(m_pOwner->GetDB()->GetCurrentPetGUID())) return FALSE;

	return TRUE;
	__UNGUARD__ return FALSE;
}
