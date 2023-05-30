/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	Grid.h
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	单个场景的管理方式 由类似矩阵的正方形格子组成的，其中每一个格子都有自己所在的行和列
			Grid就代表一个格子
			每一个Grid都存有处在该Grid中的玩家队列和obj队列
			场景使用这样的组织方式 是能快速的对obj进行查找和定位
			同时这种组织方式也为消息的广播提个了基础 所谓的3*3或者5*5的区域广播 指的都是Grid的阶数
**********************************************************************************************/


#ifndef __ZONE_H__
#define __ZONE_H__

#include "TypeDefine.h"
#include "gameobject/ObjectList.h"
#include "map/RegionManager.h"

struct _GRID_INFO
{
	uint16	m_wZoneW;
	uint16	m_wZoneH;
	uint16	m_wZoneSize;

	_GRID_INFO()
	{
		m_wZoneW = 0;
		m_wZoneH = 0;
		m_wZoneSize = 0;
	};
};

struct Grid
{
public:
	Grid();
	~Grid();

	void	Clear();
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetZoneID(GridID_t id)
	{
		m_ZoneID = id;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GridID_t GetZoneID()
	{
		return m_ZoneID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjectList *GetObjList(void)
	{
		return &m_ObjList;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjectList *GetHumanList(void)
	{
		return &m_PlayerList;
	}

	BOOL	OnEvent_ObjectEnter(Object *pObj);
	BOOL	OnEvent_ObjectLeave(Object *pObj);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void AddArea(const Region *pArea)
	{
		if(m_AreaCount >= MAX_AREA_IN_ZONE)
		{
			KCheck(FALSE && "这个 zone 的 area 也太多了吧！");
			return;
		}

		m_apArea[m_AreaCount++] = pArea;
	}

	const Region	*GetCurrentArea(const GLPos *pWorldPos);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uchar GetAreaCount()
	{
		return m_AreaCount;
	}

protected:
	ObjectList		m_PlayerList;
	ObjectList		m_ObjList;

	GridID_t	m_ZoneID;
	uchar		m_AreaCount;
	const Region	*m_apArea[MAX_AREA_IN_ZONE];
};
#endif
