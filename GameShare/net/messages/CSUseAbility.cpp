#pragma once
#include "stdafx.h"
#include "CSUseAbility.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/ObjectManager.h"
#include "gameobject/Player.h"
#include "gameobject/Behavior_Player.h"
#include "skill/Skill_Base.h"
#include "skill/Skill_Manager.h"
#include "net/messages/SCAbilityResult.h"

CSUseAbility::CSUseAbility():
	NetPacket(CS_USE_ABILITY)
{

}

CSUseAbility::~CSUseAbility()
{

}

bool CSUseAbility::process()
{
	BaseSkill* pSkill;
	/*~~~~~~~~~~~~~~~~~~~~*/

	pSkill = g_pSkillManager->GetAbility(mAbilityId);
	if (pSkill == NULL)
	{
		return false;
	}


	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	if (pMap == nullptr)
	{
		return false;
	}

	Player* pPlayer = pMap->getPlayer(mPlayerId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SkillOpera* pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	if (0 != pAbilityOpera->m_SkillID)
	{
		return false;
	}

	pPlayer->reset_AbilityOpera();

	pAbilityOpera->m_SkillID = mAbilityId;
	pAbilityOpera->m_PresID = mPrescriptionId;
	pAbilityOpera->m_Obj = mObjectGuid;
	pAbilityOpera->m_nMaxTime = pSkill->GetOperationTime();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT res = pPlayer->GetHumanAI()->PushCmd_UseAbility();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (res == OR_OK)
	{
	}

	/*~~~~~~~~~~~~~~~~*/
	SCAbilityResult* packet = new SCAbilityResult;
	/*~~~~~~~~~~~~~~~~*/
	packet->setPlayerId(mPlayerId);
	packet->setAbilityId(pAbilityOpera->m_SkillID);
	packet->setPrescriptionId(pAbilityOpera->m_PresID);
	packet->setResult(res);
	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
	return true;
}

void CSUseAbility::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void CSUseAbility::setMapId(int32_t id)
{
	mMapId = id;
}

void CSUseAbility::setAbilityId(int32_t id)
{
	mAbilityId = id;
}

void CSUseAbility::setPlatformGUID(int32_t id)
{
	mObjectGuid = id;
}

void CSUseAbility::setPrescriptionId(int32_t id)
{
	mPrescriptionId = id;
}