#ifndef __KCHARSTRUCT_H__
#define __KCHARSTRUCT_H__

#pragma once
#include "command/command.h"
#include "CharacterCommon.h"
#include <map>
#include "StructEffect.h"

// 特效组
struct ClientEffectData
{
protected:
	String  m_strEffectHandle;// 特效句柄
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
	int32			nSN;					// 标示
	int32			nNumOfLayer;			// 累积的层数，buff的层数累积用	
	int32			nImpactID;				// 对应effect表中的标示id
	int32			nSenderID;				// 发送者Id	
	UINT64			uBeginTime;				// 启动时间	
	BOOL			bLineEffect;			// 连线的特效
	BOOL			bBullet;				// 子弹效果
	int32			nSenderLogicCount;		// 发送者逻辑计数
	int32			nBulletLogicCount;		// 子弹逻辑计数

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
	LOGIC_EVENT_TYPE_DAMAGE,	/// 伤害

	LOGIC_EVENT_TYPE_NUMBERS
};

struct LogicEventData
{
	UINT64					m_uBeginTime;			// 技能效果作用的开始时间
	UINT64					m_uRemoveTime;			// 技能效果作用的持续时间
	ObjID_t					m_nSenderID;			// 攻击者的ID
	int32					m_nSenderLogicCount;	// 攻击者的逻辑计数
	int32					m_nEventType;			// 类型 eLOGIC_EVENT_TYPE
	SDamageInfo			m_damage;				// 机能效果所产生的伤害信息

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

// 中断逻辑指令
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
	int32 m_nLogicCount;		// 逻辑计数
};

// ----------------------------------------------------------------

// 逻辑指令
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
	UINT64		m_uStartTime;		// 起始时间
	int32			m_nLogicCount;		// 逻辑计数
};




// ----------------------------------------------------------------
// 动作
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
	int32			m_nActionID;		// 动作ID
};

// ----------------------------------------------------------------
// 中止动作
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
	uint32		m_uEndTime;			// 结束时间
};


// ----------------------------------------------------------------
// 移动

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
	int32		m_nNodeCount;		// 节点数目
	GLPos*		m_paposNode;		// 节点数据
	BOOL		m_bServerCommond;
	BOOL		m_bJumpMove;
};


// ----------------------------------------------------------------
/** 中止移动
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
	int32			m_nEndNodeIndex;		// 中止的节点索引(如果总节点为1，那么中止节点只可能为0)
	GLPos	m_posEndPos;			// 中止的位置(在中止的节点索引后面的出现的坐标)
	BOOL		m_bArrive;				// 强制中断移动
};

// ----------------------------------------------------------------
/** 法术发招
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
	int32			m_nMagicID;									// 法术ID
	int32			m_nTargetNum;								// 目标数量
	ObjID_t		m_nTargetObjID[MAX_SKILL_TARGET_NUM];		// 目标角色
	GLPos	m_posTarget;								// 目标位置
	FLOAT		m_fTargetDir;								// 目标方向
};

// ----------------------------------------------------------------

// 聚气

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
	int32			m_nMagicID;			// 法术ID
	ObjID_t		m_nTargetObjID;		// 目标角色
	GLPos	m_posTarget;		// 目标位置
	FLOAT		m_fTargetDir;		// 目标方向
	uint32		m_uTotalTime;		// 总时间
	uint32		m_uEndTime;			// 结束时间
	BOOL		m_bFinished;		// 结束标示
};

// ----------------------------------------------------------------
/** 法术引导
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
	int32			m_nMagicID;			// 法术ID
	ObjID_t		m_nTargetObjID;		// 目标角色
	GLPos	m_posTarget;		// 目标位置
	FLOAT		m_fTargetDir;		// 目标方向
	uint32		m_uTotalTime;		// 总时间
	uint32		m_uEndTime;			// 结束时间
	BOOL		m_bFinished;		// 结束标示
};


// ----------------------------------------------------------------
// 生活技能

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
	int32			m_nAbilityID;		// 生活技能ID
	int32			m_nPrescriptionID;	// 配方ID
	ObjID_t		m_nTargetObjID;		// 目标角色ID
	uint32		m_uEndTime;			// 结束时间
	BOOL		m_bFinished;		// 结束标示
};
// ----------------------------------------------------------------
// 跳
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
	UINT64		m_uLastIdleMotionTime;			/// 上一次做休闲动作的时间
	UINT64		m_uStartTime;					/// 待命逻辑的起始时间

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
	int32			m_nCurrentNodeIndex;			/// 当前节点的索引值
	GLPos	m_posSaveStart;					/// 保存当前的起始点
	GLPos	m_posSaveTarget;				/// 保存当前的目标点

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
	uint32		m_uCurrentTime;					/// 当前进度时间

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
	uint32		m_uCurrentTime;					/// 当前进度时间

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
	int32			m_nSaveMagicID;					/// 当前法术ID
	int32			m_nActionIndex;					/// 为了让动作按顺序播放
	int32			m_nActionCount;					/// 动作数量
	uint32			m_uAnimationEndElapseTime;		/// 动画停止的时间间隔
	BOOL			m_bTransferSkill;				// 冲锋技能

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
	int32			m_AttackerId;	// 攻击者
	Ogre::Vector3		m_DeadPos;		// 死亡位置
	Ogre::Vector3		m_CurrPos;		// 当前位置
	Ogre::Vector3		m_TarPos;		// 目标位置
	Ogre::Vector3		m_TarDir;		// 目标方向
	BOOL		m_bDeadFlyBegin;// 标识击飞动作开始
	BOOL		m_bDeadFlyEnd;	// 标识击飞动作结束
	BOOL		m_bDeadBegin;	// 标识死亡动作开始
	BOOL		m_bDeadEnd;		// 标识死亡动作结束
	//		int32			m_nCadaverAction;// 尸体动作， 要和死亡或击飞匹配
	BOOL		m_bDeadIsEnd;		// 标识结束， 动作都完成了
	BOOL		m_bIsDeadFly;		// 是击飞
	int32			m_nAttackerID;		// 攻击者ID
	FLOAT		m_fBeatFlyDist;		// 击飞距离

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

// 创建人物指令
KObjectCmdDate* CreateCharCmd(const ObjectCmd *pCmd);


#endif // __KCHARSTRUCT_H__
