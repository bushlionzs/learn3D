
#ifndef PacketUseCount_h__15_12_2008_15_51
#define PacketUseCount_h__15_12_2008_15_51
#include "TypeDefine.h"
class	PacketUseCount
{
	enum SORT_TYPE { PUC_SORT_SEND_COUNT = 0, PUC_SORT_SIZE_COUNT };
	struct PacketInfomation
	{
		int32_t	 iPacketID;
		uint32_t iPacketSendCount;
		uint32_t iPacketSizeCount;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	Reset();

	void	SetActive(MapID_t iSceneID);

	void	SaveInfoToLogFile(int32 iType);

	void	CacheInfomation(int32 iSize, int32 iPacketID, MapID_t iSceneID);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void		Sort(int32 iType);
	static int32	CompareBySendCount(const void *pArg1, const void *pArg2);
	static int32	CompareBySizeCount(const void *pArg1, const void *pArg2);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	PacketUseCount();
	~PacketUseCount();
private:
	MapID_t			m_iSceneID;
	FastLock		m_Lock;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static PacketUseCount	*GetInstance();

	static void		CreateInstance();

	static void		DeleteInstance();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	static PacketUseCount	*m_pInstance;
};
#endif
