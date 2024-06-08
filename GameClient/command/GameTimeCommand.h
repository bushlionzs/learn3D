#ifndef _KHAN_TIME_COMMAND_H_
#define _KHAN_TIME_COMMAND_H_
#include <OgreSingleton.h>
enum TimeEventType { TE_COUNT_UP = 0,			 /* ����ʱ */ TE_COUNT_DOWN,				  /* ����ʱ */ };
struct CTimeEvent
{
	/*
	 * ���������ֻ����� ;
	 * STRING m_strIndex;
	 * // ;
	 * int32 m_nIndex;
	 * //
	 */
	UINT64			m_uCurTime;		/* ��ǰ��ʱ�� ���� */
	int32				m_nLoopCount;	/* ѭ������ ����Ϊ��λ */
	BOOL			m_bLoopRun;		/* ���ִ�У���ÿ��ִ��һ�� */
	STRING			m_strEventId;	/* �¼�id */
	TimeEventType	m_eType;
	STRING			m_strArg;		/* ���� */

	int32				m_nCurCount;	/* ��ǰִ�еĴ�����������ʾ���� */

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
	/* ��ǰ�����е��¼����� */
	int32		GetTimeEventNum(void);

	/*
	 * ���һ��ʱ���¼�
	 * ������ѭ�������������룩���Ƿ�ÿ��ѭ����ִ�У��¼���id���¼��Ķ���ö�٣�������
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
	 * ��������ɾ��һ��ʱ���¼�
	 */
	int32	GetRemainTime(LPCTSTR szEventIndex);

	BOOL	RemoveTimeEvent(LPCTSTR szEventIndex);

	/* ɾ��ȫ����ʱ���¼� */
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
	/* �ڵ� */
	virtual KHAN_RETURN_RESULT	Initialize(void);

	/*  */
	virtual KHAN_RETURN_RESULT	Update(void);

	/* �ͷ� */
	virtual void				Release(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/*
	 * �¼��б� ;
	 * typedef std::list< CTimeEvent* > LIST_TIMEEVENT;
	 * LIST_TIMEEVENT m_lTimeEvent;
	 */
	typedef std::map<STRING, CTimeEvent *>	MAP_TIMEEVENT;
	MAP_TIMEEVENT m_mapTimeEvent;
};	/* class CTimeEventManager */
#define TIME_EVENT_MANAGER		CTimeEventManager::GetSingleton()
#define TIME_EVENT_MANAGER_PTR	CTimeEventManager::GetSingletonPtr()
#endif /* _KHAN_TIME_COMMAND_H_ */
