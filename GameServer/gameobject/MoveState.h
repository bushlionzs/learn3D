/*$T MapServer/Server/Obj/HumanAssistantClass/MoveState.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef MoveState_h__24_12_2008_16_47
#define MoveState_h__24_12_2008_16_47

#include "CharacterState.h"

class CharMoveState :
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
	virtual void  OnStateActive();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	OPT_RESULT LogicMoveImp();
	OPT_RESULT AddMove
		(
			int32		nHandleID,
			uint16		wNumTargetPos,
			const GLPos *paTargetPos,
			int32		nStopLogicCount,
			const GLPos *paCurPos,
			ObjID_t		nSenderID
		);
	OPT_RESULT AfreshMove(uint16 wNumTargetPos, const GLPos *paTargetPos);
	void BroatMoveMessage(const GLPos* pTargetPos, const GLPos* stopPos);
	OPT_RESULT ModifyMove(int32 nStopLogicCount, const GLPos *paCurPos);
	float	GetSafeMoveSpeed();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	CharMoveState();
	~	CharMoveState();
};
#endif
