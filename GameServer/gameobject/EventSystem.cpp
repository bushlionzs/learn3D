/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	EventSystem.cpp
			file path:	F:\khan2\src\MapServer\Server\GameLogic
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	并不是真正的事件处理机制 而是事件的集中处理类
**********************************************************************************************/


#include "stdafx.h"
#include "TypeDefine.h"
#include "EventSystem.h"
#include "map/game_map.h"
#include "skill/Spell_EffectLogicManager.h"
#include "StructSpell.h"


using namespace Messages;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL EventSystem::Init(GameMap *pMap)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		m_pMap = pMap;
		m_EventQueue.Init(512);
		m_ImpactQueue.Init(256);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void EventSystem::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pMap = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nCountOfEvents = 0;
	m_nCountOfImpacts = 0;
	m_nMaxCountOfEvent = 0;
	m_nMaxCountOfImpacts = 0;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void EventSystem::HeartBeat(Time_t nDeltaTime)
{
	__GUARD__ if(NULL == m_pMap)
	{
		return;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EventSystem::GetIndexOfFirstAvailableEventSlot(void)
{
	__GUARD__ return -1;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 EventSystem::GetIndexOfFirstAvailableImpactSlot(void)
{
	__GUARD__ return -1;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ResizeAllVector(void)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EventSystem::RegisterImpactEvent
(
	ObjID_t		nReceiver,
	ObjID_t		nSender,
	UNIT_EFFECT	&rImp,
	Time_t		nDelayTime,
	SpellID_t	nSkillID
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	&rMap = *m_pMap;
	Character	*pReceiver = NULL;
	Character	*pSender = NULL;
	Object		*pObj = rMap.GetSpecificObjByID(nReceiver);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pReceiver = static_cast<Character *>(pObj);
		}
	}

	pObj = rMap.GetSpecificObjByID(nSender);
	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pSender = static_cast<Character *>(pObj);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EffectLogic const	*pLogic = GetEffectLogic(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pLogic)
	{
		return FALSE;
	}

	if(NULL != pSender)
	{
		rImp.SetCasterObjID(pSender->GetID());
		rImp.SetCasterUniqueID(pSender->GetUniqueID());

		if(Object::OBJECT_CLASS_PLAYER == pSender->GetObjType())
		{
			rImp.MarkCreateByPlayerFlag();
		}

		rImp.SetCasterLogicCount(pSender->GetLogicCount());
		if(INVALID_ID != nSkillID)
		{
			pSender->RefixEffect(rImp);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SpellTargetingAndDepletingParams	&rParams = pSender->GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rParams.SetHurtDelayTime(nDelayTime);
	}

	if(NULL != pReceiver && NULL != pSender)
	{
		if
		(
			(TRUE == pReceiver->IsUnbreakable() && BEHAVIOR_TYPE_HOSTILITY == GetEffectStandFlag(rImp))
		||	pReceiver->IsImmuneAbsForLater()
		)
		{
		}
		else
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nRet = pReceiver->OnEvent_FiltrateEffect(rImp);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(CombatMissFlag::FLAG_NORMAL != nRet)
			{
				
			}
			else
			{
				return pReceiver->Effect_RegisterEffect(rImp);
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
BOOL EventSystem::RegisterBeSkillEvent(ObjID_t nReceiver, ObjID_t nSender, int32 nBehaviorType, Time_t nDelayTime)
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EventSystem::RegisterSkillMissEvent(ObjID_t nReceiver, ObjID_t nSender, SpellID_t nSkill, Time_t nDelayTime, int32 nFlag)
{
	__GUARD__ if(NULL == m_pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap		&rMap = *m_pMap;
	Object		*pObj = rMap.GetSpecificObjByID(nReceiver);
	Character	*pReceiver = NULL;
	Character	*pSender = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pReceiver = static_cast<Character *>(pObj);
		}
	}

	pObj = rMap.GetSpecificObjByID(nSender);
	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pSender = static_cast<Character *>(pObj);
		}
	}

	if(NULL == pSender || NULL == pReceiver)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	iHurtDelayTime = nDelayTime;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDelayTime < 0)
	{
		iHurtDelayTime = 0;
	}
	else if(nDelayTime > 3000)
	{
		iHurtDelayTime = 3000;
	}

	if(iHurtDelayTime <= 50)
	{
		SendDelayTimeMissMSG(nReceiver, nSender, nSkill, pSender->GetLogicCount(), nFlag);

		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_SkillMissMSGDelayTime	oMissDelaytime;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oMissDelaytime.m_nDelayTime = iHurtDelayTime;
	oMissDelaytime.m_nLogicCount = pSender->GetLogicCount();
	oMissDelaytime.m_nSender = nSender;
	oMissDelaytime.m_nSkill = nSkill;
	oMissDelaytime.m_nFlag = nFlag;
	pReceiver->AddDelayTimeSkillMissList(oMissDelaytime);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void EventSystem::SendDelayTimeMissMSG(ObjID_t nReceiver, ObjID_t nSender, SpellID_t nSkill, int32 iLogicCount, int32 nFlag)
{
	__GUARD__ if(NULL == m_pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap		&rMap = *m_pMap;
	Object		*pObj = rMap.GetSpecificObjByID(nReceiver);
	Character	*pReceiver = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pReceiver = static_cast<Character *>(pObj);
		}
	}

	
	return;
	__UNGUARD__ return;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EventSystem::RegisterSkillHitEvent(ObjID_t nReceiver, ObjID_t nSender, SpellID_t nSkill, Time_t nDelayTime)
{
	__GUARD__ if(NULL == m_pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap		&rMap = *m_pMap;
	Object		*pObj = rMap.GetSpecificObjByID(nReceiver);
	Character	*pReceiver = NULL;
	Character	*pSender = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()) && TRUE == pObj->IsActiveObj())
		{
			pReceiver = static_cast<Character *>(pObj);
		}
	}

	pObj = rMap.GetSpecificObjByID(nSender);
	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()))
		{
			pSender = static_cast<Character *>(pObj);
		}
	}

	if(NULL != pReceiver && NULL != pSender && TRUE == pObj->IsActiveObj())
	{
		if(TRUE == pReceiver->IsActiveObj() && TRUE == pSender->IsActiveObj())
		{
			pReceiver->OnEvent_BeHit(*pSender);

			pSender->OnEvent_HitTarget(*pReceiver);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL EventSystem::RegisterActiveSpecialObjEvent(ObjID_t nSpecialObj, Time_t nDelayTime)
{
	__GUARD__ if(NULL == m_pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap		&rMap = *m_pMap;
	Object		*pObj = rMap.GetSpecificObjByID(nSpecialObj);
	Character	*pSpecialobj = NULL;
	Character	*pSender = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjSpecial(pObj->GetObjType()) && FALSE == pObj->IsActiveObj())
		{
			pSpecialobj = static_cast<Character *>(pObj);
		}
	}

	if(NULL != pSpecialobj)
	{
		pSpecialobj->SetActiveFlag(TRUE);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}
