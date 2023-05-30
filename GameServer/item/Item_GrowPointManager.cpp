/*$T MapServer/Server/Item/GatherPointManager.cpp GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_GrowPointManager.h"
#include "map/game_map.h"
#include "BaseTool.h"
#include "TabDefine.h"
#include "TAB.h"
#include "map/map_manager.h"
#include "map/map_info.h"
#include "server_manager.h"
#include "data/data_manager.h"
#include "Share/TAB/TabDefine_Map_Misc.h"

enum MapGatherPointsSetup { TBSType, TBCount, TBControlFunc, TBInterval, };
enum MapGatherPointsData { TBIndex, TBType, TBXPosition, TBYPosition };

/*
=======================================================================================================================
=======================================================================================================================
*/

int32 Compare_GatherPoint(const void *pArg1, const void *pArg2)
{
	__GUARD__ if(pArg1 == NULL || pArg2 == NULL) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	v1 = ((GATHER_POINT_GROUPMAP_SETTING *) pArg1)->m_GatherPointRandValue;
	int32	v2 = ((GATHER_POINT_GROUPMAP_SETTING *) pArg2)->m_GatherPointRandValue;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(v1 > v2) return 1;
	if(v2 > v1)
		return -1;
	else
		return 0;

	__UNGUARD__ return 0;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
void GatherPointManager::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pLuaSystem = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_OwnerCount = 0;
	m_GatherPointCount = 0;
	m_GatherPointTypeCount = 0;

	for(int32 i = 0; i < MAX_MAP_GATHER_POINT_NUM; i++)
	{
		if(m_GatherPointMgr[i]) KSafeDelete(m_GatherPointMgr[i]);
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "UnLoad GatherPointManager...Ok!");

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TypeGatherPointManager::RandSort()
{
	__GUARD__ if(m_TypeCount > 1)
	{
		qsort(m_pData, m_TypeCount, sizeof(GATHER_POINT_GROUPMAP_SETTING), Compare_GatherPoint);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TypeGatherPointManager::SetObjID(ObjID_t id, float x, float y)
{
	__GUARD__ for(int i = 0; i < m_TypeCount; i++)
	{
		if((fabs(m_pData[i].m_GatherPointX - x) < 0.01f) && (fabs(m_pData[i].m_GatherPointY - y) < 0.01f))
		{
			m_pObjID[i] = id;
			return;
		}
	}

	__UNGUARD__
}

TypeGatherPointManager::TypeGatherPointManager()
{
	m_pData = NULL;
	m_pObjID = NULL;
	m_AddOffSet = 0;
	m_TypeCount = 0;
	m_TypeOffSet = 0;
	m_IntervalPerSeed = 0;
	m_CurrentElapse = 0;
	m_bStartCount = FALSE;
	m_LastUpdateTime = 0;
	m_CurrentCount = 0;
	m_MaxApperaCount = 0;
	m_bEnable = FALSE;
	m_IsCreateAll = FALSE;
}

TypeGatherPointManager::~TypeGatherPointManager()
{
	if(m_pData) KSafeDelete_ARRAY(m_pData);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::Load(char *strGatherPointData, char *strGatherPointSetup)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	BOOL		bRet;
	GATHER_POINT_FILE	*pGrowpointFile = MapManager::GetSingletonPtr()->GetGatherpointFile(strGatherPointData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGrowpointFile == NULL)
	{
		pGrowpointFile = MapManager::GetSingletonPtr()->GetEmptyGatherpointFile();
		if(pGrowpointFile == NULL)
		{
			KCheck(FALSE);
			return FALSE;
		}

		pGrowpointFile->m_pGrowpoint = new GATHER_POINT_LOAD;
		KCheckEx
		(
			NULL != pGrowpointFile->m_pGrowpoint,
			"[GatherPointManager::Load] Allocate memory failed(pGrowpointFile->m_pGrowpoint)!!"
		);
		pGrowpointFile->m_Count = 1;

		bRet = Load(pGrowpointFile->m_pGrowpoint, strGatherPointData, strGatherPointSetup);
		if(bRet == FALSE)
		{
			{
				QLogSystem::SLOW_LOG
					(
						SLOW_LOG_SERVER,
						"scene load growpoint data is null,sceneid = %d",
						GetMap()->MapID()
					);
			}
		}

		strncpy(pGrowpointFile->m_szFileName, strGatherPointData, _MAX_PATH - 1);
	}

	bRet = Load(pGrowpointFile->m_pGrowpoint);
	if(!bRet)
	{
		return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::Load(GATHER_POINT_LOAD *pGPLoad, char *strGatherPointData, char *strGatherPointSetup)
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum MapGatherPointsData { TBIndex, TBType, TBXPosition, TBYPosition, TBTypeEnum, TBSeedNum, TBContainerInterval, };
	/*~~~~~~~~~~~~*/

	KCheck(pGPLoad);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(strGatherPointData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!ret) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pGPLoad->m_DataCount = iTableCount;
	pGPLoad->m_pData = new GATHER_POINT_GROUPMAP_SETTING[iTableCount];
	KCheckEx(NULL != pGPLoad->m_pData, "[GatherPointManager::Load] Allocate memory failed(pGPLoad->m_pData)!!");

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCurrentTypeOffSet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < pGPLoad->m_DataCount; i++)
	{
		pGPLoad->m_pData[i].m_GatherPointType = ThirdFile.Search_Posistion(i, TBType)->iValue;
		pGPLoad->m_pData[i].m_GatherPointX = ThirdFile.Search_Posistion(i, TBXPosition)->fValue;
		pGPLoad->m_pData[i].m_GatherPointY = ThirdFile.Search_Posistion(i, TBYPosition)->fValue;

		if(iTableColumn < TBTypeEnum + 1)
		{
			pGPLoad->m_pData[i].m_GatherPointTypeEnum = GATHER_POINT_TYPE_NORMAL;
			pGPLoad->m_pData[i].SeedNum = INVALID_ID;
		}
		else
		{
			pGPLoad->m_pData[i].m_GatherPointTypeEnum = ThirdFile.Search_Posistion(i, TBTypeEnum)->iValue;
			if(pGPLoad->m_pData[i].m_GatherPointTypeEnum == GATHER_POINT_TYPE_NORMAL)
			{
				pGPLoad->m_pData[i].SeedNum = INVALID_ID;
			}
			else
			{
				KCheckEx
				(
					pGPLoad->m_pData[i].m_GatherPointTypeEnum < GATHER_POINT_TYPE_NUM,
					"生长点类型枚举值超出范围"
				);
				pGPLoad->m_pData[i].SeedNum = ThirdFile.Search_Posistion(i, TBSeedNum)->iValue;
				KCheckEx(pGPLoad->m_pData[i].SeedNum >= 0, "集合式生长点种子数不得小于0");
				pGPLoad->m_pData[i].SeedInterval = ThirdFile.Search_Posistion
					(
						i,
						TBContainerInterval
					)->iValue;
			}
		}

		pGPLoad->m_pData[i].m_GatherPointRandValue = rand();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		GLPos	GpPos;
		MapInfo		*pMapInfo = GetMap()->GetMapInfo();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pMapInfo);
		GpPos.m_fX = pGPLoad->m_pData[i].m_GatherPointX;
		GpPos.m_fZ = pGPLoad->m_pData[i].m_GatherPointY;

		if(GpPos.m_fX < 0 || GpPos.m_fX > pMapInfo->CX() || GpPos.m_fZ < 0 || GpPos.m_fZ > pMapInfo->CZ())
		{
			QLogSystem::SLOW_LOG
				(
					SLOW_LOG_SERVER,
					"Scene GatherPoint out of Range: x = %.3f z = %.3f",
					GpPos.m_fX,
					GpPos.m_fZ
				);
			pMapInfo->VerifyPos(&GpPos);
			pGPLoad->m_pData->m_GatherPointX = GpPos.m_fX;
			pGPLoad->m_pData->m_GatherPointY = GpPos.m_fZ;
		}
	}

	TABFile ThirdFile1(0);

	ret = ThirdFile1.OpenFromTXT(strGatherPointSetup);

	iTableCount = ThirdFile1.GetRecordsNum();
	iTableColumn = ThirdFile1.GetFieldsNum();
	if(!ret)
	{
		return FALSE;
	}

	KCheck(pGPLoad->m_DataCount >= iTableCount);

	pGPLoad->m_SetupCount = iTableCount;

	if(iTableCount == 0) return FALSE;

	pGPLoad->m_pSetup = new GATHER_POINT_GROUP_MAP_SETUP[iTableCount];
	KCheckEx(NULL != pGPLoad->m_pSetup, "[GatherPointManager::Load] Allocate memory failed(pGPLoad->m_pSetup)!!");

	KCheck(iTableCount > 0);
	for(int32 i = 0; i < pGPLoad->m_SetupCount; i++)
	{
		pGPLoad->m_pSetup[i].m_GatherPointType = ThirdFile1.Search_Posistion(i, TBSType)->iValue;
		pGPLoad->m_pSetup[i].m_GatherPointMaxCount = ThirdFile1.Search_Posistion(i, TBCount)->iValue;
		pGPLoad->m_pSetup[i].m_GatherPointInterval = ThirdFile1.Search_Posistion(i, TBInterval)->iValue;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::Load(GATHER_POINT_LOAD *pGPLoad)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pGPLoad);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_GatherPointCount = pGPLoad->m_DataCount;

	if(m_GatherPointCount == 0) return FALSE;

	KCheck(m_GatherPointCount > 0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCurrentTypeOffSet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_GatherPointCount; i++)
	{
		pGPLoad->m_pData[i].m_GatherPointRandValue = rand();

		KCheck
		(
			pGPLoad->m_pData[i].m_GatherPointX > 0.f
			&&	pGPLoad->m_pData[i].m_GatherPointX < m_pMap->GetMapInfo()->CX()
		);
		KCheck
		(
			pGPLoad->m_pData[i].m_GatherPointY > 0.f
			&&	pGPLoad->m_pData[i].m_GatherPointY < m_pMap->GetMapInfo()->CZ()
		);

		if(m_GatherPointMgr[iCurrentTypeOffSet])
		{
			if(m_GatherPointMgr[iCurrentTypeOffSet]->GetGatherPointType() == pGPLoad->m_pData[i].m_GatherPointType)
			{
			}
			else
			{
				iCurrentTypeOffSet++;
				m_GatherPointMgr[iCurrentTypeOffSet] = new TypeGatherPointManager();
				m_GatherPointMgr[iCurrentTypeOffSet]->SetGatherPointType(pGPLoad->m_pData[i].m_GatherPointType);
			}
		}
		else
		{
			m_GatherPointMgr[iCurrentTypeOffSet] = new TypeGatherPointManager();
			m_GatherPointMgr[iCurrentTypeOffSet]->SetGatherPointType(pGPLoad->m_pData[i].m_GatherPointType);
		}

		m_GatherPointMgr[iCurrentTypeOffSet]->IncCount();
	}

	iCurrentTypeOffSet = 0;

	for(int32 i = 0; i < m_GatherPointCount; i++)
	{
		if(m_GatherPointMgr[iCurrentTypeOffSet])
		{
			if(m_GatherPointMgr[iCurrentTypeOffSet]->GetGatherPointType() == pGPLoad->m_pData[i].m_GatherPointType)
			{
			}
			else
			{
				iCurrentTypeOffSet++;
			}

			m_GatherPointMgr[iCurrentTypeOffSet]->AddData(pGPLoad->m_pData[i]);
		}
	}

	m_GatherPointTypeCount = iCurrentTypeOffSet + 1;

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load GatherPoint  Data...Ok!");

	KCheck(m_GatherPointTypeCount >= pGPLoad->m_SetupCount);

	if(pGPLoad->m_SetupCount == 0) return FALSE;

	KCheck(pGPLoad->m_SetupCount > 0);

	for(int32 i = 0; i < m_GatherPointTypeCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32			GatherPointType = pGPLoad->m_pSetup[i].m_GatherPointType;
		TypeGatherPointManager	*pTypeGPManager = GetGpManagerByGatherPointType(GatherPointType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pTypeGPManager);
		pTypeGPManager->m_CurrentCount = 0;
		pTypeGPManager->m_MaxApperaCount = pGPLoad->m_pSetup[i].m_GatherPointMaxCount;

		if(pTypeGPManager->m_MaxApperaCount > pTypeGPManager->m_TypeCount)
		{
			/*~~~~~~~~~~~~~~~~~~*/
			char	ErrorMsg[255];
			/*~~~~~~~~~~~~~~~~~~*/

			sprintf
			(
				ErrorMsg,
				"场景中配置生长点位置的数量小于需求同时出现的数量,场景号为%d",
				m_pMap->MapID()
			);
			KCheckEx(FALSE, ErrorMsg);
			pTypeGPManager->m_MaxApperaCount = pTypeGPManager->m_TypeCount;
		}

		pTypeGPManager->m_bEnable = TRUE;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_GATHER_POINT_INFO	*pInfo = DataManager::GetSingletonPtr()->getGatherPointTable()->Get(GatherPointType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pInfo);

		pTypeGPManager->m_ScriptID = pInfo->m_ScriptID;
		KCheck(pTypeGPManager->m_ScriptID ==INVALID_ID || pTypeGPManager->m_ScriptID>100000);

		pTypeGPManager->m_IntervalPerSeed = pGPLoad->m_pSetup[i].m_GatherPointInterval;
		pTypeGPManager->RandSort();
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load GatherPoint Setup ...Ok!");

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float x = 0.0f, y = 0.0f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 iGatherPointIndex = 0; iGatherPointIndex < m_GatherPointTypeCount; iGatherPointIndex++)
	{
		if(m_GatherPointMgr[iGatherPointIndex] && m_GatherPointMgr[iGatherPointIndex]->DoTicks(uTime))
		{
			_NET_TRY
			{
				if(m_GatherPointMgr[iGatherPointIndex]->m_IsCreateAll == TRUE)
				{
					m_GatherPointMgr[iGatherPointIndex]->m_IsCreateAll = FALSE;

					for(int32 i = 0; i < m_GatherPointMgr[iGatherPointIndex]->m_TypeCount; i++)
					{
						if(m_GatherPointMgr[iGatherPointIndex]->m_pData[i].Used == FALSE)
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							BOOL	bRet = m_GatherPointMgr[iGatherPointIndex]->
								CreateGatherPointPos(x, y);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(	bRet &&	m_GatherPointMgr[iGatherPointIndex]->m_pData[i].m_GatherPointTypeEnum == GATHER_POINT_TYPE_MASS )
							{
								if(	!CallLUACreateFunc(m_GatherPointMgr[iGatherPointIndex]->m_ScriptID,x,y,m_GatherPointMgr[iGatherPointIndex]->m_GatherPointType,m_pMap->MapID())	)
								{
									KCheckEx(FALSE, "创建生长点返回失败");
									m_GatherPointMgr[iGatherPointIndex]->ReleaseGatherPointPos(x, y);
								}
							}
						}
					}

					continue;
				}

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	bRet = m_GatherPointMgr[iGatherPointIndex]->CreateGatherPointPos(x, y);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(bRet)
				{
					if(m_GatherPointMgr[iGatherPointIndex]->m_ScriptID > 0)
					{
						if ( !CallLUACreateFunc(m_GatherPointMgr[iGatherPointIndex]->m_ScriptID,x,y,m_GatherPointMgr[iGatherPointIndex]->m_GatherPointType,m_pMap->MapID()) )
						{
							KCheckEx(FALSE, "创建生长点返回失败");
							m_GatherPointMgr[iGatherPointIndex]->ReleaseGatherPointPos(x, y);
						}
						else
						{
						}
					}
					else
					{
						QLogSystem::SLOW_LOG
							(
								SLOW_LOG_SERVER,
								"GatherPointManager...No ScriptID %d !",
								iGatherPointIndex
							);
					}
				}
			}

			_NET_CATCH
			{
				QLOGGER_CODEHOLDER();
			}
		}

		if(m_GatherPointMgr[iGatherPointIndex])
		{
			m_GatherPointMgr[iGatherPointIndex]->DoSeedTicks(uTime);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::DecGatherPointTypeCount(int32 GatherPointType, float x, float y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TypeGatherPointManager	*pGpManager = GetGpManagerByGatherPointType(GatherPointType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGpManager)
	{
		return pGpManager->ReleaseGatherPointPos(x, y);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::GatherPointDataInit(char *strGatherPointData)
{
	__GUARD__ 

	TABFile ThirdFile(0);

	BOOL ret = ThirdFile.OpenFromTXT(strGatherPointData);

	int32 iTableCount = ThirdFile.GetRecordsNum();
	int32 iTableColumn = ThirdFile.GetFieldsNum();

	if(!ret)
	{
		iTableCount = 0;
		iTableColumn = 0;
	}

	m_GatherPointCount = iTableCount;

	if(iTableCount == 0) return FALSE;

	KCheck(iTableCount > 0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GATHER_POINT_GROUPMAP_SETTING	*pData;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pData = new GATHER_POINT_GROUPMAP_SETTING[m_GatherPointCount];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCurrentTypeOffSet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_GatherPointCount; i++)
	{
		pData[i].m_GatherPointType = ThirdFile.Search_Posistion(i, TBType)->iValue;
		pData[i].m_GatherPointX = ThirdFile.Search_Posistion(i, TBXPosition)->fValue;
		pData[i].m_GatherPointY = ThirdFile.Search_Posistion(i, TBYPosition)->fValue;
		pData[i].m_GatherPointRandValue = rand();

		if(m_GatherPointMgr[iCurrentTypeOffSet])
		{
			if(m_GatherPointMgr[iCurrentTypeOffSet]->GetGatherPointType() == pData[i].m_GatherPointType)
			{
			}
			else
			{
				iCurrentTypeOffSet++;
				m_GatherPointMgr[iCurrentTypeOffSet] = new TypeGatherPointManager();
				m_GatherPointMgr[iCurrentTypeOffSet]->SetGatherPointType(pData[i].m_GatherPointType);
			}
		}
		else
		{
			m_GatherPointMgr[iCurrentTypeOffSet] = new TypeGatherPointManager();
			m_GatherPointMgr[iCurrentTypeOffSet]->SetGatherPointType(pData[i].m_GatherPointType);
		}

		m_GatherPointMgr[iCurrentTypeOffSet]->IncCount();
	}

	iCurrentTypeOffSet = 0;

	for(int32 i = 0; i < m_GatherPointCount; i++)
	{
		if(m_GatherPointMgr[iCurrentTypeOffSet])
		{
			if(m_GatherPointMgr[iCurrentTypeOffSet]->GetGatherPointType() == pData[i].m_GatherPointType)
			{
			}
			else
			{
				iCurrentTypeOffSet++;
			}

			m_GatherPointMgr[iCurrentTypeOffSet]->AddData(pData[i]);
		}
	}

	KSafeDelete_ARRAY(pData);

	m_GatherPointTypeCount = iCurrentTypeOffSet + 1;

	return TRUE;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::GatherPointSetupInit(char *strGatherPointSetup)
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum MapGatherPointsSetup { TBType, TBCount, TBControlFunc, TBInterval, };
	/*~~~~~~~~~~~~*/

	TABFile ThirdFile(0);

	BOOL ret = ThirdFile.OpenFromTXT(strGatherPointSetup);

	int32 iTableCount = ThirdFile.GetRecordsNum();
	int32 iTableColumn = ThirdFile.GetFieldsNum();

	if(!ret)
	{
		iTableCount = 0;
		iTableColumn = 0;
	}

	KCheck(m_GatherPointTypeCount >= iTableCount);

	if(iTableCount == 0) return FALSE;

	KCheck(iTableCount > 0);

	for(int32 i = 0; i < m_GatherPointTypeCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32			GatherPointType = ThirdFile.Search_Posistion(i, TBType)->iValue;
		TypeGatherPointManager	*pTypeGPManager = GetGpManagerByGatherPointType(GatherPointType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pTypeGPManager);
		pTypeGPManager->m_CurrentCount = 0;
		pTypeGPManager->m_MaxApperaCount = ThirdFile.Search_Posistion(i, TBCount)->iValue;

		if(pTypeGPManager->m_MaxApperaCount > pTypeGPManager->m_TypeCount)
		{
			/*~~~~~~~~~~~~~~~~~~*/
			char	ErrorMsg[255];
			/*~~~~~~~~~~~~~~~~~~*/

			sprintf
			(
				ErrorMsg,
				"场景中配置生长点位置的数量小于需求同时出现的数量,场景号为%d",
				m_pMap->MapID()
			);
			KCheckEx(FALSE, ErrorMsg);
			pTypeGPManager->m_MaxApperaCount = pTypeGPManager->m_TypeCount;
		}

		pTypeGPManager->m_bEnable = TRUE;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_GATHER_POINT_INFO	*pInfo = DataManager::GetSingletonPtr()->getGatherPointTable()->Get(GatherPointType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pInfo);

		pTypeGPManager->m_ScriptID = pInfo->m_ScriptID;

		pTypeGPManager->m_IntervalPerSeed = ThirdFile.Search_Posistion(i, TBInterval)->iValue;

		pTypeGPManager->RandSort();
	}

	return TRUE;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherPointManager::CallLUACreateFunc(ScriptID_t FileID, float x, float y, int32 iItemBoxType, MapID_t mapId)
{
	__GUARD__ m_pLuaSystem->RunScriptFunction(mapId,FileID, "OnCreate", mapId, iItemBoxType, x, y);
	return TRUE;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GatherPointManager::CallLUAOpenBoxFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID)
{
	__GUARD__ return m_pLuaSystem->RunScriptFunction
		(
			MapID,
			FileID,
			"OnOpen",
			(int32) MapID,
			(int32) SelfId,
			(int32) TargetId
		);

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GatherPointManager::CallLUARecycleFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID)
{
	__GUARD__ return m_pLuaSystem->RunScriptFunction
		(
			MapID,
			FileID,
			"OnRecycle",
			(int32) MapID,
			(int32) SelfId,
			(int32) TargetId
		);

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GatherPointManager::CallLUAProcOverFunc(ScriptID_t FileID, ObjID_t SelfId, ObjID_t TargetId, MapID_t MapID)
{
	__GUARD__ return m_pLuaSystem->RunScriptFunction
		(
			MapID,
			FileID,
			"OnProcOver",
			(int32) MapID,
			(int32) SelfId,
			(int32) TargetId
		);

	__UNGUARD__ return -1;
}

BOOL GatherPointManager::DelGatherPointOwner( ObjID_t OwnerID )
{
	if(OwnerID == INVALID_ID) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bNewOwner = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_OwnerCount; i++)
	{
		if(m_GPOwner[i].OwnerID == OwnerID)
		{
			m_GPOwner[i].OwnerCount--;
			bNewOwner = FALSE;
			if(m_GPOwner[i].OwnerCount == 0)
			{
				m_GPOwner[i].OwnerID = INVALID_ID;
				m_OwnerCount--;
			}
		}
	}

	if(bNewOwner)
	{
		return FALSE;
	}

	return TRUE;
}

int32 GatherPointManager::GetGatherPointCountByOwner( ObjID_t OwnerID )
{
	if(OwnerID == INVALID_ID) return -1;

	for(int32 i = 0; i < m_OwnerCount; i++)
	{
		if(m_GPOwner[i].OwnerID == OwnerID)
		{
			return m_GPOwner[i].OwnerCount;
		}
	}

	return -1;
}

BOOL GatherPointManager::AddGatherPointOwner( ObjID_t OwnerID )
{
	if(OwnerID == INVALID_ID) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bNewOwner = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_OwnerCount; i++)
	{
		if(m_GPOwner[i].OwnerID == OwnerID)
		{
			m_GPOwner[i].OwnerCount++;
			bNewOwner = FALSE;
		}
	}

	if(bNewOwner)
	{
		m_GPOwner[m_OwnerCount].OwnerID = OwnerID;
		m_GPOwner[m_OwnerCount].OwnerCount = 1;
	}

	return TRUE;
}

GatherPointManager::GatherPointManager()
{
	memset(m_GatherPointMgr, 0, sizeof(TypeGatherPointManager *) * MAX_MAP_GATHER_POINT_NUM);
	m_pLuaSystem = 0;
	m_OwnerCount = 0;
	m_GatherPointCount = 0;
	m_GatherPointTypeCount = 0;
}

GatherPointManager::~GatherPointManager()
{
	m_pLuaSystem = 0;
	m_OwnerCount = 0;
	m_GatherPointCount = 0;
	m_GatherPointTypeCount = 0;

	for(int32 i = 0; i < MAX_MAP_GATHER_POINT_NUM; i++)
	{
		if(m_GatherPointMgr[i]) KSafeDelete(m_GatherPointMgr[i]);
	}
}

inline	BOOL	TypeGatherPointManager::CreateGatherPointPos(float& x,float& y)
{

	if(m_CurrentCount>=m_MaxApperaCount)
		return FALSE;

	for(int32 i = 0;i<m_MaxApperaCount;i++)
	{
		if(!m_pData[m_TypeOffSet].Used)
		{	
			x = m_pData[m_TypeOffSet].m_GatherPointX;
			y = m_pData[m_TypeOffSet].m_GatherPointY;

			m_pData[m_TypeOffSet].Used	 = TRUE;
			IncCurrentCount();

			if ( m_pData[m_TypeOffSet].m_GatherPointTypeEnum == GATHER_POINT_TYPE_MASS )
			{
				m_pData[m_TypeOffSet].CurrSeedCount = m_pData[m_TypeOffSet].SeedNum;
			}

			m_TypeOffSet++;
			if(m_TypeOffSet==m_TypeCount)
			{
				m_TypeOffSet = 0;
			}
			return TRUE;
		}
		else
		{
			m_TypeOffSet++;
			if(m_TypeOffSet==m_TypeCount)
			{
				m_TypeOffSet = 0;
			}
		}
	}

	return FALSE;



}

inline BOOL	TypeGatherPointManager::ReleaseGatherPointPos(float x,float y)
{
	__GUARD__

		for(int32 i=0;i<m_TypeCount;i++)
		{
			if((fabs(m_pData[i].m_GatherPointX-x)<0.01f)
				&& (fabs(m_pData[i].m_GatherPointY-y)<0.01f))
			{
				if ( m_pData[i].m_GatherPointTypeEnum == GATHER_POINT_TYPE_NORMAL )
				{
					m_pData[i].Used = FALSE;
					m_pObjID[i] = INVALID_ID;
					DecCurrentCount();
					return TRUE;
				}
				else if ( m_pData[i].m_GatherPointTypeEnum == GATHER_POINT_TYPE_MASS )
				{





					DecCurrentSeedCount(i);
					if ( m_pData[i].CurrSeedCount <= 0 )
					{
						m_pData[i].Used = FALSE;
						m_pData[i].CurrSeedCount= 0;
						m_pObjID[i] = INVALID_ID;
						DecCurrentCount();
						return TRUE;
					}

					return FALSE;
				}	
				else
				{
					KCheckEx(FALSE,"TypeGrowPointManager::ReleaseGrowPointPos……，生长点类型错误");
				}

			}
		}

		return FALSE;
		__UNGUARD__
			return TRUE;	
}


inline	BOOL		TypeGatherPointManager::DoTicks(uint32 uTime)
{


	if(!m_bEnable)
		return FALSE;

	if(m_bStartCount)
	{
		if(m_CurrentCount==m_MaxApperaCount)
		{
			m_bStartCount = FALSE;
			m_CurrentElapse = 0;
		}
		else
		{
			m_CurrentElapse=m_CurrentElapse+ (uTime -m_LastUpdateTime);
			m_LastUpdateTime =uTime;
		}
	}
	else
	{
		if(m_CurrentCount<m_MaxApperaCount)
		{
			m_bStartCount		=	TRUE;
			m_LastUpdateTime	=	uTime;
			m_CurrentElapse		=	0;
		}

		return FALSE;
	}

	if(m_CurrentElapse>m_IntervalPerSeed)
	{

		m_CurrentElapse = 0;
		return TRUE;
	}
	return FALSE;
}


inline	BOOL		TypeGatherPointManager::DoSeedTicks(uint32 uTime)
{
	if(!m_bEnable)
		return FALSE;


	for(int32 i=0;i<m_TypeCount;i++)
	{
		if ( m_pData[i].Used == TRUE && m_pData[i].m_GatherPointTypeEnum == GATHER_POINT_TYPE_MASS  )
		{
			if ( m_pData[i].IsStartCount )
			{
				if ( m_pData[i].CurrSeedCount == m_pData[i].SeedNum )
				{
					m_pData[i].IsStartCount = FALSE;
					m_pData[i].CurrentElapse = 0;
				}
				else
				{
					m_pData[i].CurrentElapse	= m_pData[i].CurrentElapse + (uTime - m_pData[i].LastUpdateTime);
					m_pData[i].LastUpdateTime = uTime;
				}
			}
			else
			{
				if ( m_pData[i].CurrSeedCount < m_pData[i].SeedNum )
				{
					m_pData[i].IsStartCount		= TRUE;
					m_pData[i].LastUpdateTime	= uTime;
					m_pData[i].CurrentElapse	= 0;
				}

				continue;
			}

			if ( m_pData[i].CurrentElapse > m_pData[i].SeedInterval )
			{
				m_pData[i].CurrentElapse = 0;

				IncCurrentSeedCount(i);
				continue;
			}
		}

	}

	return FALSE;
}

inline	TypeGatherPointManager*		GatherPointManager::GetGpManagerByGatherPointType(int32 GrowPointType)
{
	for(int32 i =0;i<m_GatherPointTypeCount;i++)
	{
		if(m_GatherPointMgr[i])
		{
			if(m_GatherPointMgr[i]->GetGatherPointType()== GrowPointType)
			{
				return m_GatherPointMgr[i];
			}
		}
		else
			return NULL;
	}
	return NULL;
}
