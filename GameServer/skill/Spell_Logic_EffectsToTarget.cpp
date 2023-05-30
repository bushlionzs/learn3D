/*$T MapServer/Server/Spell/SpellLogic/EffectsToTarget.cpp GC 1.140 10/10/07 10:07:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Spell_Logic_EffectsToTarget.h"
#include "Spell_Helper.h"
#include "Spell_EffectInterface.h"
#include "server_settting.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL EffectsToTarget::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; IMPACT_NUMBER > nIdx; ++nIdx)
	{
		nValue = GetActivateOnceEffectByIndex(rSkillInfo, nIdx);

		if(INVALID_ID != nValue)
		{
			g_EffectInterface.InitEffectFromData(nValue, impact, rMe);

			if
			(
				DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
			||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
			)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				DI_DamagesByValue_T	logic;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(TRUE == bCriticalFlag)
				{
					impact.MarkCriticalFlag();
				}
				else if(DI_DamagesByRate_T::ID == GetEffectLogicID(impact))
				{
					for(int32 i = 0; i < impact.MAX_IMPACT_PARAM_NUMBER; ++i)
					{
						impact.SetParamByIndex(i, 0);
					}
				}

				logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());

				ComputeCriticalDamages(impact, logic, rMe, rTar);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				CombatSystem	myCombatCore;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				myCombatCore.Reset();

				myCombatCore.GetResultImpact(rMe, rTar, impact);
			}

			RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectsToTarget::EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; IMPACT_NUMBER > nIdx; ++nIdx)
	{
		nValue = GetActivateEachTickEffectByIndex(rSkillInfo, nIdx);
		if(INVALID_ID != nValue)
		{
			g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
			if
			(
				DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
			||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
			)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				DI_DamagesByValue_T	logic;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(TRUE == bCriticalFlag)
				{
					impact.MarkCriticalFlag();
				}
				else if(DI_DamagesByRate_T::ID == GetEffectLogicID(impact))
				{
					for(int32 i = 0; i < impact.MAX_IMPACT_PARAM_NUMBER; ++i)
					{
						impact.SetParamByIndex(i, 0);
					}
				}

				logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());
				ComputeCriticalDamages(impact, logic, rMe, rTar);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				CombatSystem	myCombatCore;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				myCombatCore.Reset();
				myCombatCore.GetResultImpact(rMe, rTar, impact);
			}

			RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTarget::GetActivateOnceEffectByIndex(SpellInfo const &rSkill, int32 nIndex) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT + 2 * nIndex
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTarget::GetActivateEachTickEffectByIndex(SpellInfo const &rSkill, int32 nIndex) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_EACH_TICK_IMPACT + 2 * nIndex
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTarget::GetCriticalDamageRefix(Character &rMe, Character &rTar, int32 iTmp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iCriticalDamageRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		iCriticalDamageRate = ((Player *) &rMe)->GetEquipCriticalHurt() + ((Player *) &rMe)->GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL_HURT);
	}

	iCriticalDamageRate = (g_Config.m_ConfigInfo.m_nCriticalDamageRate + iCriticalDamageRate);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTargetC = g_Config.m_ConfigInfo.m_nToughEffCriticalDamage;
	int32	iTargetCritical = rTar.GetToughness();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTargetC < 1)
	{
		iTargetC = 1;
	}

	iTargetCritical = Float2Int(iTargetCritical * 100 / iTargetC);

	CombatSystem Combat;
	float	iFinal = Combat.RefixCritDamagebyInherenceBalance(iCriticalDamageRate, iTargetCritical, rMe, rTar);

	if(iFinal < 1)
	{
		iFinal = 1;
	}

	int32 Damage = Float2Int(iTmp * iFinal * 0.01f);

	if(g_Config.m_ConfigInfo.m_nToggleDebugInherenceBalance)
	{
		QLogSystem::QUICK_LOG
			(
			QUICK_LOG_DEBUG,
			"EffectsToTarget::GetCriticalDamageRefix iCriticalDamageRate = %d, iTargetCritical = %d, iFinal = %f, iTmp = %d, Damage = %d",
			iCriticalDamageRate,
			iTargetCritical,
			iFinal,
			iTmp,
			Damage
			);
	}

	return Damage;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void EffectsToTarget::ComputeCriticalDamages
(
	UNIT_EFFECT		&impact,
	DI_DamagesByValue_T	&logic,
	Character		&rMe,
	Character		&rTar
) const
{
	if(!impact.IsCriticalHit())
	{
		return;
	}

	logic.CriticalRefix(impact);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTmp = rMe.GetAttackNear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageNear(impact, iTmp);

	iTmp = rMe.GetAttackFar();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageFar(impact, iTmp);

	iTmp = rMe.Get_Property_AttackMagic();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageMagic(impact, iTmp);

	iTmp = rMe.Get_Property_AttackCold();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageCold(impact, iTmp);

	iTmp = rMe.Get_Property_AttackFire();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageFire(impact, iTmp);

	iTmp = rMe.Get_Property_AttackLight();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageLight(impact, iTmp);

	iTmp = rMe.Get_Property_AttackPoison();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamagePoison(impact, iTmp);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectsToTargetAndSelf::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nValue = GetActivateOnceEffectForSelf(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		RegisterImpactEvent(rMe, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	nValue = GetActivateOnceEffectForTarget(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		if
		(
			DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
		||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
		)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			DI_DamagesByValue_T	logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			CombatSystem	myCombatCore;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			myCombatCore.Reset();
			myCombatCore.GetResultImpact(rMe, rTar, impact);
		}

		RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectsToTargetAndSelf::EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nValue = GetActivateEachTickEffectForSelf(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		RegisterImpactEvent(rMe, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	nValue = GetActivateEachTickEffectForTarget(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		if
		(
			DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
		||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
		)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			DI_DamagesByValue_T	logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			CombatSystem	myCombatCore;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			myCombatCore.Reset();
			myCombatCore.GetResultImpact(rMe, rTar, impact);
		}

		RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelf::GetActivateOnceEffectForSelf(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_FOR_SELF
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelf::GetActivateEachTickEffectForSelf(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_SELF
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelf::GetActivateOnceEffectForTarget(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_FOR_TARGET
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelf::GetActivateEachTickEffectForTarget(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_TARGET
		);
	__UNGUARD__ return 0;
}

int32 EffectsToTargetAndSelfForRun::GetCriticalDamageRefix(Character &rMe, Character &rTar, int32 iTmp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iCriticalDamageRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		iCriticalDamageRate = ((Player *) &rMe)->GetEquipCriticalHurt() + ((Player *) &rMe)->GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL_HURT);
	}

	iCriticalDamageRate = (g_Config.m_ConfigInfo.m_nCriticalDamageRate + iCriticalDamageRate);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTargetC = g_Config.m_ConfigInfo.m_nToughEffCriticalDamage;
	int32	iTargetCritical = rTar.GetToughness();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTargetC < 1)
	{
		iTargetC = 1;
	}

	iTargetCritical = Float2Int(iTargetCritical * 100 / iTargetC);

	CombatSystem Combat;
	float	iFinal = Combat.RefixCritDamagebyInherenceBalance(iCriticalDamageRate, iTargetCritical, rMe, rTar);

	if(iFinal < 1)
	{
		iFinal = 1;
	}

	int32 Damage = Float2Int(iTmp * iFinal * 0.01f);

	if(g_Config.m_ConfigInfo.m_nToggleDebugInherenceBalance)
	{
		QLogSystem::QUICK_LOG
			(
			QUICK_LOG_DEBUG,
			"EffectsToTargetAndSelfForRun::GetCriticalDamageRefix iCriticalDamageRate = %d, iTargetCritical = %d, iFinal = %f, iTmp = %d, Damage = %d",
			iCriticalDamageRate,
			iTargetCritical,
			iFinal,
			iTmp,
			Damage
			);
	}

	return Damage;
	
	__UNGUARD__ return 0;
}

void EffectsToTargetAndSelfForRun::ComputeCriticalDamages
(
 UNIT_EFFECT		&impact,
 DI_DamagesByValue_T	&logic,
 Character		&rMe,
 Character		&rTar
 ) const
{
	if(!impact.IsCriticalHit())
	{
		return;
	}

	logic.CriticalRefix(impact);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTmp = rMe.GetAttackNear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageNear(impact, iTmp);

	iTmp = rMe.GetAttackFar();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageFar(impact, iTmp);

	iTmp = rMe.Get_Property_AttackMagic();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageMagic(impact, iTmp);

	iTmp = rMe.Get_Property_AttackCold();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageCold(impact, iTmp);

	iTmp = rMe.Get_Property_AttackFire();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageFire(impact, iTmp);

	iTmp = rMe.Get_Property_AttackLight();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamageLight(impact, iTmp);

	iTmp = rMe.Get_Property_AttackPoison();
	iTmp = GetCriticalDamageRefix(rMe, rTar, iTmp);
	logic.SetDamagePoison(impact, iTmp);
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectsToTargetAndSelfForRun::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nValue = GetActivateOnceEffectForSelf(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		RegisterImpactEvent(rMe, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	for( int32 i = SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_0_FOR_TARGET; i <= SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_2_FOR_TARGET; ++i)
	{
		nValue = GetActivateOnceEffectForTarget(rSkillInfo, i);
		if(INVALID_ID != nValue)
		{
			g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
			if
				(
				DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
				||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
				)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				DI_DamagesByValue_T	logic;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(TRUE == bCriticalFlag)
				{
					impact.MarkCriticalFlag();
				}
				else if(DI_DamagesByRate_T::ID == GetEffectLogicID(impact))
				{
					for(int32 i = 0; i < impact.MAX_IMPACT_PARAM_NUMBER; ++i)
					{
						impact.SetParamByIndex(i, 0);
					}
				}

				logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());
				ComputeCriticalDamages(impact, logic, rMe, rTar);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				CombatSystem	myCombatCore;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				myCombatCore.Reset();
				myCombatCore.GetResultImpact(rMe, rTar, impact);
			}

			RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectsToTargetAndSelfForRun::EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nValue = GetActivateEachTickEffectForSelf(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		RegisterImpactEvent(rMe, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	nValue = GetActivateEachTickEffectForTarget(rSkillInfo);
	if(INVALID_ID != nValue)
	{
		g_EffectInterface.InitEffectFromData(nValue, impact, rMe);
		if
		(
			DI_DamagesByValue_T::ID == GetEffectLogicID(impact)
		||	DI_DamagesByRate_T::ID == GetEffectLogicID(impact)
		)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			DI_DamagesByValue_T	logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			logic.RefixPowerByRate(impact, rSkillInfo.GetPowerRefixByRate());

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			CombatSystem	myCombatCore;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			myCombatCore.Reset();
			myCombatCore.GetResultImpact(rMe, rTar, impact);
		}

		RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelfForRun::GetActivateOnceEffectForSelf(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_FOR_SELF
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelfForRun::GetActivateEachTickEffectForSelf(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_SELF
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelfForRun::GetActivateOnceEffectForTarget(SpellInfo const &rSkill, int32 nIndex) const
{
	__GUARD__ 
		KCheck( nIndex >= SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_0_FOR_TARGET && nIndex <= SkillInfoDescriptorIndex_T::IDX_ACTIVATE_ONCE_IMPACT_2_FOR_TARGET );
	return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			nIndex
		);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectsToTargetAndSelfForRun::GetActivateEachTickEffectForTarget(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex
		(
			rSkill,
			SkillInfoDescriptorIndex_T::IDX_ACTIVATE_EACH_TICK_IMPACT_FOR_TARGET
		);
	__UNGUARD__ return 0;
}
