/*$T MapServer/Server/Obj/SpecialObjectManager.cpp GC 1.140 10/10/07 10:07:35 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "BaseTool.h"
#include "Map.h"
#include "ObjectManager.h"
#include "Trap.h"
#include "ObjPoolDefine.h"

#include "TrapManager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

SpecialObjectManager::SpecialObjectManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpecialObjectManager::~SpecialObjectManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpecialCreature *SpecialObjectManager::GetSpecial(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpecialCreature	*pSpecial = (SpecialCreature *) (GetMap()->GetObjManager()->GetObj(idObj));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSpecial == NULL)
	{
		return NULL;
	}

	if(pSpecial->GetObjType() != Object::OBJECT_CLASS_SPECIAL)
	{
		KCheck((pSpecial->GetObjType() == Object::OBJECT_CLASS_SPECIAL) && "SpecialManager::GetSpecial");
		return NULL;
	}

	return pSpecial;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialObjectManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MAX_REMOVE_SIZE 1024
	int32	aNeedRemoveSpecial[MAX_REMOVE_SIZE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(aNeedRemoveSpecial, 0, sizeof(int32) * MAX_REMOVE_SIZE);

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRemoveCount = 0;
	int32	i;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < (int32) m_uCount; i++)
	{
		if(m_papObjs[i] != NULL)
		{
			if(m_papObjs[i]->IsActiveObj())
			{
				m_papObjs[i]->HeartBeat(uTime);
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	bRet = m_papObjs[i]->HeartBeat_OutMap(uTime);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(bRet == FALSE)
				{
					aNeedRemoveSpecial[nRemoveCount++] = i;
				}
			}
		}
	}

	for(i = nRemoveCount - 1; i >= 0; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SpecialCreature *pSpecial = (SpecialCreature *) (m_papObjs[aNeedRemoveSpecial[i]]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pSpecial != NULL)
		{
			pSpecial->SetActiveFlag(FALSE);
			pSpecial->Clear();
			GetMap()->DeleteObject(pSpecial);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpecialObjectManager::RemoveAllSpecial()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Map	*pMap;
	SpecialCreature *pSpecial;
	uint32		i, uCount, uMaxCount, uLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();
	uCount = 0;
	uMaxCount = GetCount();
	uLength = GetLength();

	for(i = 0; i < uLength; i++)
	{
		pSpecial = (SpecialCreature *) (GetObjByIndex(0));
		if(pSpecial != NULL)
		{
			pSpecial->SetActiveFlag(FALSE);
			pSpecial->Clear();
			pMap->DeleteObject(pSpecial);
			uCount++;
			if(uCount >= uMaxCount) break;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}
