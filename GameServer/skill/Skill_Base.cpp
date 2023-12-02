/*$T MapServer/Server/Skill/Skill.cpp GC 1.140 10/10/07 10:07:53 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Skill_Base.h"
#include "TabDefine.h"
#include "map/game_map.h"
#include "gameobject/Behavior_Player.h"
#include "item/Item_Interface.h"
#include "net/messages/SCAbilityAction.h"
#include "net/messages/SCAbilityResult.h"

const float	EXT_ABILITY_DISTANCE = 5.0f;

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSkill::OnEvent_ProcInterrupt(Player *pPlayer)
{
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	SCAbilityAction* packet = new SCAbilityAction;
	/*~~~~~~~~~~~~~~~~~~~~*/

	packet->setObjID(pPlayer->GetID());
	packet->setAbilityId(pAbilityOpera->m_SkillID);
	packet->setLogicCount(pPlayer->GetLogicCount());
	packet->setTargetId(pAbilityOpera->m_Obj);
	packet->setPrescriptionId(pAbilityOpera->m_PresID);
	packet->setBeginOrEnd(SCAbilityAction::ABILITY_END);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet);

	/*~~~~~~~~~~~~~~~~*/
	SCAbilityResult* packet2 = new SCAbilityResult;
	/*~~~~~~~~~~~~~~~~*/

	packet2->setAbilityId(pAbilityOpera->m_SkillID);
	packet2->setPrescriptionId(pAbilityOpera->m_PresID);
	packet2->setResult(OR_FAILURE);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet2);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT BaseSkill::CanUseSkill(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	if(pPlayer->IsAbilityHaveLearned(m_SkillID) == FALSE)
	{
		return OR_WARNING;
	}

	if(m_OperationToolID != INVALID_ID && sItemInterface.CalcEquipItemCount(pPlayer, m_OperationToolID) < 1)
	{
		return OR_NO_TOOL;
	}

	/*~~~~~~~~~~*/
	Object	*pObj;
	/*~~~~~~~~~~*/

	pObj = pPlayer->GetMap()->GetSpecificObjByID(pAbilityOpera->m_Obj);
	if(pObj != NULL)
	{
		if(pPlayer->IsInValidRadius(pObj, m_PlatformDistance + EXT_ABILITY_DISTANCE) == FALSE)
		{
			return OR_OUT_PLATFORM;
		}

		pPlayer->FaceTo(pObj);
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BaseSkill::BaseSkill()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BaseSkill::Clear()
{
	m_SkillID = INVALID_ID;
	m_pStrSkillName = NULL;
	m_LevelDemand = 0;
	m_iSkillLevelLimit = 0;
	m_OperationTime = 0;
	m_OperationToolID = INVALID_ID;
	m_PlatformID = INVALID_ID;
	m_PlatformDistance = .0;
	m_OperationActionID = 0;
	memset(m_ExpTable, 0, EXPTABLE_NAME_LENGTH);
	m_ExpTableIndex = INVALID_ID;
	m_pExpTabel = NULL;
}


