/*$T MapServer/Server/Obj/HumanAssistantClass/IdleBHVState.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef IdleState_h__24_12_2008_16_45
#define IdleState_h__24_12_2008_16_45

#include "CharacterState.h"

class CharIdleState :
	public CharacterState
{
	friend class	CharacterStateMachineBuilder;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual OPT_RESULT			OnEnterState();
	virtual OPT_RESULT			OnExitState();
	virtual OPT_RESULT			OnEvent_HeartBeat(uint32 uTime);
	virtual void			Clear();
	virtual ENUM_CHARACTER_LOGIC	GetStateType();

	void  OnStateActive();
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	CharIdleState();
	~	CharIdleState();
};
#endif
