/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MapDropPosManager.cpp
			file path:	F:\khan2\src\MapServer\Server\Map
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	场景掉落位置管理器
**********************************************************************************************/


#include "stdafx.h"
#include "MapDropPosManager.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "BaseTool.h"
#include "server_settting.h"

#define MAX_SCENE_DROPPOS_SIZE	(512)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

MapDropPosManager::MapDropPosManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_MapDropPos = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nDropZNum = 0;
	m_nDropXNum = 0;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MapDropPosManager::~MapDropPosManager()
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
BOOL MapDropPosManager::Init(uint32 uMapWidth, uint32 uMapHeight)
{
	__GUARD__;
	
	if(uMapWidth > MAX_SCENE_DROPPOS_SIZE || uMapHeight > MAX_SCENE_DROPPOS_SIZE) 
		return FALSE;

	if(uMapWidth == 0 || uMapHeight == 0)
	{
		QLogSystem::SLOW_LOG( SLOW_LOG_SERVER,"MapDropPosManager::Init error uMapWidth = %d, uMapHeight = %d!\n",uMapWidth,uMapHeight);
		return TRUE;
	}

	while((m_nDropZNum + 1) * g_Config.m_ConfigInfo.m_DropPosDistance < uMapHeight)
	{
		++m_nDropZNum;
	}

	while((m_nDropXNum + 1) * g_Config.m_ConfigInfo.m_DropPosDistance < uMapWidth)
	{
		++m_nDropXNum;
	}

	m_MapDropPos = new uchar[m_nDropZNum * m_nDropXNum];
	if(m_MapDropPos == NULL)
	{
		KCheck(0);
		return FALSE;
	}

	memset(m_MapDropPos, 0, m_nDropZNum * m_nDropXNum * sizeof(uchar));

	GLPos pos;
	MapInfo* pMapInfo = m_pMap->GetMapInfo();
	for(uint32 i = 0; i < m_nDropZNum; ++i)
	{
		for(uint32 j = 0; j < m_nDropXNum; ++j)
		{
			pos.m_fX = (j + 1) * g_Config.m_ConfigInfo.m_DropPosDistance;
			pos.m_fZ = (i + 1) * g_Config.m_ConfigInfo.m_DropPosDistance;
			if(!pMapInfo->IsCanGo(pos))
			{
				m_MapDropPos[j + i * m_nDropXNum] = -1;
			}
		}
	}

	return TRUE;
	__UNGUARD__;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void MapDropPosManager::Clear()
{
	__GUARD__ if(m_MapDropPos == NULL || m_nDropZNum == 0 || m_nDropXNum == 0) return;

	KSafeDelete_ARRAY(m_MapDropPos);
	m_nDropZNum = 0;
	m_nDropXNum = 0;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MapDropPosManager::CanDrop(float pos_fx, float pos_fz)
{
	__GUARD__;

	//检查地图
	if( m_pMap == NULL )
		return FALSE;
	
	//相关检查
	if(m_MapDropPos == NULL || m_nDropZNum == 0 || m_nDropXNum == 0) 
		return FALSE;

	//x位置检查
	if( (pos_fx < g_Config.m_ConfigInfo.m_DropPosDistance) || (pos_fx > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropXNum) )
		return FALSE;

	//z位置检查
	if( (pos_fz < g_Config.m_ConfigInfo.m_DropPosDistance)|| (pos_fz > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropZNum) )
		return FALSE;

	GLPos pos;
	pos.m_fX = pos_fx;
	pos.m_fZ = pos_fz;

	//检查是否可以寻路
	if( m_pMap->GetMapInfo()->IsCanGo(pos) == FALSE )
		return FALSE;

	//计算掉落间隔网隔索引,x,z
	uint32 pos_x = (uint32) (pos_fx / g_Config.m_ConfigInfo.m_DropPosDistance);
	uint32 pos_z = (uint32) (pos_fz / g_Config.m_ConfigInfo.m_DropPosDistance);
	
	if(pos_x <= m_nDropXNum && pos_z <= m_nDropZNum)
	{
		uchar nInvalidPos = -1;
		if( m_MapDropPos[(pos_x - 1) + m_nDropXNum * (pos_z - 1)] == nInvalidPos )
			return FALSE;

		BOOL bAlive = m_MapDropPos[(pos_x - 1) + m_nDropXNum * (pos_z - 1)];
		return !bAlive;
	}

	return FALSE;
	__UNGUARD__;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void MapDropPosManager::SetDropPos(float pos_fx, float pos_fz)
{
	__GUARD__ if(m_MapDropPos == NULL || m_nDropZNum == 0 || m_nDropXNum == 0) return;
	if
	(
		(pos_fx < g_Config.m_ConfigInfo.m_DropPosDistance)
	||	(pos_fx > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropXNum)
	)
	{
		KCheck(0);
	}

	if
	(
		(pos_fz < g_Config.m_ConfigInfo.m_DropPosDistance)
	||	(pos_fz > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropZNum)
	)
	{
		KCheck(0);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	pos_x = (uint32) (pos_fx / g_Config.m_ConfigInfo.m_DropPosDistance);
	uint32	pos_z = (uint32) (pos_fz / g_Config.m_ConfigInfo.m_DropPosDistance);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pos_x <= m_nDropXNum && pos_z <= m_nDropZNum)
	{
		m_MapDropPos[(pos_x - 1) + m_nDropXNum * (pos_z - 1)] = 1;
	}
	else
	{
		KCheck(0);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void MapDropPosManager::ClearDropPos(float pos_fx, float pos_fz)
{
	__GUARD__ if(m_MapDropPos == NULL || m_nDropZNum == 0 || m_nDropXNum == 0) return;
	if
	(
		(pos_fx < g_Config.m_ConfigInfo.m_DropPosDistance)
	||	(pos_fx > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropXNum)
	)
	{
		KCheck(0);
	}

	if
	(
		(pos_fz < g_Config.m_ConfigInfo.m_DropPosDistance)
	||	(pos_fz > g_Config.m_ConfigInfo.m_DropPosDistance * m_nDropZNum)
	)
	{
		KCheck(0);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	pos_x = (uint32) (pos_fx / g_Config.m_ConfigInfo.m_DropPosDistance);
	uint32	pos_z = (uint32) (pos_fz / g_Config.m_ConfigInfo.m_DropPosDistance);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pos_x <= m_nDropXNum && pos_z <= m_nDropZNum)
	{
		m_MapDropPos[(pos_x - 1) + m_nDropXNum * (pos_z - 1)] = 0;
	}
	else
	{
		KCheck(0);
	}

	__UNGUARD__
}
