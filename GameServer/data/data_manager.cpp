#include "stdafx.h"
#include "data_manager.h"
#include "platform_file_system.h"
#include "Share/TAB/TabStruct.h"
#include "Share/TAB/TabDefine_Map_Quest.h"
#include "Share/TAB/TabDefine_Map_Misc.h"
#include "Share/TAB/TabDefine_Map_Pet.h"
#include "Share/TAB/TabDefine_Map_Monster.h"
#include "FileDef.h"
#include "BaseTool.h"
#include "SpellDataLoader.h"
#include "SplitStringLevelTwo.h"

template<>
DataManager* GameSingleton<DataManager>::m_sSingleton = NULL;

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

bool DataManager::initialize()
{
	loadMonsterData();
	loadMonsterSkillTable();
	loadQuestList();
	loadFlagMDClientFilter();
	loadNpcQuest();
	loadMonsterAIData();
	loadSpellTemplate();
	loadEffectData();
	loadCollectionData();
	loadProfessionProperty();
	loadPropertyLevelUp();
	loadBeastTable();
	loadHorseAttrTable();
	loadHorseSkillTable();
	loadHorseLevelupTable();
	loadHorsePerlimitTable();
	loadGatherPointTable();
	LoadCampAndStandDataMgr();
	return true;
}

bool DataManager::loadMonsterData()
{
	std::string dir = CPlatformFileSystem::GetInstance()->GetProcessDirectory();

	std::string monster_filename = dir + "\\..\\..\\server_resources\\public\\config\\mon_attr_ex.tab";

		enum MonsterAttrData
	{
		MonsterType = 0,
		MonsterCannotFight,
		MonsterName,
		MonsterOutLook = 10,
		MonsterCanHandle,
		MonsterBossFlag,
		Monster_CATTR_LEVEL2_SPEED,
		MonsterWalkSpeed,
		MonsterLevel = 25,
		MonsterRespawnTime,
		MonsterMinDamagePercent,
		MonsterExp,
		Monster_CATTR_LEVEL2_ATTACKRATE_NEAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_FAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_M,
		Monster_CATTR_LEVEL2_DEFENCE_NEAR,
		Monster_CATTR_LEVEL2_DEFENCE_FAR,
		Monster_CATTR_LEVEL2_DEFENCE_M,
		Monster_CATTR_LEVEL2_MAXHP,
		Monster_CATTR_LEVEL2_MAXMP,
		Monster_CATTR_LEVEL2_RESTOREHP,
		Monster_CATTR_LEVEL2_RESTOREMP,
		Monster_CATTR_LEVEL2_HIT,
		Monster_CATTR_LEVEL2_MISS,
		Monster_CATTR_LEVEL2_CRITRATE,
		Monster_CATTR_LEVEL2_TOUGHNESS,
		MonsterAttrAttack1,
		MonsterAttrAttack2,
		MonsterAttrAttack3,
		MonsterAttrAttack4,
		MonsterAttrDefence1,
		MonsterAttrDefence2,
		MonsterAttrDefence3,
		MonsterAttrDefence4,
		MonsterScriptID,
		MonsterAttackAnimTime,
		MonsterAttackCooldownTime,
		Monster_CATTR_LEVEL2_ATTACKSPEED,
		MonsterWeaponID,
		MonsterHorseID,
		MonsterBaseAI,
		MonsterExtAI,
		MonsterCamp,
		MonsterFriendValue,
		MonsterBossSnapImmID,
		MonsterBossDurationImmID,
		MonsterDropSearchRange,
		MonsterDropTeamCount,
		MonsterDropItemSetID,
		MonsterDropRate,
		MonsterDropHorseID,
	};

	mMonsterPropertyTable = new TABFile(0);
	BOOL	ret = mMonsterPropertyTable->OpenFromTXT(monster_filename.c_str());
	int32_t	iTableCount = mMonsterPropertyTable->GetRecordsNum();
	int32_t	iColumnCount = mMonsterPropertyTable->GetFieldsNum();

	KCheck(iTableCount > 0 && iTableCount < MAXTYPE_NUMBER);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char* pSplitString = NULL;
	int32_t		iValue;
	int32_t		iType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	for (int32_t i = 0; i < iTableCount; i++)
	{

		MonsterProperty* monsterProperty = new MonsterProperty;
		iType = mMonsterPropertyTable->Search_Posistion(i, MonsterType)->iValue;


		monsterProperty->m_Type = iType;
		
		mMonsterPropertyMap[iType] = monsterProperty;

		strncpy(monsterProperty->m_Name,
			mMonsterPropertyTable->Search_Posistion(i, MonsterName)->pString,
			sizeof(monsterProperty->m_Name) - 1);

		monsterProperty->m_Level = mMonsterPropertyTable->Search_Posistion(i, MonsterLevel)->iValue;
		monsterProperty->m_RespawnTime = mMonsterPropertyTable->Search_Posistion(i, MonsterRespawnTime)->iValue;
		monsterProperty->m_MinDamagePercent = mMonsterPropertyTable->Search_Posistion(i, MonsterMinDamagePercent)->iValue;
		monsterProperty->m_BaseExp = mMonsterPropertyTable->Search_Posistion(i, MonsterExp)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACK_NEAR] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_ATTACKRATE_NEAR)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACK_FAR] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_ATTACKRATE_FAR)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKRATE_M] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_ATTACKRATE_M)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCE_NEAR] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_DEFENCE_NEAR)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCE_FAR] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_DEFENCE_FAR)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCE_M] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_DEFENCE_M)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_MAXHP] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_MAXHP)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_MAXMP] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_MAXMP)->iValue;
		monsterProperty->m_Table[CPROPERTY_LEVEL2_RESTOREHP] = mMonsterPropertyTable->Search_Posistion(i, Monster_CATTR_LEVEL2_RESTOREHP)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_RESTOREMP] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_RESTOREMP
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_HIT] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_HIT
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_MISS] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_MISS
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_CRITRATE] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_CRITRATE
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_TOUGHNESS] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_TOUGHNESS
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKCOLD] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrAttack1
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKFIRE] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrAttack2
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKLIGHT] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrAttack3
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKPOISON] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrAttack4
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCECOLD] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrDefence1
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCEFIRE] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrDefence2
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCELIGHT] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrDefence3
		)->iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_DEFENCEPOISON] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterAttrDefence4
		)->iValue;

		monsterProperty->m_ScriptID = mMonsterPropertyTable->Search_Posistion
		(
			i,
			MonsterScriptID
		)->iValue;

		KCheck(monsterProperty->m_ScriptID <= 0 || monsterProperty->m_ScriptID >= 100000);

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterAttackAnimTime)->iValue;
		monsterProperty->m_AttackAnimTime = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterAttackCooldownTime)->iValue;
		monsterProperty->m_AttackCooldownTime = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterOutLook)->iValue;
		monsterProperty->m_OutLook = iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_SPEED] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_SPEED
		)->iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterWalkSpeed)->iValue;
		monsterProperty->m_WalkSpeed = iValue;

		monsterProperty->m_Table[CPROPERTY_LEVEL2_ATTACKSPEED] = mMonsterPropertyTable->Search_Posistion
		(
			i,
			Monster_CATTR_LEVEL2_ATTACKSPEED
		)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitString = mMonsterPropertyTable->Search_Posistion(i, MonsterWeaponID)->pString;
		readWeaponID(&oSplitL1, &oSplitL2, pSplitString, monsterProperty);

		pSplitString = mMonsterPropertyTable->Search_Posistion(i, MonsterHorseID)->pString;

		readHorseID(&oSplitL1, &oSplitL2, pSplitString, monsterProperty);

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterBaseAI)->iValue;
		monsterProperty->m_BaseAI = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterExtAI)->iValue;
		monsterProperty->m_ExtAI = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterCamp)->iValue;
		monsterProperty->m_Camp = iValue;

		if (iType == 11970)
		{
			int kk = 0;
		}

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterCannotFight)->iValue;
		monsterProperty->m_CannotFight = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterCanHandle)->iValue;
		monsterProperty->m_CanHandle = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterFriendValue)->iValue;
		monsterProperty->m_FriendValue = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterBossFlag)->iValue;
		monsterProperty->m_BossFlag = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterBossSnapImmID)->iValue;
		monsterProperty->m_SnapSkillImmID = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterBossDurationImmID)->iValue;
		monsterProperty->m_DurationSkillImmID = iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterDropSearchRange)->iValue;
		monsterProperty->m_DropSearchRange = (float)iValue;

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterDropTeamCount)->iValue;
		monsterProperty->m_SearchTeamCount = iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char* pSplitString = mMonsterPropertyTable->Search_Posistion(i, MonsterDropItemSetID)->pString;
		SplitStringLevelOne	pSplitL1;
		SplitStringLevelTwo	pSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitL1.Reset();
		pSplitL2.Reset();
		pSplitL1.Init('|', &pSplitL2);
		pSplitL2.Init('~', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = pSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iLineCount > 10) iLineCount = 0;
		monsterProperty->m_MonsterDropSetCount = iLineCount;
		monsterProperty->m_MonsterDropItemSetID = new int32[iLineCount];
		for (int32 nID = 0; nID < iLineCount; ++nID)
		{
			monsterProperty->m_MonsterDropItemSetID[nID] = atoi(pSplitL2.GetResultLine(nID));
		}

		iValue = mMonsterPropertyTable->Search_Posistion(i, MonsterDropRate)->iValue;
		if (iValue < 0)
		{
			monsterProperty->m_nMonsterDropRate = 0;
		}
		else
		{
			KCheck(iValue <= 100);
			monsterProperty->m_nMonsterDropRate = iValue;
		}

		monsterProperty->m_nMonsterDropRate = iValue;

		pSplitString = mMonsterPropertyTable->Search_Posistion(i, MonsterDropHorseID)->pString;
		monsterProperty->m_iHorseDropCount = CommonStringSplit
		(
			&oSplitL1,
			&oSplitL2,
			pSplitString,
			MaxHorseDropNum,
			monsterProperty->m_aHorseDropID
		);

		monsterProperty->m_Used = TRUE;
	}

	

	return true;
}


