#include "stdafx.h"
#include "TabDefine_Map.h"
#include "BaseTool.h"
#include "ScriptCacheMgr.h"
#include "server_settting.h"
#include "TAB.h"
#include "FileDef.h"
#include "gameobject/Behavior_State.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "shop/ShopManager.h"
#include "item/Item_Helper.h"
#include "gameobject/Behavior_Template.h"
#include "TabDefine_Map_Misc.h"

using namespace			TAB;

SBaseValueTab			g_BaseProfessionValueTbl;
_MAP_INFO_ATTR_TAB		g_MapInfoAttrTbl;
_TITLE_INFO_TBL			g_TitleInfoTbl;
_TITLE_COMBINATION_TBL	g_TitleComTbl;
_PROPERTY_LEVELUP_TAB		g_PropertyLevelupTab;
SLevelupExpTab			g_LevelupExpTab;
_INHERENCE_EXP_TBL		g_InherenceExpTbl;
_INHERENCE_LEVEL_AVERAGE_TBL	g_InherenceLevelTab;
_GATHER_POINT_INFO_TAB	g_GatherPointInfoTab;
_GAME_OPEN_INFO_TBL		g_GameOpenInfoTbl;
GameOpenManager         g_GameOpenManager;
IDCollectionMgr_T		g_CollectionIDMgr;
CampAndStandDataMgr	g_CampDataMgr;
SpecialObjDataMgr		g_SpecialObjDataTemplate;
ScriptCacheMgr			g_BehaviorFileDataMgr;		// ??未使用
ScriptCacheMgr			g_ScriptFileMgr;
SIPFilter				g_IPFilter;
SChatConsume			g_ChatConsumeTab;
SHairStyle				g_Hair_Style_Tab;
SGMTab				g_GMTab;
_DYSHOP_INFO_TBL		g_DyShopInfoTbl;
_SHOP_INFO_TBL			g_ShopInfoTbl;
_PKPOINT_INFO_TBL		g_PKPointTbl;
_PKLEVEL_INFO_TBL		g_PKLevelTbl;
_PKPUNISH_INFO_TBL		g_PKPunishTbl;
OpenBox_ItemInfo_Table	g_OpenBox_ItemInfo_Table;
_DURSPOIL_VALUE_TBL		g_DurSpoilValueTbl;

_ONDIE_MONSTER_TBL		g_OndieMonsterTbl;
_ONDIE_NOPUNISH_TBL		g_OndieNopunishTbl;
_ONDIE_DIFFCOUNTRY_TBL		g_OndieDiffCountryTbl;
_ONDIE_SAMECOUNTRY_TBL		g_OndieSameCountryTbl;
_ONDIE_SAMECOUNTRY_KILLER_TBL	g_OndieSameCountryKillerTbl;
_ONRELIVE_COST_TBL		g_ReliveCostTbl;
_ONDEATH_DEAL_TBL		g_DeathDealTbl;

_BEASTIE_DATA_TABLE		g_BeastieDataTable;
_VIGOR_DATA_TABLE		g_VigorDataTable;
_GUILD_MERCH_TBL		g_GuildMerchTbl;
AWARD_ATTREX_ATTR		g_AwardAttrExTbl;
SENE_COMMON_TABLE		g_SceneCommonTbl;
WORLD_SHOP_ATTREX_ATTR		g_GLShopAttrExTbl;
_ENCRYPT_INFO_ATTR_TAB		g_EncryptInfoAttrTbl;
ANSWERP_ATTREX_ATTR		g_AnawerAttrExTbl;
FUBEN_DATA_TABLE		g_FubenDataAttrTbl;
CHEAT_ACT_TABLE			g_CheatActAttrTbl;
CHANGE_PROFESSION_TABLE g_ChangeProfessionTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Map_Misc::TableInit_Map_Misc()
{}

