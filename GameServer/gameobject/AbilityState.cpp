/*$T MapServer/Server/Obj/HumanAssistantClass/AbilityState.cpp GC 1.140 10/10/07 10:07:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "AbilityState.h"
#include "Character.h"
#include "Behavior_Player.h"
#include "Player.h"
#include "net/messages/SCAbilityAction.h"
#include "skill/Skill_All.h"
#include "skill/Skill_Manager.h"
#include "item/item_interface.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

OPT_RESULT CharAbilityState::OnEnterState()
{
	if(m_pOnwer == NULL)
	{
		return OR_ABILITY_CANNOT_FIND_OWNER;
	}

	if(Object::OBJECT_CLASS_PLAYER != m_pOnwer->GetObjType())
	{
		return OR_ABILITY_OWNER_ISNOT_HUMAN;
	}

	m_bIsFinish = FALSE;
	m_pOnwer->AddLogicCount();


	SCAbilityAction* packet = new SCAbilityAction;
	/*~~~~~~~~~~~~~~~~*/

	packet->setObjID(m_pOnwer->GetID());
	packet->setLogicCount(m_pOnwer->GetLogicCount());
	packet->setAbilityId(((Player*)m_pOnwer)->m_LastOpera.m_SkillID);
	packet->setPrescriptionId(((Player*)m_pOnwer)->m_LastOpera.m_PresID);
	packet->setTargetId(((Player*)m_pOnwer)->m_LastOpera.m_Obj);
	packet->setBeginOrEnd(SCAbilityAction::ABILITY_BEGIN);
	
	NetManager::GetSingletonPtr()->sendNetMessage(packet);
	/*~~~~~~~~~~~~~~~~*/
	
	((Behavior_Player *) m_pOnwer->GetAIObj())->ForceInterruptAutoSpell();
	((Player *) m_pOnwer)->m_LastOpera.m_nCurTime = 0;
	m_pOnwer->OnEvent_ActionStarted();

	return OR_NEED_STOP_MOVE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharAbilityState::OnExitState()
{
	__GUARD__ if(m_pOnwer == NULL)
	{
		return OR_ABILITY_CANNOT_FIND_OWNER;
	}

	
	((Player *) m_pOnwer)->reset_AbilityOpera();



	__UNGUARD__ return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharAbilityState::OnEvent_HeartBeat(uint32 uTime)
{
	if (m_pOnwer == NULL)
	{
		return OR_ABILITY_CANNOT_FIND_OWNER;
	}
	((Player*)m_pOnwer)->m_LastOpera.m_nCurTime += (int32)(m_pOnwer->GetLogicTime());

	if (((Player*)m_pOnwer)->m_LastOpera.m_nCurTime >= ((Player*)m_pOnwer)->m_LastOpera.m_nMaxTime)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BaseSkill* pSkill;
		OPT_RESULT		res;

		pSkill = g_pSkillManager->GetAbility(((Player*)m_pOnwer)->m_LastOpera.m_SkillID);
		if (NULL == pSkill)
		{
			return OR_INVALID_ABILITY;
		}

		res = pSkill->OnEvent_ProcOver((Player*)m_pOnwer);

		if (res != OR_OK)
		{
		}

		m_bIsFinish = TRUE;

		return OR_ABILITY_PROC_OVER_FAIL;
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		BaseSkill* pSkill;
		/*~~~~~~~~~~~~~~~~~~~~*/

		pSkill = g_pSkillManager->GetAbility(((Player*)m_pOnwer)->m_LastOpera.m_SkillID);
		KCheck(pSkill != NULL);

		if
			(
				pSkill->GetOperationToolID() != INVALID_ID
				&& sItemInterface.CalcEquipItemCount((Player*)m_pOnwer, pSkill->GetOperationToolID()) < 1
				)
		{
			pSkill->OnEvent_ProcInterrupt((Player*)m_pOnwer);
		}
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharAbilityState::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CharacterState::	Clear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bIsFinish = TRUE;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ENUM_CHARACTER_LOGIC CharAbilityState::GetStateType()
{
	return CHARACTER_LOGIC_USE_ABILITY;
}

void  CharAbilityState::OnStateActive()
{
	int kk = 0;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharAbilityState::CharAbilityState()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharAbilityState::~CharAbilityState()
{
}