void DataManager::readWeaponID
(
	SplitStringLevelOne* pSplitL1,
	SplitStringLevelTwo* pSplitL2,
	const char* pSplitString,
	MonsterProperty* monsterProperty
)
{
	pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(MONSTER_EXT_ATTR_ENUM_SIZE >= iLineCount);
	if (MONSTER_EXT_ATTR_ENUM_SIZE < iLineCount)
	{
		return;
	}

	for (int32 iWeapon = 0; iWeapon < iLineCount; ++iWeapon)
	{
		monsterProperty->m_WeaponID[iWeapon] = atoi(pSplitL2->GetResultLine(iWeapon));
	}

	monsterProperty->m_iWeaponCount = iLineCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DataManager::readHorseID
(
	SplitStringLevelOne* pSplitL1,
	SplitStringLevelTwo* pSplitL2,
	const char* pSplitString,
	MonsterProperty* monsterProperty
)
{
	pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(MONSTER_EXT_ATTR_ENUM_SIZE >= iLineCount);
	if (MONSTER_EXT_ATTR_ENUM_SIZE < iLineCount)
	{
		return;
	}

	for (int32 iHorse = 0; iHorse < iLineCount; ++iHorse)
	{
		monsterProperty->m_HorseID[iHorse] = atoi(pSplitL2->GetResultLine(iHorse));
	}

	monsterProperty->m_iHorseCount = iLineCount;
}

MonsterProperty* DataManager::getMonsterProperty(uint32_t id)
{
	auto itor = mMonsterPropertyMap.find(id);
	if (itor != mMonsterPropertyMap.end())
	{
		return itor->second;
	}
	return nullptr;
}

int32_t DataManager::getMonsterProperty(uint32_t id, uint32_t index)
{
	auto itor = mMonsterPropertyMap.find(id);
	if (itor != mMonsterPropertyMap.end())
	{
		return itor->second->m_Table[index];
	}
	return 0;
}

_QUEST_DATA_t* DataManager::getQuestByID(int32_t questID)
{
	auto itor = mQuestMap.find(questID);
	if (itor != mQuestMap.end())
	{
		return itor->second;
	}
	return nullptr;
}

const DataManager::FlagMD& DataManager::getFlagMDClientFilter()
{
	return m_FlagMDClientFilter;
}

NPC_QUEST* DataManager::getNpcQuest(int32_t objID)
{
	auto itor = mNpcQuestMap.find(objID);
	if (itor != mNpcQuestMap.end())
	{
		return itor->second;
	}
	return nullptr;
}

MonsterAIData* DataManager::getMonsterAIData()
{
	return &mMonsterAI;
}


SpellTemplateData* DataManager::getSpellTemplate(uint32_t id)
{
	auto it = mSpellTemplateMap.find(id);
	if (it != mSpellTemplateMap.end())
	{
		return it->second;
	}
	return nullptr;
}

SpellInstanceData* DataManager::getSpellInstance(uint32_t id)
{
	auto it = mSpellInstanceMap.find(id);
	if (it != mSpellInstanceMap.end())
	{
		return it->second;
	}
	return nullptr;
}

EffectData* DataManager::getEffectData(uint32_t id)
{
	auto it = mEffectDataMap.find(id);
	if (it != mEffectDataMap.end())
	{
		return it->second;
	}
	return nullptr;
}

BaseSkill* DataManager::getSkill(uint32_t id)
{
	return nullptr;
}

_HORSE_ATTR* DataManager::getHorseAttr(uint32_t id)
{
	return &mHorseAttrTable->m_aHorseTbl[id];
}

_HORSE_ATTR_TBL* DataManager::getHorseAttrTable()
{
	return mHorseAttrTable;
}

_HORSE_SKILL_TBL* DataManager::getHorseSkillTable()
{
	return mHorseSkillTable;
}

SHorseLevelupTab* DataManager::getHorseLevelupTable()
{
	return mHorseLevelupTable;
}

_HORSE_PER_LIMIT_TBL* DataManager::getHorsePerlimitTable()
{
	return mHorsePerlimitTable;
}

IDCollection* DataManager::getCollection(uint32_t id)
{
	auto it = mCollectionMap.find(id);
	if (it != mCollectionMap.end())
	{
		return it->second;
	}
	return nullptr;
}


int32_t DataManager::getProfessionProperty(int32_t ainfotype, int32_t profession)
{
	return mProfessionPropertyTab->m_Table[ainfotype][profession];
}

int32_t DataManager::getAttrLevelUpValue(int32_t arrtype, int32_t profession, int32_t level)
{
	return mPropertyLevelUp->Get(arrtype, profession, level);
}

BaseSpellLogic* DataManager::getSpellLogicById(int32_t id)
{
	return (BaseSpellLogic*)mSpellLogicList.GetLogicById(id);
}

SpecialObjectLogic* DataManager::getSpecialObjectLogicById(int32_t id)
{
	return (SpecialObjectLogic*)mSpecialObjLogicList.GetLogicById(id);
}

const SpecialObjData_T* DataManager::getSpecialObjectDataById(int32_t id)
{
	return mSpecialObjDataMgr.GetInstanceByID(id);
}

const EffectLogic* DataManager::getEffectLogic(int32_t id)
{
	return mEffectLogicList.GetLogicById(id);
}

const Profession* DataManager::getProfessionLogic(int32_t id)
{
	return mProfessionLogicList.GetLogicById(id);
}

const ImpactSEData_T* DataManager::getImapctSEData(int32_t id)
{
	auto it = mImpactDescMap.find(id);
	if (it != mImpactDescMap.end())
		return it->second;
	return nullptr;
}

TitleInfo& DataManager::getTitleInfo()
{
	return *mTitleInfo;
}

TitleCombination& DataManager::getTitleCombination()
{
	return *mTitleCombination;
}
SMonsterWeaponAndSkillTable* DataManager::getMonsterWeaponAndSkillTable()
{
	return mMonsterWeaponAndSkillTable;
}

_BEASTIE_DATA_TABLE* DataManager::getBeastTable()
{
	return mBeastDataTable;
}

_GATHER_POINT_INFO_TAB* DataManager::getGatherPointTable()
{
	return mGatherPointTable;
}

CampAndStandDataMgr* DataManager::getCampAndStandDataMgr()
{
	return &mCampAndStandDataMgr;
}

void DataManager::loadMonsterSkillTable()
{
	mMonsterWeaponAndSkillTable = new SMonsterWeaponAndSkillTable;
	enum MonsterSkillIndex
	{
		MSI_Index = 0,
		MSI_SkillIndex = 1,
		MSI_WeaponID = 3,
		MSI_SkillID = 4
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MONSTER_SKILL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= MonsterWeaponAndSkillTable::MWAST_MAX_NUM);
	if (SMonsterWeaponAndSkillTable::MWAST_MAX_NUM < iTableCount)
	{
		return;
	}

	mMonsterWeaponAndSkillTable->m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	const char* pSplitString = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iIndex = ThirdFile.Search_Posistion(i, MSI_Index)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		mMonsterWeaponAndSkillTable->m_aWeaponSkill[iIndex].m_iIndex = iIndex;
		mMonsterWeaponAndSkillTable->m_aWeaponSkill[iIndex].m_iWeaponID = ThirdFile.Search_Posistion
		(
			i,
			MSI_WeaponID
		)->iValue;
		pSplitString = ThirdFile.Search_Posistion(i, MSI_SkillIndex)->pString;
		oSplitL1.Reset();
		oSplitL2.Reset();
		oSplitL1.Init('|', &oSplitL2);
		oSplitL2.Init('~', NULL);
		oSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = oSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(MonsterWeaponAndSkillTable::MWAST_MAX_NUM >= iLineCount);
		if (SMonsterWeaponAndSkillTable::MWAST_MAX_NUM < iLineCount)
		{
			break;
		}

		for (int32 iLine = 0; iLine < iLineCount; ++iLine)
		{
			mMonsterWeaponAndSkillTable->m_aWeaponSkill[iIndex].m_aSkillLevelIndex[iLine] = atoi(oSplitL2.GetResultLine(iLine)) - 1;
		}

		mMonsterWeaponAndSkillTable->m_aWeaponSkill[iIndex].m_iSkillLevelIndexCount = iLineCount;

		for (int32 j = 0; j < SMonsterWeaponAndSkill::MWAS_MAX_LEVEL; ++j)
		{
			mMonsterWeaponAndSkillTable->m_aWeaponSkill[iIndex].m_aSkillLevel[j] = ThirdFile.Search_Posistion
			(
				i,
				MSI_SkillID + j
			)->iValue;
		}
	}
}

