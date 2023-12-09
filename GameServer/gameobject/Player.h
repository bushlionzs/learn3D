#pragma once

#include "Character.h"
#include "StructTeam.h"


#include "BaseTool.h"
#include "StructSpell.h"

#include "HumanStateMutexDefine.h"
#include "item/Item_PlayerBaseContainer.h"
#include "item/Item_PlayerExtraBagContainer.h"
#include "item/Item_PlayerExtraBag.h"
#include "item/Item_HorseContainer.h"
#include "horse/HorseAttrCalculater.h"

#include "net_handle.h"

#define HIDE_NAME_MODEL_MAN 6000
#define HIDE_NAME_MODEL_WOMAN 6001

#define HIDE_NAME_IMPACT_MAN 7661
#define HIDE_NAME_IMPACT_WOMAN 7662


class PlayerArchive;
class Item;
class HorseContainer;
class Pet;
class Monster;
class NetPacket;
struct _QUEST_DATA_t;
class SCDetailAttribPet;
class SCCharHumanBaseAttrib;
class SCDetailAttrib;
class SCCharEquipment;
class SCQuestListRefresh;

typedef int32_t int32;
namespace	Messages
{
	class	XCDetailAttrib_Pet;
	class	XCCharHumanBaseAttrib;
	class	XCDetailAttrib;
	class	XCCharEquipment;
	class	XCQuestListRefresh;
};
class Player;
struct PetLogRecordInfo;
struct SkillLogRecordInfo;
struct TALENT_LOG_PARAM;

