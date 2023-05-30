/*$T MapServer/Server/AI/Behavior_Player.h GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __HUMANAI_H__
#define __HUMANAI_H__

#include "TypeDefine.h"
#include "Behavior_Character.h"

class	Player;
struct SDiePenaltyInfo;

class Behavior_Player :
	public Behavior_Character
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Behavior_Player(void);
	virtual		~Behavior_Player(void);

	virtual BOOL	Init(Character *pCharacter);
	virtual void	Clear(void);

	virtual void	Relive(int32 nResultCode);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//死亡状态下的心跳 add by wujianping
	virtual void	Dead_Logic(uint32 uTime);
	//组队跟随状态下的心跳 add by wujianping
	virtual void	TeamFollow_Logic(uint32 uTime);
	//战斗状态下的心跳 add by wujianping
	virtual void	Combat_Logic(uint32 uTime);
	//巡逻状态下的心跳（只有婚礼用到巡逻状态） add by wujianping
	virtual void	Patrol_Logic(uint32 uTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//被打死时的逻辑处理函数 add by wujianping
	virtual void	Event_OnDie(Object *pKiller = NULL);
	//被使用技能的逻辑处理函数 add by wujianping
	virtual void	Event_OnBeSpell(Character *pCharacter, int32 nGoodEffect);
	//被伤害的逻辑处理函数 add by wujianping
	virtual void	Event_OnDamage(int32 nDamage, Character *pAttacker);
	//被治疗的逻辑处理函数 add by wujianping
	virtual void	Event_OnBeHeal(Character *pCharacter, int32 nHeal);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//执行死亡复活 nResultCode为复活方式 add by wujianping
	OPT_RESULT PushCmd_DieResult(int32 nResultCode);
	//被召唤 nResultCode为同意或者拒绝 add by wujianping
	OPT_RESULT PushCmd_CallOfResult(int32 nResultCode);
	//执行跳跃命令 add by wujianping
	OPT_RESULT PushCmd_Jump(int32 nLogicCount);
	//执行切换心情命令 add by wujianping
	OPT_RESULT PushCmd_MoodState(int32 nMoodState);
	//进入空闲状态 add by wujianping
	OPT_RESULT PushCmd_Idle(void);
	//进入摆摊状态 add by wujianping
	OPT_RESULT PushCmd_Stall(void);
	//进入使用生活技能状态 add by wujianping
	OPT_RESULT PushCmd_UseAbility(void);
	//任务相关 add by wujianping
	OPT_RESULT PushCmd_DefaultEvent(ObjID_t idNPC);
	//任务相关 add by wujianping
	OPT_RESULT PushCmd_EventRequest(ObjID_t idNPC, ScriptID_t idEvent, int32 exIndex);
	//执行移动命令 add by wujianping
	OPT_RESULT PushCmd_Move
		(
			int32		nHandleID,
			uint16		wNumTargetPos,
			const GLPos *paTargetPos,
			int32		nStopLogicCount = INVALID_ID,
			const GLPos *paCurPos = NULL,
			ObjID_t		nSenderID = INVALID_ID
		);
	//执行使用战斗技能命令 add by wujianping
	OPT_RESULT PushCmd_UseSpell
		(
			ObjID_t idSkill,
			ObjID_t idTarget,
			float	fTargetX,
			float	fTargetZ,
			float	fDir,
			GUID_t	guidTarget,
			int32	iHurtDelayTime,
			BOOL	bChildSkill = FALSE
		);
	//执行使用物品命令 add by wujianping
	OPT_RESULT PushCmd_UseItem
		(
			ID_t		nBagIndex,
			ObjID_t		nTargetObj,
			const GLPos &posTarget,
			SHorseGuid&guidTargetPet,
			ID_t		nTargetItem
		);
	//执行接受任务命令 add by wujianping
	OPT_RESULT PushCmd_QuestAccept(ObjID_t idNPC, ScriptID_t idQuestScript);
	//执行放弃任务命令 add by wujianping
	OPT_RESULT PushCmd_QuestAbandon(ScriptID_t idQuestScript);
	//执行拒绝任务命令 add by wujianping
	OPT_RESULT PushCmd_QuestRefuse(ObjID_t idNPC, ScriptID_t idQuestScript);
	//执行提交任务命令 add by wujianping
	OPT_RESULT PushCmd_QuestSubmit(ObjID_t idNPC, ScriptID_t idQuestScript, uint32 uSelectRadioID);
	//执行继续查看任务命令 add by wujianping
	OPT_RESULT PushCmd_QuestContinue(ObjID_t idNPC, ScriptID_t idQuestScript);
	//执行组队跟随命令 add by wujianping
	OPT_RESULT PushCmd_TeamFollow();
	//执行结束组队跟随命令 add by wujianping
	OPT_RESULT PushCmd_StopTeamFollow();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//开始组队跟随 add by wujianping
	OPT_RESULT StartTeamFollow(void);
	//结束组队跟随 add by wujianping
	OPT_RESULT StopTeamFollow(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//组队成员跟随 add by wujianping
	void		TeamMemeberToMove(void);
	//进入战斗状态 add by wujianping
	BOOL		IsEnterCombatState(ObjID_t idSkill, ObjID_t idTarget);
	//把技能压入队列中 队列其实是假的，只是一个子技能的成员和一个公共技能的成员 
	//也就是说如果同时有两个技能发生，那么就会顶掉一个。并不是没有这种可能的，比如你释放一个技能A给对方，你的坐骑有一个技能就是攻击对方
	//时，有15%的概率释放一个B技能。那么实际效果是A技能顶掉B技能。因为B技能要早于A技能发生，所以被顶掉。add by wujianping
	void		PushSpellToQueue
			(
				ObjID_t idSkill,
				ObjID_t idTarget,
				float	fTargetX,
				float	fTargetZ,
				int32	iHurtDelayTime,
				float	fDir,
				GUID_t	guidTarget,
				BOOL	bChildSkill = FALSE
			);
	//使用一个物品 同样这个所谓的队列也是假的 add by wujianping
	void		PushItemToQueue
			(
				ID_t		nBagIndex,
				ObjID_t		nTargetObj,
				const GLPos &posTarget,
				SHorseGuid&guidTargetPet,
				ID_t		nTargetItem
			);
	//得到下一个路点 add by wujianping
	inline BOOL	GetFollowPos(GLPos &Pos, const GLPos *pStartPos, const GLPos *pEndPos, float fDist);
	//组队跟随 超出范围则停止跟随 并且根据距离转换移动速度，切换移动模式（走跑的切换） 
	//有关走跑的切换是客户端来完成的，服务器把玩家的移动速度同步给客户端后，客户端根据速度决定动作（走或跑）
	//add by wujianping
	inline void	FollowMove(Player *pPlayer, GLPos *pPos, float fDist);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	//死亡后的具体逻辑 add by wujianping
	void	After_Die(ObjID_t idKiller);
	//死亡后停止组队跟随 add by wujianping
	void	LeaveTeam_After_Die(void);
	//死亡后宠物被收回 add by wujianping
	void	RleasePet_After_Die(void);
	//死亡后的复活方式 请注意副本有特殊处理 add by wujianping
	void	CanRelive_After_Die(void);
	//死亡后停止摆摊 清除摆摊状态 add by wujianping
	void	Stall_After_Die(void);
	//死亡停止交易 清除交易状态 add by wujianping
	void	Exchange_After_Die(void);
	//死亡惩罚 add by wujianping
	void	Penalty_After_Die(ObjID_t idKiller);
	//死亡结束婚礼 add by wujianping
	void	Wedding_After_Die(void);

	//nobody use it add by wujianping
	void	PunishmentType_After_Die(int32 &nPenaltyID, ObjID_t idKiller);
	//nobody use it add by wujianping
	void	Punishment_Exp_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer);
	//nobody use it add by wujianping
	void	Punishment_Money_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer);
	//nobody use it add by wujianping
	void	Punishment_EquipDur_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer);
	//nobody use it add by wujianping
	void	Punishment_ItemDrop_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer);
	//nobody use it add by wujianping
	void	Punishment_EquipDrop_After_Die(const SDiePenaltyInfo *pPenaltyInfo, Player *pPlayer);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	std::unordered_map<uint32_t, void*>*GetTargetList()
	{
		return &m_TargetList;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void ClearTargetList()
	{
		m_TargetList.clear();
	}

	void   addTarget(uint32_t id, void* target)
	{
		m_TargetList[id] = target;
	}
	void* getTarget(uint32_t id)
	{
		auto it = m_TargetList.find(id);
		if (it != m_TargetList.end())
			return it->second;
		return nullptr;
	}
	void	AddTargetToList(Character *pChar);
	void	RemoveTargetFromList(Character *pChar);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	std::unordered_map<uint32_t, void*>	m_TargetList;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	StartPatrol();
	void	StopPatrol(void);
	void	PausePatrol(void);
	void	ResumePatrol(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void		OnEvent_ReliveInfoChanged(void);
	void		OnEvent_CallOfInfoChanged(void);

	OPT_RESULT		AcceptCallOf(void);
	OPT_RESULT		RefuseCallOf(void);

	virtual void	ForceInterruptAllSpell(void);
	virtual void	ForceInterruptAutoSpell(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	OPT_RESULT Validate_Event(Object *pTarget);
	BOOL	CheckTargetValid(SpellID_t nSkillID, ObjID_t TargetID);
	void	Baby_Go(const GLPos *paTargetPos);
	BOOL	CheckQuestSubmitNPCIfNecessary(ScriptID_t idEvent, Object *pTarget);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	struct SLogicParam_UseSpell
	{

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Clear(void)
		{
			QueueSpell_CleanUp();
			AutoSpell_CleanUp();
			ChildSpell_CleanUp();

			m_iHurtDelayTime = 0;
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void QueueSpell_CleanUp(void)
		{
			m_nQueuedSpell = INVALID_ID;
			m_nQueueTargetObjID = INVALID_ID;
			m_guidQueueTarget = INVALID_ID;
			m_fQueueTargetDirection = 0.0f;
			m_QueueTargetPosition.Clear();
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void AutoSpell_CleanUp(void)
		{
			if (m_nAutoShotSpell == 31)
			{
				int kk = 0;
			}

			if (m_nAutoShotTargetObjID == 1)
			{
				int kk = 0;
			}
			m_nAutoShotSpell = INVALID_ID;
			m_nAutoShotTargetObjID = INVALID_ID;
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void ChildSpell_CleanUp(void)
		{
			m_nChildSpell = INVALID_ID;
			m_nChildSpellTargetObjID = INVALID_ID;
			m_ChildSpellPosition.Clear();
		}

		SpellID_t	m_nAutoShotSpell;
		ObjID_t		m_nAutoShotTargetObjID;

		SpellID_t	m_nQueuedSpell;
		ObjID_t		m_nQueueTargetObjID;
		GLPos	m_QueueTargetPosition;
		float		m_fQueueTargetDirection;
		GUID_t		m_guidQueueTarget;

		SpellID_t	m_nChildSpell;
		ObjID_t		m_nChildSpellTargetObjID;
		GLPos	m_ChildSpellPosition;

		int32		m_iHurtDelayTime;
	};

	struct SLogicParam_UseItem
	{

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Clear(void)
		{
			m_BagIndex = INVALID_ID;
			m_TargetItem = INVALID_ID;
			m_Target = INVALID_ID;
			m_posTarget.Clear();
			m_TargetPetGUID.Reset();
		}

		ID_t		m_BagIndex;
		ID_t		m_TargetItem;
		ObjID_t		m_Target;
		SHorseGuid	m_TargetPetGUID;
		GLPos	m_posTarget;
	};

	struct SLogicParam_Dead
	{
		CTinyTimer	m_AutoTimer;
	};

	SLogicParam_UseSpell	m_paramAI_UseSpell;
	SLogicParam_UseItem	m_paramAI_UseItem;
	SLogicParam_Dead	m_paramAI_Dead;

	int32			m_TeamFollowCheckTick;
	int32			m_nSettleTime;
	BOOL			m_baHead;
	int32			m_nIndexOfPassed;
	int32			m_nIndexOfMoveTo;
	BOOL			m_bPause;
	BOOL			m_bCircle;
	ScriptID_t		m_PatrolScriptID;
};
#endif
