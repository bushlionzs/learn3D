#ifndef __TAB_DEFINE_MAP_QUEST_H__
#define __TAB_DEFINE_MAP_QUEST_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "TabStruct.h"
#include "IntegerHashMap.h"

class CGameTable;
// 任务表
class TableInit_Map_Quest
{
public:
	TableInit_Map_Quest();
	~TableInit_Map_Quest();

	BOOL	Init();
	const CGameTable* getTable(int nTable);
private:
	// 加载场景NPC
	void	LoadSceneMapNPCTable();
	// 加载obj_quest.tab
	void	Init_NPCQuestTable();
	//加载npc泡泡索引
	void	Init_NPCPaoPaoIndexTable();
	
	// 加载问答表
	void	LoadQuestionsAndAnswersTable();
	// 加载灯谜表
	void	LoadQuestDengmiTable();
	// 加载乌龙辞典
	void	LoadQuestWulongTable();
	// 加载猜谜表
	void	LoadQuestQuizTable();
	void	LoadQuestShituTable();

};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SCENE_MAP_NPC_t
{
	int32	m_Index;
	int32	m_SceneID;
	char	m_Name[NPC_NAME_LEN];
	float	m_PosX;
	float	m_PosZ;

	SCENE_MAP_NPC_t()
	{
		m_Index = 0;
		m_SceneID = -1;
		m_Name[0] = 0;
		m_PosX = 0;
		m_PosZ = 0;
	}
};
struct _SCENE_MAP_NPC_TBL
{
	SCENE_MAP_NPC_t *m_Table;
	int32		m_Count;

	_SCENE_MAP_NPC_TBL()
	{
		m_Table = 0;
		m_Count = 0;
	}
	SCENE_MAP_NPC_t *Get(int32 nIndex);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct NPC_QUEST
{
	int32	m_Type;
	int32	m_ScriptID;
	int32	m_EventCount;
	int32	m_EventList[MAX_NPC_EVENT];
	int32	m_QuestCount;
	int32	m_QuestList[MAX_NPC_EVENT];

	NPC_QUEST()
	{
		m_Type = 0;
		m_ScriptID = -1;
		m_EventCount = 0;
		m_QuestCount = 0;
		for(int32 i = 0; i < MAX_NPC_EVENT; i++)
		{
			m_EventList[i] = 0;
			m_QuestList[i] = 0;
		}
	}
};

#define NPC_EVENT_LENGTH	512
struct _NPC_QUEST_TBL
{
	NPC_QUEST	*m_Table;
	int32		m_Count;

	_NPC_QUEST_TBL()
	{
		m_Table = 0;
		m_Count = 0;
	}
	NPC_QUEST	*Get(int32 NpcType);
};




/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _NPC_PAOPAO_INDEX
{
	int32	m_iDataIndex;
	int32	m_nBaseIndex;
	int32	m_nIndexStep;
};
struct SNPCPaoPaoIndexTab
{
	_NPC_PAOPAO_INDEX	m_NPCPaoPaoIndex[MAXTYPE_NUMBER];
	int32			m_iCount;

	static int32 CompareNpcPaoPao(const void *pArg1, const void *pArg2)
	{
		__GUARD__ int32 Serial1, Serial2;

		Serial1 = ((_NPC_PAOPAO_INDEX *) pArg1)->m_iDataIndex;
		Serial2 = ((_NPC_PAOPAO_INDEX *) pArg2)->m_iDataIndex;

		if(Serial1 > Serial2)
			return 1;
		else if(Serial1 < Serial2)
			return -1;
		else
			return 0;
		__UNGUARD__ return 0;
	}

	_NPC_PAOPAO_INDEX *GetNpcPaoPaoData(int32 iDataIndex)
	{
		__GUARD__ _NPC_PAOPAO_INDEX	oAttr;
		oAttr.m_iDataIndex = iDataIndex;

		_NPC_PAOPAO_INDEX	*pResult = (_NPC_PAOPAO_INDEX *) bsearch
			(
				&oAttr,
				m_NPCPaoPaoIndex,
				m_iCount,
				sizeof(_NPC_PAOPAO_INDEX),
				(int32(*) (const void *, const void *)) CompareNpcPaoPao
			);

		if(pResult != NULL)
		{
			return pResult;
		}

		__UNGUARD__ return NULL;
	}
};
extern SNPCPaoPaoIndexTab	g_NPCPaoPaoIndexTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define QUES_CON_SIZE	256
#define OPT_CON_SIZE	64
struct SQuestionData
{
	int32	m_nIndex;
	char	m_szContex[QUES_CON_SIZE];
	char	m_szOption0[OPT_CON_SIZE];
	char	m_szOption1[OPT_CON_SIZE];
	char	m_szOption2[OPT_CON_SIZE];
	char	m_szOption3[OPT_CON_SIZE];
	char	m_szOption4[OPT_CON_SIZE];
	char	m_szOption5[OPT_CON_SIZE];
	uchar	m_Key0;
	uchar	m_Key1;
	uchar	m_Key2;
	uchar	m_Key3;
	uchar	m_Key4;
	uchar	m_Key5;

