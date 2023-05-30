#ifndef __TAB_DEFINE_MAP_SKILL_H__
#define __TAB_DEFINE_MAP_SKILL_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "SpellDataLoader.h"
#include "TabTemplateLoader.h"
#include "TabStruct.h"


// 技能表
class TableInit_Map_Skill
{
public:
	TableInit_Map_Skill();
	~TableInit_Map_Skill();

	BOOL	Init();

	BOOL	ReloadCombatTables();

private:
	// 加载技能学习表
	void	LoadSKillStudyTable();
	// 加载技能模板数据
	BOOL	LoadSkillTemplateDataMgr();
	// 加载技能数据
	BOOL	LoadSkillDataMgr();
	// 加载buff描述表
	BOOL	LoadImpactSEDataMgr();
	// 加载buff逻辑表
	BOOL	LoadStandardImpactMgr();
	// 加载buff影响表
	void	LoadImpactDirTable();
	// 加载阵营表
	BOOL	LoadCampAndStandDataMgr();
	// 加载天赋平衡表 控制除外
	void	Init_GiftBalanceInfoTable();
	// 加载天赋平衡表 控制
	void	Init_GiftBalanceInfoTable_Ctrl();
	// 加载天赋专攻表
	void	Init_GiftZhuanGongInfoTable();
	// 加载天赋专防表
	void	Init_GiftZhuanFangInfoTable();


private:
	void	ReadSkillLearn(SplitStringLevelOne *pSplitL1, const char *pSplitString, int32 *pArry);
	void	ReadSplitStringToTable(SplitStringLevelOne *pSplitL1, const char *pSplitString, int32 *pArry);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct Skill_Study_Condition
{
	enum { MAX_SKILL_LEVEL = MAX_SKIL_LEVEL_LIMIT };
	int32 m_iID;
	int32 m_iPLayerLevelRequire[MAX_SKILL_LEVEL];
	int32 m_iOccupationRequire;
	int32 m_iPlayerPointsRequire[MAX_SKILL_LEVEL];
	int32 m_iParentSkillID;
	int32 m_iParentSkillLevelRequire[MAX_SKILL_LEVEL];
	int32 m_iSpendPoints[MAX_SKILL_LEVEL];
	int32 m_iSpendMoney[MAX_SKILL_LEVEL];
	int32 m_iSpendExp[MAX_SKILL_LEVEL];
	int32 m_iSpendItem1ID[MAX_SKILL_LEVEL];
	int32 m_iSpendItem2ID[MAX_SKILL_LEVEL];
	int32 m_iSpendItem3ID[MAX_SKILL_LEVEL];
	int32 m_iSpendItem1Num[MAX_SKILL_LEVEL];
	int32 m_iSpendItem2Num[MAX_SKILL_LEVEL];
	int32 m_iSpendItem3Num[MAX_SKILL_LEVEL];
	BOOL  m_bSkillIsMutex;

	Skill_Study_Condition()
	{
		memset(this, 0, sizeof(Skill_Study_Condition));
		m_iID = INVALID_ID;
	}
};

struct Skill_Study_Condition_TABLE
{
	enum { MAX_Skill_COUNT = SpellTemplateData::MAX_ID };
	Skill_Study_Condition m_aSkillStydy_Condition[MAX_Skill_COUNT];
	int32 m_iCount;
	Skill_Study_Condition_TABLE()
	{
		m_iCount = 0;
	}
};
extern Skill_Study_Condition_TABLE	g_SkillStudyCondition;

/*
===============================================================================================================
天赋平衡表
===============================================================================================================
*/
struct GIFT_BALANCE_INFO_1
{
	int32 m_nID;
	int32 m_nLogicID;
	int32 m_nMaxLevel;
    int32 m_aInherenceLevel[MAX_GIFT_BALANCE_LEVEL];
	int32 m_aItemID[MAX_GIFT_BALANCE_LEVEL];
	int32 m_aItemCount[MAX_GIFT_BALANCE_LEVEL];


