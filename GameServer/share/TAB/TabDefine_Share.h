#ifndef __TAB_DEFINE_SHARE_H__
#define __TAB_DEFINE_SHARE_H__


#include "TabStruct.h"

/*
===============================================================================================================
TableShare表初始化类
===============================================================================================================
*/

class SplitStringLevelOne;
class SplitStringLevelTwo;

class TableInit_Share
{
public:
	TableInit_Share();
	~TableInit_Share();

	BOOL	Init();

private:
	// 加载排行榜属性表
	void	Init_TopListTable();
	// 加载帮会等级表
	void	Init_GuildLevelInfoTable();
	// 加载帮会功德表
	void	Init_GuildMeritInfoTable();
	// 加载定时器表
	void	Init_TimerDoingTable();
	// 加载师徒表
	void	Init_MasterPrenticeTable();
	// 加载帮会技能表
	void	Init_GuildSkillInfoTable();
	// 动态价格商店
	void	Init_DynamicShopInfoTable();
	// 加载帮会BUS技能消耗
	void	Init_GuildBusSkillInfoTable();

private:
	void	ReadTiemrDoingData
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			int32			*pVal,
			int32			MaxCnt
		);
	void	ReadTiemrDoingData_MapList
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			MapID_t			*pVal,
			int32			MaxCnt
		);
	void	ReadTiemrDoingReserveEX
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			int32			*pVal,
			int32			MaxCnt
		);
	void	ReadTiemrDoingMapInfo
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			int32			*pVal1,
			int32			*pVal2,
			int32			MaxCnt
		);

	void	ReadSplitStringToTable
		(
			SplitStringLevelOne *pSplitL1,
			const char *pSplitString,
			int32 *pArry
		);

};

extern TableInit_Share								g_TabInit_Share;


/*
===============================================================================================================
 排行榜属性表
===============================================================================================================
*/
struct TOP_LIST_ATTR
{
	int32	m_iTopListID;
	int32	m_Type;
	int32	m_iTopListID_BK;
	int32	m_iMaxMemberCount;
	int32	m_iEnterMinLevel;
	int32	m_iPriseType;
	int32	m_iPrise;
	int32	m_iPriseCount;
	BOOL	m_bSaveDB;
	char	m_Name[MAX_TOP_LIST_NAME];
	char	m_Contex1[MAX_TOP_LIST_PRISE_CONTEX1];
	char	m_Contex2[MAX_TOP_LIST_PRISE_CONTEX2];
	int32	m_nResetRule;

	TOP_LIST_ATTR()
	{
		m_iTopListID = -1;
		m_Type = -1;
		m_iTopListID_BK = -1;
		m_iMaxMemberCount = 0;
		m_iEnterMinLevel = 0;
		m_iPriseType = 0;
		m_iPrise = 0;
		m_iPriseCount = 0;
		m_bSaveDB = FALSE;
		memset(m_Name, 0, sizeof(m_Name));
		memset(m_Contex1, 0, sizeof(m_Contex1));
		memset(m_Contex2, 0, sizeof(m_Contex2));
		m_nResetRule = 0;
	}

	TOP_LIST_ATTR &operator=(const TOP_LIST_ATTR &rhs)
	{
		m_iTopListID = rhs.m_iTopListID;
		m_Type = rhs.m_Type;
		m_iTopListID_BK = rhs.m_iTopListID_BK;
		m_iMaxMemberCount = rhs.m_iMaxMemberCount;
		m_iEnterMinLevel = rhs.m_iEnterMinLevel;
		m_iPriseType = rhs.m_iPriseType;
		m_iPrise = rhs.m_iPrise;
		m_iPriseCount = rhs.m_iPriseCount;
		m_bSaveDB = rhs.m_bSaveDB;
		strncpy(m_Name, rhs.m_Name, sizeof(m_Name) - 1);
		strncpy(m_Contex1, rhs.m_Contex1, sizeof(m_Contex1) - 1);
		strncpy(m_Contex2, rhs.m_Contex2, sizeof(m_Contex2) - 1);
		m_nResetRule = rhs.m_nResetRule;
		return *this;
	}
};

