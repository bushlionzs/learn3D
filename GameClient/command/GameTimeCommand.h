#ifndef _KHAN_TIME_COMMAND_H_
#define _KHAN_TIME_COMMAND_H_
#include <OgreSingleton.h>
enum TimeEventType { TE_COUNT_UP = 0,			 /* 正计时 */ TE_COUNT_DOWN,				  /* 倒计时 */ };
struct CTimeEvent
{
	/*
	 * 可以用名字或索引 ;
	 * STRING m_strIndex;
	 * // ;
	 * int32 m_nIndex;
	 * //
	 */
	UINT64			m_uCurTime;		/* 当前的时间 毫秒 */
	int32				m_nLoopCount;	/* 循环次数 以秒为单位 */
	BOOL			m_bLoopRun;		/* 多次执行，即每秒执行一次 */
	STRING			m_strEventId;	/* 事件id */
	TimeEventType	m_eType;
	STRING			m_strArg;		/* 参数 */

	int32				m_nCurCount;	/* 当前执行的次数，用于显示次数 */

	CTimeEvent (void)
	{
		Clear();
	};

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void Clear(void)
	{
		/*
		 * m_strIndex = "none";
		 * m_nIndex = -1;
		 */
		m_uCurTime = 0;
		m_nLoopCount = 1;
		m_bLoopRun = FALSE;
		m_strEventId = "";
		m_eType = TE_COUNT_UP;
		m_strArg = "none";
		m_nCurCount = 0;
	};
};

/*
 =======================================================================================================================
    struct GMTimeEvent
 =======================================================================================================================
 */
class CTimeEventManager :
	public Singleton<CTimeEventManager>
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 当前队列中的事件数量 */
	int32		GetTimeEventNum(void);

	/*
	 * 添加一个时间事件
	 * 索引，循环次数（多少秒），是否每次循环都执行，事件的id（事件的定义枚举），参数
	 */
	BOOL	AddTimeEvent
			(
				LPCTSTR			szIndex /* int32 nIndex */,
				int32				nLoopCount,
				BOOL			bLoopRun,
				LPCTSTR			szEventId,
				TimeEventType	eType,
				LPCTSTR			szArg = "none"
			);

	/*
	 * BOOL AddTimeEvent( int32 nIndex, int32 nLoopCount, BOOL bLoopRun, int32 nEventId,
	 * TimeEventType eType, LPCTSTR szArg = "none" );
	 * ;
	 * 根据索引删除一个时间事件
	 */
	int32	GetRemainTime(LPCTSTR szEventIndex);

	BOOL	RemoveTimeEvent(LPCTSTR szEventIndex);

	/* 删除全部的时间事件 */
	void	RemoveAllTimeEvent(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CTimeEventManager(void);
	virtual						~CTimeEventManager(void);

	static CTimeEventManager	&GetSingleton(void);
	static CTimeEventManager	*GetSingletonPtr(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 节点 */
	virtual KHAN_RETURN_RESULT	Initialize(void);

	/*  */
	virtual KHAN_RETURN_RESULT	Update(void);

	/* 释放 */
	virtual void				Release(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/*
	 * 事件列表 ;
	 * typedef std::list< CTimeEvent* > LIST_TIMEEVENT;
	 * LIST_TIMEEVENT m_lTimeEvent;
	 */
	typedef std::map<STRING, CTimeEvent *>	MAP_TIMEEVENT;
	MAP_TIMEEVENT m_mapTimeEvent;
};	/* class CTimeEventManager */
#define TIME_EVENT_MANAGER		CTimeEventManager::GetSingleton()
#define TIME_EVENT_MANAGER_PTR	CTimeEventManager::GetSingletonPtr()
#endif /* _KHAN_TIME_COMMAND_H_ */
