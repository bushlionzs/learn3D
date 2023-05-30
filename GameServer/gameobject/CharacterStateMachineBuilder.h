/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateMachineBuilder.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CharacterStateMachineBuilder_h__24_12_2008_16_58
#define CharacterStateMachineBuilder_h__24_12_2008_16_58

#include "CharacterStateMachine.h"
#include "AbilityState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "SkillState.h"

class	CharacterStateManager;

class	CharacterStateMachineBuilder
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CharacterStateMachineBuilder();
	~	CharacterStateMachineBuilder();

	void	BuildStateSystem(CharacterStateManager *pManager, Character *pOnwer);
	void	Clear();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	CreateStateMachine(CharacterStateManager *pManager);
	void	AddStateToMachine();
	void	AddMachineToManager
		(
			CharacterStateManager	*pManager,
			CharacterStateMachine	*pMachine,
			StateMachineType	iType
		);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CharacterStateMachine	m_oMoveMachine;

	CharacterStateMachine	m_oOtherMachine;
	CharAbilityState	m_oAbilityState;
	CharIdleState		m_IdleState;
	CharMoveState		m_MoveState;
	CharSkillState		m_SkillState;
};
#endif
