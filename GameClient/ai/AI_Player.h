#pragma once
#include "AI_Base.h"

/*
 * �����ƶ��ķ������� ;
 * 8 4 2 1 �� �� �� ��
 */
#define KMT_INVALID			0x0
#define KMT_DOWN			0x1 /* �� */
#define KMT_RIGHT			0x2 /* �� */
#define KMT_UP				0x4 /* �� */
#define KMT_LEFT			0x8 /* �� */

#define KMT_LU				0xC /* ���� */
#define KMT_RU				0x6 /* ���� */
#define KMT_LD				0x9 /* ���� */
#define KMT_RD				0x3 /* ���� */

#define KMT_UP_OR_DOWN		0x5 /* ���� */
#define KMT_LEFT_OR_RIGHT	0xA /* ���� */

enum AI_CONTROL_RESULT
{
	AI_CONTROL_UNKNOW = -1, 
	AI_CONTROL_FALSE, 
	AI_CONTROL_TRUE, 
};

// �ƶ�·����ʾ
enum AI_MOVE_PATH_SHOW
{
	AI_MOVE_PATH_SHOW_NOTHING = 0,		// ����ʾ
	AI_MOVE_PATH_SHOW_CURSOR,			// ��ʾ���
	AI_MOVE_PATH_SHOW_PATH,				// ��ʾ·��
	AI_MOVE_PATH_SHOW_PATH_AND_CURSOR,	// ��ʾ·���͹��
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
	/* �߼��� */
	virtual KHAN_RETURN_RESULT	Update(void);

	/* ���� */
	virtual void				Reset(void);

	void						DisconnectObj();
	void						ConnectObj(int32 nObjID);

	/* ���ÿ��Ʊ�ʶ */
	void						SetControlOtherObjFlag(BOOL bCanControl, int32 nOtherObjID);

protected:
	void				ConnectObj(KCharacter *pCharacter);

	AI_CONTROL_RESULT	GetControlFlag();
	eRUN_CMD_RESULT_CODE			GetControlResult();

	BOOL				IsMySelfObj();

/*
 -----------------------------------------------------------------------------------------------------------------------
    ĳ�߼�״̬�е�Update��
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	Update_Command();
	void	Update_KeyMove(void);
	void	Update_PathEffect();
	void	Update_Connect();

/*
 -----------------------------------------------------------------------------------------------------------------------
    ָ��
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
	/* ִ��AIָ�� */
	virtual eRUN_CMD_RESULT_CODE	Handle_Command(const AICmd *pCmd);

