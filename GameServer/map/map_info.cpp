

#include "stdafx.h"
#include "map_info.h"
#include "BaseTool.h"
#include "server_map_path.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
MapInfo::MapInfo()
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_CX = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	m_CZ = 0;

	m_pPathFinder = NULL;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MapInfo::~MapInfo()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete(m_pPathFinder);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void MapInfo::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete(m_pPathFinder);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MapInfo::Load(char *filename)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete(m_pPathFinder);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_pPathFinder == NULL)
	{
		m_pPathFinder = new Wayfinding(this, filename, m_CX, m_CZ);
		if(m_pPathFinder == NULL)
		{
			KCheck(FALSE);
			return FALSE;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

Wayfinding* MapInfo::GetPathFinder()
{
	return m_pPathFinder;
}

BOOL MapInfo::IsCanGo(const GLPos &pos)
{
	__GUARD__ if(m_pPathFinder) return m_pPathFinder->IsCanGo(pos);

	KCheck(m_pPathFinder);
	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MapInfo::FindEmptyPos(GLPos *pos)
{
	__GUARD__
#define MAX_FIND_SIZE	24

	if(IsCanGo(*pos)) return TRUE;

	for(int32 i = 0; i < MAX_FIND_SIZE; i++)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		GLPos	pTest;
		/*~~~~~~~~~~~~~~~~~~*/

		pTest.m_fX = pos->m_fX + i;
		pTest.m_fZ = pos->m_fZ;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX;
		pTest.m_fZ = pos->m_fZ + i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX - i;
		pTest.m_fZ = pos->m_fZ;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX;
		pTest.m_fZ = pos->m_fZ - i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX + i;
		pTest.m_fZ = pos->m_fZ + i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX - i;
		pTest.m_fZ = pos->m_fZ - i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX + i;
		pTest.m_fZ = pos->m_fZ - i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}

		pTest.m_fX = pos->m_fX - i;
		pTest.m_fZ = pos->m_fZ + i;
		VerifyPos(&pTest);
		if(IsCanGo(pTest))
		{
			*pos = pTest;
			return TRUE;
		}
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL MapInfo::IsPosLogicValid(const GLPos *pos)
{
	__GUARD__
#define VALID_SIZE	10

	if
	(
		pos->m_fX < VALID_SIZE
	||	(pos->m_fX + VALID_SIZE) > CX()
	||	pos->m_fZ < VALID_SIZE
	||	(pos->m_fZ + VALID_SIZE) > CZ()
	)
	{
		return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}
