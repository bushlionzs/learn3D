#include "OgreHeader.h"
#include "GameMapRegion.h"
#include "GameMapPath.h"

#include "OgreSceneNode.h"
#include "OgreNode.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CMapRegion::CMapRegion(void)
{
	m_nCount = 0;
	m_ID = INVALID_ID;
	m_bDynamic = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CMapRegion::~CMapRegion(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapRegion::AddPoint(const VisibilityPoints *pfvPoint)
{
	m_vfPoints.push_back(*pfvPoint);
	m_nCount = (int32) m_vfPoints.size();

	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapRegion::IsBulge(int32 nIndex) const
{
	if((nIndex < 0) || (nIndex >= (int32) m_vbBulge.size()))
	{
		return FALSE;
	}

	return m_vbBulge[nIndex];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapRegion::JudgeBulge(int32 nIndex)
{
	if(nIndex >= m_nCount)
	{
		return FALSE;
	}

	if(m_nCount < 3)
	{
		/* 多边形不合法 */
		return FALSE;
	}

	if(m_nCount == 3)
	{
		/* 三角形情况 */
		return true;
	}

	int32 nIndex1, nIndex2, nIndex3;

	nIndex1 = nIndex - 1;
	nIndex2 = nIndex;
	nIndex3 = nIndex + 1;
	if(nIndex1 < 0)
	{
		nIndex1 = (int32) (m_vfPoints.size()) - 1;
	}

	if(nIndex3 >= (int32) (m_vfPoints.size()))
	{
		nIndex3 = 0;
	}

	vector2 fvLine1, fvLine2;

	fvLine1.x = m_vfPoints[nIndex1].m_position.x - m_vfPoints[nIndex2].m_position.x;
	fvLine1.y = m_vfPoints[nIndex1].m_position.y - m_vfPoints[nIndex2].m_position.y;
	fvLine2.x = m_vfPoints[nIndex3].m_position.x - m_vfPoints[nIndex2].m_position.x;
	fvLine2.y = m_vfPoints[nIndex3].m_position.y - m_vfPoints[nIndex2].m_position.y;

	FLOAT	fAngle1 = atan((-fvLine1.y) / fvLine1.x);
	FLOAT	fAngle2 = atan((-fvLine2.y) / fvLine2.x);

	if(fvLine1.x < 0.f)
	{
		fAngle1 += (FLOAT) KLU_PI;
	}

	if(fvLine2.x < 0.f)
	{
		fAngle2 += (FLOAT) KLU_PI;
	}

	if(fAngle1 < 0.f) fAngle1 = (FLOAT) KLU_PI * 2 + fAngle1;
	if(fAngle2 < 0.f) fAngle2 = (FLOAT) KLU_PI * 2 + fAngle2;

	FLOAT	fAngle = fAngle2 - fAngle1;

	if(fAngle >= 0.f)
	{
		if(fAngle < (FLOAT) KLU_PI)
			return true;
		else
			return FALSE;
	}
	else
	{
		if(fAngle < (FLOAT) (-KLU_PI))
			return true;
		else
			return FALSE;
	}

	return FALSE;
}


void CMapRegion::JudgeAllBulge(void)
{
	m_vbBulge.clear();

	int32		i;
	BOOL	bBulge;

	for(i = 0; i < (int32) m_vfPoints.size(); i++)
	{
		bBulge = JudgeBulge(i);
		m_vbBulge.push_back(bBulge);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CMapRegion::GetIndex(const vector2 *pfvPoint) const
{
	for(int32 i = 0; i < (int32) m_vfPoints.size(); i++)
	{
		if
		(
			(abs(pfvPoint->x - m_vfPoints[i].m_position.x) < 1e-10)
		&&	(abs(pfvPoint->y - m_vfPoints[i].m_position.y) < 1e-10)
		)
		{
			return i;
		}
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CMapRegion::GetNeighborBulgeIndex(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const
{
	if((m_vfPoints.empty()) || (m_vbBulge.empty()))
	{
		return -1;
	}

	if((nIndex < 0) || (nIndex >= (int32) m_vfPoints.size()))
	{
		return -1;
	}

	int32 ret = (bCountSelf) ? (nIndex) : ((bClockwise) ? (nIndex + 1) : (nIndex - 1));
	int32 i, nSize;

	nSize = (int32) m_vfPoints.size();
	for(i = 0; i < nSize; i++)
	{
		if(ret >= nSize)
		{
			ret = 0;
		}

		if(ret < 0)
		{
			ret = nSize - 1;
		}

		if(m_vbBulge[ret])
		{
			return ret;
		}
		(bClockwise) ? (ret++) : (ret--);
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CMapRegion::GetNeighborBulgeIndex(const vector2 *pfvPoint, BOOL bCountSelf, BOOL bClockwise) const
{
	int32 nIndex = GetIndex(pfvPoint);

	if(nIndex >= 0)
	{
		return GetNeighborBulgeIndex(nIndex, bCountSelf, bClockwise);
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector2 *CMapRegion::GetNeighborBulge(int32 nIndex, BOOL bCountSelf, BOOL bClockwise) const
{
	int32 ret = GetNeighborBulgeIndex(nIndex, bCountSelf, bClockwise);

	if(ret >= 0)
	{
		return &m_vfPoints[ret].m_position;
	}

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector2 *CMapRegion::GetNeighborBulge(const vector2 *pfvPoint, BOOL bCountSelf, BOOL bClockwise) const
{
	int32 nIndex = GetIndex(pfvPoint);

	if(nIndex >= 0)
	{
		return GetNeighborBulge(nIndex, bCountSelf, bClockwise);
	}

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CMapRegion::GetDistanceSq(int32 nStart, int32 nEnd, BOOL bClockwise, BOOL bOnlyBugle) const
{
	/* 起点和终点是多边形的凸点(这个条件是否需要,还是任何点都可以?商榷) */
	if(bOnlyBugle && (!IsBulge(nStart) || !IsBulge(nEnd))) return -1.f;

	FLOAT	ret = 0;
	int32		m = nStart;
	int32		n = nStart;

	while(n != nEnd)
	{
		n = GetNeighborBulgeIndex(m, FALSE, bClockwise);
		ret += CMapPath::fvDistancePow(m_vfPoints[m].m_position, m_vfPoints[n].m_position);
		m = n;
	}

	return ret;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector2 *CMapRegion::GetPoint(int32 nIndex, BOOL bLoop) const
{
	if(m_vfPoints.empty())
	{
		return NULL;
	}

	if(bLoop)
	{
		nIndex = nIndex % (int32) m_vfPoints.size();
	}
	else if(nIndex >= (int32) m_vfPoints.size())
	{
		return NULL;
	}

	return &m_vfPoints[nIndex].m_position;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector2 *CMapRegion::GetPoint(int32 nIndex) const
{
	return GetPoint(nIndex, true);
}
