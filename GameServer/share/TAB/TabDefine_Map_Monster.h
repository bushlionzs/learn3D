#ifndef __TAB_DEFINE_MAP_MONSTER_H__
#define __TAB_DEFINE_MAP_MONSTER_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "StructPet.h"
#include "TabStruct.h"
#include "gameobject/Monster.h"

// 加载怪物表
class TableInit_Map_Monster
{
public:
	TableInit_Map_Monster();
	~TableInit_Map_Monster();

	BOOL	Init();

private:
	// 加载怪物扩展属性表
	void	Init_MonsterAttrExTable();
	// 加载战车扩展属性表
	void	Init_BusAttrExTable();
	// 加载怪物ai表
	void	LoadMonsterAITable();
	// 加载怪物技能表
	void	LoadMonsterSkillTable();
	// 怪物讲话表
	void	LoadMonsterSpeakTable();
	// 随机怪物表
	void	LoadRandomMonster();

private:

	void	ReadHorseID
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			int32 iType
		);

	void	ReadWeaponID
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			int32 iType
		);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MONSTER_EXT_ATTR_ENUM_SIZE = 100;

struct SMonsterExtAttr
{
	BOOL	m_Used;
	int32	m_Type;
	char	m_Name[NPC_NAME_LEN];
	int32	m_CannotFight;
	int32	m_Level;
	int32	m_RespawnTime;
	int32	m_BaseExp;
	int32	m_OutLook;
	int32	m_BaseAI;
	int32	m_ExtAI;
	int32	m_Camp;
	float	m_DropSearchRange;
	int32	m_SearchTeamCount;
	int32	m_MonsterDropSetCount;
	int32	*m_MonsterDropItemSetID;
	int32	m_nMonsterDropRate;
	int32	m_MinDamagePercent;
	int32	m_CanHandle;
	int32	m_FriendValue;
	int32	m_WalkSpeed;
	int32	m_BossFlag;
	int32	m_SnapSkillImmID;
	int32	m_DurationSkillImmID;
	int32	m_AttackAnimTime;
	int32	m_AttackCooldownTime;
	int32	m_ScriptID;
	int32	m_WeaponID[MONSTER_EXT_ATTR_ENUM_SIZE];
	int32	m_HorseID[MONSTER_EXT_ATTR_ENUM_SIZE];
	int32	m_iWeaponCount;
	int32	m_iHorseCount;

	int32	m_aHorseDropID[MaxHorseDropNum];
	int32	m_iHorseDropCount;
	int32	m_Table[CPROPERTY_LEVEL2_NUMBER];
};

struct SMonsterAttrexTab
{
	SMonsterExtAttr	m_TableExt[MAXTYPE_NUMBER];
	uint32				m_Count;
	uint32				m_MaxType;

	SMonsterAttrexTab()
	{
		memset(m_TableExt, 0, sizeof(SMonsterExtAttr) * MAXTYPE_NUMBER);
		m_Count = 0;
	};

	static int32 CompareMonsterAttrExtTB(const void *pArg1, const void *pArg2)
	{
		__GUARD__ 
		int32 Serial1, Serial2;
		Serial1 = ((SMonsterExtAttr *) pArg1)->m_Type;
		Serial2 = ((SMonsterExtAttr *) pArg2)->m_Type;

		if(Serial1 > Serial2)
			return 1;
		else if(Serial1 < Serial2)
			return -1;
		else
			return 0;
		
		__UNGUARD__ 
		return 0;
	}

	int32 Get(uint32 MonsterType, uint32 AttrEx)
	{
		__GUARD__
		
		KCheck( AttrEx<CPROPERTY_LEVEL2_NUMBER);
		SMonsterExtAttr *pAttr = GetExtAttr (MonsterType); 
		if (NULL != pAttr)
		{
			return pAttr->m_Table[AttrEx];
		}

		__UNGUARD__ 
		return 0;
	}

	SMonsterExtAttr *GetExtAttr (uint32 MonsterType)
	{
		__GUARD__
			
		SMonsterExtAttr oAttr; oAttr.m_Type = MonsterType; 
		SMonsterExtAttr *pResult =
			(SMonsterExtAttr *) bsearch( &oAttr, 
										m_TableExt, 
										m_Count, 
										sizeof(SMonsterExtAttr),
										(int32 (*) (const void *, const void *)) CompareMonsterAttrExtTB );
		if (pResult != NULL)
		{
			return pResult;
		}
		
		__UNGUARD__
		return NULL;
	}
			