#define MAX_TOP_LIST	256
typedef TabTemplate<TOP_LIST_ATTR,MAX_TOP_LIST>		_TOP_LIST_ATTR_TBL;
extern _TOP_LIST_ATTR_TBL							g_TopListAttrTbl;

/*
===============================================================================================================
 帮会等级表
===============================================================================================================
*/
struct _GUILD_LEVEL_INFO
{
	char	m_Level;
	char	m_nMaxFamilyCount;
	int32	m_Gold;
	int32	m_Contribute;
	int32	m_nMaxGuildUserCount;
	int32	m_nMaxFamilyUserCount;
	int32	m_nMaxGoldFamilyUserCount;
	int32	m_GuildItemCount;
	int32	m_GuildMaxExp;
	int32	m_nMaxMemberGP;
	int32	m_nShiMing;
	int32	m_nPriseShiMing;	// 奖励使命点基数
	int32	m_nShiMingPriseExp;
	int32	m_nMoneyLimit;

	_GUILD_LEVEL_INFO()
	{
		m_Level = 0;
		m_nMaxFamilyCount = 0;
		m_Gold = 0;
		m_Contribute = 0;
		m_nMaxGuildUserCount = 0;
		m_nMaxFamilyUserCount = 0;
		m_nMaxGoldFamilyUserCount = 0;
		m_GuildItemCount = 0;
		m_GuildMaxExp = 0;
		m_nMaxMemberGP = 0;
		m_nShiMing = 0;
		m_nPriseShiMing = 0;
		m_nShiMingPriseExp = 0;
		m_nMoneyLimit = 0;
	}
};

typedef TabTemplate<_GUILD_LEVEL_INFO,MAX_GUILD_LEVEL>		_GUILD_LEVEL_INFO_TBL;
extern _GUILD_LEVEL_INFO_TBL	g_GuildLevelInfoTbl;


/*
===============================================================================================================
 帮会功德表
===============================================================================================================
*/
#define GUILD_MERIT_MAX_LEVEL	10
#define GUILD_MERIT_TITLE_SIZE	16
struct GUILD_MERIT_INFO
{
	int32	m_nLevel;
	int32	m_nMerit;
	char	m_szTitle[GUILD_MERIT_TITLE_SIZE];
	float	m_fMultiple;

	GUILD_MERIT_INFO()
	{
		m_nLevel = 0;
		m_nMerit = 0;
		memset( m_szTitle, 0, GUILD_MERIT_TITLE_SIZE );
		m_fMultiple = 1.0;
	}
};

typedef TabTemplate<GUILD_MERIT_INFO,MAX_GUILD_LEVEL>		_GUILD_MERIT_INFO_TBL;

struct GUILD_MERIT_INFO_TBL : public _GUILD_MERIT_INFO_TBL
{
	GUILD_MERIT_INFO* GetMeritInfo(int32 nMerit)
	{
		for( int32 i=GUILD_MERIT_MAX_LEVEL-1; i>=0; i-- )
		{
			if( nMerit >= m_TableExt[i].m_nMerit )
			{
				return &(m_TableExt[i]);
			}
		}
		return &(m_TableExt[0]);
	}	
};

extern GUILD_MERIT_INFO_TBL	g_GuildMeritInfoTbl;


/*
===============================================================================================================
 定时器表
===============================================================================================================
*/
#define TIMER_DOING_NAME_LEN	32

#define REPORT_TEXT_LEN		256

enum REPORT_TYPE
{
	REPORT_TYPE_INVALID	= 0,
	REPORT_TYPE_SLOW,
	REPORT_TYPE_QUICK,
	REPORT_TYPE_EARLIER,
	REPORT_TYPE_MID,
	REPORT_TYPE_LAST,
	REPORT_TYPE_NUM,
};

struct _TIMER_DOING_ATTR
{
	int32	m_Index;

	char	m_szName[TIMER_DOING_NAME_LEN];

	int32	m_ScriptId;

	int32	m_OperateType;

	int32	m_TimeType;