	/* �Ƿ�������ĳ��������ָ�� */
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
    ����ĳ�߼�״̬
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
    ���������������
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	SendMoveMessage(int32 nStopLogicCount, const GLPos &currPos, int32 nLogicCount, const GLPos *pPathNode, int32 nNodeNum);
	void	SendStopMoveMessage(int32 nStopLogicCount, const GLPos &currPos);
	void	SendUseSkillMessage(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	void	SendComposeItemMessage(int32 idAbility, int32 idPrescription, ObjID_t guidPlatform);
	void	SendDefaultEventMessage(int32 nTargetID);
	void	SendEnterChariotMessage(int32 idTargetObj);	/* ����ս�� */


/*
 -----------------------------------------------------------------------------------------------------------------------
    �ƶ��߼����
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL		IsCanMove();
	/* ������һ��·�� */
	void				SendMoveNode(int32 nNodeIndex, const GLPos &posCurr);
	/* �õ�����·�� */
	const MovePathList* GetMovePathBuffer();
	/* �������·�� */
	void				CleanUpMovePathBuffer();

	const Ogre::Vector3&		GetPathBeginPos()	
	{ 
		return m_fvPathBeginPos; 
	}

	const Ogre::Vector3&		GetPathFinalPos()	
	{ 
		return m_fvPathFinalPos; 
	}

	// ��ʾ�ƶ��յ�
	virtual void		ShowMoveFinalPos(const vector2& fvPos, BOOL bDirectMove, int32 nPathShow);
	// ����¼�
	void				OnTouchDown();

protected:
	/* ·�㻺�� */
	void		PushMovePathBuffer(const GLPos *pPosNode, int32 nNodeNum);
	int32		AddMoveLogicCount();
	int32		GetMoveLogicCount();

	void		SetAIStateRefreshFlagByJump(BOOL bSet)	{ m_bNeedRefreshAIStateByJump = bSet; }
	BOOL		IsNeedRefreshAIStateByJump()			{ return m_bNeedRefreshAIStateByJump; }

/*
 -----------------------------------------------------------------------------------------------------------------------
    �����߼����
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* ������ͨ���� */
	OPT_RESULT ActivateDefaultSkill(int32 nSkillID, GUID_t guidTarget, int32 nTargetObjID, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir);
	/* �жϵ�ǰ���м��� */
	BOOL	InterruptAllSkill();
	/* �л�Ŀ�� */
	void	TargetChanged();
	/* ��⼼�ܱ���ʱ��. �����������ܷ��ͺ�, ��Ҫ�б���ʱ��, �����������������������ж� */
	BOOL	CheckSkillProtectTime();

	BOOL	IsCanDo(AI_COMMAND_MUTEX_TYPE eType);
	BOOL	IsHaveAction();

	void	SetMoveForbidTime(uint32 nForbidTime);
	// �ж�AI�ƶ�
	void	InterruptMoveAI();


protected:
	/* ���ü��ܷ��ͱ���ʱ�� */
	void	SetSkillSendProtectTime();

/*
 -----------------------------------------------------------------------------------------------------------------------
    �����ƶ����
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* ���ɷ�ʹ�ü����ƶ� */
	BOOL	CanUseKeyMove();

	/* ֹͣ�����ƶ� */
	void	StopKeyMove();


public:
	/* ���ð���״̬ */
	void	ResetKeyState();

	/* ���ü���״̬ */
	void	SetKeyState(int32 nKeyId, BOOL bKeyUp);

	/*
	 ===================================================================================================================
	    ��ֹ�����ƶ�
	 ===================================================================================================================
	 */
	void SetKeyForbid(BOOL bState)
	{
		m_bKeyMoveForbid = bState;
	}

	/*
	 ===================================================================================================================
	    �Ƿ�����ƶ�״̬
	 ===================================================================================================================
	 */
	virtual BOOL IsKeyMoveMode(void)
	{
		return m_bKeyMoveMode;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
    ·����Ч���
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* ���� */
	void	UpdatePathEffect();

	/* ���һ��·�� */
	void	AddPathEffect(int32 nPathIndex, const vector2 &fvCurrPos, const vector2 &fvTargetPos);

	/* ����·����Ч */
	void	CreateNewPathLine();

	/* ���¿ɼ���Ч */
	void	UpdateVisibleEffect();

	/* ������Чλ�� */
	void	UpdateEffectPos();

	/* ���һ����Ч */
	int32	GetPathEffect();

	/* �õ���Чʵ��ID */
	int32	GetPathEffectID(int32 nEffectIndex);

	/* ����ʹ�ñ�� */
	void	SetPathEffectUseFlag(int32 nEffectIndex, BOOL bUsed);

	/* ������Ч */
	BOOL	ActivatePathEffect(int32 nEffectIndex, const vector2 &fvPos, FLOAT fDir);

	/* �ر���Ч */
	void	ShutdownPathEffect(int32 nEffectIndex);

	/* ���ָ��·�����Ч */
	void	ClearPathEffect(int32 nPathIndex);

	/* ����ָ��·�����Ч, �߹�����Ч����� */
	void	ModifyPathEffect(int32 nPathIndex, const vector2 &fvTargetPos);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* ����Ѱ·��Ч */
	void	CreatePathEffect();

	/* ���Ѱ·��Ч */
	void	RemovePathEffect();

	// �뿪����ʱ����Obj��״̬
	void	SaveLeaveSceneObjState();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	struct PathEffect
	{
		BOOL m_bUsed;		/* ʹ�ñ�� */
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
		int32 m_nPathEffectIndex; /* PathEffectBuffer �±� */
		int32 m_nPathNodeIndex;	/* ����·���±� */
		vector2 fvPos;
		FLOAT fDir;

		PathEffectIndex()
		{
			m_nPathEffectIndex = INVALID_ID;
			m_nPathNodeIndex = INVALID_ID;
			fDir = 0.f;
		}
	};

	/* ·����Ч�� */
	typedef std::vector<PathEffect> PathEffectBuffer;
	PathEffectBuffer m_vPathEffectBuffer;

	/* ·����Ч */
	typedef std::list<PathEffectIndex> PathEffectList;
	PathEffectList m_PathEffectList;

	/* ������־ */
	BOOL m_bCreatePathEffect;

	/* ��ǰ�ƶ�·���ı�ʾ */
	int32 m_nCurrPathIndex;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* ·�㻺�� */
	MovePathList m_MovePathList;

	/* ·����ʼλ�� */
	Ogre::Vector3 m_fvPathBeginPos;

	/* ·���յ�λ�� */
	Ogre::Vector3 m_fvPathFinalPos;

	/* ·��������� */
	int32 m_nMovePathRequestCount;

	/* ���ܷ���ʱ�䱸�� */
	UINT64 m_uSkillSendTime;

	/* �����ƶ�ģʽ */
	BOOL m_bKeyMoveMode;

	/* �Ƿ����Ƽ����ƶ� */
	BOOL m_bKeyMoveForbid;

	/* ������� */
	int32 m_nKeyState;

	/* �ƶ�ģʽ��� */
	int32 m_nKeyMoveType;
	int32 m_nKeyMoveTypeBackUp;

	// ��Ծ���ʱ����AI״̬
	BOOL  m_bNeedRefreshAIStateByJump;


private:
	AI_STATE m_eMySelfAI;

protected:
	/* ����ѹ������ָ� ���ݽ�ֹ����ʱ�����жϺ�ʱִ�� */
	AICmd m_SaveCommand;

	/* ��ֹ������ʱ�� */
	UINT64 m_uCmdForbidTime;

	/* ��ֹ��������ʼʱ�� */
	UINT64 m_uCmdForbidStartTime;

	/* ��ֹ�ƶ�ʱ�� */
	UINT64 m_uMoveForbidTime;

	/* ��ֹ�ƶ���ʼʱ�� */
	UINT64 m_uMoveForbidStartTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
    Obj������
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	struct AI_Control_Data
	{
		int32 nConnectObjID;					/* ��Obj */
		AI_CONTROL_RESULT nControlObjFlag;	/* �Ƿ�ӵ�п���Ȩ */

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

	/* ��ǰ��Obj������ */
	AI_Control_Data m_ConnectDate;

	/* ��Ҫ�󶨵�Obj������ */
	AI_Control_Data m_NextConnectDate;

	// ���̳���ʱ�ҽӵ��Ƿ����Լ�
	BOOL			m_bLastObjConnectedBySelf;

public:
	KAI_Player();
	virtual ~KAI_Player(void);
};	/* class */