enum
{
	DataIdx_QuestID = 0,
	DataIdx_ScriptID,
	DataIdx_QuestType,
	DataIdx_QuestName,
	DataIdx_QuestDisp,
	DataIdx_PreQuestID1,
	DataIdx_PreQuestID2,
	DataIdx_PreQuestID3,
	DataIdx_MinLevel,
	DataIdx_MaxLevel,
	DataIdx_MoneyType,
	DataIdx_NeedMoney,
	DataIdx_Country,
	DataIdx_Profession,
	DataIdx_Camp,
	DataIdx_QuestDest1,
	DataIdx_QuestDest2,
	DataIdx_QuestDest3,
	DataIdx_QuestDest4,
	DataIdx_QuestDest5,
	DataIdx_MoneyRewardType,
	DataIdx_MoneyRewardP1,
	DataIdx_MoneyRewardP2,
	DataIdx_MoneyRewardP3,
	DataIdx_ExpRewardP1,
	DataIdx_ExpRewardP2,
	DataIdx_ExpRewardP3,
	DataIdx_ShengWangType,
	DataIdx_ShengWangRewartP1,
	DataIdx_ShengWangRewartP2,
	DataIdx_ShengWangRewartP3,
	DataIdx_EnergyRewardType,
	DataIdx_EnergyReward,
	DataIdx_GuildRewardType,
	DataIdx_GuildReward,
	DataIdx_FixItemID1,
	DataIdx_FixItemNum1,
	DataIdx_FixItemID2,
	DataIdx_FixItemNum2,
	DataIdx_FixItemID3,
	DataIdx_FixItemNum3,
	DataIdx_FixItemID4,
	DataIdx_FixItemNum4,
	DataIdx_SelItemID1,
	DataIdx_SelItemNum1,
	DataIdx_SelItemID2,
	DataIdx_SelItemNum2,
	DataIdx_SelItemID3,
	DataIdx_SelItemNum3,
	DataIdx_SelItemID4,
	DataIdx_SelItemNum4,
	DataIdx_SelItemID5,
	DataIdx_SelItemNum5,
	DataIdx_SelItemID6,
	DataIdx_SelItemNum6,
	DataIdx_RewardScript,
	DataIdx_QuestDesc,
	DataIdx_QuestTarget,
	DataIdx_QuestContinue,
	DataIdx_QuestAbandon,
	DataIdx_QuestSuccess,
	DataIdx_SubmitNPCGUID,
	DataIdx_SubmitNPCName,
	DataIdx_SubmitNPCSceneID,
	DataIdx_PathIndex,
	DataIdx_AfterQuestType,
	DataIdx_AfterQuestScriptID,
	DataIdx_QuestTarget1,
	DataIdx_QuestTarget2,
	DataIdx_QuestTarget3,
	DataIdx_QuestTarget4,
	DataIdx_QuestTarget5,
	DataIdx_QuestHelp,
	DataIdx_SyncServer,	/* 服务器端不读取此数据 */
	DataIdx_QuestFlag,	/* 任务特殊处理参数 */
	DataIdx_AcceptFlag,	/* 服务器接任务标志 */
};


enum NpcQuestTab
{
	NpcType = 0,
	NpcName = 1,
	NpcDefaultDialog = 2,
	NpcDialogScript = 3,
	NpcEventList = 4,
	NpcQuestList = 5,
};

