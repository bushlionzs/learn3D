#ifndef XG_HEAD_TYPEDEF
#define XG_HEAD_TYPEDEF
///////////////////////////////////////////////////////

#ifdef _MSC_VER

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#else

#ifndef XG_MINGW
#define XG_LINUX
#endif

#endif

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdarg.h>
#include <assert.h>

#ifdef XG_LINUX					/******* linux ******/
	#include <grp.h>
	#include <pwd.h>
	#include <errno.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <signal.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <termios.h>
	#include <pthread.h>
	#include <sys/time.h>
	#include <sys/wait.h>
	#include <sys/stat.h>
	#include <sys/file.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/sysinfo.h>

	#ifndef MAX_PATH
	#define MAX_PATH	256
	#endif

	#define TRUE 		1
	#define FALSE 		0
	#define Sleep(ms)	usleep((ms)*1000)

	typedef int SOCKET;

	typedef enum
	{
		eRED = 31,
		eBLUE = 34,
		eGREEN = 32,
		eWHITE = 37,
		eYELLOW = 33
	} E_CONSOLE_COLOR;

	inline static int getch()
	{
		struct termios tm;
		struct termios old;

		int ch;
		int fd = STDIN_FILENO;

		if (tcgetattr(fd, &tm) < 0) return 0;

		old = tm;
		cfmakeraw(&tm);

		if (tcsetattr(fd, TCSANOW, &tm) < 0) return 0;

		ch = fgetc(stdin);

		if (tcsetattr(fd, TCSANOW, &old) < 0) return 0;

		return ch;
	}

	inline static void SetConsoleTextColor(E_CONSOLE_COLOR color)
	{
		printf("\e[%dm", (int)(color));
	}

#else							/****** windows *****/

	#ifndef UNICODE
	#define UNICODE
	#endif

	#ifndef _UNICODE
	#define _UNICODE
	#endif

	#include <windows.h>
	#include <conio.h>

	#ifdef _MSC_VER
	#define strcasecmp stricmp
	#pragma warning(disable:4996)
	#pragma comment(lib, "WS2_32.lib")
	#endif
	
	#define getch				_getch
	#define snprintf			_snprintf
	#define sleep(s)			Sleep((s)*1000)
	#define localtime_r(a,b)	localtime_s(b,a)

	typedef enum
	{
		eRED = FOREGROUND_RED,
		eBLUE = FOREGROUND_BLUE,
		eGREEN = FOREGROUND_GREEN,
		eYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		eWHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN
	} E_CONSOLE_COLOR;

	inline static void SetConsoleTextColor(E_CONSOLE_COLOR color)
	{
		static HANDLE console = NULL;

		if (console == NULL) console = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(console, color);
	}
#endif

#ifndef XG_AIX
typedef char 				int8;
typedef long long			int64;
typedef unsigned long long	u_int64;
#endif

typedef int					int32;
typedef short				int16;

typedef unsigned int		u_int;
typedef unsigned char		u_int8;
typedef unsigned char		u_char;
typedef unsigned long		u_long;
typedef unsigned short		u_short;

typedef unsigned int		u_int32;
typedef unsigned short		u_int16;

#ifndef ARR_LEN
#define ARR_LEN(arr)	(sizeof(arr)/sizeof(arr[0]))
#endif

#define CHECK_FALSE_RETURN(FUNC) if (FUNC){} else return false

///////////////////////////////////////////////////////
#endif
