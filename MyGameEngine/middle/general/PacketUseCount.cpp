#include "OgreHeader.h"
#include "PacketUseCount.h"

PacketUseCount *PacketUseCount::	m_pInstance = NULL;
const int32_t PACKET_COUNT_MARK = 100000;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void PacketUseCount::Reset()
{
	memset(m_aPacketInfo, 0, sizeof(m_aPacketInfo));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iSceneID = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PacketUseCount::PacketUseCount()
{
	Reset();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PacketUseCount::~PacketUseCount()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::SetActive(MapID_t iSceneID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ lock_guard<FastLock>	autolock(m_Lock);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Reset();
	m_iSceneID = iSceneID;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::SaveInfoToLogFile(int32 iType)
{
	__GUARD__ if(INVALID_ID == m_iSceneID)
	{
		return;
	}

	lock_guard<FastLock> autolock(m_Lock);

	Sort(iType);
	for(int32 i = 0; i < PACKET_MAX; ++i)
	{
		if(0 >= m_aPacketInfoSort[i].iPacketSendCount)
		{
			continue;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::CacheInfomation(int32 iSize, int32 iPacketID, MapID_t iSceneID)
{
	__GUARD__ if(INVALID_ID == m_iSceneID)
	{
		return;
	}

	if(iSceneID != m_iSceneID)
	{
		return;
	}

	if(PACKET_NONE >= iPacketID || PACKET_MAX <= iPacketID)
	{
		return;
	}

	m_aPacketInfo[iPacketID].iPacketSendCount++;
	m_aPacketInfo[iPacketID].iPacketSizeCount += iSize;
	m_aPacketInfo[iPacketID].iPacketID = iPacketID;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PacketUseCount *PacketUseCount::GetInstance()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(NULL != m_pInstance);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pInstance;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::CreateInstance()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(NULL == m_pInstance);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pInstance = new PacketUseCount;
	KCheck(NULL != m_pInstance);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::DeleteInstance()
{
	__GUARD__ if(NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PacketUseCount::Sort(int32 iType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memcpy(m_aPacketInfoSort, m_aPacketInfo, sizeof(m_aPacketInfoSort));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(PUC_SORT_SEND_COUNT == iType)
	{
		qsort
		(
			m_aPacketInfoSort,
			PACKET_MAX,
			sizeof(PacketInfomation),
			(int32(*) (const void *, const void *)) CompareBySendCount
		);
		return;
	}
	else if(PUC_SORT_SIZE_COUNT == iType)
	{
		qsort
		(
			m_aPacketInfoSort,
			PACKET_MAX,
			sizeof(PacketInfomation),
			(int32(*) (const void *, const void *)) CompareBySizeCount
		);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PacketUseCount::CompareBySendCount(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		Serial1, Serial2;
	PacketInfomation	*pCount1 = (PacketInfomation *) pArg1;
	PacketInfomation	*pCount2 = (PacketInfomation *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Serial1 = pCount1->iPacketSendCount;
	Serial2 = pCount2->iPacketSendCount;

	if(Serial1 > Serial2)
	{
		return -1;
	}
	else if(Serial1 < Serial2)
	{
		return 1;
	}
	else
	{
		return 1;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PacketUseCount::CompareBySizeCount(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		Serial1, Serial2;
	PacketInfomation	*pCount1 = (PacketInfomation *) pArg1;
	PacketInfomation	*pCount2 = (PacketInfomation *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Serial1 = pCount1->iPacketSizeCount;
	Serial2 = pCount2->iPacketSizeCount;

	if(Serial1 > Serial2)
	{
		return -1;
	}
	else if(Serial1 < Serial2)
	{
		return 1;
	}
	else
	{
		return 1;
	}

	__UNGUARD__ return 0;
}
