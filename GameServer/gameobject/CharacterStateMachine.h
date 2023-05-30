#ifndef CharacterStateMachine_h__24_12_2008_16_48
#define CharacterStateMachine_h__24_12_2008_16_48

#include "CharacterStateDef.h"
class	CharacterState;
class	CharacterStateMachine
{
	friend class	CharacterStateMachineBuilder;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void			AddState(CharacterState *pState, ENUM_CHARACTER_LOGIC eState);
	OPT_RESULT			ChangeState(ENUM_CHARACTER_LOGIC eState);
	void			OnBlock(BOOL bBlock);
	OPT_RESULT			OnEvent_HeartBeat(uint32 uTime);
	BOOL			CanTransition(ENUM_CHARACTER_LOGIC eState);
	void			Clear();
	ENUM_CHARACTER_LOGIC	GetCurrentState();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	CharacterStateMachine();
	~	CharacterStateMachine();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CharacterState		*m_aState[CHARACTER_LOGIC_NUMBERS];
	BOOL			m_bBlock;
	ENUM_CHARACTER_LOGIC	m_eCurrentState;
};
#endif