void	DataManager::loadQuestList()
{
	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_LIST);

	int32 iTableCount = ThirdFile.GetRecordsNum();
	int32 iTableColumn = ThirdFile.GetFieldsNum();

	_QUEST_DATA_t* m_QuestData = new _QUEST_DATA_t[iTableCount];

	memset(m_QuestData, 0, sizeof(_QUEST_DATA_t) * iTableCount);

	const int32 ITEMLIST_LENGTH = 512, ITEMID_LENGTH = 8;
	char chItemIDList[ITEMLIST_LENGTH] = { 0 }, chID[ITEMID_LENGTH + 1] = { 0 };
	int32 iLength = 0, iItemLength = 0;
	for (int32 i = 0; i < iTableCount; ++i)
	{
		m_QuestData[i].nQuestID = ThirdFile.Search_Posistion(i, DataIdx_QuestID)->iValue;
		m_QuestData[i].nScriptID = ThirdFile.Search_Posistion(i, DataIdx_ScriptID)->iValue;
		KCheck(m_QuestData[i].nScriptID == INVALID_ID || m_QuestData[i].nScriptID > 100000);
		m_QuestData[i].nQuestType = ThirdFile.Search_Posistion(i, DataIdx_QuestType)->iValue;
		strncpy(m_QuestData[i].szQuestName, ThirdFile.Search_Posistion(i, DataIdx_QuestName)->pString, 256);
		strncpy(m_QuestData[i].szQuestDisp, ThirdFile.Search_Posistion(i, DataIdx_QuestDisp)->pString, 256);
		m_QuestData[i].nPreQuestID1 = ThirdFile.Search_Posistion(i, DataIdx_PreQuestID1)->iValue;
		m_QuestData[i].nPreQuestID2 = ThirdFile.Search_Posistion(i, DataIdx_PreQuestID2)->iValue;
		m_QuestData[i].nPreQuestID3 = ThirdFile.Search_Posistion(i, DataIdx_PreQuestID3)->iValue;
		m_QuestData[i].nMinLevel = ThirdFile.Search_Posistion(i, DataIdx_MinLevel)->iValue;
		m_QuestData[i].nMaxLevel = ThirdFile.Search_Posistion(i, DataIdx_MaxLevel)->iValue;
		m_QuestData[i].nSpendMoneyType = ThirdFile.Search_Posistion(i, DataIdx_MoneyType)->iValue;
		m_QuestData[i].nNeedMoney = ThirdFile.Search_Posistion(i, DataIdx_NeedMoney)->iValue;
		m_QuestData[i].nCountry = ThirdFile.Search_Posistion(i, DataIdx_Country)->iValue;
		m_QuestData[i].nProfession = ThirdFile.Search_Posistion(i, DataIdx_Profession)->iValue;
		m_QuestData[i].nCamp = ThirdFile.Search_Posistion(i, DataIdx_Camp)->iValue;
		m_QuestData[i].nQuestDest[0] = ThirdFile.Search_Posistion(i, DataIdx_QuestDest1)->iValue;
		m_QuestData[i].nQuestDest[1] = ThirdFile.Search_Posistion(i, DataIdx_QuestDest2)->iValue;
		m_QuestData[i].nQuestDest[2] = ThirdFile.Search_Posistion(i, DataIdx_QuestDest3)->iValue;
		m_QuestData[i].nQuestDest[3] = ThirdFile.Search_Posistion(i, DataIdx_QuestDest4)->iValue;
		m_QuestData[i].nQuestDest[4] = ThirdFile.Search_Posistion(i, DataIdx_QuestDest5)->iValue;
		m_QuestData[i].nMoneyRewardType = ThirdFile.Search_Posistion(i, DataIdx_MoneyRewardType)->iValue;
		m_QuestData[i].nMoneyRewardP1 = ThirdFile.Search_Posistion(i, DataIdx_MoneyRewardP1)->iValue;
		m_QuestData[i].nMoneyRewardP2 = ThirdFile.Search_Posistion(i, DataIdx_MoneyRewardP2)->iValue;
		m_QuestData[i].nMoneyRewardP3 = ThirdFile.Search_Posistion(i, DataIdx_MoneyRewardP3)->iValue;
		m_QuestData[i].nExpRewardP1 = ThirdFile.Search_Posistion(i, DataIdx_ExpRewardP1)->iValue;
		m_QuestData[i].nExpRewardP2 = ThirdFile.Search_Posistion(i, DataIdx_ExpRewardP2)->iValue;
		m_QuestData[i].nExpRewardP3 = ThirdFile.Search_Posistion(i, DataIdx_ExpRewardP3)->iValue;
		m_QuestData[i].nShengWangType = ThirdFile.Search_Posistion(i, DataIdx_ShengWangType)->iValue;
		m_QuestData[i].nShengWangRewartP1 = ThirdFile.Search_Posistion(i, DataIdx_ShengWangRewartP1)->iValue;
		m_QuestData[i].nShengWangRewartP2 = ThirdFile.Search_Posistion(i, DataIdx_ShengWangRewartP2)->iValue;
		m_QuestData[i].nShengWangRewartP3 = ThirdFile.Search_Posistion(i, DataIdx_ShengWangRewartP3)->iValue;
		m_QuestData[i].nEnergyRewardType = ThirdFile.Search_Posistion(i, DataIdx_EnergyRewardType)->iValue;
		m_QuestData[i].nEnergyReward = ThirdFile.Search_Posistion(i, DataIdx_EnergyReward)->iValue;
		m_QuestData[i].nGuildRewardType = ThirdFile.Search_Posistion(i, DataIdx_GuildRewardType)->iValue;
		m_QuestData[i].nGuildReward = ThirdFile.Search_Posistion(i, DataIdx_GuildReward)->iValue;
		m_QuestData[i].nFixItemID1 = ThirdFile.Search_Posistion(i, DataIdx_FixItemID1)->iValue;
		m_QuestData[i].nFixItemNum1 = ThirdFile.Search_Posistion(i, DataIdx_FixItemNum1)->iValue;
		m_QuestData[i].nFixItemID2 = ThirdFile.Search_Posistion(i, DataIdx_FixItemID2)->iValue;
		m_QuestData[i].nFixItemNum2 = ThirdFile.Search_Posistion(i, DataIdx_FixItemNum2)->iValue;
		m_QuestData[i].nFixItemID3 = ThirdFile.Search_Posistion(i, DataIdx_FixItemID3)->iValue;
		m_QuestData[i].nFixItemNum3 = ThirdFile.Search_Posistion(i, DataIdx_FixItemNum3)->iValue;
		m_QuestData[i].nFixItemID4 = ThirdFile.Search_Posistion(i, DataIdx_FixItemID4)->iValue;
		m_QuestData[i].nFixItemNum4 = ThirdFile.Search_Posistion(i, DataIdx_FixItemNum4)->iValue;
		// 2010-03-31（ttp-29507）
		strncpy(chItemIDList, ThirdFile.Search_Posistion(i, DataIdx_SelItemID1)->pString, ITEMLIST_LENGTH);
		iLength = (int32)strlen(chItemIDList);
		KCheckEx(iLength < ITEMLIST_LENGTH, "iLength超过长度!");
		m_QuestData[i].nSelItemCount = 0;
		iItemLength = 0;
		memset(m_QuestData[i].nSelItemsID, 0, sizeof(int32) * MAX_SELECT_ITEM);
		for (int iOffSet = 0; iOffSet <= iLength && iLength > 0; iOffSet++)
		{
			if (iOffSet < iLength)
			{
				if (chItemIDList[iOffSet] != '|')
				{
					if (iItemLength >= ITEMID_LENGTH)
						KCheckEx(FALSE, "格式错误!");

					chID[iItemLength++] = chItemIDList[iOffSet];
				}// if
				else
				{
					m_QuestData[i].nSelItemsID[m_QuestData[i].nSelItemCount++] = atoi(chID);
					iItemLength = 0;
					memset(&chID, 0, sizeof(chID));
				}// else
			}
			else
			{
				m_QuestData[i].nSelItemsID[m_QuestData[i].nSelItemCount++] = atoi(chID);
			}// else
		}// if
		if (m_QuestData[i].nSelItemCount > 1)
		{
			// 获得选择类型
			m_QuestData[i].nChooseType = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum1)->iValue;
		}// if
		else
		{
			//m_QuestData[ i].nSelItemID1  = ThirdFile.Search_Posistion( i, DataIdx_SelItemID1)->iValue;
			strncpy(chItemIDList, ThirdFile.Search_Posistion(i, DataIdx_SelItemID1)->pString, ITEMLIST_LENGTH);
			m_QuestData[i].nSelItemID1 = atoi(chItemIDList);
			m_QuestData[i].nSelItemNum1 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum1)->iValue;
			m_QuestData[i].nSelItemID2 = ThirdFile.Search_Posistion(i, DataIdx_SelItemID2)->iValue;
			m_QuestData[i].nSelItemNum2 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum2)->iValue;
			m_QuestData[i].nSelItemID3 = ThirdFile.Search_Posistion(i, DataIdx_SelItemID3)->iValue;
			m_QuestData[i].nSelItemNum3 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum3)->iValue;
			m_QuestData[i].nSelItemID4 = ThirdFile.Search_Posistion(i, DataIdx_SelItemID4)->iValue;
			m_QuestData[i].nSelItemNum4 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum4)->iValue;
			m_QuestData[i].nSelItemID5 = ThirdFile.Search_Posistion(i, DataIdx_SelItemID5)->iValue;
			m_QuestData[i].nSelItemNum5 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum5)->iValue;
			m_QuestData[i].nSelItemID6 = ThirdFile.Search_Posistion(i, DataIdx_SelItemID6)->iValue;
			m_QuestData[i].nSelItemNum6 = ThirdFile.Search_Posistion(i, DataIdx_SelItemNum6)->iValue;
			m_QuestData[i].nChooseType = CHOOSE_BY_OLDTYPE;
		}// else
		m_QuestData[i].nRewardScript = ThirdFile.Search_Posistion(i, DataIdx_RewardScript)->iValue;
		strncpy(m_QuestData[i].szQuestDesc, ThirdFile.Search_Posistion(i, DataIdx_QuestDesc)->pString, 1024);
		strncpy(m_QuestData[i].szQuestManual, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget)->pString, 1024);
		strncpy(m_QuestData[i].szQuestContinue, ThirdFile.Search_Posistion(i, DataIdx_QuestContinue)->pString, 1024);
		strncpy(m_QuestData[i].szQuestAbandon, ThirdFile.Search_Posistion(i, DataIdx_QuestAbandon)->pString, 1024);
		strncpy(m_QuestData[i].szQuestSuccess, ThirdFile.Search_Posistion(i, DataIdx_QuestSuccess)->pString, 1024);
		m_QuestData[i].nSubmitNPCGUID = ThirdFile.Search_Posistion(i, DataIdx_SubmitNPCGUID)->iValue;
		strncpy(m_QuestData[i].szSubmitNPCName, ThirdFile.Search_Posistion(i, DataIdx_SubmitNPCName)->pString, NPC_NAME_LEN);
		m_QuestData[i].nSubmitNPCMapID = ThirdFile.Search_Posistion(i, DataIdx_SubmitNPCSceneID)->iValue;
		m_QuestData[i].nPathIndex = ThirdFile.Search_Posistion(i, DataIdx_PathIndex)->iValue;
		m_QuestData[i].nAfterQuestType = ThirdFile.Search_Posistion(i, DataIdx_AfterQuestType)->iValue;
		m_QuestData[i].nAfterQuestScriptID = ThirdFile.Search_Posistion(i, DataIdx_AfterQuestScriptID)->iValue;
		strncpy(m_QuestData[i].szQuestTarget1, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget1)->pString, 128);
		strncpy(m_QuestData[i].szQuestTarget2, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget2)->pString, 128);
		strncpy(m_QuestData[i].szQuestTarget3, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget3)->pString, 128);
		strncpy(m_QuestData[i].szQuestTarget4, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget4)->pString, 128);
		strncpy(m_QuestData[i].szQuestTarget5, ThirdFile.Search_Posistion(i, DataIdx_QuestTarget5)->pString, 128);
		strncpy(m_QuestData[i].szQuestHelp, ThirdFile.Search_Posistion(i, DataIdx_QuestHelp)->pString, 128);

		/* 读取任务的特殊处理 */
		m_QuestData[i].nQuestFlag = ThirdFile.Search_Posistion(i, DataIdx_QuestFlag)->iValue;

		/* 限定死这个值的范围,如果范围出错 */
		KCheck(m_QuestData[i].nQuestFlag >= 0 && m_QuestData[i].nQuestFlag <= 1);

		/* 读取接任务图标标记 */
		m_QuestData[i].nAcceptFlag = ThirdFile.Search_Posistion(i, DataIdx_AcceptFlag)->iValue;

		mQuestMap[m_QuestData[i].nQuestID] = &m_QuestData[i];
		if (m_QuestData[i].nScriptID > 0)
		{
			mQuestScriptMap[m_QuestData[i].nScriptID] = &m_QuestData[i];
		}// if
	}// for
}

