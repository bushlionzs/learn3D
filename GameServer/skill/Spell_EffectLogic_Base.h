/*$T MapServer/Server/Spell/EffectLogic/Spell_EffectLogic_Base.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef EFFECT_LOGIC_BASE_H
#define EFFECT_LOGIC_BASE_H

#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "StructEffect.h"
#include "SpellDataLoader.h"
#include "Spell_Helper.h"
#include "Spell_EffectInterface.h"


class Item;

typedef enum _EffectLogicID_T
{
	SPELL_EFFECT_000,
	SPELL_EFFECT_001,
	SPELL_EFFECT_002,
	SPELL_EFFECT_003,
	SPELL_EFFECT_004,
	SPELL_EFFECT_005,
	SPELL_EFFECT_006,
	SPELL_EFFECT_007,
	SPELL_EFFECT_008,
	SPELL_EFFECT_009,
	SPELL_EFFECT_010,
	SPELL_EFFECT_011,
	SPELL_EFFECT_012,
	SPELL_EFFECT_013,
	SPELL_EFFECT_014,
	SPELL_EFFECT_015,
	SPELL_EFFECT_016,
	SPELL_EFFECT_017,
	SPELL_EFFECT_018,
	SPELL_EFFECT_019,
	SPELL_EFFECT_020,
	SPELL_EFFECT_021,
	SPELL_EFFECT_022,
	SPELL_EFFECT_023,
	SPELL_EFFECT_024,
	SPELL_EFFECT_025,
	SPELL_EFFECT_026,
	SPELL_EFFECT_027,
	SPELL_EFFECT_028,
	SPELL_EFFECT_029,
	SPELL_EFFECT_030,
	SPELL_EFFECT_031,
	SPELL_EFFECT_032,
	SPELL_EFFECT_033,
	SPELL_EFFECT_034,
	SPELL_EFFECT_035,
	SPELL_EFFECT_036,
	SPELL_EFFECT_037,
	SPELL_EFFECT_038,
	SPELL_EFFECT_039,
	SPELL_EFFECT_040,
	SPELL_EFFECT_041,
	SPELL_EFFECT_042,
	SPELL_EFFECT_043,
	SPELL_EFFECT_044,
	SPELL_EFFECT_045,
	SPELL_EFFECT_046,
	SPELL_EFFECT_047,
	SPELL_EFFECT_048,
	SPELL_EFFECT_049,
	SPELL_EFFECT_050,
	SPELL_EFFECT_051,
	SPELL_EFFECT_052,
	SPELL_EFFECT_053,
	SPELL_EFFECT_054,
	SPELL_EFFECT_055,
	SPELL_EFFECT_056,
	SPELL_EFFECT_057,
	SPELL_EFFECT_058,
	SPELL_EFFECT_059,
	SPELL_EFFECT_060,
	SPELL_EFFECT_061,
	SPELL_EFFECT_062,
	SPELL_EFFECT_063,
	SPELL_EFFECT_064,
	SPELL_EFFECT_065,
	SPELL_EFFECT_066,
	SPELL_EFFECT_067,
	SPELL_EFFECT_068,
	SPELL_EFFECT_069,
	SPELL_EFFECT_070,
	SPELL_EFFECT_071,
	SPELL_EFFECT_072,
	SPELL_EFFECT_073,
	SPELL_EFFECT_074,
	SPELL_EFFECT_075,
	SPELL_EFFECT_076,
	SPELL_EFFECT_077,
	SPELL_EFFECT_078,
	SPELL_EFFECT_079,
	SPELL_EFFECT_080,
	SPELL_EFFECT_081,
	SPELL_EFFECT_082,
	SPELL_EFFECT_083,
	SPELL_EFFECT_084,
	SPELL_EFFECT_085,
	SPELL_EFFECT_086,
	SPELL_EFFECT_087,
	SPELL_EFFECT_088,
	SPELL_EFFECT_089,
	SPELL_EFFECT_090,
	NUMBER_OF_IMPACT_LOGIC_IDS
} EffectLogicID;


//所有BUFF的逻辑处理基类 add by wujianping
class		EffectLogic
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
	EffectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectLogic()
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/*
	===============================================================================================================
	===============================================================================================================
	*/

	virtual BOOL InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
	{
		return TRUE;
	};

	//是否是持续BUFF add by wujianping
	virtual BOOL IsOverTimed(void) const
	{
		return FALSE;
	};

	//是否是间歇发作BUFF 俗称DOT-BUFF add by wujianping
	virtual BOOL IsIntervaled(void) const
	{
		return FALSE;
	};

	//BUFF的心跳 add by wujianping
	void	HeartBeat(UNIT_EFFECT &rImp, Character &rMe) const;

	//修正技能 add by wujianping
	virtual void RefixSkill(UNIT_EFFECT &rImp, SpellInfo &rSkill) const
	{
	};

	//修正BUFF add by wujianping
	virtual void RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
	{
	};

	//修正回蓝 add by wujianping
	virtual void RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
	{
	};

	////是否能看见特殊的物品 有一个捕捉的放大镜用到此逻辑 add by wujianping
	//virtual BOOL CanViewSpecialObj(UNIT_EFFECT &rImp, SpecialCreature &rObj) const
	//{
	//	return FALSE;
	//}

	//多种类型的攻击(近远魔冰电火毒)产生的伤害 add by wujianping
	virtual void OnEvent_Damages
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32 *const		pDamageList,
		SpellID_t		nSkillID
		) const
	{
	};

	//受到伤害 add by wujianping
	virtual void	OnEvent_Damage
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32			&rDamage,
		SpellID_t		nSkillID
		) const
	{
	};

	//最终的伤害 直接减少的HP的伤害 add by wujianping
	virtual void OnEvent_FinalDamage
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		Character *const	pAttacker,
		int32			&rDamage,
		SpellID_t		nSkillID
		) const
	{
	};

	//伤害目标 add by wujianping
	virtual void OnEvent_DamageTarget
		(
		UNIT_EFFECT	&rImp,
		Character	&rMe,
		Character	&rTar,
		int32		&rDamage,
		SpellID_t	nSkillID
		) const
	{
	};

	//BUFF 生效 add by wujianping
	virtual void OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//被暴击 add by wujianping
	virtual void OnEvent_BeCriticalHit(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//被治疗 add by wujianping
	virtual void	OnEvent_BeHeal(UNIT_EFFECT &rImp, Character &rMe, int32 &nHealedHP) const
	{
	};

	//暴击目标 add by wujianping
	virtual void OnEvent_CriticalHitTarget(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//对INT属性的修正 add by wujianping
	virtual BOOL Get_Property_IntAttrRefix
		(
		UNIT_EFFECT			&rImp,
		Character			&rMe,
		CharIntAttrRefixs::Index_T	nIdx,
		int32				&rIntAttrRefix
		) const
	{
		return FALSE;
	};

	//对BOOL属性的修正 add by wujianping
	virtual BOOL Get_Property_BoolAttrRefix
		(
		UNIT_EFFECT		&rImp,
		Character		&rMe,
		CharBoolAttrs::Index_T	nIdx,
		BOOL			&rBoolAttrRefix
		) const
	{
		return FALSE;
	};


	//死亡 add by wujianping
	virtual void OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//BUFF消失 add by wujianping
	virtual void OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//治疗目标 add by wujianping
	virtual void OnEvent_HealTarget(UNIT_EFFECT &rImp, Character &rMe, int32 &rHealedHP) const
	{
	};

	//被击中 add by wujianping
	virtual void OnEvent_BeHit(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
	{
	};

	//击中目标 add by wujianping
	virtual void OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
	{
	};

	//间歇发作的BUFF结束 add by wujianping
	virtual void OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//成功使用技能 add by wujianping
	virtual void OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
	{
	};

	//忽视BUFF 也就是无视一些BUFF add by wujianping
	virtual int32 OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
	{
		return CombatMissFlag::FLAG_NORMAL;
	};


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//修正伤害 add by wujianping
	virtual BOOL RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
	{
		return FALSE;
	};

	//通过百分比修正持续的时间 add by wujianping
	virtual BOOL	RefixContinuanceByRate(UNIT_EFFECT &rImp, int32 nRate) const;
	//通过数值修正持续的时间 add by wujianping
	virtual BOOL	RefixContinuanceByPoint(UNIT_EFFECT &rImp, int32 nPoint) const;

    //引导技能 连线的效果 要用到此逻辑 就是判断对方是否还在引导中 
	//引导连线效果产生的做法是:在被引导方身上添加一个关心引导的BUFF 客户端就在有这个BUFF的玩家和引导者之间产生一条线
	//add by wujianping
	BOOL	IsSupportStillOn(UNIT_EFFECT &rImp, Character &rMe) const;

	//通知引导方 结束引导 //add by wujianping
	BOOL	NotifyStopChannelToEffectCaster(UNIT_EFFECT &rImp, Character &rMe) const;

	//修正暴击率 add by wujianping
	virtual void CriticalRefix(UNIT_EFFECT &rImp) const
	{
	};

	//搜索目标 add by wujianping
	virtual BOOL IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
	{
		return FALSE;
	};

	//置脏标记 add by wujianping
	virtual void MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
	{
	};

	//是否修正Pet的属性 add by wujianping
	virtual BOOL IsRefixPetInit() const
	{
		return FALSE;
	}

	//修正Pet的属性 add by wujianping
	virtual int32 GetRefixPetInitPara(int32 iType, UNIT_EFFECT &rImp, UNIT_EFFECT &rImpOut) const
	{
		rImpOut.Clear();
		return 0;
	};

	//修正天赋平衡 add by shangy
	virtual void RefixInherenceBalance(UNIT_EFFECT &rImp, InherenceBalanceRefixValue &rInherenceBalance) const
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//这是一个固定的计算公式 add by wujianping
	int32	GetResult(int32 iPara1, float fPara2, int32 iPara3, int32 iPara4, int32 iRate) const;

	//得到马对人物属性的修正 add by wujianping
	int32	GetHorseRefix(int32 iPara, Item *pPetItem, int32 iRate) const;

	//得到最终的伤害 add by wujianping
	void	FinalDamage(int32 *vDamage, Character &rMe) const;

	//计算剩余时间 add by wujianping
	virtual void	ContinuanceCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const;
	//计算间歇时间 add by wujianping
	virtual void	IntervalCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const;

	//搜索目标 add by wujianping
	BOOL	ScanUnitForTarget
		(
			UNIT_EFFECT	&rImp,
			Character	&rMe,
			GLPos const &rPos,
			float		fRadius,
			int32		nListSize,
			OBJLIST		&rTargets
		) const;

	//陷阱的心跳 add by wujianping
	virtual BOOL SpecialHeartBeatCheck(UNIT_EFFECT &rImp, Character &rMe) const
	{
		return TRUE;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

EffectLogic const *GetEffectLogic(UNIT_EFFECT const &rImp);

#endif
