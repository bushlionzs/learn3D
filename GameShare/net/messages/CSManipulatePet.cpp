#include "stdafx.h"
#include "CSManipulatePet.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "map/map_manager.h"
#include "net/messages/SCEnterMap.h"
#include "net/net_message_manager.h"
#include "db/db_manager.h"
#include "db/db_task.h"
#include "net/messages/SCCharHumanBaseAttrib.h"
#include "server_settting.h"
#include "data/data_manager.h"

CSManipulatePet::CSManipulatePet():
	NetPacket(CS_MANIPULATE_PET)
{

}

CSManipulatePet::~CSManipulatePet()
{

}

bool CSManipulatePet::process()
{
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	if (mType == MANIPULATE_CREATEHORSE)
	{
		int32	index = pPlayer->GetHorseIndexByGUID(mGUID);
		if (index == INVALID_ID)
		{
			return false;
		}

		_HORSE_DB* pPetDB = pPlayer->GetHorseDB(index);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pPetDB->m_byHappiness < g_Config.m_ConfigInfo.m_HorseCallUpHappiness)
		{
			pPlayer->SendOperateResultMsg(OR_NEED_HAPPINESS_60, 0);
			return false;
		}

		if (pPetDB->m_nLevel - pPlayer->GetLevel() > g_Config.m_ConfigInfo.m_HorseCallupLevelThanPlayer)
		{
			pPlayer->SendOperateResultMsg(OR_NEED_HIGH_LEVEL, 0);
			return false;
		}

		pPlayer->SetMountID(pPetDB->m_iModelID);
		pPlayer->ChangeCallUpHorse(mGUID);
		pPlayer->SetMountModelID(pPetDB->m_iModelID);

		addPassiveSkillToOnwer(pPlayer, pPetDB);
		pPlayer->MarkLevelOneAttrDirtyFlag();
		pPlayer->HorseEventScript(HORSE_CALL_SCRIPT_ON);
	}
	else if (mType == MANIPULATE_DELETEHORSE)
	{
		pPlayer->ReCallHorse();
	}
	else if (mType == MANIPULATE_FREEHORSE)
	{

	}
	return true;
}

void CSManipulatePet::addPassiveSkillToOnwer(Player* pPlayer, _HORSE_DB* pPetDB)
{
	for (int32 i = 0; i < PET_MAX_APPER_COUNT; ++i)
	{
		pPlayer->SetHorseDataIndex(i, INVALID_ID);
	}

	for (int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		if (pPetDB->m_SkillList[i].m_bCanUse == FALSE || pPetDB->m_SkillList[i].m_nSkillID == INVALID_ID)
		{
			continue;
		}

		startPassiveSkill(pPetDB->m_SkillList[i].m_nSkillID, pPlayer, 1, i);
	}
}

void CSManipulatePet::startPassiveSkill(SpellID_t iSkillID, Player* pPlayer, int32 iSkillLevel, int32 iIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellTemplateData* pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTemplate)
	{
		return;
	}

	if (pTemplate->GetPassiveFlag() <= 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellInstanceData* pInstance = DataManager::GetSingletonPtr()->getSpellInstance(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pInstance == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Descriptor* pDescriptor = pInstance->GetDescriptorByIndex(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pDescriptor == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDataIndex = pDescriptor->GetValueBySkillLevel(iSkillLevel - 1);
	Player* pTemp = const_cast<Player*>(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pTemp->SetHorseDataIndex(iIndex, iDataIndex);
	g_EffectInterface.SendEffectToUnit(*pTemp, iDataIndex, pPlayer->GetID(), iSkillID);
}

void CSManipulatePet::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void CSManipulatePet::setMapId(int32_t id)
{
	mMapId = id;
}

void CSManipulatePet::setGUID(const SHorseGuid& guid)
{
	mGUID = guid;
}

void CSManipulatePet::setManipulateType(ENUM_MANIPULATE_TYPE type)
{
	mType = type;
}