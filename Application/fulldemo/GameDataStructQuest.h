#pragma once
#define QUEST_INFO_MAXLEN (1536)

#include "StructCommandScript.h"

/*
 -----------------------------------------------------------------------------------------------------------------------
    ������Ϣ�ṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */

class KItem;

struct _QUEST_INFO
{
	BOOL	m_bFill;

	int32		m_nQuestID;				/* ����ID */
	int32		m_nType;				/* �������ͣ�0����ͨ����1����������2��ѭ������ */
	int32		m_nFlag;				/* ��ǣ���ѭ���������� */

	int32		m_nLevel;				/* ����ȼ� */
	int32		m_nKind;				/* �������� */

	/* �����Ƿ���Ҫ��ʾĳЩֵ */
	int32		m_nIsAutoSpeak;			/* �Ƿ��Զ���NPC�Ի� */
	int32		m_nNPCPosX;				/* NPC����x */
	int32		m_nNPCPosZ;				/* NPC����z */

	BOOL	m_bPlayedSound;				/* ������Ч�����ʱ */
	BOOL	m_bSubPlayedSound[5];		/* ���������ʱ���������� */

	/* ��������Ʒ */
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

	/* ������Ҫ��Ʒ */
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

	/* ������Ҫɱ����NPC */
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

	/* �����������Ʒ��Ϣ */
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

	/* �������� */
	struct QuestDemandFindNPC
	{
		STRING					strInfo;
		std::vector<ItemInfo>	vecItemInfo;

		BOOL bPlaySound;
	};

	/* ������Ҫ���Զ��� */
	struct QuestCustom
	{
		STRING szCustomString;			/* �����Զ�����ַ��� */
		int32 nCount;					/* ��Ҫ������������� */

		BOOL bPlaySound;
	};

	/* ����ɼ������ݣ�ֻ��Խű����� */
	struct QuestGroupPoint
	{
		int32 nID;
		STRING szTarget;
	};

public:

	/* ������ */
	std::vector<QuestRewardItem>	m_QuestRewardItem;		/* ��������Ʒ */

	/* ����Ŀ�� */
	std::vector<QuestDemandItem>	m_QuestDemandItem;		/* �����ռ���Ʒ */
	std::vector<QuestDemandKill>	m_vecQuestDemandKill;	/* ������Ҫɱ����NPC */
	std::vector<QuestDemandFindNPC> m_vecQuestDemandNPC;	/* �������� */
	std::vector<QuestCustom>		m_vecQuestCustom;		/* �����Զ������� */

	/* Ŀ����Ϣ */
	std::vector<STRING>				m_vecTargetInfoExt;		/* ѭ��������Ҫ */

	/* ����ɼ��㣬�ű���� */
	std::vector<QuestGroupPoint>	m_vecQuestGroupPoint;	/* ����ɼ��� */

public:

	STRING m_misName;		/* �������� */
	STRING m_misDesc;		/* �������� */
	STRING m_misContinue;	/* �������CZG */
	STRING m_misCompleted;	/* �������CZG */
	STRING m_misHelp;		/* ������ʾ��ϢCZG������ */
	STRING m_misManual;		/* ������ */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ������չ���ݣ���������Ҫ��Դ�ڷ����������Ҷ������������������������Ӱ��
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _QUEST_EXT_INFO
{
	/* �ṹ��Ա */
	QuestID_t m_nQuestId;

	FlagTool m_Flag;
	STRING m_strQuestTitle;			/* flag 0 */
	STRING m_strQuestName;			/* flag 1 */
	STRING m_strQuestTarget;		/* flag 2 */
	STRING m_strQuestSubmitNPC;		/* flag 3 */
	STRING m_strQuestManual;		/* flag 4 */
	STRING m_strQuestInfo;			/* flag 5 */
	STRING m_strQuestHelp;			/* flag 6 */

	std::vector<_QUEST_INFO::QuestRewardItem> m_QuestRewardItem;	/* ��������Ʒ */
};

/*
 * ���Ͷ��� ;
 */
typedef std::map<int32, _QUEST_INFO> MisInfo;
typedef std::map<int32, _QUEST_EXT_INFO> MisExtInfo;
typedef void (*parseLine) (char*pDest,char*pSrc,int32 j);


//�ű�������ؽӿ�
class ScriptQuestInterface
{
public:

	static MisInfo g_misInfo;				/* ���������Ϣ */
	static MisExtInfo g_misExtInfo;			/* ������չ��Ϣ */
	static _QUEST_INFO* g_misInfoPtr;		/* ����ָ�� */

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

	static void parseQuestName_CP(char *pDest, char *pSrc, int32 j);				/* ������������ */
	static void parseQuestTarget_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ŀ�� */
	static void parseQuestInfo_CP(char *pDest, char *pSrc, int32 j);				/* ����������Ϣ */
	static void parseQuestContinue_CP(char *pDest, char *pSrc, int32 j);			/* �������������Ϣ */
	static void parseQuestCompleted_CP(char *pDest, char *pSrc, int32 j);			/* �������������Ϣ */
	static void parseQuestHelp_CP(char *pDest, char *pSrc, int32 j);				/* ����������ʾ��Ϣ */
	static void parseLevelLess_CP(char *pDest, char *pSrc, int32 j);				/* �����������͵ȼ� */
	static void parseQuestKind_CP(char *pDest, char *pSrc, int32 j);				/* ������������� */
	static void parseTarget_CP(char *pDest, char *pSrc, int32 j);					/* ��������Ŀ��1 */
	static void parseExtTarget_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ŀ��Ext */
	static void parseExpBonus_CP(char *pDest, char *pSrc, int32 j);					/* ��������ľ��齱�� */
	static void parseBonusMoney1_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����1 */
	static void parseBonusMoney2_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����2 */
	static void parseBonusMoney3_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����3 */
	static void parseBonusMoney4_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����4 */
	static void parseBonusMoney5_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����5 */
	static void parseBonusMoney6_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ľ�Ǯ����6 */
	static void parseBonusItem_CP(char *pDest, char *pSrc, int32 j);				/* ��������Ĺ̶�������Ʒ */
	static void parseBonusChoiceItem_CP(char *pDest, char *pSrc, int32 j);			/* ��������Ŀ�ѡ������Ʒ */
	static void parseGroupPoint_CP(char *pDest, char *pSrc, int32 j);

};