	GIFT_BALANCE_INFO_1()
	{
		m_nID = INVALID_ID;
		m_nLogicID = INVALID_ID;
		m_nMaxLevel = 0;
		memset(m_aInherenceLevel, 0 ,sizeof(m_aInherenceLevel));
		memset(m_aItemID, 0 ,sizeof(m_aItemID));
		memset(m_aItemCount, 0 ,sizeof(m_aItemCount));
	}
};

typedef TabTemplate<GIFT_BALANCE_INFO_1,MAX_GIFT_BALANCE_COUNT>		_GIFT_BALANCE_INFO_TBL_1;
extern _GIFT_BALANCE_INFO_TBL_1	g_GiftBalanceInfoTbl;

/*
===============================================================================================================
天赋平衡表
===============================================================================================================
*/
struct GIFT_BALANCE_INFO_2
{
	int32 m_nInherenceLevel;
	int32 m_nLogicID_CtrlHit;
	int32 m_nMaxLevel_CtrlHit;
	int32 m_nItemID_CtrlHit;
	int32 m_nItemCount_CtrlHit;
	int32 m_nLogicID_CtrlMiss;
	int32 m_nMaxLevel_CtrlMiss;
	int32 m_nItemID_CtrlMiss;
	int32 m_nItemCount_CtrlMiss;


	GIFT_BALANCE_INFO_2()
	{
		m_nInherenceLevel = INVALID_ID;
		m_nLogicID_CtrlHit = INVALID_ID;
		m_nMaxLevel_CtrlHit = 0;
		m_nItemID_CtrlHit = INVALID_ID;
		m_nItemCount_CtrlHit = 0;
		m_nLogicID_CtrlMiss = INVALID_ID;
		m_nMaxLevel_CtrlMiss = 0;
		m_nItemID_CtrlMiss = INVALID_ID;
		m_nItemCount_CtrlMiss = 0;
	}
};

typedef TabTemplate<GIFT_BALANCE_INFO_2,MAX_GIFT_BALANCE_COUNT_CTRL>		_GIFT_BALANCE_INFO_TBL_2;
extern _GIFT_BALANCE_INFO_TBL_2	g_GiftBalanceInfoTbl_Ctrl;

/*
===============================================================================================================
天赋专攻表
===============================================================================================================
*/
struct GIFT_ZHUANGONG
{
	int32 m_nLevel;
	int32 m_nExp;
	int32 m_nEffect;

	GIFT_ZHUANGONG()
	{
		m_nLevel = 0;
		m_nExp = 0;
		m_nEffect = 0;
	}
};

typedef TabTemplate<GIFT_ZHUANGONG,MAX_GIFT_ZHANJING_COUNT>		_GIFT_ZHUANGONG;
extern _GIFT_ZHUANGONG	g_GiftZhuanGongInfoTbl;

/*
===============================================================================================================
天赋专防表
===============================================================================================================
*/
struct GIFT_ZHUANFANG
{
	int32 m_nLevel;
	int32 m_nExp;
	int32 m_nEffect;

	GIFT_ZHUANFANG()
	{
		m_nLevel = 0;
		m_nExp = 0;
		m_nEffect = 0;
	}
};

typedef TabTemplate<GIFT_ZHUANFANG,MAX_GIFT_ZHANJING_COUNT>		_GIFT_ZHUANFANG;
extern _GIFT_ZHUANFANG	g_GiftZhuanFangInfoTbl;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<SpellTemplateData> SpellTemplateDataMgr;
extern SpellTemplateDataMgr g_SpellTemplateDataMgr;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<SpellInstanceData> SkillDataMgr_T;
extern SkillDataMgr_T g_SpellDataMgr;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<ImpactSEData_T> ImpactSEDataMgr_T;
extern ImpactSEDataMgr_T g_EffectSEDataMgr;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<EffectData> ImpactDataMgr_T;
extern ImpactDataMgr_T g_STDEffectMgr;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<ImpactDirData_T> ImpactDirDataMgr_T;
extern ImpactDirDataMgr_T g_ImpactDirDataMgr;

#endif