/*$T MapServer/Server/Obj/Monster.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __OBJ_MONSTER_H__
#define __OBJ_MONSTER_H__

#include "Character.h"
class NetPacket;
#define MAX_SHOP_INIT	4
struct _INIT_MONSTER_OBJECT :
	public _INIT_PLAYERACTER_OBJECT
{
	GUID_t		m_GUID;
	uint32		m_uDataID;
	char		m_szName[NPC_NAME_LEN];
	char		m_szTitle[NPC_TITLE_LEN];
	ScriptID_t	m_idScript;
	int32		m_RespawnTime;
	uint32		m_uGroupID;
	uint32		m_uTeamID;
	int32		m_BaseAI;
	int32		m_ExtAIScript;
	int32		m_nPatrolID;
	int32		m_nShop[MAX_SHOP_INIT];
	uint32		m_LeaderID;
	BOOL		m_bPet;
	uint32		m_LiveTime;
	uint32		m_ObjGUID;
	CampID_t	m_CampID;
	int32		m_nQuestID;
	int32		m_nLevel;

	_INIT_MONSTER_OBJECT (void)
	{
		m_GUID = -1;
		m_uDataID = -1;
		m_szName[0] = 0;
		m_szTitle[0] = 0;
		m_RespawnTime = 60000;
		m_uGroupID = -1;
		m_uTeamID = -1;
		m_BaseAI = 0;
		m_idScript = -1;
		m_ExtAIScript = 0;
		m_nPatrolID = -1;
		m_LeaderID = -1;
		m_bPet = FALSE;
		m_LiveTime = -1;
		m_ObjGUID = INVALID_ID;
		m_CampID = INVALID_CAMP;
		m_nQuestID = INVALID_ID;
		m_nLevel = -1;

		for(int32 i = 0; i < MAX_SHOP_INIT; i++)
		{
			m_nShop[i] = -1;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Clear(void)
	{
		m_GUID = -1;
		m_uDataID = -1;
		m_szName[0] = 0;
		m_szTitle[0] = 0;
		m_RespawnTime = 60000;
		m_uGroupID = -1;
		m_uTeamID = -1;
		m_BaseAI = 0;
		m_ExtAIScript = -1;
		m_idScript = -1;
		m_nPatrolID = -1;
		m_LeaderID = -1;
		m_bPet = FALSE;
		m_LiveTime = -1;
		m_ObjGUID = INVALID_ID;

		m_CampID = INVALID_CAMP;
		m_nQuestID = INVALID_ID;
		m_nLevel = -1;

		for(int32 i = 0; i < MAX_SHOP_INIT; i++)
		{
			m_nShop[i] = -1;
		}

		_INIT_PLAYERACTER_OBJECT::Clear();
	}
};

struct SMonsterAttrBackup
{
	BOOL		m_bNameModified;
	BOOL		m_bTitleModified;
	int32		m_HP;
	int32		m_MaxHp;
	uchar		m_HPPercent;
	uchar		m_HPGuardPercent;
	float		m_MoveSpeed;
	SCampData	m_CampData;
	int32		m_nDataID;
	int32		m_nModelID;
	int32		m_nMountID;
	int32		m_nAIType;
	ObjID_t		m_OwnerID;
	GUID_t		m_OccupantGUID;
	int32		m_nStealthLevel;
	int32		m_nMoodState;
	int32		m_iWeaponID;
	int32		m_iHorseID;
	GuildID_t	m_GuildID;
	int32		m_nTargetID;
	float		m_fDir;
	int32		m_nScale;

	SMonsterAttrBackup (void)
	{
		m_bNameModified = FALSE;
		m_bTitleModified = FALSE;
		m_HP = 0;
		m_MaxHp = 1;
		m_HPPercent = 100;
		m_HPGuardPercent = 100;
		m_MoveSpeed = 0.f;

		m_nDataID = INVALID_ID;
		m_nModelID = INVALID_ID;
		m_nMountID = INVALID_ID;
		m_OwnerID = INVALID_ID;
		m_OccupantGUID = INVALID_GUID;
		m_nStealthLevel = -1;
		m_nMoodState = INVALID_MOOD_STATE;
		m_iWeaponID = -1;
		m_iHorseID = -1;
		m_GuildID = INVALID_ID;
		m_nTargetID = INVALID_ID;
		m_fDir = 0.f;
		m_nScale = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		m_bNameModified = FALSE;
		m_bTitleModified = FALSE;
		m_HP = 0;
		m_MaxHp = 1;
		m_HPPercent = 100;
		m_HPGuardPercent = 100;
		m_MoveSpeed = 0.f;
		m_CampData.Clear();
		m_nDataID = INVALID_ID;
		m_nModelID = INVALID_ID;
		m_nMountID = INVALID_ID;
		m_OwnerID = INVALID_ID;
		m_OccupantGUID = INVALID_GUID;
		m_nStealthLevel = -1;
		m_nMoodState = INVALID_MOOD_STATE;
		m_iWeaponID = -1;
		m_iHorseID = -1;
		m_GuildID = INVALID_ID;
		m_nTargetID = INVALID_ID;
		m_fDir = 0.f;
		m_nScale = 0;
	}
};

class	Player;
class	Behavior_Monster;
class	DynamicShopMgr;
struct MonsterProperty;

class Monster :
	public Character
{
private:
	MonsterProperty* mMonsterProperty = nullptr;
public:
	Monster(void);
	virtual ~Monster(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual ObjectClass GetObjType(void) const
	{
		return OBJECT_CLASS_MONSTER;
	}

	virtual void	Clear(void);

protected:
	_EFFECT_LIST	m_EffectList;
	virtual void	Effect_InitList(void);
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL HaveSpell(SpellID_t const nID) const
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL ModifySpell(SpellID_t const nID, int32 const nModifyFlag)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Spell_OnEquipItem(void)
	{
	} void	FadeOutAllEffect();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	void ResetCooldownList()
	{
		m_CooldownList.Reset();
	}

protected:
	CooldownListForMonster_T	m_CooldownList;


public:
	//ai

	int32 GetMonsterAIType(void);
	Behavior_Monster* GetMonsterAI(void) const
	{
		return((Behavior_Monster*)m_pAI_Character);
	}


public:

	virtual _EFFECT_LIST &Effect_GetEffectList(void)
	{
		return m_EffectList;
	}

	bool respawn(CharacterVisitor* pVisitor);
public:
	int32 GetRespawnTime(void) const
	{
		return m_RespawnTime;
	}

	void SetRespawnPos(const GLPos *pPos)
	{
		m_RespawnPos = *pPos;
	}


	const GLPos *GetRespawnPos(void) const
	{
		return &m_RespawnPos;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetRespawnDir(float fDir)
	{
		m_RespawnDir = fDir;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	float GetRespawnDir(void) const
	{
		return m_RespawnDir;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32		m_RespawnTime;
	CTinyTimer	m_RespawnTimer;
	float		m_RespawnDir;
	GLPos	m_RespawnPos;

	CTinyTimer	m_LiveTimer;
	uint32		m_LiveTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOccupantTeamID(TeamID_t tid)
	{
		m_Own_TeamID = tid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	TeamID_t GetOccupantTeamID()
	{
		return m_Own_TeamID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOccupantGUID(GUID_t guid)
	{
		m_OccupantGUID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GUID_t GetOccupantGUID()
	{
		return m_OccupantGUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOccupantLevel(uint32 nLevel)
	{
		m_OccupantLevel = nLevel;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetOccupantLevel()
	{
		return m_OccupantLevel;
	}
	

	void ClearKiller()
	{
		m_DamageMemList.Clear();
		m_Own_TeamID = INVALID_ID;
		m_OccupantGUID = INVALID_ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetDistribMode(uchar nMode)
	{
		m_DistribMode = nMode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline const uchar GetDistribMode() const
	{
		return m_DistribMode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetLastOwnerGUID(GUID_t guid)
	{
		m_LastOwnerGUID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline const GUID_t GetLastOwnerGuid() const
	{
		return m_LastOwnerGUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetOwnTeamLeader(GUID_t nGuid)
	{
		m_OwnTeamLeaderGUID = nGuid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline const GUID_t GetOwnTeamLeader() const
	{
		return m_OwnTeamLeaderGUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetControlValue(float fControlValue)
	{
		m_fControlValue = fControlValue;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline const float GetControlValue() const
	{
		return m_fControlValue;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	TeamID_t		m_Own_TeamID;
	GUID_t			m_OccupantGUID;
	uint32			m_OccupantLevel;
	float			m_fControlValue;
	SDamageMemList		m_DamageMemList;
	SMonsterOwnerList	m_OwnerList;

	GUID_t			m_OwnTeamLeaderGUID;
	uchar			m_DistribMode;
	GUID_t			m_LastOwnerGUID;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:



	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAIType(int32 AIType)
	{
		m_AIType = AIType;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAIType(void) const
	{
		return m_AIType;
	}



	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetPosRange(void) const
	{
		return m_PositionRange;
	}



	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetLeaderID(ObjID_t LeaderID)
	{
		m_LeaderID = LeaderID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjID_t GetLeaderID(void) const
	{
		return m_LeaderID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAIScript() const
	{
		return m_AIScript;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetAIScript(int32 val)
	{
		m_AIScript = val;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32	m_AIType;
	int32	m_AIScript;

	ObjID_t m_LeaderID;
	int32	m_PositionRange;
	Time_t	m_nOwnerElapsedTick;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	DynamicShopMgr *GetShopManager()
	{
		return m_pShopManager;
	}


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	DynamicShopMgr	*m_pShopManager;


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL isPatrolMonster(void)
	{
		return m_nPatrolID != INVALID_ID ? TRUE : FALSE;
	}

	int32 GetPatrolPathIndex(void) const
	{
		return m_nPatrolID;
	}

	uchar GetPatrolNoBreak()const
	{
		return m_bPatrolNoBreak;
	}

	void SetPatrolNoBreak(uchar bPatrolNoBreak )
	{
		m_bPatrolNoBreak = bPatrolNoBreak;
	}

	void SetCreateFlag(BOOL Flag)
	{
		m_CreateFlag = Flag;
	}

	int32 GetMonsterDropSetID()
	{
		return m_MonsterDropItemSetID;
	}

	int32 GetMonsterDropRate()
	{
		return m_nMonsterDropRate;
	}

	uint32_t		GetValidOwnerList
	(
		uint32_t	nMaxSize,
		Player** ppValidOwner,
		ObjID_t* pValidOwnerID = NULL,
		GUID_t* pValidOwnerGUID = NULL
	);

	virtual BOOL	GetNearCanDropPos(GLPos& dropPos);
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32			m_nPatrolID;
	float			m_DropSearchRange;
	int32			m_DropTeamCount;
	BOOL			m_CreateFlag;
	int32			m_MonsterDropItemSetID;
	int32			m_nMonsterDropRate;
	eBOX_DISTRIBUTE_RULER	m_DropRuler;

	uchar m_bPatrolNoBreak;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { BEKILL_QUEST_NUM = 128, };
	typedef struct SKillObj
	{
		int32	m_nQuestId;
	} tagKillObj[BEKILL_QUEST_NUM];
	tagKillObj	m_sKillObj;
	int32		m_nKillCount;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual GUID_t GetGUID(void) const
	{
		return m_NPCGUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetDataID(void) const
	{
		return m_uDataID;
	}

	


	



	









	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void SetScriptID(ScriptID_t idScript)
	{
		m_idScript = idScript;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual ScriptID_t GetScriptID(void) const
	{
		return m_idScript;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetBaseExp(void) const
	{
		return m_BaseExp;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetBaseExp(int32 iBaseExp)
	{
		m_BaseExp = iBaseExp;
	}

	int32	GetMinDamagePercent() const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMinDamagePercent(int32 iPercent)
	{
		m_MinDamagePercent = iPercent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetGroupID()
	{
		return m_uGroupID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTeamID()
	{
		return m_uTeamID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAttackAnimTime()
	{
		return m_AttackAnimTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAttackCooldownTime()
	{
		return m_AttackCooldownTime;
	}

	// 2010-11-26 by rj 获取与设置随机怪类型组号
	int32 GetRandomGroupID()
	{
		return m_iRandomGroupID;
	}

	void SetRandomGroupID(int32 iRandomGroupID)
	{
		m_iRandomGroupID = iRandomGroupID;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	GUID_t		m_GUID;
	GUID_t		m_NPCGUID;
	uint32		m_uDataID;
	char		m_szName[NPC_NAME_LEN];
	char		m_szTitle[NPC_TITLE_LEN];
	int32		m_HP;
	int32		m_Level;
	int32		m_BaseExp;
	ScriptID_t	m_idScript;
	SCampData	m_CampData;
	int32		m_MinDamagePercent;
	uint32		m_uGroupID;
	uint32		m_uTeamID;
	int32		m_AttackAnimTime;
	int32		m_AttackCooldownTime;
	int32		m_iRandomGroupID;	// 2010-11-26 by rj 随机怪类型组号，默认值 -1 不是随机怪
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

protected:
	virtual void	SendCharBaseDirectForHP();
	virtual void	Effect_ActiveScript(UNIT_EFFECT& rEffect);
	virtual void	Effect_FadeOutScript(UNIT_EFFECT& rEffect);

	void		DistributeExpToKiller();

	void		ExpToHuman(int32 nValidMemberCount, Player** apValidMember, BOOL bTeam);
	void		GoodBadValueToHuman(int32 nValidMemberCount, Player** apValidMember, BOOL bTeam);

	/*
	 -----------------------------------------------------------------------------------------------------------------------
	 -----------------------------------------------------------------------------------------------------------------------
	 */
