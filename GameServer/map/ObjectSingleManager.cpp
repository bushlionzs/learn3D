/*$T MapServer/Server/Obj/ObjectSingleManager.cpp GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "gameobject/Object.h"

#include "ObjectSingleManager.h"
#include "BaseTool.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ObjectSingleManager::ObjectSingleManager(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_papObjs = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uCount = 0;
	m_uLength = 0;
	m_uLogicInterval = 0;
	m_uCurrentLogicInterval = 0;

	m_pMap = NULL;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ObjectSingleManager::~ObjectSingleManager(void)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Term();
	/*~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_papObjs == NULL && "ObjSingleManager::~ObjectSingleManager m_papObjs not free");

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectSingleManager::Init(const _INIT_SINGLEMANAGER_OBJECT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_papObjs == NULL && "ObjSingleManager::Init m_papObjs not free");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pInit == NULL)
	{
		KCheck(pInit != NULL && "ObjSingleManager::Init");
		return FALSE;
	}

	if(pInit->m_uLength == 0)
	{
		KCheck(pInit->m_uLength > 0 && "ObjSingleManager::Init");
		return FALSE;
	}

	if(pInit->m_pMap == NULL)
	{
		KCheck(pInit->m_pMap != NULL && "ObjSingleManager::Init");
		return FALSE;
	}

	m_uCount = 0;
	m_uLength = pInit->m_uLength;
	m_papObjs = new Object *[m_uLength];
	memset(m_papObjs, 0, sizeof(Object *) * m_uLength);

	m_uLogicInterval = pInit->m_uLogicInterval;
	m_uCurrentLogicInterval = pInit->m_uLogicInterval;

	m_pMap = pInit->m_pMap;
	m_LogicTimer.BeginTimer(pInit->m_uLogicInterval, pInit->m_uCurrentTime);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ObjectSingleManager::Term(void)
{
	__GUARD__ if(m_papObjs)
	{
		KSafeDelete_ARRAY(m_papObjs);
		m_papObjs = NULL;
	}

	m_uCount = 0;
	m_uLength = 0;

	m_uLogicInterval = 0;
	m_uCurrentLogicInterval = 0;

	m_pMap = NULL;
	m_LogicTimer.Clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ObjectSingleManager::Reset()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_uCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(m_papObjs, 0, sizeof(Object *) * m_uLength);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ObjectSingleManager::SetLoadFactor(float fFactor)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_uCurrentLogicInterval = (uint32) ((float) (m_uLogicInterval) * fFactor);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_LogicTimer.SetTermTime(m_uCurrentLogicInterval);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectSingleManager::HeartBeat(uint32 uTime)
{
	__GUARD__ 

	/*~~~~~~~~~~~~*/
	uint32	i;
	BOOL	bResult;
	/*~~~~~~~~~~~~*/

	for(i = 0; i < m_uCount; i++)
	{
		if(m_papObjs[i] != NULL)
		{
	
			{
				if(m_papObjs[i]->IsActiveObj())
				{
					bResult = m_papObjs[i]->HeartBeat(uTime);
				}
				else
				{
					bResult = m_papObjs[i]->HeartBeat_OutMap(uTime);
				}
			}


		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectSingleManager::Add(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(pObj != NULL && "ObjSingleManager::Add");
		return FALSE;
	}

	if(m_uCount >= m_uLength)
	{
		/*~~~~~~~~~~~~~*/
		uint32	uNewSize;
		/*~~~~~~~~~~~~~*/

		uNewSize = m_uLength * 2;

		if (uNewSize == 0)
		{
			uNewSize = 100;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bResult = Resize(uNewSize);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!bResult)
		{
			KCheck(m_uCount < m_uLength && "ObjSingleManager::Add resize error");
			return FALSE;
		}
	}

	m_papObjs[m_uCount] = pObj;
	pObj->SetSingleMgrIndex(m_uCount);
	m_uCount++;
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectSingleManager::Remove(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(pObj != NULL && "ObjSingleManager::Remove");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uIndex = pObj->GetSingleMgrIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(uIndex >= m_uCount)
	{
		KCheck(uIndex < m_uCount && "ObjSingleManager::Remove");
		return FALSE;
	}

	m_uCount--;
	m_papObjs[m_uCount]->SetSingleMgrIndex(uIndex);
	m_papObjs[uIndex] = m_papObjs[m_uCount];
	m_papObjs[m_uCount] = NULL;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectSingleManager::Resize(uint32 uSize)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	**papSave = m_papObjs;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_papObjs = new Object *[uSize];
	if(papSave != NULL)
	{
		memcpy(m_papObjs, papSave, sizeof(Object *) * m_uCount);
	}

	memset(&(m_papObjs[m_uCount]), 0, sizeof(Object *) * (uSize - m_uCount));
	m_uLength = uSize;

	KSafeDelete_ARRAY(papSave);
	papSave = NULL;
	return TRUE;

	__UNGUARD__ return FALSE;
}
