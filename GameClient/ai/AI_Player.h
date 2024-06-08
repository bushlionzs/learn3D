#pragma once
#include "AI_Base.h"

/*
 * 键盘移动的方向类型 ;
 * 8 4 2 1 左 上 右 下
 */
#define KMT_INVALID			0x0
#define KMT_DOWN			0x1 /* 下 */
#define KMT_RIGHT			0x2 /* 右 */
#define KMT_UP				0x4 /* 上 */
#define KMT_LEFT			0x8 /* 左 */

#define KMT_LU				0xC /* 左上 */
#define KMT_RU				0x6 /* 右上 */
#define KMT_LD				0x9 /* 左下 */
#define KMT_RD				0x3 /* 右下 */

#define KMT_UP_OR_DOWN		0x5 /* 上下 */
#define KMT_LEFT_OR_RIGHT	0xA /* 左右 */

enum AI_CONTROL_RESULT
{
	AI_CONTROL_UNKNOW = -1, 
	AI_CONTROL_FALSE, 
	AI_CONTROL_TRUE, 
};

// 移动路径显示
enum AI_MOVE_PATH_SHOW
{
	AI_MOVE_PATH_SHOW_NOTHING = 0,		// 无显示
	AI_MOVE_PATH_SHOW_CURSOR,			// 显示光标
	AI_MOVE_PATH_SHOW_PATH,				// 显示路径
	AI_MOVE_PATH_SHOW_PATH_AND_CURSOR,	// 显示路径和光标
};

class CMapPath;

typedef std::vector<GLPos>	MovePathList;

class KAI_Player :
	public KAI
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 逻辑桢 */
	virtual KHAN_RETURN_RESULT	Update(void);

	/* 重置 */
	virtual void				Reset(void);

	void						DisconnectObj();
	void						ConnectObj(int32 nObjID);

	/* 设置控制标识 */
	void						SetControlOtherObjFlag(BOOL bCanControl, int32 nOtherObjID);

protected:
	void				ConnectObj(KCharacter *pCharacter);

	AI_CONTROL_RESULT	GetControlFlag();
	eRUN_CMD_RESULT_CODE			GetControlResult();

	BOOL				IsMySelfObj();

