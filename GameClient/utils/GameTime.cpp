/*$T Client/Game/Core/GameTime.cpp GC 1.140 08/23/09 04:52:41 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "StdAfx.h"
#include "GameTime.h"

/*
 * ������ʹ��ʱ�亯��ָ��,��ֹ�û�ʹ�ü򵥵ı��ٳ��ָ���ϵͳ�ٶ� ;
 * �߾���
 */
typedef BOOL (__stdcall *PFN_QUERY_COUNT_GET) (LARGE_INTEGER *);
static PFN_QUERY_COUNT_GET	g_pQueryCountGet = ::QueryPerformanceCounter;

typedef BOOL (__stdcall *PFN_QUERY_COUNT_FREQ_GET) (LARGE_INTEGER *);
static PFN_QUERY_COUNT_FREQ_GET g_pQueryCountFreqGet = ::QueryPerformanceFrequency;

/* ��ͨ */
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

	/* ʱ���ʼ�� */
	LARGE_INTEGER freq;

	m_bUsingQuery = (*g_pQueryCountFreqGet) (&freq);
	if(m_bUsingQuery)
	{
		m_secsPerTick = (1.0 / freq.QuadPart) * 1000;

		/* ʱ���ʼ�� */
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
    �����ֵ
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
    ����ʱ��
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CGameTime::Update(void)
{
	/* �ϴ�ִ��Update��ʱ�� */
	static UINT64 s_dwOldTime = 0;

	/* ������һ */
	m_dwTickCount++;

	if(m_bUsingQuery)
	{
		m_dwTimeNow = GetCurrentClockTime();
	}
	else
	{
		timeBeginPeriod(1);

		/* ��¼��ǰʱ�� */
		m_dwTimeNow = (*g_pTimeGetTime) ();
		timeEndPeriod(1);
	}

	/* ��������ʱ�� */
	m_dwDeltaTime = (FLOAT64) CalSubTime(s_dwOldTime, m_dwTimeNow);

	/* ����ÿ�������ѵ�ƽ��ʱ�� */
	const uint32 MAXTIME_CAL_LOOPTIME = 20;	/* ÿ20ms����һ��ÿ�廨�ѵ�ʱ�� */
	{
		static uint32 s_dwLoopCnt = 0;		/* ���ۼƼ��� */
		static uint32 s_dwLoopHop = 0;		/* ʱ���ۼƼ��� */

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
    ��ȡ��ǰʱ��
 =======================================================================================================================
 */
UINT64 CGameTime::GetCurrentClockTime(void)
{
	/* ��һ�λ�ȡ */
	static BOOL bFirst = TRUE;
	LARGE_INTEGER counter;
	(*g_pQueryCountGet) (&counter);

	if(bFirst)
	{
		m_uTimeOffset = counter.QuadPart;
		bFirst = FALSE; /* ֻȡһ�� */
	}

	return(UINT64) ((counter.QuadPart - m_uTimeOffset) * m_secsPerTick);
}

/*
 =======================================================================================================================
    ȡ���������֡��ƽ��ʱ��,��λ�Ǻ���
 =======================================================================================================================
 */
void CGameTime::CalAverageTime(void)
{
	/*
	 * chunlin added, 2009.1.20 ;
	 * �����������֡��ƽ��ʱ��
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
