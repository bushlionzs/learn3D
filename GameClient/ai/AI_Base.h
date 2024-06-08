
/* AI_Base.h 功能： 人物AI基类 修改记录： */
#pragma once
#include "AI_State.h"
#include "KCommand.h"

class	KCharacter;

class	KAI
{
public:
	virtual KHAN_RETURN_RESULT	Update(void);

	/* 压入一条指令 */
	virtual eRUN_CMD_RESULT_CODE	AddCommand(const AICmd *pCmd) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Idle() = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_MoveTo(FLOAT	fDestX, FLOAT fDestZ, BOOL bDirectMove = FALSE, BOOL bShowPath = FALSE, BOOL bShowCursor = FALSE) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_StopMove(BOOL bImme = TRUE) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Jump(void) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_UseSkill(int32 idSkill, GUID_t guidTarget, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_DefaultEvent(int32 nEventType, FLOAT	fTargetX, FLOAT	fTargetY, int32 nTargetId, LPCSTR szTargetName, BOOL	bShowPath = FALSE) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_ActiveTripper(int32 nObjID) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Follow(int32 nTargetID) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_PickUp() = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_ComposeItem(int32 nPrescriptionID) = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Dead() = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Stall() = 0;
	virtual eRUN_CMD_RESULT_CODE	AddCommand_OpenBox() = 0;

	virtual void		Reset(void) = 0;

protected:
	/* 指令 */
	virtual eRUN_CMD_RESULT_CODE	Handle_Command(const AICmd *pCmd) = 0;

public:

	virtual BOOL		Do_Move(const GLPos *pNodeList, uint32 nNodeNum, BOOL bDirectMove, int32 nPathShow = 0, int32 nMoveType=0)			{ return TRUE; }
	virtual BOOL 		Do_StopMove()																										{ return TRUE; }
	virtual BOOL 		Do_UseSkill(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir)			{ return TRUE; }
	virtual BOOL 		Do_ToSpeak(int32 nEventType, int32 nTargetID)																		{ return TRUE; }
	virtual BOOL 		Do_ComposeItem(int32 nAbilityID, int32 PrescriptionID, ObjID_t guidPlatform)										{ return TRUE; }
	virtual BOOL 		Do_ActiveObj(int32 nTargetID)																						{ return TRUE; }
	virtual BOOL 		Do_Jump(void)																										{ return TRUE; }

	virtual BOOL		IsKeyMoveMode(void) { return FALSE; }
	virtual BOOL		IsCanMove()			{ return FALSE; }
	// 显示移动终点
	virtual void		ShowMoveFinalPos(const vector2& fvPos, BOOL bDirectMove, int32 nPathShow) {}

public:
	KAI();
	virtual ~KAI(void);

	KCharacter*			GetCharacter(void)	{ return m_pCharacterObj; }

	/* 当前AI逻辑状态 */
	virtual AI_STATE	GetMySelfAI(void);

protected:
	KAIState*			GetActiveAI() const			{return m_pAIState;	}
	KAIState*			GetAIState(AI_STATE eAI);

	AI_ACTIVE_RESULT	ChangeAIState(AI_STATE eAI, const AICmd &cmd);
	void				ShutDownAI();

protected:
	KCharacter* m_pCharacterObj;

private:
	AISStateList	m_StateList;
	KAIState*	m_pAIState;

};	/* class */
