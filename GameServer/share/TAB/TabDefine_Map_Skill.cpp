#include "stdafx.h"
#include "TabDefine_Map.h"
#include "BaseTool.h"
#include "ScriptCacheMgr.h"

#include "TAB.h"
#include "FileDef.h"
#include "gameobject/Behavior_State.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "shop/ShopManager.h"
#include "item/Item_Helper.h"
#include "gameobject/Behavior_Template.h"
#include "TabDefine_Map_Skill.h"
#include "TabDefine_Map_Misc.h"

using namespace			TAB;

Skill_Study_Condition_TABLE	g_SkillStudyCondition;
SpellTemplateDataMgr		g_SpellTemplateDataMgr;
SkillDataMgr_T			g_SpellDataMgr;
ImpactSEDataMgr_T		g_EffectSEDataMgr;
ImpactDataMgr_T			g_STDEffectMgr;
ImpactDirDataMgr_T		g_ImpactDirDataMgr;
_GIFT_BALANCE_INFO_TBL_1	g_GiftBalanceInfoTbl;
_GIFT_BALANCE_INFO_TBL_2	g_GiftBalanceInfoTbl_Ctrl;
_GIFT_ZHUANGONG			g_GiftZhuanGongInfoTbl;
_GIFT_ZHUANFANG			g_GiftZhuanFangInfoTbl;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Map_Skill::TableInit_Map_Skill()
{}

