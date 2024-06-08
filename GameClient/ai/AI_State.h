

#ifndef _AI_STATE_H_
#define _AI_STATE_H_

enum AI_STATE
{
	AI_STATE_INVALID		= -1,
	AI_STATE_IDLE,					// 空闲
	AI_STATE_MOVE,					// 移动
	AI_STATE_USE_SKILL,				// 技能使用
	AI_STATE_ACTIVE_OBJ,			// 对TripperObj激活
	AI_STATE_TOSPEAK,				// 对话事件
	AI_STATE_DEAD,					// 死亡
	AI_STATE_FOLLOW,				// 跟随
	AI_STATE_COMPOSE_ITEM,			// 生活技能
	AI_STATE_STALL,					// 摆摊
	AI_STATE_TREASUREBOX,			// 开宝箱

	AI_STATE_NUMBERS
};

// 操作互斥
enum AI_COMMAND_MUTEX_TYPE
{
	ACMT_UNKNOW = -1,
	ACMT_IDLE,						// 休闲
	ACMT_MOVE,						// 移动
	ACMT_USE_SKILL,					// 技能使用
	ACMT_ACTIVE_OBJ,				// 对TripperObj激活
	ACMT_TOSPEAK,					// 对话事件
	ACMT_DEAD,						// 死亡
	ACMT_FOLLOW,					// 跟随
	ACMT_COMPOSE_ITEM,				// 生活技能
	ACMT_STALL,						// 摆摊
	ACMT_TREASUREBOX,				// 开宝箱
	ACMT_JUMP,						// 跳跃
	ACMT_USE_ITEM,					// 使用物品	
	ACMT_MOUNT,						// 上马
	ACMT_DISMOUNT,					// 下马
	ACMT_CHANGE_SPEED,				// 走跑切换

	ACMT_MAX_NUM,
};

enum AI_ACTIVE_RESULT
{
	AI_RES_FAILURE			= 0,	// AI状态执行失败
	AI_RES_OK,						// AI状态执行成功, 并且切换状态
	AI_RES_OK_AND_SHUTDOWN,			// AI状态执行成功, 并且关闭所有状态
	AI_RES_OK_BUT_NO_CHANGE,		// AI状态执行成功, 但不切换状态
};

enum AI_MOVE_TYPE
{
	AI_MOVE_TYPE_NORMAL = 0,
	AI_MOVE_TYPE_JUMP,
	AI_MOVE_TYPE_REFRESH,
};

class	KCharacter;
class	KAI;
struct AICmd;
/*
 =======================================================================================================================
    基类
 =======================================================================================================================
 */
class	KAIState
{
	friend class	KAI;

public:
	KAIState(KAI *pAI);
	virtual~KAIState()	{}

	virtual int32					GetStateType() const			{ return AI_STATE_INVALID; }
	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd)	{ return AI_RES_OK; }
	virtual void					OnStateShutdown()				{}
	virtual KHAN_RETURN_RESULT		Update(void)					{ return KRR_SUCCEED; }
	virtual void					Release(void)					{}

	virtual	BOOL					RefreshAIStateByJump()			{ return FALSE; }

public:
	virtual void					TargetChanged(int32 nTargetID)	{}
	// 跳跃
	virtual OPT_RESULT				Jump()							{ return OR_FAILURE; }
	// 落地事件
	virtual void					OnTouchDown()					{}


	// 中断移动标识
	virtual void					InterruptMove()					{}
	virtual BOOL					IsInterruptMove()				{ return FALSE; }
	
	/* 互斥 */
	BOOL							GetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex);
	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType() = 0;

protected:
	KAI*							GetAI()							{ return m_pAI; }
	/* 检测进入当前状态后的时间 */
	BOOL							CheckCharStateTime(UINT64 uCheckTime);
	/* 检索移动的时间间隔 */
	BOOL							CheckMoveByTime(UINT64 uDeltaTime);
	/* 设置互斥状态 */
	void							SetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex);

private:
	KAI	*	m_pAI;
	/* 互斥标识 */
	SFlag64	m_bMutexFlag;
};



