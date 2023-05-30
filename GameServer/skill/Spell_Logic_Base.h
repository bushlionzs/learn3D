#ifndef SPELL_LOGIC_BASE_H
#define SPELL_LOGIC_BASE_H

#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "gameobject/Player.h"
#include "Spell_Helper.h"
#include "Spell_Interface.h"
#include "StructEffect.h"
#include "SpellDataLoader.h"
#include "Spell_EffectInterface.h"

enum { INVALID_SPELL_ID = INVALID_ID, };
enum { MAX_MULTI_STRIKE_NUMBER = 5, };

enum
{
	NUMBER_OF_COMMON_SPELL		= 20,
	NUMBER_OF_PROFESSION_SPELL	= 30,
	NUMBER_OF_ITEM_SPELL		= 100,
	NUMBER_OF_PET_SPELL		= 150,
	NUMBER_OF_MONSTER_SPELL		= 100,
	NUMBER_OF_OTHER_SPELL		= 10,
	NUMBER_OF_ALL_SPELL		= NUMBER_OF_COMMON_SPELL +NUMBER_OF_PROFESSION_SPELL *PROFESSION_NUMBER +NUMBER_OF_PET_SPELL +NUMBER_OF_ITEM_SPELL +NUMBER_OF_MONSTER_SPELL +NUMBER_OF_OTHER_SPELL,
};
typedef enum	//技能逻辑ID	 add by shangy
{
	INVALID_SPELL_LOGIC_ID			= INVALID_ID,
	IMPACTS_TO_TARGET			= 0,
	IMPACTS_TO_TARGET_AND_SELF,
	TELEPORT_AND_IMPACTS,
	IMPACTS_TO_TARGET_AND_SELF_FOR_RUN,
	ARMOR_MASTERY				= 8,
	WEAPON_MASTERY				= 9,
	COMMON_SPELL_001			= 10,
	COMMON_SPELL_002,
	COMMON_SPELL_003,
	COMMON_SPELL_004,
	WUSHI_SPELL_001				= IMPACTS_TO_TARGET + NUMBER_OF_COMMON_SPELL,		/* 20 */
	WUSHI_SPELL_002,
	WUSHI_SPELL_003,
	WUSHI_SPELL_004,
	WUSHI_SPELL_005,
	WUSHI_SPELL_006,
	WUSHI_SPELL_007,
	WUSHI_SPELL_008,
	WUSHI_SPELL_009,
	WUSHI_SPELL_010,
	WUSHI_SPELL_011,
	WUSHI_SPELL_012,
	WUSHI_SPELL_013,
	WUSHI_SPELL_014,
	WUSHI_SPELL_015,
	WUSHI_SPELL_016,
	WUSHI_SPELL_017,
	WUSHI_SPELL_018,
	WUSHI_SPELL_019,
	JIANXIA_SPELL_001			= WUSHI_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,		/* 50 */
	JIANXIA_SPELL_002,
	JIANXIA_SPELL_003,
	JIANXIA_SPELL_004,
	JIANXIA_SPELL_005,
	JIANXIA_SPELL_006,
	JIANXIA_SPELL_007,
	JIANXIA_SPELL_008,
	JIANXIA_SPELL_009,
	JIANXIA_SPELL_010,
	JIANXIA_SPELL_011,
	JIANXIA_SPELL_012,
	JIANXIA_SPELL_013,
	JIANXIA_SPELL_014,
	JIANXIA_SPELL_015,
	JIANXIA_SPELL_016,
	JIANXIA_SPELL_017,
	JIANXIA_SPELL_018,
	JIANXIA_SPELL_019,
	QISHE_SPELL_001				= JIANXIA_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 80 */
	QISHE_SPELL_002,
	QISHE_SPELL_003,
	QISHE_SPELL_004,
	QISHE_SPELL_005,
	QISHE_SPELL_006,
	QISHE_SPELL_007,
	QISHE_SPELL_008,
	QISHE_SPELL_009,
	QISHE_SPELL_010,
	QISHE_SPELL_011,
	QISHE_SPELL_012,
	QISHE_SPELL_013,
	QISHE_SPELL_014,
	QISHE_SPELL_015,
	QISHE_SPELL_016,
	QISHE_SPELL_017,
	QISHE_SPELL_018,
	QISHE_SPELL_019,
	HUOQIANG_SPELL_001			= QISHE_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,		/* 110 */
	HUOQIANG_SPELL_002,
	HUOQIANG_SPELL_003,
	HUOQIANG_SPELL_004,
	HUOQIANG_SPELL_005,
	HUOQIANG_SPELL_006,
	HUOQIANG_SPELL_007,
	HUOQIANG_SPELL_008,
	HUOQIANG_SPELL_009,
	HUOQIANG_SPELL_010,
	HUOQIANG_SPELL_011,
	HUOQIANG_SPELL_012,
	HUOQIANG_SPELL_013,
	HUOQIANG_SPELL_014,
	HUOQIANG_SPELL_015,
	HUOQIANG_SPELL_016,
	HUOQIANG_SPELL_017,
	HUOQIANG_SPELL_018,
	HUOQIANG_SPELL_019,
	XIANZHI_SPELL_001			= HUOQIANG_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 140 */
	XIANZHI_SPELL_002,
	XIANZHI_SPELL_003,
	XIANZHI_SPELL_004,
	XIANZHI_SPELL_005,
	XIANZHI_SPELL_006,
	XIANZHI_SPELL_007,
	XIANZHI_SPELL_008,
	XIANZHI_SPELL_009,
	XIANZHI_SPELL_010,
	XIANZHI_SPELL_011,
	XIANZHI_SPELL_012,
	XIANZHI_SPELL_013,
	XIANZHI_SPELL_014,
	XIANZHI_SPELL_015,
	XIANZHI_SPELL_016,
	XIANZHI_SPELL_017,
	XIANZHI_SPELL_018,
	XIANZHI_SPELL_019,
	SAMAN_SPELL_001				= XIANZHI_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 170 */
	SAMAN_SPELL_002,
	SAMAN_SPELL_003,
	SAMAN_SPELL_004,
	SAMAN_SPELL_005,
	SAMAN_SPELL_006,
	SAMAN_SPELL_007,
	SAMAN_SPELL_008,
	SAMAN_SPELL_009,
	SAMAN_SPELL_010,
	SAMAN_SPELL_011,
	SAMAN_SPELL_012,
	SAMAN_SPELL_013,
	SAMAN_SPELL_014,
	SAMAN_SPELL_015,
	SAMAN_SPELL_016,
	SAMAN_SPELL_017,
	SAMAN_SPELL_018,
	SAMAN_SPELL_019,
	PROFESSION_7_SPELL_001			= SAMAN_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,		/* 200 */
	PROFESSION_7_SPELL_002,
	PROFESSION_7_SPELL_003,
	PROFESSION_7_SPELL_004,
	PROFESSION_7_SPELL_005,
	PROFESSION_7_SPELL_006,
	PROFESSION_7_SPELL_007,
	PROFESSION_7_SPELL_008,
	PROFESSION_7_SPELL_009,
	PROFESSION_7_SPELL_010,
	PROFESSION_7_SPELL_011,
	PROFESSION_7_SPELL_012,
	PROFESSION_7_SPELL_013,
	PROFESSION_7_SPELL_014,
	PROFESSION_7_SPELL_015,
	PROFESSION_7_SPELL_016,
	PROFESSION_7_SPELL_017,
	PROFESSION_7_SPELL_018,
	PROFESSION_7_SPELL_019,
	PROFESSION_8_SPELL_001			= PROFESSION_7_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 230 */
	PROFESSION_8_SPELL_002,
	PROFESSION_8_SPELL_003,
	PROFESSION_8_SPELL_004,
	PROFESSION_8_SPELL_005,
	PROFESSION_8_SPELL_006,
	PROFESSION_8_SPELL_007,
	PROFESSION_8_SPELL_008,
	PROFESSION_8_SPELL_009,
	PROFESSION_8_SPELL_010,
	PROFESSION_8_SPELL_011,
	PROFESSION_8_SPELL_012,
	PROFESSION_8_SPELL_013,
	PROFESSION_8_SPELL_014,
	PROFESSION_8_SPELL_015,
	PROFESSION_8_SPELL_016,
	PROFESSION_8_SPELL_017,
	PROFESSION_8_SPELL_018,
	PROFESSION_8_SPELL_019,
	PROFESSION_9_SPELL_001			= PROFESSION_8_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 260 */
	PROFESSION_9_SPELL_002,
	PROFESSION_9_SPELL_003,
	PROFESSION_9_SPELL_004,
	PROFESSION_9_SPELL_005,
	PROFESSION_9_SPELL_006,
	PROFESSION_9_SPELL_007,
	PROFESSION_9_SPELL_008,
	PROFESSION_9_SPELL_009,
	PROFESSION_9_SPELL_010,
	PROFESSION_9_SPELL_011,
	PROFESSION_9_SPELL_012,
	PROFESSION_9_SPELL_013,
	PROFESSION_9_SPELL_014,
	PROFESSION_9_SPELL_015,
	PROFESSION_9_SPELL_016,
	PROFESSION_9_SPELL_017,
	PROFESSION_9_SPELL_018,
	PROFESSION_9_SPELL_019,
	PET_SKILL_001				= PROFESSION_9_SPELL_001 + NUMBER_OF_PROFESSION_SPELL,	/* 290 */
	PET_SKILL_002,
	PET_SKILL_003,
	PET_SKILL_004,
	PET_SKILL_005,
	PET_SKILL_006,
	PET_SKILL_007,
	PET_SKILL_008,
	PET_SKILL_009,
	PET_SKILL_010,
	PET_SKILL_011,
	PET_SKILL_012,
	PET_SKILL_013,
	PET_SKILL_014,
	PET_SKILL_015,
	PET_SKILL_016,
	PET_SKILL_017,
	PET_SKILL_018,
	PET_SKILL_019,
	PET_SKILL_020,
	PET_SKILL_021,
	PET_SKILL_022,
	ITEM_SKILL_001				= PET_SKILL_001 + NUMBER_OF_PET_SPELL,			/* 440 */
	ITEM_SKILL_002,
	ITEM_SKILL_003,
	ITEM_SKILL_004,
	ITEM_SKILL_005,
	ITEM_SKILL_006,
	ITEM_SKILL_007,
	ITEM_SKILL_008,
	ITEM_SKILL_009,
	ITEM_SKILL_010,
	ITEM_SKILL_011,
	ITEM_SKILL_012,
	ITEM_SKILL_013,
	ITEM_SKILL_014,
	ITEM_SKILL_015,
	ITEM_SKILL_016,
	ITEM_SKILL_017,
	ITEM_SKILL_018,
	ITEM_SKILL_019,
	ITEM_SKILL_020,
	MONSTER_SKILL_001			= ITEM_SKILL_001 + NUMBER_OF_ITEM_SPELL,		/* 540 */
	MONSTER_SKILL_002,
	MONSTER_SKILL_003,
	MONSTER_SKILL_004,
	MONSTER_SKILL_005,
	MONSTER_SKILL_006,
	MONSTER_SKILL_007,
	MONSTER_SKILL_008,
	MONSTER_SKILL_009,
	MONSTER_SKILL_010,
	MONSTER_SKILL_011,
	MONSTER_SKILL_012,
	MONSTER_SKILL_013,
	MONSTER_SKILL_014,
	MONSTER_SKILL_015,
	MONSTER_SKILL_016,
	MONSTER_SKILL_017,
	MONSTER_SKILL_018,
	MONSTER_SKILL_019,
	MONSTER_SKILL_020,
	OTHER_SKILL_001				= MONSTER_SKILL_001 + NUMBER_OF_MONSTER_SPELL,		/* 640 */
	MAX_SKILL_LOGIC_ID			= OTHER_SKILL_001 + NUMBER_OF_OTHER_SPELL
} SpellLogicID_T;
enum
{
	COMMON_SPELL_LOGIC_ID_START		= MELEE_ATTACK,
	COMMON_SPELL_LOGIC_ID_END		= COMMON_SPELL_LOGIC_ID_START +NUMBER_OF_COMMON_SPELL -1,
	WUSHI_SPELL_LOGIC_ID_START		= WUSHI_SPELL_001,
	WUSHI_SPELL_LOGIC_ID_END		= WUSHI_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	JIANXIA_SPELL_LOGIC_ID_START		= JIANXIA_SPELL_001,
	JIANXIA_SPELL_LOGIC_ID_END		= JIANXIA_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	QISHE_SPELL_LOGIC_ID_START		= QISHE_SPELL_001,
	QISHE_SPELL_LOGIC_ID_END		= QISHE_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	HUOQIANG_SPELL_LOGIC_ID_START		= HUOQIANG_SPELL_001,
	HUOQIANG_SPELL_LOGIC_ID_END		= HUOQIANG_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	XIANZHI_SPELL_LOGIC_ID_START		= XIANZHI_SPELL_001,
	XIANZHI_SPELL_LOGIC_ID_END		= XIANZHI_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	SAMAN_SPELL_LOGIC_ID_START		= SAMAN_SPELL_001,
	SAMAN_SPELL_LOGIC_ID_END		= SAMAN_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	PROFESSION_7_SPELL_LOGIC_ID_START	= PROFESSION_7_SPELL_001,
	PROFESSION_7_SPELL_LOGIC_ID_END		= PROFESSION_7_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	PROFESSION_8_SPELL_LOGIC_ID_START	= PROFESSION_8_SPELL_001,
	PROFESSION_8_SPELL_LOGIC_ID_END		= PROFESSION_8_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	PROFESSION_9_SPELL_LOGIC_ID_START	= PROFESSION_9_SPELL_001,
	PROFESSION_9_SPELL_LOGIC_ID_END		= PROFESSION_9_SPELL_001 +NUMBER_OF_PROFESSION_SPELL -1,
	PET_SKILL_LOGIC_ID_START		= PET_SKILL_001,
	PET_SKILL_LOGIC_ID_END			= PET_SKILL_001 +NUMBER_OF_PET_SPELL -1,
	ITEM_SKILL_LOGIC_ID_START		= ITEM_SKILL_001,
	ITEM_SKILL_LOGIC_ID_END			= ITEM_SKILL_001 +NUMBER_OF_ITEM_SPELL -1,
	OTHER_SKILL_LOGIC_ID_START		= OTHER_SKILL_001,
	OTHER_SKILL_LOGIC_ID_END		= OTHER_SKILL_001 +NUMBER_OF_OTHER_SPELL,
};


