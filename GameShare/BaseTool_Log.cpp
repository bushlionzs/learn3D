#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "Util.h"
#include "BaseTool.h"

#if ( defined(__LINUX__) && (defined(__MAPSERVER__) || defined(__GLSERVER__)) )
#include "udpsender.h"
extern CUdpSender g_UdpSender;
#endif

namespace	QLogSystem
{
	FastLock	__logger_guard__;
	FastLock	__connector_log_guard__;
	int32		__print_log__ = 1;
	int32		__active_log__ = 1;
	BOOL		__allinone_log__ = FALSE;

#ifdef _LOG_GL
	const char	*__overflowLogName = "./Log/Log_GLServer_All";
#elif _LOG_SV
	const char	*__overflowLogName = "./Log/Log_MapServer_All";
#elif _LOG_SM
	const char	*__overflowLogName = "./Log/Log_DBShare_All";
#else
	const char	*__overflowLogName = "./Log/Log_Default_All";
#endif

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QUICK_LOG(int32 eChannel, const char *cszFormat, ...)
	{
		__GUARD__;
		if(__active_log__ != 1) return;
		if(eChannel < 0 || eChannel >= QUICK_LOG_NUMBER) return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szBuff[ciLog_Temp_Buff] = { 0 };
		char	szLogBuff[ciLog_Temp_Buff] = { 0 };
		va_list argptr;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		_NET_TRY
		{
			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

			if(__allinone_log__)
			{
				QLogSystem::SLOW_LOG(__overflowLogName, szBuff);
				return;
			}

			GET_TIME().Update();

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szTime[ciLog_Temp_Name] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tsnprintf
				(
				szTime,
				ciLog_Temp_Name - 1,
				"(%.2d:%.2d:%.2d %.3f %lu)",
				GET_TIME().hour(),
				GET_TIME().minute(),
				GET_TIME().second(),
				(float) (GET_TIME().TickCount()) / 1000.0,
				KGetCurrentTID()
				);
			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s %s\n", szTime, szBuff);
		}

		_NET_CATCH
		{
			if(__print_log__) printf("ERROR: QUICK LOG UNKNOWN ERROR!\n");
			return;
		}

		QLogger::instance().cache_log(eChannel, szLogBuff);

		__UNGUARD__;
	}

