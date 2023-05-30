/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateManager.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CharacterStateManager_h__24_12_2008_17_58
#define CharacterStateManager_h__24_12_2008_17_58

#include "CharacterStateMachineBuilder.h"


class	CharacterStateMachine;

class	CharacterStateManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CharacterStateManager();
	~			CharacterStateManager();
	void			Init(Character *pOnwer);
	void			AddMachine(CharacterStateMachine *pMachine, StateMachineType iType);
	BOOL			OnEvent_HeartBeat(uint32 uTime);
	OPT_RESULT			OnCommandIdle();
	OPT_RESULT			OnCommandJump();
	OPT_RESULT			OnCommandStop();
	OPT_RESULT			OnCommandMove();
	OPT_RESULT			OnCommandSkill();
	OPT_RESULT			OnCommandAbility();
	void			Clear();
	BOOL			IsCharacterLogicStopped();
	ENUM_CHARACTER_LOGIC	GetCurrentLogic();
	BOOL			IsMoving();
	void			StopMove();
	void			StopSkill();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	OPT_RESULT ChangeState(int32 iIndex, ENUM_CHARACTER_LOGIC eLogic);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CharacterStateMachine		*m_aStateMachine[CharacterState_Num];
	CharacterStateMachineBuilder	m_oBuilder;
	Character			*m_pOnwer;
};
#endif