	int32	m_ReportStartTime;
	int32	m_ReportEndTime;

	int32	m_StartTime;
	int32	m_EndTime;

	BOOL	m_bParameterRand;

	int32	m_Parameter[TIMER_PARAMETER_NUM];

	int32	m_BroadcastType[CHAR_SHOW_POS_NUM];

	int32	m_SlowReportInterval;
	char	m_SlowReportText[REPORT_TEXT_LEN];
	int32	m_SlowReportEndTime;

	int32	m_QuickReportInterval;
	char	m_QuickReportText[REPORT_TEXT_LEN];
	int32	m_QuickReportEndTime;

	int32	m_EarlierReportInterval;
	char	m_EarlierReportText[REPORT_TEXT_LEN];
	int32	m_EarlierReportEndTime;

	int32	m_MidReportInterval;
	char	m_MidReportText[REPORT_TEXT_LEN];
	int32	m_MidReportEndTime;

	int32	m_LastReportInterval;
	char	m_LastReportText[REPORT_TEXT_LEN];
	int32	m_LastReportEndTime;

	int32	m_Ruler;

	MapID_t m_TempMapId;

	int32	m_MapId[TIMER_DOING_MAP_NUM];
	int32	m_MapRatio[TIMER_DOING_MAP_NUM];

	int32	m_RatioTotal;

	BOOL	m_ModuleToggle;
	int32	m_BroadMapType; /* 广播场景类型 0表示只通知普通场景 1表示只通知战场 2表示同时通知普通场景和战场 */
	MapID_t m_MapList[TIMER_DOING_MAP_LIST];	/* 需要广播到的场景列表 */
};

typedef TabTemplate<_TIMER_DOING_ATTR,MAX_TIMER_DOING_NUM>		_TIMER_DOING_ATTR_TAB;
extern _TIMER_DOING_ATTR_TAB	g_TiemrDoingAttrTbl;


/*
===============================================================================================================
师徒表
===============================================================================================================
*/
struct MASTER_PRENTICE_ATTR
{
	MASTER_PRENTICE_ATTR()
	{
		memset(this, 0, sizeof(MASTER_PRENTICE_ATTR));
	}
	int32	m_nFinishPrenticeshipNum;
	int32	m_nMaxPrenticeCount;
	int32	m_nMasterTitleId;
};

#define MAX_MASTER_PRENTICE_INFO_NUM	5
typedef TabTemplate<MASTER_PRENTICE_ATTR,MAX_MASTER_PRENTICE_INFO_NUM>		MASTER_PRENTICE_TABLE;
extern MASTER_PRENTICE_TABLE	g_MasterPrenticeAttrTbl;

