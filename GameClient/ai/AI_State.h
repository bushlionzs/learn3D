

#ifndef _AI_STATE_H_
#define _AI_STATE_H_

enum AI_STATE
{
	AI_STATE_INVALID		= -1,
	AI_STATE_IDLE,					// ����
	AI_STATE_MOVE,					// �ƶ�
	AI_STATE_USE_SKILL,				// ����ʹ��
	AI_STATE_ACTIVE_OBJ,			// ��TripperObj����
	AI_STATE_TOSPEAK,				// �Ի��¼�
	AI_STATE_DEAD,					// ����
	AI_STATE_FOLLOW,				// ����
	AI_STATE_COMPOSE_ITEM,			// �����
	AI_STATE_STALL,					// ��̯
	AI_STATE_TREASUREBOX,			// ������

	AI_STATE_NUMBERS
};

// ��������
enum AI_COMMAND_MUTEX_TYPE
{
	ACMT_UNKNOW = -1,
	ACMT_IDLE,						// ����
	ACMT_MOVE,						// �ƶ�
	ACMT_USE_SKILL,					// ����ʹ��
	ACMT_ACTIVE_OBJ,				// ��TripperObj����
	ACMT_TOSPEAK,					// �Ի��¼�
	ACMT_DEAD,						// ����
	ACMT_FOLLOW,					// ����
	ACMT_COMPOSE_ITEM,				// �����
	ACMT_STALL,						// ��̯
	ACMT_TREASUREBOX,				// ������
	ACMT_JUMP,						// ��Ծ
	ACMT_USE_ITEM,					// ʹ����Ʒ	
	ACMT_MOUNT,						// ����
	ACMT_DISMOUNT,					// ����
	ACMT_CHANGE_SPEED,				// �����л�

	ACMT_MAX_NUM,
};

enum AI_ACTIVE_RESULT
{
	AI_RES_FAILURE			= 0,	// AI״ִ̬��ʧ��
	AI_RES_OK,						// AI״ִ̬�гɹ�, �����л�״̬
	AI_RES_OK_AND_SHUTDOWN,			// AI״ִ̬�гɹ�, ���ҹر�����״̬
	AI_RES_OK_BUT_NO_CHANGE,		// AI״ִ̬�гɹ�, �����л�״̬
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
    ����
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
	// ��Ծ
	virtual OPT_RESULT				Jump()							{ return OR_FAILURE; }
	// ����¼�
	virtual void					OnTouchDown()					{}


	// �ж��ƶ���ʶ
	virtual void					InterruptMove()					{}
	virtual BOOL					IsInterruptMove()				{ return FALSE; }
	
	/* ���� */
	BOOL							GetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex);
	virtual AI_COMMAND_MUTEX_TYPE	GetCommandMutexType() = 0;

protected:
	KAI*							GetAI()							{ return m_pAI; }
	/* �����뵱ǰ״̬���ʱ�� */
	BOOL							CheckCharStateTime(UINT64 uCheckTime);
	/* �����ƶ���ʱ���� */
	BOOL							CheckMoveByTime(UINT64 uDeltaTime);
	/* ���û���״̬ */
	void							SetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex);

private:
	KAI	*	m_pAI;
	/* �����ʶ */
	SFlag64	m_bMutexFlag;
};



/*
=======================================================================================================================
	����
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
    �ƶ�
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

	// ��Ծ
	virtual OPT_RESULT				Jump();
	// ����¼�
	virtual void					OnTouchDown();

	// �ж��ƶ���ʶ
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

	// �õ���Ծ���λ��
	Ogre::Vector2							GetJumpToPos(const Ogre::Vector2& fvTargetPos);
	// ��Ծ�߼�
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
	// �ж��ƶ���ʶ
	BOOL		m_bIsInterruptMove;
	// ����λ��
	Ogre::Vector3		m_fvJumpBeginPos;
	// �Ƿ�������·��������
	BOOL		m_bJumpInFinalNode;
};

/*
 =======================================================================================================================
    ս��
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

	/* �رյ�ǰ�ļ��� */
	void			DisableAutoSkill(BOOL bSendMessage = FALSE);
	void			DisableCurrSkill();


private:
	/* �����ѡ�����߼� */
	OPT_RESULT		AttackLogic(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, const vector3& fvTargetPos, vector3& fvPrevPos, FLOAT fDir, FLOAT fMaxRange);
	/* ʹ��Ŀ�����ͼ��� */
	OPT_RESULT		UseSkill_Target(SkillParam &skillParam);
	/* ʹ�÷������ͼ��� */
	OPT_RESULT		UseSkill_Dir(SkillParam &skillParam);
	/* ʹ���������ͼ��� */
	OPT_RESULT		UseSkill_Pos(SkillParam &skillParam);
	/* ������ */
	BOOL			CheckDistance(const vector3 &fvPos1, const vector3 &fvPos2, FLOAT fRange);
	/* �������� */
	BOOL			CheckOnrushDistance(const vector3 &fvPos1, const vector3 &fvPos2);
	/* �����ж��ƶ��߼� */
	OPT_RESULT		InterruptMoveBySkill(const _DBC_SPELL_DATA *pSkillData);
	/* ���漼������ */
	OPT_RESULT		SaveSkillParam(SkillParam &skillParam);
	/* ��⼼���Ƿ��Ŀ����Ч */
	BOOL			CheckSkillByTarget(int32 nSkillID, int32 nTargetID);
	/* �ж������Ƿ����ʹ�ü��� */
	OPT_RESULT		IsCanUseSkill(SkillParam &skillParam);
	/* �������ʩ�� */
	BOOL			IsUseToMySelf(SkillParam &skillParam);
	// ת���༼������
	OPT_RESULT		TransferModify(SkillParam &skillParam);

private:
	struct BHVParam_UseSkill
	{
		SkillID_t	m_nCurrSkillID; /* ��ͨ���� */
		SkillID_t	m_nAutoSkillID; /* �Զ����� */
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

		// ��ǰ�����Ƿ���Ч
		BOOL IsCurrSkillEnable()
		{
			return(INVALID_ID == m_nCurrSkillID) ? (FALSE) : (TRUE);
		}

		// ��ͨ�����Ƿ���Ч
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
    �¼�����
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
    �Ի��¼�
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
    �ϳ���Ʒ�¼�
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
    Obj�����¼��� ��ɼ�, ʰȡ��Ʒ��
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
    ����
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
    ����
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
    ��̯
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
    ������
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
    ״̬�б�
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
