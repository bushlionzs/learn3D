/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MapDropPosManager.h
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	场景掉落位置管理器
**********************************************************************************************/


#ifndef _SCENEDROPPOS_MANAGER_H_
#define _SCENEDROPPOS_MANAGER_H_
#include "TypeDefine.h"

class	GameMap;
class	MapDropPosManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	MapDropPosManager();
	~MapDropPosManager();

public:
	BOOL	Init(uint32 uMapWidth = 0, uint32 uMapHeight = 0);
	void	Clear();

public:

	void SetMap(GameMap*pMap)
	{
		KCheck(pMap);
		m_pMap = pMap;
	}

	BOOL	CanDrop(float pos_x, float pos_y);
	void	SetDropPos(float pos_x, float pos_y);
	void	ClearDropPos(float pos_x, float pos_y);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	uchar	*m_MapDropPos;
	uint32	m_nDropZNum;
	uint32	m_nDropXNum;

	GameMap	*m_pMap;
};
#endif
