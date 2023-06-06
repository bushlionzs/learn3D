#ifndef __KCHARSTRUCT_H__
#define __KCHARSTRUCT_H__

#pragma once
#include "command/command.h"
#include "CharacterCommon.h"
#include <map>
#include "StructEffect.h"

// ��Ч��
struct ClientEffectData
{
protected:
	String  m_strEffectHandle;// ��Ч���
	BOOL	m_bIsMountEffect;

public:
	ClientEffectData()
	{
		Reset();
	}

	virtual void Reset()
	{
		m_strEffectHandle = "";
		m_bIsMountEffect = FALSE;
	}

	void SetEffectHandle( LPCSTR szHandle, BOOL bIsMountEffect )
	{
		if (szHandle)
		{
			m_strEffectHandle = szHandle;
			m_bIsMountEffect = bIsMountEffect;
		}
	}

	LPCSTR GetEffectHandle()const	{ return m_strEffectHandle.c_str(); }
	BOOL IsMountEffect() const		{ return m_bIsMountEffect; }
};

struct ImpactEffectData :	public ClientEffectData
{
	int32			nSN;					// ��ʾ
	int32			nNumOfLayer;			// �ۻ��Ĳ�����buff�Ĳ����ۻ���	
	int32			nImpactID;				// ��Ӧeffect���еı�ʾid
	int32			nSenderID;				// ������Id	
	UINT64			uBeginTime;				// ����ʱ��	
	BOOL			bLineEffect;			// ���ߵ���Ч
	BOOL			bBullet;				// �ӵ�Ч��
	int32			nSenderLogicCount;		// �������߼�����
	int32			nBulletLogicCount;		// �ӵ��߼�����

	ImpactEffectData( void )
	{
		Reset();
	}

	virtual void Reset( void )
	{
		nSN					= INVALID_ID;
		nNumOfLayer			= 1;		
		nImpactID			= INVALID_ID;
		nSenderID			= INVALID_ID;
		uBeginTime			= INVALID_ID;
		bLineEffect			= FALSE;
		bBullet				= FALSE;
		nSenderLogicCount	= INVALID_ID;
		nBulletLogicCount	= INVALID_ID;
	
		ClientEffectData::Reset();
	}
};


enum eLOGIC_EVENT_TYPE
{
	LOGIC_EVENT_TYPE_INVALID	= -1,	
	LOGIC_EVENT_TYPE_DAMAGE,	/// �˺�

	LOGIC_EVENT_TYPE_NUMBERS
};

struct LogicEventData
{
	UINT64					m_uBeginTime;			// ����Ч�����õĿ�ʼʱ��
	UINT64					m_uRemoveTime;			// ����Ч�����õĳ���ʱ��
	ObjID_t					m_nSenderID;			// �����ߵ�ID
	int32					m_nSenderLogicCount;	// �����ߵ��߼�����
	int32					m_nEventType;			// ���� eLOGIC_EVENT_TYPE
	SDamageInfo			m_damage;				// ����Ч�����������˺���Ϣ

	LogicEventData( void )
	{
		m_uBeginTime	= 0;
		m_uRemoveTime	= 1000;
	}

	~LogicEventData()
	{
	}

	void Initialize(ObjID_t nSenderID, int32 nSenderLogicCount, const SDamageInfo *pDamageInfo)
	{
		m_nSenderID			= nSenderID;
		m_nSenderLogicCount	= nSenderLogicCount;

		m_nEventType		= LOGIC_EVENT_TYPE_DAMAGE;
		m_damage			= *pDamageInfo;
	}	

	void Reset( void )
	{
		m_uBeginTime	= 0;
		m_uRemoveTime	= 1000;

		m_damage.Reset();		
	}
};

typedef std::list< LogicEventData* >		LogicEventList;



// ----------------------------------------------------------------

// �ж��߼�ָ��
class KCharCmdDate_StopLogic : public KObjectCmdDate
{
public:
	KCharCmdDate_StopLogic(void);
	virtual ~KCharCmdDate_StopLogic(void);

	virtual int32 GetCmdType() const 		{ return OBJ_CMD_UNKOWN;	}

