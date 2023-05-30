/*$T GLServer/GL/Main/TabDefine_GL.h GC 1.140 10/10/07 10:08:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __TAB_DEFINE_GL_H__
#define __TAB_DEFINE_GL_H__

#include "TabStruct.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "StructWorldShop.h"


/*
===============================================================================================================
===============================================================================================================
*/

class TableInit_GL
{
public:
	TableInit_GL();
	~TableInit_GL();

	BOOL	Init();

protected:
	// 初始化角色模板表
	void	Init_DefaultChar();
	// 初始化战场时间表
	void	Init_BattleTimerTable();
	// 初始化帮派职务权限
	void	Init_GuildAuthRuler();
	// 初始化国家职务权限
	void	Init_CountryAuthRuler();
	// 初始化世界商店
	void	Init_WorldShopInfoTable();
	
	void	ReadWorldShopBuyCallInfo
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			uint32			&Val1,
			uint32			&Val2,
			int32			MaxCnt
		);
	// 初始化字符串过滤
	void	Init_StringFilterTbl();
	// 初始化世界仓库
	void	Init_WorldStockInfoTable();
	void	ReadWorldStockBuyCallInfo
		(
		SplitStringLevelOne	*pSplitL1,
		SplitStringLevelTwo	*pSplitL2,
		const char		*pSplitString,
		uint32			&Val1,
		uint32			&Val2,
		int32			MaxCnt
		);

protected:

	void	ReadBattleTimerDay
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			uchar			*pVal,
			int32			MaxCnt
		);
	void	ReadBattleTimerWeek
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			uchar			*pVal,
			int32			MaxCnt
		);
};
extern TableInit_GL	g_TabInit_GL;


/*
===============================================================================================================
 角色模板表
===============================================================================================================
*/
struct _DEFAULT_CHARDATA_TBL
{
	int32	m_Table[MAX_COUNTRY_NUM][MAX_PROFESSION_NUM][CHAR_ININUM];

	_DEFAULT_CHARDATA_TBL()
	{
		memset(m_Table, 0, sizeof(int32) * MAX_PROFESSION_NUM * CHAR_ININUM * MAX_COUNTRY_NUM);
	};

	int32 Get(uint32 Country, uint32 ProfessionType, uint32 CharParam)
	{
		KCheck(Country < MAX_COUNTRY_NUM && ProfessionType < MAX_PROFESSION_NUM && CharParam < CHAR_ININUM);
		return m_Table[Country][ProfessionType][CharParam];
	};

	void Set(uint32 Country, uint32 Profession, uint32 Attr, int32 iValue)
	{
		KCheck(Country < MAX_COUNTRY_NUM && Profession < PROFESSION_NUMBER && Attr < CHAR_ININUM);
		m_Table[Country][Profession][Attr] = iValue;
	}
};

extern _DEFAULT_CHARDATA_TBL	g_DefaultCharDataTbl;



/*
===============================================================================================================
 战场时间表
===============================================================================================================
*/
#define MAX_BATTLE_DAY					(32)
#define MAX_BATTLE_WEEK					(8)
#define MAX_BATTLE_COUNT				(256)

#define BATTLE_TIMER_DATE				(0)
#define BATTLE_TIMER_WEEK				(1)
#define BATTLE_TIMER_DATE_WEEK			(2)
#define BATTLE_TIMER_NONE				(3)

#define BATTLE_TYPE_GUILDBATTLE			(0)
#define BATTLE_TYPE_KINGBATTLE			(1)
#define BATTLE_TYPE_GUILDCONTEND		(2)
#define BATTLE_TYPE_COUNTRYBATTLELITE	(6)
#define BATTLE_TYPE_2V2BATTLE			(7)
#define BATTLE_TYPE_6V6BATTLE			(8)
#define BATTLE_TYPE_ZHUQUEBATTLE		(9)
#define BATTLE_TYPE_QINGLONGBATTLE		(10)
#define BATTLE_TYPE_LAIRDBATTLE			(11)

struct _TIMER_BATTLE_
{
	uint32		m_ID;

	uint32		m_TimerParam;
	uchar		m_Day[MAX_BATTLE_DAY];
	uchar		m_Week;

