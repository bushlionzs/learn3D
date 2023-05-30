#include "stdafx.h"
#include "Behavior_Helper.h"

//////////////////////////////////////////////////////////////////////////
// 避免怪物重叠的帮助类
//////////////////////////////////////////////////////////////////////////
int32 AvoidMonsterOverlap::GetDirPos(GLPos	&rTar, const GLPos &rMonsterPos, const GLPos &rPlayerPos, float	fMaxDist, float	fMinDist)
{
	__GUARD__	rTar = rPlayerPos;
	int32		nStartIndex = 0, nEndIndex = 0, nIndex = 0;
	float		vX = rPlayerPos.m_fX - rMonsterPos.m_fX;
	float		vZ = rPlayerPos.m_fZ - rMonsterPos.m_fZ;
	float		fDist = KLSqrt(&rMonsterPos, &rPlayerPos);

	if(fDist < 0.001)
	{
		return INVALID_ID;
	}

	float	fCos = vX / fDist;
	float	fSin = vZ / fDist;
	float	fRet = ::asin(fSin);

	if(fRet > 0 && vX < 0)
	{
		fRet += __PI / 2;
	}
	else if(fRet < 0 && vX < 0)
	{
		fRet -= __PI / 2;
	}

	if(fRet < 0)
	{
		fRet += 2 * __PI;
	}

	float	fStart = fRet - __PI / 4;
	fStart = fStart > 0 ? fStart : (2 * __PI + fStart);
	float	fEnd = fRet + __PI / 4;

	fEnd = fEnd > 2 * __PI ? (fEnd - 2 * __PI) : fEnd;
	nStartIndex = GetIndex(fStart);
	nEndIndex = GetIndex(fEnd);

	int32	nUsedCount = 0;

	nIndex = GetBestPos(nStartIndex, nEndIndex, nUsedCount);
	if(FALSE == HaveMonsterNearly(nIndex))
	{
		rTar = rMonsterPos;
		return INVALID_ID;
	}

	if(MAX_FRACTION / 4 - 2 < nUsedCount)
	{
		int32	nDir = (rand() % 2) > 0 ? 4 : -4;
		for(int32 i = 0; MAX_MOVETIMES > i; ++i)
		{
			nUsedCount = 0;
			nStartIndex += nDir;
			nStartIndex = (nStartIndex + MAX_FRACTION) % MAX_FRACTION;
			nEndIndex += nDir;
			nEndIndex = (nEndIndex + MAX_FRACTION) % MAX_FRACTION;

			nIndex = GetBestPos(nStartIndex, nEndIndex, nUsedCount);
			if(MAX_FRACTION / 4 - 2 > nUsedCount)
			{
				break;
			}
		}
	}

	rTar.m_fX = rPlayerPos.m_fX + fMinDist * GetCos(nIndex);
	rTar.m_fZ = rPlayerPos.m_fZ + fMinDist * GetSin(nIndex);

	return nIndex;
	__UNGUARD__ return INVALID_ID;
}

void AvoidMonsterOverlap::ResetUsedDir(void)
{
	memset(m_isUsed, 0, MAX_FRACTION);
}

void AvoidMonsterOverlap::DecUsedDir(int32 nIndex)
{
	if(nIndex >= 0 && nIndex < MAX_FRACTION)
	{
		--m_isUsed[nIndex];
		if(0 >= m_isUsed[nIndex])
		{
			m_isUsed[nIndex] = 0;
		}
	}
}

int32 AvoidMonsterOverlap::GetMinIndex(int32 nStart, int32 nEnd, int32 &nMinIndex, int32 &nUsedCount)
{
	__GUARD__	KCheck(MAX_FRACTION > nStart && 0 <= nStart && MAX_FRACTION > nEnd && 0 <= nEnd);

	for(int32 i = nStart; i <= nEnd;)
	{
		if(m_isUsed[nMinIndex] > m_isUsed[i])
		{
			nMinIndex = i;
		}

		if(m_isUsed[i])
		{
			++nUsedCount;
		}

		i += 2;
	}

	for(int32 i = nStart + 1; i <= nEnd;)
	{
		if(m_isUsed[nMinIndex] > m_isUsed[i])
		{
			nMinIndex = i;
		}

		if(m_isUsed[i])
		{
			++nUsedCount;
		}

		i += 2;
	}

	++m_isUsed[nMinIndex];

	if(MAX_USEDTIMES == m_isUsed[nMinIndex])
	{
		m_isUsed[nMinIndex] = 0;
	}

	return nMinIndex;
	__UNGUARD__ return nMinIndex;
}