	SQuestionData()
	{
		m_nIndex = INVALID_INDEX;
		memset(m_szContex, 0, QUES_CON_SIZE);
		memset(m_szOption0, 0, OPT_CON_SIZE);
		memset(m_szOption1, 0, OPT_CON_SIZE);
		memset(m_szOption2, 0, OPT_CON_SIZE);
		memset(m_szOption3, 0, OPT_CON_SIZE);
		memset(m_szOption4, 0, OPT_CON_SIZE);
		memset(m_szOption5, 0, OPT_CON_SIZE);
		m_Key0 = INVALID_INDEX;
		m_Key1 = INVALID_INDEX;
		m_Key2 = INVALID_INDEX;
		m_Key3 = INVALID_INDEX;
		m_Key4 = INVALID_INDEX;
		m_Key5 = INVALID_INDEX;
	};
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_INST_t
{
	int32	nQuestIndex;
};

struct _QUEST_DELIVERY_t :
	public _QUEST_INST_t
{
	int32	nDeliveryItemID1;
	int32	nDeliveryItemNum1;
	int32	nDeliveryItemID2;
	int32	nDeliveryItemNum2;
	int32	nDeliveryItemID3;
	int32	nDeliveryItemNum3;
};
struct __QUEST_DELIVERY
{
	_QUEST_DELIVERY_t	*m_QuestDelivery;
	int32			m_nQuestDeliveryCount;
	__QUEST_DELIVERY()
	{
		m_QuestDelivery = 0;
		m_nQuestDeliveryCount = 0;
	}
	_QUEST_DELIVERY_t	*Get(int32 nIndex);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_ENTERAREA_t :
	public _QUEST_INST_t
{
	char	szAreaName[128];
	char	szAreaSceneID[64];
	int32	nAreaID;
	int32	nAreaIndex;
	char	szEnterArea[256];
	int32	nIfHaveDialog;
	char	szEnterAreaDialog[256];
};
struct __QUEST_ENTERAREA
{
	_QUEST_ENTERAREA_t	*m_QuestEnterArea;
	int32			m_nQuestEnterAreaCount;
	__QUEST_ENTERAREA()
	{
		m_QuestEnterArea = 0;
		m_nQuestEnterAreaCount = 0;
	}
	_QUEST_ENTERAREA_t	*Get(int32 nIndex);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_KILLMONSTER_t :
	public _QUEST_INST_t
{
	int32	nMonsterSceneID;
	char	szMonsterName[NPC_NAME_LEN];
	char	szMonsterTitle[NPC_NAME_LEN];
	int32	nMonsterType;
	int32	nMonsterLevelMin;
	int32	nMonsterLevelMax;
	int32	nCourseIndex;
	int32	nKillNum;
};
struct __QUEST_KILLMONSTER
{
	_QUEST_KILLMONSTER_t	*m_QuestKillMonster;
	int32			m_nQuestKillMonsterCount;
	__QUEST_KILLMONSTER()
	{
		m_QuestKillMonster = 0;
		m_nQuestKillMonsterCount = 0;
	}
	_QUEST_KILLMONSTER_t	*Get(int32 nIndex);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_LOOKITEM_t :
	public _QUEST_INST_t
{
	int32	nLookItemType;
	int32	nItemID1;
	int32	nItemNum1;
	int32	nGrowPointType;
	int32	nCollectNum;
	int32	nMonsterSceneID;
	char	szMonsterName[NPC_NAME_LEN];
	char	szMonsterTitle[NPC_NAME_LEN];
	int32	nMonsterType;
	int32	nMonsterLevelMin;
	int32	nMonsterLevelMax;
	int32	nCourseIndex;
	int32	nDropRand;
	int32	nMaxDropNum;
};
struct __QUEST_LOOKITEM
{
	_QUEST_LOOKITEM_t	*m_QuestLookItem;
	int32			m_nQuestLookItemCount;
	__QUEST_LOOKITEM()
	{
		m_QuestLookItem = 0;
		m_nQuestLookItemCount = 0;
	}
	_QUEST_LOOKITEM_t	*Get(int32 nPunishID);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_USEITEM_t :
	public _QUEST_INST_t
{
	int32	nUseItemType;
	int32	nItemID1;
	char	szSceneID[128];
	int32	nPosX;
	int32	nPosZ;
	int32	nRadius;
	int32	nSkillID;
	char	szUseItemDesc[512];
	int32	nUseDialog;
	char	szUseItemDialog[512];
	char	szUseItemErrorDialog[60];
};
struct __QUEST_USEITEM
{
	_QUEST_USEITEM_t	*m_QuestUseItem;
	int32			m_nQuestUseItemCount;
	__QUEST_USEITEM()
	{
		m_QuestUseItem = 0;
		m_nQuestUseItemCount = 0;
	}
	_QUEST_USEITEM_t	*Get(int32 nPunishID);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUEST_HUSONG_t :
	public _QUEST_INST_t
{
	int32	nHuSongType;
	int32	nBusAI;
	int32	nAIScript;
	int32	nEventScript;
	int32	nEffectID;
	int32	nBusVisual;
	char	szNPCName[NPC_NAME_LEN];
	char	szNPCTitle[NPC_NAME_LEN];
	int32	nEmptyTime;
	int32	nBusLife;
	int32	nPatrolID;
};
struct __QUEST_HUSONG
{
	_QUEST_HUSONG_t *m_QuestHuSong;
	int32		m_nQuestHuSongCount;
	__QUEST_HUSONG()
	{
		m_QuestHuSong = 0;
		m_nQuestHuSongCount = 0;
	}
	_QUEST_HUSONG_t *Get(int32 nHuSongID);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_SELECT_ITEM 12
enum
{
    CHOOSE_BY_OLDTYPE = 0,          // 成吉思汗I选择奖励方式
    CHOOSE_BY_PROFESSION,           // 自动根据角色职业选择奖励
    CHOOSE_BY_SELECT,               // 玩家手选奖励物品
};
struct _QUEST_DATA_t
{