protected:
	SMonsterAttrBackup	m_AttrBackUp;


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	ClearSelf();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetHorseID() const
	{
		return m_iHorseID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetHorseID(int32 val)
	{
		m_iHorseID = val;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetWeaponID() const
	{
		return m_iWeaponID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetWeaponID(int32 val)
	{
		m_iWeaponID = val;
	}


	bool Init(const _INIT_OBJECT* pInit, MapID_t MapID);
	virtual bool	HeartBeat(uint32 uTime);
	virtual BOOL	HeartBeat_OutMap(uint32 uTime);



	virtual int32_t Get_Property_Rage(void);
	virtual void	Set_Property_Rage(int32_t nRage);


	virtual void		SetName(const char* pszName);
	virtual const char* GetName(void) const;

	virtual void		SetTitle(const char* pszTitle);
	virtual const char* GetTitle(void) const;

	virtual void		SetHP(int32_t nHP);
	virtual int32_t		GetHP(void);


	virtual int32_t GetHPNoClip(void);

	virtual void		SetMP(int32_t nMP);
	virtual int32_t		GetMP(void);

	virtual void		SetLevel(int32_t nLevel);
	virtual int32_t		GetLevel(void) const;

	virtual NetPacket* CreateNewObjMsg(void);
	virtual void		DestroyNewObjMsg(NetPacket* pPacket);
	virtual void		SendMsg_RefeshAttrib(void);
	virtual void		RequestBaseProperty(Player* pTargetHuman, BASEPROPERTY_REFESH_MODE nMode = REFESH_ALL);

	virtual void	OnEvent_Die(ObjID_t idKiller);
	void	OnEvent_Die_Before(ObjID_t idKiller);
	void	OnEvent_Die_After(ObjID_t idKiller);

	void Enter_Respawn(void);

	void			UpdateDamageList(int32 nDamage, Character* pCharacter);
	SDamageMemList& GetKillerRec();
	SMonsterOwnerList& GetOwnerList();

	BOOL			LockOwner(OWNERCHARACTER* poc, uchar count);
	BOOL			UnLockOwner();
public:
	bool IsLimitMove();
private:
	int32	m_iAttackNear;
	int32	m_iAttackFar;
	int32	m_iAttackMagic;
	int32	m_iDefenceNear;
	int32	m_iDefenceFar;
	int32	m_iDefenceMagic;
	int32	m_iHorseID;
	int32	m_iWeaponID;
	int32	m_iMaxHP;
	int32	m_iMaxMP;
	int32	m_iHPRestore;
	int32	m_iMPRestore;
	int32	m_iHitRate;
	int32	m_iMissRate;
	int32	m_iCriticalRate;
	int32	m_iAttackCold;
	int32	m_iAttackFire;
	int32	m_iAttackLight;
	int32	m_iAttackPoison;
	int32	m_iDefenceCold;
	int32	m_iDefenceFire;
	int32	m_iDefenceLight;
	int32	m_iDefencePoison;
public:

	virtual int32			GetMaxHP(void);
	virtual int32			Get_BaseProperty_MaxHP(void);
	virtual void			Set_BaseProperty_MaxHP(int32 const nHp);

	virtual int32			Get_Property_HPRegenerate(void);
	virtual int32			Get_BaseProperty_HPRegenerate(void);
	virtual void			Set_BaseProperty_HPRegenerate(int32 const nValue);


	virtual int32			Get_BaseProperty_MaxMP(void);
	virtual void			Set_BaseProperty_MaxMp(int32 const nMp);

	virtual int32			Get_BaseProperty_MPRegenerate(void);
	virtual void			Set_BaseProperty_MPRegenerate(int32 const nValue);

	virtual const SCampData* GetBaseCampData(void) const;
	virtual void			SetBaseCampData(const SCampData* pCampData);
	virtual int32			GetCampID(void);
	virtual int32			GetBaseCampID(void) const;
	virtual void			SetBaseCampID(int32 const nID);

	virtual int32			GetModelID(void);
	virtual int32			Get_BaseProperty_ModelID(void) const;
	virtual void			Set_BaseProperty_ModelID(int32 const nID);

	virtual BOOL			IsUnbreakable(void);

	virtual float			Get_Property_MoveSpeed(void);
	virtual int32			Get_BaseProperty_MoveSpeed(void);
	virtual void			Set_BaseProperty_MoveSpeed(int32 const nValue);

	virtual int32			Get_Property_AttackSpeed(void);
	virtual int32			Get_BaseProperty_AttackSpeed(void);
	virtual void			Set_BaseProperty_AttackSpeed(int32 const nValue);

	virtual int32			Get_Property_Miss(void);
	virtual int32			Get_BaseProperty_Miss(void);
	virtual void			Set_BaseProperty_Miss(int32 const nValue);

	virtual int32			Get_Property_Hit(void);
	virtual int32			Get_BaseProperty_Hit(void);
	virtual void			Set_BaseProperty_Hit(int32 const nValue);

	virtual int32			Get_Property_Critical(void);
	virtual int32			Get_BaseProperty_Critical(void);
	virtual void			Set_BaseProperty_Critical(int32 const nValue);

	virtual int32			GetDefenceNear(void);
	virtual int32			GetBaseDefenceNear(void);
	virtual void			SetBaseDefenceNear(int32 const nValue);

	virtual int32			GetDefenceFar(void);
	virtual int32			GetBaseDefenceFar(void);
	virtual void			SetBaseDefenceFar(int32 const nValue);

	virtual int32			GetAttackNear(void);
	virtual int32			GetBaseAttackNear(void);
	virtual void			SetBaseAttackNear(int32 const nValue);

	virtual int32			GetAttackFar(void);
	virtual int32			GetBaseAttackFar(void);
	virtual void			SetBaseAttackFar(int32 const nValue);

	virtual int32			GetToughness(void);
	virtual int32			GetBaseToughness(void);
	virtual void			SetBaseToughness(int32 const nValue);

	virtual int32			GetNearAttReduce(void);
	virtual int32			GetBaseNearAttReduce(void);
	virtual void			SetBaseNearAttReduce(int32 const nValue);

	virtual int32			GetFarAttReduce(void);
	virtual int32			GetBaseFarAttReduce(void);
	virtual void			SetBaseFarAttReduce(int32 const nValue);

	virtual int32			GetMagicAttReduce(void);
	virtual int32			GetBaseMagicAttReduce(void);
	virtual void			SetBaseMagicAttReduce(int32 const nValue);

	virtual int32			GetDreadAttResist(void);
	virtual int32			GetBaseDreadAttResist(void);
	virtual void			SetBaseDreadAttResist(int32 const nValue);

	virtual int32			GetComaAttResist(void);
	virtual int32			GetBaseComaAttResist(void);
	virtual void			SetBaseComaAttResist(int32 const nValue);

	virtual int32			GetHushAttResist(void);
	virtual int32			GetBaseHushAttResist(void);
	virtual void			SetBaseHushAttResist(int32 const nValue);

	virtual int32			GetUnArmyAttResist(void);
	virtual int32			GetBaseUnArmyAttResist(void);
	virtual void			SetBaseUnArmyAttResist(int32 const nValue);

	virtual int32			GetAttSpeedAttResist(void);
	virtual int32			GetBaseAttSpeedAttResist(void);
	virtual void			SetBaseAttSpeedAttResist(int32 const nValue);

	virtual int32			GetSkillSpeedAttResist(void);
	virtual int32			GetBaseSkillSpeedAttResist(void);
	virtual void			SetBaseSkillSpeedAttResist(int32 const nValue);

	virtual int32			GetMoveSpeedAttResist(void);
	virtual int32			GetBaseMoveSpeedAttResist(void);
	virtual void			SetBaseMoveSpeedAttResist(int32 const nValue);

	virtual int32			Get_Property_AttackMagic(void);
	virtual int32			Get_BaseProperty_AttackMagic(void);
	virtual void			Set_BaseProperty_AttackMagic(int32 const nValue);
	virtual int32			Get_Property_DefenceMagic(void);
	virtual int32			Get_BaseProperty_DefenceMagic(void);
	virtual void			Set_BaseProperty_DefenceMagic(int32 const nValue);

	virtual int32			Get_Property_AttackCold(void);
	virtual int32			Get_BaseProperty_AttackCold(void);
	virtual void			Set_BaseProperty_AttackCold(int32 const nValue);
	virtual int32			Get_Property_DefenceCold(void);
	virtual int32			Get_BaseProperty_DefenceCold(void);
	virtual void			Set_BaseProperty_DefenceCold(int32 const nValue);

	virtual int32			Get_Property_AttackFire(void);
	virtual int32			Get_BaseProperty_AttackFire(void);
	virtual void			Set_BaseProperty_AttackFire(int32 const nValue);
	virtual int32			Get_Property_DefenceFire(void);
	virtual int32			Get_BaseProperty_DefenceFire(void);
	virtual void			Set_BaseProperty_DefenceFire(int32 const nValue);

	virtual int32			Get_Property_AttackLight(void);
	virtual int32			Get_BaseProperty_AttackLight(void);
	virtual void			Set_BaseProperty_AttackLight(int32 const nValue);
	virtual int32			Get_Property_DefenceLight(void);
	virtual int32			Get_BaseProperty_DefenceLight(void);
	virtual void			Set_BaseProperty_DefenceLight(int32 const nValue);

	virtual int32			Get_Property_AttackPoison(void);
	virtual int32			Get_BaseProperty_AttackPoison(void);
	virtual void			Set_BaseProperty_AttackPoison(int32 const nValue);
	virtual int32			Get_Property_DefencePoison(void);
	virtual int32			Get_BaseProperty_DefencePoison(void);
	virtual void			Set_BaseProperty_DefencePoison(int32 const nValue);

	virtual int32			Get_Property_ReduceSlowerDuration(void);

	virtual int32			Get_Property_ReduceWeakenDuration(void);

	virtual int32			Get_Property_ReduceFaintDuration(void);

	virtual int32			Get_Property_ReducePoisonedDuration(void);

	virtual int32			GetVisionRange(void);


	
};
#endif