/*
=======================================================================================================================
	休闲
=======================================================================================================================
*/
class KAIState_Idle :
	public KAIState
{
	friend class	KAI;

public:
	KAIState_Idle(KAI *pAI);
	virtual~KAIState_Idle()	{}

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()			{ return ACMT_IDLE; };
	virtual int32					GetStateType() const			{ return AI_STATE_IDLE;	}
	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd)	{ return AI_RES_OK_AND_SHUTDOWN;	}
	virtual KHAN_RETURN_RESULT		Update(void)					{ return KRR_FAILED; }
};

/*
 =======================================================================================================================
    移动
 =======================================================================================================================
 */
class KAIState_Move :
	public KAIState
{
	friend class	KAI;

public:
	KAIState_Move(KAI *pAI);
	virtual ~KAIState_Move();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()			{ return ACMT_MOVE; }
	virtual int32					GetStateType() const			{ return AI_STATE_MOVE;	}
	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd);
	virtual void					OnStateShutdown();
	virtual KHAN_RETURN_RESULT		Update();

	virtual	BOOL					RefreshAIStateByJump();

	// 跳跃
	virtual OPT_RESULT				Jump();
	// 落地事件
	virtual void					OnTouchDown();

	// 中断移动标识
	virtual void					InterruptMove()					{ m_bIsInterruptMove = TRUE; }
	BOOL							IsInterruptMove()				{ return m_bIsInterruptMove; }

protected:
	struct MoveToParam
	{
		FLOAT	fTargetX;
		FLOAT	fTargetZ;
		FLOAT	fModifyDist;
		BOOL	bDirectMove;
		int32	nPathShow;
		int32	nMoveType;

		MoveToParam()
		{
			fTargetX		= 0.f;
			fTargetZ		= 0.f;
			fModifyDist		= 0.f;
			bDirectMove		= FALSE;
			nPathShow		= 0;
			nMoveType		= AI_MOVE_TYPE_NORMAL;
		}
	};

	OPT_RESULT						MoveTo(const MoveToParam& param);
	OPT_RESULT						StopMove();
	OPT_RESULT						IsCanMove();
	BOOL							IsMoving();

	// 得到跳跃落地位置
	Ogre::Vector2							GetJumpToPos(const Ogre::Vector2& fvTargetPos);
	// 跳跃逻辑
	OPT_RESULT						DoJump();

protected:
	struct MoveParam
	{
		FLOAT	fTargetX;
		FLOAT	fTargetZ;
		FLOAT	fModifyDist;
		BOOL	bDirectMove;
		BOOL	bStopMove;
		int32	nPathShow;

		MoveParam()
		{
			Reset();
		}
		void Reset()
		{
			fTargetX	= 0.f;
			fTargetZ	= 0.f;
			fModifyDist = 0.f;
			bDirectMove = FALSE;
			bStopMove	= FALSE;
			nPathShow	= 0;
		}
	};
	MoveParam	m_paramMove;
	
private:
	// 中断移动标识
	BOOL		m_bIsInterruptMove;
	// 起跳位置
	Ogre::Vector3		m_fvJumpBeginPos;
	// 是否在最后的路点上起跳
	BOOL		m_bJumpInFinalNode;
};

/*
 =======================================================================================================================
    战斗
 =======================================================================================================================
 */
class KAIState_CombatState :
	public KAIState_Move
{
	friend class	KAI;

public:
	KAIState_CombatState(KAI *pAI);
	virtual ~KAIState_CombatState();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()	{ return ACMT_USE_SKILL; };
	virtual int32					GetStateType() const	{ return AI_STATE_USE_SKILL; }
	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd);
	virtual void					OnStateShutdown();
	virtual KHAN_RETURN_RESULT		Update();

	virtual	BOOL					RefreshAIStateByJump();
	virtual void					TargetChanged(int32 nTargetID);

