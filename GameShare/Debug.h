#ifndef __DEBUG__H__
#define __DEBUG__H__

#include "Basics.h"


//////////////////////////////////////////////////////////////////////////
//函数宏
//////////////////////////////////////////////////////////////////////////
#define	IgnoreKCheck()	__assert_state = 1
#define RetryKCheck()	__assert_state = 2
#define KCheckState()	(__assert_state)
#define IgnoreMessage() __message_state = TRUE

//////////////////////////////////////////////////////////////////////////
//全局变量
//////////////////////////////////////////////////////////////////////////
extern int32_t __assert_state;
extern int32_t __message_state;

//////////////////////////////////////////////////////////////////////////
//功能函数
//////////////////////////////////////////////////////////////////////////
extern void _Check1(const char *file, uint32_t line, const char *func, const char *expr);
extern void _Check2(const char *file, uint32_t line, const char *func, const char *expr, const char *msg);
extern void _Check3(const char *file, uint32_t line, const char *func, const char *expr, const char *msg);
extern void _KMB(const char *msg);
extern bool RangeCheck_KCheck(int32_t nIndex, int32_t nFrom, int32_t nTo, char const *szCodeLocation);


//////////////////////////////////////////////////////////////////////////
//接口宏，包括各种平台处理
//////////////////////////////////////////////////////////////////////////
#if defined(NDEBUG)
	#define KCheck(expr)					((void) 0)
	#define KCheckEx(expr, msg)				((void) 0)
	#define KCheckSpecial(expr, msg)		((void) 0)
	#define KDialogBox(msg)					((void) 0)
#elif __LINUX__
	#define KCheck(expr)					{ if(!(expr)) { _Check1(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr); } }
	#define KCheckEx(expr, msg)				{ if(!(expr)) { _Check2(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, msg); } }
	#define KCheckSpecial(expr, msg)		{ if(!(expr)) { _Check3(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, msg); } }
	#define KCheckExPass(expr, msg)			{ if(!(expr)) { _Check2(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, msg); } }
	#define KDialogBox(msg)					((void) 0)
#elif __WIN_CONSOLE__ || __WIN32__ || __WINDOWS__
	#define KCheck(expr)					((void) ((expr) ? 0 : (_Check1(__FILE__, __LINE__, __FUNCTION__, #expr), 0)))
	#define KCheckEx(expr, msg)				((void) ((expr) ? 0 : (_Check2(__FILE__, __LINE__, __FUNCTION__, #expr, msg), 0)))
	#define KCheckSpecial(expr, msg)		((void) ((expr) ? 0 : (_Check3(__FILE__, __LINE__, __FUNCTION__, #expr, msg), 0)))
	#define KDialogBox(msg)					_KMB(msg)
#elif __MFC__
	#define KCheck(expr)					ASSERT(expr)
	#define KCheckEx(expr, msg)				((void) 0)
	#define KCheckSpecial(expr, msg)		((void) 0)
	#define KDialogBox(msg)					((void) 0)
#endif

#endif//__DEBUG__H__
