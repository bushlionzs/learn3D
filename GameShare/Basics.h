/*$T Common/Basics.h GC 1.140 10/10/09 10:06:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __BASETYPE_H__
#define __BASETYPE_H__

#ifndef GAME_CLIENT
#ifndef FD_SETSIZE
#define FD_SETSIZE	2048
#endif /* FD_SETSIZE */
#endif
#if defined(__WINDOWS__)
#pragma warning(disable : 4786)
#pragma warning(disable : 4018)
#include <WinSock2.h>
#include <Windows.h>
#include "crtdbg.h"
#elif defined(__LINUX__)
#include <sys/types.h>
#include <pthread.h>
#endif
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdarg.h>

using namespace			std;

/*
 * define void void ;
 * typedef unsigned char uchar;
 * *typedef char char;
 * *typedef unsigned int uint32;
 * *typedef int int32;
 * *typedef unsigned short USHORT;
 * *typedef short SHORT;
 * *typedef unsigned long ulong;
 * *typedef long long;
 * *typedef FLOAT float;
 * *typedef double float64;
 * *typedef long long unsigned int uint64;
 * * ;
 * typedef uchar uchar;
 * *typedef USHORT ushort;
 * *typedef uint32 uint32;
 * *typedef ulong ulong;
 */
typedef uint16_t			MSG_ID;
#if defined(_70_CLIENT)
typedef double			FLOAT64;
#endif
#define IP_SIZE		24
#define INVALID_HANDLE	- 1
#define INVALID_ID	- 1
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
#ifndef _MAX_PATH
#define _MAX_PATH	260
#endif
#if defined(NDEBUG)
#define GUARD	if(1) \
	{
#define UNGUARD \
}
#else
#define GUARD	if(1) \
	{
#define UNGUARD \
}
#endif
#if defined(NDEBUG)
#define _NET_TRY	try
#define _NET_CATCH	catch(...)
#else
#define _NET_TRY	try
#define _NET_CATCH	catch(...)
#endif
#ifndef KSafeDelete
#if defined(__WINDOWS__)
#define KSafeDelete(x) \
	if((x) != NULL) \
	{ \
		KCheck(_CrtIsValidHeapPointer(x)); \
		delete(x); \
		(x) = NULL; \
	}
#elif defined(__LINUX__)
#define KSafeDelete(x) \
	if((x) != NULL) \
	{ \
		delete(x); \
		(x) = NULL; \
	}
#endif
#endif
#ifndef KSafeDelete_ARRAY
#if defined(__WINDOWS__)
#define KSafeDelete_ARRAY(x) \
	if((x) != NULL) \
	{ \
		KCheck(_CrtIsValidHeapPointer(x)); \
		delete[](x); \
		(x) = NULL; \
	}
#elif defined(__LINUX__)
#define KSafeDelete_ARRAY(x) \
	if((x) != NULL) \
	{ \
		delete[](x); \
		(x) = NULL; \
	}
#endif
#endif
#ifndef KSafeFree
#define KSafeFree(x) \
	if((x) != NULL) \
	{ \
		free(x); \
		(x) = NULL; \
	}
#endif
#ifndef KSafeRelease
#define KSafeRelease(x) \
	if((x) != NULL) \
	{ \
		(x)->Release(); \
		(x) = NULL; \
	}
#endif
#endif