void DataManager::loadFlagMDClientFilter()
{
	enum
	{
		DataIdx_MisPos = 15,/* 个人全局时间，循环任务的任务已做参数 */
	};

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_DAY_TIPS);

	int32 iTableCount = ThirdFile.GetRecordsNum();
	int32 iTableColumn = ThirdFile.GetFieldsNum();

	KCheck(iTableColumn >= DataIdx_MisPos);
	KCheck(iTableCount);

	const int32 ITEMLIST_LENGTH = 32;
	char chItemIDList[ITEMLIST_LENGTH] = { 0 };
	int32 iLength = 0, iItemLength = 0;

	SplitStringLevelOne* pSplitL1 = new SplitStringLevelOne;
	SplitStringLevelTwo* pSplitL2 = new SplitStringLevelTwo;


	for (int32 i = 0; i < iTableCount; ++i)
	{
		strncpy(chItemIDList, ThirdFile.Search_Posistion(i, DataIdx_MisPos)->pString, ITEMLIST_LENGTH);
		iLength = (int32)strlen(chItemIDList);
		KCheckEx(iLength < ITEMLIST_LENGTH, "iLength超过长度!");


		pSplitL1->Init('|', pSplitL2);
		pSplitL2->Init('~', NULL);
		pSplitL1->DoSplit(chItemIDList);

		int32 iLineCount = pSplitL2->GetResultLineCount();

		if (6 != iLineCount)
		{
			continue;
		}
		int32 iMDIndex1 = atoi(pSplitL2->GetResultLine(0));
		int32 iMDIndex2 = atoi(pSplitL2->GetResultLine(3));

		if (!m_FlagMDClientFilter.IsSetBit(iMDIndex1))
		{
			m_FlagMDClientFilter.UpdateBit(iMDIndex1, TRUE);
		}

		if (iMDIndex1 != iMDIndex2 && !m_FlagMDClientFilter.IsSetBit(iMDIndex2))
		{
			m_FlagMDClientFilter.UpdateBit(iMDIndex2, TRUE);
		}

	}// for

	delete pSplitL1;
	delete pSplitL2;
}

void DataManager::loadNpcQuest()
{
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_NPC_QUEST);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < MAXTYPE_NUMBER);
	NPC_QUEST* pNPCQuest = new NPC_QUEST[iTableCount];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iType;
	char	EventList[NPC_EVENT_LENGTH] = { 0 };
	char	Event[16] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < iTableCount; i++)
	{
		iType = ThirdFile.Search_Posistion(i, NpcType)->iValue;

		pNPCQuest[i].m_Type = iType;
		pNPCQuest[i].m_ScriptID = ThirdFile.Search_Posistion(i, NpcDialogScript)->iValue;
		KCheck(pNPCQuest[i].m_ScriptID <= 0 || pNPCQuest[i].m_ScriptID >= 100000);

		memset(Event, 0, sizeof(Event));
		strncpy(EventList, ThirdFile.Search_Posistion(i, NpcEventList)->pString, NPC_EVENT_LENGTH);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iEventListLength = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (EventList[0] != '\0') iEventListLength = (int32)strlen(EventList);

		KCheckEx(iEventListLength < NPC_EVENT_LENGTH, "EventList超过长度!");

		/*~~~~~~~~~~~~~~~~~~~~*/
		int32	EventLength = 0;
		int32	EventIndex = 0;
		/*~~~~~~~~~~~~~~~~~~~~*/

		pNPCQuest[i].m_EventCount = 0;
		for (int EventOffSet = 0; EventOffSet <= iEventListLength && iEventListLength > 0; EventOffSet++)
		{
			if (EventOffSet < iEventListLength)
			{
				if (EventList[EventOffSet] != '|')
				{
					if (EventLength >= 12) KCheckEx(FALSE, "格式错误!");

					Event[EventLength++] = EventList[EventOffSet];
				}
				else
				{
					pNPCQuest[i].m_EventList[EventIndex++] = atoi(Event);
					pNPCQuest[i].m_EventCount++;
					EventLength = 0;
					memset(&Event, 0, sizeof(Event));
				}
			}
			else
			{
				pNPCQuest[i].m_EventList[EventIndex++] = atoi(Event);
				pNPCQuest[i].m_EventCount++;
			}
		}

		memset(Event, 0, sizeof(Event));
		strncpy(EventList, ThirdFile.Search_Posistion(i, NpcQuestList)->pString, NPC_EVENT_LENGTH);

		iEventListLength = 0;
		if (EventList[0] != '\0') iEventListLength = (int32)strlen(EventList);

		EventLength = 0;
		EventIndex = 0;
		memset(Event, 0, 16);

		KCheckEx(iEventListLength < NPC_EVENT_LENGTH, "QuestList超过长度!");

		pNPCQuest[i].m_QuestCount = 0;
		for (int EventOffSet = 0; EventOffSet <= iEventListLength && iEventListLength > 0; EventOffSet++)
		{
			if (EventOffSet < iEventListLength)
			{
				if (EventList[EventOffSet] != '|')
				{
					if (EventLength >= 12) KCheckEx(FALSE, "格式错误!");

					Event[EventLength++] = EventList[EventOffSet];
				}
				else
				{
					pNPCQuest[i].m_QuestList[EventIndex++] = atoi(Event);
					pNPCQuest[i].m_QuestCount++;
					EventLength = 0;
					memset(&Event, 0, sizeof(Event));
				}
			}
			else
			{
				pNPCQuest[i].m_QuestList[EventIndex++] = atoi(Event);
				pNPCQuest[i].m_QuestCount++;
			}
		}

		if (pNPCQuest[i].m_Type > 0)
		{
			mNpcQuestMap[pNPCQuest[i].m_Type] = &pNPCQuest[i];
		}
	}
}

