/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateMachineBuilder.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "CharacterStateMachineBuilder.h"
#include "CharacterStateManager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CharacterStateMachineBuilder::CharacterStateMachineBuilder()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharacterStateMachineBuilder::~CharacterStateMachineBuilder()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachineBuilder::BuildStateSystem(CharacterStateManager *pManager, Character *pOnwer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pManager && pOnwer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_oAbilityState.SetOnwer(pOnwer);
	m_IdleState.SetOnwer(pOnwer);
	m_MoveState.SetOnwer(pOnwer);
	m_SkillState.SetOnwer(pOnwer);
	CreateStateMachine(pManager);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachineBuilder::CreateStateMachine(CharacterStateManager *pManager)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	AddStateToMachine();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	AddMachineToManager(pManager, &m_oMoveMachine, CharacterState_Move);
	AddMachineToManager(pManager, &m_oOtherMachine, CharacterState_Other);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachineBuilder::AddStateToMachine()
{
	m_oOtherMachine.AddState(&m_oAbilityState, CHARACTER_LOGIC_USE_ABILITY);
	m_oOtherMachine.AddState(&m_IdleState, CHARACTER_LOGIC_IDLE);
	m_oOtherMachine.AddState(&m_SkillState, CHARACTER_LOGIC_USE_SKILL);

	m_oMoveMachine.AddState(&m_MoveState, CHARACTER_LOGIC_MOVE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachineBuilder::AddMachineToManager
(
	CharacterStateManager	*pManager,
	CharacterStateMachine	*pMachine,
	StateMachineType	iType
)
{
	__GUARD__ pManager->AddMachine(pMachine, iType);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharacterStateMachineBuilder::Clear()
{
	__GUARD__ m_oMoveMachine.Clear();
	m_oOtherMachine.Clear();
	m_oAbilityState.Clear();
	m_IdleState.Clear();
	m_MoveState.Clear();

	__UNGUARD__
}