/*
===============================================================================================================
帮会技能表
===============================================================================================================
*/
struct GUILD_SKILL_INFO
{
	int32 m_nSkillID;
	int32 m_aGuildLevel[MAX_GUILDSKILL_LEVEL];
	int32 m_aGuildMoney[MAX_GUILDSKILL_LEVEL];
	int32 m_aGuildExp[MAX_GUILDSKILL_LEVEL];
	int32 m_aGuildItemID[MAX_GUILDSKILL_LEVEL];
	int32 m_aGuildItemCount[MAX_GUILDSKILL_LEVEL];
	int32 m_nGuildDefaultLevel;
	int32 m_aCharInherenceLevel[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharInherenceAllLevel[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharMoney[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharBangGong[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharShengWang[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharWeiWang[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharItemID[MAX_GUILDSKILL_LEVEL];
	int32 m_aCharItemCount[MAX_GUILDSKILL_LEVEL];

	GUILD_SKILL_INFO()
	{
		m_nSkillID = INVALID_ID;
		memset(m_aGuildLevel, 0 ,sizeof(m_aGuildLevel));
		memset(m_aGuildMoney, 0 ,sizeof(m_aGuildMoney));
		memset(m_aGuildExp, 0 ,sizeof(m_aGuildExp));
		memset(m_aGuildItemID, 0 ,sizeof(m_aGuildItemID));
		memset(m_aGuildItemCount, 0 ,sizeof(m_aGuildItemCount));

		m_nGuildDefaultLevel = 0;
		memset(m_aCharInherenceLevel, 0 ,sizeof(m_aCharInherenceLevel));
		memset(m_aCharInherenceAllLevel, 0 ,sizeof(m_aCharInherenceAllLevel));
		memset(m_aCharMoney, 0 ,sizeof(m_aCharMoney));
		memset(m_aCharBangGong, 0 ,sizeof(m_aCharBangGong));
		memset(m_aCharShengWang, 0 ,sizeof(m_aCharShengWang));
		memset(m_aCharWeiWang, 0 ,sizeof(m_aCharWeiWang));
		memset(m_aCharItemID, 0 ,sizeof(m_aCharItemID));
		memset(m_aCharItemCount, 0 ,sizeof(m_aCharItemCount));
	}
};

typedef TabTemplate<GUILD_SKILL_INFO,MAX_GUILDSKILL_COUNT>		_GUILD_SKILL_INFO_TBL;
extern _GUILD_SKILL_INFO_TBL	g_GuildSkillInfoTbl;


// 动态价格商店
struct DYNAMIC_SHOP_INFO
{
	int32		m_nIndex;							//Index
	char		m_szShopName[MAX_SHOP_NAME];		// name 
	int32		m_nShopID;							//商店索引	
	int32 		m_nItemID;							//商品id	
	int32 		m_nMoneyType;						//货币类型
	int32 		m_nPrice;							//价格	
	int32 		m_nCount;							//数量	
	int32 		m_nUpdateIntervalTime;				//更新间隔时间	
	int32 		m_nUpdateMinCount;					//更新最小个数	
	int32 		m_nUpdateMaxCount;					//更新最大个数	
	int32 		m_nPriceIncrease;					//每次价格增加	
	int32 		m_nPriceDecrease;					//每次价格减少
	int32 		m_nPriceDecreaseTime;				//每次价格减少的间隔时间
	int32		m_nWeight;							//权重

	DYNAMIC_SHOP_INFO()
	{
		m_nIndex = INVALID_INDEX;				
		m_nShopID = 0;							
		m_nItemID = INVALID_ID;					
		m_nMoneyType = 0;						
		m_nPrice = 0;							
		m_nCount = 0;							
		m_nUpdateIntervalTime = 0;				
		m_nUpdateMinCount = 0;					
		m_nUpdateMaxCount = 0;					
		m_nPriceIncrease = 0;					
		m_nPriceDecrease = 0;	
		m_nPriceDecreaseTime = 0;
		m_nWeight = 0;
	}
};

enum { MAX_DYNAMIC_SHOP_COUNT = 2048};

typedef TabTemplate<DYNAMIC_SHOP_INFO, MAX_DYNAMIC_SHOP_COUNT>		_DYNAMIC_SHOP_INFO_TBL;
extern _DYNAMIC_SHOP_INFO_TBL	g_DynamicShopInfoTbl;

/*
=======================================================================================================================
=======================================================================================================================
*/

struct GUILD_BUSSKILL_CONSUME
{
	int32 m_nSkillID;						// 技能ID
	int32 m_nNextLevelSkillID;				// 下一级技能ID
	int32 m_nSkillLevel;					// 技能等级
	int32 m_nNeedGuildLevel;				// 需求帮会等级
	int32 m_nConsumeMoney;					// 消耗金钱
	int32 m_nConsumeGuildExp;				// 消耗经验

	GUILD_BUSSKILL_CONSUME()
	{
		m_nSkillID = INVALID_ID;
		m_nNextLevelSkillID = INVALID_ID;
		m_nSkillLevel = 0;
		m_nNeedGuildLevel = 0;
		m_nConsumeMoney = 0;
		m_nConsumeGuildExp = 0;
	}
};

typedef TabTemplate<GUILD_BUSSKILL_CONSUME, MAX_GUILD_BUSSKILL_COUNT>		_GUILD_BUSSKILL_CONSUME_TBL;
extern _GUILD_BUSSKILL_CONSUME_TBL g_BusSkillStudyConsumTbl;

#endif