//所有战斗技能的基类 add by wujianping
class BaseSpellLogic
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	enum { ID = INVALID_ID, };

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	BaseSpellLogic()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	~BaseSpellLogic()
	{
	};

	//抓马技能才会用到的逻辑判断 add by wujianping
	virtual BOOL	SpecificOperationOnSpellStart(Character &rMe) const;

	//是否是被动技能 add by wujianping
	virtual BOOL	IsPassive(void) const;

	//被攻击 add by wujianping
	virtual BOOL	OnEvent_Interrupt(Character &rMe) const;

	//取消技能的使用 add by wujianping
	virtual BOOL	OnEvent_Cancel(Character &rMe) const;

	//使用聚气技能 add by wujianping
	BOOL		StartCharging(Character &rMe) const;

	//使用引导技能 add by wujianping
	BOOL		StartChanneling(Character &rMe) const;

	//使用瞬发技能 add by wujianping
	BOOL		StartLaunching(Character &rMe) const;

	//判断是否可以对目标使用技能 add by wujianping
	BOOL		IsWantedTarget(Character &rMe, Character &rTar, SpellInfo const &rSpellInfo) const;

	//修正技能的伤害 add by wujianping
	void		RefixPowerByRate(SpellInfo &rSpell, int32 nRate) const;

	//技能伤害是否可以被RefixPowerByRate修正 add by wujianping
	virtual BOOL CanBeRefixed(void) const
	{
		return FALSE;
	};

	//修正技能消耗 RefixPowerByRate add by wujianping
	void	RefixDepleteByRate(SpellInfo &rSpell, int32 nRate) const;

	//使用技能的条件检查 add by wujianping
	BOOL	IsConditionSatisfied(Character &rMe) const;

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	//没有实际用处 add by wujianping
	virtual BOOL CancelSpellEffect(Character &rMe) const
	{
		return FALSE;
	};

	//动作生效时的技能 也就是聚气和瞬发动作结束时 释放的技能 add by wujianping
	BOOL	Action_ActivateOnceDispatch(Character &rMe) const;
	//再次检查技能能否生效 add by wujianping
	BOOL	ReCheckConditionForActiveOnce(Character &rMe) const;
	//动作生效时产生的技能 也就是引导技能 间歇性产生的技能 add by wujianping
	BOOL	Action_ActivateEachTickDispatch(Character &rMe) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL Refix_SkillInstance(SpellInfo &rThisPassiveSpell, SpellInfo &rTargetSpell) const
	{
		return TRUE;
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL Refix_ItemEffect
		(
		SpellInfo	&rThisPassiveSpell,
		int32		nSlotID,
		int32		nItemType,
		int32		nATTRID,
		int16		&nAttrValue
		) const
	{
		return TRUE;
	};
	void	BroadcastTargetListMessage
		(
		Character		&rMe,
		OBJLIST			&rTargets,
		HitFlagsForOBJLIST_T	&rHitFlagsForObjList
		) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
protected:
	BOOL		ActivateOnce(Character &rMe) const;
	BOOL		ActivateEachTick(Character &rMe) const;
	virtual BOOL	EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;
	virtual BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;
	virtual BOOL	TargetCheckForEachTick(Character &rMe) const;
	virtual BOOL	TargetCheckForActivateOnce(Character &rMe) const;
	BOOL		DepleteProcess(Character &rMe) const;

	BOOL		CommonConditionCheck(Character &rMe) const;

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual BOOL SpecificConditionCheck(Character &rMe) const
	{
		return TRUE;
	}

	BOOL	CommonDeplete(Character &rMe) const;

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual BOOL SpecificDeplete(Character &rMe) const
	{
		return TRUE;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual BOOL IsSpecificTargetWanted(Character &rMe, Character &rTar, SpellInfo const &rSkillInfo) const
	{
		return TRUE;
	};
	BOOL	CanelSpell(Character &rMe) const;
	Object	*GetTargetObj(Character &rMe) const;
	BOOL	IsOutOfRange(Character &rMe) const;
	BOOL	IsOutOfRange(Character &rMe, Character &rObj) const;
	BOOL	IsOutOfRange(Character &rMe, GLPos const &rPosTarget) const;
	void	SetCooldown(Character &rMe, CooldownID_t nID, int32 nCooldownTime) const;
	void	SetAutoRepeatCooldown(Character &rMe, int32 nCooldownTime) const;
	BOOL	ScanUnitForTarget(Character &rMe, float fX, float fZ, OBJLIST &rTargets) const;
	BOOL	HitThisTarget(Character &rMe, Character &rTar) const;

	int32	GetHurtDelayTime(SpellInfo &rSkillInfo, Character &rMe, Character &rTar) const;
	BOOL	CriticalHitThisTarget(Character &rMe, Character &rTar) const;
	BOOL	CalculateTargetList(Character &rMe, OBJLIST &rTargets) const;

	BOOL	IsTargetAlive(Character &rTar) const;

	float	DistanceSq(GLPos const &posStart, GLPos const &posEnd) const;
	BOOL	IsHit(Character &rMe, Character &rTar, int32 nAccuracy) const;
	BOOL	CheckEffectAvailability(Character &rMe, Character &rTar, UNIT_EFFECT &rImp) const;
	BOOL	IsCriticalHit(Character &rMe, int32 nCriticalRate, Character &rTag) const;
	Time_t	RefixPlayActionTimeWithAttackRate(Time_t nPlayActionTime, int32 nAttackRate) const;
	Time_t	RefixCooldownTimeWithAttackRate(Time_t nCooldownTime, int32 nAttackRate) const;
	BOOL	RegisterImpactEvent
		(
		Character	&rReceiver,
		Character	&rSender,
		UNIT_EFFECT	&rImp,
		Time_t		nDelayTime,
		BOOL		bCriticalFlag
		) const;
	BOOL	RegisterSpellMissEvent
		(
		Character	&rReceiver,
		Character	&rSender,
		SpellID_t	nSkill,
		Time_t		nDelayTime
		) const;
	BOOL	RegisterBeSpellEvent
		(
		Character	&rReceiver,
		Character	&rSender,
		SpellID_t	nSkill,
		Time_t		nDelayTime
		) const;

	BOOL	RegisterActiveObj(Object &rObj, Character &rSender, Time_t nDelayTime) const;

	BOOL	CalculateCanGoPos(Character &rMe, Object *rTag, GLPos &sPos) const;

	void	NormalizeWorldPos(GLPos &sPos) const;

	float	WordPosLength(float fX, float fY) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
private:
	Time_t	CalculateActionTime(Character &rMe) const;
	void	CooldownProcess(Character &rMe) const;
};

BaseSpellLogic const	*Spell_GetLogic(SpellInfo const &rSpell);

class ArmorMastery :
	public BaseSpellLogic
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	enum { ID = ARMOR_MASTERY, };
	enum { BASE_DEFENCE_NEAR = 0, BASE_DEFENCE_MAGIC = 1, };

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	ArmorMastery()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	~ArmorMastery()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL IsPassive(void) const
	{
		return TRUE;
	};

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
protected:
	BOOL	Refix_ItemEffect
		(
		SpellInfo	&rThisPassiveSkill,
		int32		nSlotID,
		int32		nItemType,
		int32		nATTRID,
		int16		&nAttrValue
		) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
private:
};