	QuestID_t	nQuestID;
	ScriptID_t	nScriptID;
	int32		nQuestType;
	char		szQuestName[256];
	char		szQuestDisp[256];
	QuestID_t	nPreQuestID1;
	QuestID_t	nPreQuestID2;
	QuestID_t	nPreQuestID3;
	int32		nMinLevel;
	int32		nMaxLevel;
	int32		nSpendMoneyType;
	int32		nNeedMoney;
	int32		nCountry;
	int16		nProfession;
	int32		nCamp;
	int32		nQuestDest[5];
	int32		nMoneyRewardType;
	int32		nMoneyRewardP1;
	int32		nMoneyRewardP2;
	int32		nMoneyRewardP3;
	int32		nExpRewardP1;
	int32		nExpRewardP2;
	int32		nExpRewardP3;
	int32		nShengWangType;					/* 声望奖励 0朝廷声望 1江湖声望 2PK值 3荣誉（功勋） 4帮贡 5文采 6 威望 7 天赋经验 */
	int32		nShengWangRewartP1;
	int32		nShengWangRewartP2;
	int32		nShengWangRewartP3;
	int32		nEnergyRewardType;
	int32		nEnergyReward;
	int32		nGuildRewardType;
	int32		nGuildReward;
	int32		nFixItemID1;
	int16		nFixItemNum1;
	int32		nFixItemID2;
	int16		nFixItemNum2;
	int32		nFixItemID3;
	int16		nFixItemNum3;
	int32		nFixItemID4;
	int16		nFixItemNum4;
	int32		nSelItemID1;
	int16		nSelItemNum1;
	int32		nSelItemID2;
	int16		nSelItemNum2;
	int32		nSelItemID3;
	int16		nSelItemNum3;
	int32		nSelItemID4;
	int16		nSelItemNum4;
	int32		nSelItemID5;
	int16		nSelItemNum5;
	int32		nSelItemID6;
	int16		nSelItemNum6;
	ScriptID_t	nRewardScript;
	char		szQuestDesc[1024];
	char		szQuestManual[1024];
	char		szQuestContinue[1024];
	char		szQuestAbandon[1024];
	char		szQuestSuccess[1024];
	GUID_t		nSubmitNPCGUID;
	char		szSubmitNPCName[NPC_NAME_LEN];
	MapID_t		nSubmitNPCMapID;
	int32		nPathIndex;
	int32		nAfterQuestType;
	ScriptID_t	nAfterQuestScriptID;

	char		szQuestTarget1[128];
	char		szQuestTarget2[128];
	char		szQuestTarget3[128];
	char		szQuestTarget4[128];
	char		szQuestTarget5[128];
	char		szQuestHelp[128];

	int32		nQuestFlag;
	int32		nAcceptFlag;