void DataManager::loadMonsterAIData()
{

	Configer	ini(FILE_MONSTER_BASE_BEHAVIOR);

	int32_t count = ini.Get_Property_Int("INFO", "AINUMBER");

	char	szSection[256], szName[256];
	for (int32 i = 0; i < count; i++)
	{
		mMonsterAI.mAIData.emplace_back();

		auto & itor = mMonsterAI.mAIData.back();
		for (int32 j = 0; j < BHVPARAM_NUMBER; j++)
		{
			sprintf(szSection, "AI%d", i);
			sprintf(szName, "AIPARAM%d", j);
			int32_t value = ini.Get_Property_Int(szSection, szName);
			if (6 == j) value = 2000;
			if (0 == j && -1 != value) value = 1000;
			itor.push_back(value);
		
		}
	}
}

void DataManager::loadSpellTemplate()
{
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_SKILL_TEMPLATE);
	int32	iTableCount = ThirdFile.GetRecordsNum();

	for (int32_t i = 0; i < iTableCount; i++)
	{

		int32_t	nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 > nID || 100000 <= nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}
		SpellTemplateData* spell = new SpellTemplateData;
		spell->InitFromDB(&ThirdFile, i);

		mSpellTemplateMap[nID] = spell;

		SpellInstanceData* instance = new SpellInstanceData;
		instance->InitFromDB(&ThirdFile, i);
		mSpellInstanceMap[nID] = instance;
	}
}

void DataManager::loadEffectData()
{
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_STANDARD_IMPACT_DATA);
	int32	iTableCount = ThirdFile.GetRecordsNum();

	for (int32_t i = 0; i < iTableCount; i++)
	{

		int32_t	nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 > nID || 100000 <= nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}
		EffectData* effect = new EffectData;
		effect->InitFromDB(&ThirdFile, i);

		mEffectDataMap[nID] = effect;
	}
}

void DataManager::loadCollectionData()
{
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ID_COLLECTION);
	int32	iTableCount = ThirdFile.GetRecordsNum();

	for (int32_t i = 0; i < iTableCount; i++)
	{

		int32_t	nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 > nID || 100000 <= nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}
		IDCollection* collection = new IDCollection;
		collection->InitFromDB(&ThirdFile, i);

		mCollectionMap[nID] = collection;
	}
}

void DataManager::loadProfessionProperty()
{
	mProfessionPropertyTab = new ProfessionPropertyTab;

	Configer	ini(FILE_BASE_VALUE);

	for (int32_t i = 0; i < PROFESSION_NUMBER; i++)
	{
		for (int32_t j = 0; j < AINFOTYPE_NUMBER; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szSection[256], szName[256];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			sprintf(szSection, "PROFESSION%d", i);
			sprintf(szName, "AINFOTYPE%d", j);
			mProfessionPropertyTab->m_Table[j][i] = ini.Get_Property_Int(szSection, szName);
		}
	}
}

void DataManager::loadPropertyLevelUp()
{
	mPropertyLevelUp = new Player_PROPERTY_LEVELUP_TAB;

	enum AttrLevelupTBData { TBLevel = 0, TBDataBegin = 1 };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ATTR_LEVEL_UP);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == MAX_TABLE_DEFINE_LEVEL + 1);

	for (int32 i = 0; i < MAX_TABLE_DEFINE_LEVEL + 1; i++)
	{
		for (int32 j = 0; j < PROFESSION_NUMBER; j++)
		{
			for (int32 k = 0; k < CPROPERTY_LEVEL_NUMBER; k++) //每个职业5行
			{
				iColumn = TBDataBegin + j * CPROPERTY_LEVEL_NUMBER + k;

				KCheck(iColumn < iTableColumn);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	iValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				mPropertyLevelUp->Set(k, j, i, iValue);
			}
		}
	}
}

void DataManager::loadSpellLogic()
{

}

void DataManager::loadImpactSE()
{
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_IMPACT_SEDATA);
	int32	iTableCount = ThirdFile.GetRecordsNum();

	for (int32_t i = 0; i < iTableCount; i++)
	{

		int32_t	nID = ThirdFile.Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 > nID || 100000 <= nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}
		ImpactSEData_T* impact = new ImpactSEData_T;
		impact->InitFromDB(&ThirdFile, i);

		mImpactDescMap[nID] = impact;
	}
}

void DataManager::loadTitle()
{
	enum TitleData
	{
		TitileID = 0,
		TitleType,
		TitleNameMale = 4,
		TitleNameFemale,
		TitleTime = 7,
		TitleBuff = 9,
		TitleSuitID = 11,
		TitleDataCount,
	};

	TABFile* ThirdFile = new TABFile(0);
	BOOL	ret = ThirdFile->OpenFromTXT(FILE_TITLE_INFO);
	int32	iTableCount = ThirdFile->GetRecordsNum();
	int32	iColumnCount = ThirdFile->GetFieldsNum();


	mTitleInfo = new TitleInfo;
	for (int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iID = ThirdFile->Search_Posistion(i, TitileID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iID >= MAX_TITLE_SIZE)
		{
			KCheckEx(FALSE, "称号ID超出称号上限！");
			continue;
		}

		mTitleInfo->m_TableInfo[iID].m_TitleID = (uchar)iID;
		mTitleInfo->m_TableInfo[iID].m_iTitleType = ThirdFile->Search_Posistion(i, TitleType)->iValue;
		strncpy
		(
			mTitleInfo->m_TableInfo[iID].m_szMaleTitle,
			ThirdFile->Search_Posistion(i, TitleNameMale)->pString,
			sizeof(mTitleInfo->m_TableInfo[iID].m_szMaleTitle) - 1
		);

		strncpy
		(
			mTitleInfo->m_TableInfo[iID].m_szFemaleTitle,
			ThirdFile->Search_Posistion(i, TitleNameFemale)->pString,
			sizeof(mTitleInfo->m_TableInfo[iID].m_szFemaleTitle) - 1
		);

		mTitleInfo->m_TableInfo[iID].m_uTime = ThirdFile->Search_Posistion(i, TitleTime)->iValue;
		mTitleInfo->m_TableInfo[iID].m_iBuffID = ThirdFile->Search_Posistion(i, TitleBuff)->iValue;
		mTitleInfo->m_TableInfo[iID].m_iSuitID = ThirdFile->Search_Posistion(i, TitleSuitID)->iValue;
	}

	mTitleCombination = new TitleCombination;
}