	int32 Count ()
	{
		return m_Count;
	}
		
}; 
extern SMonsterAttrexTab g_MonsterPropertyExTab; 


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32 BUS_EXT_ATTR_ENUM_SIZE = 100; 
struct BUS_EXT_ATTR
{
	BOOL m_Used; 
	int32 m_Type; 
	char m_Name[NPC_NAME_LEN]; 
	int32 m_CannotFight; 
	int32 m_Level; 
	int32 m_RespawnTime; 
	int32 m_BaseExp; 
	int32 m_OutLook; 
	int32 m_BaseAI; 
	int32 m_ExtAI; 
	int32 m_Camp; 
	float m_DropSearchRange; 
	int32 m_SearchTeamCount; 
	int32 m_MonsterDropItemSetID; 
	int32 m_nMonsterDropRate; 
	int32 m_MinDamagePercent; 
	int32 m_CanHandle; 
	int32 m_FriendValue; 
	int32 m_WalkSpeed; 
	int32 m_BossFlag; 
	int32 m_SnapSkillImmID; 
	int32 m_DurationSkillImmID; 
	int32 m_AttackAnimTime; 
	int32 m_AttackCooldownTime; 
	int32 m_ScriptID; 
	int32 m_WeaponID[BUS_EXT_ATTR_ENUM_SIZE]; 
	int32 m_HorseID[BUS_EXT_ATTR_ENUM_SIZE]; 
	int32 m_iWeaponCount; 
	int32 m_iHorseCount; 
	int32 m_aHorseDropID[MaxHorseDropNum]; 
	int32 m_iHorseDropCount; 
	int32 m_Table[CPROPERTY_LEVEL2_NUMBER]; 
	int32 m_iPassiveSkill_1; 
	int32 m_iPassiveSkill_2; 
	int32 m_iPassiveSkill_3; 
	int32 m_iPassiveSkill_4; 
	int32 m_iPassiveSkill_5; 
	char m_Title[NPC_TITLE_LEN]; 
	BOOL m_IsSysControl; 
	int32 m_iMemberNum; 
	BOOL m_IsShowPlayer; 
	int32 m_iSkill_1; 
	int32 m_iSkill_2; 
	int32 m_iSkill_3; 
	int32 m_iSkill_4; 
	int32 m_iSkill_5; 
	int32 m_iBusType; 
	int32 m_PKMode; 
	int32 m_MinValidFollowDist; 
	int32 m_MaxValidFollowDist;
};

struct _BUS_ATTREX_TBL
{
	BUS_EXT_ATTR m_TableExt[BUS_MAX_TYPE_NUMBER]; 
	uint32 m_Count; 
	uint32 m_MaxType; 
	
	_BUS_ATTREX_TBL ()
	{
		memset (m_TableExt, 0, sizeof (BUS_EXT_ATTR) *BUS_MAX_TYPE_NUMBER); 
		m_Count = 0;
	}
	
	static int32 CompareBusAttrExtTB (const void *pArg1, const void *pArg2)
	{
		__GUARD__ 
		int32 Serial1, Serial2; 
		Serial1 = ( (BUS_EXT_ATTR *) pArg1)->m_Type; 
		Serial2 = ( (BUS_EXT_ATTR *) pArg2)->m_Type; 
		if (Serial1 > Serial2)
			return 1;
		else if(Serial1 < Serial2)
			return -1;
		else
			return 0;
		__UNGUARD__ 
		return 0;
	}

	int32 Get(uint32 BusType, uint32 AttrEx)
	{
		__GUARD__		
		
		KCheck(AttrEx < CPROPERTY_LEVEL2_NUMBER);
		BUS_EXT_ATTR *pAttr = GetExtAttr(BusType);
		if(NULL != pAttr)
		{
			return pAttr->m_Table[AttrEx];
		}

		__UNGUARD__ 
		return 0;
	}

	BUS_EXT_ATTR *GetExtAttr(uint32 BusType)
	{
		__GUARD__ BUS_EXT_ATTR	oAttr;
		oAttr.m_Type = BusType;

		BUS_EXT_ATTR *pResult = (BUS_EXT_ATTR *) bsearch
			(
				&oAttr,
				m_TableExt,
				m_Count,
				sizeof(BUS_EXT_ATTR),
				(int32(*) (const void *, const void *)) CompareBusAttrExtTB
			);

		if(pResult != NULL)
		{
			return pResult;
		}

		__UNGUARD__ 
		return NULL;
	}