struct CHARDBNODE;
struct _OBJ_PLAYER_INIT :
	public _INIT_PLAYERACTER_OBJECT
{
	const CHARDBNODE	*m_pUseData;

	_OBJ_PLAYER_INIT (void)
	{
		m_pUseData = NULL;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual void Clear(void)
	{
		m_pUseData = NULL;
		_INIT_PLAYERACTER_OBJECT::Clear();
	}
};



struct _PLAYER_ATTR_BACKUP
{
public:
	_PLAYER_ATTR_BACKUP (void);
	void	Clear(void);
public:
	BOOL			m_bNameModified;
	BOOL			m_bNormalTitleModified;
	BOOL			m_bGuildTitleModified;
	BOOL			m_bCountryTitleModified;
	int32_t			m_Level;
	uint64			m_Exp;
	int32_t			m_HP;
	uchar			m_HPPercent;
	uchar			m_HPGuardPercent;
	int32_t			m_MP;
	int32_t			m_MaxHp;
	int32_t			m_MaxMp;
	float			m_MoveSpeed;
	int32_t			m_nMoveMode;
	int32_t			m_nDataID;
	int32_t			m_nPortraitID;
	int32_t			m_nModelID;
	int32_t			m_nMountID;
	uint32			m_uFaceMeshID;
	uint32			m_uHairMeshID;
	uint32			m_uHairColor;
	int32_t			m_nStealthLevel;
	int32_t			m_nMoodState;
	uint32			m_Siller;
	uint32			m_BindSiller;
	uint32			m_Gold;
	uint32			m_BindGold;
	char			m_SillerMode;
	char			m_GoldMode;
	int32_t			m_nGoodBadValue;
	int32_t			m_nStr;
	int32_t			m_nCon;
	int32_t			m_nInt;
	int32_t			m_nDex;
	int32_t			m_nPointRemain;
	int32_t			m_nSkillPointRemain;
	int32_t			m_nS_SkillPoints[COMMON_S_NUMBER];
	int32_t			m_nReHpSpeed;
	int32_t			m_nReMpSpeed;
	int32_t			m_nAttNear;
	int32_t			m_nAttFar;
	int32_t			m_nAttMagic;
	int32_t			m_nDefNear;
	int32_t			m_nDefFar;
	int32_t			m_nDefMagic;
	int32_t			m_nToughness;
	int32_t			m_nHit;
	int32_t			m_nMiss;
	int32_t			m_nCritic;
	int32_t			m_nCriticHurt;
	int32_t			m_MaxRage;
	int32_t			m_nRage;
	int32_t			m_nReRageSpeed;
	int32_t			m_nStrikePoint;
	int32_t			m_nAttSpeed;
	int32_t			m_nAttCold;
	int32_t			m_nDefCold;
	int32_t			m_nAttFire;
	int32_t			m_nDefFire;
	int32_t			m_nAttLight;
	int32_t			m_nDefLight;
	int32_t			m_nAttPoison;
	int32_t			m_nDefPoison;

	int32_t			m_nNearReduce;
	int32_t			m_nFarReduce;
	int32_t			m_nMagicReduce;
	int32_t			m_nDreadReduce;
	int32_t			m_nComaReduce;
	int32_t			m_nHushReduce;
	int32_t			m_nUnarmReduce;
	int32_t			m_nAttSpeedResist;
	int32_t			m_nSkillSpeedResist;
	int32_t			m_nMoveSpeedResist;

	int32_t			m_nCountry;
	int32_t			m_nProfession;
	SCampData		m_CampData;
	_DUEL_DATA		m_DuelData;
	ObjID_t			m_nOwnerID;
	SHorseGuid		m_guidCurrentHorse;
	int32_t			m_Vigor;
	int32_t			m_MaxVigor;
	int32_t			m_RegeneRate;
	int32_t			m_Energy;
	int32_t			m_MaxEnergy;
	BOOL			m_bLimitMove;
	BOOL			m_bCanActionFlag1;
	BOOL			m_bCanActionFlag2;
	BOOL			m_bQuestHaveDoneFlagsChanged;
	BOOL			m_bMainWeaponModified;
	BOOL			m_bAssiWeaponModified;
	BOOL			m_bCapModified;
	BOOL			m_bShoulderModified;
	BOOL			m_bArmorModified;
	BOOL			m_bCuffModified;
	BOOL			m_bBootModified;
	BOOL			m_bSuitModified;
	BOOL			m_bSoulModified;
	BOOL			m_bGemAffModified;

	BOOL			m_bStallIsOpen;
	BOOL			m_bStallNameChanged;
	GuildID_t		m_GuildID;
	char			m_cFamilyID;
	char			m_cGuildOfficial;
	int32_t			m_nGP;
	int32_t			m_nHonor;
	uint32			m_nInherenceExp;
	uint16			m_nInherenceLevel;
	int32_t			m_nPK;
	uint16			m_nWenCai;
	int32_t			m_nRongYu;
	int32_t			m_nShengWang;
	int32_t			m_nHotValue;
	TeamID_t		m_nTeamID;
	BOOL			m_bTerran;
	QUEST_LIST_REFRESH	m_QuestListRefresh;
	uint16			m_nKillCountToday;
	uint32			m_nBattleHonour;
	uint16			m_nPVP2V2_Mark;
	uint16			m_nPVP2V2_Level;
	int32_t			m_nPVP2V2_Mark_WeekTotal;
	int32_t           m_iFeastScore;

	BOOL			m_bBusStateModified;
	int32_t			m_nPostCode;

	int32_t			m_iStrengthPerception;
	int32_t			m_iSmartnessPerception;
	int32_t			m_iMindPerception;
	int32_t			m_iConstitutionPerception;
	int32_t			m_byGeneration;

	int32_t			m_iTargetId;
	int32_t			m_ChangeExp;
	BOOL			m_bTiredTimeModified;
	int32_t			m_nMerit;
	int32_t			m_nZoomScale;
	ID_t			m_WorldID;
};

struct SkillOpera
{
	SpellID_t		m_SkillID;
	uchar			m_SubType;
	PrescriptionID_t	m_PresID;
	ObjID_t			m_Obj;
	int32_t			m_nMaxTime;
	int32_t			m_nCurTime;
	int32_t			m_nRobotTime;
	uchar			m_BagPos[MAX_ABILITY_ITEM];
	uint32			m_uItemIndex;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	void Clear()
	{
		memset(this, 0, sizeof(SkillOpera));
	}
};

struct ReletionEffect
{
	GUID_t	m_Guid;
	int32_t	m_nEffectRate;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	void Clear()
	{
		m_Guid = INVALID_ID;
		m_nEffectRate = 0;
	}
};

#define MAX_HUMAN_LIST_SIZE	160
#define LEVELDELTA_CALLUP	(10)

struct PLAYERLIST
{
	Player	*m_aHuman[MAX_HUMAN_LIST_SIZE];
	uchar	m_Count;

	PLAYERLIST()
	{
		m_Count = 0;
	}
};

//Added by Huangqinqi
struct MONSTERLIST
{
	Monster	*m_aMonster[MAX_HUMAN_LIST_SIZE];
	uchar	m_Count;

	MONSTERLIST()
	{
		m_Count = 0;
	}
};
//Added end by Huangqinqi

class	GameConnector;
class	Behavior_Player;
class	Pet;
class	Bus;
class	AvoidMonsterOverlap;
class	ItemContainer;
struct SShop;
struct _INIT_LIST_NODE;
class Beastie;

#define MD_GUILD_BATTLE_FLAG	55

class Player :
	public Character
{
	friend class	CharAbilityState;

	/*
	目录 方便查找

	[创建 释放][标识相关][基础属性][高级属性][国家][帮会][队伍][PK][防沉迷][复活][称号][战斗技能][生活技能]
	[召唤宠物][坐骑][物品][银行 寄售][商店][任务][答题][交易 摆摊][聊天][安全时限][镖车][双倍经验][互斥状态]
	[Effect][游戏设置][金钱][属性刷新][断线重连][杀人计算荣誉][排行榜][社会关系][代练][场景相关][决斗][召集]
	[重要事件 进入场景 死亡 ......][对消息的封装][AI相关][恢复 自动回血 回蓝 回活力......][消息验证][反外挂 外挂统计]
	[密保杂项][GM指令的辅助函数][Timer杂项][跨场景 移动 位置 杂项][数据库相关][杂项]
	*/
public:
	/*****************************************************************************************************************
	// 创建 释放
	*****************************************************************************************************************/
	Player();
	virtual ~Player();

	virtual void	Clear(void);
	virtual BOOL	Init(const _INIT_OBJECT *pInit, const uchar age);
	virtual void	InitAIObj();

	/*****************************************************************************************************************
	// 标识相关
	*****************************************************************************************************************/
public:
	virtual ObjectClass GetObjType(void) const
	{
		return OBJECT_CLASS_PLAYER;
	}

	GUID_t				GetGUID(void) const;
	virtual bool	HeartBeat(uint32 uTime);

	virtual uint32		GetUniqueID(void) const;

	ConnectorID_t		GetPlayerID();

	NetHandle GetConnector()
	{
		return _player_handle;
	}

	void SetConnector(NetHandle handle)
	{
		_player_handle = handle;
	}

private:
	NetHandle _player_handle = INVALID_NET_HANDLE;

	/*****************************************************************************************************************
	// 基础属性
	*****************************************************************************************************************/
public:
	ID_t				GetWorldID();
	int32				GetAttack();

	int32				Get_Property_MaxStrikePoint(void);

	int32				GetAttrLevel1AttackNear(void);
	int32				GetAttrLevel1AttackFar(void);
	int32				GetAttrLevel1AttackMagic(void);

	int32				GetAttrLevel1Hit(void);
	int32				GetAttrLevel1Miss(void);
	int32				GetAttrLevel1Critical(void);
	int32				GetAttrLevel1MaxHP(void);
	int32				GetAttrLevel1MaxRage(void);

	int32				Get_Property_Str(void);
	int32				Get_BaseProperty_Str(void);
	void				Set_BaseProperty_Str(int32 const nValue);

	int32				Get_Property_Con(void);
	int32				Get_BaseProperty_Con(void);
	void				Set_BaseProperty_Con(int32 const nValue);

	int32				Get_Property_Int(void);
	int32				Get_BaseProperty_Int(void);
	void				Set_BaseProperty_Int(int32 const nValue);

	int32				Get_Property_Dex(void);
	int32				Get_BaseProperty_Dex(void);
	void				Set_BaseProperty_Dex(int32 const nValue);

	int32				GetMaxHP(void);
	int32				Get_BaseProperty_MaxHP(void);
	void				Set_BaseProperty_MaxHP(int32 const nHp);
	int32				Get_Property_HPRegenerate(void);
	int32				Get_BaseProperty_HPRegenerate(void);
	void				Set_BaseProperty_HPRegenerate(int32 const nValue);

	int32				GetMaxMP(void);
	int32				Get_BaseProperty_MaxMP(void);
	void				Set_BaseProperty_MaxMp(int32 const nMp);
	int32				Get_Property_MPRegenerate(void);
	int32				Get_BaseProperty_MPRegenerate(void);
	void				Set_BaseProperty_MPRegenerate(int32 const nValue);

	int32				Get_Property_MaxRage(void);
	int32				GetBaseMaxRage(void);
	void				SetBaseMaxRage(int32 const nRage);
	int32				GetRageRegenerate(void);
	int32				GetBaseRageRegenerate(void);
	void				SetBaseRageRegenerate(int32 const nValue);

	virtual const SCampData* GetBaseCampData(void) const;
	virtual void			SetBaseCampData(const SCampData* pCampData);
	int32				GetCampID(void);
	int32				GetBaseCampID(void) const;
	void				SetBaseCampID(int32_t const nID);
	void				RefixCamp();


	virtual int32_t	GetModelID(void);
	virtual int32_t	Get_BaseProperty_ModelID(void) const;
	virtual void	Set_BaseProperty_ModelID(int32 const nID);

	BOOL				IsHideName();

	virtual BOOL		IsUnbreakable(void);

	float				Get_Property_MoveSpeed(void);
	int32				Get_BaseProperty_MoveSpeed(void);
	void				Set_BaseProperty_MoveSpeed(int32_t const nValue);

	int32				Get_Property_AttackSpeed(void);
	int32				Get_BaseProperty_AttackSpeed(void);
	void				Set_BaseProperty_AttackSpeed(int32_t const nValue);

	virtual int32_t	Get_Property_Miss(void);
	virtual int32_t	Get_BaseProperty_Miss(void);
	virtual void	Set_BaseProperty_Miss(int32_t const nValue);

	int32				GetIattributeMiss();

	virtual int32_t	Get_Property_Hit(void);
	virtual int32_t	Get_BaseProperty_Hit(void);
	virtual void	Set_BaseProperty_Hit(int32_t const nValue);

	int32				GetIattributeHit();


	int32				GetIattributeCritiacalRefix();
	int32				GetEquipCriticalHurt();
	int32_t				GetCriticalHurt();

	virtual int32_t	Get_Property_Critical(void);
	int32				Get_BaseProperty_Critical(void);
	void				Set_BaseProperty_Critical(int32_t const nValue);

	virtual int32			GetDefenceNear(void);
	virtual int32			GetBaseDefenceNear(void);
	virtual void			SetBaseDefenceNear(int32_t const nValue);

	virtual int32			GetDefenceFar(void);
	virtual int32			GetBaseDefenceFar(void);
	virtual void			SetBaseDefenceFar(int32_t const nValue);

	virtual int32			GetAttackNear(void);
	virtual int32			GetBaseAttackNear(void);
	virtual void			SetBaseAttackNear(int32_t const nValue);

	virtual int32			GetAttackFar(void);
	virtual int32			GetBaseAttackFar(void);
	virtual void			SetBaseAttackFar(int32_t const nValue);

	int32				GetToughness(void);
	int32				GetBaseToughness(void);
	void				SetBaseToughness(int32_t const nValue);

	virtual int32			GetNearAttReduce(void);
	virtual int32			GetBaseNearAttReduce(void);
	virtual void			SetBaseNearAttReduce(int32_t const nValue);

	virtual int32			GetFarAttReduce(void);
	virtual int32			GetBaseFarAttReduce(void);
	virtual void			SetBaseFarAttReduce(int32_t const nValue);

	virtual int32			GetMagicAttReduce(void);
	virtual int32			GetBaseMagicAttReduce(void);
	virtual void			SetBaseMagicAttReduce(int32_t const nValue);

	virtual int32			GetDreadAttResist(void);
	virtual int32			GetBaseDreadAttResist(void);
	virtual void			SetBaseDreadAttResist(int32_t const nValue);

	virtual int32			GetComaAttResist(void);
	virtual int32			GetBaseComaAttResist(void);
	virtual void			SetBaseComaAttResist(int32_t const nValue);

	virtual int32			GetHushAttResist(void);
	virtual int32			GetBaseHushAttResist(void);
	virtual void			SetBaseHushAttResist(int32_t const nValue);

	virtual int32			GetUnArmyAttResist(void);
	virtual int32			GetBaseUnArmyAttResist(void);
	virtual void			SetBaseUnArmyAttResist(int32_t const nValue);

	virtual int32			GetSkillSpeedAttResist(void);
	virtual int32			GetBaseSkillSpeedAttResist(void);
	virtual void			SetBaseSkillSpeedAttResist(int32_t const nValue);

	virtual int32			GetMoveSpeedAttResist(void);
	virtual int32			GetBaseMoveSpeedAttResist(void);
	virtual void			SetBaseMoveSpeedAttResist(int32_t const nValue);

	int32				Get_Property_AttackMagic(void);
	int32				Get_BaseProperty_AttackMagic(void);
	void				Set_BaseProperty_AttackMagic(int32_t const nValue);

	int32				Get_Property_DefenceMagic(void);
	int32				Get_BaseProperty_DefenceMagic(void);
	void				Set_BaseProperty_DefenceMagic(int32_t const nValue);

	int32				Get_Property_AttackCold(void);
	int32				Get_BaseProperty_AttackCold(void);
	void				Set_BaseProperty_AttackCold(int32_t const nValue);

	int32				Get_Property_DefenceCold(void);
	int32				Get_BaseProperty_DefenceCold(void);
	void				Set_BaseProperty_DefenceCold(int32_t const nValue);

	int32				Get_Property_AttackFire(void);
	int32				Get_BaseProperty_AttackFire(void);
	void				Set_BaseProperty_AttackFire(int32_t const nValue);

	int32				Get_Property_DefenceFire(void);
	int32				Get_BaseProperty_DefenceFire(void);
	void				Set_BaseProperty_DefenceFire(int32_t const nValue);

	virtual int32_t	Get_Property_AttackLight(void);
	virtual int32_t	Get_BaseProperty_AttackLight(void);
	virtual void	Set_BaseProperty_AttackLight(int32_t const nValue);

	virtual int32_t	    Get_Property_DefenceLight(void);
	virtual int32_t	    Get_BaseProperty_DefenceLight(void);
	virtual void	    Set_BaseProperty_DefenceLight(int32_t const nValue);

	int32				Get_Property_AttackPoison(void);

	int32				Get_Property_DefencePoison(void);
	int32				Get_BaseProperty_DefencePoison(void);
	void				Set_BaseProperty_DefencePoison(int32_t const nValue);

	int32				Get_Property_ReduceSlowerDuration(void);

	int32				Get_Property_ReduceWeakenDuration(void);

	int32				Get_Property_ReduceFaintDuration(void);

	int32				Get_Property_ReducePoisonedDuration(void);

	int32				GetVisionRange(void);

	int32				GetProfessionReduce(int32 nTarProfession);
	int32				GetProfessionIncrease(int32 nTarProfession);

	int32				GetInherenceBalanceRefixForItem(PLAYER_PROPERTY_LEVEL4_BALANCE index);

	virtual void		SetName(const char* pszName);
	virtual const char* GetName(void) const;
	virtual void		SetHP(int32_t nHP);
	virtual int32		GetHP(void);
	virtual void		SetMP(int32_t nMP);
	virtual int32		GetMP(void);
	virtual void		SetLevel(int32_t nLevel);
	virtual int32		GetLevel(void) const;

	int32				GetBaseIntAttr_EX(CharIntProperty::Index_T nIndex);
protected:
	virtual int32_t		GetHPNoClip(void);
	/*****************************************************************************************************************
	// 高级属性
	*****************************************************************************************************************/
public:
	uint32					Get_Property_HairColor() const;
	void					SetHairColor(uint32 haircolor);
	uchar					Get_Property_HairModel() const;
	void					SetHairModel(uchar hairmodel);
	uchar					Get_Property_FaceModel() const;
	void                    SetFaceModel(uchar byModel);

	void					SetAlterPlayerExp(uint64_t AlterExp);
	void					SetAlterPlayerExpEx(uint64_t AlterExp);
	uint64_t				GetPlayerExp();
	void					SetPlayerExp(uint64_t uExp);
	void					DecreasePlayerExp(uint64_t nExp);
	virtual bool			IsPlayerExpFull();

	virtual uint32			GetDataID(void) const;
	virtual void			SetPortraitID(int32 nID);
	virtual int32			GetPortraitID(void) const;
	BOOL					GetSex();
	int32					GetCountry();
	int32_t					GetProfession();
	void					SetProfession(int32_t Profession);


	void					ValidatePlayerID();

	uint16					GetWenCai();
	void					SetWenCai(uint16 nWenCai);

	int32					GetRongYu();
	void					SetRongYu(int32 nRongYu);

	int32					GetShengWang();
	void					SetShengWang(int32 nShengWang);

	int32					GetHotValue();
	void					SetHotValue(int32 nHotValue);

	void					SetExploit(int32_t nExploit);
	int32_t					GetExploit();

	void					SetExploitDay(int16 nDay);
	int16					GetExploitDay();

	int32					Get_Property_GoodBadValue();
	int32					Set_Property_GoodBadValue(int32 nValue);
	int32					IncGoodBadValue(int32 nValue);
	int32					DecGoodBadValue(int32 nValue);

	int32					GetHonor();
	void					SetHonor(int32 nHonor);
	int32					GetFeastScore();
	void					SetFeastScore(int32 iFeastScore);

	uint32					GetCurInherenceExp();
	void					SetCurInherenceExp(uint32 nInherenceExp);
	void					DecCurInherenceExp(uint32 nInherenceExp);
	uint32					GetNextInherenceExp();
	uint32					GetNextInherenceMoney();
	uint32					GetNextInherenceItem();
	uint16					GetInherenceLevel();
	uint32					RefixInherenceExp(uint32 nInherenceExp);
	int32					GetGuildSkillAllPoint();
	void					SetGuildSkillAllPoint(int32 nallPoint);
	void					CountGuildSkillAllPoint();
	bool					IsGuildSkill(int32 nSpelllID);
private:
	int32					m_GuildSkillAllPoint;



	uint32			GetBattleHonour();

	/*****************************************************************************************************************
	// 社会关系
	*****************************************************************************************************************/
public:
	virtual BOOL		IsEnemy(Character* pCharacter);
	virtual BOOL		IsFriend(Character* pCharacter);
	virtual BOOL		IsPartner(Character* pCharacter);
	BOOL				IsMySpouse(Player& rPlayer);
	virtual void		Teleport(const GLPos* pos, uchar bShowChangeState = TRUE);
	

	BOOL				GetRelationHeartBeatFlag() const;
	const GUID_TYPE* GetDetailRelation(int32 index) const;

private:
	GUID_TYPE			m_anHaveSendDetailInfo[MAX_RELATION_SIZE];
	BOOL				m_bActiveDetailRelationInfoHeartBeat;
	uint32				m_nSendRelationDetailDataLastTime;

	/*****************************************************************************************************************
	// 复活
	*****************************************************************************************************************/
public:

protected:	

	_RELIVE_INFO				m_DefaultReliveInfo;

	/*****************************************************************************************************************
	// 称号
	*****************************************************************************************************************/
public:
	

	const char*				GetCurCountryTitleName();
	const char*				GetCurGuildTitleName();
	const char*				GetCurNormalTitleName();
	const char*				GetTitleNameByID(int32_t iTitleID, int32_t iSex);
	void					AddTitleBuff(int32_t buffID1, int32_t buffID2);
	void					DelTitleBuff(int32_t buffID1, int32_t buffID2);

	const char*				GetGuildTitleName() const;



	void					SetNormalTitleName(const char *pszTitle, int32_t iSize);
	const char*				GetNormalTitleName() const;


private:
	Time_t					m_TitleLoginTime;

	/*****************************************************************************************************************
		// 战斗技能
		*****************************************************************************************************************/
public:
	void				SetCommonSpellPoints(int32 nS, int32 Point);

	int32				GetRemainSpellPoints();
	void				SetRemainSpellPoints(int32 Point);

	int32				GetSpellPoints(int32 nS);
	void				SetSpellPoints(int32 nS, int32 Point);
	virtual int32		SpellCharacter(Character* pCharacter, SpellID_t SkillID, BOOL bNow = FALSE);

	BOOL				SpellRefixItemAttr(int32 nSlotID, int32 nItemType, int32 nATTRID, int16& nAttrValue);
	BOOL				SpellDepleteItem(void);
	virtual BOOL		SpellHaveSkill(SpellID_t const nID) const;
	virtual BOOL		SpellModify(SpellID_t const nID, int32 const nModifyFlag);
	virtual void		SpellOnEquipItem(void);

	void				SetSpellLevel(SpellID_t const nID, int32 const nLevel);

	const _PLAYER_SPELL* GetSpell(int32 const nID);

	const _SPELL_LIST& GetSpellList(void);

	virtual Time_t		GetCooldownRemained(CooldownID_t const nID) const;
	virtual BOOL		IsCooldowned(CooldownID_t const nID) const;
	virtual void		SetCooldown(CooldownID_t const nID, Time_t nCooldown);
	virtual BOOL		HeartBeat_Cooldown(uint32 uTime = 0);
	void				ClearCoolDown(void);
	virtual BOOL		HaveSpell(SpellID_t const nID) const;

protected:
	void				ReloadAllPassiveSpell();
	virtual void		RefixByInherence(int32& nDamage, Character* const pAttacker, BOOL bDOT, BOOL bPKRateCtr);
private:
	void				InitSpellList();
	BOOL				RegisterSpell(SpellID_t const nID);
	BOOL				UnregisterSpell(SpellID_t const nID);

	Time_t				m_nCommonCooldown;

	/*****************************************************************************************************************
	// 生活技能
	*****************************************************************************************************************/
public:
	const _ABILITY_LIST* GetAbilityList() const;
	SkillOpera* GetAbilityOpera();
	void						reset_AbilityOpera();
	void						interruptCurrentAbilityOpera();
	const BOOL					IsAbilityHaveLearned(SpellID_t abilityid) const;
	const int32					GetAbilityLevel(const SpellID_t abilityid) const;
	void						SetAbilityLevel(const SpellID_t abilityid, int32 lvl);
	const int32					GetAbilityExp(const SpellID_t abilityid) const;
	void						SetAbilityExp(const SpellID_t abilityid, int32 exp);
	const BOOL					IsPrescrHaveLearned(const PrescriptionID_t prescrid) const;
	void						SetPrescrLearnedFlag(const PrescriptionID_t prescrid, BOOL flag);
protected:
	virtual OPT_RESULT				BHV_UseAbility(void);
private:
	SkillOpera					m_LastOpera;
	/*****************************************************************************************************************
	// 召唤宠物
	*****************************************************************************************************************/
public:
	static void		CalculatePetDetailAttrib
	(
		SCDetailAttribPet& rMsg,
		Item* pPetItem,
		BOOL bUpdateSkill,
		int32 iIndex
	);

	void RefeshHorseDetailAttrib(SHorseGuid guidPet, BOOL bUpdateSkill);
	OPT_RESULT				TestCallUpPet(const SHorseGuid guidPet);
	OPT_RESULT				CallUpPet(void);


	void				BabyToAttack(void);
	void				BabyToStopAttack(void);

	void				BabyToProtectMe(ObjID_t iObjID);
	

	
	int32	GetMonsterPetDataID() const;
	void SetMonsterPetDataID(int32 val);
	void SetMountModelID(int32 nModelID);

protected:	

protected:
	Pet						*m_pPet[MAX_MONSTER_PET_TAKE];
private:
	int32_t					m_iMaxPetCanTake;
	HorseContainer*			mPetItem;



	/*****************************************************************************************************************
	// 坐骑
	*****************************************************************************************************************/
public:
	OPT_RESULT		FreePetToNature(PetLogRecordInfo *pPetLogParam, SHorseGuid guidPet);
	BOOL		CaptureHorse(PetLogRecordInfo *pPetLogParam, ObjID_t PetID);
	BOOL		CaptureBeastie(PetLogRecordInfo* pPetLogParam, ObjID_t beastieID);
	BOOL		AddHorseToHuman(_HORSE_DB* pPetDB, PetLogRecordInfo* pPetLogParam);
	OPT_RESULT		ReCallHorse(void);
	int32_t		GetHorseCount(void) const;
	_HORSE_DB		*GetHorseDB(int32_t nIndex) const;
	_HORSE_DB		*GetEmptyHorseDB();
	Item* GetHorseItem(SHorseGuid guid);
	int32		GetHorseIndexByGUID(SHorseGuid guid);
	SHorseGuid	GetGUIDOfCallUpHorse();
	void		ChangeCallUpHorse(SHorseGuid val);
	bool		UpdateHorseExp(int32 iExp);
	bool		UpdateHorseExpAbsolute(int32 iExp);  //增加经验绝对值

	SHorseGuid	GetLastHorseGuid();
	void		SetLastHorseGuid(SHorseGuid horseGuid);

	void	HorseEventScript(int32 iReason);

	void		HorseHeartBeat(uint32 uTime);
	BOOL		IsCanTakeMoreHorse(int32 nCount = 1);

	BOOL IsHaveHorseFindingMate() const
	{
		return !m_guidFindingMateHorse.IsNull();
	}

	void SetFindingMateHorseGUID(SHorseGuid guid)
	{
		m_guidFindingMateHorse = guid;
	}

	SHorseGuid GetFindingMateHorseGUID() const
	{
		return m_guidFindingMateHorse;
	}

	void		InitHorseUsedSkillList();
	void		StartPassiveSkillList(SpellID_t iSkillID, int32 iSkillLevel, int32 iIndex);
protected:	
	void			InitHorseIfRide();
	BOOL			AddHorse(_HORSE_DB *pPetDB);

	BOOL			RemovePet(PetLogRecordInfo *pPetLogParam, SHorseGuid guid);

protected:
	int32_t			m_iDataID;
	HorseAttrCalculater	m_ActiveHorse;
	SHorseGuid		m_guidFindingMateHorse;
	SHorseGuid		m_guidLastHorse;

	/*****************************************************************************************************************
	// 物品
	*****************************************************************************************************************/
public:
	
	SItemEffect *ItemEffect(uchar AttrType)
	{
		KCheck(AttrType < IPROPERTY_NUMBER);
		return &m_pItemEffect[AttrType];
	}

	virtual _ITEM_ALLVALUE ItemValue(uchar AttrType)
	{
		KCheck(AttrType < IPROPERTY_NUMBER);
		return m_pItemEffect[AttrType].m_Attr;
	}


	uint16				GetEquipVer();
	void				SetEquipVer(uint16 Ver);
	uint32				GetEquipID(PLAYER_EQUIP equipPoint);
	uint32				GetEquipLevel(PLAYER_EQUIP equipPoint);

	


public:
	uint32						m_iLastUpdateEquipTerm;
protected:	
	CTinyTimer					m_ItemTimer;
private:
	SItemEffect				m_pItemEffect[IPROPERTY_NUMBER];

	int32_t						m_EffectSkillNum;
	_ITEM_EFFECT_SKILL			m_EquipEffectSkill[HEQUIP_NUMBER * MAX_EQUIP_EFFECT_SKILL];

	int32_t						m_EquipEffectNum;
	_EQUIP_EFFECT				m_EquipEffect[HEQUIP_NUMBER + MAX_ITEM_SET_ATTR];

	
	uint16						m_EquipVer;

	

	/*****************************************************************************************************************
	// 银行 寄售
	*****************************************************************************************************************/
public:
	BOOL IsBankOpen()
	{
		return BankIsOpen;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetBankOpen(BOOL bopen)
	{
		BankIsOpen = bopen;
	}
	

private:
	BOOL						BankIsOpen;


	/*****************************************************************************************************************
	// 商店
	*****************************************************************************************************************/
public:
	

	void Shop(SShop *pShop)
	{
		m_pShop = pShop;
	};

	SShop *Shop()
	{
		return m_pShop;
	};
private:
	SShop			*m_pShop;
	int32_t			m_nCurSold;
	/*****************************************************************************************************************
			// 双倍经验
			*****************************************************************************************************************/
public:
	void		SetExpMult(float fMult);
	float		GetExpMult();
	float		GetBaseExp();

	int32		GetExpMultRefix(void);

	void		SetWanFaExpMult(float fMult);
	float		GetWanFaExpMult();

	float		GetEquipExpMult();

protected:
	float		m_fExpMult;
	float		m_fWanFaExpMult;
	/*****************************************************************************************************************
	// 任务
	*****************************************************************************************************************/

public:
	virtual void	OnQuestHaveDoneFlagsChanged(QuestID_t idQuest);
	virtual void	OnQuestParamChanged(uint32 uIndexQuest, uint32 uIndexParam, int32 index = 0);
	virtual void	OnAddQuest(uint32 uIndex);
	virtual void	OnRemoveQuest(QuestID_t idQuest);


	const SArchiveLoader_Quest* GetQuestList(void) const;
	void					SetQuestHaveDone(QuestID_t idQuest, BOOL bHaveDone);
	BOOL					IsQuestHaveDone(QuestID_t idQuest) const;
	int32_t					IsQuestCompleted(uint32 uIndexQuest) const;
	OPT_RESULT			AddQuest
	(
		QuestID_t	idQuest,
		ScriptID_t	idScript,
		BOOL		bKillObjectEvent = TRUE,
		BOOL		bEnterAreaEvent = TRUE,
		BOOL		bItemChangedEvent = TRUE,
		BOOL		bClickNPCEvent = FALSE
	);
	OPT_RESULT			AddQuestEx(QuestID_t idQuest, ScriptID_t idScript);
	OPT_RESULT			SetQuestEvent(QuestID_t idQuest, int32 EventID);
	BOOL				DelQuest(QuestID_t idQuest);
	void				DelQuestByIndex(uint32 uIndex);
	uint32_t			GetQuestIndexByID(QuestID_t idQuest) const;
	BOOL				IsHaveQuest(QuestID_t idQuest) const;
	void				SetQuestParam(uint32 uIndexQuest, uint32 uIndexParam, int32 nValue);
	int32				GetQuestParam(uint32 uIndexQuest, uint32 uIndexParam) const;
	void				SetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam, uint32 nValue);
	uint32				GetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam) const;
	const OWN_QUEST* GetQuest(uint32 uIndex) const;

	int32_t				GetQuestData(int32_t nIndex);
	void				SetQuestData(int32_t nIndex, int32_t nData);

	int32_t				GetQuestDataByBit(int32_t nIndex,int32_t nOffset,int32_t nSize );
	void				SetQuestDataByBit(int32_t nIndex,int32_t nOffset,int32_t nSize, int32_t nData);

	int32_t				IfCanRecvQuest(const _QUEST_DATA_t* pData, ObjID_t targetId);

	/*****************************************************************************************************************
	// 答题
	*****************************************************************************************************************/
public:
	void SetQuizGameCount(int32_t num)
	{
		m_QuizGameCount = num;
	}
	int32_t GetQuizGameCount()
	{
		return m_QuizGameCount;
	}
	void SetQuizGameQuestionIdx(int32_t nIdx)
	{
		m_QuizQuestionCycle = nIdx;
	}
	int32_t GetQuizGameQuestionIdx()
	{
		return m_QuizQuestionCycle;
	}
	void SetQuizRightCount(int32_t num)
	{
		m_QuizRightCount = num;
	}
	int32_t GetQuizRightCount()
	{
		return m_QuizRightCount;
	}
	void SetQuizWrongCount(int32_t num)
	{
		m_QuizWrongCount = num;
	}
	int32_t GetQuizWrongCount()
	{
		return m_QuizWrongCount;
	}
	void IncQuizGameCount()
	{
		++m_QuizGameCount;
	}
	void IncQuizGameQuestionIdx()
	{
		++m_QuizQuestionCycle;
	}
private:
	int32_t	m_QuizGameCount;
	int32_t	m_QuizQuestionCycle;
	int32_t	m_QuizRightCount;
	int32_t	m_QuizWrongCount;


	uint32_t GetChatNearTimeStamp()
	{
		return m_ChatNearTimeStamp;
	}

	void SetChatNearTimeStamp(uint32_t i)
	{
		m_ChatNearTimeStamp = i;
	}

	uint32_t GetChatWorldTimeStamp()
	{
		return m_ChatWorldTimeStamp;
	}

	void SetChatWorldTimeStamp(uint32_t i)
	{
		m_ChatWorldTimeStamp = i;
	}

	uint32_t GetChatUserTimeStamp()
	{
		return m_ChatUserTimeStamp;
	}

	void SetChatUserTimeStamp(uint32_t i)
	{
		m_ChatUserTimeStamp = i;
	}

	uint32_t GetChatCountryTimeStamp()
	{
		return m_ChatCountryTimeStamp;
	}

	void SetChatCountryTimeStamp(uint32_t i)
	{
		m_ChatCountryTimeStamp = i;
	}

	uint32_t GetChatTooFastTimes()
	{
		return m_ChatTooFastTimes;
	}

	void SetChatTooFastTimes(uint32_t i)
	{
		m_ChatTooFastTimes = i;
	}

	void IncChatTooFastTimes()
	{
		m_ChatTooFastTimes++;
	}

	void SetMailTimeStamp(uint32_t uTime)
	{
		m_MailTimeStamp = uTime;
	}

	uint32_t GetMailTimeStamp()
	{
		return m_MailTimeStamp;
	}

	void SetMailTooFastTimes(uint32_t uTimes)
	{
		m_MailTooFastTimes = uTimes;
	}

	uint32_t GetMailTooFastTimes()
	{
		return m_MailTooFastTimes;
	}

	void IncMailTooFastTimes()
	{
		m_MailTooFastTimes++;
	}



protected:
	uint32		m_ChatNearTimeStamp;
	uint32		m_ChatWorldTimeStamp;
	uint32		m_ChatUserTimeStamp;
	uint32		m_ChatCountryTimeStamp;
	uint32		m_ChatTooFastTimes;

	uint32		m_MailTimeStamp;
	uint32		m_MailTooFastTimes;

private:
	uint32		m_nChatReport_LastTime;

	

public:
	BOOL		m_bIsPasswdUnlock;
	BOOL		m_bProtectUnlock;
	uchar		m_OnlinePasswdErrorCount;
private:
	uint32		m_LoginProtectTime;  //上线保护时间， 玩家设置的，单位分钟。 安全时限时间
	uint32		m_RemainProtectTime; //剩余保护时间， 单位秒

	

	
	
	

private:
	_EFFECT_LIST	m_oEffectList;

	/*****************************************************************************************************************
	// 断线重连
	*****************************************************************************************************************/
public:
	void SetReconnect(BOOL bValue)
	{
		m_bReconnect = bValue;
	}

	BOOL GetReconnect()
	{
		return m_bReconnect;
	}

	void SetInitBecauseReconnect(BOOL bValue)
	{
		m_bInitBecauseReconnect = bValue;
	}

	BOOL GetInitBecauseReconnect()
	{
		return m_bInitBecauseReconnect;
	}

	void SetNewGamePlayerID(ConnectorID_t value)
	{
		m_NewGamePlayerID = value;
	}

	ConnectorID_t GetNewGamePlayerID()
	{
		return m_NewGamePlayerID;
	}

private:
	BOOL			m_bReconnect;
	BOOL			m_bInitBecauseReconnect;
	ConnectorID_t	m_NewGamePlayerID;
	

private:
	FightInfo	m_aFightInfo[FIGHT_INFO_NUM];

	/*****************************************************************************************************************
	// 排行榜
	*****************************************************************************************************************/
public:
	uint32_t GetTopListVersion() const
	{
		return m_iTopListVersion;
	}

	void SetTopListVersion(int32_t val)
	{
		m_iTopListVersion = val;
	}

private:
	uint32		m_iTopListVersion;

	

	/*****************************************************************************************************************
	// 场景相关
	*****************************************************************************************************************/
public:

	uint8			GetMapIsNullInNotifyUser() {return m_MapIsNullInNotifyUser;}
	void			SetMapIsNullInNotifyUser(uint8 uValue) {m_MapIsNullInNotifyUser = uValue;}

	BOOL IsFirstEnterMap()
	{
		return m_bFirstEnterMap;
	}

	void SetFirstEnterMap(BOOL bFirstEnter)
	{
		m_bFirstEnterMap = bFirstEnter;
	}

	BOOL			IsFirstEnterGame();
	void			ClearFirstEnterGame();

	uint32_t GetAreaTimeStamp()
	{
		return m_uTimeStamp;
	}

	void ResetAreaTimeStamp(uint32_t newTimeStamp)
	{
		m_uTimeStamp = newTimeStamp;
	}

protected:
	void		CheckArea();
public:
	BOOL		m_bFirstEnterMap;
protected:
	uint32		m_uAreaID;
	ScriptID_t	m_uAreaScript;
	uint32		m_uTimeStamp;
private:
	uint8		m_MapIsNullInNotifyUser;
	

	

	/*****************************************************************************************************************
	// 重要事件 进入场景 死亡 ......
	*****************************************************************************************************************/
public:
	virtual void	OnEnterMap(void);

	virtual void	OnEnterMapSuccess(void);

	virtual void	OnRegisterToGrid(void);
	virtual void	OnUnregisterFromGrid(void);
	virtual void	OnEvent_KillObject(ObjID_t idObj);

	virtual void	OnEvent_PetChanged(uint32 uPetDataID);
	virtual void	OnEvent_ItemChanged(uint32 uItemDataID, int32 nChangeType);
	

	

	/*****************************************************************************************************************
	// AI相关
	*****************************************************************************************************************/
public:
	Behavior_Player* GetHumanAI(void)
	{
		return ((Behavior_Player*)m_pAI_Character);
	}
	AvoidMonsterOverlap* GetAvoidOverLap()const
	{
		return m_pAvoidOverlap;
	}

	ObjID_t					GetAssistantID(void) const
	{
		return m_AssistantID;
	}

	void					SetAssistantID(ObjID_t id)
	{
		m_AssistantID = id;
	}

	PlayerArchive* GetDB()
	{
		return mDB;
	}

	void			SetCurTarget(ObjID_t idTarget);
	ObjID_t			GetCurTarget(void) const;
	void			SetPatrolID(int32_t nIndex);
	int32_t			GetPatrolID(void) const;
	void			SetCurrentPathNode(int32_t nNode);
	int32_t			GetCurrentPathNode(void) const;
protected:
	AvoidMonsterOverlap	*m_pAvoidOverlap;
	ObjID_t			m_AssistantID;
	ObjID_t			m_CurTargetID;
	
	uint32			GetElapsedVigorRecoverTick() { return m_nElapsedVigorRecoverTick; };
	void			SetElapsedVigorRecoverTick(uint32_t n){ m_nElapsedVigorRecoverTick = n; };
	virtual void	ClearRageRecoverTick();

protected:
	CTinyTimer		m_PKValueRecoverTimer;
private:
	uint32			m_nElapsedVigorRecoverTick;

	/*****************************************************************************************************************
	// 消息验证
	*****************************************************************************************************************/
public:
	

	uint32_t GetVerifyOffset()
	{
		return m_VerifyOffset;
	}
	
private:
	uint32		m_VerifyOffset;
	MSG_ID		m_MsgIdOffset;	/* 动态变化的消息ID */
	uint32		m_MsgCount;	/* 玩家消息计数 */
	

private:
	uint32		m_VipLevel;

	BOOL		m_IsBindPWCard; /* 是否绑定了密保卡 */
	BOOL		m_IsBindPhone;
	BOOL		m_IsPunch;		//是否打过卡了
	/*****************************************************************************************************************
	// GM指令的辅助函数
	*****************************************************************************************************************/
public:
	void			SetGod(uchar bGod);
	BOOL			IsGod(void) const;

	void			SetGMGodStealth(uchar bSet);
	BOOL			GetGMGodStealth(void) const;
protected:
	uchar			m_bGod;
	uchar			m_bGodStealth;
	/*****************************************************************************************************************
		// 游戏设置
		*****************************************************************************************************************/
public:
	const _SUIT_SETTING& GetEquipSuitSetting(uint32 nEquipSuitNum) const;
	virtual void			SetEquipSuitSetting(_SUIT_SETTING& nSuitSetting, uint32 nEquipSuitNum);
	const SArchiveLoader_Setting* GetSettingList(void);
	void					SetSettingData(int32 nType, _PLAYER_SETTING* Value);
	const SArchiveLoader_Setting* GetConstSettingList(void) const;
	/*****************************************************************************************************************
		// 金钱
	*****************************************************************************************************************/
public:
	uchar	DecreaseSiller(int32_t iMoneyRequire);
	void	IncreaseSiller(int32_t iMoneyRequire);
	uchar	DecreaseBindSiller(int32_t iMoneyRequire);
	void	IncreaseBindSiller(int32_t iMoneyRequire);
	uchar	SpendGold(int32_t iGoldRequire);
	void	IncreaseMoney(uchar MoneyType, int32 nCount);
	void	ReduceMoney(uchar MoneyType, int32 nCount);
	void	IncreaseCharGold(uint32 nCount);
	void	ReduceCharGold(int32 nCount);
	void	DecreaseBindGold(int32 bindGold);
	void	IncreaseBindGold(int32 bindGold);
	int32			GetMoneyByType(int32 type);
	bool			IsEnoughGold(int32 iGoldRequire);
	bool			IsEnoughMoney(int32 iMoneyRequire);
	uchar			GetSillerModeToSpend(int32 iMoneyRequire);
	int32			GetSiller();
	int32			GetCharGold();
	int32			GetGold();
	int32			GetBindSiller();
	int32			GetBindGold();
	uchar			GetSillerMode();
	void			SetSillerMode(uchar sillerMode);
	uchar			GetGoldMode();
	void			SetGoldMode(uchar goldMode);

	uint32			GetAccountGold();
	void			SetAccountGold(uint32 gold);

	void			SetStockAccountEnable(BOOL flag);
	bool			IsEnableStockAccount();

private:
	void			SetSiller(int32 siller);
	void			SetBindSiller(int32 bindSiller);
	void			SetBindGold(int32 bindGold);

private:
	uint32			m_AccountGold;
	BOOL			m_IsEnableStockAccount;
	/*****************************************************************************************************************
		// 属性刷新
		*****************************************************************************************************************/
public:
	virtual void	InitBackupAttr();
	virtual void	SendMsg_RefeshAttrib(void);
	virtual void	RequestBaseProperty(Player* pTargetHuman, BASEPROPERTY_REFESH_MODE nMode = REFESH_ALL);
	void			AskMsg_DetailAttrib(Player* pAsker);
	BOOL			CheckRefeshBase(
		SCCharHumanBaseAttrib* pBaseMsg,
		BASEPROPERTY_REFESH_MODE	nMode = SEND_TO_SELF
	);
	BOOL			CheckRefeshDetail(SCDetailAttrib* pDetailMsg);
	BOOL			CheckRefeshEquip(SCCharEquipment* pEquipMsg);
	BOOL			CheckRefeshQuest(SCQuestListRefresh* pQuestMsg);

	void			UpdateBackUpAttrib(void);
	void			UpdateBaseBackUp(void);
	void			UpdateDetailBackUp(void);
	void			UpdateEquipBackUp(void);
	void			UpdateQuestBackUp(void);

	void			SendMsg_RefeshAttribToMyself(void);
	void			SendMsg_RefeshAttribToOther(void);

	void			RefreshAttrToWorld(uint32 uTime);
	void			RefreshAttrToWorldImmediately();

protected:
	void			RefeshAttrMsg();

public:
	BOOL				m_bUpdateAttr;
	CTinyTimer			m_UpdateTimer;
	CTinyTimer			m_RefreshAttrToWorldTimer;
protected:
	CTinyTimer			m_RefeshTimer;
	_PLAYER_ATTR_BACKUP	m_AttrBackUp;


	SCCharHumanBaseAttrib* mSCCharHumanBaseAttrib = nullptr;
	SCCharEquipment* mSCCharEquipment = nullptr;
	SCQuestListRefresh* mSCQuestListRefresh = nullptr;
	/*****************************************************************************************************************
	// 跨场景 移动 位置 杂项
	*****************************************************************************************************************/
public:
	void			SetChangeMapState(uchar bChangeSceneState);
	uchar			GetChangeMapState(void) const;
	uchar getMoveIndex()
	{
		return m_MoveIndex;
	}

	void setMoveIndex(uchar index)
	{
		m_MoveIndex = index;
	}

	MapID_t		GetTransMapID();
	void		SetTransMapID(MapID_t id);
	GLPos	*GetTransWorldPos();
	void		SetTransWorldPos(const GLPos *pPos);

	BOOL		GetPosition(GLPos &Pos, const GLPos *pRefPos, float fDir);

public:
	_HORSE_DB	m_ComposeNewPetDB;		//合成后的骑参
	_HORSE_DB	m_ComposeMainPetDB;	//合成时的主骑参
	BOOL	    m_bComposeRepent;   //合成时是否可反悔
	BOOL	    m_bComposeBest;   //合成成异兽
protected:
	uchar		m_bChangeMapState;
private:
	uchar		m_MoveIndex;

	MapID_t		m_TransMapID;
	GLPos	m_TransWorldPos;

	/*****************************************************************************************************************
	// 数据库相关
	*****************************************************************************************************************/
public:
	void			ValidateShareMem(BOOL bForceAll);
protected:
	PlayerArchive*		mDB = nullptr;
	
public:
	_INIT_LIST_NODE *HumanNode()
	{
		return m_pHumanNode;
	}
	int32 GetRuntimeData(int32 index);
	void SetRuntimeData(int32_t index, int32_t value);

	void sendPacket(NetPacket* packet);
public:
	int32_t			m_RuntimeData[MAX_RUNTIME_DATA];
private:

	ObjID_t			m_iTargetForExp;
	int32_t           m_iFeastScore;
	_INIT_LIST_NODE* m_pHumanNode = nullptr;


private:
	BOOL m_bReliveFlagforImpact;	//人物死亡后不复活下线然后在上线时复活的标志

public:
	virtual int32_t	GetAttSpeedAttResist(void);
	virtual int32_t	GetBaseAttSpeedAttResist(void);
	virtual void	SetBaseAttSpeedAttResist(int32_t const nValue);

	virtual int32_t	Get_BaseProperty_AttackPoison(void);
	virtual void	Set_BaseProperty_AttackPoison(int32_t const nValue);

	virtual int32_t Get_Property_Rage(void);
	virtual void	Set_Property_Rage(int32_t nRage);


	virtual void		SetTitle(const char* pszTitle);
	virtual const char* GetTitle(void) const;

	virtual NetPacket* CreateNewObjMsg(void);
	virtual void		DestroyNewObjMsg(NetPacket* pPacket);
	void				SendOperateResultMsg(int32 nCode, int32 nResType);



	virtual _EFFECT_LIST& Effect_GetEffectList(void);
	virtual const uchar		GetTitleType(void) const;

private:
	std::unordered_map<uint32_t, _PLAYER_SPELL> mSkillMap;
public:
	void initSkill();

	ItemContainer* GetBankPetContain();
	ItemContainer* GetBankContain();
	ItemContainer* GetBaseContain();
	ItemContainer* GetExtraContain();
	ItemContainer* GetExtraBagContain(int32 nIndex);
	ItemContainer* GetEquipContain();
	ItemContainer* GetPetContain();

private:
	float	m_fWallow = 1.0f;
public:
	void			SetWallow(float fWallow)
	{
		m_fWallow = fWallow;
	}
	float			GetWallow(void) const
	{
		return m_fWallow;
	}

private:
	PlayerBaseContainer			m_EquipItem;
	PlayerBaseContainer			m_BaseItem;
	//扩展背包容器
	PlayerExtraBagContainer		m_ExtraContainerItem;

	//扩展背包中的物品
	PlayerExtraBag				m_ExtraBagItem[MAX_EXTRA_BAG_NUM];

	HorseContainer			m_PetItem;
public:
	void updateAttr();
	void updateHorse();
	void updateSkills();
	void updateEquip();
	void updateBag();
	void updateQuest();
	
};

