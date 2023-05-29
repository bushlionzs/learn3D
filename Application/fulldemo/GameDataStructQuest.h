#pragma once
#define QUEST_INFO_MAXLEN (1536)

#include "StructCommandScript.h"

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务信息结构 ;
 -----------------------------------------------------------------------------------------------------------------------
 */

class KItem;

struct _QUEST_INFO
{
	BOOL	m_bFill;

	int32		m_nQuestID;				/* 任务ID */
	int32		m_nType;				/* 任务类型，0：普通任务，1：副本任务，2：循环任务 */
	int32		m_nFlag;				/* 标记，仅循环任务有用 */

	int32		m_nLevel;				/* 任务等级 */
	int32		m_nKind;				/* 任务类型 */

	/* 任务是否需要显示某些值 */
	int32		m_nIsAutoSpeak;			/* 是否自动与NPC对话 */
	int32		m_nNPCPosX;				/* NPC坐标x */
	int32		m_nNPCPosZ;				/* NPC坐标z */

	BOOL	m_bPlayedSound;				/* 播放音效，完成时 */
	BOOL	m_bSubPlayedSound[5];		/* 子任务完成时，播放声音 */

	/* 任务奖励物品 */
	struct QuestRewardItem
	{
		SQuestBonus	ItemData;
		KItem			*pItemImpl;
		BOOL			bSelected;

		QuestRewardItem()
		:
		pItemImpl(NULL),
		bSelected(FALSE)
		{
			ItemData.Reset();
		}
	};

	/* 任务需要物品 */
	struct QuestDemandItem
	{
		STRING				szInfo;

		KItem				*pItemImpl;
		SQuestBonusItem	*pDemandItem;

		BOOL				bPlaySound;

		QuestDemandItem()
		:
		pItemImpl(NULL),
		pDemandItem(NULL),
		bPlaySound(FALSE)
		{
		}
	};

	/* 任务需要杀死的NPC */
	struct QuestDemandKill
	{
		STRING				szNPCName;
		STRING				szInfo;

		SQuestDemandKill	*pDemandKill;

		QuestDemandKill()
		:
		pDemandKill(NULL)
		{
		}
	};

	/* 送信任务的物品信息 */
	struct ItemInfo
	{
		KItem				*pItemImpl;
		SQuestBonusItem	*pDemandItem;

		ItemInfo()
		:
		pItemImpl(NULL),
		pDemandItem(NULL)
		{
		}
	};

	/* 任务送信 */
	struct QuestDemandFindNPC
	{
		STRING					strInfo;
		std::vector<ItemInfo>	vecItemInfo;

		BOOL bPlaySound;
	};

	/* 任务需要的自定义 */
	struct QuestCustom
	{
		STRING szCustomString;			/* 任务自定义的字符串 */
		int32 nCount;					/* 需要这个东东的数量 */

		BOOL bPlaySound;
	};

	/* 任务采集点数据，只针对脚本任务 */
	struct QuestGroupPoint
	{
		int32 nID;
		STRING szTarget;
	};

public:

	/* 任务奖励 */
	std::vector<QuestRewardItem>	m_QuestRewardItem;		/* 任务奖励物品 */

	/* 任务目标 */
	std::vector<QuestDemandItem>	m_QuestDemandItem;		/* 任务收集物品 */
	std::vector<QuestDemandKill>	m_vecQuestDemandKill;	/* 任务需要杀死的NPC */
	std::vector<QuestDemandFindNPC> m_vecQuestDemandNPC;	/* 任务送信 */
	std::vector<QuestCustom>		m_vecQuestCustom;		/* 任务自定义数据 */

	/* 目标信息 */
	std::vector<STRING>				m_vecTargetInfoExt;		/* 循环任务需要 */

	/* 任务采集点，脚本相关 */
	std::vector<QuestGroupPoint>	m_vecQuestGroupPoint;	/* 任务采集点 */

public:

