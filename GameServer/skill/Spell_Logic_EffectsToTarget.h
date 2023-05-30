///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName:Spell_Logic_EffectsToTarget.h
//Author:
//Date:
//Describe:ս�������߼��ľ���ʵ�֣���Ŀ�����ϼ�buff����Ŀ����Լ����ϼ�buff����Ŀ����Լ����ϼ�buff������ࣩ 
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
ս�������߼��ľ���ʵ��:
1.������Ŀ��
2.�б����ж�
3.���������������Լ����˺�ֵ
ʹ�÷�Χ��Ŀǰ�󲿷ּ���ʹ�õ��߼�
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
	class SkillInfoDescriptorIndex_T	//���ܱ��еĲ���
	{
	public: enum { IDX_ACTIVATE_ONCE_IMPACT = 0, IDX_ACTIVATE_EACH_TICK_IMPACT, };//��0 ����һ�ε�IMPACTID 1 ���ʱ�伤���IMPACTID
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
	BOOL IsPassive(void) const	//�Ƿ񱻶�����
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
ս�������߼��ľ���ʵ��:
1.������Ŀ����Լ�
2.�ޱ����ж�
3.���������������Լ����˺�ֵ
ʹ�÷�Χ���貨΢��
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
ս�������߼��ľ���ʵ�֣�
1.������Ŀ����Լ�
2.�б���ʵ��
3.���������������Լ����˺�ֵ
ʹ�÷�Χ������༼��ʹ��
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
