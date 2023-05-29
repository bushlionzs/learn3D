
#ifndef __BASETOOL_H__
#define __BASETOOL_H__

////////////////////////////////////////////////////////////////////////////////
// Time Module
////////////////////////////////////////////////////////////////////////////////
#include "TypeDefine.h"
#ifdef __LINUX__
#include <sys/utsname.h>
#include <sys/time.h>
#endif
class	TimeSystem
{
	TimeSystem(void);
	~TimeSystem(void);

public:
	static TimeSystem	&instance(void);

	BOOL				Init();

public:
	uint32				TickCount();
	uint32				NowSavedTime() const { return m_Now; }
	uint32				OrigineTime() const { return m_Begin; }
	void				Update() const;
	uint32				GetCTime() const;
	uint32				RefixANSITimeByTimeZone(uint32 uTime) const;

public:
	int32				year() const { return m_TM.tm_year + 1900; }
	int32				month() const { return m_TM.tm_mon + 1; }
	int32				day() const { return m_TM.tm_mday; }
	int32				hour() const { return m_TM.tm_hour; }
	int32				minute() const { return m_TM.tm_min; }
	int32				second() const { return m_TM.tm_sec; }
	uint32				week() const { return m_TM.tm_wday; }

	uint32				Time2DWORD() const;
	uint32				CurrentDate() const;
	uint32				DiffTime(uint32 Date1, uint32 Date2) const;

	void				ConvertUT(uint32 Date, tm *TM) const;
	void				ConvertTU(tm *TM, uint32 &Date) const;
	uint32				GetDayTime();

private:
	uint32				m_Begin;
	mutable uint32		m_Now;
	mutable time_t		m_TimeT;
	mutable tm			m_TM;

#ifdef __LINUX__
	struct timeval		_tstart, _tend;
	struct timezone		tz;
#endif

	void				_CurrentTime();
};

#define INIT_TIMESYSTEM()	TimeSystem::instance().Init()
#define GET_TIME()			TimeSystem::instance()

////////////////////////////////////////////////////////////////////////////////
// Log Module
////////////////////////////////////////////////////////////////////////////////
enum
{
	QUICK_LOG_LOGIN		= 0,
	QUICK_LOG_DEBUG		= 1,
	QUICK_LOG_ERROR		= 2,
	QUICK_LOG_FUNCTION	= 3,
	QUICK_LOG_WORLD		= 4,
	QUICK_LOG_ITEMCHANGE	= 5,
	QUICK_LOG_SEND		= 6,
	QUICK_LOG_MONEYCHANGE	= 7,
	QUICK_LOG_PET		= 8,
	QUICK_LOG_SKILL		= 9,
	QUICK_LOG_ABILITY	= 10,
	QUICK_LOG_CHAT		= 11,
	QUICK_LOG_QUEST		= 12,
	QUICK_LOG_TRADE		= 13,
	QUICK_LOG_IB		= 14,
	QUICK_LOG_GAMEWAY	= 15,
	QUICK_LOG_PRIZE		= 16,
	QUICK_LOG_GM		= 17,
	QUICK_LOG_EQUIP		= 18,
	QUICK_LOG_MAPWORLDSHOP	= 19,
	QUICK_LOG_CSIE		= 20,
	QUICK_LOG_MAPLAWLESSOP	= 21,
	QUICK_LOG_IBMONEY	= 22,
	QUICK_LOG_IBCOST	= 23,
	QUICK_LOG_MAPSTOCKACC	= 24,	//存储用户股票账户信息
	QUICK_LOG_PET_RETURN	= 25,	//
	QUICK_LOG_PET_SKILL		= 26,	//
	QUICK_LOG_ZHUANJING		= 27,	//存储专精获得信息
	QUICK_LOG_NUMBER,
};

namespace QLogSystem
{
	void	QUICK_LOG(int32, const char *cszFormat, ...);
	void	SLOW_LOG(const char *, const char *cszFormat, ...);
	void	CONNECTOR_LOG(const char *cszFormat, ...);
	void	QUICK_LOG_DB(int32, const char *cszFormat, ...);
	void	SLOW_LOG_DB(const char *, const char *cszFormat, ...);
	void	SLOW_LOG_RAW(const char * szFileName, const char *cszFormat, ...);	//写服务器状态log，格式满足运营需求

	class	nonecopy
	{
	public:
		nonecopy() {}
		~nonecopy() {}

	private:

		nonecopy(const nonecopy &) {}
		const nonecopy &operator=(const nonecopy &) {}
	};

