/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MapInfo.h
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	�����Ƕ�Wayfinding�ķ�װ 
			1�ж�Ŀ����Ƿ��ǿ����ߵ�
			2������Χһ�������ߵĵ�
**********************************************************************************************/


#ifndef __MAP_H__
#define __MAP_H__

#include "TypeDefine.h"

class	Wayfinding;

class	MapInfo
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	MapInfo();
	~MapInfo();

	void	Clear();

	BOOL	Load(char *filename);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 CX()
	{
		return m_CX;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 CZ()
	{
		return m_CZ;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32		m_CX;
	uint32		m_CZ;
	Wayfinding	*m_pPathFinder;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void VerifyPos(GLPos *Pos)
	{
		Pos->m_fX = Pos->m_fX < 0 ? 0 : Pos->m_fX;
		Pos->m_fZ = Pos->m_fZ < 0 ? 0 : Pos->m_fZ;
		Pos->m_fX = ((Pos->m_fX >= (float) m_CX) ? ((float) m_CX - 0.1f) : Pos->m_fX);
		Pos->m_fZ = ((Pos->m_fZ >= (float) m_CZ) ? ((float) m_CZ - 0.1f) : Pos->m_fZ);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Wayfinding* GetPathFinder();

	BOOL	IsCanGo(const GLPos &pos);
	BOOL	FindEmptyPos(GLPos *pos);
	BOOL	IsPosLogicValid(const GLPos *pos);
};
#endif