    // 2010-03-31（ttp-29507）所有可选奖励物品ID
    int32       nSelItemsID[ MAX_SELECT_ITEM];
    // 2010-03-31（ttp-29507）可选奖励物品计数
    int32       nSelItemCount;
    // 2010-03-31（ttp-29507）选择奖励物品类型
    int32       nChooseType;
};
struct __QUEST_DATA
{
	_QUEST_DATA_t	*m_QuestData;
	int16		m_nQuestDataCount;
	__QUEST_DATA()
	{
		m_QuestData = 0;
		m_nQuestDataCount = 0;
	}
	_QUEST_DATA_t	*Get(int32 nQuestID);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct __SCRIPT_QUEST_DATA
{
	typedef std::vector<void *>	VEC_QUESTDATA;

	IntegerHashMap m_IDTable;

	__SCRIPT_QUEST_DATA (void)
	{
	}
	~__SCRIPT_QUEST_DATA (void)
	{
		Clear();
	}
	void	InitTable(uint32 nMaxCount);
	void	Clear();

	BOOL	Add(uint32 nIdEvent, void *pData);
	BOOL	Have(uint32 nIdEvent);
	BOOL	Find(uint32 nIdEvent, uint32 nNPCGUID);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _QUESTIONS_t
{
	int32 nIndex;
	int32 nType;
	int32 nAnswerIndex1;
	int32 nAnswerIndex2;
};
struct _QUESTIONS_DATA
{
	_QUESTIONS_t	*m_QuestionData;
	int32 m_QuestionDataCount;
	_QUESTIONS_DATA()
	{
		m_QuestionData = 0;
		m_QuestionDataCount = 0;
	}
};



/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32 MAX_QUEST_DENGMI_DESC = 96;
const int32 MAX_QUEST_DENGMI_ANSWER = 20;
const int32 MAX_QUEST_DENGMI_COUNT = 1000;
struct QUEST_DENGMI_EXT_ATTR
{
	int32 m_ID;
	char m_Desc[MAX_QUEST_DENGMI_DESC];
	char m_strAnswer1[MAX_QUEST_DENGMI_ANSWER];
	char m_strAnswer2[MAX_QUEST_DENGMI_ANSWER];
	char m_strAnswer3[MAX_QUEST_DENGMI_ANSWER];
	char m_strAnswer4[MAX_QUEST_DENGMI_ANSWER];
	int32 m_nAnswer;
};

struct QUEST_DENGMI_ATTR
{
	QUEST_DENGMI_EXT_ATTR m_TableExt[MAX_QUEST_DENGMI_COUNT];
	uint32 m_Count;

	QUEST_DENGMI_ATTR()
	{
		memset(m_TableExt, 0, sizeof(QUEST_DENGMI_EXT_ATTR) * MAX_QUEST_DENGMI_COUNT);
		m_Count = 0;
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern QUEST_DENGMI_ATTR g_QuestDengmiAttrTbl;
extern QUEST_DENGMI_ATTR g_QuestQuizAttrTbl;
extern QUEST_DENGMI_ATTR g_QuestShituAttrTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct QUEST_WULONGCIDIAN_ATTR
{
	const static int32 MAX_QUEST_WULONG_DESC = 128;
	const static int32 MAX_QUEST_WULONG_ANSWER = 20;

	int32 m_ID;
	char m_Desc[MAX_QUEST_WULONG_DESC];
	char m_strAnswer1[MAX_QUEST_WULONG_ANSWER];
	char m_strAnswer2[MAX_QUEST_WULONG_ANSWER];
	char m_strAnswer3[MAX_QUEST_WULONG_ANSWER];
	char m_strAnswer4[MAX_QUEST_WULONG_ANSWER];
	int32 m_nAnswer;
};
struct QUEST_WULONGCIDIAN_TABLE
{
	const static int32 MAX_QUEST_WULONG_ATTR_COUNT = 2048;

	QUEST_WULONGCIDIAN_ATTR m_Table[MAX_QUEST_WULONG_ATTR_COUNT];
	uint32 m_Count;

	QUEST_WULONGCIDIAN_TABLE()
	{
		memset(this, 0, sizeof(QUEST_WULONGCIDIAN_TABLE));
	}

	uint32 GetCount()
	{
		return m_Count;
	}
};

extern QUEST_WULONGCIDIAN_TABLE g_QuestWulongAttrTbFirst;
extern QUEST_WULONGCIDIAN_TABLE g_QuestWulongAttrTbSec;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareNpcQuestTB(const void *pArg1, const void *pArg2);

int32 CompareQuestKillMonsterTB(const void *pArg1, const void *pArg2);

int32 CompareQuestLookItemTB(const void *pArg1, const void *pArg2);

int32 CompareQuestHuSongTB(const void *pArg1, const void *pArg2);

int32 CompareQuestDataTB(const void *pArg1, const void *pArg2);

int32 CompareQuestEnterAreaTB(const void *pArg1, const void *pArg2);

int32 CompareQuestDeliveryTB(const void *pArg1, const void *pArg2);

int32 CompareQuestUseItemTB(const void *pArg1, const void *pArg2);

int32 CompareSceneMapNpcTB(const void *pArg1, const void *pArg2);


/*
 =======================================================================================================================
 =======================================================================================================================
 */


#endif