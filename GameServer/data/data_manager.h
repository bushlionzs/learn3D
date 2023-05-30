#pragma once

#include "data_define.h"
#include "skill/Spell_EffectLogicManager.h"
#include "Camp.h"
struct NPC_QUEST;
struct _QUEST_DATA_t;
class  SpellTemplateData;
class SpellInstanceData;
class BaseSkill;
class EffectData;
class IDCollection;
class BaseSpellLogic;
class ImpactSEData_T;
struct _BEASTIE_DATA_TABLE;
struct _HORSE_ATTR_TBL;
struct _HORSE_SKILL_TBL;
struct SHorseLevelupTab;
struct _HORSE_PER_LIMIT_TBL;
struct _GATHER_POINT_INFO;
struct _GATHER_POINT_INFO_TAB;

class DataManager: public GameSingleton<DataManager>
{
public:
	typedef FixedFlag<MAX_CHAR_QUEST_DATA_NUM> FlagMD;
private:
	std::unordered_map<uint32_t, MonsterProperty*> mMonsterPropertyMap;

	TABFile* mMonsterPropertyTable = nullptr;
	std::unordered_map<int32_t, _QUEST_DATA_t*> mQuestMap;
	std::unordered_map<int32_t, _QUEST_DATA_t*> mQuestScriptMap;
	std::unordered_map<int32_t, NPC_QUEST*> mNpcQuestMap;
	std::unordered_map<int32_t, SpellTemplateData*> mSpellTemplateMap;
	std::unordered_map<int32_t, SpellInstanceData*> mSpellInstanceMap;
	std::unordered_map<int32_t, EffectData*> mEffectDataMap;
	std::unordered_map<int32_t, IDCollection*> mCollectionMap;
	std::unordered_map<int32_t, ImpactSEData_T*> mImpactDescMap;
	TitleInfo* mTitleInfo = nullptr;
	TitleCombination* mTitleCombination = nullptr;
	struct ProfessionPropertyTab* mProfessionPropertyTab = nullptr;
	struct Player_PROPERTY_LEVELUP_TAB* mPropertyLevelUp = nullptr;
	SkillLogicManager_T mSpellLogicList;
	ProfessionLogicManager_T	mProfessionLogicList;
	ImpactLogicManager_T		mEffectLogicList;
	SpecialObjLogicManager_T	mSpecialObjLogicList;

	TemplateManager<SpecialObjData_T> mSpecialObjDataMgr;
	MonsterAIData mMonsterAI;
	
	FlagMD	m_FlagMDClientFilter;

	SMonsterWeaponAndSkillTable* mMonsterWeaponAndSkillTable = nullptr;

	_BEASTIE_DATA_TABLE* mBeastDataTable = nullptr;
	_HORSE_ATTR_TBL* mHorseAttrTable = nullptr;
	_HORSE_SKILL_TBL* mHorseSkillTable = nullptr;
	SHorseLevelupTab* mHorseLevelupTable = nullptr;
	_HORSE_PER_LIMIT_TBL* mHorsePerlimitTable = nullptr;
	_GATHER_POINT_INFO_TAB* mGatherPointTable = nullptr;
	CampAndStandDataMgr mCampAndStandDataMgr;
public:
	DataManager();
	~DataManager();

	bool initialize();

	MonsterProperty* getMonsterProperty(uint32_t id);
	int32_t getMonsterProperty(uint32_t id, uint32_t index);
	_QUEST_DATA_t* getQuestByID(int32_t questID);
	const FlagMD& getFlagMDClientFilter();
	NPC_QUEST* getNpcQuest(int32_t objID);

	MonsterAIData* getMonsterAIData();

	SpellTemplateData* getSpellTemplate(uint32_t id);
	SpellInstanceData* getSpellInstance(uint32_t id);
	EffectData* getEffectData(uint32_t id);


	BaseSkill* getSkill(uint32_t id);

	_HORSE_ATTR* getHorseAttr(uint32_t id);
	_HORSE_ATTR_TBL* getHorseAttrTable();
	_HORSE_SKILL_TBL* getHorseSkillTable();
	SHorseLevelupTab* getHorseLevelupTable();
	_HORSE_PER_LIMIT_TBL* getHorsePerlimitTable();

	IDCollection* getCollection(uint32_t id);

	int32_t getProfessionProperty(int32_t ainfotype, int32_t profession);

	int32_t getAttrLevelUpValue(int32_t arrtype, int32_t profession, int32_t level);

	BaseSpellLogic* getSpellLogicById(int32_t id);
	SpecialObjectLogic* getSpecialObjectLogicById(int32_t id);

	const SpecialObjData_T* getSpecialObjectDataById(int32_t id);

	const EffectLogic* getEffectLogic(int32_t id);

	const Profession* getProfessionLogic(int32_t id);

	const ImpactSEData_T* getImapctSEData(int32_t id);
	TitleInfo& getTitleInfo();

	TitleCombination& getTitleCombination();

	SMonsterWeaponAndSkillTable* getMonsterWeaponAndSkillTable();

	_BEASTIE_DATA_TABLE* getBeastTable();

	_GATHER_POINT_INFO_TAB* getGatherPointTable();
	CampAndStandDataMgr* getCampAndStandDataMgr();

private:
	bool loadMonsterData();
	void readWeaponID
	(
		SplitStringLevelOne* pSplitL1,
		SplitStringLevelTwo* pSplitL2,
		const char* pSplitString,
		MonsterProperty* monsterProperty
	);
	void readHorseID
	(
		SplitStringLevelOne* pSplitL1,
		SplitStringLevelTwo* pSplitL2,
		const char* pSplitString,
		MonsterProperty* monsterProperty
	);

	void loadMonsterSkillTable();
	void loadQuestList();
	void loadFlagMDClientFilter();
	void loadNpcQuest();
	void loadMonsterAIData();
	void loadSpellTemplate();
	void loadEffectData();
	void loadCollectionData();
	void loadProfessionProperty();
	void loadPropertyLevelUp();
	void loadSpellLogic();
	void loadImpactSE();
	void loadTitle();
	void loadBeastTable();
	void loadHorseAttrTable();
	void loadHorseSkillTable();
	void loadHorseLevelupTable();
	void loadHorsePerlimitTable();
	void loadGatherPointTable();
	bool LoadCampAndStandDataMgr();
	
};