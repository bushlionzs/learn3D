/*$T Common/StructTopList.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_TOPLIST_H__
#define __GAMESTRUCT_TOPLIST_H__

#include "TypeDefine.h"

#pragma pack(push, 1)
#define TOP_LIST_TYPENAME_LEN		32
#define MAX_TOP_LIST_ROWS		1000
#define MAX_TOP_LIST_RECORDS		100
#define MAX_TOP_LIST_PRISE_CONTEX1	50
#define MAX_TOP_LIST_PRISE_CONTEX2	200

enum TOP_LIST_TYPE
{
	LEVEL_TOP_LIST		= 0,            // 等级
	LEVEL_TOP_LIST_BK,
	MONEY_TOP_LIST,                     // 财富
	MONEY_TOP_LIST_BK,
	HONOR_TOP_LIST,                     // 荣誉
	HONOR_TOP_LIST_BK,
	SHENGWANG_TOP_LIST,                 // 声望
	SHENGWANG_TOP_LIST_BK,
	GP_TOP_LIST,                        // 帮贡
	GP_TOP_LIST_BK,
	HOT_VALUE_TOP_LIST,                 // 魅力
	HOT_VALUE_TOP_LIST_BK,
	PK_TOP_LIST,                        // 红名（PK值）
	PK_TOP_LIST_BK,
	KILL_COUNT_TOP_LIST,                // 杀人
	KILL_COUNT_TOP_LIST_BK,
	PVP2V2_TOPLIST,                     // 战场等级
	PVP2V2_TOPLIST_BK,
	PVP2V2_MARK_TOPLIST,                // 战场积分
	PVP2V2_MARK_TOPLIST_BK,
	GUILD_TOP_LIST,                     // 帮会
	GUILD_TOP_LIST_BK,
	GUILD_BATTLE_TOP_LIST,              // 帮战积分
	GUILD_BATTLE_TOP_LIST_BK,
	WORLDCUP_TOPLIST_A,                 // 世界杯A组
	WORLDCUP_TOPLIST_B,
	COUNTRY_TOP_LIST,                   // 国家实力
	COUNTRY_TOP_LIST_BK,

	TOP_LIST_FULLDATA_SEPERATOR = COUNTRY_TOP_LIST_BK,

	MERIT_TOPLIST,				// 帮会功德
	MERIT_TOPLIST_BK,
	AMATIVE_TOPLIST,			// 恋爱
	AMATIVE_TOPLIST_BK,
	SPOUSE_TOPLIST,				// 夫妻
	SPOUSE_TOPLIST_BK,
	MASTER_TOPLIST,				// 师傅
	MASTER_TOPLIST_BK,
	DATI_TOPLIST,				// 答题
	DATI_TOPLIST_BK,
	TIEREN_TOPLIST,				// 铁人三项
	TIEREN_TOPLIST_BK,
	WULONG_TOPLIST,				// 乌龙词典
	WULONG_TOPLIST_BK,
	BAOZANG_TOPLIST,			// 宝藏守卫
	BAOZANG_TOPLIST_BK,
	TULONG_TOPLIST,				// 屠龙排行榜
	TULONG_TOPLIST_BK,
	LABA_TOPLIST,				// 小喇叭
	LABA_TOPLIST_BK,
	YANHUA_TOPLIST,				// 烟花
	YANHUA_TOPLIST_BK,
	QIULONGDAO_TOPLIST,			// 囚龙岛
	QIULONGDAO_TOPLIST_BK,
	HESHIBI_TOPLIST,			// 和氏璧
	HESHIBI_TOPLIST_BK,
	CAISHENDIAN_TOPLIST,		// 财神殿
	CAISHENDIAN_TOPLIST_BK,
	ZHUJIAZHUANG_TOPLIST,		// 祝家庄
	ZHUJIAZHUANG_TOPLIST_BK,
	LUNHUITAI_TOPLIST,			// 轮回台
	LUNHUITAI_TOPLIST_BK,
    JINGJIAOTANG_TOPLIST,       // 景教堂（副本）
    JINGJIAOTANG_TOPLIST_BK,
    ZHANSHENMIAO_TOPLIST,       // 战神墓（副本）
    ZHANSHENMIAO_TOPLIST_BK,
    INDIANTEMPLE_TOPLIST,       // 印度神庙（副本）
    INDIANTEMPLE_TOPLIST_BK,
    LV_LOULAN_TOPLIST,          // 楼兰等级排行榜
    LV_LOULAN_TOPLIST_BK,
    LV_TIANSHAN_TOPLIST,        // 天山等级排行榜
    LV_TIANSHAN_TOPLIST_BK,
    LV_KUNLUN_TOPLIST,          // 昆仑等级排行榜
    LV_KUNLUN_TOPLIST_BK,
    LV_DUNHUANG_TOPLIST,        // 敦煌等级排行榜
    LV_DUNHUANG_TOPLIST_BK,
    INHERENCE_LEVEL_TOPLIST,    // 天赋等级排行榜
    INHERENCE_LEVEL_TOPLIST_BK,
    LAIRD_BATTLE_TOPLIST,       // 领地战排行榜
    LAIRD_BATTLE_TOPLIST_BK,

	COUNTRY_STRONG_WEAK_TOPLIST, 	//国家强弱积分排行榜
	TOP_LIST_NUM
};

#define TOP_LIST_FULLDATA_NUM  (TOP_LIST_NUM-TOP_LIST_FULLDATA_SEPERATOR)

struct TOP_LIST_TYPENAME_TABLE
{
	char	m_szTypeName[TOP_LIST_NUM][TOP_LIST_TYPENAME_LEN];

	TOP_LIST_TYPENAME_TABLE()
	{
		memset(m_szTypeName, 0, sizeof(m_szTypeName));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Register(int32 nIndex, char *szName)
	{
		KCheck(nIndex >= 0 && nIndex < TOP_LIST_NUM);
		strncpy(m_szTypeName[nIndex], szName, TOP_LIST_TYPENAME_LEN - 1);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	char *GetTypeName(int32 nIndex)
	{
		KCheck(nIndex >= 0 && nIndex < TOP_LIST_NUM);
		return m_szTypeName[nIndex];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetIndex(char *szName)
	{
		if(strlen(szName) == 0) return -1;

		for(int32 i = 0; i < TOP_LIST_NUM; ++i)
		{
			if(strcmp(szName, m_szTypeName[i]) == 0) return i;
		}

		return -1;
	}
};

enum TOP_LIST_TYPE2
{
	TOP_TYPE_USER		= 0,
	TOP_TYPE_GUILD,
	TOP_TYPE_COUNTRY,
	TOP_TYPE_USER_BK,
	TOP_TYPE_GUILD_BK,
	TOP_TYPE_COUNTRY_BK,
};


struct _TOP_DATA
{
	GUID_t	m_Guid;
	int32	m_Level;
	int32	m_Country;
	char	m_Name[MAX_CHARACTER_NAME];
	int16	m_Profession;
	char	m_GuildName[MAX_GUILD_NAME_SIZE];
	int32	m_iKeyValue;
	Time_t	m_iANSITime;
	int32	m_nReserved[3];

	_TOP_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Guid = INVALID_GUID;
		m_Level = -1;
		m_Country = -1;
		memset(m_Name, 0, sizeof(m_Name));
		m_Profession = -1;
		memset(m_GuildName, 0, sizeof(m_GuildName));
		m_iKeyValue = -1;
		memset(m_nReserved, 0, sizeof(m_nReserved));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		uint32	uSize = sizeof(GUID_t) + sizeof(int32) + sizeof(int32) + sizeof(m_Name) + sizeof(int16) + sizeof
			(m_GuildName) + sizeof(int32) + sizeof(int32) * 3;

		return uSize;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(_TOP_DATA &rhs)
	{
		if
		(
			m_Guid == rhs.m_Guid
		&&	m_Level == rhs.m_Level
		&&	m_Country == rhs.m_Country
		&&	(strcmp(m_Name, rhs.m_Name) == 0)
		&&	m_Profession == rhs.m_Profession
		&&	(strcmp(m_GuildName, rhs.m_GuildName) == 0)
		&&	m_iKeyValue == rhs.m_iKeyValue
		&&	m_iANSITime == rhs.m_iANSITime
		&&	m_nReserved[0] == rhs.m_nReserved[0]
		&&	m_nReserved[1] == rhs.m_nReserved[1]
		&&	m_nReserved[2] == rhs.m_nReserved[2]
		) return TRUE;

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator!=(_TOP_DATA &rhs)
	{
		return !(*this == rhs);
	}

	
};

#pragma pack(pop)
#endif
