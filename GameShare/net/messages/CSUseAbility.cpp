#pragma once
#include "stdafx.h"
#include "CSUseAbility.h"
#include "server/map/map_manager.h"
#include "server/map/game_map.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Player.h"
#include "server/gameobject/Behavior_Player.h"
#include "server/skill/Skill_Base.h"
#include "server/skill/Skill_Manager.h"
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
		return MP_CONTINUE;
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
		return MP_CONTINUE;
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
	NetManager::GetSingletonPtr()->sendNetMessage(packet);
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