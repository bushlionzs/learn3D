/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	RegionManager.cpp
			file path:	F:\khan2\src\MapServer\Server\Map
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	��������� ��ȡ�����ļ�������Щ����ע�ᵽ��Ӧ��Map��
			�Դ�Ϊ������Ķ�����\Server\map\city_dadu\city_dadu_area.ini��
			��ν���������һ������ �������������������ȷ��һ���������� ÿһ��������԰�һ���ű�
			��Character�������� ����ýű�����OnEnterArea
			��Character�뿪���� ����ýű�����OnLeaveArea
			��Characterͣ���������� ����Ҳ���������� ����ýű�����OnOnTimer
**********************************************************************************************/

#include "stdafx.h"
#include "BaseTool.h"
#include "map/game_map.h"
#include "RegionManager.h"
#include "map/map_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

RegionManager::RegionManager(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_uAreaCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
RegionManager::~RegionManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL RegionManager::Init(MapManager* pMapManager, const char *pszPathName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ REGION_FILE	*pAreaFile = pMapManager->GetAreaFile(pszPathName);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAreaFile == NULL)
	{
		pAreaFile = pMapManager->GetEmptyAreaFile();
		if(pAreaFile == NULL)
		{
			KCheck(FALSE);
			return FALSE;
		}

		BOOL	bResult;
		Configer	iniArea;

		bResult = iniArea.Open(pszPathName);
		if(!bResult)
		{
			QLogSystem::SLOW_LOG
				(
					SLOW_LOG_SERVER,
					" RegionManager::Init can not open file;<filename=%s>",
					pszPathName
				);
			return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szSection[128], szValue[128];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 != iniArea.GetTextIfExist("area_info", "area_count", szValue, sizeof(szValue)))
		{
			pAreaFile->m_Count = (uint32) (atoi(szValue));
			m_uAreaCount = pAreaFile->m_Count;
			if(m_uAreaCount > 0)
			{
				pAreaFile->m_pArea = new Region[pAreaFile->m_Count];
				if(pAreaFile->m_pArea == NULL)
				{
					/*~~~~~~~~~~~~~~~~*/
					char	szErr[1024];
					/*~~~~~~~~~~~~~~~~*/

					tsnprintf
					(
						szErr,
						sizeof(szErr),
						"[RegionManager::Init]: New Region[%d]Failed!!",
						pAreaFile->m_Count
					);
					szErr[sizeof(szErr) - 1] = '\0';
					KCheckEx(FALSE, szErr);
					return FALSE;
				}

				/*~~~~~~*/
				uint32	i;
				/*~~~~~~*/

				for(i = 0; i < m_uAreaCount; i++)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Region	*pArea = &(pAreaFile->m_pArea[i]);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					sprintf(szSection, "area%u", i);

					if(0 == iniArea.GetTextIfExist(szSection, "guid", szValue, sizeof(szValue))) break;
					pArea->m_uAreaID = (uint32) atoi(szValue);

					if(0 == iniArea.GetTextIfExist(szSection, "script_id", szValue, sizeof(szValue)))
						break;
					pArea->m_uScriptID = (uint32) atoi(szValue);

					if(0 == iniArea.GetTextIfExist(szSection, "left", szValue, sizeof(szValue))) break;
					pArea->m_rcArea.m_fLeft = (float) atof(szValue);

					if(0 == iniArea.GetTextIfExist(szSection, "top", szValue, sizeof(szValue))) break;
					pArea->m_rcArea.m_fTop = (float) atof(szValue);

					if(0 == iniArea.GetTextIfExist(szSection, "right", szValue, sizeof(szValue))) break;
					pArea->m_rcArea.m_fRight = (float) atof(szValue);

					if(0 == iniArea.GetTextIfExist(szSection, "bottom", szValue, sizeof(szValue)))
						break;
					pArea->m_rcArea.m_fBottom = (float) atof(szValue);
				}

				strncpy(pAreaFile->m_szFileName, pszPathName, _MAX_PATH - 1);
				pAreaFile->m_szFileName[sizeof(pAreaFile->m_szFileName) - 1] = '\0';
			}
		}

		iniArea.Close();

	}

	for(int32 i = 0; i < pAreaFile->m_Count; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Region	*pArea = &(pAreaFile->m_pArea[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_pMap->RegisterArea(pArea);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RegionManager::Term(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_uAreaCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 RegionManager::GetZoneID(float x, float z)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	i;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < m_uAreaCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Region	*pArea = &m_paArea[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pArea->IsContain(x, z))
		{
			return i;
		}
	}

	return UINT_MAX;

	__UNGUARD__ return UINT_MAX;
}