	virtual void Clear(void);
	int32 GetLogicCount(void)const		{ return m_nLogicCount;	}

protected:
	void SetLogicCount(int32 nLogicCount)	{ m_nLogicCount = nLogicCount;	}

private:
	int32 m_nLogicCount;		// �߼�����
};

// ----------------------------------------------------------------

// �߼�ָ��
class KCharCmdDate_Logic : public KObjectCmdDate
{
public:

	KCharCmdDate_Logic(void);
	virtual ~KCharCmdDate_Logic(void);

	virtual int32 GetCmdType()const			{ return OBJ_CMD_UNKOWN; }

	virtual void Clear(void);
	virtual BOOL Modify(const KCharCmdDate_StopLogic *pCmd);
	UINT64 GetStartTime(void)const			{ return m_uStartTime;	}
	int32 GetLogicCount(void)const			{ return m_nLogicCount;	}

protected:
	void SetStartTime(uint32 uTime)			{ m_uStartTime = uTime;	}
	void SetLogicCount(int32 nLogicCount)		{ m_nLogicCount = nLogicCount; }
private:
	UINT64		m_uStartTime;		// ��ʼʱ��
	int32			m_nLogicCount;		// �߼�����
};




// ----------------------------------------------------------------
// ����
class KCharCmdDate_Action : public KCharCmdDate_Logic
{
public:
	KCharCmdDate_Action(void);
	virtual ~KCharCmdDate_Action(void);

	virtual int32 GetCmdType()const		{ return OBJ_CMD_ACTION;	}

	bool Initialize(uint32 uStartTime, int32 nLogicCount, int32 nActionID);
	virtual void Clear(void);
	int32 GetActionID(void)const		{ return m_nActionID;	}

private:
	int32			m_nActionID;		// ����ID
};

// ----------------------------------------------------------------
// ��ֹ����
class KCharCmdDate_StopAction : public KCharCmdDate_StopLogic
{
public:
	KCharCmdDate_StopAction(void);
	virtual ~KCharCmdDate_StopAction(void);

	virtual int32 GetCmdType()const	{ return OBJ_CMD_STOP_ACTION;	}

	bool Initialize(int32 nLogicCount, uint32 uEndTime);
	virtual void Clear(void);
	uint32 GetEndTime(void)const	{ return m_uEndTime;	}

private:
	uint32		m_uEndTime;			// ����ʱ��
};


// ----------------------------------------------------------------
// �ƶ�

class KCharCmdDate_Move : public KCharCmdDate_Logic
{
public:
	KCharCmdDate_Move(void);
	virtual ~KCharCmdDate_Move(void);

	virtual int32		GetCmdType()const				{ return OBJ_CMD_MOVE;	}

	bool	Initialize(uint32 uStartTime, int32 nLogicCount, int32 nNodeCount, const GLPos *paposNode, BOOL bServerCommond);

	virtual void		Clear(void);
	virtual BOOL		Modify(const KCharCmdDate_StopLogic *pCmd);

	int32				GetNodeCount(void)const			{ return m_nNodeCount;	}
	const GLPos*		GetNodeList(void)const			{ return m_paposNode;	}
	BOOL				IsServerCommond()				{ return m_bServerCommond; }

	BOOL				IsJumpMove()					{ return m_bJumpMove; }
	void				SetJumpMove()					{ m_bJumpMove = TRUE; }

private:
	int32		m_nNodeCount;		// �ڵ���Ŀ
	GLPos*		m_paposNode;		// �ڵ�����
	BOOL		m_bServerCommond;
	BOOL		m_bJumpMove;
};


// ----------------------------------------------------------------
/** ��ֹ�ƶ�
*/
class KCharCmdDate_StopMove : public KCharCmdDate_StopLogic
{
public:

	KCharCmdDate_StopMove(void);
	virtual ~KCharCmdDate_StopMove(void);

	virtual int32 GetCmdType()const				{ return OBJ_CMD_STOP_MOVE;	}

