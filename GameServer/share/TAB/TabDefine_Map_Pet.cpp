#include "stdafx.h"
#include "BaseTool.h"
#include "BaseTool.h"
#include "ScriptCacheMgr.h"

#include "TAB.h"
#include "FileDef.h"
#include "Behavior_State.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "ShopManager.h"
#include "Item_Helper.h"
#include "Behavior_Template.h"
#include "TabDefine_Map_Pet.h"
#include "TabDefine_Map_Quest.h"

using namespace			TAB;

_PET_PROPERTY_TBL					g_HorsePropertyTab;
SHorseLevelupTab				g_HorseLevelUpTab;
SHorseDomesticationMoneyTab	g_HorseDomesticationMoneyTab;
SHorseSkillDistrTab				g_HorseSpellDistrTab[PET_MAX_NUM];
SHorseSkillIndexTab				g_HorseSpellIndexTab[PET_SKILL_NUM];
SHorseStudySkillTab				g_HorseStudySpellTab;
_PET_APPERCEIVESPELL_TAB		g_HorseApperceiveSpellTab[PET_APPERCEIVESKILLRATE_NUM];
float							g_HorseAIStrategyTab[PET_SKILL_TYPE][PET_AITYPE];
_HORSE_ATTR_TBL					g_HorseAttrTbl;
_HORSE_MIX_TBL					g_HorseMixTbl;
_HORSE_MIX_SPELL_TBL			g_HorseMixSpellTbl;
_HORSE_SKILL_TBL				g_HorseSkillTbl;
_HORSE_ITEM_TBL					g_HorseItemTbl;
_HORSE_DROP_TBL					g_HorseDrop;
_HORSE_PER_LIMIT_TBL			g_HorsePerLimit;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Map_Pet::TableInit_Map_Pet()
{}

