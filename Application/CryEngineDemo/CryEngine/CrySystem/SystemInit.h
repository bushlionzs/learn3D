// Copyright 2013-2021 Crytek GmbH / Crytek Group. All rights reserved.

#include "System.h"
#if CRY_PLATFORM_ANDROID && defined(DEDICATED_SERVER)
	#include "AndroidConsole.h"
#endif

#include "UnixConsole.h"
#ifdef USE_UNIXCONSOLE
extern __attribute__((visibility("default"))) CUNIXConsole* pUnixConsole;
#endif
