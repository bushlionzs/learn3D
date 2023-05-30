/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateManager.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "CharacterStateManager.h"
#include "CharActionDelegator.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

CharacterStateManager::CharacterStateManager()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharacterStateManager::~CharacterStateManager()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateManager::Init(Character *pOnwer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pOnwer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Clear();
	m_pOnwer = pOnwer;
	m_oBuilder.BuildStateSystem(this, pOnwer);
	for(int32 i = 0; i < CharacterState_Num; ++i)
	{
		if(NULL == m_aStateMachine[i])
		{
			continue;
		}

		ChangeState(i, CHARACTER_LOGIC_IDLE);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CharacterStateManager::OnEvent_HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet[CharacterState_Num];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	bRet[CharacterState_Move] = OR_OK;
	bRet[CharacterState_Other] = OR_OK;
	for(int32 i = 0; i < CharacterState_Num; ++i)
	{
		if(NULL == m_aStateMachine[i])
		{
			continue;
		}

		bRet[i] = m_aStateMachine[i]->OnEvent_HeartBeat(uTime);
	}

	if(OR_ERROR == bRet[CharacterState_Move])
	{
		StopMove();
	}
	else if(bRet[CharacterState_Move] != OR_OK)
	{
		ChangeState(CharacterState_Move, CHARACTER_LOGIC_INVALID);
	}

	if(OR_OK != bRet[CharacterState_Other])
	{
		StopSkill();
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandIdle()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	OnCommandStop();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandJump()
{
	
	return OR_OK;


}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandStop()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	StopMove();
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	StopSkill();

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandMove()
{
	__GUARD__ if(CHARACTER_LOGIC_USE_ABILITY == m_aStateMachine[CharacterState_Other]->GetCurrentState())
	{
		ChangeState(CharacterState_Other, CHARACTER_LOGIC_IDLE);
	}

	return ChangeState(CharacterState_Move, CHARACTER_LOGIC_MOVE);

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandSkill()
{
	__GUARD__ return ChangeState(CharacterState_Other, CHARACTER_LOGIC_USE_SKILL);

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::OnCommandAbility()
{
	__GUARD__ return ChangeState(CharacterState_Other, CHARACTER_LOGIC_USE_ABILITY);

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateManager::AddMachine(CharacterStateMachine *pMachine, StateMachineType iType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pMachine);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(CharacterState_Move <= iType && CharacterState_Num > iType);
	m_aStateMachine[iType] = pMachine;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateManager::Clear()
{
	__GUARD__ m_oBuilder.Clear();
	memset(m_aStateMachine, 0, sizeof(m_aStateMachine));
	m_pOnwer = NULL;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CharacterStateManager::IsCharacterLogicStopped()
{
	__GUARD__ return
		(
			m_aStateMachine[CharacterState_Move]->GetCurrentState() == CHARACTER_LOGIC_INVALID
		&&	m_aStateMachine[CharacterState_Other]->GetCurrentState() == CHARACTER_LOGIC_IDLE
		);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateManager::ChangeState(int32 iIndex, ENUM_CHARACTER_LOGIC eLogic)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ 
	OPT_RESULT	ret = m_aStateMachine[iIndex]->ChangeState(eLogic);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK == ret)
	{
		return ret;
	}

	if(OR_NEED_STOP_MOVE == ret)
	{
		StopMove();
		return OR_OK;
	}

	return ret;
	//__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ENUM_CHARACTER_LOGIC CharacterStateManager::GetCurrentLogic()
{
	__GUARD__ return m_aStateMachine[CharacterState_Other]->GetCurrentState();

	__UNGUARD__ return CHARACTER_LOGIC_INVALID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CharacterStateManager::IsMoving()
{
	__GUARD__ return m_aStateMachine[CharacterState_Move]->GetCurrentState() == CHARACTER_LOGIC_MOVE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateManager::StopMove()
{
	__GUARD__ 

	ChangeState(CharacterState_Move, CHARACTER_LOGIC_INVALID);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateManager::StopSkill()
{
	__GUARD__ if(FALSE == GetGlobalActionDelegator().CanDoNextAction(*m_pOnwer))
	{
		GetGlobalActionDelegator().InterruptCurrentAction(*m_pOnwer);
	}

	ChangeState(CharacterState_Other, CHARACTER_LOGIC_IDLE);

	__UNGUARD__
}