protected:
	struct SkillParam
	{
		int32	nSkillID;
		int32	nSkillLevel;
		int32	nTargetID;
		GUID_t	guidTarget;
		FLOAT	fTargetX;
		FLOAT	fTargetZ;
		FLOAT	fDir;
		FLOAT	fMaxRange;
		FLOAT	fMinRange;

		SkillParam()
		{
			Reset();
		}

		void Reset()
		{
			nSkillID = INVALID_ID;
			nSkillLevel = 0;
			nTargetID = INVALID_ID;
			guidTarget = INVALID_ID;
			fTargetX = 0.f;
			fTargetZ = 0.f;
			fDir = 0.f;
			fMaxRange = 0.f;
			fMinRange = 0.f;
		}
	};

	OPT_RESULT		UseSkill(SkillParam &skillParam);

	/* 关闭当前的技能 */
	void			DisableAutoSkill(BOOL bSendMessage = FALSE);
	void			DisableCurrSkill();


private:
	/* 人物点选攻击逻辑 */
	OPT_RESULT		AttackLogic(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, const vector3& fvTargetPos, vector3& fvPrevPos, FLOAT fDir, FLOAT fMaxRange);
	/* 使用目标类型技能 */
	OPT_RESULT		UseSkill_Target(SkillParam &skillParam);
	/* 使用方向类型技能 */
	OPT_RESULT		UseSkill_Dir(SkillParam &skillParam);
	/* 使用坐标类型技能 */
	OPT_RESULT		UseSkill_Pos(SkillParam &skillParam);
	/* 检测距离 */
	BOOL			CheckDistance(const vector3 &fvPos1, const vector3 &fvPos2, FLOAT fRange);
	/* 检测冲锋距离 */
	BOOL			CheckOnrushDistance(const vector3 &fvPos1, const vector3 &fvPos2);
	/* 技能中断移动逻辑 */
	OPT_RESULT		InterruptMoveBySkill(const _DBC_SPELL_DATA *pSkillData);
	/* 保存技能数据 */
	OPT_RESULT		SaveSkillParam(SkillParam &skillParam);
	/* 检测技能是否对目标有效 */
	BOOL			CheckSkillByTarget(int32 nSkillID, int32 nTargetID);
	/* 判断现在是否可以使用技能 */
	OPT_RESULT		IsCanUseSkill(SkillParam &skillParam);
	/* 检测自我施法 */
	BOOL			IsUseToMySelf(SkillParam &skillParam);
	// 转移类技能修正
	OPT_RESULT		TransferModify(SkillParam &skillParam);

private:
	struct BHVParam_UseSkill
	{
		SkillID_t	m_nCurrSkillID; /* 普通技能 */
		SkillID_t	m_nAutoSkillID; /* 自动技能 */
		int32		m_nTargetID;
		GUID_t		m_guidTarget;
		vector3		m_fvTargetPos;
		FLOAT		m_fDir;
		vector3		m_fvPrevTargetPos;
		FLOAT		m_fMaxRange;
		FLOAT		m_fMinRange;

		BHVParam_UseSkill()
		{
			Reset();
		}

		const BHVParam_UseSkill &operator=(const BHVParam_UseSkill &in)
		{
			if(this != &in)
			{
				m_nCurrSkillID	= in.m_nCurrSkillID;
				m_nAutoSkillID	= in.m_nAutoSkillID;
				m_nTargetID		= in.m_nTargetID;
				m_guidTarget	= in.m_guidTarget;
				m_fvTargetPos	= in.m_fvTargetPos;
				m_fDir			= in.m_fDir;
				m_fvPrevTargetPos = in.m_fvPrevTargetPos;
				m_fMaxRange		= in.m_fMaxRange;
				m_fMinRange		= in.m_fMinRange;
			}

			return *this;
		}

		void Reset(void)
		{
			m_nCurrSkillID = INVALID_ID;
			m_nAutoSkillID = INVALID_ID;
			m_nTargetID = INVALID_ID;
			m_guidTarget = INVALID_ID;
			m_fDir = 0.0f;
			m_fMaxRange = 0.f;
			m_fMinRange = 0.f;
		}

		// 当前技能是否有效
		BOOL IsCurrSkillEnable()
		{
			return(INVALID_ID == m_nCurrSkillID) ? (FALSE) : (TRUE);
		}

		// 普通技能是否有效
		BOOL IsAutoSkillEnalbe()
		{
			return(INVALID_ID == m_nAutoSkillID) ? (FALSE) : (TRUE);
		}


		void DisableCurrSkill()
		{
			m_nCurrSkillID = INVALID_ID;
		}


		void DisableAutoSkill()
		{
			m_nAutoSkillID = INVALID_ID;
		}
	};

	SkillParam			m_paramSkill;
	BHVParam_UseSkill	m_paramBHV_UseSkill;
};


