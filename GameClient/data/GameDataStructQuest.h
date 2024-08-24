#pragma once
#define QUEST_INFO_MAXLEN (1536)

#include "StructCommandScript.h"
#include <map>
/*
 -----------------------------------------------------------------------------------------------------------------------
    ������Ϣ�ṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */

class KItem;

struct _QUEST_INFO
{
	_QUEST_INFO()
	{
		int kk = 0;
	}
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
		std::string szInfo;

		KItem *pItemImpl;
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
		std::string szNPCName;
		std::string szInfo;

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
		std::string					strInfo;
		std::vector<ItemInfo>	vecItemInfo;

		BOOL bPlaySound;
	};

	/* ������Ҫ���Զ��� */
	struct QuestCustom
	{
		std::string szCustomString;			/* �����Զ�����ַ��� */
		int32 nCount;					/* ��Ҫ������������� */

		BOOL bPlaySound;
	};

	/* ����ɼ������ݣ�ֻ��Խű����� */
	struct QuestGroupPoint
	{
		int32 nID;
		std::string szTarget;
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
	std::vector<std::string>				m_vecTargetInfoExt;		/* ѭ��������Ҫ */

	/* ����ɼ��㣬�ű���� */
	std::vector<QuestGroupPoint>	m_vecQuestGroupPoint;	/* ����ɼ��� */

public:

	std::string m_misName;		/* �������� */
	std::string m_misDesc;		/* �������� */
	std::string m_misContinue;	/* �������CZG */
	std::string m_misCompleted;	/* �������CZG */
	std::string m_misHelp;		/* ������ʾ��ϢCZG������ */
	std::string m_misManual;		/* ������ */
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
	std::string m_strQuestTitle;			/* flag 0 */
	std::string m_strQuestName;			/* flag 1 */
	std::string m_strQuestTarget;		/* flag 2 */
	std::string m_strQuestSubmitNPC;		/* flag 3 */
	std::string m_strQuestManual;		/* flag 4 */
	std::string m_strQuestInfo;			/* flag 5 */
	std::string m_strQuestHelp;			/* flag 6 */

	std::vector<_QUEST_INFO::QuestRewardItem> m_QuestRewardItem;	/* ��������Ʒ */
};

/*
 * ���Ͷ��� ;
 */
typedef std::map<int32_t, _QUEST_INFO> MisInfo;
typedef std::map<int32_t, _QUEST_EXT_INFO> MisExtInfo;
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