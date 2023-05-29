/*$T Common/StructMap.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "Util.h"
#include "StructCity.h"
#include "Version.h"

#ifndef __GAMESTRUCT_SCENE_H__
#define __GAMESTRUCT_SCENE_H__

struct MAP_LOAD
{
	char	m_szMap[_MAX_PATH];
	char	m_szMonster[_MAX_PATH];
	char	m_szGrowPointData[_MAX_PATH];
	char	m_szGrowPointSetup[_MAX_PATH];
	char	m_szPatrolPointData[_MAX_PATH];
	char	m_szArea[_MAX_PATH];
	char	m_szPet[_MAX_PATH];
	char	m_szStallInfo[_MAX_PATH];
	char	m_szPKArea[_MAX_PATH];
	BOOL	m_IsGrowPointExist;
	BOOL	m_IsStallInfoExist;
	BOOL	m_IsPKAreaExist;

	MAP_LOAD()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(MAP_LOAD));
	}
};

struct MAP_INIT_DATA
{
	int32	m_nDataType;

	MAP_INIT_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nDataType = MAP_TYPE_GAMELOGIC;
	}

	
	uint32 GetMsgSize() const
	{
		return sizeof(int32);
	}
};

#define MAX_COPY_MEMBER		30
#define MAX_FUBEN_DATA_PARAM	256
struct FUBEN_DATA
{
	MapID_t		m_SourSceneID;
	GUID_t		m_TeamLeader;
	TeamID_t	m_TeamID;
	uint32		m_NoUserCloseTime;
	uint32		m_SceneTimer;
	int32		m_Param[MAX_FUBEN_DATA_PARAM];
	GUID_t		m_MemberGUID[MAX_COPY_MEMBER];

	FUBEN_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_SourSceneID = INVALID_ID;
		m_TeamLeader = INVALID_ID;
		m_TeamID = INVALID_ID;
		m_NoUserCloseTime = 10000;
		m_SceneTimer = 0;
		memset(m_Param, 0, sizeof(int32) * MAX_FUBEN_DATA_PARAM);
		for(int32 i = 0; i < MAX_COPY_MEMBER; i++)
		{
			m_MemberGUID[i] = INVALID_ID;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddMemberGUID(GUID_t guid)
	{
		if(IsHaveMember(guid)) return;

		for(int32 i = 0; i < MAX_COPY_MEMBER; i++)
		{
			if(m_MemberGUID[i] == INVALID_ID)
			{
				m_MemberGUID[i] = guid;
				return;
			}
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsHaveMember(GUID_t guid)
	{
		for(int32 i = 0; i < MAX_COPY_MEMBER; i++)
		{
			if(m_MemberGUID[i] == guid) return TRUE;
		}

		return FALSE;
	}
};

struct CITYMAP_DATA
{
	MapID_t		m_ScenePortList[MAX_CITY_PORT];
	GUID_t		m_Creator;
	CTinyTimer	m_DynamicSceneQuitTimer;
	BOOL		m_bClose;

	CITYMAP_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL AddPort(MapID_t ScenePort)
	{
		for(uint32 i = 0; i < MAX_CITY_PORT; i++)
		{
			if(m_ScenePortList[i] == INVALID_ID)
			{
				m_ScenePortList[i] = ScenePort;
				return TRUE;
			}
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL RemovePort(MapID_t ScenePort)
	{
		for(uint32 i = 0; i < MAX_CITY_PORT; i++)
		{
			if(m_ScenePortList[i] == ScenePort)
			{
				m_ScenePortList[i] = INVALID_ID;
				return TRUE;
			}
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetPortNum()
	{
		int32	a = 0;
		for(uint32 i = 0; i < MAX_CITY_PORT; i++)
		{
			if(m_ScenePortList[i] != INVALID_ID)
			{
				a++;
			}
		}

		return a;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		for(uint32 i = 0; i < MAX_CITY_PORT; i++)
		{
			m_ScenePortList[i] = INVALID_ID;
		}

		m_Creator = INVALID_GUID;
		m_DynamicSceneQuitTimer.Clear();
		m_bClose = FALSE;
	}
};

#define MAX_GUILD_BATTLESCENE_DATA_PARAM	(32)
struct GUILDBATTLEMAP_SETTING
{
	uint32		m_SceneTimer;
	BOOL		m_bSetTimer;

	GuildID_t	m_nGuildA;
	GuildID_t	m_nGuildB;

	GUILDBATTLEMAP_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_bSetTimer = FALSE;
		m_SceneTimer = 0;
		m_nGuildA = -1;
		m_nGuildB = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGuildA(GuildID_t nGuildId)
	{
		m_nGuildA = nGuildId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GuildID_t GetGuildA()
	{
		return m_nGuildA;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGuildB(GuildID_t nGuildId)
	{
		m_nGuildB = nGuildId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GuildID_t GetGuildB()
	{
		return m_nGuildB;
	}
};

#define MAX_KINGBATTLE_DATA_PARAM	(16)
struct KINGBATTLEMAP_SETTING
{
	uint32		m_SceneTimer;
	BOOL		m_bSetTimer;

	GuildID_t	m_nGuildA;
	GuildID_t	m_nGuildB;

	KINGBATTLEMAP_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_bSetTimer = FALSE;
		m_SceneTimer = 0;
		m_nGuildA = -1;
		m_nGuildB = -1;
	}
};

#define MAX_WORLDCUP_DATA_PARAM (32)
struct WORLDCUPMAP_SETTING
{
	GuildID_t	m_nGuildA;
	GuildID_t	m_nGuildB;

	WORLDCUPMAP_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nGuildA = -1;
		m_nGuildB = -1;
	}
};

struct SCENECOPY_ANSWER
{

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Encrypt(int32 nValue)
	{
		int32	nVer = CURRENT_VERSION & 0xfffffff0;
		return 0x5f3759df - (nValue >> 1) + nVer;
	}
};
#endif