	STRING m_misName;		/* 任务名称 */
	STRING m_misDesc;		/* 任务描述 */
	STRING m_misContinue;	/* 任务继续CZG */
	STRING m_misCompleted;	/* 任务完成CZG */
	STRING m_misHelp;		/* 任务提示信息CZG，待定 */
	STRING m_misManual;		/* 任务攻略 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务扩展数据，此数据主要来源于服务器，并且对任务管理器及任务跟踪面板有影响
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _QUEST_EXT_INFO
{
	/* 结构成员 */
	QuestID_t m_nQuestId;

	FlagTool m_Flag;
	STRING m_strQuestTitle;			/* flag 0 */
	STRING m_strQuestName;			/* flag 1 */
	STRING m_strQuestTarget;		/* flag 2 */
	STRING m_strQuestSubmitNPC;		/* flag 3 */
	STRING m_strQuestManual;		/* flag 4 */
	STRING m_strQuestInfo;			/* flag 5 */
	STRING m_strQuestHelp;			/* flag 6 */

	std::vector<_QUEST_INFO::QuestRewardItem> m_QuestRewardItem;	/* 任务奖励物品 */
};

/*
 * 类型定义 ;
 */
typedef std::map<int32, _QUEST_INFO> MisInfo;
typedef std::map<int32, _QUEST_EXT_INFO> MisExtInfo;
typedef void (*parseLine) (char*pDest,char*pSrc,int32 j);


//脚本任务相关接口
class ScriptQuestInterface
{
public:

	static MisInfo g_misInfo;				/* 任务基本信息 */
	static MisExtInfo g_misExtInfo;			/* 任务扩展信息 */
	static _QUEST_INFO* g_misInfoPtr;		/* 任务指针 */

public:

	static const char *tokens_cp[];
	static parseLine fns_cp[];
	static const int32 fns_cp_count;

public:

	static void	FillQuestInfo(int32 nQuestId, int32 nScriptID);
	static _QUEST_INFO& GetQuestInfo(uint32 nQuestId);
	static _QUEST_EXT_INFO*	GetQuestExtInfo(uint32 nQuestId);

	static void RemoveQuestInfo(int32 nIndex);
	static void clearAllQuest(void);

private:

	static void RemoveQuestExtInfoByIndex(int32 nIndex);
	static void RemoveQuestExtInfoByQuestId(int32 nQuestId);
	static void ClearQuest_ScriptId(int32 nScriptId);

public:

	static void parseQuestName_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务名称 */
	static void parseQuestTarget_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务目标 */
	static void parseQuestInfo_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务信息 */
	static void parseQuestContinue_CP(char *pDest, char *pSrc, int32 j);			/* 解析任务继续信息 */
	static void parseQuestCompleted_CP(char *pDest, char *pSrc, int32 j);			/* 解析任务完成信息 */
	static void parseQuestHelp_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务提示信息 */
	static void parseLevelLess_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的最低等级 */
	static void parseQuestKind_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的类型 */
	static void parseTarget_CP(char *pDest, char *pSrc, int32 j);					/* 解析任务目标1 */
	static void parseExtTarget_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务目标Ext */
	static void parseExpBonus_CP(char *pDest, char *pSrc, int32 j);					/* 解析任务的经验奖励 */
	static void parseBonusMoney1_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励1 */
	static void parseBonusMoney2_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励2 */
	static void parseBonusMoney3_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励3 */
	static void parseBonusMoney4_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励4 */
	static void parseBonusMoney5_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励5 */
	static void parseBonusMoney6_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的金钱奖励6 */
	static void parseBonusItem_CP(char *pDest, char *pSrc, int32 j);				/* 解析任务的固定奖励物品 */
	static void parseBonusChoiceItem_CP(char *pDest, char *pSrc, int32 j);			/* 解析任务的可选奖励物品 */
	static void parseGroupPoint_CP(char *pDest, char *pSrc, int32 j);

};