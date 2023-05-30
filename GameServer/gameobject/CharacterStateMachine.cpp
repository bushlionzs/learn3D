/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateMachine.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "CharacterStateMachine.h"
#include "CharacterState.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void CharacterStateMachine::AddState(CharacterState *pState, ENUM_CHARACTER_LOGIC eState)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pState);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(CHARACTER_LOGIC_INVALID < eState && CHARACTER_LOGIC_NUMBERS > eState);
	m_aState[eState] = pState;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateMachine::ChangeState(ENUM_CHARACTER_LOGIC eState)
{
	__GUARD__ if(!CanTransition(eState))
	{
		return OR_CHANGE_STATE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~*/
	OPT_RESULT ret = OR_OK;
	/*~~~~~~~~~~~~~~~~*/

	if(CHARACTER_LOGIC_INVALID != m_eCurrentState)
	{
		m_aState[m_eCurrentState]->OnExitState();
	}

	if(CHARACTER_LOGIC_INVALID != eState)
	{
		ret = m_aState[eState]->OnEnterState();
	}

	m_eCurrentState = eState;
	return ret;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachine::OnBlock(BOOL bBlock)
{
	m_bBlock = bBlock;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharacterStateMachine::OnEvent_HeartBeat(uint32 uTime)
{
	__GUARD__ if(m_bBlock)
	{
		return OR_OK;
	}

	if(CHARACTER_LOGIC_INVALID >= m_eCurrentState)
	{
		return OR_OK;
	}

	if(NULL == m_aState[m_eCurrentState])
	{
		return OR_OK;
	}

	return m_aState[m_eCurrentState]->OnEvent_HeartBeat(uTime);

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CharacterStateMachine::CanTransition(ENUM_CHARACTER_LOGIC eState)
{
	__GUARD__ 
	if(CHARACTER_LOGIC_INVALID > eState || CHARACTER_LOGIC_NUMBERS <= eState)
	{
		return FALSE;
	}

	if(m_bBlock)
	{
		return FALSE;
	}

	return m_aState[eState] ? true : false;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachine::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bBlock = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_eCurrentState = CHARACTER_LOGIC_INVALID;
	memset(m_aState, 0, sizeof(m_aState));

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharacterStateMachine::CharacterStateMachine()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharacterStateMachine::~CharacterStateMachine()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ENUM_CHARACTER_LOGIC CharacterStateMachine::GetCurrentState()
{
	return m_eCurrentState;
}
