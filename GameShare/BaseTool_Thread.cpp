#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "Util.h"
#include "BaseTool.h"

uint32		g_ThreadCount = 0;
uint32		g_WaitQuitThreadCount = 0;
FastLock	g_thread_lock;

/*
=======================================================================================================================
=======================================================================================================================
*/

KThread::KThread()
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TID = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	m_Status = KThread::THREAD_READY;
	m_TickCount = 0;
	m_Steps = 0;

#if defined(__WINDOWS__)
	m_hThread = NULL;
#endif
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
KThread::~KThread()
{
	__GUARD__ __UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void KThread::start()
{
	__GUARD__ 
	
	if(m_Status != KThread::THREAD_READY) 
		return;

#if defined(__LINUX__)
	int32 ret = pthread_create(&m_TID, NULL, ThreadEntry, this);
	if( ret != 0 )
	{
		char msg[32] = {0};
		sprintf(msg,"Start Thread Failed! ret=%d",ret);
		KCheckEx(FALSE,msg);
	}
#elif defined(__WINDOWS__)
	m_hThread = ::CreateThread(NULL, 0, ThreadEntry, this, CREATE_SUSPENDED, &m_TID);
	KCheck(NULL != m_hThread);
	m_TID = m_TID * 1000;
	ResumeThread(m_hThread);
#endif

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void KThread::stop()
{
	__GUARD__ __UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void KThread::exit(void *retval)
{
	_NET_TRY
	{
#if defined(__LINUX__)
		pthread_exit(retval);
#elif defined(__WINDOWS__)
		::CloseHandle(m_hThread);
#endif
	}

	_NET_CATCH
	{
	}
}

#if defined(__LINUX__)

/*
=======================================================================================================================
=======================================================================================================================
*/
void *ThreadEntry(void *derivedThread)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KThread	*thread = (KThread *) derivedThread;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(thread == NULL) return NULL;
	{
		lock_guard<FastLock> autolock(g_thread_lock);

		g_ThreadCount++;
	}

	while(FALSE);

	thread->setState(KThread::THREAD_RUNNING);
	thread->run();
	thread->setState(KThread::THREAD_FINISH);
	{
		lock_guard<FastLock> autolock(g_thread_lock);

		g_WaitQuitThreadCount++;
	}

	while(FALSE);

	__UNGUARD__ return NULL;
}

#elif defined(__WINDOWS__)

/*
=======================================================================================================================
=======================================================================================================================
*/
ulong WINAPI ThreadEntry(void *derivedThread)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KThread	*thread = (KThread *) derivedThread;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(thread == NULL) return 0;
	{
		lock_guard<FastLock> autolock(g_thread_lock);

		g_ThreadCount++;
	}

	while(FALSE);

	thread->setState(KThread::THREAD_RUNNING);
	thread->run();
	thread->setState(KThread::THREAD_FINISH);
	thread->exit(NULL);
	{
		lock_guard<FastLock> autolock(g_thread_lock);

		g_WaitQuitThreadCount++;
	}

	while(FALSE);

	__UNGUARD__ return 0;
}
#endif

/*
=======================================================================================================================
=======================================================================================================================
*/
void KThread::run()
{
	__GUARD__ __UNGUARD__
}
