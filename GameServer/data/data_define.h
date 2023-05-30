#pragma once
#include <stdint.h>

#include "Define.h"
#include "DefineAttr.h"
#include "share/TAB/TabDefine_Map_Monster.h"


struct MonsterProperty
{
	bool	m_Used;
	int32_t	m_Type;
	char	m_Name[NPC_NAME_LEN];
	int32_t	m_CannotFight;
	int32_t	m_Level;
	int32_t	m_RespawnTime;
	int32_t	m_BaseExp;
	int32_t	m_OutLook;
	int32_t	m_BaseAI;
	int32_t	m_ExtAI;
	int32_t	m_Camp;
	float	m_DropSearchRange;
	int32_t	m_SearchTeamCount;
	int32_t	m_MonsterDropSetCount;
	int32_t* m_MonsterDropItemSetID;
	int32_t	m_nMonsterDropRate;
	int32_t	m_MinDamagePercent;
	int32_t	m_CanHandle;
	int32_t	m_FriendValue;
	int32_t	m_WalkSpeed;
	int32_t	m_BossFlag;
	int32_t	m_SnapSkillImmID;
	int32_t	m_DurationSkillImmID;
	int32_t	m_AttackAnimTime;
	int32_t	m_AttackCooldownTime;
	int32_t	m_ScriptID;
	int32_t	m_WeaponID[MONSTER_EXT_ATTR_ENUM_SIZE];
	int32_t	m_HorseID[MONSTER_EXT_ATTR_ENUM_SIZE];
	int32_t	m_iWeaponCount;
	int32_t	m_iHorseCount;

	int32_t	m_aHorseDropID[MaxHorseDropNum];
	int32_t	m_iHorseDropCount;
	int32_t	m_Table[CPROPERTY_LEVEL2_NUMBER];
};


struct MonsterAIData
{
	std::vector<vector<uint32_t>> mAIData;

	int32_t get(uint32_t aiType, uint32_t aiParam);
};

struct ProfessionPropertyTab
{
	int32	m_Table[AINFOTYPE_NUMBER][PROFESSION_NUMBER];

	ProfessionPropertyTab()
	{
		memset(m_Table, 0, sizeof(int32) * AINFOTYPE_NUMBER * PROFESSION_NUMBER);
	};

	int32 Get(uint32 AttrInfo, uint32 Profession)
	{
		KCheck(AttrInfo < AINFOTYPE_NUMBER&& Profession < PROFESSION_NUMBER);
		return m_Table[AttrInfo][Profession];
	};
};

struct Player_PROPERTY_LEVELUP_TAB
{
	int32	m_Table[CPROPERTY_LEVEL_NUMBER][PROFESSION_NUMBER][MAX_TABLE_DEFINE_LEVEL + 1];

	Player_PROPERTY_LEVELUP_TAB()
	{
		memset(m_Table, 0, sizeof(int32) * CPROPERTY_LEVEL_NUMBER * PROFESSION_NUMBER * MAX_TABLE_DEFINE_LEVEL);
	}

	int32 Get(uint32_t Attr, uint32_t Profession, uint32_t iLevel)
	{
		KCheck(Attr < CPROPERTY_LEVEL_NUMBER&& Profession < PROFESSION_NUMBER&& iLevel <= MAX_TABLE_DEFINE_LEVEL);
		return m_Table[Attr][Profession][iLevel];
	}

	void Set(uint32_t Attr, uint32_t Profession, uint32_t iLevel, int32 iValue)
	{
		KCheck(Attr < CPROPERTY_LEVEL_NUMBER&& Profession < PROFESSION_NUMBER&& iLevel <= MAX_TABLE_DEFINE_LEVEL);
		m_Table[Attr][Profession][iLevel] = iValue;
	}
};

struct TitleInfo
{
	STitle::TITLE_TABLE_INFO	m_TableInfo[MAX_TITLE_SIZE];

	TitleInfo()
	{
	};
	STitle::TITLE_TABLE_INFO*
		Get(uint32 uTitileID)
	{
		KCheck(uTitileID < MAX_TITLE_SIZE);
		return &m_TableInfo[uTitileID];
	};
};

struct TitleCombination
{
	STitle::TITLE_COMBINATION	m_TableCombination[MAX_TITLE_SIZE];

	TitleCombination()
	{
	};

	STitle::TITLE_COMBINATION*
		Get(uint32 uCombinationID)
	{
		KCheck(uCombinationID < MAX_TITLE_SIZE);
		return &m_TableCombination[uCombinationID];
	};
};

struct SMonsterWeaponAndSkill
{
	enum { MWAS_MAX_LEVEL = 9 };

	int32_t m_iIndex;

	int32_t m_iWeaponID;

	int32_t m_aSkillLevelIndex[MWAS_MAX_LEVEL];

	int32_t m_iSkillLevelIndexCount;

	int32_t m_aSkillLevel[MWAS_MAX_LEVEL];
};

struct SMonsterWeaponAndSkillTable
{
	enum { MWAST_MAX_NUM = 1500 };
	int32 m_Count;
	SMonsterWeaponAndSkill m_aWeaponSkill[MWAST_MAX_NUM];
	SMonsterWeaponAndSkillTable()
	{
		memset(this, 0, sizeof(SMonsterWeaponAndSkillTable));
	}
};
