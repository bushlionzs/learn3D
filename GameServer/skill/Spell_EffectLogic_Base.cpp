/*$T MapServer/Server/Spell/EffectLogic/SpellEffectLogic.cpp GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Spell_EffectLogic_Base.h"
#include "map/game_map.h"
#include "StructEffect.h"
#include "Spell_EffectLogicManager.h"
#include "gameobject/CharActionDelegator.h"
#include "data/data_manager.h"

/*
=======================================================================================================================
=======================================================================================================================
*/
void EffectLogic::FinalDamage(int32 *vDamage, Character &rMe) const
{
	__GUARD__ if(0 != vDamage[DAMAGE_TYPE_NEAR])
	{
		vDamage[DAMAGE_TYPE_NEAR] -= rMe.GetDefenceNear();
		if(rMe.GetNearAttReduce() != 0)
		{
			vDamage[DAMAGE_TYPE_NEAR] /= rMe.GetNearAttReduce();
		}
	}

	if(0 != vDamage[DAMAGE_TYPE_FAR])
	{
		vDamage[DAMAGE_TYPE_FAR] -= rMe.GetDefenceFar();
		if(rMe.GetFarAttReduce() != 0)
		{
			vDamage[DAMAGE_TYPE_FAR] /= rMe.GetFarAttReduce();
		}
	}

	if(0 != vDamage[DAMAGE_TYPE_M])
	{
		vDamage[DAMAGE_TYPE_M] -= rMe.Get_Property_DefenceMagic();
		if(rMe.GetMagicAttReduce() != 0)
		{
			vDamage[DAMAGE_TYPE_M] /= rMe.GetMagicAttReduce();
		}
	}

	if(0 != vDamage[DAMAGE_TYPE_COLD])
	{
		vDamage[DAMAGE_TYPE_COLD] -= rMe.Get_Property_DefenceCold();
	}

	if(0 != vDamage[DAMAGE_TYPE_FIRE])
	{
		vDamage[DAMAGE_TYPE_FIRE] -= rMe.Get_Property_DefenceFire();
	}

	if(0 != vDamage[DAMAGE_TYPE_LIGHT])
	{
		vDamage[DAMAGE_TYPE_LIGHT] -= rMe.Get_Property_DefenceLight();
	}

	if(0 != vDamage[DAMAGE_TYPE_POISON])
	{
		vDamage[DAMAGE_TYPE_POISON] -= rMe.Get_Property_DefencePoison();
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void EffectLogic::ContinuanceCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 const	nContinuance = rImp.GetContinuance();
	int32			nContinuanceElapsed = rImp.GetContinuanceElapsed();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == rImp.IsFadeOut())
	{
		if(TRUE == IsOverTimed())
		{
			if(-1 == nContinuance)
			{
				return;
			}

			if(nContinuanceElapsed <= nContinuance)
			{
				nContinuanceElapsed += nDeltaTime;
			}

			if(nContinuanceElapsed > nContinuance)
			{
				rMe.Effect_OnEffectFadeOut(rImp);
			}

			rImp.SetContinuanceElapsed(nContinuanceElapsed);
		}
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void EffectLogic::IntervalCalc(UNIT_EFFECT &rImp, Character &rMe, int32 nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nElapsedInterval = rImp.GetIntervalElapsed();
	int32		nContinuance = rImp.GetContinuance();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDeltaTime > nContinuance && 0 <= nContinuance)
	{
		nDeltaTime = nContinuance;
	}

	nElapsedInterval += nDeltaTime;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 const	nInterval = GetEffectInterval(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(nElapsedInterval >= nInterval)
	{
		OnEvent_IntervalOver(rImp, rMe);
		nElapsedInterval -= nInterval;
	}

	rImp.SetIntervalElapsed(nElapsedInterval);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL EffectLogic::RefixContinuanceByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ if(0 < rImp.GetContinuance() && TRUE == IsEffectOverTimed(rImp))
	{
		rImp.SetContinuance(Float2Int((rImp.GetContinuance() * nRate) / 100.0f));
	}

	__UNGUARD__ return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL EffectLogic::RefixContinuanceByPoint(UNIT_EFFECT &rImp, int32 nPoint) const
{
	__GUARD__ if(0 < rImp.GetContinuance() && TRUE == IsEffectOverTimed(rImp))
	{
		rImp.SetContinuance(rImp.GetContinuance() + nPoint);
	}

	__UNGUARD__ return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 EffectLogic::GetResult(int32 iPara1, float fPara2, int32 iPara3, int32 iPara4, int32 iRate) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRate = iRate * 0.01f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return Float2Int((iPara3 * iPara4 * 0.01f) * fRate);
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
EffectLogic const *GetEffectLogic(UNIT_EFFECT const &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t	nLogicID = GetEffectLogicID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return DataManager::GetSingletonPtr()->getEffectLogic(nLogicID);
	__UNGUARD__ return NULL;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */

void EffectLogic::HeartBeat(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bContinue = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == NeedEffectChannelSupport(rImp))
	{
		if(FALSE == IsSupportStillOn(rImp, rMe))
		{
			bContinue = FALSE;
		}
	}

	if(FALSE == rMe.IsAliveInDeed())
	{
		if(FALSE == IsEffectRemainOnCorpse(rImp))
		{
			bContinue = FALSE;
		}
	}

	if(FALSE == SpecialHeartBeatCheck(rImp, rMe))
	{
		bContinue = FALSE;
	}

	if(TRUE == bContinue)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nDeltaTime = rMe.GetLogicTime();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(TRUE == IsOverTimed())
		{
			if(TRUE == IsIntervaled())
			{
				IntervalCalc(rImp, rMe, nDeltaTime);
			}

			ContinuanceCalc(rImp, rMe, nDeltaTime);
		}
	}
	else
	{
		rMe.Effect_OnEffectFadeOut(rImp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectLogic::ScanUnitForTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	GLPos const &rPos,
	float		fRadius,
	int32		nListSize,
	OBJLIST		&rTargets
) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ GameMap			*pMap = rMe.GetMap();
	//SCANOR_AEIMPACT_INIT	ScanOperatorIniter;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//ScanOperatorIniter.m_pLogic = this;
	//ScanOperatorIniter.m_pMe = &rMe;
	//ScanOperatorIniter.m_pMap = pMap;
	//ScanOperatorIniter.m_pTargets = &rTargets;
	//ScanOperatorIniter.m_fRadius = fRadius;

	//if(-1 == nListSize)
	//{
	//	ScanOperatorIniter.m_nCount = rTargets.MAX_OBJ_LIST_SIZE - 1;
	//}
	//else
	//{
	//	ScanOperatorIniter.m_nCount = nListSize;
	//}

	//ScanOperatorIniter.m_Impact = rImp;
	//ScanOperatorIniter.m_CentrePoint.m_fX = rPos.m_fX;
	//ScanOperatorIniter.m_CentrePoint.m_fZ = rPos.m_fZ;

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Scanor_AEImpact	Scanor;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//Scanor.Init(&ScanOperatorIniter);
	//if(NULL != pMap)
	//{
	//	if(FALSE == pMap->Scan(&Scanor))
	//	{
	//		return FALSE;
	//	}
	//}
	//else
	//{
	//	return FALSE;
	//}

	//return TRUE;
	//__UNGUARD__ 
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectLogic::IsSupportStillOn(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(FALSE == IsObjCharacter(pObj->GetObjType()))
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	&rCaster = *(Character *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == GetGlobalActionDelegator().IsChanneling(rCaster))
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

BOOL EffectLogic::NotifyStopChannelToEffectCaster(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__
	if( TRUE == IsSupportStillOn(rImp, rMe) )
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pObj = GetEffectCaster(rMe, rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pObj)
		{
			return FALSE;
		}

		if(FALSE == IsObjCharacter(pObj->GetObjType()))
		{
			return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	&rCaster = *(Character *) pObj;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ActionDelegator	ActionOptor;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ActionOptor.StopChanneling(rCaster);
	}
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EffectLogic::GetHorseRefix(int32 iPara, Item *pPetItem, int32 iRate) const
{
	return 0;
}

