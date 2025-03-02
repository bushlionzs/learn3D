// Copyright 2004-2021 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "System.h"
#include <time.h>
//#include "ini_vars.h"
#include <CryCore/Platform/CryLibrary.h>

#if defined(_RELEASE) && CRY_PLATFORM_DURANGO //note: check if orbis needs this
//exclude some not needed functionality for release console builds
	#define EXCLUDE_UPDATE_ON_CONSOLE
#endif

#if CRY_PLATFORM_LINUX
	#include <execinfo.h> // for backtrace
#endif

#if CRY_PLATFORM_ANDROID
	#include <unwind.h> // for _Unwind_Backtrace and _Unwind_GetIP
#endif

#include <CryNetwork/INetwork.h>
#include <Cry3DEngine/I3DEngine.h>
#include <CryRenderer/IRenderer.h>
#include <CrySystem/File/ICryPak.h>
#include <CrySystem/ConsoleRegistration.h>
#include <JobManager/JobManager.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CryInput/IInput.h>
#include <CrySystem/ILog.h>
#include <CrySystem/SystemInitParams.h>
#include <CryAudio/IAudioSystem.h>
#include <CryAnimation/ICryAnimation.h>
#include <CryScriptSystem/IScriptSystem.h>
#include <CrySystem/IProcess.h>
#include <CrySystem/IBudgetingSystem.h>
#include <CryGame/IGameFramework.h>
#include <CryNetwork/INotificationNetwork.h>
#include <CrySystem/ICodeCheckpointMgr.h>
#include <CrySystem/Profilers/IStatoscope.h>

#include <Cry3DEngine/ITimeOfDay.h>
#include <CrySchematyc/ICore.h>
#include "CryPak.h"

#include <CryString/CryPath.h>

#include "XML/xml.h"
#include "XML/ReadWriteXMLSink.h"


#include "XML/XmlUtils.h"
#include "Serialization/ArchiveHost.h"
#include <CrySystem/Profilers/IDiskProfiler.h>
#include "SystemEventDispatcher.h"

#include <CryMemory/ILocalMemoryUsage.h>
#include "ResourceManager.h"
#include "MemoryManager.h"

#include <CryThreading/IThreadManager.h>


#include <CrySystem/ZLib/IZLibCompressor.h>
#include <CrySystem/ZLib/IZlibDecompressor.h>
#include <CrySystem/ZLib/ILZ4Decompressor.h>
#include <zlib.h>

#include "BootProfiler.h"
#if ALLOW_BROFILER
#	include <Cry_Brofiler.h>
#	include "Profiling/CryBrofiler.h"
#endif
#include "Profiling/ProfilingRenderer.h"
#include "Profiling/NullProfiler.h"
#include "Profiling/CryProfilingSystem.h"
#include "Profiling/CryProfilingSystemSharedImpl.h"

#include <CryMath/PNoise3.h>
#include <CryString/StringUtils.h>
#include <CrySystem/Scaleform/IFlashUI.h>

#include <../CryAction/ILevelSystem.h>
#include <../CryAction/IViewSystem.h>


#if CRY_PLATFORM_WINDOWS
	#include <timeapi.h>
	#include <algorithm>
#endif

// Define global cvars.
SSystemCVars g_cvars;

#include <CrySystem/ITextModeConsole.h>

extern int CryMemoryGetAllocatedSize();

// these heaps are used by underlying System structures
// to allocate, accordingly, small (like elements of std::set<..*>) and big (like memory for reading files) objects
// hopefully someday we'll have standard MT-safe heap
//CMTSafeHeap g_pakHeap;
CMTSafeHeap* g_pPakHeap = 0;// = &g_pakHeap;


#include <CrySystem/CVarOverride.h>
#include "CmdLine.h"
#include <CryMath/Random.h>


#if defined(CVARS_WHITELIST)
struct SCVarsWhitelistConfigSink : public ILoadConfigurationEntrySink
{
	virtual void OnLoadConfigurationEntry(const char* szKey, const char* szValue, const char* szGroup)
	{
		if (gEnv->pSystem->IsCVarWhitelisted(szKey, false))
		{
			gEnv->pConsole->LoadConfigVar(szKey, szValue);
		}
	}
} g_CVarsWhitelistConfigSink;
#endif // defined(CVARS_WHITELIST)

/////////////////////////////////////////////////////////////////////////////////
// System Implementation.
//////////////////////////////////////////////////////////////////////////
CSystem::CSystem(const SSystemInitParams& startupParams)
#if defined(SYS_ENV_AS_STRUCT)
	: m_env(gEnv)
#elif !defined(CRY_IS_MONOLITHIC_BUILD)
	: m_gameLibrary(nullptr)
#endif
{
	MEMSTAT_CONTEXT(EMemStatContextType::Other, "CSystem Constructor");

	m_pSystemEventDispatcher = new CSystemEventDispatcher(); // Must be first.
	m_pSystemEventDispatcher->RegisterListener(this, "CSystem");

	//////////////////////////////////////////////////////////////////////////
	// Reset handles.
	memset(&m_dll, 0, sizeof(m_dll));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Initialize global environment interface pointers.
	m_env.pSystem = this;
	m_env.pTimer = &m_Time;
	m_env.pNameTable = &m_nameTable;
	m_env.startProfilingSection = &CNullProfiler::StartSectionStatic;
	m_env.recordProfilingMarker = &CNullProfiler::RecordMarkerStatic;

	m_env.SetFMVIsPlaying(false);
	m_env.SetCutsceneIsPlaying(false);

#if CRY_PLATFORM_DESKTOP
	m_env.SetIsClient(false);
#endif
#if !defined(SYS_ENV_AS_STRUCT)
	gEnv = &m_env;
#endif
	//////////////////////////////////////////////////////////////////////////

	m_randomGenerator.SetState(m_Time.GetAsyncTime().GetMicroSecondsAsInt64());

	m_pStreamEngine = nullptr;
	m_PhysThread = nullptr;

	m_pIFont = nullptr;
	m_pVisRegTest = nullptr;
	m_rIntialWindowSizeRatio = nullptr;
	m_rWidth = nullptr;
	m_rHeight = nullptr;
	m_rColorBits = nullptr;
	m_rDepthBits = nullptr;
	m_cvSSInfo = nullptr;
	m_rStencilBits = nullptr;
	m_rFullscreen = nullptr;
	m_rDriver = nullptr;
	m_pPhysicsLibrary = nullptr;
	m_sysNoUpdate = nullptr;
	m_pMemoryManager = nullptr;
	m_pProcess = nullptr;
	m_pMtState = nullptr;

	m_pValidator = nullptr;
	m_pCmdLine = nullptr;
	m_pDefaultValidator = nullptr;
	m_pIBudgetingSystem = nullptr;
	m_pIZLibCompressor = nullptr;
	m_pIZLibDecompressor = nullptr;
	m_pILZ4Decompressor = nullptr;
	m_pNULLRenderAuxGeom = nullptr;
	m_pLocalizationManager = nullptr;
	m_sys_physics_enable_MT = nullptr;
	m_sys_min_step = nullptr;
	m_sys_max_step = nullptr;

	m_pNotificationNetwork = nullptr;

	m_cvAIUpdate = nullptr;

	m_pUserCallback = nullptr;
#if defined(CVARS_WHITELIST)
	m_pCVarsWhitelistConfigSink = &g_CVarsWhitelistConfigSink;
#endif // defined(CVARS_WHITELIST)
	m_sys_memory_debug = nullptr;
	m_sysWarnings = nullptr;
	m_sysKeyboard = nullptr;
	m_sys_profile_watchdog_timeout = nullptr;
	m_sys_job_system_filter = nullptr;
	m_sys_job_system_enable = nullptr;
	m_sys_job_system_profiler = nullptr;
	m_sys_job_system_max_worker = nullptr;
	m_sys_job_system_worker_boost_enabled = nullptr;
	m_sys_spec = nullptr;
	m_sys_firstlaunch = nullptr;
	m_sys_enable_budgetmonitoring = nullptr;
	m_sys_use_Mono = nullptr;
	m_sys_dll_ai = nullptr;
	m_sys_dll_response_system = nullptr;
	m_sys_user_folder = nullptr;

#if !defined(_RELEASE)
	m_sys_resource_cache_folder = nullptr;
#endif

	m_sys_initpreloadpacks = nullptr;
	m_sys_menupreloadpacks = nullptr;

	//	m_sys_filecache = nullptr;
	m_gpu_particle_physics = nullptr;
	m_pCpu = nullptr;

	m_bQuit = false;
	m_bShaderCacheGenMode = false;
	m_bRelaunch = false;
	m_iLoadingMode = 0;
	m_bIgnoreUpdates = false;
	m_bNoCrashDialog = false;

#ifndef _RELEASE
	m_checkpointLoadCount = 0;
	m_loadOrigin = eLLO_Unknown;
	m_hasJustResumed = false;
	m_expectingMapCommand = false;
#endif

	// no mem stats at the moment
	m_pMemStats = nullptr;
	m_pSizer = nullptr;
	m_pCVarQuit = nullptr;

	m_pDownloadManager = nullptr;
	m_bForceNonDevMode = false;
	m_bWasInDevMode = false;
	m_bInDevMode = false;
	m_bGameFolderWritable = false;

	m_nServerConfigSpec = CONFIG_VERYHIGH_SPEC;
	m_nMaxConfigSpec = CONFIG_ORBIS_NEO;

	//m_hPhysicsThread = INVALID_HANDLE_VALUE;
	//m_hPhysicsActive = INVALID_HANDLE_VALUE;
	//m_bStopPhysics = 0;
	//m_bPhysicsActive = 0;

	m_pProgressListener = nullptr;

	m_bPaused = false;
	m_bNoUpdate = false;
	m_nUpdateCounter = 0;
	m_iApplicationInstance = -1;

	m_pPhysRenderer = nullptr;

	m_root = PathUtil::AddSlash(PathUtil::GetEnginePath());

	m_pXMLUtils = new CXmlUtils(this);
	m_pArchiveHost = Serialization::CreateArchiveHost();

	m_pMemoryManager = CryGetIMemoryManager();
	m_pResourceManager = new CResourceManager;
	m_pTextModeConsole = nullptr;
	m_pDiskProfiler = nullptr;
	m_ttMemStatSS = 0;

	m_pLegacyProfiler = nullptr;
	m_pProfilingSystem = nullptr;
	m_pProfileRenderer = nullptr;

#ifdef ENABLE_PROFILING_CODE
	const std::vector<Cry::ProfilerRegistry::SEntry>& profilers = Cry::ProfilerRegistry::Get();

	const Cry::ProfilerRegistry::SEntry* cmdLineProfilerChoice = nullptr;
	for (const Cry::ProfilerRegistry::SEntry& profilerEntry : profilers)
	{
		if (strstr(startupParams.szSystemCmdLine, profilerEntry.cmdLineArgument.c_str()) != nullptr)
		{
			if (CRY_VERIFY(cmdLineProfilerChoice == nullptr, "You specified more than one profiler on the command line!"))
				cmdLineProfilerChoice = &profilerEntry;
		}
	}

	const Cry::ProfilerRegistry::SEntry defaultEntry = CCryProfilingSystem::MakeRegistryEntry();
	
	if (cmdLineProfilerChoice == nullptr)
	{
		cmdLineProfilerChoice = &defaultEntry;
	}

	m_pProfilingSystem = cmdLineProfilerChoice->factory();
	m_env.startProfilingSection = cmdLineProfilerChoice->sectionCallback;
	m_env.recordProfilingMarker = cmdLineProfilerChoice->markerCallback;

	if (cmdLineProfilerChoice->name == defaultEntry.name)
	{
		m_pLegacyProfiler = reinterpret_cast<CCryProfilingSystem*>(m_pProfilingSystem);
	}

#if defined(ENABLE_LOADING_PROFILER)
	if (!startupParams.bShaderCacheGen)
	{
		CBootProfiler::GetInstance().Init(this, startupParams.szSystemCmdLine);
	}
	if (m_pLegacyProfiler)
		m_pLegacyProfiler->SetBootProfiler(&CBootProfiler::GetInstance());
#endif
	m_pProfileRenderer = new CProfilingRenderer;

	const char* szVerbosity = strstr(startupParams.szSystemCmdLine, "-profile_verbosity=");
	if (szVerbosity != nullptr)
	{
		szVerbosity += sizeof("-profile_verbosity=") - 1;
		int verbosity = atoi(szVerbosity);
		if (verbosity > 0)
			CCryProfilingSystem::s_verbosity = verbosity;
	}
#endif


	CRY_PROFILE_SECTION(PROFILE_LOADING_ONLY, "CSystem Boot");

	m_pMiniGUI = nullptr;
	m_pPerfHUD = nullptr;

	m_pHmdManager = nullptr;
	m_sys_vr_support = nullptr;

	g_pPakHeap = new CMTSafeHeap;

	m_bUIFrameworkMode = false;

	m_PlatformOSCreateFlags = 0;

	// create job manager
	m_env.pJobManager = GetJobManagerInterface();

	m_UpdateTimesIdx = 0U;

	m_PlatformOSCreateFlags = 0;

	m_bHasRenderedErrorMessage = false;

	m_pImeManager = nullptr;

}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
CSystem::~CSystem()
{
	ShutDown();

	SAFE_DELETE(m_pImeManager);
	UnregisterWindowMessageHandler(this);

	FreeLib(m_dll.hNetwork);
	FreeLib(m_dll.hAI);
	FreeLib(m_dll.hInput);
	FreeLib(m_dll.hScript);
	FreeLib(m_dll.hPhysics);
	FreeLib(m_dll.hEntitySystem);
	FreeLib(m_dll.hRenderer);
	FreeLib(m_dll.hFlash);
	FreeLib(m_dll.hFont);
	FreeLib(m_dll.hMovie);
	FreeLib(m_dll.hIndoor);
	FreeLib(m_dll.h3DEngine);
	FreeLib(m_dll.hAnimation);
	FreeLib(m_dll.hGame);
	FreeLib(m_dll.hSound);
	SAFE_DELETE(m_pVisRegTest);
#if defined(USE_DISK_PROFILER)
	SAFE_DELETE(m_pDiskProfiler);
#endif
	SAFE_DELETE(m_pXMLUtils);
	SAFE_DELETE(m_pArchiveHost);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pSystemEventDispatcher);
	//	SAFE_DELETE(m_pMemoryManager);
	SAFE_DELETE(m_pNULLRenderAuxGeom);


	gEnv->pThreadManager->UnRegisterThirdPartyThread("Main");

	SAFE_DELETE(g_pPakHeap);

	m_env.startProfilingSection = &CNullProfiler::StartSectionStatic;
	m_env.recordProfilingMarker = &CNullProfiler::RecordMarkerStatic;
	SAFE_DELETE(m_pProfilingSystem);

	m_env.pSystem = nullptr;