	class QLogger :
		nonecopy
	{

	private:
		QLogger(void);
		~QLogger(void);
	
	public:
		static QLogger	&instance(void);

		BOOL			Init(int32 cachesize);
		void			RegisterAllLogPath();
		void			RegisterLogPath(int32 eChannel, const char* szPath,uchar flag);
		void			cache_log(int32, char *msg);
		void			Update(int32 logid);
		void			UpdateAll(void);
		void			GetChannelName(int32 channel, char *szName);

	protected:
		void			showmsg(const char *cszMsg);

	private:
		char			*m_pMemoryLog[QUICK_LOG_NUMBER];
		int32			m_MemorySize;
		int32			m_WritePos[QUICK_LOG_NUMBER];
		FastLock		m_channelLock[QUICK_LOG_NUMBER];
		char			*m_szLogPath[QUICK_LOG_NUMBER];
		uchar			m_Flag_DBFormat[QUICK_LOG_NUMBER];
		char			*m_pSaveLog;
	};

	static const int32	ciDefault_Log_Cache_Size = 1024 * 1024 * 4;
	static const int32	ciLog_Temp_Buff = 4096;
	static const int32	ciLog_Temp_Name = 128;

	BOOL				__get_logger_guard_state(void);
	void				__open_print_log(BOOL bIsOpen);
	BOOL				__is_open_print_log(void);
	void				__open_allinone(BOOL bIsOpen);
	BOOL				__is_open_allinone(void);
}

#if defined(__LINUX__)
#define QLOGGER_CODEHOLDER() \
	(QLogSystem::SLOW_LOG(SLOW_LOG_SERVERERROR, "%s %d %s", __FILE__, __LINE__, __PRETTY_FUNCTION__))
#define QLOGGER_PACKETCODEHOLDER(x) \
	( \
	QLogSystem::SLOW_LOG \
	( \
	SLOW_LOG_SERVERERROR, \
	"f:%s l:%d p:%d %s", \
	__FILE__, \
	__LINE__, \
	x, \
	__PRETTY_FUNCTION__ \
	) \
	)
#else
#define QLOGGER_CODEHOLDER()	(QLogSystem::SLOW_LOG(SLOW_LOG_SERVERERROR, "%s %d %s", __FILE__, __LINE__, __FUNCTION__))
#define QLOGGER_PACKETCODEHOLDER(x) \
	(QLogSystem::SLOW_LOG(SLOW_LOG_SERVERERROR, "f:%s l:%d p:%d %s", __FILE__, __LINE__, x, __FUNCTION__))
#endif

#define QLOGGER_GUARD_STATE		QLogSystem::__get_logger_guard_state()
#define QLOGGER_INITIALIZE()		QLogSystem::QLogger::instance().Init(QLogSystem::ciDefault_Log_Cache_Size)
#define QLOGGER_UPDATE()		QLogSystem::QLogger::instance().UpdateAll()
#define QLOGGER_PRINTLOG_OPEN()		QLogSystem::__open_print_log(TRUE)
#define QLOGGER_PRINTLOG_CLOSE()	QLogSystem::__open_print_log(FALSE)
#define QLOGGER_PRINTLOG_ISOPEN()	QLogSystem::__is_open_print_log()
#define QLOGGER_ALLINONE_OPEN()		QLogSystem::__open_allinone(TRUE)
#define QLOGGER_ALLINONE_CLOSE()	QLogSystem::__open_allinone(FALSE)
#define QLOGGER_ALLINONE_ISOPEN()	QLogSystem::__is_open_allinone()

static const char	*SLOW_LOG_AIDEBUG = "./Log/AIDebug";
static const char	*SLOW_LOG_LOGIN = "./Log/Login";
static const char	*SLOW_LOG_LOGIN_COUNT = "./Log/LoginCount";
static const char	*SLOW_LOG_SERVER = "./Log/Mapserver";
static const char	*SLOW_LOG_RECONNECT = "./Log/Reconnect";
static const char	*SLOW_LOG_MSGERROR = "./Log/MsgError";
static const char	*SLOW_LOG_SERVERERROR = "./Log/Error";
static const char	*SLOW_LOG_SERVERFUNC = "./Log/Functions";
static const char	*SLOW_LOG_WORLD = "./Log/GLserver";
static const char	*SLOW_LOG_CONFIG = "./Log/Config";
static const char	*SLOW_LOG_ASSERT = "./Log/KCheck";
static const char	*SLOW_LOG_RECYCLEPLAYER = "./Log/Recycle";
static const char	*SLOW_LOG_MAPSERVER_SHAREMEM = "./Log/Mapsharemem";
static const char	*SLOW_LOG_GL_SHAREMEM = "./Log/GLsharemem";
static const char	*SLOW_LOG_GL_DBCENTER = "./Log/DBCenter";
static const char	*SLOW_LOG_DBSAVE = "./Log/DBSaveLog";
static const char	*SLOW_LOG_ONLINE_USR_CNT = "./Log/onlineuser";
static const char	*SLOW_LOG_DEAMON = "./Log/Deamon";
static const char	*SLOW_LOG_WORLDCHAT = "./Log/WorldChat";
static const char	*SLOW_LOG_CLIENT_ERROR_REPORT = "./Log/ClientErrorReport";
static const char	*SLOW_LOG_GL_WORLD_SHOP = "./Log/db/GLWorldShop";
static const char	*SLOW_LOG_LOGIN_LAWLESS_OP = "./Log/db/LoginLawlessOp";
static const char	*SLOW_LOG_GL_STOCK_TRADE = "./Log/db/GLStockTrade";
static const char	*SLOW_LOG_GL_STOCK_ACC = "./Log/db/GLStockAcc";
static const char	*SLOW_LOG_GL_GUILD = "./Log/db/GLGuild"; 
static const char	*SLOW_LOG_GL_IBMONEY = "./Log/db/ibmoneylog"; 
static const char	*SLOW_LOG_GL_IBCOST = "./Log/db/ibcostlog"; 
static const char	*SLOW_LOG_MAPSERVER_USAGE = "./Log/MapUsage";
static const char	*SLOW_LOG_MSG_RECORD = "./Log/MsgRecord";
static const char	*SLOW_LOG_SKILL = "./Log/db/skill";
// ... (Billing) -->
static const char	*SLOW_LOG_BILLING = "./Log/Billing";
// <--