TableInit_Map_Misc::~TableInit_Map_Misc()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Misc::Init()
{
	__GUARD__

	BOOL bRet;

	Init_BaseValueTable();
	Init_MapInfoTable();
	Init_TitleInfoTable();
	Init_TitleCombinationTable();
	LoadAttrLevelupTable();
	LoadLevelExpTable();
	LoadInherenceExpTable();
	LoadInherenceLevelAverageTable();
	LoadGrowPointTable();
	LoadGameOpenTable();
	
	bRet = LoadIdCollectionMgr();
	KCheck(bRet);
	bRet = LoadSpecialObjDataMgr();
	KCheck(bRet);

	LoadScriptListFile();
	LoadIPRange();
	LoadChatConsume();
	LoadHairStyleTable();
	LoadGMTable();
	LoadDyShopInfoTable();
	g_StrLoadShopInfoTable();
	LoadPKPointInfoTable();
	LoadPKLevelInfoTable();
	LoadPKPunishInfoTable();
	LoadOpenBoxInfoTable();
	LoadDurSpoilInfoTable();

	LoadOndieMonsterTable();
	LoadOndieNopunishTable();
	LoadOndieDiffCountryTable();
	LoadOndieSameCountryTable();
	LoadOndieSameCountryKillerTable();
	LoadReliveCostTable();
	LoadDeathDealTable();

	LoadBeastieDataTable();
	LoadVigorDataTable();
	LoadAwardInfoTable();
	LoadSceneCommonTable();
	LoadWorldShopInfoTable();
	LoadEncryptInfoTable();
	LoadAnswerInfoTable();
	LoadFubenDataTable();
	LoadCheatActDataTable();
    LoadChangeProfession();

	return TRUE;
	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::Init_BaseValueTable()
{
	__GUARD__ 
		
	Configer	ini(FILE_BASE_VALUE);

	for(int32 i = 0; i < PROFESSION_NUMBER; i++)
	{
		for(int32 j = 0; j < AINFOTYPE_NUMBER; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szSection[256], szName[256];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			sprintf(szSection, "PROFESSION%d", i);
			sprintf(szName, "AINFOTYPE%d", j);
			g_BaseProfessionValueTbl.m_Table[j][i] = ini.Get_Property_Int(szSection, szName);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::Init_MapInfoTable()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum MapInfoAttrData
	{
		Index,
		PartIndex,
		SceneId,
		SceneName,
		DestPosX,
		DestPosZ,
		SceneType,
		MinMapLevel,
		MinUserLevel,
		NEEDMONEY	= MinUserLevel + 2,
		NEEDITEM,
		SourceSceneId	= NEEDITEM + 3,
		SourcePosX,
		SourcePosZ,
	};
	/*~~~~~~~~~~~~*/

	TABFile DBFile(0);
	BOOL ret = DBFile.OpenFromTXT(FILE_MAP_INFO_LIST);
	KCheckEx(ret, FILE_MAP_INFO_LIST);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_MAP_INFO_NUM);
	g_MapInfoAttrTbl.m_Count = iTableCount;

	KCheck(SourcePosZ < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_MapInfoAttrTbl.m_TableExt[i].m_Index = DBFile.Search_Posistion(i, Index)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_PartIndex = DBFile.Search_Posistion(i, PartIndex)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_SceneId = DBFile.Search_Posistion(i, SceneId)->iValue;
		strncpy
		(
			g_MapInfoAttrTbl.m_TableExt[i].m_SceneName,
			DBFile.Search_Posistion(i, SceneName)->pString,
			SCENE_NAME_LEN
		);

		g_MapInfoAttrTbl.m_TableExt[i].m_DestPosX = DBFile.Search_Posistion(i, DestPosX)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_DestPosZ = DBFile.Search_Posistion(i, DestPosZ)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_SceneType = DBFile.Search_Posistion(i, SceneType)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_MinMapLevel = DBFile.Search_Posistion(i, MinMapLevel)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_MinUserLevel = DBFile.Search_Posistion(i, MinUserLevel)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_NeedMoney = DBFile.Search_Posistion(i, NEEDMONEY)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_NeedItem = DBFile.Search_Posistion(i, NEEDITEM)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_SourceSceneId = DBFile.Search_Posistion(i, SourceSceneId)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_SourcePosX = DBFile.Search_Posistion(i, SourcePosX)->iValue;
		g_MapInfoAttrTbl.m_TableExt[i].m_SourcePosZ = DBFile.Search_Posistion(i, SourcePosZ)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::Init_TitleInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum TitleData
	{
		TitileID			= 0,
		TitleType,
		TitleNameMale			= 4,
		TitleNameFemale,
		TitleTime			= 7,
		TitleBuff			= 9,
		TitleSuitID			= 11,
		TitleDataCount,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_TITLE_INFO);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_TITLE_SIZE);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iID = ThirdFile.Search_Posistion(i, TitileID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iID >= MAX_TITLE_SIZE)
		{
			KCheckEx(FALSE, "称号ID超出称号上限！");
			continue;
		}

		g_TitleInfoTbl.m_TableInfo[iID].m_TitleID = (uchar) iID;
		g_TitleInfoTbl.m_TableInfo[iID].m_iTitleType = ThirdFile.Search_Posistion(i, TitleType)->iValue;
		strncpy
		(
			g_TitleInfoTbl.m_TableInfo[iID].m_szMaleTitle,
			ThirdFile.Search_Posistion(i, TitleNameMale)->pString,
			sizeof(g_TitleInfoTbl.m_TableInfo[iID].m_szMaleTitle) - 1
		);

		strncpy
		(
			g_TitleInfoTbl.m_TableInfo[iID].m_szFemaleTitle,
			ThirdFile.Search_Posistion(i, TitleNameFemale)->pString,
			sizeof(g_TitleInfoTbl.m_TableInfo[iID].m_szFemaleTitle) - 1
		);

		g_TitleInfoTbl.m_TableInfo[iID].m_uTime = ThirdFile.Search_Posistion(i, TitleTime)->iValue;
		g_TitleInfoTbl.m_TableInfo[iID].m_iBuffID = ThirdFile.Search_Posistion(i, TitleBuff)->iValue;
		g_TitleInfoTbl.m_TableInfo[iID].m_iSuitID = ThirdFile.Search_Posistion(i, TitleSuitID)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::Init_TitleCombinationTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum TitleData
	{
		Group_ID			= 0,
		TitileID,
		ID_1,
		ID_2,
		ID_3,
		ID_4,
		ID_5,
		ID_6,
		ID_7,
		ID_8,
		ID_9,
		ID_10,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_TITLE_COMBINATION);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_TITLE_SIZE);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iID = ThirdFile.Search_Posistion(i, Group_ID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iID >= MAX_TITLE_SIZE)
		{
			KCheckEx(FALSE, "组ID超出上限！");
			continue;
		}

		g_TitleComTbl.m_TableCombination[iID].m_iGroupID = iID;
		g_TitleComTbl.m_TableCombination[iID].m_comTitleID = ThirdFile.Search_Posistion(i, TitileID)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[0] = ThirdFile.Search_Posistion(i, ID_1)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[1] = ThirdFile.Search_Posistion(i, ID_2)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[2] = ThirdFile.Search_Posistion(i, ID_3)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[3] = ThirdFile.Search_Posistion(i, ID_4)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[4] = ThirdFile.Search_Posistion(i, ID_5)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[5] = ThirdFile.Search_Posistion(i, ID_6)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[6] = ThirdFile.Search_Posistion(i, ID_7)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[7] = ThirdFile.Search_Posistion(i, ID_8)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[8] = ThirdFile.Search_Posistion(i, ID_9)->iValue;
		g_TitleComTbl.m_TableCombination[iID].m_arPart[9] = ThirdFile.Search_Posistion(i, ID_10)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadAttrLevelupTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum AttrLevelupTBData { TBLevel = 0, TBDataBegin = 1 };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ATTR_LEVEL_UP);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == MAX_TABLE_DEFINE_LEVEL + 1);

	for(int32 i = 0; i < MAX_TABLE_DEFINE_LEVEL + 1; i++)
	{
		for(int32 j = 0; j < PROFESSION_NUMBER; j++)
		{
			for(int32 k = 0; k < CPROPERTY_LEVEL_NUMBER; k++) //每个职业5行
			{
				iColumn = TBDataBegin + j * CPROPERTY_LEVEL_NUMBER + k;

				KCheck(iColumn < iTableColumn);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	iValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				g_PropertyLevelupTab.Set(k, j, i, iValue);
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadLevelExpTable()
{
	__GUARD__ 
		
	TABFile			ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PLAYER_EXP_LEVEL);
	int32			iTableCount = ThirdFile.GetRecordsNum();

	KCheck(iTableCount == MAX_PLAYER_EXP_LEVEL);

	for(int32 i = 0; i < MAX_PLAYER_EXP_LEVEL; i++)
	{
		g_LevelupExpTab.m_Table[i][0] = i;
		g_LevelupExpTab.m_Table[i][1] = StrToUINT64(ThirdFile.Search_Posistion(i, 1)->pString);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadInherenceExpTable()
{
	__GUARD__ 
	
	TABFile			ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PLAYER_EXP_INHERENCE);
	int32			iTableCount = ThirdFile.GetRecordsNum();

	KCheck(iTableCount == MAX_PLAYER_INHERENCE_LEVEL);

	for(int32 i = 0; i < MAX_PLAYER_INHERENCE_LEVEL; i++)
	{
		g_InherenceExpTbl.m_Table_Exp[i] = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_InherenceExpTbl.m_Table_Money[i] = ThirdFile.Search_Posistion(i, 2)->iValue;
		g_InherenceExpTbl.m_Table_Item[i] = ThirdFile.Search_Posistion(i, 3)->iValue;
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Misc::LoadInherenceLevelAverageTable()
{
	__GUARD__ 

		TABFile			ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_INHERENCE_LEVEL_AVERAGE);
	int32			iTableCount = ThirdFile.GetRecordsNum();

	KCheck(iTableCount < MAX_INHERENCE_LEVEL_AVERAGE);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_InherenceLevelTab.m_Table_Player_level[i] = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_InherenceLevelTab.m_Table_Inherence_level[i] = ThirdFile.Search_Posistion(i, 2)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadGrowPointTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum GrowPointTBLData
	{
		TBIndex					= 0,
		TBName					= 1,
		TBOpenAbility				= 2,
		TBMesh					= 3,
		TBOpenTask				= 4,
		TBTips					= 5,
		TBOpenTime				= 6,
		TBScriptID				= 7,
		TBOpenAnim				= 8
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GROWPOINT);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(TBOpenAnim < iColumnCount);

	g_GatherPointInfoTab.m_Count = iTableCount;
	g_GatherPointInfoTab.m_Table = new _GATHER_POINT_INFO[iTableCount];
	for(int32 i = 0; i < iTableCount; i++)
	{
		g_GatherPointInfoTab.m_Table[i].m_GrowPointIndex = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		g_GatherPointInfoTab.m_Table[i].m_OpenTime = ThirdFile.Search_Posistion(i, TBOpenTime)->iValue;
		g_GatherPointInfoTab.m_Table[i].m_OpenAnim = ThirdFile.Search_Posistion(i, TBOpenAnim)->iValue;
		g_GatherPointInfoTab.m_Table[i].m_OpenAbility = ThirdFile.Search_Posistion(i, TBOpenAbility)->iValue;
		g_GatherPointInfoTab.m_Table[i].m_ScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
		KCheck(g_GatherPointInfoTab.m_Table[i].m_ScriptID <= 0 || g_GatherPointInfoTab.m_Table[i].m_ScriptID >= 100000);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadGameOpenTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum GameOpenTBLData
	{
		TBIndex					= 0,
		TBName					= 1,
		TBGameId				= 2,
		TBValue					= 3
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GAMEOPEN);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(TBValue < iColumnCount);

	g_GameOpenInfoTbl.m_Count = iTableCount;
	g_GameOpenInfoTbl.m_Table = new _GAME_OPEN_INFO[iTableCount];
	for(int32 i = 0; i < iTableCount; i++)
	{
		g_GameOpenInfoTbl.m_Table[i].m_GameOpenIndex = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		g_GameOpenInfoTbl.m_Table[i].m_nGameId = ThirdFile.Search_Posistion(i, TBGameId)->iValue;
		g_GameOpenInfoTbl.m_Table[i].m_nValue = ThirdFile.Search_Posistion(i, TBValue)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Misc::LoadIdCollectionMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_CollectionIDMgr.InitFromDB(FILE_ID_COLLECTION))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Misc::LoadSpecialObjDataMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_SpecialObjDataTemplate.InitFromDB(FILE_SPECIAL_OBJ_DATA))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadScriptListFile()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	ret = g_ScriptFileMgr.Init(FILE_SCRIPT, FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadIPRange()
{
	__GUARD__

	Configer	ini(FILE_IPRANGE);
	int32		i;
	

	g_IPFilter.m_EnableCount = ini.Get_Property_Int("enableip", "count");
	for(i = 0; i < g_IPFilter.m_EnableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szIP[32], szMask[32];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		sprintf(szIP, "ip%d", i);
		sprintf(szMask, "mask%d", i);
		ini.GetText("enableip", szIP, g_IPFilter.m_aaIPEnable[i], IP_SIZE);
		ini.GetText("enableip", szMask, g_IPFilter.m_aaMaskEnable[i], IP_SIZE);
	}

	g_IPFilter.m_DisableCount = ini.Get_Property_Int("disableip", "count");
	for(i = 0; i < g_IPFilter.m_DisableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szIP[32], szMask[32];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		sprintf(szIP, "ip%d", i);
		sprintf(szMask, "mask%d", i);
		ini.GetText("disableip", szIP, g_IPFilter.m_aaIPDisable[i], IP_SIZE);
		ini.GetText("disableip", szMask, g_IPFilter.m_aaMaskDisable[i], IP_SIZE);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadChatConsume()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_CHAT_CONSUME);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_ChatConsumeTab.m_Count = iTableCount;

	KCheck(iTableCount <= MAX_CHAT_TYPE_INTABLE);
	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iIndex = ThirdFile.Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeCount = 0;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_DelayTime = ThirdFile.Search_Posistion(i, 2)->iValue * 1000;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[0] = ThirdFile.Search_Posistion(i, 4)->iValue;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeValue[0] = ThirdFile.Search_Posistion(i, 5)->iValue;
		if(g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[0] != CHAT_NEED_NONE)
			g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeCount = 1;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[1] = ThirdFile.Search_Posistion(i, 6)->iValue;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeValue[1] = ThirdFile.Search_Posistion(i, 7)->iValue;
		if(g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[1] != CHAT_NEED_NONE)
			g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeCount = 2;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[2] = ThirdFile.Search_Posistion(i, 8)->iValue;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeValue[2] = ThirdFile.Search_Posistion(i, 9)->iValue;
		if(g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeType[2] != CHAT_NEED_NONE)
			g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_ConsumeCount = 3;
		g_ChatConsumeTab.m_ChatComsumeType[iIndex].m_NeedLevel = ThirdFile.Search_Posistion(i, 10)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadHairStyleTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_HAIRSTYLE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Hair Style table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_Hair_Style_Tab.m_uCount = iTableCount;

	KCheck(iTableCount <= MAX_HAIR_STYLE_INTABLE);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_Hair_Style_Tab.m_HairStyle[i].m_nIndex = ThirdFile.Search_Posistion
			(
				i,
				SHairStyleType::HAIRSTYLE_INDEX
			)->iValue;
		g_Hair_Style_Tab.m_HairStyle[i].m_nRaceID = ThirdFile.Search_Posistion
			(
				i,
				SHairStyleType::HAIRSTYLE_RACEID
			)->iValue;
		g_Hair_Style_Tab.m_HairStyle[i].m_uItemSerial = ThirdFile.Search_Posistion
			(
				i,
				SHairStyleType::HAIRSTYLE_ITEMSERIAL
			)->iValue;
		g_Hair_Style_Tab.m_HairStyle[i].m_nItemCostCount = ThirdFile.Search_Posistion
			(
				i,
				SHairStyleType::HAIRSTYLE_ITEMCOSTCOUNT
			)->iValue;
		g_Hair_Style_Tab.m_HairStyle[i].m_nUseScope = ThirdFile.Search_Posistion
			(
				i,
				SHairStyleType::HAIRSTYLE_USESCOPE
			)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadGMTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum GMTable { GM_GUID = 0, GM_RIGHT, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GMLIST);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_GMTab.m_uCount = ThirdFile.GetRecordsNum();
	KCheck(g_GMTab.m_uCount <= MAX_GM_SIZE);

	for(int32 i = 0; i < g_GMTab.m_uCount; ++i)
	{
		//g_GMTab.m_aGUID[i] = (GUID_t) (ThirdFile.Search_Posistion(i, GM_GUID)->iValue);
		g_GMTab.m_aGUID[i] = (GUID_t)StrToUINT64(ThirdFile.Search_Posistion(i, GM_GUID)->pString);
		g_GMTab.m_nRight[i] = ThirdFile.Search_Posistion(i, GM_RIGHT)->iValue;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadDyShopInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_DY_SHOP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read DyShop Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_DyShopInfoTbl.m_iCount = iTableCount;

	KCheck(iTableCount <= MAX_DYSHOP_GROUP);

	/*~~~~~~~~~~~~~~~~*/
	int32	itemnum = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_DyShopInfoTbl.m_aGroupInfo[i].m_GroupId = ThirdFile.Search_Posistion
			(
				i,
				DYSHOP_GROUP::DY_GROUPID
			)->iValue;
		g_DyShopInfoTbl.m_aGroupInfo[i].m_GoodsNum = ThirdFile.Search_Posistion
			(
				i,
				DYSHOP_GROUP::DY_NUM
			)->iValue;
		itemnum = g_DyShopInfoTbl.m_aGroupInfo[i].m_GoodsNum;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	k = 0, j = 0, num = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		while(k < itemnum * DYSHOP_GROUP::DY_ITEM_PROPERTY_NUM)
		{
			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_ItemID = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;
			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_ItemNumMin = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;
			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_ItemNumMax = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;

			KCheck
			(
				g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_ItemNumMin <= g_DyShopInfoTbl.
					m_aGroupInfo[i].m_Goods[num].m_ItemNumMax
			);

			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_Rate = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;
			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_RandPriceType = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;
			g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_PriceNum = ThirdFile.Search_Posistion
				(
					i,
					DYSHOP_GROUP::DY_BEGIN + k++
				)->iValue;

			for(int32 j = 0; j < 10; ++j)
			{
				g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_PriceType[j] = ThirdFile.Search_Posistion
					(
						i,
						DYSHOP_GROUP::DY_BEGIN + k++
					)->iValue;
				g_DyShopInfoTbl.m_aGroupInfo[i].m_Goods[num].m_Price[j] = ThirdFile.Search_Posistion
					(
						i,
						DYSHOP_GROUP::DY_BEGIN + k++
					)->iValue;
			}

			++num;
		}
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::g_StrLoadShopInfoTable()
{
	__GUARD__	
	
	LoadGuildMechTable();

	uint32		d = sizeof(SItem);
	TABFile		ShopFile(0);
	BOOL		ret = ShopFile.OpenFromTXT(FILE_SHOP);
	int32		iTableCount = ShopFile.GetRecordsNum();
	int32		iTableColumn = ShopFile.GetFieldsNum();

	g_ShopInfoTbl.m_iCount = iTableCount;
	KCheck(iTableCount < MAX_SHOP_GROUP);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		itemnum = 0;
	int32		i, j, k;
	int32		itemTypeSn;
	SItemType	itemType;
	int32		PerItemNum = 0;
	int32		MaxItemNum = 0;
	uint32		nPrice = 0;
	float		PerRate = 0.0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < iTableCount; i++)
	{
		g_ShopInfoTbl.m_aShop[i].m_ShopId = ShopFile.Search_Posistion(i, SHOP_ID)->iValue;
		strncpy
		(
			g_ShopInfoTbl.m_aShop[i].m_ShopName,
			ShopFile.Search_Posistion(i, SHOP_NAME)->pString,
			SHOP_NAME_LENGTH - 1
		);
		g_ShopInfoTbl.m_aShop[i].m_ShopName[SHOP_NAME_LENGTH - 1] = 0;

		g_ShopInfoTbl.m_aShop[i].m_nBuyType = ShopFile.Search_Posistion(i, SHOP_BUY_TYPE)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_PriceType = ShopFile.Search_Posistion(i, SHOP_PRICE_TYPE)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_scale = ShopFile.Search_Posistion(i, SHOP_SCALE)->fValue;
		g_ShopInfoTbl.m_aShop[i].m_nRate = ShopFile.Search_Posistion(i, SHOP_RATE)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_IsDyShop = ShopFile.Search_Posistion(i, SHOP_TYPE)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_refreshTime1 = ShopFile.Search_Posistion(i, SHOP_REFRESH_TIME_1)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_refreshTime2 = ShopFile.Search_Posistion(i, SHOP_REFRESH_TIME_2)->iValue;
		itemnum = ShopFile.Search_Posistion(i, SHOP_ITEM_NUM)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_TimeType = ShopFile.Search_Posistion(i, SHOP_TIME_TYPE)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_StartTime = ShopFile.Search_Posistion(i, SHOP_START_TIME)->iValue;
		g_ShopInfoTbl.m_aShop[i].m_EndTime = ShopFile.Search_Posistion(i, SHOP_END_TIME)->iValue;
		KCheck(itemnum <= 40);

		/*~~~~~~~~~~~~~*/
		int32	nNum = 0;
		/*~~~~~~~~~~~~~*/

		for(k = 0; k < itemnum * SHOP_ITEM_PROPERTY_NUM; k++)
		{
			itemTypeSn = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + k)->iValue;

			if(itemTypeSn == 0)
			{
				break;
			}

			nNum++;
			k = k + 4;
		}

		itemnum = nNum;

		g_ShopInfoTbl.m_aShop[i].m_ItemList = new SShop::_MERCHANDISE_LIST(itemnum);

		for(j = 0; j < itemnum * SHOP_ITEM_PROPERTY_NUM; j++)
		{
			itemTypeSn = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + j)->iValue;

			if(g_ShopInfoTbl.m_aShop[i].m_PriceType == CU_GP)
			{
				if(itemTypeSn <= 0 || itemTypeSn >= MAX_GUILD_MERCH)
				{
					/*~~~~~~~~~~~~~~~~~~~*/
					char	assetmsg[1024];
					/*~~~~~~~~~~~~~~~~~~~*/

					sprintf(assetmsg, "文件%s中第%d行第%d列的帮贡商品索引不正确", FILE_SHOP, i, j);
					KCheckEx(FALSE, assetmsg);
				}

				itemTypeSn = g_GuildMerchTbl.m_aMerchList[itemTypeSn - 1].m_nMerchID;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			STSerialHelper	help(itemTypeSn);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			itemType = help.GetItemTypeStruct();

			PerItemNum = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(PerItemNum < 0) PerItemNum = 1;
			if(PerItemNum > 100) PerItemNum = 100;

			MaxItemNum = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(MaxItemNum == 0) MaxItemNum = -1;
			if(PerItemNum > 100) PerItemNum = 100;

			nPrice = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(nPrice == -1) nPrice = 0;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ratePer = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			uchar	nIconType = 0;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(ratePer >= 100)
			{
				nIconType = ratePer - 100;
				ratePer = 100;
			}

			if(ratePer == -1)
				PerRate = 1.0;
			else
				PerRate = ratePer / 100.f;

			g_ShopInfoTbl.m_aShop[i].m_ItemList->AddType
				(
					itemType,
					PerItemNum,
					MaxItemNum,
					PerRate,
					nIconType,
					g_ShopInfoTbl.m_aShop[i].m_PriceType,
					nPrice
				);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadPKPointInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PK_POINT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read PK_Point Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_PKPointTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_PK_NUM);

	/*~~~~~~~~~~~~~~~~*/
	int32	itemnum = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_PKPointTbl.m_aPKPointInfo[i].m_nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		g_PKPointTbl.m_aPKPointInfo[i].m_nMin = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_PKPointTbl.m_aPKPointInfo[i].m_nMax = ThirdFile.Search_Posistion(i, 2)->iValue;
		g_PKPointTbl.m_aPKPointInfo[i].m_nValue = ThirdFile.Search_Posistion(i, 3)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadPKLevelInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PK_LEVEL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read PK_Level Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_PKLevelTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_PK_NUM);

	/*~~~~~~~~~~~~~~~~*/
	int32	itemnum = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_PKLevelTbl.m_aPKPointInfo[i].m_nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		g_PKLevelTbl.m_aPKPointInfo[i].m_nMin = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_PKLevelTbl.m_aPKPointInfo[i].m_nMax = ThirdFile.Search_Posistion(i, 2)->iValue;
		g_PKLevelTbl.m_aPKPointInfo[i].m_nValue = ThirdFile.Search_Posistion(i, 3)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadPKPunishInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PK_PUNISH);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read PK_Punish Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_PKPunishTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_PK_NUM);

	/*~~~~~~~~~~~~~~~~*/
	int32	itemnum = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_PKPunishTbl.m_aPKPointInfo[i].m_nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		g_PKPunishTbl.m_aPKPointInfo[i].m_nMin = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_PKPunishTbl.m_aPKPointInfo[i].m_nMax = ThirdFile.Search_Posistion(i, 2)->iValue;
		g_PKPunishTbl.m_aPKPointInfo[i].m_nValue = ThirdFile.Search_Posistion(i, 3)->iValue;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOpenBoxInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_OPENBOX_ITEM);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "InitOpenBoxInfoTable failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= OpenBox_ItemInfo_Table::ITEM_KIND_MAX_NUM && iTableCount >= 0);
	KCheck(iTableColumn <= OpenBox_ItemInfo_Table::COLUMN_MAX_NUM && iTableColumn >= 0);

	g_OpenBox_ItemInfo_Table.m_KindRealNum = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~*/
		int	nIndex = 0;
		/*~~~~~~~~~~~~~~~*/

		g_OpenBox_ItemInfo_Table.m_ItemInfoRow[i].m_Index = ThirdFile.Search_Posistion(i, nIndex++)->iValue;

		for(int32 j = 0; j < OpenBox_ItemInfo_Table::ItemInfoRow::ITEM_INFO_MAX_NUM; ++j)
		{
			if(ThirdFile.Search_Posistion(i, nIndex)->iValue > 0)
			{
				g_OpenBox_ItemInfo_Table.m_ItemInfoRow[i].m_ItemInfo[j].m_ItemID = ThirdFile.Search_Posistion(i, nIndex++)->iValue;

				g_OpenBox_ItemInfo_Table.m_ItemInfoRow[i].m_ItemInfo[j].m_Rate1 = ThirdFile.Search_Posistion(i, nIndex++)->iValue;

				g_OpenBox_ItemInfo_Table.m_ItemInfoRow[i].m_ItemInfo[j].m_Rate2 = ThirdFile.Search_Posistion(i, nIndex++)->iValue;

				g_OpenBox_ItemInfo_Table.m_ItemInfoRow[i].m_RealNum++;
			}
			else
			{
				break;
			}
		}
	}

}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadDurSpoilInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_DUR_SPOIL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "InitDurSpoilInfoTable failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int	nIndex = 0;
		int32	EquipPos = ThirdFile.Search_Posistion(i, nIndex++)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(EquipPos > -1);
		KCheck(EquipPos < EQUIP_TYPE_NUM);

		g_DurSpoilValueTbl.m_Table[EquipPos].m_nDamageMode = ThirdFile.Search_Posistion(i, nIndex++)->iValue;
		g_DurSpoilValueTbl.m_Table[EquipPos].m_nValue = ThirdFile.Search_Posistion(i, nIndex)->iValue;
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOndieMonsterTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		ONDIEMONSTER_ENDURE_MIN			= 1,
		ONDIEMONSTER_ENDURE_MAX,
		ONDIEMONSTER_BAGDROP_MIN,
		ONDIEMONSTER_BAGDROP_MAX,
		ONDIEMONSTER_EQUIPDROP_MIN,
		ONDIEMONSTER_EQUIPDROP_MAX,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONDIE_MONSTER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Ondie_Monster Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieMonsterTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_ONDIE_NUM);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_OndieMonsterTbl.m_aEndureMin[i] = ThirdFile.Search_Posistion(i, ONDIEMONSTER_ENDURE_MIN)->iValue;
		g_OndieMonsterTbl.m_aEndureMax[i] = ThirdFile.Search_Posistion(i, ONDIEMONSTER_ENDURE_MAX)->iValue;
		g_OndieMonsterTbl.m_aBagDropMin[i] = ThirdFile.Search_Posistion(i, ONDIEMONSTER_BAGDROP_MIN)->iValue;
		g_OndieMonsterTbl.m_aBagDropMax[i] = ThirdFile.Search_Posistion(i, ONDIEMONSTER_BAGDROP_MAX)->iValue;
		g_OndieMonsterTbl.m_aEquipDropMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEMONSTER_EQUIPDROP_MIN
			)->iValue;
		g_OndieMonsterTbl.m_aEquipDropMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEMONSTER_EQUIPDROP_MAX
			)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOndieNopunishTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { ONDIENOPUNISH_ENDURE_MIN = 1, ONDIENOPUNISH_ENDURE_MAX, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONDIE_NOPUNISH);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Ondie_Nopunish Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieNopunishTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_ONDIE_NUM);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_OndieNopunishTbl.m_aEndureMin[i] = ThirdFile.Search_Posistion(i, ONDIENOPUNISH_ENDURE_MIN)->iValue;
		g_OndieNopunishTbl.m_aEndureMax[i] = ThirdFile.Search_Posistion(i, ONDIENOPUNISH_ENDURE_MAX)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOndieDiffCountryTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		ONDIEDIFFCOUNTRY_ENDURE_MIN		= 1,
		ONDIEDIFFCOUNTRY_ENDURE_MAX,
		ONDIEDIFFCOUNTRY_BAGDROP_MIN,
		ONDIEDIFFCOUNTRY_BAGDROP_MAX,
		ONDIEDIFFCOUNTRY_EQUIPDROP_MIN,
		ONDIEDIFFCOUNTRY_EQUIPDROP_MAX,
		ONDIEDIFFCOUNTRY_HONOR,
		ONDIEDIFFCOUNTRY_KILLER_HONOR,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONDIE_DIFFCOUNTRY);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Ondie_DiffCountry Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieDiffCountryTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_ONDIE_NUM_2);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_OndieDiffCountryTbl.m_aEndureMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_ENDURE_MIN
			)->iValue;
		g_OndieDiffCountryTbl.m_aEndureMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_ENDURE_MAX
			)->iValue;
		g_OndieDiffCountryTbl.m_aBagDropMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_BAGDROP_MIN
			)->iValue;
		g_OndieDiffCountryTbl.m_aBagDropMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_BAGDROP_MAX
			)->iValue;
		g_OndieDiffCountryTbl.m_aEquipDropMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_EQUIPDROP_MIN
			)->iValue;
		g_OndieDiffCountryTbl.m_aEquipDropMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_EQUIPDROP_MAX
			)->iValue;
		g_OndieDiffCountryTbl.m_aSelfHonor[i] = ThirdFile.Search_Posistion(i, ONDIEDIFFCOUNTRY_HONOR)->iValue;
		g_OndieDiffCountryTbl.m_aKillerHonor[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIEDIFFCOUNTRY_KILLER_HONOR
			)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOndieSameCountryTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		ONDIESAMECOUNTRY_ENDURE_MIN		= 1,
		ONDIESAMECOUNTRY_ENDURE_MAX,
		ONDIESAMECOUNTRY_BAGDROP_MIN,
		ONDIESAMECOUNTRY_BAGDROP_MAX,
		ONDIESAMECOUNTRY_EQUIPDROP_MIN,
		ONDIESAMECOUNTRY_EQUIPDROP_MAX,
		ONDIESAMECOUNTRY_PK,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONDIE_SAMECOUNTRY);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Ondie_SameCountry Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieSameCountryTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_ONDIE_NUM_2);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_OndieSameCountryTbl.m_aEndureMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_ENDURE_MIN
			)->iValue;
		g_OndieSameCountryTbl.m_aEndureMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_ENDURE_MAX
			)->iValue;
		g_OndieSameCountryTbl.m_aBagDropMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_BAGDROP_MIN
			)->iValue;
		g_OndieSameCountryTbl.m_aBagDropMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_BAGDROP_MAX
			)->iValue;
		g_OndieSameCountryTbl.m_aEquipDropMin[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_EQUIPDROP_MIN
			)->iValue;
		g_OndieSameCountryTbl.m_aEquipDropMax[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRY_EQUIPDROP_MAX
			)->iValue;
		g_OndieSameCountryTbl.m_aSelfPK[i] = ThirdFile.Search_Posistion(i, ONDIESAMECOUNTRY_PK)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadOndieSameCountryKillerTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { ONDIESAMECOUNTRYKILLER_PK1 = 1, ONDIESAMECOUNTRYKILLER_PK2, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONDIE_SAMECOUNTRY_KILLER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read Ondie_Killer Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieSameCountryKillerTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_ONDIE_NUM_2);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_OndieSameCountryKillerTbl.m_aPK1[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRYKILLER_PK1
			)->iValue;
		g_OndieSameCountryKillerTbl.m_aPK2[i] = ThirdFile.Search_Posistion
			(
				i,
				ONDIESAMECOUNTRYKILLER_PK2
			)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadReliveCostTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { RELIVECOST_1 = 1, RELIVECOST_2, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ONRELIVE_COST);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read OnRelive_Cost Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_OndieSameCountryKillerTbl.m_nCount = iTableCount;

	KCheck(iTableCount <= MAX_RELIVE_COST);

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_ReliveCostTbl.m_aCost1[i] = ThirdFile.Search_Posistion(i, RELIVECOST_1)->iValue;
		g_ReliveCostTbl.m_aCost2[i] = ThirdFile.Search_Posistion(i, RELIVECOST_2)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadDeathDealTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		DEATHDEAL_DEATH_SCENEID			= 0,
		DEATHDEAL_SCENENAME,
		DEATHDEAL_SCENEID,
		DEATHDEAL_X				= 5,
		DEATHDEAL_Z,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_DEATH_DEAL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "Read DeathDeal Info table failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_DeathDealTbl.m_nCount = iTableCount;

	for(int32 i = 0; i < iTableCount; i++)
	{
		g_DeathDealTbl.m_aX[i] = ThirdFile.Search_Posistion(i, DEATHDEAL_X)->iValue;
		g_DeathDealTbl.m_aZ[i] = ThirdFile.Search_Posistion(i, DEATHDEAL_Z)->iValue;
		g_DeathDealTbl.m_aSceneID[i] = ThirdFile.Search_Posistion(i, DEATHDEAL_SCENEID)->iValue;
	}

	__UNGUARD__
}




