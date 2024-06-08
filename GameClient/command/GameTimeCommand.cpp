/*$T Client/Game/Command/GameTimeCommand.cpp GC 1.140 08/23/09 04:52:40 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/* GMTimeEvent.cpp */
#include "StdAfx.h"
#include "GameTimeCommand.h"
#include "GameTime.h"
#include "GameCommandSystem.h"
/*
 * TimeEvent ;
 */
template<>
CTimeEventManager * Singleton<CTimeEventManager>::msSingleton = NULL;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CTimeEventManager *CTimeEventManager::GetSingletonPtr(void)
{
	return msSingleton;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CTimeEventManager &CTimeEventManager::GetSingleton(void)
{
	KLAssert(msSingleton);
	return(*msSingleton);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CTimeEventManager::CTimeEventManager(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CTimeEventManager::~CTimeEventManager(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CTimeEventManager::Initialize(void)
{
	return KRR_SUCCEED;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CTimeEventManager::Update(void)
{
	/*
	 * if( m_lTimeEvent.empty() ) return ;
	 * CTimeEvent* pTimeEvent = NULL;
	 * LIST_TIMEEVENT::iterator itCur, itEnd, itPrev;
	 * itCur = m_lTimeEvent.begin();
	 * itEnd = m_lTimeEvent.end();
	 * // TickTime 单位: 毫秒 int32 nTickTime = (int32)( GAME_TIME_PTR->GetLoopTime()
	 * 1000.f );
	 * // 遍历队列，找出符合条件的执行 while( itCur != itEnd ) { pTimeEvent = *itCur;
	 * itPrev = itCur;
	 * itCur ++;
	 * if( !pTimeEvent ) continue;
	 * // 时间到 pTimeEvent->m_uCurTime += nTickTime;
	 * if( pTimeEvent->m_uCurTime >= 900 ) // 到达1秒 { // 时间参数复位
	 * pTimeEvent->m_uCurTime = 0;
	 * // 将次数添加到事件中 int32 nCount = 0;
	 * if( TE_COUNT_UP == pTimeEvent->m_eType ) nCount = pTimeEvent->m_nCurCount;
	 * else if( TE_COUNT_DOWN == pTimeEvent->m_eType ) nCount = pTimeEvent->m_nLoopCount;
	 * // 只执行一次的 if( pTimeEvent->m_nLoopCount < 1 ) { // 执行事件
	 * COMMAND_SYS_PTR->AddCommand( pTimeEvent->m_strEventId,
	 * pTimeEvent->m_strArg.c_str(), "", nCount );
	 * // Execute // 删除事件 KSafeDelete( pTimeEvent );
	 * // 从队列中去除 m_lTimeEvent.erase( itPrev );
	 * } else { // 显示计时用 ++ ( pTimeEvent->m_nCurCount );
	 * // 每次都执行 if( pTimeEvent->m_bLoopRun ) { // 执行事件
	 * COMMAND_SYS_PTR->AddCommand( pTimeEvent->m_strEventId,
	 * pTimeEvent->m_strArg.c_str(), "", nCount );
	 * } // 循环次数减少 -- ( pTimeEvent->m_nLoopCount );
	 * } } }
	 */
	if(m_mapTimeEvent.empty()) return KRR_SUCCEED;

	/* TickTime 单位: 毫秒 */
	int32 nTickTime = (int32) (GAME_TIME_PTR->GetLoopTime() * 1000.f);
	CTimeEvent				*pTimeEvent = NULL;
	MAP_TIMEEVENT::iterator itCur, itEnd, itPrev;

	itCur = m_mapTimeEvent.begin();
	itEnd = m_mapTimeEvent.end();

	for(; itCur != itEnd; itCur = itPrev)
	{
		itPrev = itCur;
		itPrev++;

		pTimeEvent = (*itCur).second;
		if(NULL == pTimeEvent)
		{
			continue;
		}

		/* 时间到 */
		pTimeEvent->m_uCurTime += nTickTime;
		if(pTimeEvent->m_uCurTime >= 900)	/* 到达1秒 */
		{
			/* 时间参数复位 */
			pTimeEvent->m_uCurTime = 0;

			/* 将次数添加到事件中 */
			int32 nCount = 0;

			if(TE_COUNT_UP == pTimeEvent->m_eType)
				nCount = pTimeEvent->m_nCurCount;
			else if(TE_COUNT_DOWN == pTimeEvent->m_eType)
				nCount = pTimeEvent->m_nLoopCount;

			/* 只执行一次的 */
			if(pTimeEvent->m_nLoopCount < 1)
			{
				/* 执行事件 */
				COMMAND_SYS_PTR->AddCommand(pTimeEvent->m_strEventId, pTimeEvent->m_strArg.c_str(), "", nCount);	/* Execute
																													 * */

				/* 删除事件 */
				KSafeDelete(pTimeEvent);

				/* 从队列中去除 */
				m_mapTimeEvent.erase(itCur);
			}
			else
			{
				/* 显示计时用 */
				++(pTimeEvent->m_nCurCount);

				/* 每次都执行 */
				if(pTimeEvent->m_bLoopRun)
				{
					/* 执行事件 */
					COMMAND_SYS_PTR->AddCommand(pTimeEvent->m_strEventId, pTimeEvent->m_strArg.c_str(), "", nCount);
				}

				/* 循环次数减少 */
				--(pTimeEvent->m_nLoopCount);
			}
		}
	}

	return KRR_SUCCEED;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CTimeEventManager::Release(void)
{
	RemoveAllTimeEvent();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CTimeEventManager::GetTimeEventNum(void)
{
	/*
	 * return (int32)( m_lTimeEvent.size() );
	 */
	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CTimeEventManager::AddTimeEvent
(
	LPCTSTR szIndex /* int32 nIndex */,
	int32 nLoopCount,
	BOOL bLoopRun,
	LPCTSTR szEventId,
	TimeEventType eType,
	LPCTSTR szArg
)
{
	if(1 > strlen(szIndex) || 0 == strcmp("none", szIndex)) return FALSE;

	CTimeEvent	*pTimeEvent = new CTimeEvent;

	if(!pTimeEvent) return FALSE;

	/*
	 * if( -1 == nIndex ) ;
	 * return FALSE;
	 * ;
	 * pTimeEvent->m_nIndex = nIndex;
	 * pTimeEvent->m_strIndex = szIndex;
	 */
	pTimeEvent->m_uCurTime = 0; /* GAME_TIME_PTR->GetTimeNow();
								 * */
	pTimeEvent->m_nLoopCount = nLoopCount;
	pTimeEvent->m_bLoopRun = bLoopRun;

	/*
	 * pTimeEvent->m_eEventId = (GAME_COMMAND_ID)nEventId;
	 */
	pTimeEvent->m_strEventId = szEventId;
	pTimeEvent->m_eType = eType;
	pTimeEvent->m_strArg = szArg;

	/*
	 * m_lTimeEvent.push_back( pTimeEvent );
	 */
	m_mapTimeEvent[szIndex] = pTimeEvent;

	return TRUE;
}

/*
 =======================================================================================================================
    BOOL CTimeEventManager::AddTimeEvent( int32 nIndex, int32 nLoopCount, BOOL bLoopRun, int32 nEventId, TimeEventType eType,
    LPCTSTR szArg ) { CTimeEvent* pTimeEvent = new CTimeEvent;
    if( !pTimeEvent ) return FALSE;
    if( -1 == nIndex ) return FALSE;
    pTimeEvent->m_nIndex = nIndex;
    pTimeEvent->m_uCurTime = GAME_TIME_PTR->GetTimeNow();
    pTimeEvent->m_nLoopCount = nLoopCount;
    pTimeEvent->m_bLoopRun = bLoopRun;
    pTimeEvent->m_eEventId = (GAME_COMMAND_ID)nEventId;
    pTimeEvent->m_eType = eType;
    pTimeEvent->m_strArg = szArg;
    m_lTimeEvent.push_back( pTimeEvent );
    return TRUE;
    }
 =======================================================================================================================
 */
BOOL CTimeEventManager::RemoveTimeEvent(LPCTSTR szEventIndex /* int32 nEventIndex */ )
{
	/*
	 * if( nEventIndex < 0 || nEventIndex >= (int32)m_lTimeEvent.size() ) return FALSE;
	 * CTimeEvent* pTimeEvent = NULL;
	 * LIST_TIMEEVENT::iterator itCur, itEnd, itDel;
	 * itCur = m_lTimeEvent.begin();
	 * itEnd = m_lTimeEvent.end();
	 * while( itCur != itEnd ) { pTimeEvent = *itCur;
	 * itDel = itCur;
	 * itCur++;
	 * if( pTimeEvent->m_nIndex == nEventIndex ) { KSafeDelete( pTimeEvent );
	 * m_lTimeEvent.erase( itDel );
	 * // 索引重新排序 // 用 return TRUE;
	 * } }
	 */
	if(1 > strlen(szEventIndex) || 0 == strcmp("none", szEventIndex)) return FALSE;

	MAP_TIMEEVENT::iterator iterFind = m_mapTimeEvent.find(szEventIndex);

	if(iterFind != m_mapTimeEvent.end())
	{
		KSafeDelete(iterFind->second);
		iterFind->second = NULL;
		m_mapTimeEvent.erase(iterFind);
		return TRUE;
	}

	return FALSE;
}

int32 CTimeEventManager::GetRemainTime(LPCTSTR szEventIndex)
{
	if(1 > strlen(szEventIndex) || 0 == strcmp("none", szEventIndex)) return FALSE;

	MAP_TIMEEVENT::iterator iterFind = m_mapTimeEvent.find(szEventIndex);

	if(iterFind != m_mapTimeEvent.end())
	{
		return iterFind->second->m_nLoopCount;
	}

	return 0;

}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CTimeEventManager::RemoveAllTimeEvent(void)
{
	/*
	 * CTimeEvent* pTimeEvent = NULL;
	 * LIST_TIMEEVENT::iterator itCur, itEnd, itDel;
	 * itCur = m_lTimeEvent.begin();
	 * itEnd = m_lTimeEvent.end();
	 * while( itCur != itEnd ) { pTimeEvent = *itCur;
	 * itDel = itCur;
	 * itCur++;
	 * KSafeDelete( pTimeEvent );
	 * m_lTimeEvent.erase( itDel );
	 * } m_lTimeEvent.clear();
	 */
	CTimeEvent				*pTimeEvent = NULL;
	MAP_TIMEEVENT::iterator itCur, itEnd, itNext;

	itCur = m_mapTimeEvent.begin();
	itEnd = m_mapTimeEvent.end();

	for(; itCur != itEnd; itCur = itNext)
	{
		itNext = itCur;
		itNext++;

		pTimeEvent = itCur->second;
		KSafeDelete(pTimeEvent);

		m_mapTimeEvent.erase(itCur);
	}

	m_mapTimeEvent.clear();
}
