#include "stdafx.h"
#include "TabDefine_Share.h"
#include "BaseTool.h"
#include "FileDef.h"
#include "TAB.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"

using namespace		TAB;

TableInit_Share				g_TabInit_Share;
_TOP_LIST_ATTR_TBL			g_TopListAttrTbl;
_GUILD_LEVEL_INFO_TBL		g_GuildLevelInfoTbl;
GUILD_MERIT_INFO_TBL		g_GuildMeritInfoTbl;
_TIMER_DOING_ATTR_TAB		g_TiemrDoingAttrTbl;
MASTER_PRENTICE_TABLE		g_MasterPrenticeAttrTbl;
_GUILD_SKILL_INFO_TBL		g_GuildSkillInfoTbl;
_DYNAMIC_SHOP_INFO_TBL		g_DynamicShopInfoTbl;
_GUILD_BUSSKILL_CONSUME_TBL g_BusSkillStudyConsumTbl;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Share::TableInit_Share()
{}

TableInit_Share::~TableInit_Share()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Share::Init()
{
	__GUARD__

	Init_TopListTable();
	Init_GuildLevelInfoTable();
	Init_GuildMeritInfoTable();
	Init_TimerDoingTable();
	Init_MasterPrenticeTable();
	Init_GuildSkillInfoTable();
	Init_DynamicShopInfoTable();
	Init_GuildBusSkillInfoTable();

	return TRUE;
	__UNGUARD__
	return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::Init_TopListTable()
{
	__GUARD__ 
	
	enum TopListAttrData
	{
		TL_TopListID	= 0,
		TL_Name,
		TL_MemberCount,
		TL_EnterMinLevel,
		TL_SAVEDB,
		TL_TYPE,
		TL_BKID,
		TL_PriseType	= 8,
		TL_Prise,
		TL_PriseCount,
		TL_PriseContex1,
		TL_PriseContex2,
		TL_ResetRule,
	};

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_TOP_LIST);
	KCheckEx(ret, FILE_TOP_LIST);

	int32	iTableCount = DBFile.GetRecordsNum();
	KCheck(iTableCount <= MAX_TOP_LIST);
	g_TopListAttrTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_TopListAttrTbl.GetData(i)->m_iTopListID = DBFile.Search_Posistion(i, TL_TopListID)->iValue;
		KCheck( g_TopListAttrTbl.GetData(i)->m_iTopListID == i && "Public/Config/TopList.tab 的第一列应从0开始并保持连续");
		
		strncpy( g_TopListAttrTbl.GetData(i)->m_Name,DBFile.Search_Posistion(i, TL_Name)->pString,MAX_TOP_LIST_NAME - 1);

		int32	iMemberCount = DBFile.Search_Posistion(i, TL_MemberCount)->iValue;
		KCheck(iMemberCount <= MAX_TOP_LIST_ROWS);
		g_TopListAttrTbl.GetData(i)->m_iMaxMemberCount = iMemberCount;
		g_TopListAttrTbl.GetData(i)->m_iEnterMinLevel = DBFile.Search_Posistion(i, TL_EnterMinLevel)->iValue;
		g_TopListAttrTbl.GetData(i)->m_bSaveDB = DBFile.Search_Posistion(i, TL_SAVEDB)->iValue;
		g_TopListAttrTbl.GetData(i)->m_Type = DBFile.Search_Posistion(i, TL_TYPE)->iValue;

		int32	bkid = DBFile.Search_Posistion(i, TL_BKID)->iValue;
		KCheck(bkid >= -2 && bkid < TOP_LIST_NUM);
		g_TopListAttrTbl.GetData(i)->m_iTopListID_BK = bkid;
		g_TopListAttrTbl.GetData(i)->m_iPriseType = DBFile.Search_Posistion(i, TL_PriseType)->iValue;
		g_TopListAttrTbl.GetData(i)->m_iPrise = DBFile.Search_Posistion(i, TL_Prise)->iValue;
		g_TopListAttrTbl.GetData(i)->m_iPriseCount = DBFile.Search_Posistion(i, TL_PriseCount)->iValue;

		KCheck
		(
			MAIL_GIVE_MONEY == g_TopListAttrTbl.GetData(i)->m_iPriseType
			||	MAIL_GIVE_ITEM == g_TopListAttrTbl.GetData(i)->m_iPriseType
			||	INVALID_ID == g_TopListAttrTbl.GetData(i)->m_iPriseType
		);

		int32	iSize = (int32) strlen(DBFile.Search_Posistion(i, TL_PriseContex1)->pString);
		KCheck(MAX_TOP_LIST_PRISE_CONTEX1 > iSize);
		strncpy( g_TopListAttrTbl.GetData(i)->m_Contex1, DBFile.Search_Posistion(i, TL_PriseContex1)->pString, iSize );

		iSize = (int32) strlen(DBFile.Search_Posistion(i, TL_PriseContex2)->pString);
		KCheck(MAX_TOP_LIST_PRISE_CONTEX2 > iSize);
		strncpy( g_TopListAttrTbl.GetData(i)->m_Contex2, DBFile.Search_Posistion(i, TL_PriseContex2)->pString, iSize );

		g_TopListAttrTbl.GetData(i)->m_nResetRule = DBFile.Search_Posistion(i, TL_ResetRule)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::Init_GuildLevelInfoTable()
{
	__GUARD__
	
	enum GuildLevelData
	{
		LEVELID			= 0,
		MAXFAMILY,
		GOLD,
		CONTRIBUTE,
		MAXGUILDUSER,
		MAXGOLDFAMILYUSER,
		MAXFAMILYUSER,
		GUILDITEMCOUNT,
		GUILDEXP,
		MEMBERGP,
		SHIMING,
		PRISESHIMING,
		SHIMINGPRISEEXP,
		MONEY,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GUILD_LEVEL);
	KCheckEx(ret, FILE_GUILD_LEVEL);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount <= MAX_GUILD_LEVEL);
	g_GuildLevelInfoTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GuildLevelInfoTbl.GetData(i)->m_Level = ThirdFile.Search_Posistion(i, LEVELID)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMaxFamilyCount = ThirdFile.Search_Posistion(i, MAXFAMILY)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_Gold = ThirdFile.Search_Posistion(i, GOLD)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_Contribute = ThirdFile.Search_Posistion(i, CONTRIBUTE)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMaxGuildUserCount = ThirdFile.Search_Posistion(i,MAXGUILDUSER)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMaxGoldFamilyUserCount = ThirdFile.Search_Posistion(i,MAXGOLDFAMILYUSER)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMaxFamilyUserCount = ThirdFile.Search_Posistion(i,MAXFAMILYUSER)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_GuildItemCount = ThirdFile.Search_Posistion(i,GUILDITEMCOUNT)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_GuildMaxExp = ThirdFile.Search_Posistion(i, GUILDEXP)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMaxMemberGP = ThirdFile.Search_Posistion(i, MEMBERGP)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nShiMing = ThirdFile.Search_Posistion(i, SHIMING)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nPriseShiMing = ThirdFile.Search_Posistion(i, PRISESHIMING)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nShiMingPriseExp = ThirdFile.Search_Posistion(i, SHIMINGPRISEEXP)->iValue;
		g_GuildLevelInfoTbl.GetData(i)->m_nMoneyLimit = ThirdFile.Search_Posistion(i, MONEY)->iValue;
	}
	
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::Init_GuildMeritInfoTable()
{
	__GUARD__ 
	
	enum GuildMeritData
	{
		LEVELID = 0,
		MERIT,
		TITLE,
		MULTIPLE,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GUILD_MERIT);
	KCheckEx(ret, FILE_GUILD_MERIT);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount <= GUILD_MERIT_MAX_LEVEL);
	g_GuildMeritInfoTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GuildMeritInfoTbl.GetData(i)->m_nLevel = ThirdFile.Search_Posistion(i, LEVELID)->iValue;
		g_GuildMeritInfoTbl.GetData(i)->m_nMerit = ThirdFile.Search_Posistion(i, MERIT)->iValue;
		strncpy( g_GuildMeritInfoTbl.GetData(i)->m_szTitle, ThirdFile.Search_Posistion(i, TITLE)->pString, GUILD_MERIT_TITLE_SIZE-1 );
		g_GuildMeritInfoTbl.GetData(i)->m_fMultiple = ThirdFile.Search_Posistion(i, MULTIPLE)->fValue;
	}
	
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::Init_MasterPrenticeTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { FinishPrenticeshipCount = 0, MaxPrenticeCount, MasterTitle, };

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_MASTER_PRENTICE_TABLE_NAME);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_MASTER_PRENTICE_TABLE_NAME);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount <= MAX_MASTER_PRENTICE_INFO_NUM);
	g_MasterPrenticeAttrTbl.m_Count = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_MasterPrenticeAttrTbl.m_TableExt[i].m_nFinishPrenticeshipNum = DBFile.Search_Posistion
			(
				i,
				FinishPrenticeshipCount
			)->iValue;
		g_MasterPrenticeAttrTbl.m_TableExt[i].m_nMaxPrenticeCount = DBFile.Search_Posistion
			(
				i,
				MaxPrenticeCount
			)->iValue;
		g_MasterPrenticeAttrTbl.m_TableExt[i].m_nMasterTitleId = DBFile.Search_Posistion
			(
				i,
				MasterTitle
			)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::Init_TimerDoingTable()
{
	__GUARD__ 
	
	enum TimerDoingAttrData
	{
		Index			= 0,
		szName,
		ScriptId,
		OperateType,
		TimeType,
		ReportStartTime,
		ReportEndTime,
		StartTime,
		EndTime,
		ParameterRand,
		Parameter0,
		Parameter1,
		Parameter2,
		Parameter3,
		Parameter4,
		BroadcastType,
		SlowReportInterval,
		SlowReportText,
		SlowReportEndTime,
		QuickReportInterval,
		QuickReportText,
		QuickReportEndTime,
		EarlierReportInterval,
		EarlierReportText,
		EarlierReportEndTime,
		MidReportInterval,
		MidReportText,
		MidReportEndTime,
		LastReportInterval,
		LastReportText,
		LastReportEndTime,
		Ruler,
		TempMapId,
		Map0,
		Map1,
		Map2,
		Map3,
		Map4,
		Map5,
		Map6,
		Map7,
		Map8,
		Map9,
		ModuleToggle,
		BroadMapType,
		BroadMapList,
	};

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_TIMER_DOING_LIST);
	KCheckEx(ret, FILE_TIMER_DOING_LIST);

	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	KCheck(iTableCount >= 0 && iTableCount < MAX_TIMER_DOING_NUM);
	memset((void *) &g_TiemrDoingAttrTbl, 0, sizeof(g_TiemrDoingAttrTbl));
	KCheck(BroadMapList < iColumnCount);

	const char		*pSplitString = NULL;
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;

	g_TiemrDoingAttrTbl.SetSize( iTableCount );
	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_TiemrDoingAttrTbl.GetData(i)->m_Index = DBFile.Search_Posistion(i, Index)->iValue;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_szName,
			DBFile.Search_Posistion(i, szName)->pString,
			TIMER_DOING_NAME_LEN - 1
		);

		g_TiemrDoingAttrTbl.GetData(i)->m_ScriptId = DBFile.Search_Posistion(i, ScriptId)->iValue;
		KCheck(g_TiemrDoingAttrTbl.GetData(i)->m_ScriptId <= 0 || g_TiemrDoingAttrTbl.GetData(i)->m_ScriptId >= 100000);
		g_TiemrDoingAttrTbl.GetData(i)->m_OperateType = DBFile.Search_Posistion(i, OperateType)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_TimeType = DBFile.Search_Posistion(i, TimeType)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_ReportStartTime = DBFile.Search_Posistion
			(
				i,
				ReportStartTime
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_ReportEndTime = DBFile.Search_Posistion(i, ReportEndTime)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_StartTime = DBFile.Search_Posistion(i, StartTime)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_EndTime = DBFile.Search_Posistion(i, EndTime)->iValue;

		/*~~~~~~~~~~*/
		int32	j = 0;
		/*~~~~~~~~~~*/

		for(j = 0; j < TIMER_PARAMETER_NUM; j++)
		{
			if(j == 0 && DBFile.Search_Posistion(i, ParameterRand)->iValue > 0)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				const int32	ParaNum = 20;
				int32		TempPara[ParaNum];
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				memset(TempPara, -1, sizeof(int32) * ParaNum);
				pSplitString = DBFile.Search_Posistion(i, Parameter0)->pString;
				ReadTiemrDoingReserveEX(&oSplitL1, &oSplitL2, pSplitString, TempPara, ParaNum);

				/*~~~~~~~~~~~~*/
				int32	cnt = 0;
				/*~~~~~~~~~~~~*/

				for(int32 index = 0; index < ParaNum; index++)
				{
					if(TempPara[index] >= 0)
						cnt++;
					else
						break;
				}

				/*~~~~~~~~~~~~~~~~~~~*/
				int32	nReserveEX = 0;
				/*~~~~~~~~~~~~~~~~~~~*/

				if(cnt > 0) nReserveEX = rand() % cnt;

				g_TiemrDoingAttrTbl.GetData(i)->m_Parameter[0] = TempPara[nReserveEX];
			}
			else
			{
				g_TiemrDoingAttrTbl.GetData(i)->m_Parameter[j] = atoi(DBFile.Search_Posistion(i, Parameter0 + j)->pString);
			}
		}

		pSplitString = DBFile.Search_Posistion(i, BroadcastType)->pString;

		for(j = 0; j < CHAR_SHOW_POS_NUM; j++) g_TiemrDoingAttrTbl.GetData(i)->m_BroadcastType[j] = -1;

		ReadTiemrDoingData
		(
			&oSplitL1,
			&oSplitL2,
			pSplitString,
			g_TiemrDoingAttrTbl.GetData(i)->m_BroadcastType,
			CHAR_SHOW_POS_NUM
		);

		g_TiemrDoingAttrTbl.GetData(i)->m_SlowReportInterval = DBFile.Search_Posistion
			(
				i,
				SlowReportInterval
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_SlowReportInterval *= 1000;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_SlowReportText,
			DBFile.Search_Posistion(i, SlowReportText)->pString,
			REPORT_TEXT_LEN - 1
		);
		g_TiemrDoingAttrTbl.GetData(i)->m_SlowReportEndTime = DBFile.Search_Posistion
			(
				i,
				SlowReportEndTime
			)->iValue;

		g_TiemrDoingAttrTbl.GetData(i)->m_QuickReportInterval = DBFile.Search_Posistion
			(
				i,
				QuickReportInterval
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_QuickReportInterval *= 1000;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_QuickReportText,
			DBFile.Search_Posistion(i, QuickReportText)->pString,
			REPORT_TEXT_LEN - 1
		);
		g_TiemrDoingAttrTbl.GetData(i)->m_QuickReportEndTime = DBFile.Search_Posistion
			(
				i,
				QuickReportEndTime
			)->iValue;

		g_TiemrDoingAttrTbl.GetData(i)->m_EarlierReportInterval = DBFile.Search_Posistion
			(
				i,
				EarlierReportInterval
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_EarlierReportInterval *= 1000;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_EarlierReportText,
			DBFile.Search_Posistion(i, EarlierReportText)->pString,
			REPORT_TEXT_LEN - 1
		);
		g_TiemrDoingAttrTbl.GetData(i)->m_EarlierReportEndTime = DBFile.Search_Posistion
			(
				i,
				EarlierReportEndTime
			)->iValue;

		g_TiemrDoingAttrTbl.GetData(i)->m_MidReportInterval = DBFile.Search_Posistion
			(
				i,
				MidReportInterval
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_MidReportInterval *= 1000;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_MidReportText,
			DBFile.Search_Posistion(i, MidReportText)->pString,
			REPORT_TEXT_LEN - 1
		);
		g_TiemrDoingAttrTbl.GetData(i)->m_MidReportEndTime = DBFile.Search_Posistion
			(
				i,
				MidReportEndTime
			)->iValue;

		g_TiemrDoingAttrTbl.GetData(i)->m_LastReportInterval = DBFile.Search_Posistion
			(
				i,
				LastReportInterval
			)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_LastReportInterval *= 1000;
		strncpy
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_LastReportText,
			DBFile.Search_Posistion(i, LastReportText)->pString,
			REPORT_TEXT_LEN - 1
		);
		g_TiemrDoingAttrTbl.GetData(i)->m_LastReportEndTime = DBFile.Search_Posistion
			(
				i,
				LastReportEndTime
			)->iValue;

		g_TiemrDoingAttrTbl.GetData(i)->m_Ruler = DBFile.Search_Posistion(i, Ruler)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_TempMapId = (MapID_t) DBFile.Search_Posistion(i, TempMapId)->iValue;
		g_TiemrDoingAttrTbl.GetData(i)->m_RatioTotal = 0;

		for(j = 0; j < TIMER_DOING_MAP_NUM; j++)
		{
			pSplitString = DBFile.Search_Posistion(i, Map0 + j)->pString;
			ReadTiemrDoingMapInfo
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				&g_TiemrDoingAttrTbl.GetData(i)->m_MapId[j],
				&g_TiemrDoingAttrTbl.GetData(i)->m_MapRatio[j],
				2
			);

			g_TiemrDoingAttrTbl.GetData(i)->m_RatioTotal += g_TiemrDoingAttrTbl.GetData(i)->m_MapRatio[j];
		}

		if(g_TiemrDoingAttrTbl.GetData(i)->m_Ruler > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	MapId[TIMER_DOING_MAP_NUM] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			memcpy(MapId, g_TiemrDoingAttrTbl.GetData(i)->m_MapId, sizeof(int32) * TIMER_DOING_MAP_NUM);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	MapRatio[TIMER_DOING_MAP_NUM] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			memcpy
			(
				MapRatio,
				g_TiemrDoingAttrTbl.GetData(i)->m_MapRatio,
				sizeof(int32) * TIMER_DOING_MAP_NUM
			);

			for(j = 0; j < TIMER_DOING_MAP_NUM; j++)
			{
				g_TiemrDoingAttrTbl.GetData(i)->m_MapId[j] = INVALID_ID;
			}

			for(int32 cnt = 0; cnt < g_TiemrDoingAttrTbl.GetData(i)->m_Ruler; cnt++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~*/
				int32	Max = MapRatio[0];
				/*~~~~~~~~~~~~~~~~~~~~~~*/

				for(j = 1; j < TIMER_DOING_MAP_NUM; j++)
				{
					if(MapRatio[j] > Max)
					{
						Max = MapRatio[j];
					}
				}

				/*~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	nRet = rand() % Max;
				/*~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(j = TIMER_DOING_MAP_NUM - 1; j >= 0; j--)
				{
					if(nRet <= MapRatio[j])
					{
						g_TiemrDoingAttrTbl.GetData(i)->m_MapId[cnt] = MapId[j];

						if(j < TIMER_DOING_MAP_NUM - 1)
						{
							memcpy
							(
								&MapId[j],
								&MapId[j + 1],
								(TIMER_DOING_MAP_NUM - 1 - j) * sizeof(int32)
							);
							memcpy
							(
								&MapRatio[j],
								&MapRatio[j + 1],
								(TIMER_DOING_MAP_NUM - 1 - j) * sizeof(int32)
							);
						}
						else
						{
							MapId[j] = INVALID_ID;
							MapRatio[j] = INVALID_ID;
						}
						break;
					}
				}
			}
		}

		g_TiemrDoingAttrTbl.GetData(i)->m_ModuleToggle = DBFile.Search_Posistion(i, ModuleToggle)->iValue > 0;

		/* 读取需要通知的场景类型 */
		g_TiemrDoingAttrTbl.GetData(i)->m_BroadMapType = DBFile.Search_Posistion(i, BroadMapType)->iValue;
		KCheck
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_BroadMapType >= 0
			&&	g_TiemrDoingAttrTbl.GetData(i)->m_BroadMapType <= 3
		);

		/* 读取需要广播的场景列表 */
		pSplitString = DBFile.Search_Posistion(i, BroadMapList)->pString;
		memset
		(
			g_TiemrDoingAttrTbl.GetData(i)->m_MapList,
			-1,
			sizeof(g_TiemrDoingAttrTbl.GetData(i)->m_MapList)
		);
		ReadTiemrDoingData_MapList
		(
			&oSplitL1,
			&oSplitL2,
			pSplitString,
			g_TiemrDoingAttrTbl.GetData(i)->m_MapList,
			TIMER_DOING_MAP_LIST
		);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::ReadTiemrDoingData
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			*pVal,
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

	for(int32 id = 0; id < iLineCount; ++id)
	{
		if(atoi(pSplitL2->GetResultLine(0)) == 0)
		{
			for(int32 i = 0; i < MaxCnt; i++)
			{
				pVal[id] = 1;
				return;
			}
		}
		else
			pVal[atoi(pSplitL2->GetResultLine(id))] = atoi(pSplitL2->GetResultLine(id));
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::ReadTiemrDoingData_MapList
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	MapID_t			*pVal,
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

	/*~~~~~~~~~~~~~~~~~~*/
	int32	nCurCount = 0;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int32 id = 0; id < iLineCount; ++id)
	{
		if(atoi(pSplitL2->GetResultLine(id)) != -1)
		{
			if(nCurCount < TIMER_DOING_MAP_LIST) pVal[nCurCount++] = atoi(pSplitL2->GetResultLine(id));
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::ReadTiemrDoingReserveEX
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			*pVal,
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

	for(int32 id = 0; id < iLineCount; ++id)
	{
		pVal[id] = atoi(pSplitL2->GetResultLine(id));
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Share::ReadTiemrDoingMapInfo
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			*pVal1,
	int32			*pVal2,
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
	{
		*pVal1 = atoi(pSplitL2->GetResultLine(0));
		*pVal2 = atoi(pSplitL2->GetResultLine(1));
	}
}

void TableInit_Share::ReadSplitStringToTable(SplitStringLevelOne *pSplitL1, const char *pSplitString, int32 *pArry)
{
	pSplitL1->Reset();
	pSplitL1->Init('|', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL1->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MAX_GUILDSKILL_LEVEL >= iLineCount && "天赋修行级别超过最大限度");
	if(MAX_GUILDSKILL_LEVEL < iLineCount)
	{
		iLineCount = MAX_GUILDSKILL_LEVEL;
	}

	for(int32 i = 0; i < iLineCount; ++i)
	{
		pArry[i] = atof(pSplitL1->GetResultLine(i));
	}
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Share::Init_GuildSkillInfoTable()
{
	__GUARD__

	enum GuildLevelData
	{
		SKILLID			= 0,
		GUILD_LEVEL,
		GUILD_MONEY,
		GUILD_EXP,
		GUILD_ITEMID,
		GUILD_ITEMCOUNT,
		GUILD_DEFAULT_LEVEL,
		CHAR_INHERENCE_LEVEL,
		CHAR_IHERENCE_ALL_LEVEL,
		CHAR_MONEY,
		CHAR_BANGGONG,
		CHAR_SHENGWANG,
		CHAR_WEIWANG,
		CHAR_ITEMID,
		CHAR_ITEMCOUNT,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GUILD_SKILL_INFO);
	KCheckEx(ret, FILE_GUILD_SKILL_INFO);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GUILDSKILL_COUNT);
	g_GuildSkillInfoTbl.SetSize( iTableCount );

	SplitStringLevelOne	oSplitL1;
	const char		*pSplitString = NULL;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GuildSkillInfoTbl.GetData(i)->m_nSkillID = ThirdFile.Search_Posistion(i, SKILLID)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, GUILD_LEVEL)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aGuildLevel);

		pSplitString = ThirdFile.Search_Posistion(i, GUILD_MONEY)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aGuildMoney);

		pSplitString = ThirdFile.Search_Posistion(i, GUILD_EXP)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aGuildExp);

		pSplitString = ThirdFile.Search_Posistion(i, GUILD_ITEMID)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aGuildItemID);

		pSplitString = ThirdFile.Search_Posistion(i, GUILD_ITEMCOUNT)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aGuildItemCount);

		g_GuildSkillInfoTbl.GetData(i)->m_nGuildDefaultLevel = ThirdFile.Search_Posistion(i, GUILD_DEFAULT_LEVEL)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_INHERENCE_LEVEL)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharInherenceLevel);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_IHERENCE_ALL_LEVEL)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharInherenceAllLevel);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_MONEY)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharMoney);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_BANGGONG)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharBangGong);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_SHENGWANG)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharShengWang);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_WEIWANG)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharWeiWang);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_ITEMID)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharItemID);

		pSplitString = ThirdFile.Search_Posistion(i, CHAR_ITEMCOUNT)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GuildSkillInfoTbl.GetData(i)->m_aCharItemCount);

	}

	__UNGUARD__
}