int32 AvoidMonsterOverlap::GetBestPos(int32 nStartIndex, int32 nEndIndex, int32 &nUsedCount)
{
	__GUARD__ int32 nIndex = 0;
	int32		nMinIndex = nStartIndex;
	int32		nStepLen = (nEndIndex - nStartIndex) > 0 ? (nEndIndex - nStartIndex) / 2 :
	(nEndIndex - nStartIndex + MAX_FRACTION) / 2;

	nMinIndex += nStepLen;
	if(nMinIndex >= MAX_FRACTION)
	{
		nMinIndex -= MAX_FRACTION;
	}

	if(nStartIndex > nEndIndex)
	{
		int32	Min1 = GetMinIndex(0, nEndIndex, nMinIndex, nUsedCount);
		int32	Min2 = GetMinIndex(nStartIndex, MAX_FRACTION - 1, nMinIndex, nUsedCount);

		if(m_isUsed[Min1] > m_isUsed[Min2])
		{
			nIndex = Min2;
			--m_isUsed[Min1];
		}
		else
		{
			nIndex = Min1;
			--m_isUsed[Min2];
		}
	}
	else
	{
		nIndex = GetMinIndex(nStartIndex, nEndIndex, nMinIndex, nUsedCount);
	}

	return nIndex;
	__UNGUARD__ return 0;
}

int32 AvoidMonsterOverlap::GetPosIfNoMonster(float fvalue)
{
	__GUARD__ for(int32 i = 0; MAX_FRACTION > i; ++i)
	{
		if(2 * i * __PI / MAX_FRACTION >= fvalue)
		{
			float	fStep1 = fabs(2 * i * __PI / MAX_FRACTION - fvalue);
			int32	j = i - 1 < 0 ? MAX_FRACTION - 1 : i - 1;
			float	fStep2 = fabs(2 * j * __PI / MAX_FRACTION - fvalue);
			int32	m = i + 1 > MAX_FRACTION - 1 ? MAX_FRACTION - i - 1 : i + 1;
			int32	n = j - 1 < 0 ? MAX_FRACTION - 1 : j - 1;

			if(0 == m_isUsed[i] && 0 == m_isUsed[j] && 0 == m_isUsed[m] && 0 == m_isUsed[n])
			{
				return fStep1 > fStep2 ? j : i;
			}
			else
			{
				return -1;
			}
		}
	}

	return -1;
	__UNGUARD__ return -1;
}

void AvoidMonsterOverlap::VerifyIndex(int32 &nIndex)
{
	__GUARD__ if(nIndex >= MAX_FRACTION)
	{
		nIndex -= MAX_FRACTION;
	}

	if(nIndex < 0)
	{
		nIndex += MAX_FRACTION;
	}

	__UNGUARD__
}

BOOL AvoidMonsterOverlap::HaveMonsterNearly(int32 nIndex)
{
	__GUARD__ int32 nTempIndex = nIndex - 1;

	VerifyIndex(nTempIndex);
	if(m_isUsed[nTempIndex] > 0) return TRUE;

	nTempIndex = nIndex;
	VerifyIndex(nTempIndex);

	if(m_isUsed[nTempIndex] > 1) return TRUE;

	nTempIndex = nIndex + 1;
	VerifyIndex(nTempIndex);
	if(m_isUsed[nTempIndex] > 0) return TRUE;

	return FALSE;
	__UNGUARD__ return FALSE;
}

void AvoidMonsterOverlap::InitCosSin(void)
{
	for(int32 i = 0; MAX_FRACTION > i; ++i)
	{
		m_fSin[i] = sin(i * 2 * __PI / MAX_FRACTION);
		m_fCos[i] = sin(i * 2 * __PI / MAX_FRACTION + __HALF_PI);
	}
}

float AvoidMonsterOverlap::GetCos(int32 index) const
{
	if(index < 0 || index >= MAX_FRACTION)
	{
		KCheck(NULL && "AvoidOverlap...GetCos()...index=invalid...");
		return 0.f;
	}

	return m_fCos[index];
}

float AvoidMonsterOverlap::GetSin(int32 index) const
{
	if(index < 0 || index >= MAX_FRACTION)
	{
		KCheck(NULL && "AvoidOverlap...GetSin()...index=invalid...");
		return 0.f;
	}

	return m_fSin[index];
}

