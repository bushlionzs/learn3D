/*$T MapServer/Server/Obj/Beastie/BeastieManager.cpp GC 1.140 10/10/07 10:07:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "BaseTool.h"
#include "map/game_map.h"
#include "gameobject/Beastie.h"
#include "ObjectManager.h"
#include "BeastieManager.h"
#include "map_manager.h"
#include "FileDef.h"
#include "gameobject/Behavior_Beastie.h"
#include "data/data_manager.h"
#include "Share/TAB/TabDefine_Map_Misc.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BeastieManager::BeastieManager(void)
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
BeastieManager::~BeastieManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Beastie *BeastieManager::GetBeastie(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Beastie *pBeastie = (Beastie *) (GetMap()->GetObjManager()->GetObj(idObj));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pBeastie == NULL)
	{
		return NULL;
	}

	if(pBeastie->GetObjType() != Object::OBJECT_CLASS_BEASTIE)
	{
		KCheck((pBeastie->GetObjType() == Object::OBJECT_CLASS_BEASTIE) && "BeastieManager::GetBeastie");
		return NULL;
	}

	return pBeastie;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BeastieManager::LoadBeastie(MapID_t mapId)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap		*pMap = GetMap();
	_OBJ_BEASTIE_INIT	beastieInit;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	_BEASTIE_DATA_TABLE* beastieTable = DataManager::GetSingletonPtr()->getBeastTable();
	for(int32 i = 0; i < beastieTable->m_uCount; ++i)
	{
		if(beastieTable->m_BeastieItem[i].m_nSceneId != mapId) continue;

		beastieInit.m_uBeastieId = beastieTable->m_BeastieItem[i].m_uBeastieId;
		strncpy
		(
			beastieInit.m_szName,
			beastieTable->m_BeastieItem[i].m_szName,
			sizeof(beastieInit.m_szName) - 1
		);
		beastieInit.m_Pos.m_fX = beastieTable->m_BeastieItem[i].m_PosX;
		beastieInit.m_Pos.m_fZ = beastieTable->m_BeastieItem[i].m_PosZ;
		beastieInit.m_nItemId = beastieTable->m_BeastieItem[i].m_nItemId;
		beastieInit.m_fSpeed = beastieTable->m_BeastieItem[i].m_fSpeed;
		beastieInit.m_nModelId = beastieTable->m_BeastieItem[i].m_nModelId;
		beastieInit.m_RespawnTime = beastieTable->m_BeastieItem[i].m_RespawnTime;
		beastieInit.m_Dir = beastieTable->m_BeastieItem[i].m_fDirection;
		beastieInit.m_nBeastieType = beastieTable->m_BeastieItem[i].m_nType;

		beastieInit.m_nCampId = 20;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Beastie *pBeastie = (Beastie *) (pMap->NewObject(Object::OBJECT_CLASS_BEASTIE));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pBeastie == NULL) break;
		pBeastie->Accept(&m_BeastieVisitor);
		pBeastie->Init(&beastieInit);
		pBeastie->SetActiveFlag(TRUE);

		beastieInit.Clear();
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load %s ...OK!", FILE_BEASTIE_ATTR);
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BeastieManager::RemoveAllBeastie(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap;
	Beastie		*pBeastie;
	uint32		i, uCount, uMaxCount, uLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();
	uCount = 0;
	uMaxCount = GetCount();
	uLength = GetLength();

	for(i = 0; i < uLength; i++)
	{
		pBeastie = (Beastie *) (GetObjByIndex(0));
		if(pBeastie != NULL)
		{
			pBeastie->SetActiveFlag(FALSE);
			pBeastie->Clear();
			pMap->DeleteObject(pBeastie);
			uCount++;
			if(uCount >= uMaxCount) break;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BeastieManager::RemoveBeastie(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMap)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pObj = pMap->GetBeastie(idObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pObj->GetObjType() == Object::OBJECT_CLASS_BEASTIE && "BeastieManager::RemoveBeastie error");
		if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_BEASTIE)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Beastie		*pBeastie = (Beastie *) pObj;
			Behavior_Beastie	*pAI = pBeastie->GetBeastieAI();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pAI->ChangeState(ESTATE_DEAD);
		}
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BeastieManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MAX_REMOVE_SIZE 1024
	int32	aNeedRemoveBeastie[MAX_REMOVE_SIZE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(aNeedRemoveBeastie, 0, sizeof(int32) * MAX_REMOVE_SIZE);

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRemoveCount = 0;
	int32	i;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < (int32) m_uCount; i++)
	{
		if(m_papObjs[i] != NULL)
		{
			_NET_TRY
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
						aNeedRemoveBeastie[nRemoveCount++] = i;
					}
				}
			}

			_NET_CATCH
			{
				QLOGGER_CODEHOLDER();
			}
		}
	}

	for(i = nRemoveCount - 1; i >= 0; i--)
	{
		_NET_TRY
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Beastie *pBeastie = (Beastie *) (m_papObjs[aNeedRemoveBeastie[i]]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pBeastie != NULL)
			{
				pBeastie->SetActiveFlag(FALSE);
				pBeastie->Clear();
				GetMap()->DeleteObject(pBeastie);
			}
		}

		_NET_CATCH
		{
			QLOGGER_CODEHOLDER();
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 BeastieManager::GetRand(int32 iMin, int32 iMax)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRand = ((float) (m_pMap->GetRand100()) / 100.0f);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return(int32) (iMin + ((float) (iMax - iMin) * fRand + 0.5f));

	__UNGUARD__ return iMin;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BeastieManager::ClearRemoveArray(int32 *aNeedRemovePet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(aNeedRemovePet, 0, sizeof(int32) * MAX_REMOVE_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BeastieManager::Clear()
{
	m_pMap = NULL;
}