/*
 =======================================================================================================================
    事件基类
 =======================================================================================================================
 */
class KAIState_ToEvent :
	public KAIState_Move
{
	friend class	KAI;

public:
	KAIState_ToEvent(KAI *pAI);
	virtual ~KAIState_ToEvent();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()		{ return ACMT_UNKNOW; };
	virtual int32					GetStateType() const		{ return AI_STATE_INVALID; }

	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd);
	virtual void					OnStateShutdown();

	virtual KHAN_RETURN_RESULT		Update();
	virtual	BOOL					RefreshAIStateByJump();

protected:
	virtual AI_ACTIVE_RESULT		DefaultEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow);
	virtual BOOL					CheckDistance(int32	nEventType,int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName) = 0;
	virtual BOOL					DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName) = 0;
	virtual BOOL					GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow) = 0;
	virtual BOOL					CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow) = 0;
	virtual BOOL					RecheckTargetPos() = 0;

protected:
	struct BHVParam_DefaultEvent
	{
		int32		m_nTargetID;
		vector3		m_fvTargetPos;
		vector3		m_fvPrevTargetPos;
		int32		m_nEventType;
		STRING		m_sNpcName;
		FLOAT		m_OperationDist;
		int32		m_nPathShow;

		BHVParam_DefaultEvent()
		{
			Reset();
		}

		void Reset()
		{
			m_nTargetID		= INVALID_ID;
			m_nEventType	= INVALID_ID;
			m_sNpcName		= "";
			m_OperationDist = 0.f;
			m_nPathShow		= 0;
		}
	};

	BHVParam_DefaultEvent	m_paramBHV_DefaultEvent;
};

/*
 =======================================================================================================================
    对话事件
 =======================================================================================================================
 */
class KAIState_ToSpeak :
	public KAIState_ToEvent
{
	friend class	KAI;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	KAIState_ToSpeak(KAI *pAI);
	virtual ~KAIState_ToSpeak();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()	{ return ACMT_TOSPEAK; };
	virtual int32					GetStateType() const	{ return AI_STATE_TOSPEAK; }

protected:
	virtual BOOL	CheckDistance(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName);
	virtual BOOL	DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName);
	virtual BOOL	GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow);
	virtual BOOL	CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow);
	virtual BOOL	RecheckTargetPos();
};


/*
 =======================================================================================================================
    合成物品事件
 =======================================================================================================================
 */
class KAIState_ComposeItem :
	public KAIState_ToEvent
{
	friend class	KAI;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	KAIState_ComposeItem(KAI *pAI);
	virtual ~KAIState_ComposeItem();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()	{ return ACMT_COMPOSE_ITEM; };
	virtual int32					GetStateType() const	{ return AI_STATE_COMPOSE_ITEM;	}

protected:

	virtual BOOL DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName);
	virtual BOOL CheckDistance(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)	{ return TRUE;	}	
	virtual BOOL GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)	{ return FALSE;	}
	virtual BOOL CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)	{ return TRUE;	}
	virtual BOOL RecheckTargetPos()	{ return FALSE;	}
};

/*
 =======================================================================================================================
    Obj激活事件。 如采集, 拾取物品等
 =======================================================================================================================
 */