/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadBeastieDataTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		BEASTIE_ID				= 0,
		MODEL_ID				= 1,
		HEAD_IMAGE				= 2,
		SCENE_ID				= 3,
		RESPAWN_TIME				= 13,
		BEASTIE_NAME,
		POS_X,
		POS_Z,
		ITEM_ID,
		SPEED,
		DIRCTION,
		TYPE
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_BEASTIE_ATTR);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < _BEASTIE_DATA_TABLE::MAX_ITEM_COUNT);

	g_BeastieDataTable.m_uCount = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_BeastieDataTable.m_BeastieItem[i].m_nSceneId = ThirdFile.Search_Posistion(i, SCENE_ID)->iValue;
		g_BeastieDataTable.m_BeastieItem[i].m_uBeastieId = ThirdFile.Search_Posistion(i, BEASTIE_ID)->iValue;

		strncpy
		(
			g_BeastieDataTable.m_BeastieItem[i].m_szName,
			ThirdFile.Search_Posistion(i, BEASTIE_NAME)->pString,
			sizeof(g_BeastieDataTable.m_BeastieItem[i].m_szName) - 1
		);

		g_BeastieDataTable.m_BeastieItem[i].m_PosX = ThirdFile.Search_Posistion(i, POS_X)->fValue;
		g_BeastieDataTable.m_BeastieItem[i].m_PosZ = ThirdFile.Search_Posistion(i, POS_Z)->fValue;
		g_BeastieDataTable.m_BeastieItem[i].m_nItemId = ThirdFile.Search_Posistion(i, ITEM_ID)->iValue;
		g_BeastieDataTable.m_BeastieItem[i].m_fSpeed = ThirdFile.Search_Posistion(i, SPEED)->fValue;
		g_BeastieDataTable.m_BeastieItem[i].m_nModelId = ThirdFile.Search_Posistion(i, MODEL_ID)->iValue;
		g_BeastieDataTable.m_BeastieItem[i].m_RespawnTime = ThirdFile.Search_Posistion(i, RESPAWN_TIME)->iValue;
		g_BeastieDataTable.m_BeastieItem[i].m_fDirection = ThirdFile.Search_Posistion(i, DIRCTION)->fValue;
		g_BeastieDataTable.m_BeastieItem[i].m_nType = ThirdFile.Search_Posistion(i, TYPE)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadVigorDataTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { LEVEL = 0, RECOVER_ONCE, MAX_VIGOR, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_VIGOR_DATA);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == _VIGOR_DATA_TABLE::MAX_ITEM_COUNT);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_VigorDataTable.m_VigorItem[i].m_Level = (uchar) ThirdFile.Search_Posistion(i, LEVEL)->iValue;
		g_VigorDataTable.m_VigorItem[i].m_RecoverOnce = ThirdFile.Search_Posistion(i, RECOVER_ONCE)->iValue;
		g_VigorDataTable.m_VigorItem[i].m_MaxVigor = ThirdFile.Search_Posistion(i, MAX_VIGOR)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadGuildMechTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { Index = 0, ItemID, GuildLevel, GuildExp, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GUILDSHOP);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= MAX_GUILD_MERCH);

	g_GuildMerchTbl.m_iCount = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	assetmsg[1024];
		int32	iIndex = ThirdFile.Search_Posistion(i, Index)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		iIndex -= 1;

		if(iIndex < 0 || iIndex >= MAX_GUILD_MERCH)
		{
			sprintf(assetmsg, "文件%s中第%d行的帮贡商品索引不应为%d", FILE_GUILDSHOP, i, iIndex);
			KCheckEx(FALSE, assetmsg);
			continue;
		}

		g_GuildMerchTbl.m_aMerchList[iIndex].m_nMerchID = ThirdFile.Search_Posistion(i, ItemID)->iValue;
		if(g_GuildMerchTbl.m_aMerchList[iIndex].m_nMerchID < 0)
		{
			sprintf(assetmsg, "文件%s中第%d行的帮贡商品ID不应小于0", FILE_GUILDSHOP, i);
			KCheckEx(FALSE, assetmsg);
			continue;
		}

		g_GuildMerchTbl.m_aMerchList[iIndex].m_nGuildLevel = ThirdFile.Search_Posistion(i, GuildLevel)->iValue;
		if(g_GuildMerchTbl.m_aMerchList[iIndex].m_nGuildLevel < 0)
		{
			sprintf(assetmsg, "文件%s中第%d行的帮会等级不应小于0", FILE_GUILDSHOP, i);
			KCheckEx(FALSE, assetmsg);
			continue;
		}

		g_GuildMerchTbl.m_aMerchList[iIndex].m_nGuildExp = ThirdFile.Search_Posistion(i, GuildExp)->iValue;
		if(g_GuildMerchTbl.m_aMerchList[iIndex].m_nGuildExp < 0)
		{
			sprintf(assetmsg, "文件%s中第%d行的帮会经验不应小于0", FILE_GUILDSHOP, i);
			KCheckEx(FALSE, assetmsg);
			continue;
		}
	}

	g_GuildMerchTbl.m_bInitOK = TRUE;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadAwardInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum AwardAttrData { AwardId = 0,Name , Text, ScriptId, BagNeedSpace, MinSpliceNum, };
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_AWARD_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_AWARD_INFO);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount >= 0 && iTableCount < AWARD_EXT_ATTR_ENUM_SIZE);

	memset((void *) &g_AwardAttrExTbl, 0, sizeof(g_AwardAttrExTbl));

	g_AwardAttrExTbl.m_Count = iTableCount;

	KCheck(MinSpliceNum < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_AwardAttrExTbl.m_TableExt[i].m_AwardId = DBFile.Search_Posistion(i, AwardId)->iValue;

		strncpy
		(
			g_AwardAttrExTbl.m_TableExt[i].m_AwardName,
			DBFile.Search_Posistion(i, Name)->pString,
			AWARD_NAME_LEN
		);
		strncpy
		(
			g_AwardAttrExTbl.m_TableExt[i].m_AwardText,
			DBFile.Search_Posistion(i, Text)->pString,
			AWARD_TEXT_LEN
		);

		g_AwardAttrExTbl.m_TableExt[i].m_ScriptId = DBFile.Search_Posistion(i, ScriptId)->iValue;
		KCheck(g_AwardAttrExTbl.m_TableExt[i].m_ScriptId <= 0 || g_AwardAttrExTbl.m_TableExt[i].m_ScriptId >= 100000);
		g_AwardAttrExTbl.m_TableExt[i].m_BagNeedSpace = DBFile.Search_Posistion(i, BagNeedSpace)->iValue;
		g_AwardAttrExTbl.m_TableExt[i].m_MinSpliceNum = DBFile.Search_Posistion(i, MinSpliceNum)->iValue;
		if(g_AwardAttrExTbl.m_TableExt[i].m_BagNeedSpace != 0)
		{
			KCheck(g_AwardAttrExTbl.m_TableExt[i].m_MinSpliceNum != 0);
		}
	}

	g_AwardAttrExTbl.m_Count = iTableCount;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadSceneCommonTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { eSceneId = 0, eScriptString, eIsTiredScene, };
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_SCENE_COMMON);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_SCENE_COMMON);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount >= 0 && iTableCount <= MAX_SCENE);

	KCheck(iTableCount == g_Config.m_MapInfo.m_MapCount);

	memset((void *) &g_SceneCommonTbl.m_TableExt, -1, sizeof(g_SceneCommonTbl.m_TableExt));

	g_SceneCommonTbl.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char		*pSplitString = NULL;
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_SceneCommonTbl.m_TableExt[i].m_SceneId = DBFile.Search_Posistion(i, eSceneId)->iValue;
		pSplitString = DBFile.Search_Posistion(i, eScriptString)->pString;

		if(pSplitString && pSplitString[0] != 0)
		{
			ReadSceneCommonScriptData
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_SceneCommonTbl.m_TableExt[i].m_ScriptList,
				SC_MAX_SCRIPT_NUM
			);
		}

		g_SceneCommonTbl.m_TableExt[i].m_IsTiredScene = DBFile.Search_Posistion(i, eIsTiredScene)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadWorldShopInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum AwardAttrData { ShopId = 0, GoldCash, Charge, ConcentNum, RemainTime, PageNum, };
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

	KCheck(PageNum < iColumnCount);

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
	}

	g_GLShopAttrExTbl.m_Count = iTableCount;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadEncryptInfoTable()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum EncryptInfoAttrData
	{
		Index,
		Parameter,
		ScriptId				= Parameter + ENCRYPT_OP_PARAM_NUM,
		FnName,
		Result,
	};
	/*~~~~~~~~~~~~*/

	TABFile DBFile(0);
	BOOL ret = DBFile.OpenFromTXT(FILE_ENCRYPT_INFO);
	KCheckEx(ret, FILE_ENCRYPT_INFO);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_ENCRYPT_INFO_NUM);
	g_EncryptInfoAttrTbl.m_Count = iTableCount;

	KCheck(Result < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_EncryptInfoAttrTbl.m_TableExt[i].m_Index = DBFile.Search_Posistion(i, Index)->iValue;
		for(int32 paraId = 0; paraId < ENCRYPT_OP_PARAM_NUM; paraId++)
		{
			g_EncryptInfoAttrTbl.m_TableExt[i].m_Parameter[paraId] = DBFile.Search_Posistion
				(
					i,
					Parameter + paraId
				)->iValue;
		}

		g_EncryptInfoAttrTbl.m_TableExt[i].m_ScriptId = DBFile.Search_Posistion(i, ScriptId)->iValue;
		KCheck(g_EncryptInfoAttrTbl.m_TableExt[i].m_ScriptId <= 0 || g_EncryptInfoAttrTbl.m_TableExt[i].m_ScriptId >= 100000);
		strncpy
		(
			g_EncryptInfoAttrTbl.m_TableExt[i].m_FnName,
			DBFile.Search_Posistion(i, FnName)->pString,
			ENCRYPT_OP_FUNCTION_NAME_SIZE
		);

		g_EncryptInfoAttrTbl.m_TableExt[i].m_Result = DBFile.Search_Posistion(i, Result)->iValue;
	}

	g_EncryptInfoAttrTbl.m_Count = iTableCount;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadAnswerInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum WorldShopAttrData { AnswerId = 0, Title, Result, };
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_SCENE_ANSWERS_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_SCENE_ANSWERS_INFO);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount >= 0 && iTableCount < ANSWER_LIST_NUM);
	memset((void *) &g_AnawerAttrExTbl, 0, sizeof(g_AnawerAttrExTbl));
	g_AnawerAttrExTbl.m_Count = iTableCount;

	KCheck(Result < iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_AnawerAttrExTbl.m_TableExt[i].m_AnswerId = DBFile.Search_Posistion(i, AnswerId)->iValue;
		strncpy
		(
			g_AnawerAttrExTbl.m_TableExt[i].m_Title,
			DBFile.Search_Posistion(i, Title)->pString,
			ANSWER_LIST_NUM
		);
		g_AnawerAttrExTbl.m_TableExt[i].m_Result = DBFile.Search_Posistion(i, Result)->iValue;
	}

	g_AnawerAttrExTbl.m_Count = iTableCount;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadFubenDataTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		eId					= 0,
		eScriptId,
		eBossFlag,
		eIndexFlag,
		eLevelMin,
		eLevelMax,
		eName,
		eTitle,
		eDataId,
		eGUID,
		ePosX,
		ePosZ,
		ePosR,
		eAI,
		eAIScript,
		eFlag0,
		eFlag1,
		eFlag2,
		eFlag3,
		eCreateCount,
		eFaceDir,
		ePartolId,
		eCampId,
		eColumnMaxCount
	};
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_FUBEN_DATA_TABLE_NAME);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_FUBEN_DATA_TABLE_NAME);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iColumnCount == eColumnMaxCount);

	if(iTableCount <= 0) return;

	g_FubenDataAttrTbl.m_FubenData = new FUBEN_DATA_ATTR[iTableCount];
	KCheck(g_FubenDataAttrTbl.m_FubenData);
	g_FubenDataAttrTbl.m_Count = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FUBEN_DATA_ATTR &cda = g_FubenDataAttrTbl.m_FubenData[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		cda.nId = DBFile.Search_Posistion(i, eId)->iValue;
		cda.nScriptId = DBFile.Search_Posistion(i, eScriptId)->iValue;
		KCheck(cda.nScriptId <= 0 || cda.nScriptId >= 100000);
		cda.nBossFlag = DBFile.Search_Posistion(i, eBossFlag)->iValue;
		cda.nIndexFlag = DBFile.Search_Posistion(i, eIndexFlag)->iValue;
		cda.nLevelMin = DBFile.Search_Posistion(i, eLevelMin)->iValue;
		cda.nLevelMax = DBFile.Search_Posistion(i, eLevelMax)->iValue;
		strncpy(cda.strName, DBFile.Search_Posistion(i, eName)->pString, MAX_CHARACTER_NAME);
		cda.strName[MAX_CHARACTER_NAME - 1] = 0;
		strncpy(cda.strTitle, DBFile.Search_Posistion(i, eTitle)->pString, MAX_CHARACTER_NAME);
		cda.strTitle[MAX_CHARACTER_NAME - 1] = 0;
		cda.nDataId = DBFile.Search_Posistion(i, eDataId)->iValue;
		cda.nGUID = DBFile.Search_Posistion(i, eGUID)->iValue;
		cda.nPosX = DBFile.Search_Posistion(i, ePosX)->fValue;
		cda.nPosZ = DBFile.Search_Posistion(i, ePosZ)->fValue;
		cda.nPosR = DBFile.Search_Posistion(i, ePosR)->iValue;
		cda.nAI = DBFile.Search_Posistion(i, eAI)->iValue;
		cda.nAIScript = DBFile.Search_Posistion(i, eAIScript)->iValue;
		cda.nFlag0 = DBFile.Search_Posistion(i, eFlag0)->iValue;
		cda.nFlag1 = DBFile.Search_Posistion(i, eFlag1)->iValue;
		cda.nFlag2 = DBFile.Search_Posistion(i, eFlag2)->iValue;
		cda.nFlag3 = DBFile.Search_Posistion(i, eFlag3)->iValue;
		cda.nCreateCount = DBFile.Search_Posistion(i, eCreateCount)->iValue;
		cda.nFaceDir = DBFile.Search_Posistion(i, eFaceDir)->iValue;
		cda.nPatrolId = DBFile.Search_Posistion(i, ePartolId)->iValue;
		cda.nCampID = DBFile.Search_Posistion(i, eCampId)->iValue;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::LoadCheatActDataTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { eId = 0, eValid, eErrorCount, eOPMode, eText, eColumnMaxCount };
	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT(FILE_CHEAT_ACT_DATA_TABLE_NAME);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, FILE_CHEAT_ACT_DATA_TABLE_NAME);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iColumnCount == eColumnMaxCount);
	if(iTableCount <= 0) return;
	KCheck(iTableCount >= 0 && iTableCount < CHEAT_ACT_NUM);
	memset((void *) &g_CheatActAttrTbl, 0, sizeof(g_CheatActAttrTbl));
	g_CheatActAttrTbl.m_Count = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_CheatActAttrTbl.m_TableExt[i].nId = DBFile.Search_Posistion(i, eId)->iValue;
		g_CheatActAttrTbl.m_TableExt[i].bValid = DBFile.Search_Posistion(i, eValid)->iValue;
		g_CheatActAttrTbl.m_TableExt[i].nErrorCount = DBFile.Search_Posistion(i, eErrorCount)->iValue;
		g_CheatActAttrTbl.m_TableExt[i].nOPMode = DBFile.Search_Posistion(i, eOPMode)->iValue;
	}

	__UNGUARD__
}