int32 AvoidMonsterOverlap::GetIndex(float fValue)
{
	int32	i;

	for(i = 0; MAX_FRACTION > i; ++i)
	{
		if(i * 2 * __PI / MAX_FRACTION >= fValue)
		{
			return i;
		}
	}

	if(MAX_FRACTION == i)
	{
		return 0;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
// 怪物AI的数学帮助类
//////////////////////////////////////////////////////////////////////////
int32 MathSinCos::	mTrigTableSize;
float MathSinCos::	mTrigTableFactor;
float *MathSinCos:: mSinTable = 0;

MathSinCos		g_MathSinCos;

MathSinCos::MathSinCos(uint32 trigTableSize)
{
	mTrigTableSize = trigTableSize;
	mTrigTableFactor = mTrigTableSize / (2 * __PI);

	mSinTable = new float[mTrigTableSize];

	buildTrigTables();
}

MathSinCos::~MathSinCos()
{
	delete[] mSinTable;
}

void MathSinCos::buildTrigTables(void)
{
	float	angle;

	for(int32 i = 0; i < mTrigTableSize; ++i)
	{
		angle = 2 * __PI * i / mTrigTableSize;
		mSinTable[i] = sin(angle);
	}
}

float MathSinCos::SinTable(float fValue)
{
	int32	idx;
	if(fValue >= 0)
	{
		idx = int32(fValue * mTrigTableFactor) % mTrigTableSize;
	}
	else
	{
		idx = mTrigTableSize - (int32(-fValue * mTrigTableFactor) % mTrigTableSize) - 1;
	}

	return mSinTable[idx];
}


//////////////////////////////////////////////////////////////////////////
// 怪物AI巡逻的帮助类
//////////////////////////////////////////////////////////////////////////

void PatrolRoadsPointMgr::Init(GameMap*pMap)
{
	m_pMap = pMap;
}

void PatrolRoadsPointMgr::Clear(void)
{
	m_PatrolRoadsPointList = NULL;
	m_nPatrolRoadsPointCount = 0;
}

void PatrolRoadsPointMgr::LoadPatrolRoadsPoint(const char *filename)
{
	
}

BOOL PatrolRoadsPointMgr::FindPatrolRoadsPoint(int32 PatrolRoadsPointID) const
{
	if(PatrolRoadsPointID < 0 || PatrolRoadsPointID > m_nPatrolRoadsPointCount - 1)
	{
		return FALSE;
	}

	return TRUE;
}

int32 PatrolRoadsPointMgr::GetPatrolRoadsPoint(int32 patrolPathIndex, int32 patrolPointIndex, BOOL	&baHead, GLPos	&rTar, int32 &rSettleTime, ScriptID_t &rScriptID, BOOL bCircle, GLPos* rCheckPos)
{
	__GUARD__ if(patrolPathIndex < 0 || patrolPathIndex > m_nPatrolRoadsPointCount - 1)
	{
		char	szTemp[128];
		tsnprintf
			(
			szTemp,
			128,
			"patrolPathIndex=%d...patrolPathIndex < 0 || patrolPathIndex > m_nPatrolPathCount-1",
			patrolPathIndex
			);
		KCheck(FALSE && szTemp);
		return NULL;
	}

	if(patrolPointIndex < 0 || patrolPointIndex > m_PatrolRoadsPointList[patrolPathIndex].m_nPatrolPointCount - 1)
	{
		char	szTemp[128];
		tsnprintf
			(
			szTemp,
			128,
			"PatrolPointIndex=%d...patrolPointIndex < 0 || patrolPointIndex > m_PatrolRoadsPointList[patrolPathIndex].m_nPatrolPointCount-1",
			patrolPointIndex
			);
		KCheck(FALSE && szTemp);
		return NULL;
	}

	if (rCheckPos != NULL && (*rCheckPos) != m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_PatrolRoadsPoint)
	{
		rTar = m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_PatrolRoadsPoint;
		return patrolPointIndex;
	}

	int32	nCount = m_PatrolRoadsPointList[patrolPathIndex].m_nPatrolPointCount;
	if(baHead)
	{
		if(patrolPointIndex + 1 >= nCount)
		{
			GLPos	*pCurPos = &
				(m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_PatrolRoadsPoint);
			GLPos	*pStartPos = &
				(m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[0].m_PatrolRoadsPoint);
			if((*pCurPos) == (*pStartPos) || bCircle)
			{
				patrolPointIndex = 1;
			}
			else
			{
				--patrolPointIndex;
				baHead = FALSE;
			}
		}
		else
		{
			++patrolPointIndex;
		}
	}
	else
	{
		if(patrolPointIndex - 1 < 0)
		{
			patrolPointIndex = 1;
			baHead = TRUE;
		}
		else
		{
			--patrolPointIndex;
		}
	}
	{
		patrolPointIndex < 0 ? patrolPointIndex = 0 : NULL;
		patrolPointIndex + 1 > nCount ? patrolPointIndex = nCount - 1 : NULL;
	}

	rScriptID = m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_ScriptID;
	rSettleTime = m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_nSettleTime;
	rTar = m_PatrolRoadsPointList[patrolPathIndex].m_PatrolUnitList[patrolPointIndex].m_PatrolRoadsPoint;
	return patrolPointIndex;

	__UNGUARD__ return NULL;
}

