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
	//����״̬�µ����� add by wujianping
	virtual void	Dead_Logic(uint32 uTime);
	//��Ӹ���״̬�µ����� add by wujianping
	virtual void	TeamFollow_Logic(uint32 uTime);
	//ս��״̬�µ����� add by wujianping
	virtual void	Combat_Logic(uint32 uTime);
	//Ѳ��״̬�µ�������ֻ�л����õ�Ѳ��״̬�� add by wujianping
	virtual void	Patrol_Logic(uint32 uTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//������ʱ���߼������� add by wujianping
	virtual void	Event_OnDie(Object *pKiller = NULL);
	//��ʹ�ü��ܵ��߼������� add by wujianping
	virtual void	Event_OnBeSpell(Character *pCharacter, int32 nGoodEffect);
	//���˺����߼������� add by wujianping
	virtual void	Event_OnDamage(int32 nDamage, Character *pAttacker);
	//�����Ƶ��߼������� add by wujianping
	virtual void	Event_OnBeHeal(Character *pCharacter, int32 nHeal);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//ִ���������� nResultCodeΪ���ʽ add by wujianping
	OPT_RESULT PushCmd_DieResult(int32 nResultCode);
	//���ٻ� nResultCodeΪͬ����߾ܾ� add by wujianping
	OPT_RESULT PushCmd_CallOfResult(int32 nResultCode);
	//ִ����Ծ���� add by wujianping
	OPT_RESULT PushCmd_Jump(int32 nLogicCount);
	//ִ���л��������� add by wujianping
	OPT_RESULT PushCmd_MoodState(int32 nMoodState);
	//�������״̬ add by wujianping
	OPT_RESULT PushCmd_Idle(void);
	//�����̯״̬ add by wujianping
	OPT_RESULT PushCmd_Stall(void);
	//����ʹ�������״̬ add by wujianping
	OPT_RESULT PushCmd_UseAbility(void);
	//������� add by wujianping
	OPT_RESULT PushCmd_DefaultEvent(ObjID_t idNPC);
	//������� add by wujianping
	OPT_RESULT PushCmd_EventRequest(ObjID_t idNPC, ScriptID_t idEvent, int32 exIndex);
	//ִ���ƶ����� add by wujianping
	OPT_RESULT PushCmd_Move
		(
			int32		nHandleID,
			uint16		wNumTargetPos,
			const GLPos *paTargetPos,
			int32		nStopLogicCount = INVALID_ID,
			const GLPos *paCurPos = NULL,
			ObjID_t		nSenderID = INVALID_ID
		);
	//ִ��ʹ��ս���������� add by wujianping
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
	//ִ��ʹ����Ʒ���� add by wujianping
	OPT_RESULT PushCmd_UseItem
		(
			ID_t		nBagIndex,
			ObjID_t		nTargetObj,
			const GLPos &posTarget,
			SHorseGuid&guidTargetPet,
			ID_t		nTargetItem
		);
	//ִ�н����������� add by wujianping
	OPT_RESULT PushCmd_QuestAccept(ObjID_t idNPC, ScriptID_t idQuestScript);
	//ִ�з����������� add by wujianping
	OPT_RESULT PushCmd_QuestAbandon(ScriptID_t idQuestScript);
	//ִ�оܾ��������� add by wujianping
	OPT_RESULT PushCmd_QuestRefuse(ObjID_t idNPC, ScriptID_t idQuestScript);
	//ִ���ύ�������� add by wujianping
	OPT_RESULT PushCmd_QuestSubmit(ObjID_t idNPC, ScriptID_t idQuestScript, uint32 uSelectRadioID);
	//ִ�м����鿴�������� add by wujianping
	OPT_RESULT PushCmd_QuestContinue(ObjID_t idNPC, ScriptID_t idQuestScript);
	//ִ����Ӹ������� add by wujianping
	OPT_RESULT PushCmd_TeamFollow();
	//ִ�н�����Ӹ������� add by wujianping
	OPT_RESULT PushCmd_StopTeamFollow();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//��ʼ��Ӹ��� add by wujianping
	OPT_RESULT StartTeamFollow(void);
	//������Ӹ��� add by wujianping
	OPT_RESULT StopTeamFollow(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//��ӳ�Ա���� add by wujianping
	void		TeamMemeberToMove(void);
	//����ս��״̬ add by wujianping
	BOOL		IsEnterCombatState(ObjID_t idSkill, ObjID_t idTarget);
	//�Ѽ���ѹ������� ������ʵ�Ǽٵģ�ֻ��һ���Ӽ��ܵĳ�Ա��һ���������ܵĳ�Ա 
	//Ҳ����˵���ͬʱ���������ܷ�������ô�ͻᶥ��һ����������û�����ֿ��ܵģ��������ͷ�һ������A���Է������������һ�����ܾ��ǹ����Է�
	//ʱ����15%�ĸ����ͷ�һ��B���ܡ���ôʵ��Ч����A���ܶ���B���ܡ���ΪB����Ҫ����A���ܷ��������Ա�������add by wujianping
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
	//ʹ��һ����Ʒ ͬ�������ν�Ķ���Ҳ�Ǽٵ� add by wujianping
	void		PushItemToQueue
			(
				ID_t		nBagIndex,
				ObjID_t		nTargetObj,
				const GLPos &posTarget,
				SHorseGuid&guidTargetPet,
				ID_t		nTargetItem
			);
	//�õ���һ��·�� add by wujianping
	inline BOOL	GetFollowPos(GLPos &Pos, const GLPos *pStartPos, const GLPos *pEndPos, float fDist);
	//��Ӹ��� ������Χ��ֹͣ���� ���Ҹ��ݾ���ת���ƶ��ٶȣ��л��ƶ�ģʽ�����ܵ��л��� 
	//�й����ܵ��л��ǿͻ�������ɵģ�����������ҵ��ƶ��ٶ�ͬ�����ͻ��˺󣬿ͻ��˸����ٶȾ����������߻��ܣ�
	//add by wujianping
	inline void	FollowMove(Player *pPlayer, GLPos *pPos, float fDist);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	//������ľ����߼� add by wujianping
	void	After_Die(ObjID_t idKiller);
	//������ֹͣ��Ӹ��� add by wujianping
	void	LeaveTeam_After_Die(void);
	//��������ﱻ�ջ� add by wujianping
	void	RleasePet_After_Die(void);
	//������ĸ��ʽ ��ע�⸱�������⴦�� add by wujianping
	void	CanRelive_After_Die(void);
	//������ֹͣ��̯ �����̯״̬ add by wujianping
	void	Stall_After_Die(void);
	//����ֹͣ���� �������״̬ add by wujianping
	void	Exchange_After_Die(void);
	//�����ͷ� add by wujianping
	void	Penalty_After_Die(ObjID_t idKiller);
	//������������ add by wujianping
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