TableInit_Map_Skill::~TableInit_Map_Skill()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Skill::Init()
{
	__GUARD__

	BOOL bRet;
	LoadSKillStudyTable();

	bRet = LoadCampAndStandDataMgr();
	KCheck(bRet);
	bRet = LoadSkillTemplateDataMgr();
	KCheck(bRet);
	bRet = LoadSkillDataMgr();
	KCheck(bRet);
	bRet = LoadImpactSEDataMgr();
	KCheck(bRet);
	bRet = LoadStandardImpactMgr();
	KCheck(bRet);

	LoadImpactDirTable();

	Init_GiftBalanceInfoTable();
	Init_GiftBalanceInfoTable_Ctrl();

	Init_GiftZhuanGongInfoTable();
	Init_GiftZhuanFangInfoTable();

	return TRUE;
	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Skill::LoadSKillStudyTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	enum SkillStydyIndex
	{
		SSI_ID					= 0,
		SSI_PLayerLevelRequire,
		SSI_OccupationRequire,
		SSI_PlayerPointsRequire,
		SSI_ParentSkillID,
		SSI_ParentSkillLevelRequire,
		SSI_SpendPoints,
		SSI_SpendMoney,
		SSI_SpendExp,
		SSI_SpendItem1ID,
		SSI_SpendItem1Num,
		SSI_SpendItem2ID,
		SSI_SpendItem2Num,
		SSI_SpendItem3ID,
		SSI_SpendItem3Num,
		SSI_SkillIsMutex,
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_SKILL_STUDY);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "InitSKillStudyTable failed, please check it.");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= Skill_Study_Condition_TABLE::MAX_Skill_COUNT);

	g_SkillStudyCondition.m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	oSplitL1;
	const char		*pSplitString = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iIndex = ThirdFile.Search_Posistion(i, SSI_ID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iID = iIndex;
		pSplitString = ThirdFile.Search_Posistion(i, SSI_PLayerLevelRequire)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iPLayerLevelRequire
		);

		g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iOccupationRequire = ThirdFile.Search_Posistion
			(
				i,
				SSI_OccupationRequire
			)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, SSI_PlayerPointsRequire)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iPlayerPointsRequire
		);

		g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iParentSkillID = ThirdFile.Search_Posistion
			(
				i,
				SSI_ParentSkillID
			)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, SSI_ParentSkillLevelRequire)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iParentSkillLevelRequire
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendPoints)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendPoints
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendMoney)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendMoney
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendExp)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendExp
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem1ID)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem1ID
		);
		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem1Num)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem1Num
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem2ID)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem2ID
		);
		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem2Num)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem2Num
		);

		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem3ID)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem3ID
		);
		pSplitString = ThirdFile.Search_Posistion(i, SSI_SpendItem3Num)->pString;
		ReadSkillLearn
		(
			&oSplitL1,
			pSplitString,
			g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_iSpendItem3Num
		);

		g_SkillStudyCondition.m_aSkillStydy_Condition[iIndex].m_bSkillIsMutex = ThirdFile.Search_Posistion
			(
			i,
			SSI_SkillIsMutex
			)->iValue;
	}
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Skill::LoadSkillTemplateDataMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_SpellTemplateDataMgr.InitFromDB(FILE_SKILL_TEMPLATE))
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
BOOL TableInit_Map_Skill::LoadSkillDataMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_SpellDataMgr.InitFromDB(FILE_SKILL_TEMPLATE))
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
BOOL TableInit_Map_Skill::LoadImpactSEDataMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_EffectSEDataMgr.InitFromDB(FILE_IMPACT_SEDATA))
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
BOOL TableInit_Map_Skill::LoadStandardImpactMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_STDEffectMgr.InitFromDB(FILE_STANDARD_IMPACT_DATA))
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
void TableInit_Map_Skill::LoadImpactDirTable()
{
	__GUARD__ if(TRUE == g_ImpactDirDataMgr.InitFromDB(FILE_IMPACT_DIR))
	{
	}
	else
	{
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Skill::ReloadCombatTables(void)
{
	/*~~~~~~~~~*/
	BOOL	bRet;
	/*~~~~~~~~~*/

	TableInit_Map_Misc TableMisc;
	bRet = LoadCampAndStandDataMgr();
	KCheck(bRet);
	bRet = LoadSkillTemplateDataMgr();
	KCheck(bRet);
	bRet = LoadSkillDataMgr();
	KCheck(bRet);
	bRet = LoadImpactSEDataMgr();
	KCheck(bRet);
	bRet = TableMisc.LoadSpecialObjDataMgr();
	KCheck(bRet);
	bRet = TableMisc.LoadIdCollectionMgr();
	KCheck(bRet);
	bRet = LoadStandardImpactMgr();
	KCheck(bRet);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Skill::LoadCampAndStandDataMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == g_CampDataMgr.InitFromDB(FILE_CAMP_AND_STAND))
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
void TableInit_Map_Skill::ReadSkillLearn(SplitStringLevelOne *pSplitL1, const char *pSplitString, int32 *pArry)
{
	pSplitL1->Reset();
	pSplitL1->Init('|', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCount = pSplitL1->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(Skill_Study_Condition::MAX_SKILL_LEVEL >= iCount);
	if(Skill_Study_Condition::MAX_SKILL_LEVEL < iCount)
	{
		return;
	}

	for(int32 j = 0; j < iCount; ++j)
	{
		pArry[j] = atoi(pSplitL1->GetResultLine(j));
	}

	if(iCount < Skill_Study_Condition::MAX_SKILL_LEVEL)
	{
		for(int32 i = iCount; i < Skill_Study_Condition::MAX_SKILL_LEVEL; ++i)
		{
			pArry[i] = pArry[0];
		}
	}
}

void TableInit_Map_Skill::ReadSplitStringToTable(SplitStringLevelOne *pSplitL1, const char *pSplitString, int32 *pArry)
{
	pSplitL1->Reset();
	pSplitL1->Init('|', NULL);
	pSplitL1->DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL1->GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MAX_GIFT_BALANCE_LEVEL >= iLineCount && "天赋平衡级别超过最大限度");
	if(MAX_GIFT_BALANCE_LEVEL < iLineCount)
	{
		iLineCount = MAX_GIFT_BALANCE_LEVEL;
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
void TableInit_Map_Skill::Init_GiftBalanceInfoTable()
{
	__GUARD__

	enum GiftBalance
	{
		ID			= 0,
		LOGIC_ID,
		MAX_LEVEL,
		GIFT_LEVEL,
		ITEM,
		ITEM_COUNT,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GIFT_BALANCE_INFO_1);
	KCheckEx(ret, FILE_GIFT_BALANCE_INFO_1);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GIFT_BALANCE_COUNT);
	g_GiftBalanceInfoTbl.SetSize( iTableCount );

	SplitStringLevelOne	oSplitL1;
	const char		*pSplitString = NULL;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GiftBalanceInfoTbl.GetData(i)->m_nID = ThirdFile.Search_Posistion(i, ID)->iValue;
		g_GiftBalanceInfoTbl.GetData(i)->m_nLogicID = ThirdFile.Search_Posistion(i, LOGIC_ID)->iValue;
		g_GiftBalanceInfoTbl.GetData(i)->m_nMaxLevel = ThirdFile.Search_Posistion(i, MAX_LEVEL)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, GIFT_LEVEL)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GiftBalanceInfoTbl.GetData(i)->m_aInherenceLevel);

		pSplitString = ThirdFile.Search_Posistion(i, ITEM)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GiftBalanceInfoTbl.GetData(i)->m_aItemID);

		pSplitString = ThirdFile.Search_Posistion(i, ITEM_COUNT)->pString;
		ReadSplitStringToTable(&oSplitL1, pSplitString, g_GiftBalanceInfoTbl.GetData(i)->m_aItemCount);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Skill::Init_GiftBalanceInfoTable_Ctrl()
{
	__GUARD__

	enum GiftBalance
	{
		INHERNCE_LEVEL			= 0,
		LOGIC_ID_CTRLHIT,
		MAX_LEVEL_CTRLHIT,
		ITEM_CTRLHIT,
		ITEM_COUNT_CTRLHIT,
		LOGIC_ID_CTRLMISS      = 9,
		MAX_LEVEL_CTRLMISS,
		ITEM_CTRLMISS,
		ITEM_COUNT_CTRLMISS,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GIFT_BALANCE_INFO_2);
	KCheckEx(ret, FILE_GIFT_BALANCE_INFO_2);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GIFT_BALANCE_COUNT_CTRL);
	g_GiftBalanceInfoTbl_Ctrl.SetSize( iTableCount );

	SplitStringLevelOne	oSplitL1;
	const char		*pSplitString = NULL;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nInherenceLevel = ThirdFile.Search_Posistion(i, INHERNCE_LEVEL)->iValue;

		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nLogicID_CtrlHit = ThirdFile.Search_Posistion(i, LOGIC_ID_CTRLHIT)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nMaxLevel_CtrlHit = ThirdFile.Search_Posistion(i, MAX_LEVEL_CTRLHIT)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nItemID_CtrlHit = ThirdFile.Search_Posistion(i, ITEM_CTRLHIT)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nItemCount_CtrlHit = ThirdFile.Search_Posistion(i, ITEM_COUNT_CTRLHIT)->iValue;

		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nLogicID_CtrlMiss = ThirdFile.Search_Posistion(i, LOGIC_ID_CTRLMISS)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nMaxLevel_CtrlMiss = ThirdFile.Search_Posistion(i, MAX_LEVEL_CTRLMISS)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nItemID_CtrlMiss = ThirdFile.Search_Posistion(i, ITEM_CTRLMISS)->iValue;
		g_GiftBalanceInfoTbl_Ctrl.GetData(i)->m_nItemCount_CtrlMiss = ThirdFile.Search_Posistion(i, ITEM_COUNT_CTRLMISS)->iValue;
	}

	__UNGUARD__
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Skill::Init_GiftZhuanGongInfoTable()
{
	__GUARD__

	enum GiftZhuanGong
	{
		LEVEL			= 0,
		EXP,
		EFFECT,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GIFT_ZHUANGONG);
	KCheckEx(ret, FILE_GIFT_ZHUANGONG);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GIFT_ZHANJING_COUNT);
	g_GiftZhuanGongInfoTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GiftZhuanGongInfoTbl.GetData(i)->m_nLevel = ThirdFile.Search_Posistion(i, LEVEL)->iValue;
		g_GiftZhuanGongInfoTbl.GetData(i)->m_nExp = ThirdFile.Search_Posistion(i, EXP)->iValue;
		g_GiftZhuanGongInfoTbl.GetData(i)->m_nEffect = ThirdFile.Search_Posistion(i, EFFECT)->iValue;
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Skill::Init_GiftZhuanFangInfoTable()
{
	__GUARD__

	enum GiftZhuanFang
	{
		LEVEL			= 0,
		EXP,
		EFFECT,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GIFT_ZHUANFANG);
	KCheckEx(ret, FILE_GIFT_ZHUANFANG);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	KCheck(iTableCount < MAX_GIFT_ZHANJING_COUNT);
	g_GiftZhuanFangInfoTbl.SetSize( iTableCount );

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_GiftZhuanFangInfoTbl.GetData(i)->m_nLevel = ThirdFile.Search_Posistion(i, LEVEL)->iValue;
		g_GiftZhuanFangInfoTbl.GetData(i)->m_nExp = ThirdFile.Search_Posistion(i, EXP)->iValue;
		g_GiftZhuanFangInfoTbl.GetData(i)->m_nEffect = ThirdFile.Search_Posistion(i, EFFECT)->iValue;
	}

	__UNGUARD__
}