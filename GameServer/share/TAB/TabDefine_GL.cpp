/*$T GLServer/GL/Main/WorldTable.cpp GC 1.140 10/10/07 10:08:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TabDefine_GL.h"
#include "BaseTool.h"
#include "FileDef.h"
#include "TAB.h"
#include "AuthRuler.h"

using namespace		TAB;

_DEFAULT_CHARDATA_TBL	g_DefaultCharDataTbl;
_TIMER_BATTLE_TAB		g_BattleTimerTbl;
WORLD_SHOP_ATTREX_ATTR	g_GLShopAttrExTbl;
_STRING_FILTER_TABLE	g_StringFilterTbl;
WORLD_STOCK_ATTREX_ATTR g_GLStockAttrExTbl;
TableInit_GL				g_TabInit_GL;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

TableInit_GL::TableInit_GL()
{
}

TableInit_GL::~TableInit_GL()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_GL::Init()
{
	__GUARD__

	Init_DefaultChar();
	Init_BattleTimerTable();
	Init_GuildAuthRuler();
	Init_CountryAuthRuler();
	Init_WorldShopInfoTable();
	Init_StringFilterTbl();
	Init_WorldStockInfoTable();

	return TRUE;
	__UNGUARD__ 
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_BattleTimerTable()
{
	__GUARD__;
	
	enum TimerGuildBattle
	{
		eIndex			= 0,
		eParam,
		eDay,
		eWeek,
		eBegSignupTime,
		eEndSignupTime,
		eBegBattleTime,
		eEndBattleTime,
		eScriptID,
		eType,
		eParam0,
		eParam1,
		eParam2,
		eParam3,
		eParam4,
	};

	TABFile DBFile(0);
	BOOL ret = DBFile.OpenFromTXT(FILE_TIMER_BATTLE_LIST);

	KCheckEx(ret, FILE_TIMER_BATTLE_LIST);

	int32 iTableCount = DBFile.GetRecordsNum();
	int32 iColumnCount = DBFile.GetFieldsNum();

	KCheck(iTableCount >= 0 && iTableCount < MAX_BATTLE_COUNT);

	memset((void *) &g_BattleTimerTbl, 0, sizeof(g_BattleTimerTbl));
	g_BattleTimerTbl.SetSize( iTableCount );

	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_BattleTimerTbl.GetData(i)->m_ID				= DBFile.Search_Posistion(i, eIndex)->iValue;
		g_BattleTimerTbl.GetData(i)->m_TimerParam		= DBFile.Search_Posistion(i, eParam)->iValue;

		const char *pSplitString						= DBFile.Search_Posistion(i,eDay)->pString;
		ReadBattleTimerDay( &oSplitL1,&oSplitL2, pSplitString, &g_BattleTimerTbl.GetData(i)->m_Day[0],MAX_BATTLE_DAY);

		g_BattleTimerTbl.GetData(i)->m_Week				= DBFile.Search_Posistion(i, eWeek)->iValue;

		g_BattleTimerTbl.GetData(i)->m_BegSignupTime	= DBFile.Search_Posistion(i, eBegSignupTime)->iValue;
		g_BattleTimerTbl.GetData(i)->m_EndSignupTime	= DBFile.Search_Posistion(i, eEndSignupTime)->iValue;

		g_BattleTimerTbl.GetData(i)->m_BegBattleTime	= DBFile.Search_Posistion(i, eBegBattleTime)->iValue;
		g_BattleTimerTbl.GetData(i)->m_EndBattleTime	= DBFile.Search_Posistion(i, eEndBattleTime)->iValue;

		g_BattleTimerTbl.GetData(i)->m_ScriptID			= DBFile.Search_Posistion(i, eScriptID)->iValue;
		g_BattleTimerTbl.GetData(i)->m_nType			= DBFile.Search_Posistion(i, eType)->iValue;

		g_BattleTimerTbl.GetData(i)->m_nParam0			= DBFile.Search_Posistion(i, eParam0)->iValue;
		g_BattleTimerTbl.GetData(i)->m_nParam1			= DBFile.Search_Posistion(i, eParam1)->iValue;
		g_BattleTimerTbl.GetData(i)->m_nParam2			= DBFile.Search_Posistion(i, eParam2)->iValue;
		g_BattleTimerTbl.GetData(i)->m_nParam3			= DBFile.Search_Posistion(i, eParam3)->iValue;
		g_BattleTimerTbl.GetData(i)->m_nParam4			= DBFile.Search_Posistion(i, eParam4)->iValue;
	}

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_WorldShopInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum WorldShopAttrData
	{
		ShopId			= 0,
		GoldCash,
		Charge,
		ConcentNum,
		RemainTime,
		PageNum,
		IsBuyBack		= PageNum + 2,
		BuyCallEnum,
		WorldShopEnd		= BuyCallEnum + 3 * BUY_CALL_ENUM_NUM
	};

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_WORLD_SHOP_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_WORLD_SHOP_INFO);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount >= 0 && iTableCount < SHOP_LIST_NUM);

	memset((void *) &g_GLShopAttrExTbl, 0, sizeof(g_GLShopAttrExTbl));

	g_GLShopAttrExTbl.m_Count = iTableCount;

	KCheck(WorldShopEnd - 1 < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GLShopAttrExTbl.m_TableExt[i].m_ShopId = DBFile.Search_Posistion(i, ShopId)->iValue;
		g_GLShopAttrExTbl.m_TableExt[i].m_GoldCash = DBFile.Search_Posistion(i, GoldCash)->iValue;
		g_GLShopAttrExTbl.m_TableExt[i].m_Charge = DBFile.Search_Posistion(i, Charge)->iValue;
		g_GLShopAttrExTbl.m_TableExt[i].m_ConcentNum = DBFile.Search_Posistion(i, ConcentNum)->iValue;
		g_GLShopAttrExTbl.m_TableExt[i].m_RemainTime = DBFile.Search_Posistion(i, RemainTime)->iValue;
		g_GLShopAttrExTbl.m_TableExt[i].m_PageNum = DBFile.Search_Posistion(i, PageNum)->iValue;
		KCheck(g_GLShopAttrExTbl.m_TableExt[i].m_ConcentNum <= USER_MAX_SELL_NUM);
		KCheck(g_GLShopAttrExTbl.m_TableExt[i].m_PageNum <= MAX_SHOP_PAGE_NUM);

		g_GLShopAttrExTbl.m_TableExt[i].m_IsBuyBack = DBFile.Search_Posistion(i, IsBuyBack)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char		*pSplitString = NULL;
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 BuyCallIndex = 0; BuyCallIndex < BUY_CALL_ENUM_NUM; BuyCallIndex++)
		{
			pSplitString = DBFile.Search_Posistion(i, BuyCallEnum + BuyCallIndex * 3)->pString;
			ReadWorldShopBuyCallInfo
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_GLShopAttrExTbl.m_TableExt[i].m_MinBuyBackPrice[BuyCallIndex],
				g_GLShopAttrExTbl.m_TableExt[i].m_MaxBuyBackPrice[BuyCallIndex],
				2
			);

			g_GLShopAttrExTbl.m_TableExt[i].m_MaxBuyBackCount[BuyCallIndex] = DBFile.Search_Posistion
				(
					i,
					BuyCallEnum + BuyCallIndex * 3 + 1
				)->iValue;

			pSplitString = DBFile.Search_Posistion(i, BuyCallEnum + BuyCallIndex * 3 + 2)->pString;
			ReadWorldShopBuyCallInfo
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_GLShopAttrExTbl.m_TableExt[i].m_MinBuyBackTime[BuyCallIndex],
				g_GLShopAttrExTbl.m_TableExt[i].m_MaxBuyBackTime[BuyCallIndex],
				2
			);
		}
	}

	__UNGUARD__
}


/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_GL::Init_WorldStockInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum WorldStockAttrData
	{
		Id				= 0,
		IsBuyBack,	
		BuyCallEnum,
		WorldStockEnd	= BuyCallEnum + 3 * BUY_CALL_ENUM_NUM
	};

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_WORLD_STOCK_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_WORLD_STOCK_INFO);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == 1);

	memset((void *) &g_GLStockAttrExTbl, 0, sizeof(g_GLStockAttrExTbl));

	KCheck(WorldStockEnd - 1 < iColumnCount);

	for ( int32 i = 0; i < iTableCount; ++i )
	{
		g_GLStockAttrExTbl.m_TableExt[0].m_Id = DBFile.Search_Posistion(i, Id)->iValue;
		g_GLStockAttrExTbl.m_TableExt[0].m_IsBuyBack = DBFile.Search_Posistion(i, IsBuyBack)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char		*pSplitString = NULL;
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 BuyCallIndex = 0; BuyCallIndex < BUY_CALL_ENUM_NUM; BuyCallIndex++)
		{
			pSplitString = DBFile.Search_Posistion(i, BuyCallEnum + BuyCallIndex * 3)->pString;
			ReadWorldStockBuyCallInfo
				(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_GLStockAttrExTbl.m_TableExt[0].m_MinBuyBackPrice[BuyCallIndex],
				g_GLStockAttrExTbl.m_TableExt[0].m_MaxBuyBackPrice[BuyCallIndex],
				2
				);

			g_GLStockAttrExTbl.m_TableExt[0].m_MaxBuyBackCount[BuyCallIndex] = DBFile.Search_Posistion
				(
				i,
				BuyCallEnum + BuyCallIndex * 3 + 1
				)->iValue;

			pSplitString = DBFile.Search_Posistion(i, BuyCallEnum + BuyCallIndex * 3 + 2)->pString;
			ReadWorldStockBuyCallInfo
				(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_GLStockAttrExTbl.m_TableExt[0].m_MinBuyBackTime[BuyCallIndex],
				g_GLStockAttrExTbl.m_TableExt[0].m_MaxBuyBackTime[BuyCallIndex],
				2
				);
			}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::ReadWorldShopBuyCallInfo
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	uint32			&Val1,
	uint32			&Val2,
	int32			MaxCnt
)
{
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MaxCnt == iLineCount);
	Val1 = atoi(pSplitL2->GetResultLine(0));
	Val2 = atoi(pSplitL2->GetResultLine(1));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::ReadWorldStockBuyCallInfo
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	uint32			&Val1,
	uint32			&Val2,
	int32			MaxCnt
)
{
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MaxCnt == iLineCount);
	Val1 = atoi(pSplitL2->GetResultLine(0));
	Val2 = atoi(pSplitL2->GetResultLine(1));
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_DefaultChar()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum DefaultRoleTBData
	{
		TBEnterScence		= 0,
		TBBornX,
		TBBornY,
		TBCamp,
		TBIniLevel,
		TBIniExp,
		TBIniHP,
		TBIniRage,
		TBIniStr,
		TBIniCon,
		TBIniInt,
		TBIniDex,
		TBIniSkill1,
		TBIniSkill2,
		TBIniSkill3,
		TBIniSkill4,
		TBIniSkill5,
		TBIniAbility1,
		TBIniAbility2,
		TBIniAbility3,
		TBIniAbility4,
		TBIniAbility5,
		TBMoney,
		TBIniNum,
	};

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_CHAR_DEFAULT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_CHAR_DEFAULT);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 n = 0; n < MAX_COUNTRY_NUM; ++n)
	{
		for(int32 i = 0; i < MAX_PREFESSION_NUM; i++)
		{
			for(int32 j = 0; j < TBIniNum; j++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	iValue = DBFile.Search_Posistion(i + n * MAX_PREFESSION_NUM, j + 3)->iValue;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				g_DefaultCharDataTbl.Set(n, i, j, iValue);
			}
		}
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_GuildAuthRuler()
{
	AuthRuler_Guild::GetInstance().LoadAuthTable();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_CountryAuthRuler()
{
	AuthRuler_Country::GetInstance().LoadAuthTable();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::Init_StringFilterTbl()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum FILTER_KEY_WORD { KEY_WORD = 1, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_STRING_FILTER_TABLE_NAME);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_STRING_FILTER_TABLE_NAME);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= FILTER_KEY_WORD_NUM);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_StringFilterTbl.AddFilterItem(ThirdFile.Search_Posistion(i, KEY_WORD)->pString);
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::ReadBattleTimerDay
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	uchar			*pVal,
	int32			MaxCnt
)
{
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MaxCnt >= iLineCount);
	if(MaxCnt < iLineCount)
	{
		return;
	}

	if(atoi(pSplitL2->GetResultLine(0)) == 0)
	{
		for(int32 i = 0; i < MaxCnt; ++i)
		{
			pVal[i] = 1;
		}

		return;
	}
	else
	{
		/*~~~~~~~~~~*/
		int32	i = 0;
		/*~~~~~~~~~~*/

		for(i = 0; i < MaxCnt; ++i)
		{
			pVal[i] = 0;
		}

		for(i = 0; i < iLineCount; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nIdx = atoi(pSplitL2->GetResultLine(i));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nIdx >= 0 && nIdx < MAX_BATTLE_DAY)
			{
				pVal[nIdx] = 1;
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_GL::ReadBattleTimerWeek
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	uchar			*pVal,
	int32			MaxCnt
)
{
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MaxCnt >= iLineCount);
	if(MaxCnt < iLineCount)
	{
		return;
	}

	if(atoi(pSplitL2->GetResultLine(0)) == 0)
	{
		for(int32 i = 0; i < MaxCnt; ++i)
		{
			pVal[i] = 1;
		}

		return;
	}
	else
	{
		/*~~~~~~~~~~*/
		int32	i = 0;
		/*~~~~~~~~~~*/

		for(i = 0; i < MaxCnt; ++i)
		{
			pVal[i] = 0;
		}

		for(i = 0; i < iLineCount; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nIdx = atoi(pSplitL2->GetResultLine(i));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nIdx >= 0 && nIdx < MAX_BATTLE_WEEK)
			{
				pVal[nIdx] = 1;
			}
		}
	}
}