	bool Initialize(int32 nLogicCount, int32 nEndNodeIndex, const GLPos *pPos, BOOL bArrive);
	virtual void Clear(void);
	int32 GetEndNodeIndex(void)const			{ return m_nEndNodeIndex;	}
	const GLPos *GetEndPos(void)const	{ return &m_posEndPos;	}
	BOOL IsArrive()							{ return m_bArrive; }

private:
	int32			m_nEndNodeIndex;		// ��ֹ�Ľڵ�����(����ܽڵ�Ϊ1����ô��ֹ�ڵ�ֻ����Ϊ0)
	GLPos	m_posEndPos;			// ��ֹ��λ��(����ֹ�Ľڵ���������ĳ��ֵ�����)
	BOOL		m_bArrive;				// ǿ���ж��ƶ�
};

// ----------------------------------------------------------------
/** ��������
*/
#define MAX_SKILL_TARGET_NUM (16)

class KCharCmdDate_SkillSend : public KCharCmdDate_Logic
{
public:

	KCharCmdDate_SkillSend(void);
	virtual ~KCharCmdDate_SkillSend(void);

	virtual int32 GetCmdType()const					{ return OBJ_CMD_SKILL_SEND;	}

	bool Initialize(	uint32 uStartTime,int32 nLogicCount,int32 nMagicID,int32 nTargetNum,
		const ObjID_t* pTargetIDList, const GLPos *pTargetPos,	FLOAT fTargetDir);

	virtual void Clear(void);
	int32 GetMagicID(void)const					{ return m_nMagicID;	}
	int32 GetTargetNum()const						{ return m_nTargetNum;	}
	ObjID_t GetTargetObjID(int32 nIndex)const
	{
		if (nIndex>=0 && nIndex<MAX_SKILL_TARGET_NUM)
		{
			return m_nTargetObjID[nIndex];
		}
		return INVALID_ID;		
	}
	const ObjID_t* GetTargetObjID()const		{ return m_nTargetObjID;	}
	const GLPos *GetTargetPos(void)const	{ return &m_posTarget;	}
	FLOAT GetTargetDir(void)const				{ return m_fTargetDir;	}

private:
	int32			m_nMagicID;									// ����ID
	int32			m_nTargetNum;								// Ŀ������
	ObjID_t		m_nTargetObjID[MAX_SKILL_TARGET_NUM];		// Ŀ���ɫ
	GLPos	m_posTarget;								// Ŀ��λ��
	FLOAT		m_fTargetDir;								// Ŀ�귽��
};

// ----------------------------------------------------------------

// ����

class KCharCmdDate_SkillCharge : public KCharCmdDate_Logic
{
public:

	KCharCmdDate_SkillCharge(void);
	virtual ~KCharCmdDate_SkillCharge(void);

	virtual int32 GetCmdType()const					{ return OBJ_CMD_SKILL_CHARGE;	}

	bool Initialize(	uint32 uStartTime, int32 nLogicCount, int32 nMagicID,
		ObjID_t nTargetID,const GLPos *pTargetPos, FLOAT fTargetDir,uint32 uTotalTime);

	virtual void Clear(void);
	virtual BOOL Modify(const KCharCmdDate_StopLogic *pCmd);
	int32 GetMagicID(void)const					{ return m_nMagicID;	}
	ObjID_t GetTargetObjID(void)const			{ return m_nTargetObjID;	}
	const GLPos *GetTargetPos(void)const	{ return &m_posTarget;	}
	FLOAT GetTargetDir(void)const				{ return m_fTargetDir;	}
	uint32 GetTotalTime(void)const				{ return m_uTotalTime;	}
	uint32 GetEndTime(void)const					{ return m_uEndTime;	}
	BOOL IsFinished(void)const					{ return m_bFinished;	}

private:
	int32			m_nMagicID;			// ����ID
	ObjID_t		m_nTargetObjID;		// Ŀ���ɫ
	GLPos	m_posTarget;		// Ŀ��λ��
	FLOAT		m_fTargetDir;		// Ŀ�귽��
	uint32		m_uTotalTime;		// ��ʱ��
	uint32		m_uEndTime;			// ����ʱ��
	BOOL		m_bFinished;		// ������ʾ
};

// ----------------------------------------------------------------
/** ��������
*/
class KCharCmdDate_SkillChannel : public KCharCmdDate_Logic
{
public:

	KCharCmdDate_SkillChannel(void);
	virtual ~KCharCmdDate_SkillChannel(void);

