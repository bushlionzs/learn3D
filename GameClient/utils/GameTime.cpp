/*$T Client/Game/Core/GameTime.cpp GC 1.140 08/23/09 04:52:41 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "StdAfx.h"
#include "GameTime.h"

/*
 * 保存所使用时间函数指针,防止用户使用简单的变速齿轮更改系统速度 ;
 * 高精度
 */
typedef BOOL (__stdcall *PFN_QUERY_COUNT_GET) (LARGE_INTEGER *);
static PFN_QUERY_COUNT_GET	g_pQueryCountGet = ::QueryPerformanceCounter;

typedef BOOL (__stdcall *PFN_QUERY_COUNT_FREQ_GET) (LARGE_INTEGER *);
static PFN_QUERY_COUNT_FREQ_GET g_pQueryCountFreqGet = ::QueryPerformanceFrequency;

/* 普通 */
typedef DWORD (__stdcall *PFN_TIME_GET_TIME) (void);
static PFN_TIME_GET_TIME	g_pTimeGetTime = ::timeGetTime;
template<>
CGameTime * Singleton<CGameTime>::msSingleton = NULL;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CGameTime *CGameTime::GetSingletonPtr(void)
{
	return msSingleton;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CGameTime &CGameTime::GetSingleton(void)
{
	KLAssert(msSingleton);
	return(*msSingleton);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CGameTime::Initialize(void)
{
	m_fLoopTime = 0.0f;
	m_dwDeltaTime = 0;
	m_dwTickCount = 0;

	m_serverTime = 0;
	m_localTime = 0;
	m_fAverageTime = 20.f;

	/* 时间初始化 */
	LARGE_INTEGER freq;

	m_bUsingQuery = (*g_pQueryCountFreqGet) (&freq);
	if(m_bUsingQuery)
	{
		m_secsPerTick = (1.0 / freq.QuadPart) * 1000;

		/* 时间初始化 */
		m_dwTimeNow = GetCurrentClockTime();
	}
	else
	{
		m_dwTimeNow = (*g_pTimeGetTime) ();
	}

	return KRR_SUCCEED;
}

/*
 =======================================================================================================================
    计算差值
 =======================================================================================================================
 */
UINT64 CGameTime::CalSubTime(UINT64 timeStart, UINT64 timeEnd)
{
	if(timeEnd < timeStart)
		return(0xFFFFFFFFFFFFFFFFULL - timeStart) + timeEnd;
	else
		return timeEnd - timeStart;
}

/*
 =======================================================================================================================
    更新时间
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CGameTime::Update(void)
{
	/* 上次执行Update的时间 */
	static UINT64 s_dwOldTime = 0;

	/* 桢数加一 */
	m_dwTickCount++;

	if(m_bUsingQuery)
	{
		m_dwTimeNow = GetCurrentClockTime();
	}
	else
	{
		timeBeginPeriod(1);

		/* 记录当前时间 */
		m_dwTimeNow = (*g_pTimeGetTime) ();
		timeEndPeriod(1);
	}

	/* 计算流逝时间 */
	m_dwDeltaTime = (FLOAT64) CalSubTime(s_dwOldTime, m_dwTimeNow);

	/* 计算每桢所花费的平均时间 */
	const uint32 MAXTIME_CAL_LOOPTIME = 20;	/* 每20ms计算一次每桢花费的时间 */
	{
		static uint32 s_dwLoopCnt = 0;		/* 桢累计计数 */
		static uint32 s_dwLoopHop = 0;		/* 时间累计计数 */

		s_dwLoopCnt++;
		s_dwLoopHop += m_dwDeltaTime;

		if(s_dwLoopHop > MAXTIME_CAL_LOOPTIME)
		{
			m_fLoopTime = (s_dwLoopHop / (FLOAT) s_dwLoopCnt) / 1000.0f;

			s_dwLoopCnt = 0;
			s_dwLoopHop = 0;
		}
	}

	CalAverageTime();

	s_dwOldTime = m_dwTimeNow;

	return KRR_SUCCEED;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CGameTime::Release(void)
{
}

/*
 =======================================================================================================================
    获取当前时间
 =======================================================================================================================
 */
UINT64 CGameTime::GetCurrentClockTime(void)
{
	/* 第一次获取 */
	static BOOL bFirst = TRUE;
	LARGE_INTEGER counter;
	(*g_pQueryCountGet) (&counter);

	if(bFirst)
	{
		m_uTimeOffset = counter.QuadPart;
		bFirst = FALSE; /* 只取一次 */
	}

	return(UINT64) ((counter.QuadPart - m_uTimeOffset) * m_secsPerTick);
}

/*
 =======================================================================================================================
    取得最近若干帧的平均时间,单位是毫秒
 =======================================================================================================================
 */
void CGameTime::CalAverageTime(void)
{
	/*
	 * chunlin added, 2009.1.20 ;
	 * 计算最近若干帧的平均时间
	 */
	const FLOAT MAX_TIME_CAL = 0.5f;
	static std::deque<float>	deltaTimeList;
	float timeSum = 0;
	std::deque<float>::iterator iter;

	for(iter = deltaTimeList.begin(); iter != deltaTimeList.end(); iter++)
	{
		timeSum += *iter;
	}

	size_t size = deltaTimeList.size();

	if(size != 0) m_fAverageTime = (FLOAT) timeSum / (FLOAT) size;

	float dt = (float) m_dwDeltaTime;

	deltaTimeList.push_back(m_dwDeltaTime);
	size = deltaTimeList.size();

	int32 framenum = MAX_TIME_CAL * 1000.f / m_fAverageTime;

	if(framenum > 300) framenum = 300;

	float decreaseNum = size - framenum;

	if(size > framenum)
	{
		decreaseNum *= 0.2f;
		while(decreaseNum > 0 && size > 1)
		{
			deltaTimeList.pop_front();
			size = deltaTimeList.size();
			decreaseNum -= 1;
		}
	}

	/* end */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CGameTime::SetServerTime(time_t sTime)
{
	m_serverTime = sTime;
	time(&m_localTime);

	m_localTime_Pre = g_pTimeGetTime();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
time_t CGameTime::GetServerTime(void)
{
	if(m_serverTime <= 0) return 0;

	DWORD nElaspedTime_sec = (g_pTimeGetTime() - m_localTime_Pre) / 1000;

	return m_serverTime + nElaspedTime_sec;
}