	int32 Count()
	{
		return m_Count;
	};
};
extern _BUS_ATTREX_TBL			g_BusAttrExTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SMonsterBHVTab
{
	int32	m_Table[MAXAI_NUMBER][BHVPARAM_NUMBER];
	int32	m_Count;

	SMonsterBHVTab()
	{
		memset(m_Table, 0, sizeof(int32) * MAXAI_NUMBER * BHVPARAM_NUMBER);
		m_Count = 0;
	};

	int32 Get(uint32 AIType, uint32 AIParam)
	{
		if(!(AIType < (uint32) m_Count && AIParam < BHVPARAM_NUMBER))
		{
			char szMsg[128] = { 0 };
			tsnprintf_s( szMsg, 128, "！！策划填表错误或程序使用LuaFunction_CreateMonster时指定的AI类型错误！！" );
			KCheckEx(AIType < (uint32) m_Count && AIParam < BHVPARAM_NUMBER, szMsg);
		}
		return m_Table[AIType][AIParam];
	};

	int32 Count()
	{
		return m_Count;
	};
};
extern SMonsterBHVTab	g_MonsterBehaviorTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct MonsterWeaponAndSkill
{
	enum { MWAS_MAX_LEVEL = 9 };

	int32 m_iIndex;

	int32 m_iWeaponID;

	int32 m_aSkillLevelIndex[MWAS_MAX_LEVEL];

	int32 m_iSkillLevelIndexCount;

	int32 m_aSkillLevel[MWAS_MAX_LEVEL];
};

struct MonsterWeaponAndSkillTable
{
	enum { MWAST_MAX_NUM = 1500 };
	int32 m_Count;
	MonsterWeaponAndSkill m_aWeaponSkill[MWAST_MAX_NUM];
	MonsterWeaponAndSkillTable()
	{
		memset(this, 0, sizeof(MonsterWeaponAndSkillTable));
	}
};
extern MonsterWeaponAndSkillTable	g_MonsterWeaponAndSkill;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SMonsterSpeakTab
{
	struct MonsterSpeakItem
	{
		int32	nSpeakID;
		char	szSpeakContent[MAX_MONSTERSPEAK_CONTENT];
	};

	MonsterSpeakItem	m_Table[MAXCHAT_NUMBER];
	int32				m_NumberOfType[MAXCHATTYPE_NUMBER];
	int32				m_TypeCount;
	int32				m_Count;

	SMonsterSpeakTab()
	{
		memset(m_NumberOfType, 0, sizeof(int32) * MAXCHATTYPE_NUMBER);
		memset(m_Table, 0, sizeof(MonsterSpeakItem) * MAXCHAT_NUMBER);
		m_TypeCount = 0;
		m_Count = 0;
	};

	const char *Get(uint32 ChatType, int32 Index = -1)
	{
		if(-1 != Index && 0 < Index && m_Count > Index) return m_Table[Index].szSpeakContent;

		KCheck(ChatType < (uint32) m_TypeCount && ChatType > -1);
		if(ChatType < (uint32) m_TypeCount && ChatType > -1) return "error";

		int32 Offset = 0;
		for(uint32 i = 0; i < ChatType; i++)
		{
			Offset += m_NumberOfType[i];
		}

		int32 index = rand() % (m_NumberOfType[ChatType] + 1) + Offset;
		KCheck(index < m_Count);
		return m_Table[index].szSpeakContent;
	};

	int32 Count()
	{
		return m_Count;
	};

	int32 TypeCount()
	{
		return m_TypeCount;
	};
};
extern SMonsterSpeakTab	g_MonsterSpeakTab;

///////////////////////////////////////////随机怪配置/////////////////////////////////////////////////////

#define RANDOM_PERGROUP_MAXMONSTER	64
#define RANDOM_PERMAP_MAXGROUP		64

// 随机怪具体配置数据结构
struct RandomMonsterConfig
{
	_INIT_MONSTER_OBJECT m_MonsterConfig;
	MapID_t m_iSceneID;
	ID_t	m_iGroupID;

	RandomMonsterConfig()
	{
		m_iSceneID = -1;
		m_iGroupID = -1;
	}
};

// 随机怪分组数据结构
struct RandomMonsterGroup
{
	RandomMonsterConfig *m_paMonster[RANDOM_PERGROUP_MAXMONSTER];		// 本图本组随机怪配置数组
	uint32 m_uMonsterCount;											// 本图本组随机怪配置读取数量
    
	RandomMonsterGroup()
	{
		memset(this, 0, sizeof(RandomMonsterGroup));
	}
};

// 随机怪地图表示数据结构
struct RandomMonsterMap
{
	RandomMonsterGroup *m_paMonsterGroup[RANDOM_PERMAP_MAXGROUP];		// 本图随机怪配置组数组，索引为组 ID

	RandomMonsterMap()
	{
		memset(this, 0, sizeof(RandomMonsterMap));
	}
};

// 随机怪配置全局变量，索引为 SceneID
extern RandomMonsterMap *g_pRandomMonsterConfig[MAX_SCENE];

#endif