	virtual int32 GetCmdType()const					{ return OBJ_CMD_SKILL_CHANNEL;	}

	bool Initialize(	uint32 uStartTime, int32 nLogicCount, int32 nMagicID,
		ObjID_t nTargetID,const GLPos *pTargetPos,FLOAT fTargetDir,uint32 uTotalTime);

	virtual void Clear(void);
	virtual BOOL Modify(const KCharCmdDate_StopLogic *pCmd);
	int32 GetMagicID(void)const					{ return m_nMagicID;	}
	ObjID_t GetTargetObjID(void)const			{ return m_nTargetObjID;	}
	const GLPos *GetTargetPos(void)const	{ return &m_posTarget;	}
	FLOAT GetTargetDir(void)const				{ return m_fTargetDir;	}
	uint32 GetTotalTime(void)const				{ return m_uTotalTime;	}
	uint32 GetEndTime(void)const					{ return m_uEndTime;	}	
	BOOL IsFinished(void)const					{ return m_bFinished;	}

private:
	int32			m_nMagicID;			// ����ID
	ObjID_t		m_nTargetObjID;		// Ŀ���ɫ
	GLPos	m_posTarget;		// Ŀ��λ��
	FLOAT		m_fTargetDir;		// Ŀ�귽��
	uint32		m_uTotalTime;		// ��ʱ��
	uint32		m_uEndTime;			// ����ʱ��
	BOOL		m_bFinished;		// ������ʾ
};


// ----------------------------------------------------------------
// �����

class KCharCmdDate_Ability : public KCharCmdDate_Logic
{
public:

	KCharCmdDate_Ability(void);
	virtual ~KCharCmdDate_Ability(void);

	virtual int32 GetCmdType()const				{ return OBJ_CMD_ABILITY;	}

	bool Initialize(uint32 uStartTime, int32 nLogicCount, int32 nAbilityID, int32 nPrescriptionID, ObjID_t nTargetObjID);
	virtual void Clear(void);
	virtual BOOL Modify(const KCharCmdDate_StopLogic *pCmd);
	int32 GetAbilityID(void)const
	{
		return m_nAbilityID;
	}
	int32 GetPrescriptionID(void)const		{ return m_nPrescriptionID;}
	ObjID_t GetTargetObjID(void)const		{ return m_nTargetObjID;}
	uint32 GetEndTime(void)const				{ return m_uEndTime;}
	BOOL IsFinished(void)const				{ return m_bFinished; }

private:
	int32			m_nAbilityID;		// �����ID
	int32			m_nPrescriptionID;	// �䷽ID
	ObjID_t		m_nTargetObjID;		// Ŀ���ɫID
	uint32		m_uEndTime;			// ����ʱ��
	BOOL		m_bFinished;		// ������ʾ
};
// ----------------------------------------------------------------
// ��
class KCharCmdDate_Jump : public KCharCmdDate_Logic
{
public:
	KCharCmdDate_Jump();
	~KCharCmdDate_Jump();

	virtual int32 GetCmdType()const			{ return OBJ_CMD_JUMP;	}

	bool Initialize(int32 nLogicCount);
};





// ----------------------------------------------------------------

struct CharStateData_Idle
{
	UINT64		m_uLastIdleMotionTime;			/// ��һ�������ж�����ʱ��
	UINT64		m_uStartTime;					/// �����߼�����ʼʱ��

	CharStateData_Idle()
	{
		Reset();
	}
	void Reset()
	{
		m_uLastIdleMotionTime = 0;
		m_uStartTime = 0;
	}
};
// ----------------------------------------------------------------
struct CharStateData_Move
{
	int32			m_nCurrentNodeIndex;			/// ��ǰ�ڵ������ֵ
	GLPos	m_posSaveStart;					/// ���浱ǰ����ʼ��
	GLPos	m_posSaveTarget;				/// ���浱ǰ��Ŀ���

	CharStateData_Move()
	{
		Reset();
	}
	void Reset()
	{
		m_nCurrentNodeIndex = 0;
		m_posSaveStart.Clear();
		m_posSaveTarget.Clear();
	}
};
// ----------------------------------------------------------------
struct CharStateData_Charge
{
	int32			m_nSkillID;
	uint32		m_uCurrentTime;					/// ��ǰ����ʱ��

