/*$T MapServer/Server/Obj/MonsterObjectManager.cpp GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "BaseTool.h"
#include "TAB.h"
#include "TabDefine.h"
#include "game_map.h"
#include "ObjectManager.h"
#include "gameobject/Monster.h"

#include "MonsterManager.h"
#include "map/map_manager.h"

#include "map/map_manager.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "map/map_info.h"
#include "gameobject/Pet.h"
#include "map/game_map.h"
#include "quest/quest_manager.h"
#include "data/data_manager.h"

//extern int32	g_CMDAlwaysLoadMonsterIni;

#define SECSIZE		64
#define DIR_STEP	(__PI / 18.f)

using namespace TAB;



SMonsterFile::~SMonsterFile()
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
void SMonsterFile::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_szFileName, 0, _MAX_PATH);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete_ARRAY(m_pInit);
	KSafeDelete_ARRAY(m_pAllocFlag);
	m_Count = 0;

	KSafeDelete_ARRAY(m_pInitUsing);
	m_CountUsing = 0;

	m_OperateCount = 0;
	KSafeDelete_ARRAY(m_pOperate);

	m_DataCount = 0;
	KSafeDelete_ARRAY(m_pData);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SMonsterFile::LoadData()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_pAllocFlag, 0, m_Count * sizeof(BOOL));
	int32		i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (i = 0; i < m_OperateCount; i++)
	{
		if (!LoadData_i(i)) return FALSE;
	}

	for (i = 0; i < m_Count; i++)
	{
		if (m_pAllocFlag[i] == TRUE) continue;

		m_pInitUsing[m_CountUsing] = m_pInit[i];
		m_CountUsing++;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SMonsterFile::LoadData_i(int32 iIndex)
{
	__GUARD__
#define MAX_MONSTER_FILE	512

		_INIT_MONSTER_OPT* pOperate = &(m_pOperate[iIndex]);
	if (pOperate->m_DataDef >= m_DataCount)
	{
		KCheckEx(FALSE, "数据定义范围超标");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_INIT_MONSTER_DATA* pData = &(m_pData[pOperate->m_DataDef]);
	int32			iSelectCount = 0;
	int32			aSelectMonsterIndex[MAX_MONSTER_FILE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(aSelectMonsterIndex, -1, sizeof(int32) * MAX_MONSTER_FILE);

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for (i = 0; i < m_Count; i++)
	{
		if (m_pAllocFlag[i] == TRUE)
		{
			continue;
		}

		switch (pOperate->m_SelectType)
		{
		case MONSTER_VALUE_GUID:
			if (pOperate->m_Value.m_GUID == m_pInit[i].m_GUID)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_TYPE:
			if (pOperate->m_Value.m_Type == m_pInit[i].m_uDataID)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_NAME:
			if (strcmp(pOperate->m_Value.m_Name, m_pInit[i].m_szName) == 0)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_POS:
			if
				(
					pOperate->m_Value.m_Pos.m_fX == m_pInit[i].m_Pos.m_fX
					&& pOperate->m_Value.m_Pos.m_fZ == m_pInit[i].m_Pos.m_fZ
					)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_SCRIPTID:
			if (pOperate->m_Value.m_ScriptID == m_pInit[i].m_idScript)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_GROUPID:
			if (pOperate->m_Value.m_GroupID == m_pInit[i].m_uGroupID)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_TEAMID:
			if (pOperate->m_Value.m_TeamID == m_pInit[i].m_uTeamID)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_BASEAI:
			if (pOperate->m_Value.m_BaseAI == m_pInit[i].m_BaseAI)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_AIFILE:
			if (pOperate->m_Value.m_AIFile == m_pInit[i].m_ExtAIScript)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		case MONSTER_VALUE_PATROLID:
			if (pOperate->m_Value.m_PatrolID == m_pInit[i].m_nPatrolID)
			{
				m_pAllocFlag[i] = TRUE;
				aSelectMonsterIndex[iSelectCount] = i;
				iSelectCount++;
			}
			break;

		default:
		{
			KCheck(FALSE);
		}
		break;
		}
	}

	if (pData->m_DataType == MONSTER_VALUE_TRAND || pData->m_DataType == MONSTER_VALUE_GRAND)
	{
		/*~~~~~~~~~~~~~~~~~~~*/
		uint32	uTotalRand = 0;
		uint32	i;
		/*~~~~~~~~~~~~~~~~~~~*/

		for (i = 0; i < (uint32)iSelectCount; i++)
		{
			if (pData->m_DataType == MONSTER_VALUE_TRAND)
			{
				uTotalRand += m_pInit[aSelectMonsterIndex[i]].m_uTeamID;
			}
			else if (pData->m_DataType == MONSTER_VALUE_GRAND)
			{
				uTotalRand += m_pInit[aSelectMonsterIndex[i]].m_uGroupID;
			}
		}

		uTotalRand == 0 ? uTotalRand = 1 : uTotalRand;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nCountMin = pOperate->m_MaxLeft > iSelectCount ? iSelectCount : pOperate->m_MaxLeft;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_CountUsing = 0;
		for (int32 j = 0; j < nCountMin; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			uint32	uRandH = rand();
			uint32	uRandL = rand();
			uint32	uRand = ((uRandH & 0xFFFF) * 0xFFFF + uRandL & 0xFFFF) % uTotalRand;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			m_pInitUsing[m_CountUsing].Clear();

			/*~~~~~~~~~~~~~~~~*/
			uint32	uTotalC = 0;
			/*~~~~~~~~~~~~~~~~*/

			for (i = 0; i < (uint32)iSelectCount; i++)
			{
				if (pData->m_DataType == MONSTER_VALUE_TRAND)
				{
					uTotalC += m_pInit[aSelectMonsterIndex[i]].m_uTeamID;
				}
				else if (pData->m_DataType == MONSTER_VALUE_GRAND)
				{
					uTotalC += m_pInit[aSelectMonsterIndex[i]].m_uGroupID;
				}

				if (uRand < uTotalC)
				{
					m_pInitUsing[m_CountUsing] = m_pInit[aSelectMonsterIndex[i]];
					break;
				}
			}

			m_CountUsing++;
		}
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	aDataIndex[MAX_MONSTER_FILE];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for (i = 0; i < MAX_MONSTER_FILE; i++)
		{
			if (i >= pData->m_DataCount)
				aDataIndex[i] = INVALID_INDEX;
			else
				aDataIndex[i] = i;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iMinCount = ((iSelectCount > pData->m_DataCount) ? (pData->m_DataCount) : (iSelectCount));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_CountUsing = 0;
		for (i = 0; i < iMinCount; i++)
		{
			m_pInitUsing[m_CountUsing].Clear();

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iCurSelect = rand() % iSelectCount;
			int32	iSelectRet = INVALID_INDEX;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for (int32 j = 0; j < iSelectCount; j++)
			{
				if (aSelectMonsterIndex[iCurSelect] != INVALID_INDEX)
				{
					iSelectRet = aSelectMonsterIndex[iCurSelect];
					aSelectMonsterIndex[iCurSelect] = INVALID_INDEX;
					break;
				}

				iCurSelect++;
				if (iCurSelect >= iSelectCount) iCurSelect = 0;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iCurData = rand() % pData->m_DataCount;
			int32	iDataRet = INVALID_INDEX;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for (int32 k = 0; k < pData->m_DataCount; k++)
			{
				if (aDataIndex[iCurData] != INVALID_INDEX)
				{
					iDataRet = aDataIndex[iCurData];
					aDataIndex[iCurData] = INVALID_INDEX;
					break;
				}

				iCurData++;
				if (iCurData >= pData->m_DataCount) iCurData = 0;
			}

			KCheck(iSelectRet != INVALID_INDEX && iDataRet != INVALID_INDEX);
			m_pInitUsing[m_CountUsing] = m_pInit[iSelectRet];
			switch (pData->m_DataType)
			{
			case MONSTER_VALUE_GUID:
				m_pInitUsing[m_CountUsing].m_GUID = pData->m_pDataValue[iDataRet].m_GUID;
				break;

			case MONSTER_VALUE_TYPE:
				m_pInitUsing[m_CountUsing].m_uDataID = pData->m_pDataValue[iDataRet].m_Type;
				break;

			case MONSTER_VALUE_NAME:
				strncpy
				(
					m_pInitUsing[m_CountUsing].m_szName,
					pData->m_pDataValue[iDataRet].m_Name,
					NPC_NAME_LEN
				);
				break;

			case MONSTER_VALUE_POS:
				m_pInitUsing[m_CountUsing].m_Pos.m_fX = pData->m_pDataValue[iDataRet].m_Pos.m_fX;
				m_pInitUsing[m_CountUsing].m_Pos.m_fZ = pData->m_pDataValue[iDataRet].m_Pos.m_fZ;
				break;

			case MONSTER_VALUE_SCRIPTID:
				m_pInitUsing[m_CountUsing].m_idScript = pData->m_pDataValue[iDataRet].m_ScriptID;
				break;

			case MONSTER_VALUE_GROUPID:
				m_pInitUsing[m_CountUsing].m_uGroupID = pData->m_pDataValue[iDataRet].m_GroupID;
				break;

			case MONSTER_VALUE_TEAMID:
				m_pInitUsing[m_CountUsing].m_uTeamID = pData->m_pDataValue[iDataRet].m_TeamID;
				break;

			case MONSTER_VALUE_BASEAI:
				m_pInitUsing[m_CountUsing].m_BaseAI = pData->m_pDataValue[iDataRet].m_BaseAI;
				break;

			case MONSTER_VALUE_AIFILE:
				m_pInitUsing[m_CountUsing].m_ExtAIScript = pData->m_pDataValue[iDataRet].m_AIFile;
				break;

			case MONSTER_VALUE_PATROLID:
				m_pInitUsing[m_CountUsing].m_nPatrolID = pData->m_pDataValue[iDataRet].m_PatrolID;
				break;

			default:
			{
				KCheck(FALSE);
			}
			break;
			};

			m_CountUsing++;
			if (m_CountUsing >= pOperate->m_MaxLeft) break;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

MonsterObjectManager::MonsterObjectManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MonsterObjectManager::~MonsterObjectManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Monster *MonsterObjectManager::GetMonster(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Monster	*pMonster = (Monster *) (GetMap()->GetObjManager()->GetObj(idObj));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster == NULL)
	{
		return NULL;
	}

	if(pMonster->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		KCheck((pMonster->GetObjType() == Object::OBJECT_CLASS_MONSTER) && "MonsterManager::GetMonster");
		return NULL;
	}

	return pMonster;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MonsterObjectManager::LoadMonsterTab(const char *pszFileName, MapID_t MapID)
{
	/*~~~~~~~~~~~~*/
     enum Monster_Tab
	{
		Monster_Tab_Index,
		Monster_Tab_Guid,
		Monster_Tab_Type,
		Monster_Tab_Obj_id,
		Monster_Tab_Camp_id,
		Monster_Tab_Name,
		Monster_Tab_Title,
		Monster_Tab_Pos_x,
		Monster_Tab_Pos_z,
		Monster_Tab_Dir,
		Monster_Tab_Script_id,
		Monster_Tab_Respawn_time,
		Monster_Tab_Group_id,
		Monster_Tab_Team_id,
		Monster_Tab_Base_ai,
		Monster_Tab_Ai_file,
		Monster_Tab_Patrol_id,
		Monster_Tab_Shop0,
		Monster_Tab_Shop1,
		Monster_Tab_Shop2,
		Monster_Tab_Shop3,
		Monster_Tab_ReputationID,
		Monster_Tab_Level,
	};
	/*~~~~~~~~~~~~*/

	GameMap *pMap = GetMap();
	int32 i;
	_INIT_MONSTER_OBJECT init;

	SMonsterFile *pMonsterFile = MapManager::GetSingletonPtr()->GetMonsterFile(pszFileName);
	if(pMonsterFile == NULL)
	{
		TABFile* monstertab = new TABFile(0);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		TABFile& ThirdFile = *monstertab;
		BOOL	ret = ThirdFile.OpenFromTXT(pszFileName);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(ret);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iTableCount = ThirdFile.GetRecordsNum();
		int32	iTableColumn = ThirdFile.GetFieldsNum();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(iTableColumn == 23);

		pMonsterFile = MapManager::GetSingletonPtr()->GetEmptyMonsterFile(pszFileName);
		KCheck(pMonsterFile);

		pMonsterFile->m_Count = iTableCount;
		if(!pMonsterFile->m_pInit) 
			pMonsterFile->m_pInit = new _INIT_MONSTER_OBJECT[iTableCount];

		if(!pMonsterFile->m_pAllocFlag) 
			pMonsterFile->m_pAllocFlag = new BOOL[iTableCount];

		if(!pMonsterFile->m_pInitUsing) 
			pMonsterFile->m_pInitUsing = new _INIT_MONSTER_OBJECT[iTableCount];

		for(i = 0; i < iTableCount; i++)
		{
			init.m_GUID = ThirdFile.Search_Posistion(i, Monster_Tab_Guid)->iValue;
			init.m_uDataID = ThirdFile.Search_Posistion(i, Monster_Tab_Type)->iValue;

			MonsterProperty* pExtAttr = DataManager::GetSingletonPtr()->getMonsterProperty(init.m_uDataID);
			if(pExtAttr == NULL)
			{
				continue;
			}

			strncpy
			(
				init.m_szName,
				ThirdFile.Search_Posistion(i, Monster_Tab_Name)->pString,
				sizeof(init.m_szName) - 1
			);
			strncpy
			(
				init.m_szTitle,
				ThirdFile.Search_Posistion(i, Monster_Tab_Title)->pString,
				sizeof(init.m_szTitle) - 1
			);

			init.m_Pos.m_fX = ThirdFile.Search_Posistion(i, Monster_Tab_Pos_x)->fValue;
			init.m_Pos.m_fZ = ThirdFile.Search_Posistion(i, Monster_Tab_Pos_z)->fValue;

			init.m_Dir = (float) ThirdFile.Search_Posistion(i, Monster_Tab_Dir)->iValue;
			init.m_Dir = (float) (init.m_Dir) * DIR_STEP + __HALF_PI;
			if(init.m_Dir > 2.f * __PI)
			{
				init.m_Dir -= 2.f * __PI;
			}

			init.m_ObjGUID = ThirdFile.Search_Posistion(i, Monster_Tab_Obj_id)->iValue;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(init.m_ObjGUID);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pQuest != NULL)
			{
				init.m_idScript = pQuest->m_ScriptID;
			}
			else
			{
				init.m_idScript = ThirdFile.Search_Posistion(i, Monster_Tab_Script_id)->iValue;
			}

			KCheck(init.m_idScript <= 0|| init.m_idScript > 100000 );

			init.m_RespawnTime = ThirdFile.Search_Posistion(i, Monster_Tab_Respawn_time)->iValue;

			init.m_uGroupID = ThirdFile.Search_Posistion(i, Monster_Tab_Group_id)->iValue;

			init.m_uTeamID = ThirdFile.Search_Posistion(i, Monster_Tab_Team_id)->iValue;

			init.m_BaseAI = ThirdFile.Search_Posistion(i, Monster_Tab_Base_ai)->iValue;

			init.m_BaseAI = ThirdFile.Search_Posistion(i, Monster_Tab_Base_ai)->iValue;
			if(init.m_BaseAI == -1) init.m_BaseAI = pExtAttr->m_BaseAI;

			init.m_ExtAIScript = ThirdFile.Search_Posistion(i, Monster_Tab_Ai_file)->iValue;
			if(init.m_ExtAIScript == -1) init.m_ExtAIScript = pExtAttr->m_ExtAI;

			init.m_nPatrolID = ThirdFile.Search_Posistion(i, Monster_Tab_Patrol_id)->iValue;

			init.m_nShop[0] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop0)->iValue;

			init.m_nShop[1] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop1)->iValue;

			init.m_nShop[2] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop2)->iValue;

			init.m_nShop[3] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop3)->iValue;

			init.m_nLevel = ThirdFile.Search_Posistion(i, Monster_Tab_Level)->iValue;

			init.m_LeaderID = -1;

			init.m_bPet = FALSE;

			init.m_CampID = ThirdFile.Search_Posistion(i, Monster_Tab_Camp_id)->iValue;

			pMap->GetMapInfo()->VerifyPos(&(init.m_Pos));

			pMonsterFile->m_pInit[i] = init;
		}

		strncpy(pMonsterFile->m_szFileName, pszFileName, _MAX_PATH - 1);
	}

	if(pMonsterFile->m_OperateCount > 0)
	{
		if(!pMonsterFile->LoadData())
		{
			KCheck(FALSE);
			return FALSE;
		}
	}
	else
	{
		pMonsterFile->m_CountUsing = pMonsterFile->m_Count;
		memcpy
		(
			pMonsterFile->m_pInitUsing,
			pMonsterFile->m_pInit,
			sizeof(_INIT_MONSTER_OBJECT) * pMonsterFile->m_Count
		);
	}

	for(i = 0; i < pMonsterFile->m_CountUsing; i++)
	{
		MonsterProperty* pExtAttr = DataManager::GetSingletonPtr()->getMonsterProperty(pMonsterFile->m_pInitUsing[i].m_uDataID);
		if(pExtAttr == NULL)
		{
			continue;
		}

		if(pMonsterFile->m_pInitUsing[i].m_bPet == TRUE)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Pet	*pPet = (Pet *) (pMap->NewObject(Object::OBJECT_CLASS_PET));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pPet == NULL) break;

			/*~~~~~~~~~~~~~~~~~~~~*/
			_INIT_PET_OBJECT	petinit;
			/*~~~~~~~~~~~~~~~~~~~~*/

			
			petinit.m_GUID = pMonsterFile->m_pInitUsing[i].m_GUID;
			petinit.m_Pos = pMonsterFile->m_pInitUsing[i].m_Pos;
			if(pMonsterFile->m_pInitUsing[i].m_szName[0] = '\0')
			{
				strncpy
				(
					petinit.m_PetDB.m_szName,
					pMonsterFile->m_pInitUsing[i].m_szName,
					sizeof(petinit.m_PetDB.m_szName) - 1
				);
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				MonsterProperty* pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(petinit.m_PetDB.m_nDataID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pAttr)
				{
					strncpy
					(
						petinit.m_PetDB.m_szName,
						pAttr->m_Name,
						sizeof(petinit.m_PetDB.m_szName) - 1
					);
				}
			}

			pPet->Init(&petinit);
			pPet->SetActiveFlag(TRUE);
		}
		else
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster *pMonster = (Monster *) (pMap->NewObject(Object::OBJECT_CLASS_MONSTER));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			pMonster->Accept(&m_MonsterVisitor);
			pMonster->Init(&(pMonsterFile->m_pInitUsing[i]), MapID);
			pMonster->SetActiveFlag(TRUE);
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MonsterObjectManager::LoadMonster(const char *pszFileName, MapID_t MapID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap		*pMap;
	_INIT_MONSTER_OBJECT	init;
	const MonsterProperty*pExtAttr;
	char			szSection[SECSIZE], szReadText[SECSIZE], szDebugString[1024];
	int32			i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SMonsterFile	*pMonsterFile = MapManager::GetSingletonPtr()->GetMonsterFile(pszFileName);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonsterFile == NULL)
	{
		pMonsterFile = MapManager::GetSingletonPtr()->GetEmptyMonsterFile(pszFileName);

		Configer	f(pszFileName);
		int32	iOperateCount = 0;
		BOOL	bRet = f.GetIntIfExist("setting", "operatecount", iOperateCount);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(bRet)
		{
			pMonsterFile->m_OperateCount = iOperateCount;

			/*~~~~~~~~~~~~~~~~~~~*/
			int32	iDataCount = 0;
			/*~~~~~~~~~~~~~~~~~~~*/

			bRet = f.GetIntIfExist("setting", "datacount", iDataCount);
			KCheck(bRet);
			pMonsterFile->m_DataCount = iDataCount;

			pMonsterFile->m_pOperate = new _INIT_MONSTER_OPT[iOperateCount];
			if(pMonsterFile->m_pOperate == NULL)
			{
				KCheck(FALSE);
				return FALSE;
			}

			pMonsterFile->m_pData = new _INIT_MONSTER_DATA[iDataCount];
			if(pMonsterFile->m_pData == NULL)
			{
				KCheck(FALSE);
				return FALSE;
			}

			for(i = 0; i < iOperateCount; i++)
			{
				sprintf(szSection, "operate%d", i);
				if(0 == f.GetText(szSection, "selecttype", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				pMonsterFile->m_pOperate[i].m_SelectType = (int32) atoi(szReadText);

				if(0 == f.GetText(szSection, "selectvalue", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				switch(pMonsterFile->m_pOperate[i].m_SelectType)
				{
				case MONSTER_VALUE_GUID:
					pMonsterFile->m_pOperate[i].m_Value.m_GUID = (GUID_t) atoi(szReadText);
					break;

				case MONSTER_VALUE_TYPE:
					pMonsterFile->m_pOperate[i].m_Value.m_Type = (int32) atoi(szReadText);
					break;

				case MONSTER_VALUE_NAME:
					strncpy(pMonsterFile->m_pOperate[i].m_Value.m_Name, szReadText, NPC_NAME_LEN);
					break;

				case MONSTER_VALUE_POS:
					pMonsterFile->m_pOperate[i].m_Value.m_Pos.m_fX = (float) atof(szReadText);
					pMonsterFile->m_pOperate[i].m_Value.m_Pos.m_fZ = (float) atof(szReadText);
					break;

				case MONSTER_VALUE_SCRIPTID:
					pMonsterFile->m_pOperate[i].m_Value.m_ScriptID = (ScriptID_t) atoi(szReadText);
					break;

				case MONSTER_VALUE_GROUPID:
					pMonsterFile->m_pOperate[i].m_Value.m_GroupID = (GroupID_t) atoi(szReadText);
					break;

				case MONSTER_VALUE_TEAMID:
					pMonsterFile->m_pOperate[i].m_Value.m_TeamID = (TeamID_t) atoi(szReadText);
					break;

				case MONSTER_VALUE_BASEAI:
					pMonsterFile->m_pOperate[i].m_Value.m_BaseAI = (int32) atoi(szReadText);
					break;

				case MONSTER_VALUE_AIFILE:
					pMonsterFile->m_pOperate[i].m_Value.m_AIFile = (int32) atoi(szReadText);
					break;

				case MONSTER_VALUE_PATROLID:
					pMonsterFile->m_pOperate[i].m_Value.m_PatrolID = (int32) atoi(szReadText);
					break;

				default:
					{
						KCheck(FALSE);
					}
					break;
				};
				if(0 == f.GetText(szSection, "data_def", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				pMonsterFile->m_pOperate[i].m_DataDef = (int32) atoi(szReadText);

				if(0 == f.GetText(szSection, "maxleft", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				pMonsterFile->m_pOperate[i].m_MaxLeft = (int32) atoi(szReadText);
			}

			for(i = 0; i < iDataCount; i++)
			{
				sprintf(szSection, "data_def%d", i);
				if(0 == f.GetText(szSection, "datatype", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				pMonsterFile->m_pData[i].m_DataType = (int32) atoi(szReadText);

				if(0 == f.GetText(szSection, "count", szReadText, sizeof(szReadText)))
				{
					KCheck(FALSE);
					continue;
				}

				pMonsterFile->m_pData[i].m_DataCount = (int32) atoi(szReadText);
				pMonsterFile->m_pData[i].m_pDataValue = new SMonsterAttrValue[pMonsterFile->m_pData[i].m_DataCount];
				if(pMonsterFile->m_pData[i].m_pDataValue == NULL)
				{
					KCheck(FALSE);
					continue;
				}

				for(int32 j = 0; j < pMonsterFile->m_pData[i].m_DataCount; j++)
				{
					/*~~~~~~~~~~~~~~~~*/
					char	szValue[64];
					/*~~~~~~~~~~~~~~~~*/

					sprintf(szValue, "value%d", j);
					if(0 == f.GetText(szSection, szValue, szReadText, sizeof(szReadText)))
					{
						KCheck(FALSE);
						continue;
					}

					switch(pMonsterFile->m_pData[i].m_DataType)
					{
					case MONSTER_VALUE_GUID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_GUID = (GUID_t) atoi(szReadText);
						break;

					case MONSTER_VALUE_TYPE:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_Type = (int32) atoi(szReadText);
						break;

					case MONSTER_VALUE_NAME:
						strncpy
						(
							pMonsterFile->m_pData[i].m_pDataValue[j].m_Name,
							szReadText,
							NPC_NAME_LEN
						);
						break;

					case MONSTER_VALUE_POS:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_Pos.m_fX = (float) atof(szReadText);
						sprintf(szValue, "valueex%d", j);
						if(0 == f.GetText(szSection, szValue, szReadText, sizeof(szReadText)))
						{
							KCheck(FALSE);
							break;
						}

						pMonsterFile->m_pData[i].m_pDataValue[j].m_Pos.m_fZ = (float) atof(szReadText);
						break;

					case MONSTER_VALUE_SCRIPTID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_ScriptID = (ScriptID_t) atoi(szReadText);
						break;

					case MONSTER_VALUE_GRAND:
					case MONSTER_VALUE_GROUPID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_GroupID = (GroupID_t) atoi(szReadText);
						break;

					case MONSTER_VALUE_TRAND:
					case MONSTER_VALUE_TEAMID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_TeamID = (TeamID_t) atoi(szReadText);
						break;

					case MONSTER_VALUE_BASEAI:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_BaseAI = (int32) atoi(szReadText);
						break;

					case MONSTER_VALUE_AIFILE:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_AIFile = (int32) atoi(szReadText);
						break;

					case MONSTER_VALUE_PATROLID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_PatrolID = (int32) atoi(szReadText);
						break;

					default:
						{
							KCheck(FALSE);
						}
						break;
					};
				}
			}
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iMonsterCount = f.Get_Property_Int("info", "monstercount");
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pMonsterFile->m_Count = iMonsterCount;

		strncpy(pMonsterFile->m_szFileName, pszFileName, _MAX_PATH - 1);

		pMonsterFile->m_pInit = new _INIT_MONSTER_OBJECT[iMonsterCount];
		KCheck(pMonsterFile->m_pInit);
		if(pMonsterFile->m_pInit == NULL) return FALSE;

		pMonsterFile->m_pAllocFlag = new BOOL[iMonsterCount];
		KCheck(pMonsterFile->m_pAllocFlag);
		if(pMonsterFile->m_pAllocFlag == NULL) return FALSE;

		pMonsterFile->m_pInitUsing = new _INIT_MONSTER_OBJECT[iMonsterCount];
		KCheck(pMonsterFile->m_pInitUsing);
		if(pMonsterFile->m_pInitUsing == NULL) return FALSE;

		for(i = 0; i < iMonsterCount; i++)
		{
			sprintf(szSection, "monster%d", i);
			if(0 == f.GetText(szSection, "guid", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"guid"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_GUID = (GUID_t) (atoi(szReadText));

			if(0 == f.GetText(szSection, "type", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"type"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_uDataID = atoi(szReadText);

			pExtAttr = DataManager::GetSingletonPtr()->getMonsterProperty(init.m_uDataID);
			if(pExtAttr == NULL)
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find attrib, pszFileName=<%s>,section=<%s>,type=<%s>",
					pszFileName,
					szSection,
					"type"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);

				continue;
			}

			if(f.GetTextIfExist(szSection, "name", szReadText, sizeof(szReadText)))
				strncpy(init.m_szName, szReadText, sizeof(init.m_szName) - 1);
			else
				init.m_szName[0] = '\0';

			if(f.GetTextIfExist(szSection, "title", szReadText, sizeof(szReadText)))
				strncpy(init.m_szTitle, szReadText, sizeof(init.m_szTitle) - 1);
			else
				init.m_szTitle[0] = '\0';

			if(0 == f.GetText(szSection, "pos_x", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"pos_x"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_Pos.m_fX = (float) atof(szReadText);

			if(0 == f.GetText(szSection, "pos_z", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"pos_z"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_Pos.m_fZ = (float) atof(szReadText);

			if(0 == f.GetText(szSection, "dir", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"dir"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_Dir = (float) (atoi(szReadText)) * DIR_STEP + __HALF_PI;
			if(init.m_Dir > 2.f * __PI)
			{
				init.m_Dir -= 2.f * __PI;
			}

			if(0 != f.GetTextIfExist(szSection, "obj_id", szReadText, sizeof(szReadText)))
			{
				init.m_ObjGUID = atoi(szReadText);
			}
			else
			{
				init.m_ObjGUID = INVALID_ID;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			NPC_QUEST	*pQuest = DataManager::GetSingletonPtr()->getNpcQuest(init.m_ObjGUID);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pQuest != NULL)
			{
				init.m_idScript = pQuest->m_ScriptID;
			}
			else
			{
				init.m_idScript = -1;
			}

			if(0 == f.GetText(szSection, "respawn_time", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"respawn_time"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_RespawnTime = (int32) (atoi(szReadText));

			if(0 == f.GetText(szSection, "group_id", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"group_id"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_uGroupID = (uint32) (atoi(szReadText));

			if(0 == f.GetText(szSection, "team_id", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"team_id"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_uTeamID = (uint32) (atoi(szReadText));

			if(f.GetTextIfExist(szSection, "base_ai", szReadText, sizeof(szReadText)))
			{
				init.m_BaseAI = atoi(szReadText);
				KCheck(init.m_BaseAI < g_MonsterBehaviorTab.m_Count);
			}
			else
			{
				init.m_BaseAI = pExtAttr->m_BaseAI;
				KCheck(init.m_BaseAI < g_MonsterBehaviorTab.m_Count);
			}

			if(f.GetTextIfExist(szSection, "ai_file", szReadText, sizeof(szReadText)))
			{
				init.m_ExtAIScript = atoi(szReadText);
			}
			else
			{
				init.m_ExtAIScript = pExtAttr->m_ExtAI;
			}

			if(0 == f.GetText(szSection, "patrol_id", szReadText, sizeof(szReadText)))
			{
				sprintf
				(
					szDebugString,
					"LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>",
					pszFileName,
					szSection,
					"patrol_id"
				);
				QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szDebugString);
				KCheck(FALSE);
				continue;
			}

			init.m_nPatrolID = atoi(szReadText);

			if(0 != f.GetTextIfExist(szSection, "shop0", szReadText, sizeof(szReadText)))
			{
				init.m_nShop[0] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[0] = -1;
			}

			if(0 != f.GetTextIfExist(szSection, "shop1", szReadText, sizeof(szReadText)))
			{
				init.m_nShop[1] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[1] = -1;
			}

			if(0 != f.GetTextIfExist(szSection, "shop2", szReadText, sizeof(szReadText)))
			{
				init.m_nShop[2] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[2] = -1;
			}

			if(0 != f.GetTextIfExist(szSection, "shop3", szReadText, sizeof(szReadText)))
			{
				init.m_nShop[3] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[3] = -1;
			}

			if(0 != f.GetTextIfExist(szSection, "leaderid", szReadText, sizeof(szReadText)))
			{
				init.m_LeaderID = atoi(szReadText);
			}
			else
			{
				init.m_LeaderID = -1;
			}

			if(0 != f.GetTextIfExist(szSection, "ispet", szReadText, sizeof(szReadText)))
			{
				init.m_bPet = atoi(szReadText);
			}
			else
			{
				init.m_bPet = FALSE;
			}

			if(0 != f.GetTextIfExist(szSection, "camp_id", szReadText, sizeof(szReadText)))
			{
				init.m_CampID = atoi(szReadText);
			}
			else
			{
				init.m_CampID = INVALID_CAMP;
			}

			pMap->GetMapInfo()->VerifyPos(&(init.m_Pos));

			pMonsterFile->m_pInit[i] = init;
		}

	}

	if(pMonsterFile->m_OperateCount > 0)
	{
		if(!pMonsterFile->LoadData())
		{
			KCheck(FALSE);
			return FALSE;
		}
	}
	else
	{
		pMonsterFile->m_CountUsing = pMonsterFile->m_Count;
		memcpy
		(
			pMonsterFile->m_pInitUsing,
			pMonsterFile->m_pInit,
			sizeof(_INIT_MONSTER_OBJECT) * pMonsterFile->m_Count
		);
	}

	for(i = 0; i < pMonsterFile->m_CountUsing; i++)
	{
		pExtAttr = DataManager::GetSingletonPtr()->getMonsterProperty(pMonsterFile->m_pInitUsing[i].m_uDataID);
		if(pExtAttr == NULL)
		{
			continue;
		}

		if(pMonsterFile->m_pInitUsing[i].m_bPet == TRUE)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Pet	*pPet = (Pet *) (pMap->NewObject(Object::OBJECT_CLASS_PET));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pPet == NULL) break;

			/*~~~~~~~~~~~~~~~~~~~~*/
			_INIT_PET_OBJECT	petinit;
			/*~~~~~~~~~~~~~~~~~~~~*/

			
			petinit.m_GUID = pMonsterFile->m_pInitUsing[i].m_GUID;
			petinit.m_Pos = pMonsterFile->m_pInitUsing[i].m_Pos;
			if(pMonsterFile->m_pInitUsing[i].m_szName[0] = '\0')
			{
				strncpy
				(
					petinit.m_PetDB.m_szName,
					pMonsterFile->m_pInitUsing[i].m_szName,
					sizeof(petinit.m_PetDB.m_szName) - 1
				);
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				MonsterProperty*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(petinit.m_PetDB.m_nDataID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pAttr)
				{
					strncpy
					(
						petinit.m_PetDB.m_szName,
						pAttr->m_Name,
						sizeof(petinit.m_PetDB.m_szName) - 1
					);
				}
			}

			pPet->Init(&petinit);
			pPet->SetActiveFlag(TRUE);
		}
		else
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster *pMonster = (Monster *) (pMap->NewObject(Object::OBJECT_CLASS_MONSTER));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pMonster == NULL) break;

			pMonster->SetActiveFlag(TRUE);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MonsterObjectManager::RemoveAllMonster(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap;
	Monster		*pMonster;
	uint32		i, uCount, uMaxCount, uLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();
	uCount = 0;
	uMaxCount = GetCount();
	uLength = GetLength();

	for(i = 0; i < uLength; i++)
	{
		pMonster = (Monster *) (GetObjByIndex(0));
		if(pMonster != NULL)
		{
			pMonster->SetActiveFlag(FALSE);
			pMonster->Clear();
			pMap->DeleteObject(pMonster);
			uCount++;
			if(uCount >= uMaxCount)
			{
				break;
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
BOOL MonsterObjectManager::HeartBeat(uint32 uTime)
{
	__GUARD__

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MAX_REMOVE_SIZE 1024
	int32	aNeedRemoveMonster[MAX_REMOVE_SIZE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(aNeedRemoveMonster, 0, sizeof(int32) * MAX_REMOVE_SIZE);

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
					aNeedRemoveMonster[nRemoveCount++] = i;
				}
			}

		}
	}

	for(i = nRemoveCount - 1; i >= 0; i--)
	{
		_NET_TRY
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster *pMonster = (Monster *) (m_papObjs[aNeedRemoveMonster[i]]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pMonster != NULL)
			{
				pMonster->SetActiveFlag(FALSE);
				pMonster->Clear();
				GetMap()->DeleteObject(pMonster);
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
ObjID_t MonsterObjectManager::FindMonsterByGUID(GUID_t guid)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	for(i = 0; i < (int32) m_uCount; i++)
	{
		if(m_papObjs[i] != NULL)
		{
			if(m_papObjs[i]->IsActiveObj())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Monster *pMonster = (Monster *) (m_papObjs[i]);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pMonster->GetGUID() == guid)
				{
					return pMonster->GetID();
				}
			}
		}
	}

	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MonsterObjectManager::InitMonsterData(_MONSTER_INIT *pInit, int32 nDataID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(FALSE && "MonsterManager::InitMonsterData");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pInit == NULL || nDataID == INVALID_ID) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MonsterProperty*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAttr == NULL) return FALSE;

	return TRUE;

	__UNGUARD__ return FALSE;
}