////////////////////////////////////////////////////////////////////////////////
// Thread Module
////////////////////////////////////////////////////////////////////////////////
enum ThreadStep { ts_0, ts_1, ts_2, ts_3, ts_4, ts_5, ts_6, ts_7, ts_8, ts_9, };
class KThread
{
public:
	enum RunState { THREAD_READY, THREAD_RUNNING, THREAD_EXITING, THREAD_FINISH };

public:
	KThread();
	virtual ~KThread();

public:
	void			start();
	virtual void	stop();
	void			exit(void *retval = NULL);
	virtual void	run();

public:

	TID				getTID() { return m_TID; }
	RunState		getState() { return m_Status; }
	void			setState(RunState status) { m_Status = status; }
	int32			getTickCount() { return m_TickCount; }
	int32			getSteps() { return m_Steps; }
	
	virtual	BOOL	getInit() 
	{
		return FALSE;
	}

private:
	TID		m_TID;
	RunState	m_Status;

#if defined(__WINDOWS__)
	HANDLE		m_hThread;
#endif

protected:
	int32	m_TickCount;
	int32	m_Steps;
};

extern uint32	g_ThreadCount;
extern uint32	g_WaitQuitThreadCount;

#if defined(__LINUX__)
void		*ThreadEntry(void *derivedThread);
#elif defined(__WINDOWS__)
ulong WINAPI	ThreadEntry(void *derivedThread);
#endif


////////////////////////////////////////////////////////////////////////////////
// Configer Module
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <fstream>
#include <map>

typedef std::map<std::string,int>							ConfigerValueHashMap;
typedef std::map<std::string,ConfigerValueHashMap* >		ConfigerSectionHashMap;

#define CONFIGER_BUF_SIZE		1024
#define CONFIGER_NOTE			(';')

class Configer
{
public:
	Configer();
	Configer(const char* filename);
	virtual ~Configer();

	BOOL	Open(const char* filename);
	void	Close();

	int32	Get_Property_Int( const char *section, const char *key, int32 nDefault=0 );
	BOOL	GetIntIfExist(const char *section, const char *key, int32& nResult );
	float	GetFloat(const char *section, const char *key, float fDefault=0.0f );
	BOOL	GetFloatIfExist(const char *section, const char *key, float& fResult );
	BOOL	GetText(const char *section, const char *key, char *str, int32 size, const char* strDefault="" );
	BOOL	GetTextIfExist(const char *section, const char *key, char *str, int32 size );

private:
	BOOL	_GetInt(const char *section, const char *key, int32& nResult );
	BOOL	_GetFloat(const char *section, const char *key, float& fResult );
	BOOL	_GetText(const char *section, const char *key, char *str, int32 size );
	void	_TrimString( char* buf );
	BOOL	_ParseSection( char* buf, char** pSection );
	BOOL	_ParseKey( char* buf, char** sKey, char** sValue );
	void	_ResizeBuf();
	char*	_GetBufString(int32 nPos);
	int32	_AddBufString(char* str);

private:
	std::ifstream				m_ifile;
	char						m_szFileName[MAX_FILE_PATH];
	ConfigerSectionHashMap		m_SectionData;
	ConfigerValueHashMap*		m_pCurSection;
	char*						m_pBuf;
	int32						m_nBufLen;
	int32						m_nBufMaxLen;
};

#endif

