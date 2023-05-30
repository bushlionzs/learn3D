#ifndef _AIHELPER_H_
#define _AIHELPER_H_

#include "TypeDefine.h"
#include "Behavior_Character.h"
#include "Util.h"

//////////////////////////////////////////////////////////////////////////
// 避免怪物重叠的帮助类
//////////////////////////////////////////////////////////////////////////
class	AvoidMonsterOverlap
{
public:
	enum { MAX_FRACTION = 16, MAX_MOVETIMES = 4, MAX_USEDTIMES = 255, };
	AvoidMonsterOverlap(void)
	{
		memset(m_isUsed, 0, sizeof(uchar) * MAX_FRACTION);
		InitCosSin();
	}

	virtual~AvoidMonsterOverlap(void)
	{
	}

	int32 GetDirPos(GLPos	&rTar, const GLPos &rMonsterPos, const GLPos &rPlayerPos, float	fMaxDist, float	fMinDist);
	void ResetUsedDir(void);
	void DecUsedDir(int32 nIndex);

protected:
	int32 GetMinIndex(int32 nStart, int32 nEnd, int32 &nMinIndex, int32 &nUsedCount);
	int32 GetBestPos(int32 nStartIndex, int32 nEndIndex, int32 &nUsedCount);
	int32 GetPosIfNoMonster(float fvalue);
	void VerifyIndex(int32 &nIndex);
	BOOL HaveMonsterNearly(int32 nIndex);
	void InitCosSin(void);
	float GetCos(int32 index) const;
	float GetSin(int32 index) const;
	int32 GetIndex(float fValue);
	
private:
	uchar	m_isUsed[MAX_FRACTION];
	float	m_fCos[MAX_FRACTION];
	float	m_fSin[MAX_FRACTION];
};


//////////////////////////////////////////////////////////////////////////
// 怪物AI的数学帮助类
//////////////////////////////////////////////////////////////////////////
class	MathSinCos
{
protected:
	static int	mTrigTableSize;
	static float	mTrigTableFactor;
	static float	*mSinTable;

	void		buildTrigTables();
	static float	SinTable(float fValue);
public:
	static inline float Cos(const float &fValue) {	return SinTable(fValue + __HALF_PI); }
	static inline float Sin(const float &fValue) {	return SinTable(fValue); }

	MathSinCos(uint32 trigTableSize = 4096);
	~	MathSinCos();
};

extern MathSinCos	g_MathSinCos;


//////////////////////////////////////////////////////////////////////////
// 怪物AI巡逻的帮助类
//////////////////////////////////////////////////////////////////////////
struct SPatrolRoadsPoint
{
	struct PatrolUnit
	{
		int32		m_nSettleTime;
		ScriptID_t	m_ScriptID;
		GLPos	m_PatrolRoadsPoint;
		PatrolUnit()
		{
			m_nSettleTime = 0;
			m_ScriptID = -1;
		}
		void Clear(void)
		{
			m_nSettleTime = 0;
			m_ScriptID = -1;
		}
	};

	int32		m_nPatrolPointCount;
	PatrolUnit	*m_PatrolUnitList;

	SPatrolRoadsPoint()
	{
		m_nPatrolPointCount = 0;
		m_PatrolUnitList = NULL;
	}
	~SPatrolRoadsPoint()
	{
		Clear();
	}
	void Clear(void)
	{
		m_nPatrolPointCount = 0;
		KSafeDelete(m_PatrolUnitList);
	}
};

class	GameMap;
class	PatrolRoadsPointMgr
{
public:
	PatrolRoadsPointMgr()
	{
		m_nPatrolRoadsPointCount = 0;
		m_PatrolRoadsPointList = NULL;
	}
	~PatrolRoadsPointMgr()
	{
		Clear();
	}

	void	Init(GameMap *pMap);
	void	Clear(void);
	void	LoadPatrolRoadsPoint(const char *filename);

	int32	GetPatrolRoadsPoint(int32 patrolPathIndex, int32 patrolPointIndex, BOOL &baHead, GLPos &rTar, int32 &rSettleTime, ScriptID_t	&rScriptID,	BOOL bCircle = FALSE, GLPos* rCheckPos = NULL);
	BOOL	FindPatrolRoadsPoint(int32 PatrolRoadsPointID) const;
private:
	int32		m_nPatrolRoadsPointCount;
	SPatrolRoadsPoint	*m_PatrolRoadsPointList;
	GameMap*m_pMap;
};

#endif