void DataManager::loadBeastTable()
{
	mBeastDataTable = new _BEASTIE_DATA_TABLE;

	enum
	{
		BEASTIE_ID = 0,
		MODEL_ID = 1,
		HEAD_IMAGE = 2,
		SCENE_ID = 3,
		RESPAWN_TIME = 13,
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

	mBeastDataTable->m_uCount = iTableCount;

	for (int32 i = 0; i < iTableCount; ++i)
	{
		mBeastDataTable->m_BeastieItem[i].m_nSceneId = ThirdFile.Search_Posistion(i, SCENE_ID)->iValue;
		mBeastDataTable->m_BeastieItem[i].m_uBeastieId = ThirdFile.Search_Posistion(i, BEASTIE_ID)->iValue;

		strncpy
		(
			mBeastDataTable->m_BeastieItem[i].m_szName,
			ThirdFile.Search_Posistion(i, BEASTIE_NAME)->pString,
			sizeof(mBeastDataTable->m_BeastieItem[i].m_szName) - 1
		);

		mBeastDataTable->m_BeastieItem[i].m_PosX = ThirdFile.Search_Posistion(i, POS_X)->fValue;
		mBeastDataTable->m_BeastieItem[i].m_PosZ = ThirdFile.Search_Posistion(i, POS_Z)->fValue;
		mBeastDataTable->m_BeastieItem[i].m_nItemId = ThirdFile.Search_Posistion(i, ITEM_ID)->iValue;
		mBeastDataTable->m_BeastieItem[i].m_fSpeed = ThirdFile.Search_Posistion(i, SPEED)->fValue;
		mBeastDataTable->m_BeastieItem[i].m_nModelId = ThirdFile.Search_Posistion(i, MODEL_ID)->iValue;
		mBeastDataTable->m_BeastieItem[i].m_RespawnTime = ThirdFile.Search_Posistion(i, RESPAWN_TIME)->iValue;
		mBeastDataTable->m_BeastieItem[i].m_fDirection = ThirdFile.Search_Posistion(i, DIRCTION)->fValue;
		mBeastDataTable->m_BeastieItem[i].m_nType = ThirdFile.Search_Posistion(i, TYPE)->iValue;
	}
}


void ReadHorseSkillSlot
(
	SplitStringLevelOne* pSplitL1,
	SplitStringLevelTwo* pSplitL2,
	const char* pSplitString,
	_HORSE_SKILL_SLOT& oSlot
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
	for (int32 iSkill = 0; iSkill < iLineCount; ++iSkill)
	{
		oSlot.m_aSkillSlot[iSkill] = atoi(pSplitL2->GetResultLine(iSkill));
	}

	__UNGUARD__
}

enum HorseAttrData
{
	HorseDataID = 0,
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
	HorseSkillRealizationID = HorseInitSkillTbl + 24,
	HorseScriptID,
	HorseDataCount
};

void DataManager::loadHorseAttrTable()
{
	TABFile* table = new TABFile(0);
	TABFile& ThirdFile = *table;
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_ATTR);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	mHorseAttrTable = new _HORSE_ATTR_TBL;


	mHorseAttrTable->m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char* pSplitString = NULL;
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(HorseDataCount == iColumnCount);

	for (int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = ThirdFile.Search_Posistion(i, HorseDataID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iType >= MAX_HORSE_TYPE)
		{
			KCheckEx(FALSE, "马表中填写的马ID号超出范围");
			continue;
		}

		mHorseAttrTable->m_aHorseTbl[iType].m_nDataID = iType;
		strncpy
		(
			mHorseAttrTable->m_aHorseTbl[iType].m_sName,
			ThirdFile.Search_Posistion(i, HorseName)->pString,
			sizeof(mHorseAttrTable->m_aHorseTbl[iType].m_sName) - 1
		);
		mHorseAttrTable->m_aHorseTbl[iType].m_iLevel = ThirdFile.Search_Posistion(i, HorseLevel)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iTakeLevel = ThirdFile.Search_Posistion(i, HorseTakeLevel)->iValue;

		// rj 2010-8-23 天赋及个人等级初始化表值
		mHorseAttrTable->m_aHorseTbl[iType].m_iReqInherenceLevel = ThirdFile.Search_Posistion(i, HorseReqInherenceLevel)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iReqPersonLevel = ThirdFile.Search_Posistion(i, HorseReqPersonLevel)->iValue;


		mHorseAttrTable->m_aHorseTbl[iType].m_iReturnToChildRandSum = ThirdFile.Search_Posistion
		(
			i,
			HorseReturnToChildRandSum
		)->iValue;
		if (mHorseAttrTable->m_aHorseTbl[iType].m_iReturnToChildRandSum > 0)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseReturnToChildID)->pString;
			mHorseAttrTable->m_aHorseTbl[iType].m_iReturnToChildIDCount = CommonStringSplit
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				MaxReturnToChildIDNum,
				mHorseAttrTable->m_aHorseTbl[iType].m_aReturnToChildID
			);

			pSplitString = ThirdFile.Search_Posistion(i, HorseReturnToChildRandRate)->pString;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ratecount = CommonStringSplit
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				MaxReturnToChildIDNum,
				mHorseAttrTable->m_aHorseTbl[iType].m_aReturnToChildRandRate
			);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (mHorseAttrTable->m_aHorseTbl[iType].m_iReturnToChildIDCount != ratecount)
			{
			
			}

			/*~~~~~~~~~~~~~~~~*/
			int32	seedsum = 0;
			/*~~~~~~~~~~~~~~~~*/

			for (int32 tochild = 0; tochild < ratecount; tochild++)
			{
				seedsum += mHorseAttrTable->m_aHorseTbl[iType].m_aReturnToChildRandRate[tochild];
			}

			if (seedsum != mHorseAttrTable->m_aHorseTbl[iType].m_iReturnToChildRandSum)
			{
				
			}
		}

		pSplitString = ThirdFile.Search_Posistion(i, HorseChildID)->pString;
		mHorseAttrTable->m_aHorseTbl[iType].m_iChildIDCount = CommonStringSplit
		(
			&oSplitL1,
			&oSplitL2,
			pSplitString,
			MaxReturnToChildIDNum,
			mHorseAttrTable->m_aHorseTbl[iType].m_aChildID
		);

		mHorseAttrTable->m_aHorseTbl[iType].m_bCanMating = ThirdFile.Search_Posistion(i, HorseCanMating)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_bCanCompose = ThirdFile.Search_Posistion(i, HorseCanCompose)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_bVariation = ThirdFile.Search_Posistion
		(
			i,
			HorseIsVariation
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_byGeneration = ThirdFile.Search_Posistion
		(
			i,
			HorseGeneration
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iLifeHaveMaster = ThirdFile.Search_Posistion
		(
			i,
			HorseLifeHaveMaster
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_LifeNoMaster = ThirdFile.Search_Posistion
		(
			i,
			HorseLifeNoMaster
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iStrengthMin = ThirdFile.Search_Posistion
		(
			i,
			HorseStrengthMin
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iStrengthMax = ThirdFile.Search_Posistion
		(
			i,
			HorseStrengthMax
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSmartnessMin = ThirdFile.Search_Posistion
		(
			i,
			HorseSmartnessMin
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSmartnessMax = ThirdFile.Search_Posistion
		(
			i,
			HorseSmartnessMax
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMindMin = ThirdFile.Search_Posistion(i, HorseMindMin)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMindMax = ThirdFile.Search_Posistion(i, HorseMindMax)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iConstitutionMin = ThirdFile.Search_Posistion
		(
			i,
			HorseConstitutionMin
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iConstitutionMax = ThirdFile.Search_Posistion
		(
			i,
			HorseConstitutionMax
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iStrengthMinPer = ThirdFile.Search_Posistion
		(
			i,
			HorseStrengthMinPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iStrengthMaxPer = ThirdFile.Search_Posistion
		(
			i,
			HorseStrengthMaxPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSmartnessMinPer = ThirdFile.Search_Posistion
		(
			i,
			HorseSmartnessMinPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSmartnessMaxPer = ThirdFile.Search_Posistion
		(
			i,
			HorseSmartnessMaxPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMindMinPer = ThirdFile.Search_Posistion
		(
			i,
			HorseMindMinPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMindMaxPer = ThirdFile.Search_Posistion
		(
			i,
			HorseMindMaxPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iConstitutionMinPer = ThirdFile.Search_Posistion
		(
			i,
			HorseConstitutionMinPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iConstitutionMaxPer = ThirdFile.Search_Posistion
		(
			i,
			HorseConstitutionMaxPer
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSavvyMin = ThirdFile.Search_Posistion(i, HorseSavvyMin)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iSavvyMax = ThirdFile.Search_Posistion(i, HorseSavvyMax)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_GenGuMin = ThirdFile.Search_Posistion(i, HorseGenGuMin)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_GenGuMax = ThirdFile.Search_Posistion(i, HorseGenGuMax)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iPullulationRateMin = ThirdFile.Search_Posistion
		(
			i,
			HorsePullulationRateMin
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iPullulationRateMax = ThirdFile.Search_Posistion
		(
			i,
			HorsePullulationRateMax
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMoveSpeed = ThirdFile.Search_Posistion(i, HorseMoveSpeed)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iBehaveID = ThirdFile.Search_Posistion(i, HorseBehaveID)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iMountID = ThirdFile.Search_Posistion(i, HorseMountID)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iInitSkillRandSum = ThirdFile.Search_Posistion
		(
			i,
			HorseInitSkillRandSum
		)->iValue;
		for (int32 iSlot = 0; iSlot < PET_MAX_SKILL_COUNT; ++iSlot)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseInitSkillTbl + iSlot * 2)->pString;
			ReadHorseSkillSlot
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				mHorseAttrTable->m_aHorseTbl[iType].m_oSkillSlot[iSlot]
			);

			pSplitString = ThirdFile.Search_Posistion(i, HorseInitSkillTbl + iSlot * 2 + 1)->pString;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ratecount = CommonStringSplit
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				MaxSlotSkillNum,
				mHorseAttrTable->m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_aSkillRandRate
			);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (ratecount != mHorseAttrTable->m_aHorseTbl[iType].m_oSkillSlot[iSlot].m_iSkillCount)
			{
				
			}
			else
			{
				mHorseAttrTable->m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_iSkillCount = ratecount;
			}

			/*~~~~~~~~~~~~~~~~*/
			int32	ratesum = 0;
			/*~~~~~~~~~~~~~~~~*/

			for (int32 i = 0; i < ratecount; i++)
			{
				ratesum += mHorseAttrTable->m_aHorseTbl[iType].m_oSillRandRate[iSlot].m_aSkillRandRate[i];
			}

			if (ratesum > mHorseAttrTable->m_aHorseTbl[iType].m_iInitSkillRandSum)
			{
			}
		}

		mHorseAttrTable->m_aHorseTbl[iType].m_iRealizationID = ThirdFile.Search_Posistion
		(
			i,
			HorseSkillRealizationID
		)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_iScriptID = ThirdFile.Search_Posistion(i, HorseScriptID)->iValue;
		KCheck(mHorseAttrTable->m_aHorseTbl[iType].m_iScriptID <= 0 || mHorseAttrTable->m_aHorseTbl[iType].m_iScriptID >= 100000);
		mHorseAttrTable->m_aHorseTbl[iType].m_iKindType = ThirdFile.Search_Posistion(i, HorseKindType)->iValue;
		mHorseAttrTable->m_aHorseTbl[iType].m_bIsFixedHold = ThirdFile.Search_Posistion
		(
			i,
			HorseIsFixedHold
		)->iValue;
	}
}



void DataManager::loadHorseSkillTable()
{
	enum HorseSkillRealData
	{
		HorseRealDataID = 0,
		HorseDataCount,
		HorseSkillSlot,
		HorseSkillDataCount = 8
	};

	mHorseSkillTable = new _HORSE_SKILL_TBL;
	TABFile* table = new TABFile(0);
	TABFile& ThirdFile = *table;
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_HORSE_SKILL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();


	mHorseSkillTable->m_iCount = iTableCount;

	const char* pSplitString = NULL;

	KCheck(HorseSkillDataCount == iColumnCount);

	for (int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = ThirdFile.Search_Posistion(i, HorseRealDataID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iType >= MAX_HORSE_SKILL_REALIZATION)
		{
			KCheckEx(FALSE, "马技能表中填写的ID号超出范围");
			continue;
		}

		mHorseSkillTable->m_aHorseSkillRealizationTbl[iType].m_iSkillRealizationID = iType;
		mHorseSkillTable->m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount = ThirdFile.Search_Posistion
		(
			i,
			HorseDataCount
		)->iValue;
		if (mHorseSkillTable->m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount > MaxSlotNum)
			mHorseSkillTable->m_aHorseSkillRealizationTbl[iType].m_iSkillSlotCount = MaxSlotNum;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for (int32 iSlot = 0; iSlot < PET_MAX_APPER_COUNT; ++iSlot)
		{
			pSplitString = ThirdFile.Search_Posistion(i, HorseSkillSlot + iSlot)->pString;
			ReadHorseSkillSlot
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				mHorseSkillTable->m_aHorseSkillRealizationTbl[iType].m_oSkillSlot[iSlot]
			);
		}
	}
}

void DataManager::loadHorseLevelupTable()
{
	mHorseLevelupTable = new SHorseLevelupTab;
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_PET_LEVELUP);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mHorseLevelupTable->m_iCount = iTableCount;

	/*~~~~~~~~~~~~~~~*/
	int32	iLevel = 0;
	int32	iExp = 0;
	/*~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < iTableCount; i++)
	{
		iLevel = ThirdFile.Search_Posistion(i, 0)->iValue;

		iExp = ThirdFile.Search_Posistion(i, 1)->iValue;
		mHorseLevelupTable->m_Table[iLevel] = iExp;
	}
}

void DataManager::loadHorsePerlimitTable()
{

	mHorsePerlimitTable = new _HORSE_PER_LIMIT_TBL;
	TABFile	ThirdFile(0);
	BOOL			ret = ThirdFile.OpenFromTXT(FILE_HORSE_ZIZHI);
	int32			iTableCount = ThirdFile.GetRecordsNum();
	int32			iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount <= MAX_HORSE_GENRATION && "FILE_HORSE_ZIZHI");
	mHorsePerlimitTable->m_iCount = iTableCount;

	for (int32 i = 0; i < iTableCount; ++i)
	{
		mHorsePerlimitTable->m_aLimit[i] = ThirdFile.Search_Posistion(i, 0)->iValue;
	}
}

void DataManager::loadGatherPointTable()
{
	enum GrowPointTBLData
	{
		TBIndex = 0,
		TBName = 1,
		TBOpenAbility = 2,
		TBMesh = 3,
		TBOpenTask = 4,
		TBTips = 5,
		TBOpenTime = 6,
		TBScriptID = 7,
		TBOpenAnim = 8
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GROWPOINT);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();

	mGatherPointTable = new _GATHER_POINT_INFO_TAB;

	mGatherPointTable->m_Count = iTableCount;
	mGatherPointTable->m_Table = new _GATHER_POINT_INFO[iTableCount];
	for (int32 i = 0; i < iTableCount; i++)
	{
		mGatherPointTable->m_Table[i].m_GrowPointIndex = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		mGatherPointTable->m_Table[i].m_OpenTime = ThirdFile.Search_Posistion(i, TBOpenTime)->iValue;
		mGatherPointTable->m_Table[i].m_OpenAnim = ThirdFile.Search_Posistion(i, TBOpenAnim)->iValue;
		mGatherPointTable->m_Table[i].m_OpenAbility = ThirdFile.Search_Posistion(i, TBOpenAbility)->iValue;
		mGatherPointTable->m_Table[i].m_ScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
	}
}

bool DataManager::LoadCampAndStandDataMgr()
{
	return mCampAndStandDataMgr.InitFromDB(FILE_CAMP_AND_STAND);
}
