#include "stdafx.h"
#include "Spell_TrapObjLogic_Trap.h"
#include "gameobject/Trap.h"
#include "map/MapScanerOperators.h"
#include "Spell_EffectInterface.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void TrapObjectLogic::ForceActivate(SpecialCreature &rThis) const
{
	if(FALSE == rThis.IsFadeOut())
	{
		Activate(rThis);
		ForceFadeOut(rThis);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TrapObjectLogic::ForceFadeOut(SpecialCreature &rThis) const
{
	if(TRUE == ActivateWhenFadeOut(rThis))
	{
		Activate(rThis);
	}

	rThis.MarkFadeOutFlag();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TrapObjectLogic::OnEvent_Tick(SpecialCreature &rThisObj) const
{
	if(TRUE == TriggerCheck(rThisObj))
	{
		Activate(rThisObj);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TrapObjectLogic::OnEvent_TimeOver(SpecialCreature &rThisObj) const
{
	if(TRUE == rThisObj.IsFadeOut())
	{
		return;
	}

	if(TRUE == ActivateWhenFadeOut(rThisObj))
	{
		Activate(rThisObj);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::TriggerCheck(SpecialCreature &rThis) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ OBJLIST	Targets;
	GameMap*pMap = rThis.GetMap();
	SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SCANOPT_SOBJ_SCANPLAYER_INIT	ScanOperatorIniter;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ScanOperatorIniter.m_pMe = &rThis;
	ScanOperatorIniter.m_pMap = pMap;
	ScanOperatorIniter.m_pTargets = &Targets;
	ScanOperatorIniter.m_fRadius = pData->GetTriggerRadius();
	ScanOperatorIniter.m_nCount = 1;
	ScanOperatorIniter.m_CentrePoint.m_fX = rThis.GetGLPos()->m_fX;
	ScanOperatorIniter.m_CentrePoint.m_fZ = rThis.GetGLPos()->m_fZ;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScanOpt_SObj_ScanPlayer	Scanor;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Scanor.Init(&ScanOperatorIniter);
	if(NULL != pMap)
	{
		if(FALSE == pMap->Scan(&Scanor))
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	if(0 < Targets.m_Count)
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
void TrapObjectLogic::Activate(SpecialCreature &rThis) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ OBJLIST	Targets;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rThis.IsFadeOut())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap*pMap = rThis.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return;
	}

	if(0 < rThis.GetActiveTimes())
	{
		rThis.SetActiveTimes(rThis.GetActiveTimes() - 1);
	}
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SCANOPT_SOBJ_SCANPLAYER_INIT	ScanOperatorIniter;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		ScanOperatorIniter.m_pMe = &rThis;
		ScanOperatorIniter.m_pMap = pMap;
		ScanOperatorIniter.m_pTargets = &Targets;
		ScanOperatorIniter.m_fRadius = pData->GetEffectRadius();
		if(-1 == pData->GetEffectedObjNumber())
		{
			ScanOperatorIniter.m_nCount = Targets.MAX_OBJ_LIST_SIZE - 1;
		}
		else
		{
			ScanOperatorIniter.m_nCount = pData->GetEffectedObjNumber();
		}

		ScanOperatorIniter.m_CentrePoint.m_fX = rThis.GetGLPos()->m_fX;
		ScanOperatorIniter.m_CentrePoint.m_fZ = rThis.GetGLPos()->m_fZ;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ScanOpt_SObj_ScanPlayer	Scanor;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Scanor.Init(&ScanOperatorIniter);
		if(FALSE == pMap->Scan(&Scanor))
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ObjID_List	TargetIdList;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		TargetIdList.m_nCount = Targets.m_Count;
		for(int32 idx = 0; Targets.m_Count > idx; ++idx)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pTar = Targets.m_aObj[idx];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			TargetIdList.m_aIDs[idx] = pTar->GetID();

			if(TRUE == IsObjCharacter(pTar->GetObjType()))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Character	&rTar = (Character &) *pTar;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Player	*pPlayer = static_cast<Player *>(&rTar);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				}
			}
		}

		rThis.OnEvent_Trigger(TargetIdList);
		for(int32 idx = 0; Targets.m_Count > idx; ++idx)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pTar = Targets.m_aObj[idx];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pTar)
			{
				if(TRUE == IsObjCharacter(pTar->GetObjType()))
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Character	&rTar = (Character &) *pTar;
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER)
					{
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
						Player	*pPlayer = static_cast<Player *>(&rTar);
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					}

					EffectOnChar(rThis, rTar);
				}
			}
		}
	}

	while(0);
	Targets.Clear();
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SScanoptsObjScanTrapInit	ScanOperatorIniter;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		ScanOperatorIniter.m_pMe = &rThis;
		ScanOperatorIniter.m_pMap = pMap;
		ScanOperatorIniter.m_pTargets = &Targets;
		ScanOperatorIniter.m_fRadius = pData->GetEffectRadius();
		ScanOperatorIniter.m_nCount = pData->GetEffectedObjNumber();
		ScanOperatorIniter.m_CentrePoint.m_fX = rThis.GetGLPos()->m_fX;
		ScanOperatorIniter.m_CentrePoint.m_fZ = rThis.GetGLPos()->m_fZ;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ScanOptSObjScanTrap	Scanor;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Scanor.Init(&ScanOperatorIniter);
		if(FALSE == pMap->Scan(&Scanor))
		{
			return;
		}

		for(int32 idx = 0; Targets.m_Count > idx; ++idx)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pTar = Targets.m_aObj[idx];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pTar)
			{
				if(rThis.GetID() != pTar->GetID())
				{
					if(TRUE == IsObjSpecial(pTar->GetObjType()))
					{
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
						SpecialCreature &rTar = (SpecialCreature &) *pTar;
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

						EffectOnTrap(rThis, rTar);
					}
				}
			}
		}
	}

	while(0);

	if(0 == rThis.GetActiveTimes())
	{
		rThis.MarkFadeOutFlag();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::CanTriggerBySpecificObj(SpecialCreature &rMe, Character &rTar) const
{
	__GUARD__ if(FALSE == rTar.IsAliveInDeed())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = (Character *) rMe.GetSpecificObjInSameSceneByID(rMe.GetOwnerID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pOwner)
	{
		return FALSE;
	}

	if(pOwner->IsEnemy(&rTar))
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
BOOL TrapObjectLogic::CanTriggerBySpecificObj(SpecialCreature &rThis, SpecialCreature &rOther) const
{
	__GUARD__ if(TRAP_OBJ != rOther.GetClass())
	{
		return FALSE;
	}

	if(TRUE == CanTriggerByTrap(rThis))
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
BOOL TrapObjectLogic::IsScanedTargetValid(SpecialCreature &rThis, Character &rScaned) const
{
	__GUARD__ return CanTriggerBySpecificObj(rThis, rScaned);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::IsScanedTargetValid(SpecialCreature &rThis, SpecialCreature &rScaned) const
{
	__GUARD__ if(rThis.GetID() != rScaned.GetID())
	{
		return CanTriggerBySpecificObj(rScaned, rThis);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::EffectOnChar(SpecialCreature &rThis, Character &rTar) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nImpact = INVALID_ID;
	int32		nOdds = 0;
	int32		nRand = 0;
	GameMap*pMap = rThis.GetMap();
	Character	*pOwner = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		rThis.MarkFadeOutFlag();
		return FALSE;
	}

	Object	*pObj = pMap->GetSpecificObjByID(rThis.GetOwnerID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj || FALSE == pObj->IsActiveObj() || !IsObjCharacter(pObj->GetObjType()))
	{
		return FALSE;
	}

	pOwner = static_cast<Character *>(pObj);

	pMap->GetEventCore().RegisterBeSkillEvent(rTar.GetID(), rThis.GetOwnerID(), BEHAVIOR_TYPE_HOSTILITY, 500);
	nImpact = GetEffect0(rThis);
	if(INVALID_ID != nImpact)
	{
		BOOL bRlt = CheckEffectAvailability(*pOwner, rTar, nImpact);

		if (bRlt)
		{
			g_EffectInterface.SendEffectToUnit
				(
				rTar,
				nImpact,
				rThis.GetOwnerID(),
				500,
				FALSE,
				rThis.GetPowerRefixByRate()
				);
		}
		else
		{
			pMap->GetEventCore().RegisterSkillMissEvent
				(
				rTar.GetID(),
				rThis.GetOwnerID(),
				0,
				0, 
				CombatMissFlag::FLAG_RESIST
				);
		}

		//g_EffectInterface.SendEffectToUnit
		//	(
		//	rTar,
		//	nImpact,
		//	rThis.GetOwnerID(),
		//	500,
		//	FALSE,
		//	rThis.GetPowerRefixByRate()
		//	);
	}

	nImpact = GetEffect1(rThis);
	if(INVALID_ID != nImpact)
	{
		BOOL bRlt = CheckEffectAvailability(*pOwner, rTar, nImpact);
		if (bRlt)
		{
			g_EffectInterface.SendEffectToUnit
				(
				rTar,
				nImpact,
				rThis.GetOwnerID(),
				500,
				FALSE,
				rThis.GetPowerRefixByRate()
				);
		}
		else
		{
			pMap->GetEventCore().RegisterSkillMissEvent
				(
				rTar.GetID(),
				rThis.GetOwnerID(),
				0,
				0,
				CombatMissFlag::FLAG_RESIST
				);
		}

		//g_EffectInterface.SendEffectToUnit
		//	(
		//	rTar,
		//	nImpact,
		//	rThis.GetOwnerID(),
		//	500,
		//	FALSE,
		//	rThis.GetPowerRefixByRate()
		//	);
	}

	nRand = pMap->GetRand100();
	nOdds = GetEffect2ActivateOdds(rThis);
	if(nRand < nOdds)
	{
		nImpact = GetEffect2(rThis);
		if(INVALID_ID != nImpact)
		{
			BOOL bRlt = CheckEffectAvailability(*pOwner, rTar, nImpact);

			if (bRlt)
			{
				g_EffectInterface.SendEffectToUnit
					(
					rTar,
					nImpact,
					rThis.GetOwnerID(),
					500,
					FALSE,
					rThis.GetPowerRefixByRate()
					);
			}
			else
			{
				pMap->GetEventCore().RegisterSkillMissEvent
					(
					rTar.GetID(),
					rThis.GetOwnerID(),
					0,
					0,
					CombatMissFlag::FLAG_RESIST
					);
			}

			//g_EffectInterface.SendEffectToUnit
			//	(
			//	rTar,
			//	nImpact,
			//	rThis.GetOwnerID(),
			//	500,
			//	FALSE,
			//	rThis.GetPowerRefixByRate()
			//	);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL TrapObjectLogic::CheckEffectAvailability(Character &rMe, Character &rTar, ID_t nDataIndex) const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::EffectOnTrap(SpecialCreature &rThis, SpecialCreature &rTar) const
{
	__GUARD__ if(TRAP_OBJ != rTar.GetClass())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TrapObjectLogic const	*pLogic = (TrapObjectLogic const *) ObjSpecial_GetLogic(rTar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pLogic)
	{
		KCheckEx(FALSE, "[TrapLogic_T::EffectOnTrap]: Can't find Logic Instance.");
		return FALSE;
	}

	if(TRUE == pLogic->CanTriggerBySpecificObj(rTar, rThis))
	{
		ForceActivate(rTar);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::CanTriggerByTrap(SpecialCreature &rThis) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nFlag = pData->GetTrapUsedFlags();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 < (nFlag & MASK_TRIGGER_BY_TRAP))
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::ActivateWhenFadeOut(SpecialCreature &rThis) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nFlag = pData->GetTrapUsedFlags();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 < (nFlag & MASK_ACTIVATE_WHEN_FADE_OUT))
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TrapObjectLogic::CanTriggerByCharacter(SpecialCreature &rThis) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nFlag = pData->GetTrapUsedFlags();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 < (nFlag & MASK_TRIGGER_BY_CHARACTER))
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 TrapObjectLogic::GetEffect0(SpecialCreature &rThis) const
{
	__GUARD__ return GetDescriptorValueByIndex(rThis, DescriptorIndex::INDEX_EFFECT0);
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 TrapObjectLogic::GetEffect1(SpecialCreature &rThis) const
{
	__GUARD__ return GetDescriptorValueByIndex(rThis, DescriptorIndex::INDEX_EFFECT1);
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 TrapObjectLogic::GetEffect2(SpecialCreature &rThis) const
{
	__GUARD__ return GetDescriptorValueByIndex(rThis, DescriptorIndex::INDEX_EFFECT2);
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 TrapObjectLogic::GetEffect2ActivateOdds(SpecialCreature &rThis) const
{
	__GUARD__ return GetDescriptorValueByIndex(rThis, DescriptorIndex::INDEX_EFFECT2_ACTIVATE_ODDS);
	__UNGUARD__ return INVALID_ID;
}
