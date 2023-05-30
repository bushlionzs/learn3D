/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	ScanerOperator.h 
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	Scanor是所有搜索周围obj操作的基类
			具体的搜索操作 比如：
			Scanor_GuildMember
			Scanor_Human
			Scanor_Monster
			Scanor_SectorSkill
			Scanor_Teammate
			ScanOpt_SObj_ScanPlayer 
			ScanOptSObjScanTrap 
			Scanor_NearestMonster
			等等
**********************************************************************************************/


#ifndef __SCANOR_H__
#define __SCANOR_H__

#include "TypeDefine.h"

enum SCANRET { SCANRETURN_CONTINUE = 0, SCANRETURN_BREAK, SCANRETURN_RETURN, SCANRETURN_NUMBER, };

class	GameMap;
class	Object;

struct SCANOR_INIT
{
	GameMap		*m_pMap;

	GridID_t	m_GridID;

	int32		m_nZoneRadius;

	BOOL		m_bScanPlayer;

	SCANOR_INIT()
	{
		m_pMap = NULL;
		m_GridID = INVALID_ID;
		m_nZoneRadius = 0;
		m_bScanPlayer = FALSE;
	};
};

class	Scanor
{
	friend class	Map;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor();
	virtual		~Scanor();

	virtual BOOL	Init(SCANOR_INIT *pInit);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual BOOL OnEvent_BeforeScan()
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL On_IsNeedScan(GridID_t ZoneID)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 OnEvent_FindObj(Object *pObj)
	{
		return SCANRETURN_CONTINUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void OnEvent_AfterScan()
	{ ;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	GameMap *GetMap()
	{
		return m_pMap;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	GameMap*m_pMap;

	GridID_t	m_GridID;

	int32		m_nGridRadius;

	BOOL		m_bScanPlayer;
};
#endif
