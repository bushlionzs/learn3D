/*$T Common/Debug.cpp GC 1.140 10/10/07 10:06:26 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Debug.h"
#include "TypeDefine.h"
#include <time.h>
#include "Util.h"

#ifdef __LINUX__
#include <execinfo.h>
#endif
int32	__assert_state = 0;
int32	__message_state = FALSE;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _KMessage(const char *szTemp)
{
#ifdef __LINUX__
	printf("KCheck:%s", szTemp);
#endif
#ifndef GAME_CLIENT
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szPostFix[16] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

		/*~~~~~~~~~~~~~~~~~~*/
		static FastLock llock;
		/*~~~~~~~~~~~~~~~~~~*/

		lock_guard<FastLock> autolock(llock);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szName[_MAX_PATH] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf
		(
			szName,
			_MAX_PATH - 1,
			"./Log/assert_%s_%.4d-%.2d-%.2d.log",
			szPostFix,
			GET_TIME().year(),
			GET_TIME().month(),
			GET_TIME().day()
		);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FILE	*f = fopen(szName, "a");
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(f)
		{
			fwrite(szTemp, 1, strlen(szTemp), f);
			fwrite("\n", 1, 1, f);
			fclose(f);
		}
	}

	while(FALSE);
#endif
#if defined(__WINDOWS__)
	{
		/*~~~~~~~~~~~~~~~~~*/
		static FastLock lock;
		/*~~~~~~~~~~~~~~~~~*/

		if(KCheckState() != 1)
		{
			lock_guard<FastLock> autolock(lock);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iRet = ::MessageBoxA(NULL, szTemp, "Òì³£", MB_OK);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		}
	}

	while(FALSE);
#elif defined(__LINUX__)
#endif
#ifdef GAME_CLIENT
	throw(std::exception(szTemp));
#else
	throw(1);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _KMB(const char *msg)
{
	if(__message_state) return;
#if defined(__WINDOWS__)
	::MessageBoxA(NULL, msg, "×´Ì¬ÐÅÏ¢", MB_OK);
#elif defined(__LINUX__)
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _Check1(const char *file, uint32 line, const char *func, const char *expr)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTemp[1024] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifdef __LINUX__
	tsnprintf(szTemp, sizeof(szTemp), "[%s][%d][%s][%s]\n", file, line, func, expr);
#else
	tsnprintf(szTemp, sizeof(szTemp), "[%s][%d][%s][%s]", file, line, func, expr);
#endif
#ifndef GAME_CLIENT
	GET_TIME().Update();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTime[QLogSystem::ciLog_Temp_Name];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(szTime, 0, QLogSystem::ciLog_Temp_Name);

	tsnprintf
	(
		szTime,
		QLogSystem::ciLog_Temp_Name - 1,
		" (%lu)(T0=%d-%d-%d_%d:%d:%d T1=%.3f)\n",
		KGetCurrentTID(),
		GET_TIME().year(),
		GET_TIME().month(),
		GET_TIME().day(),
		GET_TIME().hour(),
		GET_TIME().minute(),
		GET_TIME().second(),
		(float) (GET_TIME().TickCount()) / 1000.0
	);
	strncat(szTemp, szTime, QLogSystem::ciLog_Temp_Name - 1);
#endif
	szTemp[1023] = '\0';
	_KMessage(szTemp);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _Check2(const char *file, uint32 line, const char *func, const char *expr, const char *msg)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTemp[1024] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifdef __LINUX__
	tsnprintf(szTemp, sizeof(szTemp), "[%s][%d][%s][%s]\n[%s]\n", file, line, func, expr, msg);
#else
	tsnprintf(szTemp, sizeof(szTemp), "[%s][%d][%s][%s]\n[%s]", file, line, func, expr, msg);
#endif
#ifndef GAME_CLIENT
	GET_TIME().Update();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTime[QLogSystem::ciLog_Temp_Name];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(szTime, 0, QLogSystem::ciLog_Temp_Name);

	tsnprintf
	(
		szTime,
		QLogSystem::ciLog_Temp_Name - 1,
		" (%lu)(T0=%d-%d-%d_%d:%d:%d T1=%.3f)\n",
		KGetCurrentTID(),
		GET_TIME().year(),
		GET_TIME().month(),
		GET_TIME().day(),
		GET_TIME().hour(),
		GET_TIME().minute(),
		GET_TIME().second(),
		(float) (GET_TIME().TickCount()) / 1000.0
	);
	strncat(szTemp, szTime, QLogSystem::ciLog_Temp_Name - 1);
#endif
	szTemp[1023] = '\0';
	_KMessage(szTemp);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _Check3(const char *file, uint32 line, const char *func, const char *expr, const char *msg)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTemp[1024] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifdef __LINUX__
	tsnprintf(szTemp, sizeof(szTemp), "S[%s][%d][%s][%s]\nS[%s]\n", file, line, func, expr, msg);
#else
	tsnprintf(szTemp, sizeof(szTemp), "S[%s][%d][%s][%s]\nS[%s]", file, line, func, expr, msg);
#endif
#ifndef GAME_CLIENT
	GET_TIME().Update();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szTime[QLogSystem::ciLog_Temp_Name];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(szTime, 0, QLogSystem::ciLog_Temp_Name);

	tsnprintf
	(
		szTime,
		QLogSystem::ciLog_Temp_Name - 1,
		" (%lu)(T0=%d-%d-%d_%d:%d:%d T1=%.3f)\n",
		KGetCurrentTID(),
		GET_TIME().year(),
		GET_TIME().month(),
		GET_TIME().day(),
		GET_TIME().hour(),
		GET_TIME().minute(),
		GET_TIME().second(),
		(float) (GET_TIME().TickCount()) / 1000.0
	);
	strncat(szTemp, szTime, QLogSystem::ciLog_Temp_Name - 1);
#endif
	szTemp[1023] = '\0';
	_KMessage(szTemp);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL RangeCheck_KCheck(int32 nIndex, int32 nFrom, int32 nTo, char const *szCodeLocation)
{
	/*~~~~~~~~~~~~~~~~~~~*/
	int32	nUpBorder = 0;
	int32	nLowBorder = 0;
	char	szBuff[1024];
	/*~~~~~~~~~~~~~~~~~~~*/

	if(nFrom > nTo)
	{
		nUpBorder = nFrom;
		nLowBorder = nTo;
	}
	else
	{
		nUpBorder = nTo;
		nLowBorder = nFrom;
	}

	KCheck(0 <= nUpBorder);
	KCheck(0 <= nLowBorder);
	KCheck(0 <= nIndex);
	if(nIndex >= nLowBorder && nIndex <= nUpBorder)
	{
		return TRUE;
	}

	tsnprintf
	(
		szBuff,
		sizeof(szBuff),
		"[%s] Index out of range!! nIndex=%d, but legal range is [%d, %d]. check it now, please!!",
		szCodeLocation,
		nIndex,
		nLowBorder,
		nUpBorder
	);
	szBuff[sizeof(szBuff) - 1] = '\0';
	KCheckEx(FALSE, szBuff);
	return FALSE;
}
