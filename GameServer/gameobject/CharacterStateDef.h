/*$T MapServer/Server/Obj/HumanAssistantClass/CharacterStateDef.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef CharacterStateDef_h__25_12_2008_11_56
#define CharacterStateDef_h__25_12_2008_11_56

enum ENUM_CHARACTER_LOGIC
{
	CHARACTER_LOGIC_INVALID		= -1,
	CHARACTER_LOGIC_IDLE,
	CHARACTER_LOGIC_MOVE,
	CHARACTER_LOGIC_USE_SKILL,
	CHARACTER_LOGIC_USE_ABILITY,
	CHARACTER_LOGIC_NUMBERS
};

enum StateMachineType { CharacterState_Move = 0, CharacterState_Other, CharacterState_Num };

typedef struct CHARACTER_STATE_PARA
{
	int32		nHandleID;
	uint16		wNumTargetPos;
	const GLPos *paTargetPos;
	int32		nStopLogicCount;
	const GLPos *paCurPos;
	SpellID_t	idSkill;
	ObjID_t		idTarget;
	int32		iHurtDelayTime;
	float		fDir;
	GUID_t		guidTarget;
	ObjID_t		idSender;
	CHARACTER_STATE_PARA()
	{
		wNumTargetPos = 0;
		iHurtDelayTime = 0;
		guidTarget = 0;
		fDir = .0f;
		nHandleID = INVALID_ID;
		nStopLogicCount = INVALID_ID;
		idSkill = INVALID_ID;
		idTarget = INVALID_ID;
		idSender = INVALID_ID;
		paCurPos = NULL;
		paTargetPos = NULL;
	}
	~CHARACTER_STATE_PARA()
	{
	}
}
CharaterStatePara;
#endif
