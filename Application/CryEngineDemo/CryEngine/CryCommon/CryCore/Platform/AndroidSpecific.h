// Copyright 2013-2022 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#define RC_EXECUTABLE "rc"
#define USE_CRT       1

// Standard includes.
#include <malloc.h>
#include <stdint.h>
#include <fcntl.h>
#include <float.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>
#include <sys/socket.h>

#include "LinuxSpecific.h"
// These functions do not exist int the wchar.h header.
#undef wscasecomp
#undef wscasencomp
extern int wcsicmp(const wchar_t* s1, const wchar_t* s2);
extern int wcsnicmp(const wchar_t* s1, const wchar_t* s2, size_t count);

#define TARGET_DEFAULT_ALIGN (16U)

#define __debugbreak() raise(SIGTRAP)

// There is no __finite in android, only isfinite.
#undef __finite
#define __finite  isfinite

#define S_IWRITE  S_IWUSR

// In RELEASE disable printf and fprintf
#if defined(_RELEASE) && !defined(RELEASE_LOGGING)
	#include <stdio.h>
	#undef printf
	#define printf(...)  (void) 0
	#undef fprintf
	#define fprintf(...) (void) 0
#endif

// C style FILE wrapper for opening file in APK
FILE* android_apk_fopen(const char* fname, const char* mode);

// Returns path to CRYENGINE and Crytek provided 3rd Party shared libraries
const char* CryGetSharedLibraryStoragePath();

// Get path to user application internal storage
// On Android this points to the secure internal storage path
const char* CryGetApplicationInternalStoragePath();

// Get path to user application external storage
// On Android this points to the external storage path which is accessible by file explorers and other applications
const char* CryGetApplicationExternalStoragePath();

// Get path to user application assets storage
// On Android this points to the path where the expansion files are located
const char* CryGetApplicationAssetPath();

#include "AndroidJNI.h"

inline constexpr size_t GetPlatformVersion()
{
	return __ANDROID_API__;
}

inline constexpr const char* GetPlatformDescription()
{
	return "Android API";
}