	void QUICK_LOG_DB(int32 eChannel, const char *cszFormat, ...)
	{
		__GUARD__;
		if(__active_log__ != 1) return;
		if(eChannel < 0 || eChannel >= QUICK_LOG_NUMBER) return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szBuff[ciLog_Temp_Buff] = { 0 };
		char	szLogBuff[ciLog_Temp_Buff] = { 0 };
		va_list argptr;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		_NET_TRY
		{
			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

			if(__allinone_log__)
			{
				QLogSystem::SLOW_LOG(__overflowLogName, szBuff);
				return;
			}

			GET_TIME().Update();

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szTime[ciLog_Temp_Name] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tsnprintf
				(
					szTime,
					ciLog_Temp_Name - 1,
					"%.4d-%.2d-%.2d %.2d:%.2d:%.2d,%.3f,%lu",
					GET_TIME().year(),
					GET_TIME().month(),
					GET_TIME().day(),
					GET_TIME().hour(),
					GET_TIME().minute(),
					GET_TIME().second(),
					(float) (GET_TIME().TickCount()) / 1000.0,
					KGetCurrentTID()
				);
			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s,%s\n", szTime, szBuff);
		}

		_NET_CATCH
		{
			if(__print_log__) printf("ERROR: QUICK LOG UNKNOWN ERROR!\n");
			return;
		}

		QLogger::instance().cache_log(eChannel, szLogBuff);

		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void SLOW_LOG(const char *szLogPathName, const char *cszFormat, ...)
	{
		__GUARD__;

		if(__active_log__ != 1) 
			return;
		if(szLogPathName == NULL || szLogPathName[0] == 0) 
			return;

		char szBuff[ciLog_Temp_Buff] = { 0 };
		char szLogBuff[ciLog_Temp_Buff] = { 0 };
		
		va_list argptr;


		_NET_TRY
		{
			//组织日志字符串
			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

			GET_TIME().Update();

			char szTime[ciLog_Temp_Name] = { 0 };
			tsnprintf( szTime, ciLog_Temp_Name - 1, "(%.2d:%.2d:%.2d %.3f %lu)", 
					   GET_TIME().hour(), 
					   GET_TIME().minute(), 
					   GET_TIME().second(), 
					   (float) (GET_TIME().TickCount()) / 1000.0, 
					   KGetCurrentTID() );

			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s %s\n", szTime, szBuff);
		}
		_NET_CATCH
		{
			if(__print_log__) 
				printf("ERROR: SLOW LOG UNKNOWN ERROR!\n");
			return;
		}


		{
			//开始写日志
			lock_guard<FastLock> guard(__logger_guard__);

			_NET_TRY
			{
				//打开日志文件
				FILE *f = NULL;
				char szName[_MAX_PATH] = { 0 };

				if(__allinone_log__)
				{
					tsnprintf( szName,_MAX_PATH - 1,"%s_%.4d-%.2d-%.2d.log",
							   __overflowLogName,
							   GET_TIME().year(),
							   GET_TIME().month(),
							   GET_TIME().day() );

					f = fopen(szName, "a+");
				}
				else
				{
					tsnprintf( szName,_MAX_PATH - 1,"%s_%.4d-%.2d-%.2d.log",
							   szLogPathName,
							   GET_TIME().year(),
							   GET_TIME().month(),
							   GET_TIME().day());

					f = fopen(szName, "a+");
				}

				//打开有效,写日志
				if(f)
				{
					_NET_TRY
					{
						fwrite(szLogBuff, 1, strlen(szLogBuff), f);
					}
					_NET_CATCH
					{
					}

					fclose(f);
				}
			}
			_NET_CATCH
			{
			}
		}

		if(TRUE == __print_log__) 
			printf("%s", szLogBuff);

		__UNGUARD__
	}

	void SLOW_LOG_DB(const char *szLogPathName, const char *cszFormat, ...)
	{
		__GUARD__;

		if(__active_log__ != 1) 
			return;
		if(szLogPathName == NULL || szLogPathName[0] == 0) 
			return;

		char szBuff[ciLog_Temp_Buff] = { 0 };
		char szLogBuff[ciLog_Temp_Buff] = { 0 };
		
		va_list argptr;


		_NET_TRY
		{
			//组织日志字符串
			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

			GET_TIME().Update();

			char szTime[ciLog_Temp_Name] = { 0 };
			tsnprintf( 
						szTime, 
						ciLog_Temp_Name - 1, "\"%.4d-%.2d-%.2d %.2d:%.2d:%.2d\",%.3f,%lu",
						GET_TIME().year(),
						GET_TIME().month(),
						GET_TIME().day(),
						GET_TIME().hour(), 
						GET_TIME().minute(), 
						GET_TIME().second(), 
						(float) (GET_TIME().TickCount()) / 1000.0, 
						KGetCurrentTID() 
					);

			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s,%s\n", szTime, szBuff);
		}
		_NET_CATCH
		{
			if(__print_log__) 
				printf("ERROR: SLOW LOG UNKNOWN ERROR!\n");
			return;
		}


		{
			//开始写日志
			lock_guard<FastLock> guard(__logger_guard__);

			_NET_TRY
			{
				//打开日志文件
				FILE *f = NULL;
				char szName[_MAX_PATH] = { 0 };

				if(__allinone_log__)
				{
					tsnprintf( szName,_MAX_PATH - 1,"%s_%.4d-%.2d-%.2d.log",
							   __overflowLogName,
							   GET_TIME().year(),
							   GET_TIME().month(),
							   GET_TIME().day() );

					f = fopen(szName, "a+");
				}
				else
				{
					tsnprintf( szName,_MAX_PATH - 1,"%s_%.4d-%.2d-%.2d.log",
							   szLogPathName,
							   GET_TIME().year(),
							   GET_TIME().month(),
							   GET_TIME().day() );

					f = fopen(szName, "a+");
				}

				//打开有效,写日志
				if(f)
				{
					_NET_TRY
					{
						fwrite(szLogBuff, 1, strlen(szLogBuff), f);
					}
					_NET_CATCH
					{
					}

					fclose(f);
				}
			}
			_NET_CATCH
			{
			}
		}

		if(TRUE == __print_log__) 
			printf("%s", szLogBuff);

		__UNGUARD__
	}

	void CONNECTOR_LOG(const char *cszFormat, ...)
	{
		__GUARD__

		char	szBuff[ciLog_Temp_Buff] = { 0 };
		char	szLogBuff[ciLog_Temp_Buff] = { 0 };
		char	szPostFix[16] = { 0 };
		char	szName[_MAX_PATH] = { 0 };
		va_list argptr;

		_NET_TRY
		{
			GET_TIME().Update();

			lock_guard<FastLock> guard(__connector_log_guard__);

			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

#if defined(_70_CLIENT) && defined(_70_LOGIN)
			tsnprintf_s(szPostFix, 16, "login");
#elif defined(_70_CLIENT) && defined(_70_SERVER)
			tsnprintf_s(szPostFix, 16, "map");
#elif defined(_70_SERVER) && defined(_70_WORLD)
			tsnprintf_s(szPostFix, 16, "gl");
#elif defined(_70_DBCENTER) && defined(_70_LOGIN)
			tsnprintf_s(szPostFix, 16, "dbc");
#elif defined(_70_DBCENTER) && defined(_70_SHAREMEM)
			tsnprintf_s(szPostFix, 16, "sm");
#endif

			tsnprintf
			(
				szName,
				_MAX_PATH - 1,
				"./Log/connector_%s_%.4d-%.2d-%.2d.log",
				szPostFix,
				GET_TIME().year(),
				GET_TIME().month(),
				GET_TIME().day()
			);


			char szTime[ciLog_Temp_Name] = { 0 };
			tsnprintf
				(
				szTime,
				ciLog_Temp_Name - 1,
				"(%.2d:%.2d:%.2d %.3f %lu)",
				GET_TIME().hour(),
				GET_TIME().minute(),
				GET_TIME().second(),
				(float) (GET_TIME().TickCount()) / 1000.0,
				KGetCurrentTID()
				);
			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s %s\n", szTime, szBuff);

			FILE* f = fopen(szName, "a");
			if(f)
			{
				fwrite(szLogBuff, 1, strlen(szLogBuff), f);
				fclose(f);
			}
		}
		_NET_CATCH
		{
			printf("ERROR: CONNECTOR LOG UNKNOWN ERROR!\n");
			return;
		}

		if(TRUE == __print_log__) 
			printf("%s", szLogBuff);

		__UNGUARD__
	}

	void SLOW_LOG_RAW(const char * szFileName, const char *cszFormat, ...)
	{
		__GUARD__

		char	szBuff[ciLog_Temp_Buff] = { 0 };
		char	szTime[ciLog_Temp_Name] = { 0 };
		char	szLogBuff[ciLog_Temp_Buff] = { 0 };
		va_list argptr;

		_NET_TRY
		{
			GET_TIME().Update();
			lock_guard<FastLock> guard(__logger_guard__);
			va_start(argptr, cszFormat);
			tvsnprintf(szBuff, ciLog_Temp_Buff - ciLog_Temp_Name - 1, cszFormat, argptr);
			va_end(argptr);

			tsnprintf
				(
				szTime,
				ciLog_Temp_Name - 1,
				"%.4d%.2d%.2d_%.2d:%.2d:%.2d",
				GET_TIME().year(),
				GET_TIME().month(),
				GET_TIME().day(),
				GET_TIME().hour(),
				GET_TIME().minute(),
				GET_TIME().second()
				);

			tsnprintf_s(szLogBuff, ciLog_Temp_Buff, "%s %s\n", szTime, szBuff);

			FILE* f = fopen(szFileName, "a");
			if(f)
			{
				fwrite(szLogBuff, 1, strlen(szLogBuff), f);
				fclose(f);
			}
		}
		_NET_CATCH
		{
			return;
		}

		if(TRUE == __print_log__) 
			printf("%s", szLogBuff);

		__UNGUARD__
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	QLogger &QLogger::instance(void)
	{
		/*~~~~~~~~~~~~~~~~~~~*/
		static QLogger	s_qlog;
		/*~~~~~~~~~~~~~~~~~~~*/

		return s_qlog;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	QLogger::QLogger()
	{
		__GUARD__;
		for(int32 i = 0; i < QUICK_LOG_NUMBER; i++)
		{
			m_pMemoryLog[i] = NULL;
			m_WritePos[i] = 0;
			m_szLogPath[i] = NULL;
			m_Flag_DBFormat[i] = 0;
		}

		m_pSaveLog = NULL;
		m_MemorySize = 0;
		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	QLogger::~QLogger(void)
	{
		__GUARD__;
		for(int32 i = 0; i < QUICK_LOG_NUMBER; i++)
		{
			KSafeDelete_ARRAY(m_pMemoryLog[i]);
			m_WritePos[i] = 0;
			KSafeDelete_ARRAY(m_szLogPath[i]);
		}

		KSafeDelete_ARRAY(m_pSaveLog);
		m_MemorySize = 0;
		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	BOOL QLogger::Init(int32 cachesize)
	{
		__GUARD__;
		if(0 < cachesize)
			m_MemorySize = cachesize;
		else
			m_MemorySize = ciDefault_Log_Cache_Size;
		for(int32 i = 0; i < QUICK_LOG_NUMBER; i++)
		{
			m_pMemoryLog[i] = new char[m_MemorySize];
			if(m_pMemoryLog[i] == NULL) return FALSE;
			memset(m_pMemoryLog[i], 0, m_MemorySize);
			m_WritePos[i] = 0;
		}

		m_pSaveLog = new char[m_MemorySize];
		if(m_pSaveLog == NULL) return FALSE;
		memset(m_pSaveLog, 0, m_MemorySize);

		RegisterAllLogPath();

		return TRUE;
		__UNGUARD__;
		return FALSE;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::RegisterAllLogPath()
	{
		__GUARD__

		RegisterLogPath( QUICK_LOG_LOGIN,			"./Log/login",			0 );
		RegisterLogPath( QUICK_LOG_DEBUG,			"./Log/debug",			0 );
		RegisterLogPath( QUICK_LOG_ERROR,			"./Log/errors",			0 );
		RegisterLogPath( QUICK_LOG_FUNCTION,		"./Log/functions",		0 );
		RegisterLogPath( QUICK_LOG_WORLD,			"./Log/world",			0 );
		RegisterLogPath( QUICK_LOG_ITEMCHANGE,		"./Log/db/itemchange",	1 );
		RegisterLogPath( QUICK_LOG_SEND,			"./Log/send",			0 );
		RegisterLogPath( QUICK_LOG_MONEYCHANGE,		"./Log/db/moneychange",	1 );
		RegisterLogPath( QUICK_LOG_PET,				"./Log/db/pet",			1 );
		RegisterLogPath( QUICK_LOG_SKILL,			"./Log/db/skill",		1 );
		RegisterLogPath( QUICK_LOG_ABILITY,			"./Log/db/ability",		1 );
		RegisterLogPath( QUICK_LOG_CHAT,			"./Log/chat",			0 );
		RegisterLogPath( QUICK_LOG_QUEST,			"./Log/quest",			0 );
		RegisterLogPath( QUICK_LOG_TRADE,			"./Log/db/trade",		1 );
		RegisterLogPath( QUICK_LOG_IB,				"./Log/db/ib",			1 );
		RegisterLogPath( QUICK_LOG_GAMEWAY,			"./Log/db/GamePlay",	1 );
		RegisterLogPath( QUICK_LOG_PRIZE,			"./Log/db/Award",		1 );
		RegisterLogPath( QUICK_LOG_GM,				"./Log/db/GM",			1 );
		RegisterLogPath( QUICK_LOG_EQUIP,			"./Log/db/EquipExtra",	1 );
		RegisterLogPath( QUICK_LOG_MAPWORLDSHOP,	"./Log/db/MapWorldShop",1 );
		RegisterLogPath( QUICK_LOG_CSIE,			"./Log/CSIllegalEnter",	0 );
		RegisterLogPath( QUICK_LOG_MAPLAWLESSOP,	"./Log/db/MapLawlessOp",1 );
		RegisterLogPath( QUICK_LOG_IBMONEY,			"./Log/db/ibmoneylog",	1 );
		RegisterLogPath( QUICK_LOG_IBCOST,			"./Log/db/ibcostlog",	1 );
		RegisterLogPath( QUICK_LOG_MAPSTOCKACC,		"./Log/db/MapStockAcc",	1 );
		RegisterLogPath( QUICK_LOG_PET_RETURN,		"./Log/db/petreturn",	1 );
		RegisterLogPath( QUICK_LOG_PET_SKILL,		"./Log/db/petskill",	1 );
		RegisterLogPath( QUICK_LOG_ZHUANJING,		"./Log/db/zhuanjing",	1 );


		__UNGUARD__
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::RegisterLogPath(int32 eChannel, const char* szPath,uchar flag)
	{
		__GUARD__
		KCheck( eChannel>=0 && eChannel<QUICK_LOG_NUMBER );
		uint32 uSize = (uint32)strlen(szPath)+1;
		m_szLogPath[eChannel] = new char[uSize];
		KCheck(m_szLogPath[eChannel]);
		memset(m_szLogPath[eChannel],0,uSize);
		strncpy( m_szLogPath[eChannel], szPath, uSize-1 );
		m_Flag_DBFormat[eChannel] = flag;

		__UNGUARD__
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::cache_log(int32 eChannel, char *szMsg)
	{
		__GUARD__;
		if(__active_log__ != 1) return;
		if(eChannel < 0 || eChannel >= QUICK_LOG_NUMBER) return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLen = (int32) strlen(szMsg);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iLen <= 0) return;

		if(m_WritePos[eChannel] > (m_MemorySize - iLen - 4096))
		{
			_NET_TRY
			{
				char	szLogName[256] = { 0 };
				GetChannelName(eChannel, szLogName);
				strcat( szLogName, ".discard" );

				FILE	*f = fopen(szLogName, "a+");
				if(f)
				{
					_NET_TRY
					{
						fwrite(szMsg, 1, strlen(szMsg), f);
					}

					_NET_CATCH
					{
					}

					fclose(f);
				}
			}

			_NET_CATCH
			{
			}

			return;
		}
		{
			lock_guard<FastLock> guard(m_channelLock[eChannel]);

			_NET_TRY
			{
				memcpy(m_pMemoryLog[eChannel] + m_WritePos[eChannel], szMsg, iLen);
				m_WritePos[eChannel] += iLen;

				if( eChannel==QUICK_LOG_IBMONEY || eChannel==QUICK_LOG_IBCOST )
				{
#if ( defined(__LINUX__) && (defined(__MAPSERVER__) || defined(__GLSERVER__)) )
					if( g_Config.m_LogServerInfo.m_bEnable == 1 )
					{
						char szSend[1024] = {0};
						uint16 uLen = (uint16)iLen;
						uchar eType = (uchar)eChannel;
						memcpy( szSend, &eType, sizeof(uchar) );
						memcpy( szSend+sizeof(uchar), &uLen, sizeof(uint16) );
						memcpy( szSend+sizeof(uchar)+sizeof(uint16), szMsg, uLen ); 
						g_UdpSender.Send(szSend,uLen+sizeof(uchar)+sizeof(uint16));
					}
#endif
				}
			}

			_NET_CATCH
			{
			}
		}

		showmsg(szMsg);
		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::showmsg(const char *cszMsg)
	{
		__GUARD__;
		if(TRUE == __print_log__) printf("%s", cszMsg);
		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::GetChannelName(int32 channel, char *szName)
	{
		__GUARD__;
		if(channel < 0 || channel >= QUICK_LOG_NUMBER || !szName) return;
		uchar flag = m_Flag_DBFormat[channel];
		memset(szName, 0, _MAX_PATH);

		if( 1 )//flag == 0 )
		{
			tsnprintf
				(
				szName,
				_MAX_PATH - 1,
				"%s_%.4d-%.2d-%.2d.log",
				m_szLogPath[channel],
				GET_TIME().year(),
				GET_TIME().month(),
				GET_TIME().day()
				);
		}
		else
		{
			tsnprintf
				(
				szName,
				_MAX_PATH - 1,
				"%s_%.4d-%.2d-%.2d-%.2d.log",
				m_szLogPath[channel],
				GET_TIME().year(),
				GET_TIME().month(),
				GET_TIME().day(),
				GET_TIME().hour()
				);			
		}

		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::Update(int32 channel)
	{
		__GUARD__;

		/*~~~~~~~~~~~~~~~~~~~~~~*/
		char	szName[_MAX_PATH];
		/*~~~~~~~~~~~~~~~~~~~~~~*/

		GetChannelName(channel, szName);

		/*~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nNeedSaveSize = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~*/
		{
			lock_guard<FastLock> guard(m_channelLock[channel]);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	*pTemp = m_pMemoryLog[channel];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			m_pMemoryLog[channel] = m_pSaveLog;
			m_pSaveLog = pTemp;
			nNeedSaveSize = m_WritePos[channel];
			m_WritePos[channel] = 0;
		}

		_NET_TRY
		{
			if(nNeedSaveSize == 0) return;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			FILE	*f = fopen(szName, "a+");
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(f)
			{
				_NET_TRY
				{
					fwrite(m_pSaveLog, 1, nNeedSaveSize, f);
				}

				_NET_CATCH
				{
				}

				fclose(f);
			}
		}

		_NET_CATCH
		{
		}

		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void QLogger::UpdateAll()
	{
		__GUARD__;
		for(int32 i = 0; i < QUICK_LOG_NUMBER; i++) Update(i);
		__UNGUARD__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	BOOL __get_logger_guard_state(void)
	{
		return __logger_guard__.mStatus;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void __open_print_log(BOOL bIsOpen)
	{
		__print_log__ = bIsOpen;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	BOOL __is_open_print_log(void)
	{
		return __print_log__;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	void __open_allinone(BOOL bIsOpen)
	{
		__allinone_log__ = bIsOpen;
	}

	/*
	=======================================================================================================================
	=======================================================================================================================
	*/
	BOOL __is_open_allinone(void)
	{
		return __allinone_log__;
	}
}	/* namespace QLogSystem end . */