	uint32		m_BegSignupTime;
	uint32		m_EndSignupTime;

	uint32		m_BegBattleTime;
	uint32		m_EndBattleTime;

	ScriptID_t	m_ScriptID;

	uint32		m_nType;

	int32		m_nParam0;						//参数0
	int32		m_nParam1;						//参数1
	int32		m_nParam2;						//参数2
	int32		m_nParam3;						//参数3
	int32		m_nParam4;						//参数4
};

typedef TabTemplate<_TIMER_BATTLE_,MAX_BATTLE_COUNT> _TIMER_BATTLE_TAB;
extern _TIMER_BATTLE_TAB g_BattleTimerTbl;


/*
===============================================================================================================
===============================================================================================================
*/
#define BUY_CALL_ENUM_NUM	10

struct WORLD_SHOP_EXT_ATTR
{
	uchar	m_ShopId;
	int32	m_GoldCash;
	int32	m_Charge;
	uchar	m_ConcentNum;
	uint32	m_RemainTime;
	uchar	m_PageNum;
	BOOL	m_IsBuyBack;
	uint32	m_MinBuyBackPrice[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackPrice[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackCount[BUY_CALL_ENUM_NUM];
	uint32	m_MinBuyBackTime[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackTime[BUY_CALL_ENUM_NUM];
};

typedef TabTemplate<WORLD_SHOP_EXT_ATTR,SHOP_LIST_NUM>		WORLD_SHOP_ATTREX_ATTR;
extern WORLD_SHOP_ATTREX_ATTR	g_GLShopAttrExTbl;


/*
===============================================================================================================
===============================================================================================================
*/
struct WORLD_STOCK_EXT_ATTR
{
	uchar	m_Id;
	BOOL	m_IsBuyBack;
	uint32	m_MinBuyBackPrice[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackPrice[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackCount[BUY_CALL_ENUM_NUM];
	uint32	m_MinBuyBackTime[BUY_CALL_ENUM_NUM];
	uint32	m_MaxBuyBackTime[BUY_CALL_ENUM_NUM];
};

typedef TabTemplate<WORLD_STOCK_EXT_ATTR,1>		WORLD_STOCK_ATTREX_ATTR;
extern WORLD_STOCK_ATTREX_ATTR	g_GLStockAttrExTbl;


/*
===============================================================================================================
===============================================================================================================
*/
#define FILTER_KEY_WORD_LEN	32
#define FILTER_KEY_WORD_NUM	10
struct _STRING_FILTER_TABLE
{
	struct _STRING_FILTER_ITEM
	{
		char	m_KeyWord[FILTER_KEY_WORD_LEN];
	};

	_STRING_FILTER_ITEM	m_FilterItem[FILTER_KEY_WORD_NUM];
	uint32			m_Count;
	int32			m_Pos;

	_STRING_FILTER_TABLE()
	{
		Clear();
	}

	void Clear()
	{
		m_Count = 0;
		m_Pos = 0;
		memset(&m_FilterItem, 0, sizeof(m_FilterItem));
	}

	BOOL AddFilterItem(const char *filter)
	{
		__GUARD__ for(int32 i = 0; i < m_Count; ++i)
		{
			if(strstr(filter, m_FilterItem[i].m_KeyWord)) return FALSE;
		}

		if(FILTER_KEY_WORD_NUM == m_Count)
		{
			if(FILTER_KEY_WORD_NUM == m_Pos) m_Pos = 0;
			if(strlen(filter) >= FILTER_KEY_WORD_LEN) return TRUE;

			memset(m_FilterItem[m_Pos].m_KeyWord, 0, FILTER_KEY_WORD_LEN);
			strncpy(m_FilterItem[m_Pos].m_KeyWord, filter, FILTER_KEY_WORD_LEN - 1);
			++m_Pos;
			return TRUE;
		}

		if(strlen(filter) >= FILTER_KEY_WORD_LEN) return TRUE;

		strncpy(m_FilterItem[m_Count].m_KeyWord, filter, FILTER_KEY_WORD_LEN - 1);
		++m_Count;

		__UNGUARD__ return TRUE;
	}
};

extern _STRING_FILTER_TABLE	g_StringFilterTbl;


#endif