/*
 加载职业转换技能对应表。（2010-03-25 by ql）
 注意：因为职业和技能的转换是两两对应的，所以表里不必把所有职业和技能的转换数据都放入，程序会处理相应的职业及其技能转换信息。
 */
void TableInit_Map_Misc::LoadChangeProfession()
{
    __GUARD__;

    enum
    {
        eId = 0, 
        eProfIDSrc, 
        eSkillSrc, 
        eSkillDst, 
        eProfIDDst, 
        eDescription,
        eColumnCount
    };

	TABFile DBFile(0);
	BOOL	ret = DBFile.OpenFromTXT( FILE_CHANGE_PROFESSION_TABLE_NAME);

	KCheckEx( ret, FILE_CHANGE_PROFESSION_TABLE_NAME);

	int32	iTableCount = DBFile.GetRecordsNum();
	int32	iColumnCount = DBFile.GetFieldsNum();

	KCheck( iColumnCount == eColumnCount);

	if( iTableCount <= 0)
        return;

	KCheck( iTableCount >= 0 && iTableCount < ( MAX_CHAR_SKILL_NUM * PROFESSION_NUMBER / 2) );
	memset( ( void *)&g_ChangeProfessionTbl, 0, sizeof( g_ChangeProfessionTbl) );

    // 遍历整个表中本职业的行
    for( int32 i = 0; i < iTableCount; ++i)
    {
        int32 iProfSrc = DBFile.Search_Posistion( i, eProfIDSrc)->iValue;
        KCheck( iProfSrc >= PROFESSION_WUSHI && iProfSrc < PROFESSION_NUMBER);
        int32 iProfDst = DBFile.Search_Posistion( i, eProfIDDst)->iValue;
        KCheck( iProfDst >= PROFESSION_WUSHI && iProfDst < PROFESSION_NUMBER);
        int32 iSkillSrc = DBFile.Search_Posistion( i, eSkillSrc)->iValue;
        //KCheck( iProfDst >= 0 && iProfDst < MAX_CHAR_SKILL_NUM);
        int32 iSkillDst = DBFile.Search_Posistion( i, eSkillDst)->iValue;
        //KCheck( iProfDst >= 0 && iProfDst < MAX_CHAR_SKILL_NUM);

        // 保存职业对应技能转换数据
        g_ChangeProfessionTbl.m_arrConvert[ iProfSrc][ g_ChangeProfessionTbl.m_iCount[ iProfSrc] ].m_Index    = i;
        g_ChangeProfessionTbl.m_arrConvert[ iProfSrc][ g_ChangeProfessionTbl.m_iCount[ iProfSrc] ].m_ProfSrc  = iProfSrc;
        g_ChangeProfessionTbl.m_arrConvert[ iProfSrc][ g_ChangeProfessionTbl.m_iCount[ iProfSrc] ].m_SkillSrc = iSkillSrc;
        g_ChangeProfessionTbl.m_arrConvert[ iProfSrc][ g_ChangeProfessionTbl.m_iCount[ iProfSrc] ].m_SkillDst = iSkillDst;
        g_ChangeProfessionTbl.m_arrConvert[ iProfSrc][ g_ChangeProfessionTbl.m_iCount[ iProfSrc] ].m_ProfDest = iProfDst;
        ++g_ChangeProfessionTbl.m_iCount[ iProfSrc];

        // 保存转换目标职业的对应技能转换数据
        g_ChangeProfessionTbl.m_arrConvert[ iProfDst][ g_ChangeProfessionTbl.m_iCount[ iProfDst] ].m_Index    = i;
        g_ChangeProfessionTbl.m_arrConvert[ iProfDst][ g_ChangeProfessionTbl.m_iCount[ iProfDst] ].m_ProfSrc  = iProfDst;
        g_ChangeProfessionTbl.m_arrConvert[ iProfDst][ g_ChangeProfessionTbl.m_iCount[ iProfDst] ].m_SkillSrc = iSkillDst;
        g_ChangeProfessionTbl.m_arrConvert[ iProfDst][ g_ChangeProfessionTbl.m_iCount[ iProfDst] ].m_SkillDst = iSkillSrc;
        g_ChangeProfessionTbl.m_arrConvert[ iProfDst][ g_ChangeProfessionTbl.m_iCount[ iProfDst] ].m_ProfDest = iProfSrc;
        ++g_ChangeProfessionTbl.m_iCount[ iProfDst];
    }// for

    __UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Misc::ReadSceneCommonScriptData
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	ScriptID_t		*pVal,
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
			for(int i = 0; i < MaxCnt; i++)
			{
				pVal[id] = -1;
				return;
			}
		}
		else
			pVal[id] = atoi(pSplitL2->GetResultLine(id));
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_GatherPointTab(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_GATHER_POINT_INFO	*pTB1 = (_GATHER_POINT_INFO *) pArg1;
	_GATHER_POINT_INFO	*pTB2 = (_GATHER_POINT_INFO *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->m_GrowPointIndex > pTB2->m_GrowPointIndex)
		return 1;
	else if(pTB1->m_GrowPointIndex < pTB2->m_GrowPointIndex)
		return -1;
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_GATHER_POINT_INFO *_GATHER_POINT_INFO_TAB::Get(int32 GrowType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	_GATHER_POINT_INFO	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_GrowPointIndex = GrowType;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_GATHER_POINT_INFO	*pResult = (_GATHER_POINT_INFO *) bsearch
		(
			&tb,
			m_Table,
			m_Count,
			sizeof(_GATHER_POINT_INFO),
			(int32(*) (const void *, const void *)) Compare_GatherPointTab
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		KCheck(FALSE);
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search _GATHER_POINT_INFO  GrowPointType:%d Get Errors", GrowType);
	}

	return 0;
}

void GameOpenManager::SetGameOpen( int32 gameId, BOOL bOpen)
{
    std::lock_guard< FastLock> autolock( m_Lock);

    for(int32 i = 0; i < g_GameOpenInfoTbl.m_Count; i++)
    {
        if((g_GameOpenInfoTbl.m_Table[i].m_nGameId) == gameId)
        {
            if( bOpen == TRUE)
            {
                g_GameOpenInfoTbl.m_Table[i].m_nValue = TRUE;
            }// if
            else if( bOpen == FALSE)
            {
                g_GameOpenInfoTbl.m_Table[i].m_nValue = FALSE;
            }// else if
            break;
        }// if
    }// for
}

