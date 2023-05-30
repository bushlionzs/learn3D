/*$T MapServer/Server/Obj/Pet.h GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __PET_H__
#define __PET_H__

#include "Character.h"
#include "StructPet.h"
struct _INIT_PET_OBJECT :
	public _INIT_PLAYERACTER_OBJECT
{
	GUID_t	m_GUID;
	_HORSE_DB m_PetDB;
	ObjID_t m_CreatorID;
	int32	m_nIndex;
	int32	m_RespawnTime;

	_INIT_PET_OBJECT (void)
	{
		m_GUID = INVALID_GUID;
		m_PetDB.Clear();
		m_CreatorID = INVALID_ID;
		m_nIndex = -1;
		m_RespawnTime = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Clear(void)
	{
		m_GUID = INVALID_GUID;
		m_PetDB.Clear();
		m_CreatorID = INVALID_ID;
		m_nIndex = -1;
		m_RespawnTime = -1;

		_INIT_PLAYERACTER_OBJECT::Clear();
	}
};

struct _PET_PROPERTY_BACKUP
{
public:
	BOOL		m_bNameModified;
	BOOL		m_bTitleModified;

	float		m_MoveSpeed;
	SCampData	m_CampData;
	ObjID_t		m_nOwnerID;

	int32		m_nAIType;
	int32		m_Level;

	int32		m_HP;
	int32		m_MaxHp;
	int32		m_nDataID;
	int32		m_nModelID;
	int32		m_nMountID;

	SHorseGuid	m_GUID;
	uchar		m_byGeneration;
	uchar		m_byHappiness;

	uint32		m_nExp;

	int32		m_iStrengthPerception;
	int32		m_iSmartnessPerception;
	int32		m_iMindPerception;
	int32		m_iConstitutionPerception;

	int32		m_iPullulationRate;

	int32		m_nRemainPoint;

	int32		m_iStrength;
	int32		m_iSmartness;
	int32		m_iMind;
	int32		m_iConstitution;

	int32		m_nAtt_Near;
	int32		m_nAtt_Far;
	int32		m_nAtt_Magic;
	int32		m_nDef_Near;
	int32		m_nDef_Far;
	int32		m_nDef_Magic;

	int32		m_nHit;
	int32		m_nMiss;
	int32		m_nCritical;

	int32		m_nTargetID;
	int32		m_nScale;
public:
	_PET_PROPERTY_BACKUP (void);

	void	Clear(void);
};

enum
{
	IDX_ONWER_LIFE_RATE	= 0,
	IDX_ONWER_ATTACK_RATE,
	IDX_ONWER_DEFANCE_RATE,
	IDX_ONWER_MISS_RATE,
	IDX_ONWER_TOUGHNESS_RATE,
	IDX_ONWER_CRITICAL_RATE,
	IDX_ONWER_HIT_RATE,
};

#define MAX_CAPTURER_NUM	(6)
#define LEVELDELTA_GETEXP	(5)
#define SEND_LIFE_INTERVAL	(30)

class Behavior_Pet;
class Pet :
	public Character
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	Behavior_Pet;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Pet(void);
	virtual ~Pet(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual ObjectClass GetObjType(void) const
	{
		return OBJECT_CLASS_PET;
	}

	virtual void	Clear();
	virtual BOOL	Init(const _INIT_OBJECT *pInit);

	virtual bool	HeartBeat(uint32 uTime = 0);

	virtual void	InitAIObj();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	const _HORSE_DB *GetPetDB(void) const
	{
		return &m_PetDB;
	}

	void	InitMonsterPetDB(_Monster_Pet_DB_Struct &oMonsterPet);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	InitLife();

	void	InitHP();
	void	InitBaseAttr();

	BOOL	InitSkill();

	int32	GetLifeTime();
	void	GetNowImpactList(_Monster_Pet_DB_Struct &oMonsterPet);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	IsEnemy(Character *pCharacter);
	virtual BOOL	IsFriend(Character *pCharacter);
	virtual BOOL	IsPartner(Character *pCharacter);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual NetPacket	*CreateNewObjMsg(void);
	virtual void		DestroyNewObjMsg(NetPacket*pPacket);

	virtual void		InitBackupAttr();
	virtual void		SendMsg_RefeshAttrib(void);
	virtual void		RequestBaseProperty(Player *pTargetHuman, BASEPROPERTY_REFESH_MODE nMode = REFESH_ALL);
	virtual void		AskMsg_DetailAttrib(Player *pTargetHuman);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	virtual void	SendCharBaseDirectForHP();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	_PET_PROPERTY_BACKUP	m_AttrBackUp;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	HeartBeat_Happiness(uint32 uTime = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	CTinyTimer	m_HappinessTimer;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL	HeartBeat_Life(uint32 uTime = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	CTinyTimer	m_LifeTimer;
	uint32		m_BeginTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void		LevelUp(void);
	virtual void	SetReliveInfo(BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual BOOL		Spell_HaveSpell(SpellID_t const nID) const;

	const SHorseSkill	*Spell_GetSpell(int32 nIndex) const;

	int32			Spell_GetCount_CortrolByPlayer(void);
	int32			Spell_GetMaxCount_CortrolByPlayer(void);
	int32			Spell_GetCount_CortrolByAI(void);
	int32			Spell_GetMaxCount_CortrolByAI(void);

	BOOL			Spell_RegisterSpell(SpellID_t const nID, int32 nIndex);
	BOOL			Spell_UnregisterSpell(SpellID_t const nID, int32 nIndex);
	BOOL			Spell_ModifySpell_Study(SpellID_t nID);
	BOOL			Spell_ModifySpell_Realize(SpellID_t nID);
	BOOL			Spell_ModifySpell_Profession(SpellID_t nID);
	BOOL			Spell_Apperceive(void);

	virtual void		Spell_OnEquipItem(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual _EFFECT_LIST	&Effect_GetEffectList(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	virtual void	Effect_InitList(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	_EFFECT_LIST	m_ImpactList;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual Time_t	GetCooldownRemained(CooldownID_t const nID) const;
	virtual BOOL	IsCooldowned(CooldownID_t const nID) const;
	virtual void	SetCooldown(CooldownID_t const nID, Time_t nCooldown);
	virtual BOOL	HeartBeat_Cooldown(uint32 uTime = 0);
	virtual BOOL	HeartBeat_Recover(uint32 uTime = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	RecallPet();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int32	GetCaptureCount(void) const;

	BOOL	AddCapturer(ObjID_t idObj);
	BOOL	DelCapturer(ObjID_t idObj);
	void	CleanAllCapturer(void);
	void	SendCaptureFailedToOthers(ObjID_t idObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32	m_nCapturerCount;
	ObjID_t m_aCapturer[MAX_CAPTURER_NUM];

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual ObjID_t		GetOwnerID(void) const;
	virtual Character	*GetOwner(void);

	Behavior_Pet			*GetPetAI(void) const;
	void			SetTargetID(ObjID_t TargetID);
	ObjID_t			GetTargetID(void) const;
	const GLPos		*GetRespawnPos(void) const;

	void			ToAttack(ObjID_t TargetID);
	BOOL			PushSkillToCache(int32 idSkill);
	void			GetRateOfBuffTakeEffect(int32 idSkill, int32 &rateOfBuffTakeEffect);
	BOOL			IsFollowMode();
	void			SetFollowMode(BOOL bFlag);

	_PET_CTRL_STATE		GetCtrlState(void) const;

	void			SetCtrlState(const _PET_CTRL_STATE eState);

	uint32		GetMoveIntervalTimer(void);
	void		SetMoveIntervalTimer(uint32 uNowTime);

	const GLPos* GetTargetOldPos( void )const;
	void SetTargetOldPos( const GLPos* CurPos );

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	ObjID_t			m_OwnerID;
	ObjID_t			m_TargetID;
	GLPos		m_RespawnPos;
	int32			m_RespawnTime;

	int32			m_aCacheOfSkill[MONSTER_PET_MAX_SKILL];
	CooldownListForPet_T	m_CooldownList;

	int32			m_AIType;
	int32			m_iLevel;
	int32			m_iDataID;
	SHorseGuid		m_guidPet;
	int32			m_iHP;
	int32			m_iMP;
	BOOL			m_bFollowMode;
	_PET_CTRL_STATE		m_nCtrlState;
	uint32			m_uMoveIntervalTimer;
	GLPos		m_TargetOldPos;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual GUID_t		GetGUID(void) const;

	Player			*GetCreator(void) const;
	const Player		*GetConstCreator(void) const;

	void			SetHorseGUID(SHorseGuid guid);
	SHorseGuid		GetHorseGUID(void) const;

	void			SetDataID(const uint32 dataID);
	virtual uint32		GetDataID(void) const;

	virtual void		SetName(const char *pszName);
	virtual const char	*GetName(void) const;

	virtual void		SetTitle(const char *pszTitle);
	virtual const char	*GetTitle(void) const;

	void			IncrementExp(int32 nIncrement);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetExp(void) const
	{
		return 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void SetExp(int32 nExp)
	{
	};

	virtual void	SetHP(int32 nHP);
	virtual int32	GetHP(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual void SetMP(int32 nMP)
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetMP(void)
	{
		return 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual int32 Get_Property_Rage(void)
	{
		return 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Set_Property_Rage(int32 nRage)
	{
	};

	virtual int32	GetAIType(void) const;
	virtual void	SetAIType(int32 nAIType);

	virtual int32	GetLevel(void) const;
	virtual void	SetLevel(int32 nLevel);

	virtual uchar	GetGeneration(void) const;
	virtual void	Set_Property_Generation(uchar byGeneration);

	void		IncrementHappyness(int32 nIncrement);
	uchar		GetHappiness(void) const;
	void		SetHappiness(uchar byHappiness);

	int32		GetGenGu(void) const;
	void		SetGenGu(int32 nGenGu);

	virtual int32	GetStrPerception(void) const;
	virtual int32	GetSmartnessPerception(void) const;
	virtual int32	GetMindPerception(void) const;

	virtual int32	GetConstitutionPerception(void) const;

	virtual int32	GetRemainPoint(void) const;
	virtual void	SetRemainPoint(int32 nRemainPoint);
	int32		GetIndexInOnwer();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	GUID_t			m_GUID;
	ObjID_t			m_CreatorID;
	Player			*m_pCreator;
	int32			m_nIndex;
	_HORSE_DB			m_PetDB;
	_MONSTER_PET_ATTR	m_oInit;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	virtual int32			Get_Property_Str(void);
	
	virtual int32			GetMaxHP(void);
	virtual int32			Get_BaseProperty_MaxHP(void);
	virtual void			Set_BaseProperty_MaxHP(int32 const nHp);

	virtual int32			Get_BaseProperty_HPRegenerate(void);

	virtual int32			Get_BaseProperty_MaxMP(void);


	virtual int32			Get_Property_MPRegenerate(void);


	virtual const SCampData	*GetCampData(void);
	virtual const SCampData	*GetBaseCampData(void) const;
	virtual void			SetBaseCampData(const SCampData *pCampData);
	virtual int32			GetCampID(void);
	virtual int32			GetBaseCampID(void) const;
	virtual void			SetBaseCampID(int32 const nID);

	virtual int32			GetModelID(void);
	virtual int32			Get_BaseProperty_ModelID(void) const;
	virtual void			Set_BaseProperty_ModelID(int32 const nID);

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

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32	GetAttrValueByType(int32 iType);
	int32	GetRefixRate(int32 iType);
	int32	GetRefixValue(int32 iType);

private:
	int32	m_iHitRate;
	int32	m_iMissRate;
	int32	m_iCriticalRate;

protected:
	virtual void		RefixByInherence(int32 &nDamage, Character *const pAttacker, BOOL bDOT, BOOL bPKRateCtr);
};
#endif
