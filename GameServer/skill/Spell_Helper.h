///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName:Spell_Helper.h
//Author:
//Date:
//Describe:战斗技能相关的参数结构定义，及部分辅助功能的实现
//History:
//		1.
//		2.
//		3.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SPELL_HELP_H
#define SPELL_HELP_H

#include "TypeDefine.h"
#include "SpellDataLoader.h"
#include "Enum.h"
#include "Struct.h"
#include "StructDB.h"

class Character;
class SpellInfo;

enum SpellControlType	//控制类技能的类型：近，远，魔 add by shangy
{
	SCT_NULL = -1,
	SCT_NEAR = 0,
	SCT_FAR,
	SCT_MAGIC
};

enum TargetCamp	//目标阵营类型 add by shangy
{
	TC_PARTNER = 0,
	TC_ENEMY,
	TC_PARTNER_PET,
	TC_PARTNER_EXCEPT_SELF,
	TC_ENEMY_AND_PLAYER,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CombatSystem
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum	//技能效果类型 add by shangy
{
	DAMAGE_SPECIAL_EFFECT_NEAR	= 0,
	DAMAGE_SPECIAL_EFFECT_FAR,
	DAMAGE_SPECIAL_EFFECT_MAGIC,
	DAMAGE_SPECIAL_EFFECT_COLD,
	DAMAGE_SPECIAL_EFFECT_FIRE,
	DAMAGE_SPECIAL_EFFECT_LIGHT,
	DAMAGE_SPECIAL_EFFECT_POISON
} DamageSEID_T;

/*
====================================================================================================================== =
add by shangy
CombatSystem;
通过对设定的基础数值（人物的属性值和技能的修正值）对战斗中的数值进行计算，并修正对应Impact
====================================================================================================================== =
*/
class	CombatSystem
{
public:

	CombatSystem();
	~CombatSystem();
	//根据攻击者的命中和目标的闪避计算命中率 最小值10 add by shangy
	int32	CalculateHitRate(Character& rAttacker, Character& rTag);
	//根据攻击者控制技能的命中和目标的控制技能的闪避计算命中率 最小值25 add by shangy
	int32	CalculateHitRateForControlSpell(Character& rAttacker, Character& rTag, SpellControlType eType);
	//是否击中
	BOOL	IsHit(int32 nHitRate, int32 nRand);
	//是否暴击  暴击率 = 自身暴击率 + 技能修正暴击率 - 对方韧性 add by shangy
	BOOL	IsCriticalHit(Character& rAttacker, int32 nCriticalRate, int32 nRand, Character& rTar, int32 iToughness);
	void	Reset();
	//计算伤害：在Impact注册到目标之前，根据人物自身属性，对Impact的近，远，魔，冰，火，光，毒进行计算。 add by shangy
	BOOL	GetResultImpact(Character& rAttacker, Character& rDefenceer, UNIT_EFFECT& rImp);
	//将Impact上的的近，远，魔，冰，火，光，毒属性叠加到当前攻击伤害上。 add by shangy
	void	InitAttackValueData(UNIT_EFFECT& rImp);
	void	InitAttackRateData(UNIT_EFFECT& rImp, Character& rMe);
public:
	//获得和设置当前近，远，魔，冰，火，光，毒属性 add by shangy
	int32	GetAdditionalAttackNear(void) const;
	void	SetAdditionalAttackNear(int32 nValue);
	int32	GetAdditionalAttackFar(void) const;
	void	SetAdditionalAttackFar(int32 nValue);
	int32	GetAdditionalAttackMagic(void) const;
	void	SetAdditionalAttackMagic(int32 nValue);
	int32	GetAdditionalAttackCold(void) const;
	void	SetAdditionalAttackCold(int32 nValue);
	int32	GetAdditionalAttackFire(void) const;
	void	SetAdditionalAttackFire(int32 nValue);
	int32	GetAdditionalAttackLight(void) const;
	void	SetAdditionalAttackLight(int32 nValue);
	int32	GetAdditionalAttackPoison(void) const;
	void	SetAdditionalAttackPoison(int32 nValue);

