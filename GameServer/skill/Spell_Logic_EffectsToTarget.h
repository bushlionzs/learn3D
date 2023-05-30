///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName:Spell_Logic_EffectsToTarget.h
//Author:
//Date:
//Describe:战斗技能逻辑的具体实现：在目标身上加buff，在目标和自己身上加buff，在目标和自己身上加buff（冲锋类） 
//History:
//		1.
//		2.
//		3.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef IMPACTTOTARGET_H
#define IMPACTTOTARGET_H

#include "TypeDefine.h"
#include "Spell_Logic_Base.h"
#include "Spell_EffectLogic_All.h"

/*
=======================================================================================================================
add by shangy
EffectsToTarget ;
战斗技能逻辑的具体实现:
1.作用于目标
2.有暴击判断
3.按照人物自身属性计算伤害值
使用范围：目前大部分技能使用的逻辑
=======================================================================================================================
*/
class EffectsToTarget :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = IMPACTS_TO_TARGET, };
	enum { IMPACT_NUMBER = 6, };
	class SkillInfoDescriptorIndex_T	//技能表中的参数
	{
	public: enum { IDX_ACTIVATE_ONCE_IMPACT = 0, IDX_ACTIVATE_EACH_TICK_IMPACT, };//：0 激活一次的IMPACTID 1 间隔时间激活的IMPACTID
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	EffectsToTarget()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectsToTarget()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsPassive(void) const	//是否被动技能
	{
		return FALSE;
	};

	int32	GetActivateOnceEffectByIndex(SpellInfo const &rSkill, int32 nIndex) const;
	int32	GetActivateEachTickEffectByIndex(SpellInfo const &rSkill, int32 nIndex) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

	void	ComputeCriticalDamages
		(
			UNIT_EFFECT		&impact,
			DI_DamagesByValue_T	&logic,
			Character		&rMe,
			Character		&rTar
		) const;
	int32	GetCriticalDamageRefix(Character &rMe, Character &rTar, int32 iTmp) const;
	BOOL	EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

/*
=======================================================================================================================
add by shangy
class EffectsToTargetAndSelf :
战斗技能逻辑的具体实现:
1.作用于目标和自己
2.无暴击判断
3.按照人物自身属性计算伤害值
使用范围：凌波微步
=======================================================================================================================
*/
class EffectsToTargetAndSelf :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = IMPACTS_TO_TARGET_AND_SELF, };
	class SkillInfoDescriptorIndex_T
	{
	public:
		enum
		{
			IDX_ACTIVATE_ONCE_IMPACT_FOR_SELF	= 0,
			IDX_ACTIVATE_ONCE_IMPACT_FOR_TARGET,
			IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_SELF,
			IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_TARGET,
		};
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	EffectsToTargetAndSelf()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectsToTargetAndSelf()
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

	int32	GetActivateOnceEffectForSelf(SpellInfo const &rSkill) const;
	int32	GetActivateEachTickEffectForSelf(SpellInfo const &rSkill) const;
	int32	GetActivateOnceEffectForTarget(SpellInfo const &rSkill) const;
	int32	GetActivateEachTickEffectForTarget(SpellInfo const &rSkill) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;
	BOOL	EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

/*
=======================================================================================================================
add by shangy
EffectsToTargetAndSelfForRun ;
战斗技能逻辑的具体实现：
1.作用于目标和自己
2.有暴击实现
3.按照人物自身属性计算伤害值
使用范围：冲锋类技能使用
=======================================================================================================================
*/
class EffectsToTargetAndSelfForRun :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = IMPACTS_TO_TARGET_AND_SELF_FOR_RUN, };
	class SkillInfoDescriptorIndex_T
	{
	public:
		enum
		{
			IDX_ACTIVATE_ONCE_IMPACT_FOR_SELF	= 0,
			IDX_ACTIVATE_ONCE_IMPACT_0_FOR_TARGET,
			IDX_ACTIVATE_ONCE_IMPACT_1_FOR_TARGET,
			IDX_ACTIVATE_ONCE_IMPACT_2_FOR_TARGET,
			IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_SELF,
			IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_TARGET,
		};
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	EffectsToTargetAndSelfForRun()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~EffectsToTargetAndSelfForRun()
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

	int32	GetActivateOnceEffectForSelf(SpellInfo const &rSkill) const;
	int32	GetActivateEachTickEffectForSelf(SpellInfo const &rSkill) const;
	int32	GetActivateOnceEffectForTarget(SpellInfo const &rSkill, int32 nIndex) const;
	int32	GetActivateEachTickEffectForTarget(SpellInfo const &rSkill) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	ComputeCriticalDamages
		(
		UNIT_EFFECT		&impact,
		DI_DamagesByValue_T	&logic,
		Character		&rMe,
		Character		&rTar
		) const;
	int32	GetCriticalDamageRefix(Character &rMe, Character &rTar, int32 iTmp) const;
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;
	BOOL	EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};
#endif