class KAIState_ActiveObj :
	public KAIState_ToEvent
{
	friend class	KAI;

public:
	KAIState_ActiveObj(KAI *pAI);
	virtual ~KAIState_ActiveObj();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()	{ return ACMT_ACTIVE_OBJ; };
	virtual int32					GetStateType() const	{ return AI_STATE_ACTIVE_OBJ; }

protected:
	virtual BOOL	CheckDistance(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName);
	virtual BOOL	DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName);
	virtual BOOL	GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow);
	virtual BOOL	CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow);

	virtual BOOL RecheckTargetPos()	{ return TRUE;	}
};

/*
 =======================================================================================================================
    跟随
 =======================================================================================================================
 */
class KAIState_Follow :
	public KAIState_Move
{
	friend class	KAI;

public:
	KAIState_Follow(KAI *pAI);
	virtual ~KAIState_Follow();

	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType()	{ return ACMT_FOLLOW; };
	virtual int32					GetStateType() const	{ return AI_STATE_FOLLOW; }

public:
	virtual AI_ACTIVE_RESULT		OnStateActive(const AICmd &cmd);
	virtual void					OnStateShutdown();

	virtual KHAN_RETURN_RESULT		Update();
	virtual	BOOL					RefreshAIStateByJump();

protected:
	BOOL	Follow(int32 nTargetID);

private:
	struct BHVParam_Follow
	{
		ObjID_t m_nTargetID;
		vector3 m_fvPrevPos;

		BHVParam_Follow()
		{
			Reset();
		}
		void Reset()
		{
			m_nTargetID = INVALID_ID;
			m_fvPrevPos.x = 0.f;
			m_fvPrevPos.y = 0.f;
			m_fvPrevPos.z = 0.f;
		}
	};
	BHVParam_Follow	m_paramBHV_Follow;
};

/*
 =======================================================================================================================
    死亡
 =======================================================================================================================
 */
class KAIState_Dead :
	public KAIState
{
	friend class	KAI;

public:
	KAIState_Dead(KAI *pAI);
	virtual ~KAIState_Dead();

	virtual AI_COMMAND_MUTEX_TYPE GetCommandMutexType() { return ACMT_DEAD; };

	virtual int32 GetStateType() const
	{
		return AI_STATE_DEAD;
	}

public:
	virtual AI_ACTIVE_RESULT	OnStateActive(const AICmd &cmd);
	virtual void				OnStateShutdown();

	virtual KHAN_RETURN_RESULT	Update();
};

/*
 =======================================================================================================================
    摆摊
 =======================================================================================================================
 */
class KAIState_Stall :
	public KAIState_Move
{
	friend class	KAI;

public:
	KAIState_Stall(KAI *pAI);
	virtual ~KAIState_Stall();

	virtual AI_COMMAND_MUTEX_TYPE GetCommandMutexType() { return ACMT_STALL; };

	virtual int32 GetStateType() const
	{
		return AI_STATE_STALL;
	}

public:
	virtual AI_ACTIVE_RESULT	OnStateActive(const AICmd &cmd);
	virtual void				OnStateShutdown();

	virtual KHAN_RETURN_RESULT	Update();
};

/*
 =======================================================================================================================
    开宝箱
 =======================================================================================================================
 */
class KAIState_TreasureBox :
	public KAIState_Move
{
	friend class	KAI;

public:
	KAIState_TreasureBox(KAI *pAI);
	virtual ~KAIState_TreasureBox();

	virtual AI_COMMAND_MUTEX_TYPE GetCommandMutexType() { return ACMT_TREASUREBOX; };

	virtual int32 GetStateType() const
	{
		return AI_STATE_TREASUREBOX;
	}

public:
	virtual AI_ACTIVE_RESULT	OnStateActive(const AICmd &cmd);
	virtual void				OnStateShutdown();

	virtual KHAN_RETURN_RESULT	Update();
};

/*
 =======================================================================================================================
    状态列表
 =======================================================================================================================
 */
class	AISStateList
{

public:
	AISStateList();
	~AISStateList();

	void		InitStateList(KAI *pAI);

	KAIState	*GetStateInstance(AI_STATE eState) const;

protected:
	void	RegisterState(KAIState *pState);
	void	ReleaseState(void);

private:
	KAIState	*m_pStateList[ACMT_MAX_NUM];
};
#endif 