TableInit_Map_Pet::~TableInit_Map_Pet()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Pet::Init()
{
	__GUARD__

	LoadPetAttrTable();
	LoadPetLevelUpTable();
	LoadPetDomesticationMoney();
	LoadPetSkillDistributeTable();
	LoadPetSkillIndexTable();
	LoadPetStudySkillTable();
	LoadPetApperceiveSkillTable();
	LoadPetAIStrategyTable();
	LoadHorseAttrTable();
	LoadHorseMixTable();
	LoadHorseMixSpellTable();
	LoadHorseRealTable();
	LoadHorseItemTable();
	LoadHorseDropTable();
	LoadHorsePerLimitTable();


	return TRUE;
	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareOfHorseItemTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ uint32	Serial1, Serial2;

	Serial1 = ((_HORSE_ITEM *) pArg1)->m_iItemID;
	Serial2 = ((_HORSE_ITEM *) pArg2)->m_iItemID;

	if(Serial1 > Serial2)
		return 1;
	else if(Serial1 < Serial2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}


_HORSE_ITEM *_HORSE_ITEM_TBL::GetHorseItemAttr(int32 iHorseItemID)
{
	__GUARD__ 
	
	_HORSE_ITEM	tb;
	tb.m_iItemID = iHorseItemID;

	_HORSE_ITEM	*pResult = (_HORSE_ITEM *) bsearch
		(
			&tb,
			g_HorseItemTbl.m_aHorseItem,
			g_HorseItemTbl.m_iCount,
			sizeof(_HORSE_ITEM),
			(int32(*) (const void *, const void *)) CompareOfHorseItemTB
		);

	if(pResult)
	{
		return pResult;
	}
	else
	{
		return NULL;
	}

	__UNGUARD__ 
	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::ReadHorseSkillSlot
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	_HORSE_SKILL_SLOT	&oSlot
)
{
	__GUARD__ pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(MaxSlotSkillNum >= iLineCount);
	oSlot.m_iSkillCount = iLineCount;
	for(int32 iSkill = 0; iSkill < iLineCount; ++iSkill)
	{
		oSlot.m_aSkillSlot[iSkill] = atoi(pSplitL2->GetResultLine(iSkill));
	}

	__UNGUARD__
}





/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetAttrTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum PetAttrData
	{
		PetID					= 0,
		PetTakeLevel,
		PetName,
		PetCamp,
		IsVarPet,
		IsBabyPet,
		PetFoodType,
		PetSkillCount,
		VoluntarySkill,
		PassiveSkill1,
		PassiveSkill2,
		PassiveSkill3,
		PassiveSkill4,
		PetLife,
		PetStrPerception,
		PetConPerception,
		PetDexPerception,
		PetIntPerception,
		PetGrowRate0,
		PetGrowRate1,
		PetGrowRate2,
		PetGrowRate3,
		PetGrowRate4,
		CowardiceRate,
		WarinessRate,
		LoyalismRate,
		CanninessRate,
		ValourRate,
		PetAttrEnd,
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_PET_ATTR);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAXTYPE_NUMBER);
	g_HorsePropertyTab.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~*/
	int32	iValue = 0;
	int32	iType = 0;
	/*~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		iValue = ThirdFile.Search_Posistion(i, PetID)->iValue;
		iType = iValue;

		if(iType >= MAXTYPE_NUMBER)
		{
			KCheckEx(FALSE, "宠物表ID超出范围值");
			continue;
		}

		if(g_HorsePropertyTab.m_MaxType < (uint32) iType) g_HorsePropertyTab.m_MaxType = iType;

		g_HorsePropertyTab.m_TableExt[iType].m_Type = iType;

		strncpy
		(
			g_HorsePropertyTab.m_TableExt[iType].m_Name,
			ThirdFile.Search_Posistion(i, PetName)->pString,
			sizeof(g_HorsePropertyTab.m_TableExt[i].m_Name) - 1
		);

		iValue = ThirdFile.Search_Posistion(i, PetTakeLevel)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_TakeLevel = iValue;

		iValue = ThirdFile.Search_Posistion(i, IsVarPet)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_bVarPet = iValue;

		iValue = ThirdFile.Search_Posistion(i, IsBabyPet)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_bBabyPet = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetFoodType)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_FoodType = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetSkillCount)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_PassiveSkillCount = iValue;

		iValue = ThirdFile.Search_Posistion(i, VoluntarySkill)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_VoluntarySkill = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill1)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_PassiveSkill1 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill2)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_PassiveSkill2 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill3)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_PassiveSkill3 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill4)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_PassiveSkill4 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetStrPerception)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_iStrengthPerception = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetConPerception)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_iSmartnessPerception = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetDexPerception)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_iMindPerception = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetIntPerception)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_iConstitutionPerception = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetGrowRate0)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_GrowRate0 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetGrowRate1)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_GrowRate1 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetGrowRate2)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_GrowRate2 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetGrowRate3)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_GrowRate3 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PetGrowRate4)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_GrowRate4 = iValue;

		iValue = ThirdFile.Search_Posistion(i, CowardiceRate)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_CowardiceRate = iValue;

		iValue = ThirdFile.Search_Posistion(i, WarinessRate)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_WarinessRate = iValue;

		iValue = ThirdFile.Search_Posistion(i, LoyalismRate)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_LoyalismRate = iValue;

		iValue = ThirdFile.Search_Posistion(i, CanninessRate)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_CanninessRate = iValue;

		iValue = ThirdFile.Search_Posistion(i, ValourRate)->iValue;
		g_HorsePropertyTab.m_TableExt[iType].m_ValourRate = iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetLevelUpTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_LEVELUP);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_HorseLevelUpTab.m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~*/
	int32	iLevel = 0;
	int32	iExp = 0;
	/*~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		iLevel = ThirdFile.Search_Posistion(i, 0)->iValue;

		iExp = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_HorseLevelUpTab.m_Table[iLevel] = iExp;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetDomesticationMoney()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_DOMESTICATION_MONEY);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	int32			iLevel = 0;
	float			fDomesticationMoney = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		iLevel = ThirdFile.Search_Posistion(i, 0)->iValue;

		fDomesticationMoney = ThirdFile.Search_Posistion(i, 1)->fValue;
		g_HorseDomesticationMoneyTab.m_Table[iLevel] = fDomesticationMoney;
	}

	__UNGUARD__
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetSkillDistributeTable()
{
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_SKILLDISTRIBUTE);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	int32			iPetID = 0;
	int32			iRange = 0;

	for(int32 i = 0; i < iTableCount; i++)
	{
		iPetID = ThirdFile.Search_Posistion(i, 0)->iValue;
		g_HorseSpellDistrTab[i].m_PetID = iPetID;
		for(int32 j = 2; j < iColumnCount; j++)
		{
			iRange = ThirdFile.Search_Posistion(i, j)->iValue;
			if(iRange > 0)
			{
				for(int32 n = 0; n < PET_MAX_SKILL_COUNT; ++n)
				{
					if(g_HorseSpellDistrTab[i].m_Table[n].m_nSkillIndex == -1)
					{
						g_HorseSpellDistrTab[i].m_Table[n].m_nSkillIndex = j - 2;
						g_HorseSpellDistrTab[i].m_Table[n].m_nSkillRange = iRange;
						break;
					}
				}
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetSkillIndexTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_SKILLINDEXTBL);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	int32			iIndex = 0;
	int32			idSkill = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(g_HorseSpellIndexTab, 0, sizeof(SHorseSkillIndexTab) * PET_SKILL_NUM);

	for(int32 i = 0; i < iTableCount; i++)
	{
		iIndex = ThirdFile.Search_Posistion(i, 0)->iValue;
		idSkill = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_HorseSpellIndexTab[i].m_nIndex = iIndex;
		g_HorseSpellIndexTab[i].m_nSkillID = idSkill;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetStudySkillTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_STUDYSKILLTBL);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	int32			nID;
	int32			nMaxSpaceCount;
	int32			nSpaceCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		KCheck(i < PET_STUDYSKILLRATE_NUM);

		nMaxSpaceCount = ThirdFile.Search_Posistion(i, 2)->iValue;
		nSpaceCount = ThirdFile.Search_Posistion(i, 1)->iValue;
		nID = GEN_HORSE_STUDYSPELL_ID(nMaxSpaceCount, nSpaceCount);

		g_HorseStudySpellTab.m_aStudySkill[nID].m_nID = nID;
		g_HorseStudySpellTab.m_aStudySkill[nID].m_nMaxSpaceCount = nMaxSpaceCount;
		g_HorseStudySpellTab.m_aStudySkill[nID].m_nSpaceCount = nSpaceCount;
		g_HorseStudySpellTab.m_aStudySkill[nID].m_nNewPercent = ThirdFile.Search_Posistion(i, 3)->iValue;;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetApperceiveSkillTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_APPERCEIVESKILLTBL);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(g_HorseApperceiveSpellTab, 0, sizeof(_PET_APPERCEIVESPELL_TAB) * PET_APPERCEIVESKILLRATE_NUM);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		KCheck(i < PET_APPERCEIVESKILLRATE_NUM);

		g_HorseApperceiveSpellTab[i].m_nSkillCount = ThirdFile.Search_Posistion(i, 2)->iValue;
		g_HorseApperceiveSpellTab[i].m_nLearnedVoluntarySkillCount = ThirdFile.Search_Posistion(i, 1)->iValue;
		g_HorseApperceiveSpellTab[i].m_nLearnedPassiveSkillCount = ThirdFile.Search_Posistion(i, 3)->iValue;
		g_HorseApperceiveSpellTab[i].m_nApperceiveVoluntarySkillRate = ThirdFile.Search_Posistion(i, 4)->iValue;
		g_HorseApperceiveSpellTab[i].m_nApperceivePassiveSkillRate = ThirdFile.Search_Posistion(i, 5)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadPetAIStrategyTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { AITypeBegin = 2, };
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_PET_AISTRATEGYTBL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(g_HorseAIStrategyTab, 0, sizeof(float) * PET_AITYPE * PET_SKILL_TYPE);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		KCheck(i < PET_SKILL_TYPE);
		for(int32 j = AITypeBegin; j < iColumnCount; ++j)
		{
			KCheck(j < PET_AITYPE + AITypeBegin);
			g_HorseAIStrategyTab[i][j - AITypeBegin] = ThirdFile.Search_Posistion(i, j)->fValue;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadHorseAttrTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum HorseAttrData
	{
		HorseDataID			= 0,
		HorseLevel,
		HorseCanMating,
		HorseCanCompose,
		HorseName,
		HorseKindType,
		HorseKindName,
		HorseTakeLevel,
		HorseReqInherenceLevel,		// rj 2010-8-23 天赋及个人等级字段索引枚举
		HorseReqPersonLevel,
		HorseIsVariation,
		HorseIsFixedHold,
		HorseCNC,
		HorseReturnToChildRandSum,
		HorseReturnToChildID,
		HorseReturnToChildRandRate,
		HorseChildID,
		HorseGeneration,
		HorseLifeHaveMaster,
		HorseLifeNoMaster,
		HorseStrengthMin,
		HorseStrengthMax,
		HorseSmartnessMin,
		HorseSmartnessMax,
		HorseMindMin,
		HorseMindMax,
		HorseConstitutionMin,
		HorseConstitutionMax,
		HorseStrengthMinPer,
		HorseStrengthMaxPer,
		HorseSmartnessMinPer,
		HorseSmartnessMaxPer,
		HorseMindMinPer,
		HorseMindMaxPer,
		HorseConstitutionMinPer,
		HorseConstitutionMaxPer,
		HorseSavvyMin,
		HorseSavvyMax,
		HorseGenGuMin,
		HorseGenGuMax,
		HorsePullulationRateMin,
		HorsePullulationRateMax,
		HorseMoveSpeed,
		HorseBehaveID,
		HorseMountID,
		HorseInitSkillRandSum,
		HorseInitSkillTbl,
		HorseSkillRealizationID		= HorseInitSkillTbl + 24,
		HorseScriptID,
		HorseDataCount
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_ATTR);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_HORSE_TYPE && "../Server/Config/qichengjichu.tab");
	g_HorseAttrTbl.m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char		*pSplitString = NULL;
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(HorseDataCount == iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = ThirdFile.Search_Posistion(i, HorseDataID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iType >= MAX_HORSE_TYPE)
		{
			KCheckEx(FALSE, "马表中填写的马ID号超出范围");
			continue;
		}

		g_HorseAttrTbl.m_aHorseTbl[iType].m_nDataID = iType;
		strncpy
		(
			g_HorseAttrTbl.m_aHorseTbl[iType].m_sName,
			ThirdFile.Search_Posistion(i, HorseName)->pString,
			sizeof(g_HorseAttrTbl.m_aHorseTbl[iType].m_sName) - 1
		);
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iLevel = ThirdFile.Search_Posistion(i, HorseLevel)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iTakeLevel = ThirdFile.Search_Posistion(i, HorseTakeLevel)->iValue;
		
		// rj 2010-8-23 天赋及个人等级初始化表值
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iReqInherenceLevel = ThirdFile.Search_Posistion(i, HorseReqInherenceLevel)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iReqPersonLevel = ThirdFile.Search_Posistion(i, HorseReqPersonLevel)->iValue;


		g_HorseAttrTbl.m_aHorseTbl[iType].m_iReturnToChildRandSum = ThirdFile.Search_Posistion
			(
				i,
				HorseReturnToChildRandSum
			)->iValue;
		if(g_HorseAttrTbl.m_aHorseTbl[iType].m_iReturnToChildRandSum > 0)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseReturnToChildID)->pString;
			g_HorseAttrTbl.m_aHorseTbl[iType].m_iReturnToChildIDCount = CommonStringSplit
				(
					&oSplitL1,
					&oSplitL2,
					pSplitString,
					MaxReturnToChildIDNum,
					g_HorseAttrTbl.m_aHorseTbl[iType].m_aReturnToChildID
				);

			pSplitString = ThirdFile.Search_Posistion(i, HorseReturnToChildRandRate)->pString;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ratecount = CommonStringSplit
				(
					&oSplitL1,
					&oSplitL2,
					pSplitString,
					MaxReturnToChildIDNum,
					g_HorseAttrTbl.m_aHorseTbl[iType].m_aReturnToChildRandRate
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(g_HorseAttrTbl.m_aHorseTbl[iType].m_iReturnToChildIDCount != ratecount)
			{
				/*~~~~~~~~~~~~~~~~~~~*/
				char	assetmsg[1024];
				/*~~~~~~~~~~~~~~~~~~~*/

				sprintf
				(
					assetmsg,
					"文件%s中ID为%d的骑乘还童概率分子的数量和还童ID的数量不相等",
					FILE_HORSE_ATTR,
					iType
				);
				KCheckEx(FALSE, assetmsg);
			}

			/*~~~~~~~~~~~~~~~~*/
			int32	seedsum = 0;
			/*~~~~~~~~~~~~~~~~*/

			for(int32 tochild = 0; tochild < ratecount; tochild++)
			{
				seedsum += g_HorseAttrTbl.m_aHorseTbl[iType].m_aReturnToChildRandRate[tochild];
			}

			if(seedsum != g_HorseAttrTbl.m_aHorseTbl[iType].m_iReturnToChildRandSum)
			{
				/*~~~~~~~~~~~~~~~~~~~*/
				char	assetmsg[1024];
				/*~~~~~~~~~~~~~~~~~~~*/

				sprintf(assetmsg, "文件%s中还童概率分子的总和不等于还童概率分母", FILE_HORSE_ATTR);
				KCheckEx(FALSE, assetmsg);
			}
		}

		pSplitString = ThirdFile.Search_Posistion(i, HorseChildID)->pString;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iChildIDCount = CommonStringSplit
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				MaxReturnToChildIDNum,
				g_HorseAttrTbl.m_aHorseTbl[iType].m_aChildID
			);

		g_HorseAttrTbl.m_aHorseTbl[iType].m_bCanMating = ThirdFile.Search_Posistion(i, HorseCanMating)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_bCanCompose = ThirdFile.Search_Posistion(i, HorseCanCompose)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_bVariation = ThirdFile.Search_Posistion
			(
				i,
				HorseIsVariation
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_byGeneration = ThirdFile.Search_Posistion
			(
				i,
				HorseGeneration
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iLifeHaveMaster = ThirdFile.Search_Posistion
			(
				i,
				HorseLifeHaveMaster
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_LifeNoMaster = ThirdFile.Search_Posistion
			(
				i,
				HorseLifeNoMaster
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iStrengthMin = ThirdFile.Search_Posistion
			(
				i,
				HorseStrengthMin
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iStrengthMax = ThirdFile.Search_Posistion
			(
				i,
				HorseStrengthMax
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSmartnessMin = ThirdFile.Search_Posistion
			(
				i,
				HorseSmartnessMin
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSmartnessMax = ThirdFile.Search_Posistion
			(
				i,
				HorseSmartnessMax
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMindMin = ThirdFile.Search_Posistion(i, HorseMindMin)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMindMax = ThirdFile.Search_Posistion(i, HorseMindMax)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iConstitutionMin = ThirdFile.Search_Posistion
			(
				i,
				HorseConstitutionMin
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iConstitutionMax = ThirdFile.Search_Posistion
			(
				i,
				HorseConstitutionMax
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iStrengthMinPer = ThirdFile.Search_Posistion
			(
				i,
				HorseStrengthMinPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iStrengthMaxPer = ThirdFile.Search_Posistion
			(
				i,
				HorseStrengthMaxPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSmartnessMinPer = ThirdFile.Search_Posistion
			(
				i,
				HorseSmartnessMinPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSmartnessMaxPer = ThirdFile.Search_Posistion
			(
				i,
				HorseSmartnessMaxPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMindMinPer = ThirdFile.Search_Posistion
			(
				i,
				HorseMindMinPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMindMaxPer = ThirdFile.Search_Posistion
			(
				i,
				HorseMindMaxPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iConstitutionMinPer = ThirdFile.Search_Posistion
			(
				i,
				HorseConstitutionMinPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iConstitutionMaxPer = ThirdFile.Search_Posistion
			(
				i,
				HorseConstitutionMaxPer
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSavvyMin = ThirdFile.Search_Posistion(i, HorseSavvyMin)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iSavvyMax = ThirdFile.Search_Posistion(i, HorseSavvyMax)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_GenGuMin = ThirdFile.Search_Posistion(i, HorseGenGuMin)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_GenGuMax = ThirdFile.Search_Posistion(i, HorseGenGuMax)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iPullulationRateMin = ThirdFile.Search_Posistion
			(
				i,
				HorsePullulationRateMin
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iPullulationRateMax = ThirdFile.Search_Posistion
			(
				i,
				HorsePullulationRateMax
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMoveSpeed = ThirdFile.Search_Posistion(i, HorseMoveSpeed)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iBehaveID = ThirdFile.Search_Posistion(i, HorseBehaveID)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iMountID = ThirdFile.Search_Posistion(i, HorseMountID)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iInitSkillRandSum = ThirdFile.Search_Posistion
			(
				i,
				HorseInitSkillRandSum
			)->iValue;
		for(int32 iSlot = 0; iSlot < PET_MAX_SKILL_COUNT; ++iSlot)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseInitSkillTbl + iSlot * 2)->pString;
			ReadHorseSkillSlot
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_HorseAttrTbl.m_aHorseTbl[iType].m_oSkillSlot[iSlot]
			);

			pSplitString = ThirdFile.Search_Posistion(i, HorseInitSkillTbl + iSlot * 2 + 1)->pString;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ratecount = CommonStringSplit
				(
					&oSplitL1,
					&oSplitL2,
					pSplitString,
					MaxSlotSkillNum,
					g_HorseAttrTbl.m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_aSkillRandRate
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(ratecount != g_HorseAttrTbl.m_aHorseTbl[iType].m_oSkillSlot[iSlot].m_iSkillCount)
			{
				/*~~~~~~~~~~~~~~~~~~~~*/
				char	assertmsg[1024];
				/*~~~~~~~~~~~~~~~~~~~~*/

				sprintf
				(
					assertmsg,
					"文件%s中骑乘%d的技能%d的概率数量与可选技能数量不相等",
					FILE_HORSE_ATTR,
					iType,
					iSlot
				);
				KCheckEx(NULL, assertmsg);
			}
			else
			{
				g_HorseAttrTbl.m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_iSkillCount = ratecount;
			}

			/*~~~~~~~~~~~~~~~~*/
			int32	ratesum = 0;
			/*~~~~~~~~~~~~~~~~*/

			for(int32 i = 0; i < ratecount; i++)
			{
				ratesum += g_HorseAttrTbl.m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_aSkillRandRate[i];
			}

			if(ratesum > g_HorseAttrTbl.m_aHorseTbl[iType].m_iInitSkillRandSum)
			{
				/*~~~~~~~~~~~~~~~~~~~~*/
				char	assertmsg[1024];
				/*~~~~~~~~~~~~~~~~~~~~*/

				sprintf
				(
					assertmsg,
					"文件%s中骑乘%d的技能%d的概率总和超过了概率分母",
					FILE_HORSE_ATTR,
					iType,
					iSlot
				);
				KCheckEx(NULL, assertmsg);
			}
		}

		g_HorseAttrTbl.m_aHorseTbl[iType].m_iRealizationID = ThirdFile.Search_Posistion
			(
				i,
				HorseSkillRealizationID
			)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iScriptID = ThirdFile.Search_Posistion(i, HorseScriptID)->iValue;
		KCheck(g_HorseAttrTbl.m_aHorseTbl[iType].m_iScriptID <= 0 || g_HorseAttrTbl.m_aHorseTbl[iType].m_iScriptID >= 100000);
		g_HorseAttrTbl.m_aHorseTbl[iType].m_iKindType = ThirdFile.Search_Posistion(i, HorseKindType)->iValue;
		g_HorseAttrTbl.m_aHorseTbl[iType].m_bIsFixedHold = ThirdFile.Search_Posistion
			(
				i,
				HorseIsFixedHold
			)->iValue;
	}

	__UNGUARD__
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Pet::LoadHorseMixTable()
{
	__GUARD__ enum HorseMixData
	{
		HorseDataID			= 0,
		HorseMixOdds,
		HorseMixdeno,
		RemainValue1,
		RemainValue2,
		HorseMixDataCount
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_MIX);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_HORSE_TYPE && "../Server/Config/qichengmix.tab");
	g_HorseMixTbl.m_iCount = iTableCount;
	KCheck(HorseMixDataCount == iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = ThirdFile.Search_Posistion(i, HorseDataID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iType >= MAX_HORSE_TYPE)
		{
			KCheckEx(FALSE, "马表中填写的马ID号超出范围");
			continue;
		}

		g_HorseMixTbl.m_aHorseTbl[i].m_nDataID = iType;
		g_HorseMixTbl.m_aHorseTbl[i].m_nMixOdds = ThirdFile.Search_Posistion(i, HorseMixOdds)->iValue;
		g_HorseMixTbl.m_aHorseTbl[i].m_nMixdeno = ThirdFile.Search_Posistion(i, HorseMixdeno)->iValue;
		g_HorseMixTbl.m_aHorseTbl[i].m_nRemainValue1 = ThirdFile.Search_Posistion(i, RemainValue1)->iValue;
		g_HorseMixTbl.m_aHorseTbl[i].m_nRemainValue2 = ThirdFile.Search_Posistion(i, RemainValue2)->iValue;

	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__UNGUARD__
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void TableInit_Map_Pet::LoadHorseMixSpellTable()
{
	__GUARD__ enum HorseMixSpellData
	{
		HorseSpellTotal			= 0,
		HorseSpell0,
		HorseSpell1,
		HorseSpell2,
		HorseSpell3,
		HorseSpell4,
		HorseSpell5,
		HorseSpell6,
		HorseMixSpellDataCount
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_MIX_SPELL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && "../Server/Config/qichengmixspell.tab");
	g_HorseMixSpellTbl.m_iCount = iTableCount;
	KCheck(HorseMixSpellDataCount == iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpellTotal = ThirdFile.Search_Posistion(i, HorseSpellTotal)->iValue;
		//KCheck(i == g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpellTotal);
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell0 = ThirdFile.Search_Posistion(i, HorseSpell0)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell1 = ThirdFile.Search_Posistion(i, HorseSpell1)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell2 = ThirdFile.Search_Posistion(i, HorseSpell2)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell3 = ThirdFile.Search_Posistion(i, HorseSpell3)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell4 = ThirdFile.Search_Posistion(i, HorseSpell4)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell5 = ThirdFile.Search_Posistion(i, HorseSpell5)->iValue;
		g_HorseMixSpellTbl.m_aHorseTbl[i].m_nHorseSpell6 = ThirdFile.Search_Posistion(i, HorseSpell6)->iValue;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__UNGUARD__
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadHorseRealTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum HorseSkillRealData { HorseRealDataID = 0, HorseDataCount, HorseSkillSlot, HorseSkillDataCount = 8 };
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_SKILL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_HORSE_SKILL_REALIZATION && "../Server/Config/qichengskill.tab");
	g_HorseSkillTbl.m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char	*pSplitString = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(HorseSkillDataCount == iColumnCount);

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = ThirdFile.Search_Posistion(i, HorseRealDataID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iType >= MAX_HORSE_SKILL_REALIZATION)
		{
			KCheckEx(FALSE, "马技能表中填写的ID号超出范围");
			continue;
		}

		g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_iSkillRealizationID = iType;
		g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount = ThirdFile.Search_Posistion
			(
				i,
				HorseDataCount
			)->iValue;
		KCheck
		(
			g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount <= MaxSlotNum
			&&	"马技能槽数量超出限制"
		);
		if(g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount > MaxSlotNum)
			g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount = MaxSlotNum;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 iSlot = 0; iSlot < PET_MAX_APPER_COUNT; ++iSlot)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseSkillSlot + iSlot)->pString;
			ReadHorseSkillSlot
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				g_HorseSkillTbl.m_aHorseSkillRealizationTbl[iType].m_oSkillSlot[iSlot]
			);
		}
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadHorseItemTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum HorseItemData
	{
		HorseItemID			= 0,
		HorseItemType			= 2,
		HorseAttrChangePercent,
		HorseAttrChangePoint,
		HorseStudySkillID,
		HorseSuccessRate,
		HorseUseLevel,
		HorseTakeLevel,
		HorseOnlyAberrance,
		HorseItemDataCount
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_ITEM);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_HORSE_ITEM && "../Public/Config/qichengdaoju.tab");
	g_HorseItemTbl.m_iCount = iTableCount;

	KCheck(HorseItemDataCount == iColumnCount && "../Public/Config/qichengdaoju.tab列数改变");

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_HorseItemTbl.m_aHorseItem[i].m_iItemID = ThirdFile.Search_Posistion(i, HorseItemID)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_iItemType = ThirdFile.Search_Posistion(i, HorseItemType)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_iAttrChangePercent = ThirdFile.Search_Posistion
			(
				i,
				HorseAttrChangePercent
			)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_iAttrChangePoint = ThirdFile.Search_Posistion
			(
				i,
				HorseAttrChangePoint
			)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_iStudySkillID = ThirdFile.Search_Posistion
			(
				i,
				HorseStudySkillID
			)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_iSuccessRate = ThirdFile.Search_Posistion(i, HorseSuccessRate)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_nUseLevel = ThirdFile.Search_Posistion(i, HorseUseLevel)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_nTakeLevel = ThirdFile.Search_Posistion(i, HorseTakeLevel)->iValue;
		g_HorseItemTbl.m_aHorseItem[i].m_nOnlyAberrance = ThirdFile.Search_Posistion(i, HorseOnlyAberrance)->iValue;

	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadHorseDropTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum HorseDropData
	{
		HorseDropID			= 0,
		HorseMonsterImportance,
		HorseMaxDropNum,
		HorseDropGroup,
		HorseDropDataCount		= HorseDropGroup + 3 * MaxHorseDropGroupNum
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_DROP);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAX_HORSE_DROP && "qichengdrop_content.tab");
	g_HorseDrop.m_iCount = iTableCount;

	KCheck(HorseDropDataCount == iColumnCount && "../Public/Config/qichengdrop_content.tab列数改变");

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char		*pSplitString = NULL;
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iIndex = ThirdFile.Search_Posistion(i, HorseDropID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_HorseDrop.m_aHorse_drop[iIndex].m_iDropID = iIndex;
		g_HorseDrop.m_aHorse_drop[iIndex].m_iMonsterImportance = ThirdFile.Search_Posistion
			(
				i,
				HorseMonsterImportance
			)->iValue;
		g_HorseDrop.m_aHorse_drop[iIndex].m_iMaxDropNum = ThirdFile.Search_Posistion
			(
				i,
				HorseMaxDropNum
			)->iValue;
		for(int32 iGroup = 0; iGroup < MaxHorseDropGroupNum; ++iGroup)
		{
			g_HorseDrop.m_aHorse_drop[iIndex].m_aDropGroup[iGroup].m_iGroupImportance = ThirdFile.Search_Posistion(i, HorseDropGroup + iGroup * 3)->iValue;
			g_HorseDrop.m_aHorse_drop[iIndex].m_aDropGroup[iGroup].m_iGroupMaxDropTimes = ThirdFile.Search_Posistion(i, HorseDropGroup + iGroup * 3 + 1)->iValue;
			pSplitString = ThirdFile.Search_Posistion(i, HorseDropGroup + iGroup * 3 + 2)->pString;
			g_HorseDrop.m_aHorse_drop[iIndex].m_aDropGroup[iGroup].m_iHorseIDCount = CommonStringSplit
				(
					&oSplitL1,
					&oSplitL2,
					pSplitString,
					MaxReturnToChildIDNum,
					g_HorseDrop.m_aHorse_drop[iIndex].m_aDropGroup[iGroup].m_aGroupHorseID
				);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Pet::LoadHorsePerLimitTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_HORSE_ZIZHI);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount <= MAX_HORSE_GENRATION && "FILE_HORSE_ZIZHI");
	g_HorsePerLimit.m_iCount = iTableCount;

	for(int32 i = 0; i < iTableCount; ++i)
	{
		g_HorsePerLimit.m_aLimit[i] = ThirdFile.Search_Posistion(i, 0)->iValue;
	}

	__UNGUARD__
}