// 动态价格商店
void TableInit_Share::Init_DynamicShopInfoTable()
{
	__GUARD__

 	enum DynamicShopData
 	{
		INDEX,							//Index
		DYNAMIC_SHOP_NAME,				//商店name	
		DYNAMIC_SHOP_ID,				//商店索引		
		ITEM_ID,						//商品id	
		MONEY_TYPE,						//货币类型
		PRICE,							//价格	
		COUNT,							//数量	
		UPDATE_INTERVAL_TIME,			//更新间隔时间	
		UPDATE_MIN_COUNT,				//更新最小个数	
		UPDATE_MAX_COUNT,				//更新最大个数	
		PRICE_INCREASE,					//每次价格增加	
		PRICE_DECREASE,					//每次价格减少
		PRICE_DECREASE_TIME,			//每次价格减少的间隔时间
		WEIGHT,							//权重

 	};
 	TABFile ThirdFile(0);
 	BOOL	ret = ThirdFile.OpenFromTXT(FILE_DYNAMIC_SHOP);
 	KCheckEx(ret, FILE_DYNAMIC_SHOP);
 
 	int32	iTableCount = ThirdFile.GetRecordsNum();
 	KCheck(iTableCount < MAX_DYNAMIC_SHOP_COUNT);
 	g_DynamicShopInfoTbl.SetSize( iTableCount );
 
 	for(int32 i = 0; i < iTableCount; ++i)
 	{
 		g_DynamicShopInfoTbl.GetData(i)->m_nIndex			= ThirdFile.Search_Posistion(i, INDEX)->iValue;
		strncpy( g_DynamicShopInfoTbl.GetData(i)->m_szShopName, 
			ThirdFile.Search_Posistion(i, DYNAMIC_SHOP_NAME)->pString, MAX_SHOP_NAME - 1);
		g_DynamicShopInfoTbl.GetData(i)->m_nShopID			= ThirdFile.Search_Posistion(i, DYNAMIC_SHOP_ID)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nItemID			= ThirdFile.Search_Posistion(i, ITEM_ID)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nMoneyType		= ThirdFile.Search_Posistion(i, MONEY_TYPE)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nPrice			= ThirdFile.Search_Posistion(i, PRICE)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nCount			= ThirdFile.Search_Posistion(i, COUNT)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nUpdateIntervalTime= ThirdFile.Search_Posistion(i, UPDATE_INTERVAL_TIME)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nUpdateMinCount	= ThirdFile.Search_Posistion(i, UPDATE_MIN_COUNT)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nUpdateMaxCount	= ThirdFile.Search_Posistion(i, UPDATE_MAX_COUNT)->iValue;
 		g_DynamicShopInfoTbl.GetData(i)->m_nPriceIncrease	= ThirdFile.Search_Posistion(i, PRICE_INCREASE)->iValue;
		g_DynamicShopInfoTbl.GetData(i)->m_nPriceDecrease	= ThirdFile.Search_Posistion(i, PRICE_DECREASE)->iValue;
		g_DynamicShopInfoTbl.GetData(i)->m_nPriceDecreaseTime= ThirdFile.Search_Posistion(i, PRICE_DECREASE_TIME)->iValue;
		g_DynamicShopInfoTbl.GetData(i)->m_nWeight			= ThirdFile.Search_Posistion(i, WEIGHT)->iValue;
 	}

	__UNGUARD__
}