	//天赋平衡
	int32 RefixCritRatebyInherenceBalance(int32 nCrit, int32 nToughness, Character& rAttacker, Character& rTar);

	int32 RefixHitbyInherenceBalance(int32 nHit, int32 nMiss, Character& rAttacker, Character& rTar);

	float RefixCritDamagebyInherenceBalance(int32 nCritDamageRate, int32 nCritDamageDerateRatrByToughness, Character& rAttacker, Character& rTar);

	//获取职业伤害修正率(包括装备修正和专精修正)
	int32	GetProfessionDamageRefixRate(Character& rAttacker, Character& rTar);

protected:
	//计算近，远，魔，冰，火，光，毒的伤害，在NormalDamage计算的结果上加入目标的伤害减免和自身的忽略伤害减免属性影响 add by shangy
	int32	NearDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	FarDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	MagicalDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	ColdDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	FireDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	LightDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	int32	PoisonDamage(Character& rMe, Character& rTar, int32 iLogicID, int32 nAdditionAttack = 0, int32 nAdditionDefence = 0);
	//计算伤害的公共方法（近，远，魔） 伤害 = 自身攻 - 目标防 - 目标物品属性中对应的防御值 add by shangy
	int32	NormalDamage(Character& rTar, int32 nAttack, int32 nDefence, int32 iType);
	//计算伤害的公共方法（冰，火，光，毒） 伤害 = 自身攻 - 目标物品属性中对应的防御值 add by shangy
	int32	AttrDamage(Character& rTar, int32& nResist, int32 nAttack, int32 iType);
	//根据人物的原始属性和其他附加属性计算加成之后的属性值 add by shangy
	int32	GetValueByCalType(int32 iSrc, int32 iAddition, int32 iType, int32 iParaTab);


private:
	int32	m_nAdditionalAttackNear;
	int32	m_nAdditionalAttackFar;
	int32	m_nAdditionalAttackMagic;
	int32	m_nAdditionalAttackCold;
	int32	m_nAdditionalAttackFire;
	int32	m_nAdditionalAttackLight;
	int32	m_nAdditionalAttackPoison;
	int32	m_nAdditionalDefenceNear;
	int32	m_nAdditionalDefenceFar;
	int32	m_nAdditionalDefenceMagic;
	int32	m_nAdditionalDefenceCold;
	int32	m_nAdditionalDefenceFire;
	int32	m_nAdditionalDefenceLight;
	int32	m_nAdditionalDefencePoison;
	int32	m_ImpactDataTbl[DAMAGE_TYPE_NUMBER];
};

typedef enum _ConditionAndDepleteID
{
	CD_INVALID				= INVALID_ID,
	C_UNIT_MUST_HAVE_IMPACT			= 0,
	C_UNIT_HP_MUST_LESS_THAN_BY_RATE,
	C_UNIT_HP_MUST_MORE_THAN_BY_RATE,
	C_TARGET_MUST_HAVE_IMPACT,
	C_TARGET_HP_MUST_LESS_THAN_BY_RATE,
	C_TARGET_HP_MUST_MORE_THAN_BY_RATE,
	CD_HP_BY_VALUE,
	CD_HP_BY_RATE,
	CD_RAGE0_BY_VALUE,
	CD_RAGE0_BY_RATE,
	CD_RAGE1_BY_VALUE,
	CD_RAGE1_BY_RATE,
	CD_RAGE2_BY_VALUE,
	CD_RAGE2_BY_RATE,
	CD_RAGE3_BY_VALUE,
	CD_RAGE3_BY_RATE,
	CD_RAGE4_BY_VALUE,
	CD_RAGE4_BY_RATE,
	CD_RAGE5_BY_VALUE,
	CD_RAGE5_BY_RATE,
	D_CANCEL_SPECIFIC_IMPACT,
	CD_CANCEL_SPECIFIC_IMPACT,
	C_TARGET_MUST_BE_MY_SPOUSE,
} ConditionAndDepleteID;

/*
=======================================================================================================================
add by shangy
CDSystem ;
这里的CD表示ConditionCheckAndDeplete，与技能冷却没有关系。
当使用技能时对技能的使用条件进行判断以及消耗相应的物品或怒气，MP等
每个技能可以配置三组检查或消耗条件，最后一组可以配置消耗物品
每组配置如下：
在spell_logic.tab中
“条件或消耗参数说明”列 描述
“条件和消耗逻辑”列配置对应的ID 其值定义在 ConditionAndDepleteID中
“条件或消耗参数值p1（v=p1*level+p2）”	参数1
“条件或消耗参数值p2（v=p1*level+p2）” 参数2
每组数据对应ConditionAndDepleteTerm结构

特例：当SpellTargetingAndDepletingParams中的m_bIgnoreConditionCheck为true时不进行这个检查
，主要是给脚本中提供一个直接无条件（冷却时间除外）使用技能的方法
=======================================================================================================================
*/

class Player;
typedef class	CDSystem
{
public:
	//根据ID进行分发，具体逻辑由成员类处理 add by shangy
	BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	//对消耗物品的检查和消耗 add by shangy
	BOOL	ConditionCheckByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	BOOL	DepleteByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const;

private:
	class	ConDepLogic
	{
	public:
		enum { ID = CD_INVALID, };
		virtual BOOL ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const { return TRUE; };
		virtual BOOL Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const { return TRUE; };
	protected:
		int32	NotEnoughRageForProfession(Player& rMe) const;
		//根据其他Buff(SpellEffect021,SpellEffect029,SpellEffect075)对当前使用技能的修正，对消耗进行修正。 add by shangy
		int32	RefixValue(int32 iValue, Character& rMe, ConditionAndDepleteTerm const& rData) const;
		//获得通用消耗，公式:Param0 * SkillLevel + Param1 add by shangy
		int32	GetCommonDeplete(ConditionAndDepleteTerm const& rData, SpellInfo& rSkillInfo) const;
		BOOL	RageConditionCheckByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	RageDepleteByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const;

		BOOL	RageConditionCheckByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	RageDepleteByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//判断人物身上是否有特定集合的buff, Param0: CollectionID 
	//对应Collection数据定义在FILE_ID_COLLECTION中 add by shangy
	class CDUnitHaveImpact : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_MUST_HAVE_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//根据通用消耗公式，获得HP上限百分比。检查血量是否低于上限血量
	//上限血量:人物最大血量 * HP上限百分比 再经过Buff修正后得到上限血量 add by shangy
	class CDUnitHpLessThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_HP_MUST_LESS_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//人物血量高于上限血量的检查 add by shangy
	class CDUnitHpMoreThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_UNIT_HP_MUST_MORE_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//根据比例减血 add by shangy
	class CDHpByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_HP_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//目标血量低于上限血量的检查 add by shangy
	class CDTargetHpLessThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_HP_MUST_LESS_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//目标血量高于上限血量的检查 add by shangy
	class CDTargetHpMoreThanByRate : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_HP_MUST_MORE_THAN_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//目标必须拥有特定集合的buff, Param0: CollectionID 
	//对应Collection数据定义在FILE_ID_COLLECTION中 add by shangy
	class CDTargetMustHaveImpact : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_MUST_HAVE_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//驱散特定集合的buff, Param0: CollectionID 
	//对应Collection数据定义在FILE_ID_COLLECTION中 add by shangy
	class CDCancelSpecialImpact_D : public ConDepLogic
	{
	public:
		enum { ID = D_CANCEL_SPECIFIC_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//目标必须是伴侣 add by shangy
	class CDTargetMustBeMySpouse : public ConDepLogic
	{
	public:
		enum { ID = C_TARGET_MUST_BE_MY_SPOUSE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//按比例伤血 add by shangy
	class CDHpByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_HP_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 武士，十字军 add by shangy
	class CDRage0ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE0_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 武士，十字军 add by shangy
	class CDRage0ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE0_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 剑侠，圣火使 add by shangy
	class CDRage1ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE1_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 剑侠，圣火使 add by shangy
	class CDRage1ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE1_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 骑射，刺客 add by shangy
	class CDRage2ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE2_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 骑射，刺客 add by shangy
	class CDRage2ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE2_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 火枪，近卫军 add by shangy
	class CDRage3ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE3_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 火枪，近卫军 add by shangy
	class CDRage3ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE3_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 先知，隐修士 add by shangy
	class CDRage4ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE4_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 先知，隐修士 add by shangy
	class CDRage4ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE4_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by value 萨满，喇嘛 add by shangy
	class CDRage5ByValue : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE5_BY_VALUE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//消耗怒气 by Rate 萨满，喇嘛 add by shangy
	class CDRage5ByRate : public ConDepLogic
	{
	public:
		enum { ID = CD_RAGE5_BY_RATE, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

	//驱散特定集合的buff, Param0: CollectionID 
	//对应Collection数据定义在FILE_ID_COLLECTION中 add by shangy
	class CDCancelSpecialImpact_CD : public ConDepLogic
	{
	public:
		enum { ID = CD_CANCEL_SPECIFIC_IMPACT, };
		BOOL	ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const;
		BOOL	Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const;
	};

private:
	CDUnitHaveImpact			m_C_UnitHaveImpact;
	CDUnitHpLessThanByRate		m_C_UnitHpLessThanByRate;
	CDUnitHpMoreThanByRate		m_C_UnitHpMoreThanByRate;
	CDTargetMustHaveImpact		m_C_TargetMustHaveImpact;
	CDTargetHpLessThanByRate	m_C_TargetHpLessThanByRate;
	CDTargetHpMoreThanByRate	m_C_TargetHpMoreThanByRate;
	CDHpByValue					m_CD_HpByValue;
	CDHpByRate					m_CD_HpByRate;
	CDRage0ByValue				m_CD_Rage0ByValue;
	CDRage1ByValue				m_CD_Rage1ByValue;
	CDRage2ByValue				m_CD_Rage2ByValue;
	CDRage3ByValue				m_CD_Rage3ByValue;
	CDRage4ByValue				m_CD_Rage4ByValue;
	CDRage5ByValue				m_CD_Rage5ByValue;
	CDRage0ByRate				m_CD_Rage0ByRate;
	CDRage1ByRate				m_CD_Rage1ByRate;
	CDRage2ByRate				m_CD_Rage2ByRate;
	CDRage3ByRate				m_CD_Rage3ByRate;
	CDRage4ByRate				m_CD_Rage4ByRate;
	CDRage5ByRate				m_CD_Rage5ByRate;
	CDCancelSpecialImpact_D		m_D_CancelSpecialImpact;
	CDCancelSpecialImpact_D		m_CD_CancelSpecialImpact;
	CDTargetMustBeMySpouse		m_C_TargetMustBeMySpouse;
} ConditionAndDepleteCore_T;

/*
=======================================================================================================================
add by shangy
SpellTargetingAndDepletingParams ;
战斗技能针对的目标和消耗的数据参数
=======================================================================================================================
*/
class	SpellTargetingAndDepletingParams
{

public:
	enum { MAX_PARAM_NUMBER = 8, };

	//该参数对应的技能ID add by shangy
	SpellID_t			GetActivatedSpell(void) const;
	void				SetActivatedSpell(SpellID_t nSpell);

	//该参数对应的脚本ID add by shangy
	//目前只有使用物品的操作会绑定脚本，使用技能没有绑定脚本的
	ScriptID_t			GetActivatedScript(void) const;
	void				SetActivatedScript(ScriptID_t nScript);

	//技能或使用物品目标 add by shangy
	ObjID_t				GetTargetObj(void) const;
	void				SetTargetObj(ObjID_t nObj);

	//技能使用目标的GUID add by shangy
	GUID_t				GetTargetGuid(void) const;
	void				SetTargetGuid(GUID_t nGuid);

	//目标位置 add by shangy
	GLPos const &	GetTargetPosition(void) const;
	void				SetTargetPosition(GLPos const &rPos);

	//目标朝向 add by shangy
	float				GetTargetDirection(void) const;
	void				SetTargetDirection(float fDir);

	//物品在背包中的位置 add by shangy
	int32				GetTargetBagSlot(void) const;
	void				SetTargetBagSlot(int32 nSlot);

	//Pet GUID (TargetID and TargetGUID) add by shangy
	SHorseGuid const &	GetTargetPetGuid(void) const;
	void				SetTargetPetGuid(SHorseGuid const &rGuid);
	
	//是否忽略检查条件 只在脚本调用的时候会设置该值（LuaFunction_UnitUseSkill），为true时不检查使用技能条件，只要冷却时间满足直接使用技能。
	//对应的检查项在spell_logic.tab中“条件和消耗逻辑”列配置，在CDSystem中的对应类中进行检查。每个技能共可以配置三组检查条件。 add by shangy
	BOOL				GetIgnoreConditionCheckFlag(void) const;
	void				SetIgnoreConditionCheckFlag(BOOL bFlag);
	//消耗怒气 add by shangy
	int32				GetDepletedRage(void) const;
	void				SetDepletedRage(int32 nDepleted);
	//消耗StrikePoints add by shangy
	int32				GetDepletedStrikePoints(void) const;
	void				SetDepletedStrikePoints(int32 nDepleted);
	//消耗Item的GUID add by shangy
	SItemGuid const &	GetDepletedItemGuid(void) const;
	void				SetDepletedItemGuid(SItemGuid const &rGuid);
	//消耗Item的背包Index add by shangy
	int32				GetBagIndexOfDepletedItem(void) const;
	void				SetBagIndexOfDepletedItem(int32 nIndex);
	//消耗Item在背包中的Index add by shangy
	int32				GetItemIndexOfDepletedItem(void) const;
	void				SetItemIndexOfDepletedItem(int32 nIndex);
	//如果物品为绑定，则设置绑定 add by shangy
	void				SetItemBind();
	BOOL				IsDepletedItemBind();
	//延迟时间 spell_logic.tab中配置的时间 add by shangy
	Time_t				GetDelayTime(void) const;
	void				SetDelayTime(Time_t nTime);
	//目标个数 add by shangy
	int32				GetTargetCount(void) const;
	void				SetTargetCount(int32 nCount);
	//错误码 add by shangy
	ID_t				GetErrCode(void) const;
	void				SetErrCode(ID_t nErr);
	//错误参数 add by shangy
	int32				GetErrParam(void) const;
	void				SetErrParam(int32 nParam);
	//动态参数 add by shangy
	BOOL				IsDynamicParamIndexLegal(int32 nIndex) const;
	int32				GetDynamicParamByIndex(int32 nIndex) const;
	void				SetDynamicParamByIndex(int32 nIndex, int32 nValue);
	//伤害延迟时间 最终作用于对应Impact上 add by shangy
	int32				GetHurtDelayTime() const;
	void				SetHurtDelayTime(int32 val);

	// 追踪符
	void SetFindPlayerItemDataName(const char* name);
	const char* GetFindPlayerItemDataName();

public:
	SpellTargetingAndDepletingParams(void);
	~SpellTargetingAndDepletingParams(void){};
	SpellTargetingAndDepletingParams &operator	=(SpellTargetingAndDepletingParams const &rhs);
	void Reset(void);

private:
	SpellID_t	m_nActivatedSpell;
	ScriptID_t	m_nActivatedScript;
	ObjID_t		m_nTargetObj;
	GUID_t		m_guidTargetPartner;
	GLPos	m_posTargetPosition;
	float		m_fTargetDirection;
	int32		m_nTargetBagSlot;
	SHorseGuid	m_guidTargetPet;
	BOOL		m_bIgnoreConditionCheck;
	int32		m_nDepletedRage;
	int32		m_nDepletedStrikePoints;
	SItemGuid	m_guidDepletedItem;
	int32		m_nBagIndexOfDepletedItem;
	int32		m_nItemIndexOfDepletedItem;
	Time_t		m_nDelayTime;
	int32		m_nTargetCount;
	int32		m_aDynamicParams[MAX_PARAM_NUMBER];
	ID_t		m_nErrCode;
	int32		m_nErrParam;
	int32		m_iHurtDelayTime;
	BOOL		m_bDeletedItemBind;
	char		m_szFindPlayerItemName[MAX_CHARACTER_NAME];
};


/*
=======================================================================================================================
add by shangy
SpellTargetChecker ;
检查技能使用目标有效性
=======================================================================================================================
*/
class	SpellTargetChecker
{

public:
	typedef enum
	{
		INVALID_CHECKER_ID	= INVALID_ID,
		ALL_TYPE_ARE_LEGAL	= 0,
		NPCS_ARE_LEGAL		= 1,
		ONLY_PC_IS_LEGAL	= 2,
		ONLY_PET_IS_LEGAL	= 3,
		NON_TYPE_IS_LEGAL	= 4,
		NUMBER_OF_CHECKERS
	} TargetTypeCheckerID_T;

	enum { ID = INVALID_CHECKER_ID, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class AllTypesAreLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ALL_TYPE_ARE_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class NonPlayerCharactersAreLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::NPCS_ARE_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class OnlyPlayerCharacterIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ONLY_PC_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class OnlyPetIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::ONLY_PET_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

class NonTypeIsLegal : public SpellTargetChecker
{
public:
	enum { ID = SpellTargetChecker::NON_TYPE_IS_LEGAL, };
	virtual BOOL	IsLegal(Character const &rTarget) const;
};

/*
=======================================================================================================================
add by shangy
SpellInfo ;
技能信息，包含了技能大部分的基本属性信息。
=======================================================================================================================
*/

class	SpellInfo
{
public:
	SpellInfo();
	SpellInfo(SpellInfo const &rSrc);
	~SpellInfo(){};

	void			Init(void);
	SpellID_t		GetSpellID(void) const;
	void			SetSpellID(SpellID_t const nID);;
	int32			GetAccuracy(void) const;
	void			SetAccuracy(int32 const nID);
	int32			GetCriticalRate(void) const;
	void			SetCriticalRate(int32 const nRate);
	int32			GetDepleteRefixByValue(void) const;
	void			SetDepleteRefixByValue(int32 nValue);
	int32			GetDepleteRefixByRate(void) const;
	void			SetDepleteRefixByRate(int32 nRate);
	int32			GetPowerRefixByValue(void) const;
	void			SetPowerRefixByValue(int32 nValue);
	int32			GetPowerRefixByRate(void) const;
	void			SetPowerRefixByRate(int32 nRate);
	int32			GetTimeRefixByValue(void) const;
	void			SetTimeRefixByValue(int32 nValue);
	int32			GetTimeRefixByRate(void) const;
	void			SetTimeRefixByRate(int32 nRate);
	Time_t			GetCooldownTime(void) const;
	void			SetCooldownTime(Time_t const nTime);
	Time_t			GetChargeTime(void) const;
	void			SetChargeTime(Time_t const nTime);
	Time_t			GetChannelTime(void) const;
	void			SetChannelTime(Time_t const nTime);
	float			GetMinSkillDistance() const;
	void			SetMinSkillDistance(float val);
	float			GetMaxSkillDistance() const;
	void			SetMaxSkillDistance(float val);
	void			SetChargesOrInterval(int32 val);
	int16_t			GetProfession(void) const;
	char const		*GetName(void) const;
	int32			GetTalentLevelRequirement(void) const;
	BOOL			GetMustUseWeaponFlag(void) const;
	BOOL			GetDisableByFlag1(void) const;
	BOOL			GetDisableByFlag2(void) const;
	BOOL			GetDisableByFlag3(void) const;
	int32			GetRangedSkillFlag(void) const;
	BOOL			IsForceBreakPreSkill(void) const;
	int32			GetTargetMustInSpecialState(void) const;
	ID_t			GetSpellType(void) const;
	CooldownID_t	GetCooldownID(void) const;
	ID_t			GetSelectType(void) const;
	ID_t			GetOperateModeForPetSpell(void) const;
	ID_t			GetPetRateOfSpell(void) const;
	ID_t			GetTypeOfPetSpell(void) const;
	ID_t			GetImpactID(void) const;
	ID_t			GetTargetingLogic(void) const;
	Time_t			GetPlayActionTime(void) const;
	float			GetOptimalRangeMin() const;
	float			GetOptimalRangeMax() const;
	void			SetOptimalRangeMax(float fDistance);
	ID_t			GetStandFlag(void) const;
	ID_t			GetTargetLogicByStand(void) const;
	int32			GetSpeedOfBullet(void) const;
	int32			GetHurtDelayTime(void) const;
	ID_t			GetTargetCheckByObjType(void) const;
	BOOL			IsPartyOnly(void) const;
	int32			GetChargesOrInterval(void) const;
	BOOL			IsAutoShotSpell(void) const;
	BOOL			UseNormalAttackRate(void) const;
	float			GetRadius(void) const;
	float			GetAngle(void) const;
	float			GetRectangleWidth(void) const;
	int32			Get_Property_MaxTargetNumber(void) const;
	void			SetMaxTargetNumber(int32 val);
	BOOL			CanInterruptAutoShot(void) const;
	Time_t			GetDelayTime(void) const;
	ID_t			GetLogicID(void) const;
	ConditionAndDepleteTerm const*	Get_Property_ConDepTermByIndex(int32 const nIdx) const;
	int32				GetSpellLevel(void) const;
	Descriptor const*	GetDescriptorByIndex(int32 const nIdx) const;
	int32				GetCharacterSpellLevel() const;
	void				SetCharacterSpellLevel(int32 val);
	int32				GetChannelBackRate() const;
	void				SetChannelBackRate(int32 val);
	int32				GetChannelBackHappanRate() const;
	void				SetChannelBackHappanRate(int32 val);
	int32				GetSpellLogicCount() const;
	void				SetSpellLogicCount(int32 val);
	int32				GetControlType(void) const;

	SpellInfo &operator	=(SpellTemplateData const &rSrc);
	SpellInfo &operator	=(SpellInstanceData const &rSrc);
	SpellInfo &operator	=(SpellInfo const &rSrc);

protected:

	SpellID_t	GetInstanceID(void) const;
	void		SetInstanceID(SpellID_t const nID);
	void		InitOptimalRangeMin();
	void		InitOptimalRangeMax();
	void		InitChargesOrInterval();
	void		InitMaxTargetNumber();

private:
	SpellID_t	m_nSpellID;
	int32		m_nInstanceID;
	int32		m_nAccuracy;
	int32		m_nCriticalRate;
	int32		m_nDepleteRefixByValue;
	int32		m_nDepleteRefixByRate;
	int32		m_nPowerRefixByValue;
	int32		m_nPowerRefixByRate;
	int32		m_nTimeRefixByValue;
	int32		m_nTimeRefixByRate;
	Time_t		m_nCooldownTime;
	Time_t		m_nChargeTime;
	Time_t		m_nChannelTime;
	float		m_fMinSkillDistance;
	float		m_fMaxSkillDistance;
	int32		m_ChargesOrInterval;
	int32		m_iMaxTargetNumber;
	int32		m_iSpellLevel;
	int32		m_iSpellLogicCount;
	int32		m_iChannelBackRate;
	int32		m_iChannelBackHappanRate;
};

#endif
