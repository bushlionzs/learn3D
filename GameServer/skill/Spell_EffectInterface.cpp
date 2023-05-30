/*$T MapServer/Server/Spell/EffectSystem.cpp GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "stdlib.h"
#include "TypeDefine.h"
#include "Spell_EffectInterface.h"
#include "map/game_map.h"
#include "Spell_EffectLogicManager.h"
#include "BaseTool.h"
#include "TabDefine.h"
#include "SpellDataLoader.h"
#include "data/data_manager.h"

EffectInterface	g_EffectInterface;


/*
=======================================================================================================================
=======================================================================================================================
*/
int32 GetEffectScriptID(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		nEffectID = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nEffectID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return INVALID_ID;
	}

	return pData->GetEventScriptID();
	__UNGUARD__ return INVALID_ID;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Character *GetEffectCharacterObj(UNIT_EFFECT &rImp, Character &rMe)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return NULL;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pAttacker = (Character *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pAttacker;
	__UNGUARD__ return NULL;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */

uint32 EffectInterface::GetUniqueID()
{
	__GUARD__++m_uUniqueID;
	if(0 == m_uUniqueID) ++m_uUniqueID;
	return m_uUniqueID;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectInterface::SendEffectToUnit
(
	Character	&rTar,
	ID_t		nDataIndex,
	ObjID_t		nSender,
	SpellID_t	nSkillID,
	Time_t		nDelayTime,
	BOOL		bCriticalFlag,
	int32		nRefixRate
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ UNIT_EFFECT	impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nDataIndex)
	{
		return FALSE;
	}

	if(TRUE == InitEffectFromData(nDataIndex, impact, rTar))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		EffectLogic const	*pLogic = GetEffectLogic(impact);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pLogic)
		{
			KCheck(NULL == "[EffectSystem::SendEffectToUnit]: Can't find sprcific logic for this impact.");
			return FALSE;
		}

		if(TRUE == bCriticalFlag)
		{
			impact.MarkCriticalFlag();
		}

		if(0 != nRefixRate)
		{
			pLogic->RefixPowerByRate(impact, nRefixRate);
		}

		if(0 > nDelayTime)
		{
			nDelayTime = 0;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		GameMap		*pMap = rTar.GetMap();
		Character	*pChar = NULL;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pMap)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = pMap->GetSpecificObjByID(nSender);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(IsObjCharacter(pObj->GetObjType()))
			{
				impact.SetSkillID(nSkillID);
			}

			return pMap->GetEventCore().RegisterImpactEvent(rTar.GetID(), nSender, impact, nDelayTime);
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/

BOOL EffectInterface::InitEffectFromData(ID_t nDataIndex, UNIT_EFFECT &rImp, Character &rTar) const
{
	__GUARD__ rImp.Clear();

	rImp.SetDataIndex(nDataIndex);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		rImp.SetImpactID(pData->GetImpactID());

		rImp.SetContinuance(pData->GetContinuance());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		EffectLogic const	*pLogic = GetEffectLogic(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pLogic)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rTar.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pMap == NULL)
			{
				return FALSE;
			}

			/*~~~~~~~~~~~~~~~~~~~~*/
			int32	iSkillLevel = 0;
			/*~~~~~~~~~~~~~~~~~~~~*/

			rImp.SetSkillLevel(iSkillLevel);

			if(TRUE == pLogic->InitFromData(rImp, *pData))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EffectInterface::SendEffectToUnit
(
	Character	&rTar,
	ID_t		nDataIndex,
	ObjID_t		nSender,
	Time_t		nDelayTime,
	BOOL		bCriticalFlag,
	int32		nRefixRate
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ UNIT_EFFECT	impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nDataIndex)
	{
		return FALSE;
	}

	if(TRUE == InitEffectFromData(nDataIndex, impact, rTar))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		EffectLogic const	*pLogic = GetEffectLogic(impact);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pLogic)
		{
			KCheck(NULL == "[EffectSystem::SendEffectToUnit]: Can't find sprcific logic for this impact.");
			return FALSE;
		}

		if(TRUE == bCriticalFlag)
		{
			impact.MarkCriticalFlag();
		}

		if(0 != nRefixRate)
		{
			pLogic->RefixPowerByRate(impact, nRefixRate);
		}

		if(0 > nDelayTime)
		{
			nDelayTime = 0;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		GameMap		*pMap = rTar.GetMap();
		Character	*pChar = NULL;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pMap)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = pMap->GetSpecificObjByID(nSender);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(IsObjCharacter(pObj->GetObjType()))
			{
				pChar = static_cast<Character *>(pObj);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				SpellInfo	&rSkillInfo = pChar->GetSpellInfo();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				impact.SetSkillID(rSkillInfo.GetSpellID());
			}

			return pMap->GetEventCore().RegisterImpactEvent(rTar.GetID(), nSender, impact, nDelayTime);
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t GetEffectLogicID(UNIT_EFFECT const &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetLogicID();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectOverTimed(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL			bIsOverTimed = pData->IsOverTimed();
	EffectLogic const	*pLogic = GetEffectLogic(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pLogic)
	{
		if(pLogic->IsOverTimed() != bIsOverTimed)
		{
			KCheck(NULL == "[IsEffectOverTimed] Logic is not match the data.");
			return pLogic->IsOverTimed();
		}
	}

	return bIsOverTimed;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t GetEffectID(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetImpactID();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
EffectData const *GetEffectDataBlock(ID_t nDataIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EffectData const	*pData = DataManager::GetSingletonPtr()->getEffectData(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		char	szBuffer[256];
		/*~~~~~~~~~~~~~~~~~~*/

		sprintf(szBuffer, "[GetEffectDataBlock]: Can't find specific Data for impact(%d)", nDataIndex);
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG, szBuffer);

		return NULL;
	}

	return pData;
	__UNGUARD__ return NULL;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Object *GetEffectCaster(Object &rMe, UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = NULL;
	ObjID_t			nCasterID = rImp.GetCasterObjID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != nCasterID)
	{
		pObj = rMe.GetSpecificObjInSameSceneByID(nCasterID);
	}

	if(NULL == pObj)
	{
		if(TRUE == rImp.IsCreateByPlayer())
		{
			pObj = rMe.GetSpecificHumanInSameSceneByGUID(rImp.GetCasterUniqueID());
			if(NULL != pObj)
			{
				nCasterID = pObj->GetID();
			}
			else
			{
				nCasterID = INVALID_ID;
			}
		}
		else
		{
			nCasterID = INVALID_ID;
		}
	}

	rImp.SetCasterObjID(nCasterID);
	return pObj;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t GetEffectMutexID(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetMutexID();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t GetEffectLevel(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetLevel();
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t GetEffectStandFlag(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetStandFlag();
	}

	return BEHAVIOR_TYPE_NEUTRALITY;
	__UNGUARD__ return BEHAVIOR_TYPE_NEUTRALITY;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectRemainOnCorpse(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsRemainOnCorpse();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CanEffectBeDispeled(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->CanBeDispeled();
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CanEffectBeCanceled(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->CanBeCanceled();
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL NeedEffectChannelSupport(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->NeedChannelSupport();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectFadeOutWhenUnitOnDamage(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsFadeOutWhenUnitOnDamage();
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectFadeOutWhenUnitStartActions(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsFadeOutWhenUnitStartActions();
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectFadeOutWhenUnitOffline(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsFadeOutWhenUnitOffline();
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectStillTimingWhenUnitOffline(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsStillTimingWhenUnitOffline();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectPassive(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IsPassive();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t IgnoreEffectFliter(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->IgnoreFliter();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Time_t GetEffectTableContinuance(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetContinuance();
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Time_t GetEffectInterval(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetInterval();
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GetEffectDataDescriptorValueByIndex(int32 nDataIndex, int32 nIndex, int32 iLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Descriptor const	*pDescriptor = pData->GetDescriptorByIndex(nIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pDescriptor)
		{
			return pDescriptor->GetValueBySkillLevel(iLevel);
		}
		else
		{
			KCheck(NULL == "[GetEffectDataDescriptorValueByIndex]: Illegal index found!");
		}
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectInCollection(UNIT_EFFECT &rImp, int32 nCollectionID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		nID = INVALID_ID;
	IDCollection const	*pCollection = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pCollection = DataManager::GetSingletonPtr()->getCollection(nCollectionID);
	if(NULL != pCollection)
	{
		switch(pCollection->GetType())
		{
		case IDCollection::TYPE_BUFF_ID:
			if(TRUE == IsEffectOverTimed(rImp))
			{
				nID = GetEffectID(rImp);
			}
			break;

		case IDCollection::TYPE_EFFECT_LOGIC_ID:
			nID = GetEffectLogicID(rImp);
			break;

		case IDCollection::TYPE_EFFECT_MUTEX_ID:
			nID = GetEffectMutexID(rImp);
			break;

		case IDCollection::TYPE_SPELL_ID:
			nID = rImp.GetSkillID();
			break;

		case IDCollection::TYPE_DIRECT_EFFECT_ID:
			nID = GetEffectID(rImp);
			break;

		case IDCollection::TYPE_SPELL_LOGIC_ID:
		default:
			break;
		}

		if(INVALID_ID != nID)
		{
			if(0 < pCollection->GetCollectionSize())
			{
				return pCollection->IsThisIDInCollection(nID);
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GetEffectMutexByCasterFlag(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetMutexByCasterFlag();
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsEffectsABMutexed(UNIT_EFFECT &rImpactA, UNIT_EFFECT &rImpactB)
{
	__GUARD__ if(GetEffectMutexID(rImpactA) != GetEffectMutexID(rImpactB))
	{
		return FALSE;
	}

	if(TRUE == GetEffectMutexByCasterFlag(rImpactA) && TRUE == GetEffectMutexByCasterFlag(rImpactB))
	{
		if
		(
			(rImpactA.GetCasterUniqueID() != rImpactB.GetCasterUniqueID())
		||	(rImpactA.IsCreateByPlayer() != rImpactB.IsCreateByPlayer())
		)
		{
			return FALSE;
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CanEffectAReplaceB(UNIT_EFFECT &rImpactA, UNIT_EFFECT &rImpactB)
{
	__GUARD__ if(FALSE == IsEffectsABMutexed(rImpactA, rImpactB))
	{
		return FALSE;
	}

	if
	(
		rImpactA.GetSkillID() == rImpactB.GetSkillID()
	&&	INVALID_ID != rImpactA.GetSkillID()
	&&	INVALID_ID != rImpactB.GetSkillID()
	)
	{
		if(GetEffectLevel(rImpactA) < GetEffectLevel(rImpactB))
		{
			return FALSE;
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 GetEffectPKRateCtr(UNIT_EFFECT &rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = GetEffectDataBlock(nDataIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		return pData->GetPKRateCtr();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}