	CharStateData_Charge()
	{
		Reset();
	}
	void Reset()
	{
		m_nSkillID = INVALID_ID;
		m_uCurrentTime = 0;
	}
};
// ----------------------------------------------------------------
struct CharStateData_Channel
{
	int32			m_nSkillID;
	uint32		m_uCurrentTime;					/// ��ǰ����ʱ��

	CharStateData_Channel()
	{
		Reset();
	}
	void Reset()
	{
		m_nSkillID = INVALID_ID;
		m_uCurrentTime = 0;
	}
};
// ----------------------------------------------------------------
struct CharStateData_Send
{
	int32			m_nSaveMagicID;					/// ��ǰ����ID
	int32			m_nActionIndex;					/// Ϊ���ö�����˳�򲥷�
	int32			m_nActionCount;					/// ��������
	uint32			m_uAnimationEndElapseTime;		/// ����ֹͣ��ʱ����
	BOOL			m_bTransferSkill;				// ��漼��

	CharStateData_Send()
	{
		Reset();
	}
	void Reset()
	{
		m_nSaveMagicID = INVALID_ID;
		m_nActionIndex = 0;
		m_nActionCount = 0;
		m_uAnimationEndElapseTime = 0;
		m_bTransferSkill = FALSE;
	}
};	
// ----------------------------------------------------------------
struct CharStateData_Ability
{
	uint32		m_uTotalTime;
	uint32		m_uCurrentTime;

	CharStateData_Ability()
	{
		Reset();
	}
	void Reset()
	{
		m_uTotalTime = 0;
		m_uCurrentTime = 0;
	}
};
// ----------------------------------------------------------------
struct CharStateData_Stall
{
	enum ENUM_STALL_ANIMATION
	{
		STALL_ANIMATION_INVALID	= -1,
		STALL_ANIMATION_SITDOWN,
		STALL_ANIMATION_IDLE,
		STALL_ANIMATION_STANDUP,

		STALL_ANIMATION_NUMBER
	};

	int32			m_nCurrentAnimation;			/// ENUM_STALL_ANIMATION

	CharStateData_Stall()
	{
		Reset();
	}
	void Reset()
	{
		m_nCurrentAnimation = 0;
	}
};
// ----------------------------------------------------------------
struct CharStateData_Dead
{
	int32			m_AttackerId;	// ������
	Ogre::Vector3		m_DeadPos;		// ����λ��
	Ogre::Vector3		m_CurrPos;		// ��ǰλ��
	Ogre::Vector3		m_TarPos;		// Ŀ��λ��
	Ogre::Vector3		m_TarDir;		// Ŀ�귽��
	BOOL		m_bDeadFlyBegin;// ��ʶ���ɶ�����ʼ
	BOOL		m_bDeadFlyEnd;	// ��ʶ���ɶ�������
	BOOL		m_bDeadBegin;	// ��ʶ����������ʼ
	BOOL		m_bDeadEnd;		// ��ʶ������������
	//		int32			m_nCadaverAction;// ʬ�嶯���� Ҫ�����������ƥ��
	BOOL		m_bDeadIsEnd;		// ��ʶ������ �����������
	BOOL		m_bIsDeadFly;		// �ǻ���
	int32			m_nAttackerID;		// ������ID
	FLOAT		m_fBeatFlyDist;		// ���ɾ���

	CharStateData_Dead()
	{
		Reset();
	}

	void Reset()
	{
		m_AttackerId	= INVALID_ID;
		m_bDeadFlyBegin	= FALSE;
		m_bDeadFlyEnd	= TRUE;
		m_bDeadBegin	= FALSE;
		m_bDeadEnd		= TRUE;
		m_bDeadIsEnd	= FALSE;
		m_bIsDeadFly	= FALSE;
		m_nAttackerID	= INVALID_ID;
		m_fBeatFlyDist	= 0.f;
	}
};

// ��������ָ��
KObjectCmdDate* CreateCharCmd(const ObjectCmd *pCmd);


#endif // __KCHARSTRUCT_H__