#if !defined(SYS_ENV_AS_STRUCT)
	gEnv = 0;
#endif

}

//////////////////////////////////////////////////////////////////////////
void CSystem::FreeLib(WIN_HMODULE hLibModule)
{
	if (hLibModule)
	{
		CryFreeLibrary(hLibModule);
	}
}

//////////////////////////////////////////////////////////////////////////
IStreamEngine* CSystem::GetStreamEngine()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
IRemoteConsole* CSystem::GetIRemoteConsole()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SetForceNonDevMode(const bool bValue)
{
	m_bForceNonDevMode = bValue;
	if (bValue)
		SetDevMode(false);
}

//////////////////////////////////////////////////////////////////////////
bool CSystem::GetForceNonDevMode() const
{
	return m_bForceNonDevMode;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SetDevMode(bool bEnable)
{
	if (bEnable)
		m_bWasInDevMode = true;
	m_bInDevMode = bEnable;
}


///////////////////////////////////////////////////
void CSystem::ShutDown()
{
	
	
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void CSystem::Quit()
{
	CryLog("CSystem::Quit invoked from thread %" PRI_THREADID " (main is %" PRI_THREADID ")", GetCurrentThreadId(), gEnv->mMainThreadId);

	if (m_bQuit)
		return;
	m_bQuit = true;

	if (m_pUserCallback)
		m_pUserCallback->OnQuit();
	// Fast Quit.

	// clean up properly the console
	if (m_pTextModeConsole)
		m_pTextModeConsole->OnShutdown();

	if (m_env.pRenderer)
	{
		ICVar* pCVarGamma = m_env.pConsole->GetCVar("r_Gamma");
		if (pCVarGamma)
			pCVarGamma->Set(1.0f); // prevent mysterious gamma snap back on quit (CE-15284)
		m_env.pRenderer->RestoreGamma();
	}

	if (m_pCVarQuit && m_pCVarQuit->GetIVal() != 0)
	{
		// Dispatch the fast-shutdown event so other systems can do any last minute processing.
		if (m_pSystemEventDispatcher != NULL)
		{
			m_pSystemEventDispatcher->OnSystemEvent(ESYSTEM_EVENT_FAST_SHUTDOWN, 0, 0);
		}

		if (m_env.pNetwork)
			m_env.pNetwork->FastShutdown();

		// HACK! to save cvars on quit.
		SaveConfiguration();

		if (gEnv->pFlashUI)
			gEnv->pFlashUI->Shutdown();

		if (m_env.pRenderer)
		{
			m_env.pRenderer->StopRenderIntroMovies(false);
			m_env.pRenderer->StopLoadtimeFlashPlayback();
		}

#if defined(INCLUDE_SCALEFORM_SDK) || defined(CRY_FEATURE_SCALEFORM_HELPER)
		if (m_env.pRenderer)
			m_env.pRenderer->FlushRTCommands(true, true, true);

		if (gEnv->pScaleformHelper)
		{
			gEnv->pScaleformHelper->Destroy();
			gEnv->pScaleformHelper = nullptr;
		}
#endif

		if (m_env.pRenderer)
			m_env.pRenderer->ShutDownFast();

		CryLogAlways("System:Quit");

		// Shut down audio as late as possible but before the streaming system and console get released!
		SAFE_RELEASE(m_env.pAudioSystem);


		// Commit files changes to the disk.
#if CRY_PLATFORM_LINUX || CRY_PLATFORM_ANDROID
		fflush(NULL);
#else
		_flushall();
#endif
		

#if CAPTURE_REPLAY_LOG
		CryGetIMemReplay()->Stop();
#endif

		GetIRemoteConsole()->Stop();

		//////////////////////////////////////////////////////////////////////////
		// [marco] in test mode, kill the process and quit without performing full C libs cleanup
		// (for faster closing of application)
		CRY_ASSERT(m_pCVarQuit->GetIVal());
#if CRY_PLATFORM_ORBIS
		_Exit(0);
#elif CRY_PLATFORM_WINDOWS
		TerminateProcess(GetCurrentProcess(), 0);
#else
		_exit(0);
#endif
	}
#if !CRY_PLATFORM_LINUX && !CRY_PLATFORM_ANDROID && !CRY_PLATFORM_APPLE && !CRY_PLATFORM_DURANGO && !CRY_PLATFORM_ORBIS
	PostQuitMessage(0);
#endif
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool CSystem::IsQuitting() const
{
	return m_bQuit;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SetIProcess(IProcess* process)
{
	m_pProcess = process;
	//if (m_pProcess)
	//m_pProcess->SetPMessage("");
}

void CSystem::StartBootProfilerSession(const char* szName)
{
#ifdef ENABLE_LOADING_PROFILER
	CBootProfiler::GetInstance().StartSession(szName);
#endif
}

void CSystem::EndBootProfilerSession()
{
#ifdef ENABLE_LOADING_PROFILER
	CBootProfiler::GetInstance().StopSession();
#endif
}

//////////////////////////////////////////////////////////////////////////
// Physics thread task
//////////////////////////////////////////////////////////////////////////

class IPhysicsThreadTask : public IThread
{
public:
	virtual ~IPhysicsThreadTask()
	{
	}
	// Start accepting work on thread
	virtual void ThreadEntry() = 0;

	// Signals the thread that it should not accept anymore work and exit
	virtual void SignalStopWork() = 0;
};

class CPhysicsThreadTask : public IPhysicsThreadTask
{
public:

	CPhysicsThreadTask()
	{
		m_bStopRequested = 0;
		m_bIsActive = 0;
		m_stepRequested = 0;
		m_bProcessing = 0;
		m_doZeroStep = 0;
		m_lastStepTimeTaken = 0U;
		m_lastWaitTimeTaken = 0U;
	}

	virtual ~CPhysicsThreadTask()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	// IThread implementation.
	//////////////////////////////////////////////////////////////////////////
	// Start accepting work on thread
	virtual void ThreadEntry()
	{
		
	}

	// Signals the thread that it should not accept anymore work and exit
	virtual void SignalStopWork()
	{
		Pause();
		m_bStopRequested = 1;
		m_FrameEvent.Set();
		m_bIsActive = 0;
	}

	int Pause()
	{
		
		return 0;
	}
	int Resume()
	{
		if (!m_bIsActive)
		{
			m_bIsActive = 1;
			return 1;
		}
		return 0;
	}
	int IsActive() { return m_bIsActive; }
	int RequestStep(float dt)
	{
		return false;
	}
	float  GetRequestedStep() { return m_stepRequested; }

	uint64 LastStepTaken() const
	{
		return m_lastStepTimeTaken;
	}

	uint64 LastWaitTime() const
	{
		return m_lastWaitTimeTaken;
	}

	void EnsureStepDone()
	{
		CRY_PROFILE_SECTION_WAITING(PROFILE_SYSTEM, "SysUpdate:PhysicsEnsureDone");

		if (m_bIsActive)
		{
			while (m_stepRequested > 0.0f || m_bProcessing)
			{
				m_FrameDone.Wait();
			}
		}
	}

protected:

	volatile int    m_bStopRequested;
	volatile int    m_bIsActive;
	volatile float  m_stepRequested;
	volatile int    m_bProcessing;
	volatile int    m_doZeroStep;
	volatile uint64 m_lastStepTimeTaken;
	volatile uint64 m_lastWaitTimeTaken;

	CryEvent        m_FrameEvent;
	CryEvent        m_FrameDone;
};

void CSystem::CreatePhysicsThread()
{
	if (!m_PhysThread)
	{
		m_PhysThread = new CPhysicsThreadTask;
		if (!gEnv->pThreadManager->SpawnThread(m_PhysThread, "Physics"))
		{
			CryFatalError("Error spawning \"Physics\" thread.");
		}
	}
}

void CSystem::KillPhysicsThread()
{
	if (m_PhysThread)
	{
		m_PhysThread->SignalStopWork();
		gEnv->pThreadManager->JoinThread(m_PhysThread, eJM_Join);
		delete m_PhysThread;
		m_PhysThread = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
int CSystem::SetThreadState(ESubsystem subsys, bool bActive)
{
	switch (subsys)
	{
	case ESubsys_Physics:
		{
			if (m_PhysThread)
			{
				return bActive ? ((CPhysicsThreadTask*)m_PhysThread)->Resume() : ((CPhysicsThreadTask*)m_PhysThread)->Pause();
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SleepIfNeeded()
{
	CRY_PROFILE_FUNCTION(PROFILE_SYSTEM)

	static ICVar * pSysMaxFPS = NULL;
	static ICVar* pVSync = NULL;

	if (pSysMaxFPS == NULL && gEnv && gEnv->pConsole)
		pSysMaxFPS = gEnv->pConsole->GetCVar("sys_MaxFPS");
	if (pVSync == NULL && gEnv && gEnv->pConsole)
		pVSync = gEnv->pConsole->GetCVar("r_Vsync");

	int32 maxFPS = 0;

	if (m_env.IsDedicated())
	{
		const float maxRate = m_svDedicatedMaxRate->GetFVal();
		maxFPS = int32(maxRate);
	}
	else
	{
		if (pSysMaxFPS && pVSync)
		{
			uint32 vSync = pVSync->GetIVal();
			if (vSync == 0)
			{
				maxFPS = pSysMaxFPS->GetIVal();
				if (maxFPS == 0)
				{
					const bool bInLoading = (ESYSTEM_GLOBAL_STATE_RUNNING != m_systemGlobalState);
					if (bInLoading || IsPaused() || m_throttleFPS)
					{
						maxFPS = 60;
					}
				}
			}
		}
	}

	if (maxFPS > 0)
	{
		const int64 safeMarginMS = 5; // microseconds
		const int64 thresholdMs = (1000 * 1000) / (maxFPS);

		ITimer* pTimer = gEnv->pTimer;
		static int64 sTimeLast = pTimer->GetAsyncTime().GetMicroSecondsAsInt64();
		int64 currentTime = pTimer->GetAsyncTime().GetMicroSecondsAsInt64();
		for (;;)
		{
			const int64 frameTime = currentTime - sTimeLast;
			if (frameTime >= thresholdMs)
				break;
			if (thresholdMs - frameTime > 10 * 1000)
				CrySleep(1);
			else
				CrySleep(0);

			currentTime = pTimer->GetAsyncTime().GetMicroSecondsAsInt64();
		}

		m_lastTickTime = pTimer->GetAsyncTime();
		sTimeLast = m_lastTickTime.GetMicroSecondsAsInt64() + safeMarginMS;
	}
}

//////////////////////////////////////////////////////////////////////
#if CRY_PLATFORM_WINDOWS
HWND g_hBreakWnd;
WNDPROC g_prevWndProc;
LRESULT CALLBACK BreakWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_HOTKEY)
		__debugbreak();
	return CallWindowProc(g_prevWndProc, hWnd, msg, wParam, lParam);
}

struct SBreakHotKeyThread : public IThread
{
	SBreakHotKeyThread()
		: m_bRun(true)
	{
	}

	// Start accepting work on thread
	virtual void ThreadEntry()
	{
		g_hBreakWnd = CreateWindowExW(0, L"Message", L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_MESSAGE, 0, GetModuleHandleW(0), 0);
		g_prevWndProc = (WNDPROC)SetWindowLongPtrW(g_hBreakWnd, GWLP_WNDPROC, (LONG_PTR)BreakWndProc);
		RegisterHotKey(g_hBreakWnd, 0, 0, VK_PAUSE);
		MSG msg;
		while (GetMessage(&msg, g_hBreakWnd, 0, 0) && m_bRun)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		UnregisterHotKey(g_hBreakWnd, 0);
	}

	// Signals the thread that it should not accept anymore work and exit
	void SignalStopWork()
	{
		m_bRun = false;
	}

protected:
	volatile bool m_bRun;
};

SBreakHotKeyThread* g_pBreakHotkeyThread;
#endif

class BreakListener : public IInputEventListener
{
	bool OnInputEvent(const SInputEvent& ie)
	{
		if (ie.deviceType == eIDT_Keyboard && ie.keyId == eKI_Pause && ie.state & (eIS_Pressed | eIS_Down))
			__debugbreak();
		return true;
	}
} g_BreakListener;

volatile int g_lockInput = 0;

struct SBreakListenerTask : public IThread
{
	SBreakListenerTask()
	{
		m_bStop = 0;
		m_nBreakIdle = 0;
	}
	// Start accepting work on thread
	virtual void ThreadEntry()
	{
		do
		{
			CrySleep(200);
			if (++m_nBreakIdle > 1)
			{
				WriteLock lock(g_lockInput);
				gEnv->pInput->Update(true);
				m_nBreakIdle = 0;
			}
		}
		while (!m_bStop);
	}
	// Signals the thread that it should not accept anymore work and exit
	void SignalStopWork()
	{
		m_bStop = 1;
	}
	volatile int m_bStop;
	int          m_nBreakIdle;
};
SBreakListenerTask g_BreakListenerTask;
bool g_breakListenerOn = false;

extern DWORD g_idDebugThreads[];
extern int g_nDebugThreads;
int prev_sys_float_exceptions = -1;

//////////////////////////////////////////////////////////////////////
void CSystem::PrePhysicsUpdate()
{
	CRY_PROFILE_SECTION(PROFILE_SYSTEM, "System::PrePhysicsUpdate");

	if (m_env.pGameFramework)
	{
		m_env.pGameFramework->PrePhysicsUpdate();
	}


	//////////////////////////////////////////////////////////////////////
	//update entity system
	if (m_env.pEntitySystem && g_cvars.sys_entitysystem)
	{
		if (gEnv->pSchematyc != nullptr)
		{
			gEnv->pSchematyc->PrePhysicsUpdate();
		}

		

		m_env.pEntitySystem->PrePhysicsUpdate();
	}
}

void CSystem::RunMainLoop()
{
	MEMSTAT_CONTEXT(EMemStatContextType::Other, "CSystem::MainLoop");

	if (m_bShaderCacheGenMode)
	{
		return;
	}

#if CRY_PLATFORM_WINDOWS
	if (!(gEnv && m_env.pSystem) || (!m_env.IsEditor() && !m_env.IsDedicated()))
	{
		if (m_env.pHardwareMouse == nullptr)
		{
			::ShowCursor(FALSE);
		}
	}
#endif

	for (;;)
	{
#if CRY_PLATFORM_DURANGO
		Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent);
#endif
		if (!DoFrame())
		{
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
bool CSystem::DoFrame(const SDisplayContextKey& displayContextKey, const SGraphicsPipelineKey& graphicsPipelineKey, CEnumFlags<ESystemUpdateFlags> updateFlags)
{
	if(m_pProfilingSystem && !updateFlags.Check(ESYSUPDATE_EDITOR))
		m_pProfilingSystem->StartFrame();
#if ALLOW_BROFILER
	BROFILER_FRAME("Main");
#endif

	

	CRY_PROFILE_FUNCTION(PROFILE_SYSTEM);
#if defined(JOBMANAGER_SUPPORT_PROFILING)
	m_env.GetJobManager()->SetFrameStartTime(m_env.pTimer->GetAsyncTime());
#endif

	if (m_env.pGameFramework != nullptr)
	{
		m_env.pGameFramework->PreSystemUpdate();
	}

	

	if (ITextModeConsole* pTextModeConsole = GetITextModeConsole())
	{
		pTextModeConsole->BeginDraw();
	}

	// Tell the network to go to sleep
	if (m_env.pNetwork)
	{
		m_env.pNetwork->SyncWithGame(eNGS_SleepNetwork);
	}

	if (!m_env.IsEditing())  // Editor calls its own rendering update
		RenderBegin(displayContextKey, graphicsPipelineKey);

	bool continueRunning = true;

	// The Editor is responsible for updating the system manually, so we should skip in that case.
	if (!(updateFlags & ESYSUPDATE_EDITOR))
	{
		int pauseMode;

		if (m_env.pRenderer != nullptr && m_env.pRenderer->IsPost3DRendererEnabled())
		{
			pauseMode = 0;
			updateFlags |= ESYSUPDATE_IGNORE_AI;
		}
		else if (m_env.pGameFramework != nullptr)
		{
			pauseMode = (m_env.pGameFramework->IsGamePaused() || !m_env.pGameFramework->IsGameStarted()) ? 1 : 0;
		}
		else
		{
			pauseMode = 0;
		}

		if (!Update(updateFlags, pauseMode))
		{
			continueRunning = false;
		}
	}

	if (m_env.pGameFramework != nullptr)
	{
		if (!m_env.pGameFramework->PostSystemUpdate(m_hasWindowFocus, updateFlags))
		{
			continueRunning = false;
		}
	}


	// Synchronize all animations to ensure that their computation has finished
	// Has to be done before view update, in case camera depends on a joint
	if (m_env.pCharacterManager && !IsLoading())
	{
		m_env.pCharacterManager->SyncAllAnimations();
	}

	if (m_env.pGameFramework != nullptr && !updateFlags.Check(ESYSUPDATE_EDITOR_ONLY) && !updateFlags.Check(ESYSUPDATE_EDITOR_AI_PHYSICS))
	{
		m_env.pGameFramework->PreFinalizeCamera(updateFlags);
	}


	ICVar* pCameraFreeze = gEnv->pConsole->GetCVar("e_CameraFreeze");
	const bool isCameraFrozen = pCameraFreeze && pCameraFreeze->GetIVal() != 0;

	const CCamera& rCameraToSet = isCameraFrozen ? m_env.p3DEngine->GetRenderingCamera() : m_ViewCamera;
	m_env.p3DEngine->PrepareOcclusion(rCameraToSet, SGraphicsPipelineKey::BaseGraphicsPipelineKey);

	if (m_env.pGameFramework != nullptr)
	{
		m_env.pGameFramework->PreRender();
	}

	Render(graphicsPipelineKey);

	if (m_env.pGameFramework != nullptr)
	{
		m_env.pGameFramework->PostRender(updateFlags);
	}

	if (updateFlags & ESYSUPDATE_EDITOR_AI_PHYSICS)
	{
		return continueRunning;
	}

#if !defined(_RELEASE) && !CRY_PLATFORM_DURANGO
	RenderPhysicsHelpers();
#endif

	RenderEnd();

	if (m_env.pGameFramework != nullptr)
	{
		m_env.pGameFramework->PostRenderSubmit();
	}

	if (!(updateFlags & ESYSUPDATE_EDITOR))
	{
		if (m_env.pStatoscope)
		{
			m_env.pStatoscope->Tick();
		}

		if (ITextModeConsole* pTextModeConsole = GetITextModeConsole())
		{
			pTextModeConsole->EndDraw();
		}

		m_env.p3DEngine->SyncProcessStreamingUpdate();

		if(m_pProfilingSystem)
			m_pProfilingSystem->EndFrame();
	}

	SleepIfNeeded();
	return continueRunning;
}

//////////////////////////////////////////////////////////////////////
bool CSystem::Update(CEnumFlags<ESystemUpdateFlags> updateFlags, int nPauseMode)
{
	CRY_PROFILE_FUNCTION(PROFILE_SYSTEM)
	MEMSTAT_CONTEXT(EMemStatContextType::Other, "CSystem::Update");

#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	// do the dedicated sleep earlier than the frame profiler to avoid having it counted
	if (gEnv->IsDedicated())
	{
	#if defined(MAP_LOADING_SLICING)
		gEnv->pSystemScheduler->SchedulingSleepIfNeeded();
	#endif // defined(MAP_LOADING_SLICING)
	}
#endif //EXCLUDE_UPDATE_ON_CONSOLE
#if CAPTURE_REPLAY_LOG
	if (CryGetIMemoryManager() && CryGetIMemReplay())
	{
		CryGetIMemReplay()->AddFrameStart();
		if ((--m_ttMemStatSS) <= 0)
		{
			CryGetIMemReplay()->AddScreenshot();
			m_ttMemStatSS = 30;
		}
	}
#endif //CAPTURE_REPLAY_LOG


	m_pPlatformOS->Tick(m_Time.GetRealFrameTime());

#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	if (g_cvars.sys_keyboard_break && !g_breakListenerOn)
	{
	#if CRY_PLATFORM_WINDOWS
		if (m_env.IsEditor() && !g_pBreakHotkeyThread)
		{
			g_pBreakHotkeyThread = new SBreakHotKeyThread();
			if (!gEnv->pThreadManager->SpawnThread(g_pBreakHotkeyThread, "WINAPI_BreakHotkeyListener"))
			{
				CryFatalError("Error spawning \"WINAPI_BreakHotkeyListener\" thread.");
			}
		}
	#endif
		if (!gEnv->pThreadManager->SpawnThread(&g_BreakListenerTask, "BreakListener"))
		{
			CryFatalError("Error spawning \"BreakListener\" thread.");
		}
		gEnv->pInput->AddEventListener(&g_BreakListener);
		g_breakListenerOn = true;
	}
	else if (!g_cvars.sys_keyboard_break && g_breakListenerOn)
	{
	#if CRY_PLATFORM_WINDOWS
		if (g_pBreakHotkeyThread)
			g_pBreakHotkeyThread->SignalStopWork();
	#endif
		gEnv->pInput->RemoveEventListener(&g_BreakListener);
		g_BreakListenerTask.SignalStopWork();
		g_breakListenerOn = false;
	}
#endif //EXCLUDE_UPDATE_ON_CONSOLE

	m_nUpdateCounter++;
#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	if (!m_sDelayedScreeenshot.empty())
	{
		gEnv->pRenderer->ScreenShot(m_sDelayedScreeenshot.c_str());
		m_sDelayedScreeenshot.clear();
	}

	if (m_pUserCallback)
		m_pUserCallback->OnUpdate();

	//////////////////////////////////////////////////////////////////////////
	// Enable/Disable floating exceptions.
	//////////////////////////////////////////////////////////////////////////
	prev_sys_float_exceptions += 1 + g_cvars.sys_float_exceptions & prev_sys_float_exceptions >> 31;
	if (prev_sys_float_exceptions != g_cvars.sys_float_exceptions)
	{
		prev_sys_float_exceptions = g_cvars.sys_float_exceptions;
		m_env.pThreadManager->EnableFloatExceptions((EFPE_Severity) g_cvars.sys_float_exceptions);                  // Set FP Exceptions for this thread
		m_env.pThreadManager->EnableFloatExceptionsForEachOtherThread((EFPE_Severity)g_cvars.sys_float_exceptions); // Set FP Exceptions for all other threads
	}
#endif //EXCLUDE_UPDATE_ON_CONSOLE
	//////////////////////////////////////////////////////////////////////////

	CTimeValue updateStart = gEnv->pTimer->GetAsyncTime();

	if (m_env.pLog)
	{
		MEMSTAT_CONTEXT(EMemStatContextType::Other, "Log::Update");
		m_env.pLog->Update();
	}

#if !defined(RELEASE) || defined(RELEASE_LOGGING)
	GetIRemoteConsole()->Update();
#endif

	if (gEnv->pLocalMemoryUsage != NULL)
	{
		gEnv->pLocalMemoryUsage->OnUpdate();
	}

	if (!gEnv->IsEditor() && gEnv->pRenderer)
	{
		CCamera rCamera = GetViewCamera();

		// if aspect ratio changes or is different from default we need to update camera
		const float fNewAspectRatio = gEnv->pRenderer->GetPixelAspectRatio();
		const int nNewWidth = gEnv->pRenderer->GetOverlayWidth();
		const int nNewHeight = gEnv->pRenderer->GetOverlayHeight();

		if ((fNewAspectRatio != rCamera.GetPixelAspectRatio()) ||
			(nNewWidth != rCamera.GetViewSurfaceX()) ||
			(nNewHeight != rCamera.GetViewSurfaceZ()))
		{
			rCamera.SetFrustum(
				nNewWidth,
				nNewHeight,
				rCamera.GetFov(),
				rCamera.GetNearPlane(),
				rCamera.GetFarPlane(),
				fNewAspectRatio);

			SetViewCamera(rCamera);
		}
	}


	if (nPauseMode != 0)
		m_bPaused = true;
	else
		m_bPaused = false;

#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	if (m_bIgnoreUpdates)
		return true;
#endif //EXCLUDE_UPDATE_ON_CONSOLE

	const bool bNotLoading = !IsLoading();

	if (m_env.pCharacterManager)
	{
		if (bNotLoading)
		{
			m_env.pCharacterManager->Update(nPauseMode != 0);
		}
		else
		{
			m_env.pCharacterManager->DummyUpdate();
		}
	}

	bool bNoUpdate = false;
#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	//check what is the current process
	IProcess* pProcess = GetIProcess();
	if (!pProcess)
		return (true); //should never happen

	if (m_sysNoUpdate && m_sysNoUpdate->GetIVal())
	{
		bNoUpdate = true;
		updateFlags = { ESYSUPDATE_IGNORE_AI, ESYSUPDATE_IGNORE_PHYSICS };
	}

	m_bNoUpdate = bNoUpdate;
#endif //EXCLUDE_UPDATE_ON_CONSOLE
	//check if we are quitting from the game
	if (IsQuitting())
		return (false);

#if CRY_PLATFORM_WINDOWS
	// process window messages
	{
		CRY_PROFILE_SECTION(PROFILE_SYSTEM, "SysUpdate:PeekMessageW");

		if (m_hWnd && ::IsWindow((HWND)m_hWnd))
		{
			PumpWindowMessage(true, m_hWnd);
		}
	}
#endif

	//////////////////////////////////////////////////////////////////////
	//update time subsystem
	m_Time.UpdateOnFrameStart();



	// Don't do a thing if we're not in a level
	if (m_env.p3DEngine && bNotLoading)
		m_env.p3DEngine->OnFrameStart();



	//////////////////////////////////////////////////////////////////////
	// initial network update
	if (m_env.pNetwork)
	{
		m_env.pNetwork->SyncWithGame(eNGS_FrameStart);
	}

	//////////////////////////////////////////////////////////////////////////
	// Update script system.
	if (m_env.pScriptSystem && bNotLoading)
	{
		m_env.pScriptSystem->Update();
	}

	if (m_env.pInput)
	{
		bool updateInput =
			!(updateFlags & ESYSUPDATE_EDITOR) ||
			(updateFlags & ESYSUPDATE_EDITOR_AI_PHYSICS);
		if (updateInput)
		{
			//////////////////////////////////////////////////////////////////////
			//update input system
#if !CRY_PLATFORM_WINDOWS
			m_env.pInput->Update(true);
#else
			bool bFocus = (::GetForegroundWindow() == m_hWnd) || m_env.IsEditor();
			{
				WriteLock lock(g_lockInput);
				m_env.pInput->Update(bFocus);
				g_BreakListenerTask.m_nBreakIdle = 0;
			}
#endif
		}
	}

	//////////////////////////////////////////////////////////////////////
	//update console system
	if (m_env.pConsole)
	{
		CRY_PROFILE_SECTION(PROFILE_SYSTEM, "SysUpdate:Console");

		if (!(updateFlags & ESYSUPDATE_EDITOR))
			m_env.pConsole->Update();
	}
#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	//////////////////////////////////////////////////////////////////////
	//update notification network system
	if (m_pNotificationNetwork)
	{
		m_pNotificationNetwork->Update();
	}
#endif //EXCLUDE_UPDATE_ON_CONSOLE

	// When in Editor and outside of Game Mode we will need to update the listeners here.
	// But when in Editor and in Game Mode the ViewSystem will update the listeners.
	if (!m_env.IsEditorGameMode())
	{
		if (updateFlags.Check(ESYSUPDATE_EDITOR) && !bNoUpdate && nPauseMode != 1)
		{
			gEnv->pGameFramework->GetIViewSystem()->UpdateAudioListeners();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Update Resource Manager.
	//////////////////////////////////////////////////////////////////////////
	m_pResourceManager->Update();



	// Use UI timer for CryMovie, because it should not be affected by pausing game time
	const float fMovieFrameTime = m_Time.GetFrameTime(ITimer::ETIMER_UI);

	// Run movie system pre-update
	if (!bNoUpdate)
	{
		UpdateMovieSystem(updateFlags.UnderlyingValue(), fMovieFrameTime, true);
	}

#ifndef EXCLUDE_UPDATE_ON_CONSOLE
	if (nPauseMode != 1)
#endif //EXCLUDE_UPDATE_ON_CONSOLE
	{
		//////////////////////////////////////////////////////////////////////
		//update entity system
		if (m_env.pEntitySystem && !bNoUpdate && g_cvars.sys_entitysystem)
		{
			m_env.pEntitySystem->Update();
		}
	}

	// Run movie system post-update
	if (!bNoUpdate)
	{
		UpdateMovieSystem(updateFlags.UnderlyingValue(), fMovieFrameTime, false);
	}

	//////////////////////////////////////////////////////////////////////
	//update process (3D engine)
	if (!(updateFlags & ESYSUPDATE_EDITOR) && !bNoUpdate)
	{
		if (ITimeOfDay* pTOD = m_env.p3DEngine->GetTimeOfDay())
			pTOD->Tick();

		if (m_env.p3DEngine)
			m_env.p3DEngine->Tick();  // clear per frame temp data

		if (m_pProcess)
		{
			if (m_pProcess->GetFlags() & PROC_3DENGINE)
			{
				if ((nPauseMode != 1) && !IsEquivalent(m_ViewCamera.GetPosition(), Vec3(0, 0, 0), VEC_EPSILON))
				{
					m_pProcess->Update();
				}
			}
			else
			{
				m_pProcess->Update();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////
	//update sound system part 2
	if (!bNoUpdate)
	{
		UpdateAudioSystems();
	}

	//////////////////////////////////////////////////////////////////////
	// final network update
	if (m_env.pNetwork)
	{
		m_env.pNetwork->SyncWithGame(eNGS_FrameEnd);
		m_env.pNetwork->SyncWithGame(eNGS_DisplayDebugInfo);
		m_env.pNetwork->SyncWithGame(eNGS_WakeNetwork);   // This will wake the network thread up
	}

#ifdef DOWNLOAD_MANAGER
	if (m_pDownloadManager && !bNoUpdate)
	{
		m_pDownloadManager->Update();
	}
#endif //DOWNLOAD_MANAGER
#if !CRY_PLATFORM_LINUX && !CRY_PLATFORM_ANDROID && !CRY_PLATFORM_ORBIS
	if (m_sys_SimulateTask->GetIVal() > 0)
	{
		// have a chance to win longest Pi calculation content
		int64 delay = m_sys_SimulateTask->GetIVal();
		int64 start = CryGetTicks();
		double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4.0, p = 1.0, an, bn, tn, pn, Pi = 0.0;
		while (CryGetTicks() - start < delay)
		{
			// do something
			an = (a + b) / 2.0;
			bn = sqrt(a * b);
			tn = t - p * (a - an) * (a - an);
			pn = 2 * p;

			a = an;
			b = bn;
			t = tn;
			p = pn;

			Pi = (a + b) * (a + b) / 4 / t;
		}
		//CryLog("Task calculate PI = %f ", Pi); // Thats funny , but it works :-)
	}
#endif


	m_pSystemEventDispatcher->Update();

	if (gEnv->pSchematyc != nullptr)
	{
		gEnv->pSchematyc->Update();
	}


	//Now update frame statistics
	CTimeValue cur_time = gEnv->pTimer->GetAsyncTime();

	CTimeValue a_second(g_cvars.sys_update_profile_time);
	std::vector<std::pair<CTimeValue, float>>::iterator it = m_updateTimes.begin();
	for (std::vector<std::pair<CTimeValue, float>>::iterator eit = m_updateTimes.end(); it != eit; ++it)
		if ((cur_time - it->first) < a_second)
			break;

	if (it != m_updateTimes.begin())
		m_updateTimes.erase(m_updateTimes.begin(), it);

	float updateTime = (cur_time - updateStart).GetMilliSeconds();
	m_updateTimes.push_back(std::make_pair(cur_time, updateTime));

	UpdateUpdateTimes();

	return !m_bQuit;
}

IManualFrameStepController* CSystem::GetManualFrameStepController() const
{
	return nullptr;
}

bool CSystem::UpdateLoadtime()
{
	m_pPlatformOS->Tick(m_Time.GetRealFrameTime());

	/*
	   // uncomment this code if input processing is required
	   // during level loading
	   if (m_env.pInput)
	   {
		//////////////////////////////////////////////////////////////////////
		//update input system
	 #if !CRY_PLATFORM_WINDOWS
		m_env.pInput->Update(true);
	 #else
		bool bFocus = (GetFocus()==m_hWnd) || m_bEditor;
		{
		  WriteLock lock(g_lockInput);
		  m_env.pInput->Update(bFocus);
		  g_BreakListenerTask.m_nBreakIdle = 0;
		}
	 #endif
	   }
	 */

	return !m_bQuit;
}

void CSystem::UpdateAudioSystems()
{
	const bool isLoadInProgress = m_systemGlobalState > ESYSTEM_GLOBAL_STATE_INIT &&
								  m_systemGlobalState <= ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_END;

	if (m_env.pAudioSystem != nullptr && !isLoadInProgress)   //do not update pAudioSystem during async level load
	{
		CRY_PROFILE_SECTION(PROFILE_SYSTEM, "UpdateAudioSystems");

		m_env.pAudioSystem->ExternalUpdate();
	}
}

//////////////////////////////////////////////////////////////////////////
void CSystem::GetUpdateStats(SSystemUpdateStats& stats)
{
	if (m_updateTimes.empty())
	{
		stats = SSystemUpdateStats();
	}
	else
	{
		stats.avgUpdateTime = 0;
		stats.maxUpdateTime = -FLT_MAX;
		stats.minUpdateTime = +FLT_MAX;
		for (std::vector<std::pair<CTimeValue, float>>::const_iterator it = m_updateTimes.begin(), eit = m_updateTimes.end(); it != eit; ++it)
		{
			const float t = it->second;
			stats.avgUpdateTime += t;
			stats.maxUpdateTime = max(stats.maxUpdateTime, t);
			stats.minUpdateTime = min(stats.minUpdateTime, t);
		}
		stats.avgUpdateTime /= m_updateTimes.size();

		size_t sz = m_updateTimes.size();
		if (sz > 1)
		{
			const std::pair<CTimeValue, float> head = m_updateTimes.front();
			const std::pair<CTimeValue, float> tail = m_updateTimes.back();
			stats.avgUpdateRate = (sz - 1) / (tail.first - head.first).GetSeconds();
		}
		else
		{
			stats.avgUpdateRate = 0.0f;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CSystem::UpdateMovieSystem(const int updateFlags, const float fFrameTime, const bool bPreUpdate)
{
	if (m_env.pMovieSystem && !(updateFlags & ESYSUPDATE_EDITOR) && g_cvars.sys_trackview)
	{
		float fMovieFrameTime = fFrameTime;

		if (fMovieFrameTime > g_cvars.sys_maxTimeStepForMovieSystem)
			fMovieFrameTime = g_cvars.sys_maxTimeStepForMovieSystem;

		
	}
}

//////////////////////////////////////////////////////////////////////////
// XML stuff
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
XmlNodeRef CSystem::CreateXmlNode(const char* sNodeName, bool bReuseStrings)
{
	return new CXmlNode(sNodeName, bReuseStrings);
}

//////////////////////////////////////////////////////////////////////////
IXmlUtils* CSystem::GetXmlUtils()
{
	return m_pXMLUtils;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SetViewCamera(CCamera& Camera)
{
	m_ViewCamera = Camera;
	m_ViewCamera.CalculateRenderMatrices();
}

//////////////////////////////////////////////////////////////////////////
XmlNodeRef CSystem::LoadXmlFromFile(const char* sFilename, bool bReuseStrings)
{
	CRY_PROFILE_FUNCTION_ARG(PROFILE_LOADING_ONLY, sFilename);

	return m_pXMLUtils->LoadXmlFromFile(sFilename, bReuseStrings);
}

//////////////////////////////////////////////////////////////////////////
XmlNodeRef CSystem::LoadXmlFromBuffer(const char* buffer, size_t size, bool bReuseStrings)
{
	CRY_PROFILE_FUNCTION(PROFILE_LOADING_ONLY)
	return m_pXMLUtils->LoadXmlFromBuffer(buffer, size, bReuseStrings);
}

//////////////////////////////////////////////////////////////////////////
bool CSystem::CheckLogVerbosity(int verbosity)
{
	if (verbosity <= m_env.pLog->GetVerbosityLevel())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::Warning(EValidatorModule module, EValidatorSeverity severity, int flags, const char* file, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	WarningV(module, severity, flags, file, format, args);
	va_end(args);
}

//////////////////////////////////////////////////////////////////////////
void CSystem::WarningOnce(EValidatorModule module, EValidatorSeverity severity, int flags, const char* file, const char* format, ...)
{
	char szBuffer[MAX_WARNING_LENGTH];
	va_list args;
	va_start(args, format);
	cry_vsprintf(szBuffer, format, args);
	va_end(args);

	CryAutoLock<CryMutex> lock(m_mapWarningOnceMutex);
	uint32 crc = CCrc32::ComputeLowercase(szBuffer);
	if (m_mapWarningOnceAlreadyPrinted.find(crc) == m_mapWarningOnceAlreadyPrinted.end())
	{
		m_mapWarningOnceAlreadyPrinted[crc] = true;

		Warning(VALIDATOR_MODULE_ANIMATION, VALIDATOR_WARNING, VALIDATOR_FLAG_FILE, 0, szBuffer);
	}
}

inline const char* ValidatorModuleToString(EValidatorModule module)
{
	switch (module)
	{
	case VALIDATOR_MODULE_RENDERER:
		return "Renderer";
	case VALIDATOR_MODULE_3DENGINE:
		return "3DEngine";
	case VALIDATOR_MODULE_ASSETS:
		return "Assets";
	case VALIDATOR_MODULE_AI:
		return "AI";
	case VALIDATOR_MODULE_ANIMATION:
		return "Animation";
	case VALIDATOR_MODULE_ENTITYSYSTEM:
		return "EntitySystem";
	case VALIDATOR_MODULE_SCRIPTSYSTEM:
		return "Script";
	case VALIDATOR_MODULE_SYSTEM:
		return "System";
	case VALIDATOR_MODULE_AUDIO:
		return "Audio";
	case VALIDATOR_MODULE_GAME:
		return "Game";
	case VALIDATOR_MODULE_MOVIE:
		return "Movie";
	case VALIDATOR_MODULE_EDITOR:
		return "Editor";
	case VALIDATOR_MODULE_NETWORK:
		return "Network";
	case VALIDATOR_MODULE_PHYSICS:
		return "Physics";
	case VALIDATOR_MODULE_FLOWGRAPH:
		return "FlowGraph";
	case VALIDATOR_MODULE_ONLINE:
		return "Online";
	case VALIDATOR_MODULE_DRS:
		return "DynamicResponseSystem";
	default:
		break;
	}
	return "";
}

//////////////////////////////////////////////////////////////////////////
void CSystem::WarningV(EValidatorModule module, EValidatorSeverity severity, int flags, const char* file, const char* format, va_list args)
{
	// Fran: No logging in a testing environment
	if (m_env.pLog == 0)
	{
		return;
	}

	const char* sModuleFilter = m_env.pLog->GetModuleFilter();
	if (sModuleFilter && *sModuleFilter != 0)
	{
		const char* sModule = ValidatorModuleToString(module);
		if (strlen(sModule) > 1 || CryStringUtils::stristr(sModule, sModuleFilter) == 0)
		{
			// Filter out warnings from other modules.
			return;
		}
	}

	bool bDbgBreak = false;
	if (severity == VALIDATOR_ERROR_DBGBRK)
	{
		bDbgBreak = true;
		severity = VALIDATOR_ERROR; // change it to a standard VALIDATOR_ERROR for simplicity in the rest of the system
	}

	IMiniLog::ELogType ltype = ILog::eComment;
	switch (severity)
	{
	case VALIDATOR_ERROR:
		ltype = ILog::eError;
		break;
	case VALIDATOR_WARNING:
		ltype = ILog::eWarning;
		break;
	case VALIDATOR_COMMENT:
		ltype = ILog::eComment;
		break;
	case VALIDATOR_ASSERT:
		ltype = ILog::eAssert;
		break;
	default:
		break;
	}
	char szBuffer[MAX_WARNING_LENGTH];
	cry_vsprintf(szBuffer, format, args);

	if (file && *file)
	{
		CryFixedStringT<MAX_WARNING_LENGTH> fmt = szBuffer;
		fmt += " [File=";
		fmt += file;
		fmt += "]";

		m_env.pLog->LogWithType(ltype, flags | VALIDATOR_FLAG_SKIP_VALIDATOR, "%s", fmt.c_str());
	}
	else
	{
		m_env.pLog->LogWithType(ltype, flags | VALIDATOR_FLAG_SKIP_VALIDATOR, "%s", szBuffer);
	}

	//if(file)
	//m_env.pLog->LogWithType( ltype, "  ... caused by file '%s'",file);

	if (m_pValidator && (flags & VALIDATOR_FLAG_SKIP_VALIDATOR) == 0)
	{
		SValidatorRecord record;
		record.file = file;
		record.text = szBuffer;
		record.module = module;
		record.severity = severity;
		record.flags = flags;
		record.assetScope = m_env.pLog->GetAssetScopeString();
		m_pValidator->Report(record);
	}

#if !defined(_RELEASE)
	if (bDbgBreak && g_cvars.sys_error_debugbreak)
		__debugbreak();
#endif
}

//////////////////////////////////////////////////////////////////////////
void CSystem::Deltree(const char* szFolder, bool bRecurse)
{
	__finddata64_t fd;
	string filespec = szFolder;
	filespec += "*.*";

	intptr_t hfil = 0;
	if ((hfil = _findfirst64(filespec.c_str(), &fd)) == -1)
	{
		return;
	}

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			string name = fd.name;

			if ((name != ".") && (name != ".."))
			{
				if (bRecurse)
				{
					name = szFolder;
					name += fd.name;
					name += "/";

					Deltree(name.c_str(), bRecurse);
				}
			}
		}
		else
		{
			string name = szFolder;

			name += fd.name;

			DeleteFile(name.c_str());
		}

	}
	while (!_findnext64(hfil, &fd));

	_findclose(hfil);

	RemoveDirectory(szFolder);
}

//////////////////////////////////////////////////////////////////////////
void CSystem::GetLocalizedPath(char const* const szLanguage, string& szLocalizedPath)
{
	string pakSuffix = (g_cvars.sys_localization_pak_suffix) ? g_cvars.sys_localization_pak_suffix->GetString() : "";
	szLocalizedPath = PathUtil::GetLocalizationFolder() + CRY_NATIVE_PATH_SEPSTR + szLanguage + pakSuffix + ".pak";
}

//////////////////////////////////////////////////////////////////////////
void CSystem::GetLocalizedAudioPath(char const* const szLanguage, string& szLocalizedPath)
{
	szLocalizedPath = PathUtil::GetLocalizationFolder() + CRY_NATIVE_PATH_SEPSTR + szLanguage + ".pak";
}

//////////////////////////////////////////////////////////////////////////
void CSystem::CloseLanguagePak(char const* const szLanguage)
{
	string szLocalizedPath;
	GetLocalizedPath(szLanguage, szLocalizedPath);
	m_env.pCryPak->ClosePacks(szLocalizedPath);
}

//////////////////////////////////////////////////////////////////////////
void CSystem::CloseLanguageAudioPak(char const* const szLanguage)
{
	string szLocalizedPath;
	GetLocalizedAudioPath(szLanguage, szLocalizedPath);
	m_env.pCryPak->ClosePacks(szLocalizedPath);
}

#if CRY_PLATFORM_DURANGO
//////////////////////////////////////////////////////////////////////////
void CSystem::OnPLMEvent(EPLM_Event event)
{

	switch (event)
	{
	case EPLMEV_ON_RESUMING:
		{
			CryLogAlways("CSystem::OnPLMEvent --- OnResuming");
			if (m_pSystemEventDispatcher)
				m_pSystemEventDispatcher->OnSystemEvent(ESYSTEM_EVENT_PLM_ON_RESUMING, 0, 0);
			if (gEnv->pRenderer)
				gEnv->pRenderer->ResumeDevice();
			gEnv->ePLM_State = EPLM_RUNNING;
			break;
		}

	case EPLMEV_ON_SUSPENDING:
		{
			CryLogAlways("CSystem::OnPLMEvent --- OnSuspending");
			if (m_pSystemEventDispatcher)
				m_pSystemEventDispatcher->OnSystemEvent(ESYSTEM_EVENT_PLM_ON_SUSPENDING, 0, 0);
			if (gEnv->pRenderer)
				gEnv->pRenderer->SuspendDevice();
			gEnv->ePLM_State = EPLM_SUSPENDED;
			break;
		}

	case EPLMEV_ON_CONSTRAINED:
		{
			CryLogAlways("CSystem::OnPLMEvent --- OnConstrained");
			if (m_pSystemEventDispatcher)
				m_pSystemEventDispatcher->OnSystemEvent(ESYSTEM_EVENT_PLM_ON_CONSTRAINED, 0, 0);
			gEnv->ePLM_State = EPLM_CONSTRAINED;
			break;
		}

	case EPLMEV_ON_FULL:
		{
			CryLogAlways("CSystem::OnPLMEvent --- OnFull");
			if (m_pSystemEventDispatcher)
				m_pSystemEventDispatcher->OnSystemEvent(ESYSTEM_EVENT_PLM_ON_FULL, 0, 0);
			gEnv->ePLM_State = EPLM_RUNNING;
			break;
		}

	default:
		{
			CryWarning(VALIDATOR_MODULE_SYSTEM, VALIDATOR_ERROR, "Unhandled PLM Event!");
			break;
		}
	}
}
#endif

//////////////////////////////////////////////////////////////////////////
void CSystem::UnloadSchematycModule()
{
}

//////////////////////////////////////////////////////////////////////////
void CSystem::Relaunch(bool bRelaunch)
{
	if (m_sys_firstlaunch)
		m_sys_firstlaunch->Set(0);

	m_bRelaunch = bRelaunch;
	SaveConfiguration();
}

//////////////////////////////////////////////////////////////////////////
ICrySizer* CSystem::CreateSizer()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
uint32 CSystem::GetUsedMemory()
{
	return CryMemoryGetAllocatedSize();
}

//////////////////////////////////////////////////////////////////////////
ILocalizationManager* CSystem::GetLocalizationManager()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
IResourceManager* CSystem::GetIResourceManager()
{
	return m_pResourceManager;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::debug_GetCallStackRaw(void** callstack, uint32& callstackLength)
{
#if CRY_PLATFORM_ORBIS || CRY_PLATFORM_WINAPI
	uint32 callstackCapacity = callstackLength;
#endif

#if CRY_PLATFORM_WINAPI
	uint32 nNumStackFramesToSkip = 1;
#endif

	memset(callstack, 0, sizeof(void*) * callstackLength);

#if !CRY_PLATFORM_ANDROID
	callstackLength = 0;
#endif

#if CRY_PLATFORM_ORBIS
	uint csLength = 0;
	void** stack = NULL;
	__asm__ __volatile__ ("mov %%rbp, %0" : "=r" (stack)); // WARNING: This could be brittle
	while (csLength < callstackCapacity && stack)
	{
		callstack[csLength] = stack[1];
		stack = (void**)stack[0];
		csLength++;
	}
	callstackLength = csLength;
#elif CRY_PLATFORM_WINAPI
	if (callstackCapacity > 0x40)
		callstackCapacity = 0x40;
	callstackLength = RtlCaptureStackBackTrace(nNumStackFramesToSkip, callstackCapacity, callstack, NULL);
#endif
	/*
	   static int aaa = 0;
	   aaa++;

	   if ((aaa & 0xF)  == 0)
	   {
	   CryLogAlways( "RtlCaptureStackBackTrace = (%d)",callstackLength );
	   for (int i=0; i<callstackLength; i++)
	   {
	   CryLogAlways( "   [%d] = (%X)",i,callstack[i] );
	   }
	   }

	   callstackLength = IDebugCallStack::instance()->CollectCallStackFrames( callstack,callstackCapacity );
	   if ((aaa & 0xF)  == 0)
	   {
	   CryLogAlways( "StackWalk64 = (%d)",callstackLength );
	   for (int i=0; i<callstackLength; i++)
	   {
	   CryLogAlways( "   [%d] = (%X)",i,callstack[i] );
	   }
	   }
	 */

	if (callstackLength > 0)
	{
		std::reverse(callstack, callstack + callstackLength);
	}
}

//////////////////////////////////////////////////////////////////////////
void CSystem::ExecuteCommandLine()
{
	CRY_PROFILE_FUNCTION(PROFILE_LOADING_ONLY);
	// should only be called once
	{
		static bool bCalledAlready = false;
		assert(!bCalledAlready);
		bCalledAlready = true;
	}


	// execute command line arguments e.g. +g_gametype ASSAULT +map "testy"

	ICmdLine* pCmdLine = GetICmdLine();
	assert(pCmdLine);

	const int iCnt = pCmdLine->GetArgCount();

	for (int i = 0; i < iCnt; ++i)
	{
		const ICmdLineArg* pCmd = pCmdLine->GetArg(i);

		if (pCmd->GetType() == eCLAT_Post)
		{
			string sLine = pCmd->GetName();

			if (gEnv->pSystem->IsCVarWhitelisted(sLine.c_str(), false))
			{
				if (pCmd->GetValue())
					sLine += string(" ") + pCmd->GetValue();

				GetILog()->Log("Executing command from command line: \n%s\n", sLine.c_str()); // - the actual command might be executed much later (e.g. level load pause)
				GetIConsole()->ExecuteString(sLine.c_str(), false, !m_bShaderCacheGenMode);
			}
#if defined(DEDICATED_SERVER)
			else
			{
				GetILog()->LogError("Failed to execute command: '%s' as it is not whitelisted\n", sLine.c_str());
			}
#endif
		}
	}

	//gEnv->pConsole->ExecuteString("sys_RestoreSpec test*"); // to get useful debugging information about current spec settings to the log file
}

ITextModeConsole* CSystem::GetITextModeConsole()
{
	if (m_env.IsDedicated())
		return m_pTextModeConsole;

	return 0;
}

//////////////////////////////////////////////////////////////////////////
ESystemConfigSpec CSystem::GetConfigSpec(bool bClient)
{
	if (bClient)
	{
		if (m_sys_spec)
			return (ESystemConfigSpec)m_sys_spec->GetIVal();
		return CONFIG_VERYHIGH_SPEC; // highest spec.
	}
	else
		return m_nServerConfigSpec;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::SetConfigSpec(ESystemConfigSpec spec, bool bClient)
{
	if (bClient)
	{
		if (m_sys_spec)
			m_sys_spec->Set((int)spec);
	}
	else
	{
		m_nServerConfigSpec = spec;
	}
}

//////////////////////////////////////////////////////////////////////////
ESystemConfigSpec CSystem::GetMaxConfigSpec() const
{
	return m_nMaxConfigSpec;
}

//////////////////////////////////////////////////////////////////////////
Cry::IProjectManager* CSystem::GetIProjectManager()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
CPNoise3* CSystem::GetNoiseGen()
{
	static CPNoise3 m_pNoiseGen;
	return &m_pNoiseGen;
}

//////////////////////////////////////////////////////////////////////////
sUpdateTimes& CSystem::GetCurrentUpdateTimeStats()
{
	return m_UpdateTimes[m_UpdateTimesIdx];
}

//////////////////////////////////////////////////////////////////////////
const sUpdateTimes* CSystem::GetUpdateTimeStats(uint32& index, uint32& num)
{
	index = m_UpdateTimesIdx;
	num = NUM_UPDATE_TIMES;
	return m_UpdateTimes;
}

void CSystem::FillRandomMT(uint32* pOutWords, uint32 numWords)
{
	AUTO_LOCK(m_mtLock);
	if (!m_pMtState)
	{
		struct TicksTime
		{
			int64  ticks;
			time_t tm;
		};

		TicksTime tt = { CryGetTicks(), time(nullptr) };
		m_pMtState = new CMTRand_int32(reinterpret_cast<uint32*>(&tt), sizeof(tt) / sizeof(uint32));
	}

	for (uint32 i = 0; i < numWords; ++i)
		pOutWords[i] = m_pMtState->GenerateUint32();
}

void CSystem::UpdateUpdateTimes()
{
	sUpdateTimes& sample = m_UpdateTimes[m_UpdateTimesIdx];
	if (m_PhysThread)
	{
		static uint64 lastMainTime = 0U;
		static uint64 lastPhysWait = 0U;
		uint64 physTime = 0, mainTime = 0;
		uint32 yields = 0;
		physTime = ((CPhysicsThreadTask*)m_PhysThread)->LastStepTaken();
		mainTime = CryGetTicks() - lastMainTime;
		lastMainTime = mainTime;
		lastPhysWait = ((CPhysicsThreadTask*)m_PhysThread)->LastWaitTime();
		sample.PhysStepTime = physTime;
		sample.SysUpdateTime = mainTime;
		sample.PhysYields = yields;
		sample.physWaitTime = lastPhysWait;
	}
	++m_UpdateTimesIdx;
	if (m_UpdateTimesIdx >= NUM_UPDATE_TIMES) m_UpdateTimesIdx = 0;
}

IPhysicsDebugRenderer* CSystem::GetIPhysicsDebugRenderer()
{
	return nullptr;
}

IPhysRenderer* CSystem::GetIPhysRenderer()
{
	return nullptr;
}

ICryProfilingSystem* CSystem::GetProfilingSystem()
{
	return m_pProfilingSystem;
}

ILegacyProfiler* CSystem::GetLegacyProfilerInterface()
{
	return m_pLegacyProfiler;
}

#ifndef _RELEASE
void CSystem::GetCheckpointData(ICheckpointData& data)
{
	data.m_totalLoads = m_checkpointLoadCount;
	data.m_loadOrigin = m_loadOrigin;
}

void CSystem::IncreaseCheckpointLoadCount()
{
	if (!m_hasJustResumed)
		++m_checkpointLoadCount;

	m_hasJustResumed = false;
}

void CSystem::SetLoadOrigin(LevelLoadOrigin origin)
{
	switch (origin)
	{
	case eLLO_NewLevel: // Intentional fall through
	case eLLO_Level2Level:
		m_expectingMapCommand = true;
		break;

	case eLLO_Resumed:
		m_hasJustResumed = true;
		break;

	case eLLO_MapCmd:
		if (m_expectingMapCommand)
		{
			// We knew a map command was coming, so don't process this.
			m_expectingMapCommand = false;
			return;
		}
		break;
	default:
		break;
	}

	m_loadOrigin = origin;
	m_checkpointLoadCount = 0;
}
#endif

//////////////////////////////////////////////////////////////////////
void CSystem::OnLanguageCVarChanged(ICVar* const pLanguage)
{
	
}

//////////////////////////////////////////////////////////////////////
void CSystem::OnLanguageAudioCVarChanged(ICVar* const pLanguageAudio)
{
	if (pLanguageAudio != nullptr && pLanguageAudio->GetType() == ECVarType::String)
	{
		CSystem* const pSystem = static_cast<CSystem*>(gEnv->pSystem);

		if (pSystem != nullptr)
		{
			char const* const szNewLanguage = pLanguageAudio->GetString();

			if (!pSystem->m_currentLanguageAudio.empty())
			{
				pSystem->CloseLanguageAudioPak(pSystem->m_currentLanguageAudio.c_str());
			}

			pSystem->m_currentLanguageAudio = szNewLanguage;

			pSystem->GetISystemEventDispatcher()->OnSystemEvent(ESYSTEM_EVENT_AUDIO_LANGUAGE_CHANGED, 0, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CSystem::OnLocalizationFolderCVarChanged(ICVar* const pLocalizationFolder)
{
	
}

void CSystem::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_LEVEL_LOAD_END:
		{
			SetSystemGlobalState(ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_END);
		}
		break;
	case ESYSTEM_EVENT_LEVEL_LOAD_START_LOADINGSCREEN:
	case ESYSTEM_EVENT_LEVEL_UNLOAD:
		{
			gEnv->pCryPak->DisableRuntimeFileAccess(false);
		}
		break;
	case ESYSTEM_EVENT_LEVEL_PRECACHE_END:
		{
			if (!gEnv->IsEditing())
			{
				gEnv->pCryPak->DisableRuntimeFileAccess(true);
			}
		}
		break;
	default:
		break;
	}
}

ESystemGlobalState CSystem::GetSystemGlobalState(void)
{
	return m_systemGlobalState;
}

const char* CSystem::GetSystemGlobalStateName(const ESystemGlobalState systemGlobalState)
{
	static const char* const s_systemGlobalStateNames[] = {
		"INIT",                    // ESYSTEM_GLOBAL_STATE_INIT,
		"LEVEL_LOAD_PREPARE",      // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_PREPARE,
		"LEVEL_LOAD_START",        // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START,
		"LEVEL_LOAD_MATERIALS",    // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_MATERIALS,
		"LEVEL_LOAD_OBJECTS",      // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_OBJECTS,
		"LEVEL_LOAD_CHARACTERS",   // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_CHARACTERS,
		"LEVEL_LOAD_STATIC_WORLD", // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_STATIC_WORLD,
		"LEVEL_LOAD_ENTITIES",     // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_ENTITIES,
		"LEVEL_LOAD_PRECACHE",     // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_PRECACHE,
		"LEVEL_LOAD_TEXTURES",     // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_START_TEXTURES,
		"LEVEL_LOAD_END",          // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_END,
		"LEVEL_LOAD_ENDING",       // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_ENDING,
		"LEVEL_LOAD_COMPLETE",     // ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_COMPLETE
		"RUNNING",                 // ESYSTEM_GLOBAL_STATE_RUNNING,
	};
	const size_t numElements = CRY_ARRAY_COUNT(s_systemGlobalStateNames);
	const size_t index = (size_t)systemGlobalState;
	if (index >= numElements)
	{
		return "INVALID INDEX";
	}
	return s_systemGlobalStateNames[index];
}

void CSystem::SetSystemGlobalState(const ESystemGlobalState systemGlobalState)
{
	static CTimeValue s_startTime = CTimeValue();
	if (systemGlobalState != m_systemGlobalState)
	{
		if (gEnv && gEnv->pTimer)
		{
#if !defined(EXCLUDE_NORMAL_LOG)
			const CTimeValue endTime = gEnv->pTimer->GetAsyncTime();
			const float numSeconds = endTime.GetDifferenceInSeconds(s_startTime);
#endif
			CryLog("SetGlobalState %d->%d '%s'->'%s' %3.1f seconds",
				   m_systemGlobalState, systemGlobalState,
				   CSystem::GetSystemGlobalStateName(m_systemGlobalState), CSystem::GetSystemGlobalStateName(systemGlobalState),
				   numSeconds);
			s_startTime = gEnv->pTimer->GetAsyncTime();
		}
	}
	m_systemGlobalState = systemGlobalState;
}

//////////////////////////////////////////////////////////////////////////
void CSystem::RegisterWindowMessageHandler(IWindowMessageHandler* pHandler)
{
	assert(pHandler && !stl::find(m_windowMessageHandlers, pHandler) && "This IWindowMessageHandler is already registered");
	m_windowMessageHandlers.push_back(pHandler);
}

//////////////////////////////////////////////////////////////////////////
void CSystem::UnregisterWindowMessageHandler(IWindowMessageHandler* pHandler)
{
#if defined(USE_CRY_ASSERT)
	bool bRemoved = stl::find_and_erase(m_windowMessageHandlers, pHandler);
	assert(pHandler && bRemoved && "This IWindowMessageHandler was not registered");
#else
	stl::find_and_erase(m_windowMessageHandlers, pHandler);
#endif
}

//////////////////////////////////////////////////////////////////////////
int CSystem::PumpWindowMessage(bool bAll, CRY_HWND opaqueHWnd)
{
#if CRY_PLATFORM_WINDOWS
	int count = 0;
	const HWND hWnd = (HWND)opaqueHWnd;
	const bool bUnicode = hWnd != NULL ?
						  IsWindowUnicode(hWnd) != FALSE :
						  !(gEnv && gEnv->IsEditor());
	#if defined(UNICODE) || defined(_UNICODE)
	// Once we compile as Unicode app on Windows, we should detect non-Unicode windows
	assert(bUnicode && "The window is not Unicode, this is most likely a bug");
	#endif

	// Pick the correct function for handling messages
	typedef BOOL (WINAPI *    PeekMessageFunc)(MSG*, HWND, UINT, UINT, UINT);
	typedef LRESULT (WINAPI * DispatchMessageFunc)(const MSG*);
	const PeekMessageFunc pfnPeekMessage = bUnicode ? PeekMessageW : PeekMessageA;
	const DispatchMessageFunc pfnDispatchMessage = bUnicode ? DispatchMessageW : DispatchMessageA;

	do
	{
		// Get a new message
		MSG msg;
		BOOL bHasMessage = pfnPeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
		if (bHasMessage == FALSE) break;
		++count;

		// Special case for WM_QUIT
		if (msg.message == WM_QUIT)
		{
			return -1;
		}

		if (msg.message == WM_ACTIVATE)
		{
			if (msg.wParam != WA_INACTIVE)
				m_hWndActive = msg.hwnd;
			else
				m_hWndActive = (CRY_HWND)msg.lParam;

			// During the time demo, do not sleep even in inactive window.
			if (!gEnv->pGameFramework || !gEnv->pGameFramework->IsInTimeDemo())
				// use sys_maxFPS to throttle the engine
				m_throttleFPS = msg.wParam != WA_INACTIVE;
		}

		// Pre-process the message for IME
		if (msg.hwnd == m_hWnd)
		{
			for (std::vector<IWindowMessageHandler*>::const_iterator it = m_windowMessageHandlers.begin(); it != m_windowMessageHandlers.end(); ++it)
			{
				IWindowMessageHandler* pHandler = *it;
				pHandler->PreprocessMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
			}
		}

		// Dispatch the message
		TranslateMessage(&msg);
		pfnDispatchMessage(&msg);
	}
	while (bAll);

	return count;
#else
	// No window message support on this platform
	return 0;
#endif
}

//////////////////////////////////////////////////////////////////////////
bool CSystem::IsImeSupported() const
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool CSystem::IsCVarWhitelisted(const char* szName, bool silent) const
{
	CRY_ASSERT(szName != nullptr);

	if (szName[0] == '?')
	{
		return true;
	}

	if (szName[0] == '+')
	{
		++szName;
	}

	const char* pNameEnd = std::max(strchr(szName, ' '), strchr(szName, '='));
	if (pNameEnd == nullptr)
	{
		return ::IsCVarWhitelisted(szName);
	}
	else
	{
		const string name(szName, pNameEnd);
		return ::IsCVarWhitelisted(name.c_str());
	}
}

//////////////////////////////////////////////////////////////////////////
#if CRY_PLATFORM_WINDOWS

enum class EMouseWheelOrigin
{
	ScreenSpace,
	WindowSpace,
	WindowSpaceClamped
};

	#ifndef GET_X_LPARAM
		#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
	#endif
	#ifndef GET_Y_LPARAM
		#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
	#endif

bool CSystem::HandleMessage(CRY_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return true;
}

#endif

//////////////////////////////////////////////////////////////////////////
#if CRY_PLATFORM_WINDOWS
static LRESULT WINAPI WndProc(CRY_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CSystem* pSystem = 0;
	if (gEnv)
	{
		pSystem = static_cast<CSystem*>(gEnv->pSystem);
	}
	if (pSystem && !pSystem->m_bQuit)
	{
		LRESULT result;
		bool bAny = false;
		for (std::vector<IWindowMessageHandler*>::const_iterator it = pSystem->m_windowMessageHandlers.begin(); it != pSystem->m_windowMessageHandlers.end(); ++it)
		{
			IWindowMessageHandler* pHandler = *it;
			LRESULT maybeResult = 0xDEADDEAD;
			if (pHandler->HandleMessage(hWnd, uMsg, wParam, lParam, &maybeResult))
			{
				assert(maybeResult != 0xDEADDEAD && "Message handler indicated a resulting value, but no value was written");
				if (bAny)
				{
					assert(result == maybeResult && "Two window message handlers tried to return different result values");
				}
				else
				{
					bAny = true;
					result = maybeResult;
				}
			}
		}
		if (bAny)
		{
			// One of the registered handlers returned something
			return result;
		}
	}

	// Handle with the default procedure
	#if defined(UNICODE) || defined(_UNICODE)
	assert(IsWindowUnicode((HWND)hWnd) && "Window should be Unicode when compiling with UNICODE");
	#else
	if (!IsWindowUnicode((HWND)hWnd))
	{
		return DefWindowProcA((HWND)hWnd, uMsg, wParam, lParam);
	}
	#endif
	return DefWindowProcW((HWND)hWnd, uMsg, wParam, lParam);
}
#endif

//////////////////////////////////////////////////////////////////////////
void* CSystem::GetRootWindowMessageHandler()
{
#if CRY_PLATFORM_WINDOWS
	return &WndProc;
#else
	assert(false && "This platform does not support window message handlers");
	return NULL;
#endif
}

ICmdLine* CSystem::GetICmdLine()
{
	return m_pCmdLine;
}

Cry::IPluginManager* CSystem::GetIPluginManager()
{
	return nullptr;
}

uint32 CSystem::GetCPUFlags()
{
	return 0;
}

int CSystem::GetLogicalCPUCount()
{
	return 0;
}

#undef EXCLUDE_UPDATE_ON_CONSOLE
