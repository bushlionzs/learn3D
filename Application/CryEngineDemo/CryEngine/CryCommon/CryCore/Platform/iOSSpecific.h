// Copyright 2013-2022 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CryPlatform/AppleSpecific.h>
#include <float.h>
#include <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR
	#define IOS_SIMULATOR
	#include <xmmintrin.h>
#endif

// stubs for virtual keys, isn't used on iOS
#define VK_UP      0
#define VK_DOWN    0
#define VK_RIGHT   0
#define VK_LEFT    0
#define VK_CONTROL 0
#define VK_SCROLL  0

#define SIZEOF_PTR 8
typedef uint64_t threadID;

inline constexpr size_t GetPlatformVersion()
{
	return __IPHONE_OS_VERSION_MAX_ALLOWED;
}

inline constexpr const char* GetPlatformDescription()
{
	return "iOS";
}