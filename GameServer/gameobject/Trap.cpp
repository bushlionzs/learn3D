/*$T MapServer/Server/Obj/Special.cpp GC 1.140 10/10/07 10:07:35 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "map/game_map.h"
//#include "XCNewSpecial.h"
#include "Trap.h"
#include "Struct.h"
#include "TabDefine.h"
#include "skill/Spell_TrapObjLogic.h"
#include "skill/Spell_EffectLogicManager.h"
#include "data/data_manager.h"



/*
 =======================================================================================================================
 =======================================================================================================================
 */

SpecialCreature::SpecialCreature(void)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpecialCreature::~SpecialCreature(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialCreature::Init(const _INIT_OBJECT *pInit)
{
	__GUARD__ if(NULL == pInit)
	{
		return FALSE;
	}

	if(!Creature::Init(pInit)) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_INIT_SPECIAL_OBJECT const *pIniter = (_INIT_SPECIAL_OBJECT const *) pInit;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nDataID = pIniter->m_nDataID;
	m_nOwner = pIniter->m_nOwnerID;

	if(INVALID_ID == m_nDataID)
	{
		return FALSE;
	}

	return InitFromData();
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Creature::	Clear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nContinuance = 0;
	m_nInterval = 0;
	m_nElapsedInterval = 0;
	m_nDelayTime = 0;
	m_nOwner = INVALID_ID;
	m_nPowerRefixByValue = 0;
	m_nPowerRefixByRate = 0;
	m_nDataID = INVALID_ID;
	m_nStealthLevel = 0;
	m_bFadeOut = false;
	m_nActiveTimes = 0;
	m_nClass = INVALID_ID;
	memset((void *) m_aParams, 0, sizeof(m_aParams));

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialCreature::InitFromData()
{
	__GUARD__ if(INVALID_ID == m_nDataID)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialObjData_T const	*pData = DataManager::GetSingletonPtr()->getSpecialObjectDataById(m_nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialObjectLogic const *pLogic = ObjSpecial_GetLogic(*this);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nContinuance = pData->GetContinuance();
	m_nInterval = pData->GetInterval();
	m_bFadeOut = false;
	m_nActiveTimes = pData->GetActiveTimes();
	m_nClass = pLogic->GetType();
	m_nStealthLevel = pData->GetStealthLevel();

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpecialCreature::GetParamByIndex(int32 nIdx) const
{
	__GUARD__ if(0 > nIdx || NUM_OF_PARAMS <= nIdx)
	{
		KCheckEx(NULL, "[SpecialCreature::GetParamByIndex(int32 nIdx)]: nIdx out of range!!");
		return -1;
	}

	return m_aParams[nIdx];
	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::SetParamByIndex(int32 nIdx, int32 nParam)
{
	__GUARD__ if(0 > nIdx || NUM_OF_PARAMS <= nIdx)
	{
		KCheckEx(NULL, "[SpecialCreature::GetParamByIndex(int32 nIdx)]: nIdx out of range!!");
	}
	else
	{
		m_aParams[nIdx] = nParam;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool SpecialCreature::HeartBeat(uint32 uTime)
{
	__GUARD__ if(FALSE == Creature::HeartBeat(uTime))
	{
		return FALSE;
	}

	if(TRUE == m_bFadeOut)
	{
		SetActiveFlag(FALSE);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Time_t	nDeltaTime = GetLogicTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < m_nInterval)
	{
		nDeltaTime > m_nContinuance ? nDeltaTime = m_nContinuance : NULL;
		m_nElapsedInterval += nDeltaTime;
		while(m_nElapsedInterval >= m_nInterval)
		{
			OnEvent_Tick();
			m_nElapsedInterval -= m_nInterval;
		}
	}

	if(0 < m_nContinuance)
	{
		if(0 < m_nContinuance)
		{
			m_nContinuance -= nDeltaTime;
		}

		if(0 >= m_nContinuance)
		{
			OnEvent_TimeOver();
			m_bFadeOut = TRUE;
			m_nContinuance = 0;
		}
	}
	else
	{
		m_bFadeOut = TRUE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialCreature::HeartBeat_OutMap(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = Creature::HeartBeat_OutMap(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return bResult;
	}

	if(TRUE == IsFadeOut())
	{
		return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialCreature::IsCanViewMe(const Object *pObj)
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::OnEvent_Tick(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjectLogic const	*pLogic = ObjSpecial_GetLogic(*this);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pLogic)
	{
		pLogic->OnEvent_Tick(*this);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::OnEvent_TimeOver(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjectLogic const	*pLogic = ObjSpecial_GetLogic(*this);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pLogic)
	{
		pLogic->OnEvent_TimeOver(*this);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
NetPacket*SpecialCreature::CreateNewObjMsg(void)
{
	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::DestroyNewObjMsg(IMessage *pPacket)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::OnEvent_Trigger(ObjID_List const &rTargetList)
{
	__GUARD__ if(GetMap() != NULL)
	{
		
	}
	else
	{
		KCheckEx(FALSE, "[SpecialCreature::OnTrigger]: GetMap() return NULL!!");
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpecialCreature::OnEvent_FadeOut(void)
{
	__GUARD__ if(GetMap() != NULL)
	{
		
	}
	else
	{
		KCheckEx(FALSE, "[SpecialCreature::OnFadeOut]: GetMap() return NULL!!");
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpecialObjData_T const *SpecialCreature::GetDataRecord(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialObjData_T const	*pData = DataManager::GetSingletonPtr()->getSpecialObjectDataById(m_nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		KCheckEx(FALSE, "[TrapLogic_T::FadeOutNow]: Can not find data record!");
	}

	return pData;
	__UNGUARD__ return NULL;
}
