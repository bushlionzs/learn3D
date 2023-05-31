/*$T MapServer/Server/Spell/SpellLogic/ProfessionSpellLogic.cpp GC 1.140 10/10/07 10:07:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "gameobject/Trap.h"
#include "TabDefine.h"
#include "Spell_Interface.h"
#include "Spell_TrapObjLogic_Trap.h"
#include "Spell_Logic_Profession.h"
#include "Spell_EffectLogic_All.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL XianZhi_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
	Object					*pObj = rMe.Spell_CreateObjSpecial
		(
			rParams.GetTargetPosition(),
			nDataIndex
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		KCheckEx(FALSE, "[XianZhi_Spell001::EffectOnUnitOnce]: Can't create Special Object!");
		return FALSE;
	}

	RegisterActiveObj(*pObj, rMe, 500);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HuoQiang_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 <= nDataIndex)
	{
		g_EffectInterface.SendEffectToUnit(rTar, nDataIndex, rMe.GetID(), rParams.GetDelayTime(), bCriticalFlag);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		nRefixedAbsorbRate = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 1);
	UNIT_EFFECT	*pTargetImp = rTar.Effect_GetFirstEffectOfSpecificLogicID(DS_XianZhi009_T::ID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTargetImp)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		DS_XianZhi009_T logic;
		/*~~~~~~~~~~~~~~~~~~*/

		return TRUE;
	}

	pTargetImp = rTar.Effect_GetFirstEffectOfSpecificLogicID(DS_XianZhi014_T::ID);
	if(NULL != pTargetImp)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		DS_XianZhi014_T logic;
		/*~~~~~~~~~~~~~~~~~~*/

		logic.SetAbsorbRate(*pTargetImp, nRefixedAbsorbRate);
		return TRUE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL JianXia_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	UNIT_EFFECT				impact;
	int32					nDepleteStrikePointSegment = rParams.GetDepletedStrikePoints() /
		STRIKE_POINT_SEGMENT_SIZE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(1 > nDepleteStrikePointSegment)
	{
		nDepleteStrikePointSegment = 1;
	}
	else if((MAX_STRIKE_POINT_SEGMENT) < nDepleteStrikePointSegment)
	{
		nDepleteStrikePointSegment = MAX_STRIKE_POINT_SEGMENT;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, nDepleteStrikePointSegment - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != nDataIndex)
	{
		g_EffectInterface.InitEffectFromData(nDataIndex, impact, rMe);
		if(DI_DamagesByValue_T::ID == GetEffectLogicID(impact))
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
BOOL WuShi_Spell001::IsSpecificTargetWanted(Character &rMe, Character &rTar, SpellInfo const &rSkillInfo) const
{
	__GUARD__ if(rMe.GetID() != rTar.GetID())
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL WuShi_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
	UNIT_EFFECT				impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_EffectInterface.InitEffectFromData(nDataIndex, impact, rMe);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ModifyHpMpRageStrikePointByValue_T const	logic;
	int32						nRage = rParams.GetDepletedRage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < rParams.GetTargetCount())
	{
		nRage = nRage / rParams.GetTargetCount();
	}

	logic.SetRageModification(impact, nRage);

	RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL WuShi_Spell002::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nRate = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
	UNIT_EFFECT				impact;
	CombatSystem				myCombatCore;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	myCombatCore.Reset();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nAdditionalAttack = Float2Int((rParams.GetDepletedRage() * nRate) / 100.0f);
	int32	nRefixRate = rSkillInfo.GetPowerRefixByRate();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;
	nAdditionalAttack = Float2Int(nAdditionalAttack * nRefixRate / 100.0f);
	myCombatCore.SetAdditionalAttackNear(nAdditionalAttack);
	myCombatCore.GetResultImpact(rMe, rTar, impact);

	RegisterImpactEvent(rTar, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SaMan_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	UNIT_EFFECT				impact;
	SOT_ShadowGuard_T			logic;
	int32					nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_EffectInterface.InitEffectFromData(nDataIndex, impact, rMe);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		nGuardDataID = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 1);
	Character	*pGuard = nullptr;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pGuard)
	{
		KCheckEx(FALSE, "[SaMan_Spell001::TakeEffectNow]:Can't Create __GUARD__. check now.");
		rParams.SetErrCode(OR_DEFAULT_ERROR);
		return FALSE;
	}

	logic.SetSummonerID(impact, rMe.GetID());
	logic.SetShadowGuardID(impact, pGuard->GetID());

	RegisterImpactEvent(rMe, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);
	RegisterImpactEvent(*pGuard, rMe, impact, rParams.GetDelayTime(), bCriticalFlag);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL QiShe_Spell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	GUID_t					guidTarget = rParams.GetTargetGuid();
	int32					nDataIndex = rSkillInfo.GetDescriptorByIndex(0)->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	Time_t					nDuration = rSkillInfo.GetDescriptorByIndex(1)->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != nDataIndex)
	{
		g_EffectInterface.SendEffectToUnit(rMe, nDataIndex, rMe.GetID(), rParams.GetDelayTime(), bCriticalFlag);
	}


	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL JianXia_SpellTrap::SpecificConditionCheck(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	SOT_Traps_T				Logic;
	int32					nAllTypeTotal = 0;
	int32					nThisTypeCount = 0;
	int32 const				nMaxTrapCount = Logic.MAX_TRAP_COUNT;
	const Descriptor			*pDescriptor1 = rSkillInfo.GetDescriptorByIndex(0);
	int32					nImpactDataIndex = pDescriptor1->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	const Descriptor			*pDescriptor2 = rSkillInfo.GetDescriptorByIndex(1);
	int32					nTrapDataIndex = pDescriptor2->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	const Descriptor			*pDescriptor3 = rSkillInfo.GetDescriptorByIndex(2);
	int32 const				nCountUpBorder = pDescriptor3->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	SpecialObjData_T const			*pData = DataManager::GetSingletonPtr()->getSpecialObjectDataById(nTrapDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		KCheckEx(FALSE, "[SkillLogic_T::SpecificConditionCheck]: Illegal Trap data found!!");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		nType = pData->GetClass();
	UNIT_EFFECT	*pImp = rMe.Effect_GetFirstEffectOfSpecificLogicID(Logic.ID);
	int32		nTrapCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pImp)
	{
		Logic.GetTrapCountOfSpecificType(*pImp, rMe, nType, nAllTypeTotal, nThisTypeCount);
		if(nMaxTrapCount <= nAllTypeTotal || nCountUpBorder <= nThisTypeCount)
		{
			rParams.SetErrCode(OR_TOO_MANY_TRAPS);
			return FALSE;
		}
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL JianXia_SpellTrap::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nImpactDataIndex = rSkillInfo.GetDescriptorByIndex(0)->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	int32					nTrapDataIndex = rSkillInfo.GetDescriptorByIndex(1)->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 > nImpactDataIndex || 0 > nTrapDataIndex)
	{
		KCheckEx(FALSE, "[Profession_7_Spell001::EffectOnUnitOnce]: Illegal data index found!!");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialCreature *pTrap = (SpecialCreature *) rMe.Spell_CreateObjSpecial(*(rMe.GetGLPos()), nTrapDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTrap)
	{
		KCheckEx(FALSE, "[SkillLogic_T::TakeEffectNow_ForTraps]: Can't create Special Obj!");
		return FALSE;
	}

	pTrap->SetPowerRefixByRate(rSkillInfo.GetPowerRefixByRate());
	pTrap->SetPowerRefixByValue(rSkillInfo.GetPowerRefixByValue());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nContinuance = pTrap->GetContinuance();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nContinuance = nContinuance + Float2Int(rSkillInfo.GetTimeRefixByRate() * nContinuance / 100.0f);
	nContinuance += rSkillInfo.GetTimeRefixByValue();
	pTrap->SetContinuance(nContinuance);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SOT_Traps_T	Logic;
	UNIT_EFFECT	impact;
	UNIT_EFFECT	*pImp = rMe.Effect_GetFirstEffectOfSpecificLogicID(Logic.ID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pImp)
	{
		g_EffectInterface.InitEffectFromData(nImpactDataIndex, impact, rMe);
		if(Logic.ID != GetEffectLogicID(impact))
		{
			KCheckEx(FALSE, "[Profession_7_Spell001::EffectOnUnitOnce]: Impact Data Error, Check it now..");
			return FALSE;
		}

		if(FALSE == Logic.AddNewTrap(impact, rMe, pTrap->GetID()))
		{
			KCheckEx(FALSE, "[Profession_7_Spell001::EffectOnUnitOnce]: Unknown Error, Check it now..");
			return FALSE;
		}

		RegisterImpactEvent(rMe, rMe, impact, 100, FALSE);
	}
	else
	{
		if(FALSE == Logic.AddNewTrap(*pImp, rMe, pTrap->GetID()))
		{
			return FALSE;
		}
	}

	RegisterActiveObj(*pTrap, rMe, 500);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Profession_9_Spell002::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Object					*pObj = NULL;
	ObjID_t					nObjID = 0;
	SpecialCreature				*pTrap = NULL;
	SpecialObjectLogic const			*pObjLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	impact;
		int32		nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID != nDataIndex)
		{
			g_EffectInterface.SendEffectToUnit
				(
					rMe,
					nDataIndex,
					rMe.GetID(),
					rParams.GetDelayTime(),
					bCriticalFlag
				);
		}
	}

	while(0);
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SOT_Traps_T	logic;
		UNIT_EFFECT	*pImp = rMe.Effect_GetFirstEffectOfSpecificLogicID(logic.ID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pImp)
		{
			return TRUE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = *pImp;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 nIdx = 0; logic.MAX_TRAP_COUNT >= nIdx; ++nIdx)
		{
			nObjID = logic.GetTrapByIndex(rImp, nIdx);
			if(INVALID_ID != nObjID)
			{
				pObj = rMe.GetSpecificObjInSameSceneByID(nObjID);
				if(NULL != pObj)
				{
					if(TRUE == IsObjSpecial(pObj->GetObjType()))
					{
						pTrap = (SpecialCreature *) pObj;
						pObjLogic = ObjSpecial_GetLogic(*pTrap);
						if(NULL != pObjLogic)
						{
							if(TRAP_OBJ == pObjLogic->GetType())
							{
								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
								TrapObjectLogic const	*pTrapLogic =
									(TrapObjectLogic const *) pObjLogic;
								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

								pTrapLogic->ForceActivate(*pTrap);
							}
						}
					}
				}
			}
		}
	}

	while(0);
	return TRUE;
	__UNGUARD__ return FALSE;
}