/*
 -----------------------------------------------------------------------------------------------------------------------
    某逻辑状态中的Update桢
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	Update_Command();
	void	Update_KeyMove(void);
	void	Update_PathEffect();
	void	Update_Connect();

/*
 -----------------------------------------------------------------------------------------------------------------------
    指令
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual eRUN_CMD_RESULT_CODE	AddCommand(const AICmd *pCmd);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Idle();
	virtual eRUN_CMD_RESULT_CODE	AddCommand_MoveTo(FLOAT fDestX, FLOAT fDestZ, BOOL bDirectMove = FALSE, BOOL bShowPath = FALSE, BOOL bShowCursor = FALSE);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_StopMove(BOOL bImme = TRUE);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Jump(void);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_UseSkill(int32 idSkill, GUID_t guidTarget, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_DefaultEvent(int32 nEventType, FLOAT fTargetX, FLOAT fTargetY, int32 nTargetId, LPCSTR szTargetName, BOOL bShowPath = FALSE);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_ActiveTripper(int32 nObjID);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Follow(int32 nTargetID);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_PickUp();
	virtual eRUN_CMD_RESULT_CODE	AddCommand_ComposeItem(int32 nPrescriptionID);
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Dead();
	virtual eRUN_CMD_RESULT_CODE	AddCommand_Stall();
	virtual eRUN_CMD_RESULT_CODE	AddCommand_OpenBox();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 执行AI指令 */
	virtual eRUN_CMD_RESULT_CODE	Handle_Command(const AICmd *pCmd);

	/* 是否限制了某个操作的指令 */
	eRUN_CMD_RESULT_CODE			IsLimitCmd(const AICmd *pCmd);

	void				SetCmdForbidTime(uint32 nForbidTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	Do_Move(const GLPos *pNodeList, uint32 nNodeNum, BOOL bDirectMove, int32 nPathShow = AI_MOVE_PATH_SHOW_NOTHING, int32 nMoveType=0);
	virtual BOOL	Do_StopMove();
	virtual BOOL	Do_UseSkill(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	virtual BOOL	Do_ToSpeak(int32 nEventType, int32 nTargetID);
	virtual BOOL	Do_ComposeItem(int32 nAbilityID, int32 PrescriptionID, ObjID_t guidPlatform);
	virtual BOOL	Do_ActiveObj(int32 nTargetID);
	virtual BOOL 	Do_Jump(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
    进入某逻辑状态
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	eRUN_CMD_RESULT_CODE	EnterState_Idle();
	eRUN_CMD_RESULT_CODE	Enter_Move(FLOAT fTargetX, FLOAT fTargetZ, BOOL bDirectMove = FALSE, BOOL bShowPath = FALSE, BOOL bShowCursor = FALSE);
	eRUN_CMD_RESULT_CODE	Enter_StopMove(BOOL bImme);
	eRUN_CMD_RESULT_CODE	Enter_UseSkill(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	eRUN_CMD_RESULT_CODE	Enter_ActiveTripperObj(int32 nTargetID);
	eRUN_CMD_RESULT_CODE	Enter_DefaultEvent(int32 nEvent, FLOAT fTargetX, FLOAT fTargetZ, int32 nTargetID, LPCSTR pName, BOOL bShowPath);
	eRUN_CMD_RESULT_CODE	Enter_Follow(int32 nTargetID);
	eRUN_CMD_RESULT_CODE	Enter_PickUpItem(void);
	eRUN_CMD_RESULT_CODE	Enter_ComposeItem(int32 nPrescriptionID);
	eRUN_CMD_RESULT_CODE	Enter_Dead();
	eRUN_CMD_RESULT_CODE	Enter_Stall();
	eRUN_CMD_RESULT_CODE	Enter_OpenBox();
	eRUN_CMD_RESULT_CODE	Enter_Jump();

/*
 -----------------------------------------------------------------------------------------------------------------------
    向服务器发送命令
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	SendMoveMessage(int32 nStopLogicCount, const GLPos &currPos, int32 nLogicCount, const GLPos *pPathNode, int32 nNodeNum);
	void	SendStopMoveMessage(int32 nStopLogicCount, const GLPos &currPos);
	void	SendUseSkillMessage(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	void	SendComposeItemMessage(int32 idAbility, int32 idPrescription, ObjID_t guidPlatform);
	void	SendDefaultEventMessage(int32 nTargetID);
	void	SendEnterChariotMessage(int32 idTargetObj);	/* 进入战车 */


/*
 -----------------------------------------------------------------------------------------------------------------------
    移动逻辑相关
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL		IsCanMove();
	/* 发送下一个路点 */
	void				SendMoveNode(int32 nNodeIndex, const GLPos &posCurr);
	/* 得到缓冲路点 */
	const MovePathList* GetMovePathBuffer();
	/* 清除缓冲路点 */
	void				CleanUpMovePathBuffer();

	const Ogre::Vector3&		GetPathBeginPos()	
	{ 
		return m_fvPathBeginPos; 
	}

	const Ogre::Vector3&		GetPathFinalPos()	
	{ 
		return m_fvPathFinalPos; 
	}

	// 显示移动终点
	virtual void		ShowMoveFinalPos(const vector2& fvPos, BOOL bDirectMove, int32 nPathShow);
	// 落地事件
	void				OnTouchDown();

protected:
	/* 路点缓冲 */
	void		PushMovePathBuffer(const GLPos *pPosNode, int32 nNodeNum);
	int32		AddMoveLogicCount();
	int32		GetMoveLogicCount();

	void		SetAIStateRefreshFlagByJump(BOOL bSet)	{ m_bNeedRefreshAIStateByJump = bSet; }
	BOOL		IsNeedRefreshAIStateByJump()			{ return m_bNeedRefreshAIStateByJump; }

/*
 -----------------------------------------------------------------------------------------------------------------------
    技能逻辑相关
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 激活普通攻击 */
	OPT_RESULT ActivateDefaultSkill(int32 nSkillID, GUID_t guidTarget, int32 nTargetObjID, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	/* 中断当前所有技能 */
	BOOL	InterruptAllSkill();
	/* 切换目标 */
	void	TargetChanged();
	/* 检测技能保护时间. 聚气引导技能发送后, 需要有保护时间, 用来避免立即被其他操作中断 */
	BOOL	CheckSkillProtectTime();

	BOOL	IsCanDo(AI_COMMAND_MUTEX_TYPE eType);
	BOOL	IsHaveAction();

	void	SetMoveForbidTime(uint32 nForbidTime);
	// 中断AI移动
	void	InterruptMoveAI();


protected:
	/* 设置技能发送保护时间 */
	void	SetSkillSendProtectTime();

/*
 -----------------------------------------------------------------------------------------------------------------------
    键盘移动相关
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 检测可否使用键盘移动 */
	BOOL	CanUseKeyMove();

	/* 停止键盘移动 */
	void	StopKeyMove();


public:
	/* 重置按键状态 */
	void	ResetKeyState();

	/* 设置键盘状态 */
	void	SetKeyState(int32 nKeyId, BOOL bKeyUp);

	/*
	 ===================================================================================================================
	    禁止键盘移动
	 ===================================================================================================================
	 */
	void SetKeyForbid(BOOL bState)
	{
		m_bKeyMoveForbid = bState;
	}

	/*
	 ===================================================================================================================
	    是否键盘移动状态
	 ===================================================================================================================
	 */
	virtual BOOL IsKeyMoveMode(void)
	{
		return m_bKeyMoveMode;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
    路点特效相关
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 更新 */
	void	UpdatePathEffect();

	/* 添加一个路点 */
	void	AddPathEffect(int32 nPathIndex, const vector2 &fvCurrPos, const vector2 &fvTargetPos);

	/* 创建路径特效 */
	void	CreateNewPathLine();

	/* 更新可见特效 */
	void	UpdateVisibleEffect();

	/* 更新特效位置 */
	void	UpdateEffectPos();

	/* 获得一个特效 */
	int32	GetPathEffect();

	/* 得到特效实体ID */
	int32	GetPathEffectID(int32 nEffectIndex);

	/* 设置使用标记 */
	void	SetPathEffectUseFlag(int32 nEffectIndex, BOOL bUsed);

	/* 激活特效 */
	BOOL	ActivatePathEffect(int32 nEffectIndex, const vector2 &fvPos, FLOAT fDir);

	/* 关闭特效 */
	void	ShutdownPathEffect(int32 nEffectIndex);

	/* 清除指定路点的特效 */
	void	ClearPathEffect(int32 nPathIndex);

	/* 修正指定路点的特效, 走过的特效清除掉 */
	void	ModifyPathEffect(int32 nPathIndex, const vector2 &fvTargetPos);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 创建寻路特效 */
	void	CreatePathEffect();

	/* 清除寻路特效 */
	void	RemovePathEffect();

	// 离开场景时保存Obj绑定状态
	void	SaveLeaveSceneObjState();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	struct PathEffect
	{
		BOOL m_bUsed;		/* 使用标记 */
		int32 m_nOjbEffectId; /* OBJID */

		PathEffect()
		{
			m_bUsed = FALSE;
			m_nOjbEffectId = INVALID_ID;
		}
		void SetUsed(BOOL bUsed)
		{
			m_bUsed = bUsed;
		}
	};

	struct PathEffectIndex
	{
		int32 m_nPathEffectIndex; /* PathEffectBuffer 下标 */
		int32 m_nPathNodeIndex;	/* 人物路点下标 */
		vector2 fvPos;
		FLOAT fDir;

		PathEffectIndex()
		{
			m_nPathEffectIndex = INVALID_ID;
			m_nPathNodeIndex = INVALID_ID;
			fDir = 0.f;
		}
	};

	/* 路点特效池 */
	typedef std::vector<PathEffect> PathEffectBuffer;
	PathEffectBuffer m_vPathEffectBuffer;

	/* 路点特效 */
	typedef std::list<PathEffectIndex> PathEffectList;
	PathEffectList m_PathEffectList;

	/* 创建标志 */
	BOOL m_bCreatePathEffect;

	/* 当前移动路径的标示 */
	int32 m_nCurrPathIndex;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 路点缓冲 */
	MovePathList m_MovePathList;

	/* 路点起始位置 */
	Ogre::Vector3 m_fvPathBeginPos;

	/* 路点终点位置 */
	Ogre::Vector3 m_fvPathFinalPos;

	/* 路点请求计数 */
	int32 m_nMovePathRequestCount;

	/* 技能发送时间备份 */
	UINT64 m_uSkillSendTime;

	/* 键盘移动模式 */
	BOOL m_bKeyMoveMode;

	/* 是否限制键盘移动 */
	BOOL m_bKeyMoveForbid;

	/* 按键标记 */
	int32 m_nKeyState;

	/* 移动模式标记 */
	int32 m_nKeyMoveType;
	int32 m_nKeyMoveTypeBackUp;

	// 跳跃落地时更新AI状态
	BOOL  m_bNeedRefreshAIStateByJump;


private:
	AI_STATE m_eMySelfAI;

protected:
	/* 保存压进来的指令， 根据禁止操作时间来判断何时执行 */
	AICmd m_SaveCommand;

	/* 禁止操作的时间 */
	UINT64 m_uCmdForbidTime;

	/* 禁止操作的起始时间 */
	UINT64 m_uCmdForbidStartTime;

	/* 禁止移动时间 */
	UINT64 m_uMoveForbidTime;

	/* 禁止移动起始时间 */
	UINT64 m_uMoveForbidStartTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
    Obj绑定数据
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	struct AI_Control_Data
	{
		int32 nConnectObjID;					/* 绑定Obj */
		AI_CONTROL_RESULT nControlObjFlag;	/* 是否拥有控制权 */

		AI_Control_Data()
		{
			Reset();
		}

		void Reset()
		{
			nConnectObjID = INVALID_ID;
			nControlObjFlag = AI_CONTROL_UNKNOW;
		}
	};

	/* 当前绑定Obj的数据 */
	AI_Control_Data m_ConnectDate;

	/* 将要绑定的Obj的数据 */
	AI_Control_Data m_NextConnectDate;

	// 过程场景时挂接的是否是自己
	BOOL			m_bLastObjConnectedBySelf;

public:
	KAI_Player();
	virtual ~KAI_Player(void);
};	/* class */