class TeleportAndEffects :
	public BaseSpellLogic
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	enum { ID = TELEPORT_AND_IMPACTS, };
	class SkillInfoDescriptorIndex_T
	{
	public: enum { IDX_IMPACT_1 = 0, IDX_IMPACT_2, IDX_IMPACT_3, IDX_IMPACT_TELEPORT };
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	TeleportAndEffects()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	~TeleportAndEffects()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL IsPassive(void) const
	{
		return FALSE;
	};

	int32	GetEffect1(SpellInfo const &rSkill) const;
	int32	GetEffect2(SpellInfo const &rSkill) const;
	int32	GetEffect3(SpellInfo const &rSkill) const;
	int32	GetEffectTeleport(SpellInfo const &rSkill) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
private:
};

class WeaponMastery :
	public BaseSpellLogic
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	enum { ID = WEAPON_MASTERY, };
	enum { BASE_ATTACK_NEAR_REFIX, BASE_ATTACK_MAGIC_REFIX, MASTERY_OF_WEAPON_TYPE1, MASTERY_OF_WEAPON_TYPE2, };

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	WeaponMastery()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	~WeaponMastery()
	{
	};

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL IsPassive(void) const
	{
		return TRUE;
	};

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
protected:
	BOOL	Refix_ItemEffect
		(
		SpellInfo	&rThisPassiveSkill,
		int32		nSlotID,
		int32		nItemType,
		int32		nATTRID,
		int16		&nAttrValue
		) const;

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
private:
};
#endif