void TableInit_Share::Init_GuildBusSkillInfoTable()
{
	__GUARD__

	enum BUS_SKILL_CONSUME
	{
		SKILL_ID				= 0,		// 技能ID
		SKILL_NEXTLEVELID		= 1,		// 下一级技能ID
		SKILL_LEVEL				= 2,		// 等级
		SKILL_NEEDGUILDLEVEL	= 3,
		SKILL_CONSUME_MONEY		= 4,		// 消耗帮会金钱
		SKILL_CONSUME_GUILDEXP	= 5,		// 消耗帮会经验
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GUILD_BUS_SKILL_STUDY_CONSUME);
	KCheckEx(ret, FILE_GUILD_BUS_SKILL_STUDY_CONSUME);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GUILD_BUSSKILL_COUNT);

	g_BusSkillStudyConsumTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++ i)
	{
		g_BusSkillStudyConsumTbl.GetData(i)->m_nSkillID = ThirdFile.Search_Posistion(i, SKILL_ID)->iValue;

		g_BusSkillStudyConsumTbl.GetData(i)->m_nNextLevelSkillID = ThirdFile.Search_Posistion(i, SKILL_NEXTLEVELID)->iValue;

		g_BusSkillStudyConsumTbl.GetData(i)->m_nSkillLevel = ThirdFile.Search_Posistion(i, SKILL_LEVEL)->iValue;

		g_BusSkillStudyConsumTbl.GetData(i)->m_nNeedGuildLevel = ThirdFile.Search_Posistion(i, SKILL_NEEDGUILDLEVEL)->iValue;

		g_BusSkillStudyConsumTbl.GetData(i)->m_nConsumeMoney = ThirdFile.Search_Posistion(i, SKILL_CONSUME_MONEY)->iValue;

		g_BusSkillStudyConsumTbl.GetData(i)->m_nConsumeGuildExp = ThirdFile.Search_Posistion(i, SKILL_CONSUME_GUILDEXP)->iValue;
	}

	__UNGUARD__
}
