
#include "stdafx.h"
#include "ArchiveHolder.h"
#include "BaseTool.h"

////////////////////////////////////////////////////////////////////////////////
// API Module
////////////////////////////////////////////////////////////////////////////////
#if __LINUX__
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#elif __WINDOWS__
#include <WinBase.h>
#endif

/*
=======================================================================================================================
=======================================================================================================================
*/
MKHandle ArchiveNode::CreateMemKeeper(MK_VALUE key, uint32 Size)
{
	__GUARD__
#if __LINUX__
		MKHandle hd = shmget(key, Size, IPC_CREAT | IPC_EXCL | 0666);
	printf("handle = %d ,key = %d ,error: %d \r\n", hd, key, errno);
	return hd;

	/*~~~~~~~~~~~~~~~*/
#elif __WINDOWS__
		char	keybuf[64];
	/*~~~~~~~~~~~~~~~*/

	memset(keybuf, 0, 64);
	sprintf(keybuf, "%d", key);
	return CreateFileMapping((HANDLE) 0xFFFFFFFFFFFFFFFF, NULL, PAGE_READWRITE, 0, Size, keybuf);
#endif
	__UNGUARD__ return MKHandle(-1);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
MKHandle ArchiveNode::OpenMenKeeper(MK_VALUE key, uint32 Size)
{
	__GUARD__
#if __LINUX__
		MKHandle hd = shmget(key, Size, 0);
	printf("handle = %d ,key = %d ,error: %d \r\n", hd, key, errno);
	return hd;

	/*~~~~~~~~~~~~~~~*/
#elif __WINDOWS__
		char	keybuf[64];
	/*~~~~~~~~~~~~~~~*/

	memset(keybuf, 0, 64);
	sprintf(keybuf, "%d", key);
	return OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, keybuf);
#endif
	__UNGUARD__ return MKHandle(-1);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
char *ArchiveNode::ViewMemKeeper(MKHandle handle)
{
	__GUARD__
#if __LINUX__
		return (char *) shmat(handle, 0, 0);
#elif __WINDOWS__
		return (char *) MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
#endif
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ArchiveNode::UnViewMemKeeper(char *MemoryPtr)
{
	__GUARD__
#if __LINUX__
		shmdt(MemoryPtr);
#elif __WINDOWS__
		UnmapViewOfFile(MemoryPtr);
#endif
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ArchiveNode::TerminateMemKeeper(MKHandle handle)
{
	__GUARD__
#if __LINUX__
		shmctl(handle, IPC_RMID, 0);
#elif __WINDOWS__
		CloseHandle(handle);
#endif
	__UNGUARD__
}

////////////////////////////////////////////////////////////////////////////////
// Unit Module
////////////////////////////////////////////////////////////////////////////////
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ArchiveNodeWrapper::Create(MK_VALUE key, uint32 Size)
{
	__GUARD__ if(m_CmdArg == CMD_MODE_CLEARALL) return FALSE;

	m_hold = ArchiveNode::CreateMemKeeper(key, Size);
	if(m_hold == INVALID_SM_HANDLE)
	{
		QLogSystem::SLOW_LOG(m_LogPath, "Create ShareMem Error SM_KET = %d", key);
		return FALSE;
	}

	m_pHeader = ArchiveNode::ViewMemKeeper(m_hold);

	if(m_pHeader)
	{
		m_pDataPtr = m_pHeader + sizeof(SMHead);
		((SMHead *) m_pHeader)->m_Key = key;
		((SMHead *) m_pHeader)->m_Size = Size;
		m_Size = Size;
		QLogSystem::SLOW_LOG(m_LogPath, "Create ShareMem Ok SM_KET = %d", key);
		return TRUE;
	}
	else
	{
		QLogSystem::SLOW_LOG(m_LogPath, "Map ShareMem Error SM_KET = %d", key);
		return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ArchiveNodeWrapper::Destory()
{
	__GUARD__ if(m_pHeader)
	{
		ArchiveNode::UnViewMemKeeper(m_pHeader);
		m_pHeader = 0;
	}

	if(m_hold)
	{
		ArchiveNode::TerminateMemKeeper(m_hold);
		m_hold = 0;
	}

	m_Size = 0;

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ArchiveNodeWrapper::ViewMap(MK_VALUE key, uint32 Size)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_hold = ArchiveNode::OpenMenKeeper(key, Size);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_CmdArg == CMD_MODE_CLEARALL)
	{
		Destory();
		printf("Close ShareMemory key = %d \r\n", key);
		return FALSE;
	}

	if(m_hold == INVALID_SM_HANDLE)
	{
		QLogSystem::SLOW_LOG(m_LogPath, "Attach ShareMem Error SM_KET = %d", key);
		return FALSE;
	}

	m_pHeader = ArchiveNode::ViewMemKeeper(m_hold);

	if(m_pHeader)
	{
		m_pDataPtr = m_pHeader + sizeof(SMHead);
		KCheck(((SMHead *) m_pHeader)->m_Key == key);
		KCheck(((SMHead *) m_pHeader)->m_Size == Size);
		m_Size = Size;
		QLogSystem::SLOW_LOG(m_LogPath, "Attach ShareMem OK SM_KET = %d", key);
		return TRUE;
	}
	else
	{
		QLogSystem::SLOW_LOG(m_LogPath, "Map ShareMem Error SM_KET = %d", key);
		return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ArchiveNodeWrapper::SetUpdateTime(uint32 uTime)
{
	__GUARD__((SMHead *) m_pHeader)->m_HeadVer = uTime;
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 ArchiveNodeWrapper::GetUpdateTime()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uTime = ((SMHead *) m_pHeader)->m_HeadVer;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return uTime;
	__UNGUARD__
}

////////////////////////////////////////////////////////////////////////////////
// Manager Module
////////////////////////////////////////////////////////////////////////////////

ArchiveNodePool<PlayerMK>	*g_pHumanMKPool = NULL;

/*
=======================================================================================================================
=======================================================================================================================
*/

template<>
BOOL MKManager<PlayerMK>::HeartBeat(uint32 uTime)
{
	return TRUE;
}

