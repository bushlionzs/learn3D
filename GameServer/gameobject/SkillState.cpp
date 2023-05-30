#include "stdafx.h"
#include "SkillState.h"
#include "skill/Spell_Helper.h"
#include "gameobject/Character.h"
#include "skill/Spell_Interface.h"
#include "gameobject/CharActionDelegator.h"
#include "data/data_manager.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

OPT_RESULT CharSkillState::OnEnterState()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ OPT_RESULT	ret = StopMoveWhenUseSkill(m_pOnwer->m_oStatePara.idSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_TRY_CATCH_RETURN == ret || OR_INVALID_SKILL == ret)
	{
		return ret;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams	&rParams = m_pOnwer->GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != rParams.GetActivatedScript())
	{
		return OR_OK;
	}

	m_pOnwer->AddLogicCount();

	/*~~~~~~~~~~~~~~~~*/
	GLPos	pos;
	/*~~~~~~~~~~~~~~~~*/

	if(NULL != m_pOnwer->m_oStatePara.paTargetPos)
	{
		pos.m_fX = m_pOnwer->m_oStatePara.paTargetPos->m_fX;
		pos.m_fZ = m_pOnwer->m_oStatePara.paTargetPos->m_fZ;
	}
	else
	{
		pos.m_fX = 0.0f;
		pos.m_fZ = 0.0f;
	}

	if
	(
		FALSE == g_SpellCore.ProcessSpellRequest
			(
				*m_pOnwer,
				m_pOnwer->m_oStatePara.idSkill,
				m_pOnwer->m_oStatePara.idTarget,
				pos,
				m_pOnwer->m_oStatePara.fDir,
				m_pOnwer->m_oStatePara.guidTarget,
				m_pOnwer->m_oStatePara.iHurtDelayTime
			)
	)
	{
		return(OPT_RESULT) m_pOnwer->GetTargetingAndDepletingParams().GetErrCode();
	}

	return ret;

	__UNGUARD__ return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharSkillState::OnExitState()
{
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharSkillState::OnEvent_HeartBeat(uint32 uTime)
{
	__GUARD__ if(m_pOnwer->IsDie())
	{
		return OR_DIE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Time_t	nDeltaTime = m_pOnwer->GetLogicTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(GetGlobalActionDelegator().OnEvent_HeartBeat(*m_pOnwer, nDeltaTime))
	{
		return OR_OK;
	}
	else
	{
		return OR_SKILL_STATE_ERROR;
	}

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ENUM_CHARACTER_LOGIC CharSkillState::GetStateType()
{
	return CHARACTER_LOGIC_USE_SKILL;
}

void  CharSkillState::OnStateActive()
{
	int kk = 0;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharSkillState::Clear()
{
	CharacterState::Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharSkillState::CharSkillState()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharSkillState::~CharSkillState()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharSkillState::StopMoveWhenUseSkill(SpellID_t idSkill)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(idSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		return OR_INVALID_SKILL;
	}

	/*~~~~~~~~~~~~~~~~*/
	OPT_RESULT ret = OR_OK;
	/*~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != m_pOnwer->GetObjType())
	{
		if
		(
			SKILL_TYPE_GATHER == pSkillTemplate->GetSkillType()
		||	SKILL_TYPE_LEAD == pSkillTemplate->GetSkillType()
		)
		{
			ret = OR_NEED_STOP_MOVE;
		}
	}

	if(Object::OBJECT_CLASS_MONSTER == m_pOnwer->GetObjType())
	{
		m_pOnwer->m_paramLogic_Move.Reset();
		return ret;
	}

	if(pSkillTemplate->IsRunSkill())
	{
		m_pOnwer->m_paramLogic_Move.Reset();
	}

	return ret;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}
