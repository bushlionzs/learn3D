/*$T Common/ScriptCommandStruct.h GC 1.140 10/10/07 10:06:54 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __SCRIPTCOMMANDSTRUCT_H__
#define __SCRIPTCOMMANDSTRUCT_H__

#include "TypeDefine.h"

enum eSCRIPT_CMD
{
	SCRIPT_COMMAND_INVALID			= -1,
	SCRIPT_COMMAND_EVENT_LIST_RESPONSE,         // 显示只有取消按钮的对话框
	SCRIPT_COMMAND_QUEST_RESPONSE,              // 显示任务信息，客户端按确定后服务器走xxx_CheckAndAccept
	SCRIPT_COMMAND_QUEST_REGIE,                 // 没有用到
	SCRIPT_COMMAND_QUEST_DEMAND_RESPONSE,
	SCRIPT_COMMAND_QUEST_CONTINUE_RESPONSE,     // 显示确认取消对话框，客户端按确定后服务器走xxx_OnSubmit
	SCRIPT_COMMAND_QUEST_TIPS,                  // 显示中上提示Tip，可以废弃，因为Msg2Player( , , , 8, 3)完全可以实现同样的功能，而且更简洁
	SCRIPT_COMMAND_TRADE,                       // 没有用到
	SCRIPT_COMMAND_SKILL_STUDY,                 // 打开技能学习界面
	SCRIPT_COMMAND_EVENT_LIST_HIDE,
	SCRIPT_COMMAND_QUEST_UPDATE,
	SCRIPT_COMMAND_QUESTDENGMI,
	SCRIPT_COMMAND_GUILDSKILL_STUDY_GUILD,
	SCRIPT_COMMAND_GUILDSKILL_STUDY_CHAR,
	SCRIPT_COMMAND_INHERENCEBALANCE_STUDY,
	SCRIPT_COMMAND_GUILD_BUSSKILL_STUDY_BYMONEY,		// 帮会神兽技能学习使用金钱
	SCRIPT_COMMAND_GUILD_BUSSKILL_STUDY_BYEXP,			// 帮会神兽技能学习使用经验
};

struct FlagTool
{

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsSetBit(int32 bit) const
	{
		uint32	i = bit / 32;

		if(i < FLAG_BIT / 32)
		{
			if(m_uFlags[i] & (1 << (uint32) (bit - 32 * i))) return TRUE;
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UpdateBit(int32 bit, BOOL bUpDate)
	{
		uint32	i = bit / 32;

		if(i < FLAG_BIT / 32)
		{
			if(bUpDate)
			{
				m_uFlags[i] |= (1 << (uint32) (bit - 32 * i));
			}
			else
			{
				m_uFlags[i] &= (~(1 << (uint32) (bit - 32 * i)));
			}
		}
		else
		{
			KCheckEx(FALSE, "数组越界！");
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_uFlags, 0, sizeof(m_uFlags));
	}


	const static int32	FLAG_BIT = 256;
	uint32			m_uFlags[FLAG_BIT / 32];
};

#define DEF_SCRIPT_STRING_LEN	(1024 + 1)
struct SScriptString
{
	int16	m_Size;
	char	m_szString[DEF_SCRIPT_STRING_LEN];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_Size = 0;
		memset(m_szString, 0, sizeof(m_szString));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SScriptString &operator=(uint32 uValue)
	{
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SScriptString &operator=(const char *pszString)
	{
		if(pszString != NULL)
		{
			m_Size = (int16) strlen(pszString);
			if(m_Size > DEF_SCRIPT_STRING_LEN - 1) m_Size = DEF_SCRIPT_STRING_LEN - 1;
			if(m_Size > 0) memcpy(m_szString, pszString, m_Size);

			m_szString[m_Size] = 0;
		}
		else
		{
			m_Size = 0;
			m_szString[0] = 0;
		}

		return *this;
	}

	uint32	GetBufSize(void) const;

};

enum eEVENT_ITEM_TYPE
{
	EVENT_ITEM_TYPE_INVALID			= -1,
	EVENT_ITEM_TYPE_SECTION,
	EVENT_ITEM_TYPE_SCRIPT_ID,
	EVENT_ITEM_TYPE_TEXT,
};

struct SScriptEventItem
{
	int32		m_nType;
	int32		m_state;
	int32		m_index;
	SScriptString	m_strString;
	ScriptID_t	m_idScript;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_nType = EVENT_ITEM_TYPE_INVALID;
		m_strString.Reset();
	}

	uint32	GetBufSize(void) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetSection(const SScriptString *pstrSection)
	{
		m_nType = EVENT_ITEM_TYPE_SECTION;
		m_strString = *pstrSection;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetScriptID(int32 index, int32 state, ScriptID_t idScript, const SScriptString *pstrSection)
	{
		m_nType = EVENT_ITEM_TYPE_SCRIPT_ID;
		m_state = state;
		m_index = index;
		m_idScript = idScript;
		m_strString = *pstrSection;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetText(const SScriptString *pstrSection)
	{
		m_nType = EVENT_ITEM_TYPE_TEXT;
		m_strString = *pstrSection;
	}

};

#define MAX_EVENT_LIST_ITEM_COUNT	(16)
struct SScriptParamEventList
{
	ObjID_t		m_idNPC;
	uchar		m_yItemCount;
	SScriptEventItem m_seiItem[MAX_EVENT_LIST_ITEM_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_idNPC = INVALID_ID;
		m_yItemCount = 0;

		/*~~~~~~*/
		uint32	i;
		/*~~~~~~*/

		for(i = 0; i < MAX_EVENT_LIST_ITEM_COUNT; i++)
		{
			m_seiItem[i].Reset();
		}
	}

	uint32	GetBufSize(void) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void AddItem(const SScriptEventItem *pItem)
	{
		if(m_yItemCount < MAX_EVENT_LIST_ITEM_COUNT)
		{
			m_seiItem[m_yItemCount] = *pItem;
			m_yItemCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const SScriptEventItem *GetItem(uchar yIndex) const
	{
		return(yIndex < m_yItemCount) ? (&m_seiItem[yIndex]) : (NULL);
	}

};

struct SQuestBonusItem
{
	uchar	m_yCount;
	uint32	m_uItemID;
	uchar	m_yIndex;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_yCount = 0;
		m_yIndex = 0;
		m_uItemID = UINT_MAX;
	}

	uint32	GetBufSize(void) const;

};
struct SQuestDemandKill
{
	uint32	m_yCount;
	uint32	m_uNPCID;
	uchar	m_yIndex;
	uchar	m_LevelMin;
	uchar	m_LevelMax;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_yCount = 0;
		m_yIndex = 0;
		m_LevelMin = 0;
		m_LevelMax = 0;
		m_uNPCID = UINT_MAX;
	}

	uint32	GetBufSize(void) const;

};
enum ENUM_QUEST_BONUS_TYPE
{
	QUEST_BONUS_TYPE_INVALID		= -1,
	QUEST_BONUS_TYPE_MONEY,
	QUEST_BONUS_TYPE_MONEY1,
	QUEST_BONUS_TYPE_MONEY2,
	QUEST_BONUS_TYPE_MONEY3,
	QUEST_BONUS_TYPE_ITEM,
	QUEST_BONUS_TYPE_ITEM_RAND,
	QUEST_BONUS_TYPE_ITEM_RADIO,
	QUEST_BONUS_TYPE_EXP,
	QUEST_BONUS_TYPE_MONEY4,
	QUEST_BONUS_TYPE_MONEY5,
	QUEST_BONUS_TYPE_MONEY6,
	QUEST_BONUS_TYPE_MONEY7,
	QUEST_BONUS_TYPE_MONEY8,
	QUEST_BONUS_TYPE_MONEY9,
	QUEST_BONUS_TYPE_VIGOR,
	QUEST_BONUS_TYPE_CHARM,
	QUEST_BONUS_TYPE_GENIUS,
	QUEST_BONUS_TYPE_GUILD_EXP,
	QUEST_BONUS_TYPE_COUNTRY_FOOD,
	QUEST_BONUS_TYPE_COUNTRY_MONEY,
	QUEST_BONUS_TYPE_COUNTRY_WOOD,
	QUEST_BONUS_TYPE_COUNTRY_METAL,
	QUEST_BONUS_TYPE_WEIWANG,
	QUEST_BONUS_TYPE_INHERENCE_EXP,
	QUEST_BONUS_TYPE_GUILD_MONEY,
};

struct SQuestBonus
{
	int32	m_nType;
	union
	{
		uint32		m_uMoney;
		uint32		m_uExp;
		SQuestBonusItem m_ItemBonus;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_nType = QUEST_BONUS_TYPE_INVALID;
		m_ItemBonus.Reset();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney1(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY1;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney2(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY2;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney3(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY3;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney4(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY4;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney5(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY5;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney6(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY6;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney7(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY7;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney8(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY8;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMoney9(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_MONEY9;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetExp(uint32 uExp)
	{
		m_nType = QUEST_BONUS_TYPE_EXP;
		m_uExp = uExp;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItem(uint32 uItemID, uchar yItemCount)
	{
		m_nType = QUEST_BONUS_TYPE_ITEM;
		m_ItemBonus.m_yCount = yItemCount;
		m_ItemBonus.m_uItemID = uItemID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItemRand(void)
	{
		m_nType = QUEST_BONUS_TYPE_ITEM_RAND;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItemRadio(uint32 uItemID, uchar yItemCount)
	{
		m_nType = QUEST_BONUS_TYPE_ITEM_RADIO;
		m_ItemBonus.m_yCount = yItemCount;
		m_ItemBonus.m_uItemID = uItemID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Set_Property_Vigor(uint32 uEnergy)
	{
		m_nType = QUEST_BONUS_TYPE_VIGOR;
		m_uMoney = uEnergy;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCharm(uint32 uCharm)
	{
		m_nType = QUEST_BONUS_TYPE_CHARM;
		m_uMoney = uCharm;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGenius(uint32 uGenius)
	{
		m_nType = QUEST_BONUS_TYPE_GENIUS;
		m_uMoney = uGenius;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGuildExp(uint32 uExp)
	{
		m_nType = QUEST_BONUS_TYPE_GUILD_EXP;
		m_uExp = uExp;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCountryFood(uint32 uFood)
	{
		m_nType = QUEST_BONUS_TYPE_COUNTRY_FOOD;
		m_uMoney = uFood;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCountryMoney(uint32 uMoney)
	{
		m_nType = QUEST_BONUS_TYPE_COUNTRY_MONEY;
		m_uMoney = uMoney;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCountryWood(uint32 uWood)
	{
		m_nType = QUEST_BONUS_TYPE_COUNTRY_WOOD;
		m_uMoney = uWood;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCountryMetal(uint32 uMetal)
	{
		m_nType = QUEST_BONUS_TYPE_COUNTRY_METAL;
		m_uMoney = uMetal;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetWeiWang(uint32 uWeiWang)
	{
		m_nType = QUEST_BONUS_TYPE_WEIWANG;
		m_uMoney = uWeiWang;
	}

	void SetInherenceExp(uint32 uInherenceExp )
	{
		m_nType = QUEST_BONUS_TYPE_INHERENCE_EXP;
		m_uMoney = uInherenceExp;
	}

	void SetGuildMoney(uint32 uGuildMoney )
	{
		m_nType = QUEST_BONUS_TYPE_GUILD_MONEY;
		m_uMoney = uGuildMoney;
	}

	uint32	GetBufSize(void) const;

};

#define MAX_QUEST_TEXT_COUNT	(8)
#define MAX_QUEST_BONUS_COUNT	(32)
struct ScriptParam_QuestInfo
{
	ObjID_t		m_idNPC;
	ScriptID_t	m_idScript;
	QuestID_t	m_idQuest;
	uchar		m_yFlags;
	uchar		m_yTextCount;
	SScriptString	m_aText[MAX_QUEST_TEXT_COUNT];
	uchar		m_yBonusCount;
	SQuestBonus	m_aBonus[MAX_QUEST_BONUS_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_idNPC = INVALID_ID;
		m_idScript = INVALID_ID;
		m_idQuest = INVALID_ID;
		m_yTextCount = 0;
		m_yFlags = 0;

		/*~~~~~~*/
		uint32	i;
		/*~~~~~~*/

		for(i = 0; i < MAX_QUEST_TEXT_COUNT; i++)
		{
			m_aText[i].Reset();
		}

		m_yBonusCount = 0;
		for(i = 0; i < MAX_QUEST_BONUS_COUNT; i++)
		{
			m_aBonus[i].Reset();
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddText(const SScriptString *pstrText)
	{
		if(m_yTextCount < MAX_QUEST_TEXT_COUNT)
		{
			m_aText[m_yTextCount] = *pstrText;
			m_yTextCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddBonus(const SQuestBonus *pBonus)
	{
		if(m_yBonusCount < MAX_QUEST_BONUS_COUNT)
		{
			m_aBonus[m_yBonusCount] = *pBonus;
			m_yBonusCount++;
		}
	}

	uint32	GetBufSize(void) const;

	void	SetFlag(int32 nIndex);

};

typedef SScriptParamEventList	ScriptParam_QuestRegie;

typedef SQuestBonusItem		SQuestDemandItem;

#define MAX_QUEST_DEMAND_COUNT	(8)
struct ScriptParam_QuestDemandInfo
{
	enum { QUEST_NODONE = 0, QUEST_DONE, QUEST_CHECK, };
	ObjID_t m_idNPC;
	ScriptID_t m_idScript;
	QuestID_t m_idQuest;
	int32 m_bDone;
	uchar m_yTextCount;
	SScriptString m_aText[MAX_QUEST_TEXT_COUNT];
	uchar m_yDemandCount;
	SQuestDemandItem m_aDemandItem[MAX_QUEST_DEMAND_COUNT];
	uchar m_yBonusCount;
	SQuestBonus m_aBonus[MAX_QUEST_BONUS_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_idNPC = INVALID_ID;
		m_idScript = INVALID_ID;
		m_idQuest = INVALID_ID;
		m_bDone = FALSE;
		m_yDemandCount = 0;
		m_yTextCount = 0;

		/*~~~~~~*/
		uint32	i;
		/*~~~~~~*/

		for(i = 0; i < MAX_QUEST_TEXT_COUNT; i++)
		{
			m_aText[i].Reset();
		}

		for(i = 0; i < MAX_QUEST_DEMAND_COUNT; i++)
		{
			m_aDemandItem[i].Reset();
		}

		m_yBonusCount = 0;
		for(i = 0; i < MAX_QUEST_BONUS_COUNT; i++)
		{
			m_aBonus[i].Reset();
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddText(const SScriptString *pstrText)
	{
		if(m_yTextCount < MAX_QUEST_TEXT_COUNT)
		{
			m_aText[m_yTextCount] = *pstrText;
			m_yTextCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddDemandItem(const SQuestDemandItem *pItem)
	{
		if(m_yDemandCount < MAX_QUEST_DEMAND_COUNT)
		{
			m_aDemandItem[m_yDemandCount] = *pItem;
			m_yDemandCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddBonus(const SQuestBonus *pBonus)
	{
		if(m_yBonusCount < MAX_QUEST_BONUS_COUNT)
		{
			m_aBonus[m_yBonusCount] = *pBonus;
			m_yBonusCount++;
		}
	}

	uint32	GetBufSize(void) const;

};

struct ScriptParam_QuestContinueInfo
{
	ObjID_t		m_idNPC;
	ScriptID_t	m_idScript;
	QuestID_t	m_idQuest;
	uchar		m_yTextCount;
	SScriptString	m_aText[MAX_QUEST_TEXT_COUNT];
	uchar		m_yBonusCount;
	SQuestBonus	m_aBonus[MAX_QUEST_BONUS_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_idNPC = INVALID_ID;
		m_idScript = INVALID_ID;
		m_idQuest = INVALID_ID;
		m_yBonusCount = 0;
		m_yTextCount = 0;

		/*~~~~~~*/
		uint32	i;
		/*~~~~~~*/

		for(i = 0; i < MAX_QUEST_TEXT_COUNT; i++)
		{
			m_aText[i].Reset();
		}

		for(i = 0; i < MAX_QUEST_BONUS_COUNT; i++)
		{
			m_aBonus[i].Reset();
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddText(const SScriptString *pstrText)
	{
		if(m_yTextCount < MAX_QUEST_TEXT_COUNT)
		{
			m_aText[m_yTextCount] = *pstrText;
			m_yTextCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddBonus(const SQuestBonus *pBonus)
	{
		if(m_yBonusCount < MAX_QUEST_BONUS_COUNT)
		{
			m_aBonus[m_yBonusCount] = *pBonus;
			m_yBonusCount++;
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSelectItemID(int32 nIndex)
	{
		int32	i;
		for(i = 0; i < m_yBonusCount; i++)
		{
			if(QUEST_BONUS_TYPE_ITEM_RADIO == m_aBonus[i].m_nType) break;
		}

		if(i == m_yBonusCount)
			return 0;
		else
			return m_aBonus[i + nIndex].m_ItemBonus.m_uItemID;
	}

	uint32	GetBufSize(void) const;
};

struct ScriptParam_QuestTips
{
	SScriptString	m_strText;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_strText.Reset();
	}

	uint32	GetBufSize(void) const;

};

#define MAX_TRADE_ITEM_COUNT	(128)
struct STradeUnit
{
	uint32		m_uDataID;
	SItemType	m_typeItem;
	uchar		m_yCount;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_uDataID = UINT_MAX;
		m_typeItem.Clear();
		m_yCount = 0;
	}

	uint32	GetBufSize(void) const;

};

struct SScriptParamTrade
{
	uchar		m_yItemCount;
	STradeUnit	m_aTradeItem[MAX_TRADE_ITEM_COUNT];
	BOOL		m_bRepair;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_yItemCount = 0;

		/*~~~~~~*/
		uint32	i;
		/*~~~~~~*/

		for(i = 0; i < MAX_TRADE_ITEM_COUNT; i++)
		{
			m_aTradeItem[i].Reset();
		}
	}

	uint32	GetBufSize(void) const;

};

struct ScriptParam_QuestUpdate
{
	QuestID_t	m_QuestId;

	FlagTool	m_flag;
	SScriptString	m_strQuestTitle;
	SScriptString	m_strQuestName;
	SScriptString	m_strQuestTarget;
	SScriptString	m_strQuestSubmitNPC;
	SScriptString	m_strQuestManual;
	SScriptString	m_strQuestInfo;
	SScriptString	m_strQuestHelp;

	uchar		m_yBonusCount;
	SQuestBonus	m_aBonus[MAX_QUEST_BONUS_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_QuestId = -1;
		m_flag.Clear();

		m_strQuestTitle.Reset();
		m_strQuestName.Reset();
		m_strQuestTarget.Reset();
		m_strQuestSubmitNPC.Reset();
		m_strQuestManual.Reset();
		m_strQuestInfo.Reset();
		m_strQuestHelp.Reset();

		m_yBonusCount = 0;

		for(int32 i = 0; i < MAX_QUEST_BONUS_COUNT; ++i)
		{
			m_aBonus[i].Reset();
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestID(QuestID_t nQuestId)
	{
		m_QuestId = nQuestId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestTitle(const SScriptString *pstrText)
	{
		m_strQuestTitle = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(0, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestName(const SScriptString *pstrText)
	{
		m_strQuestName = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(1, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestTarget(const SScriptString *pstrText)
	{
		m_strQuestTarget = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(2, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestSubmitNPC(const SScriptString *pstrText)
	{
		m_strQuestSubmitNPC = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(3, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestManual(const SScriptString *pstrText)
	{
		m_strQuestManual = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(4, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestInfo(const SScriptString *pstrText)
	{
		m_strQuestInfo = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(5, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestHelp(const SScriptString *pstrText)
	{
		m_strQuestHelp = *pstrText;
		if(pstrText->m_Size > 0) m_flag.UpdateBit(6, TRUE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddBonus(const SQuestBonus *pBonus)
	{
		if(m_yBonusCount < MAX_QUEST_BONUS_COUNT)
		{
			m_aBonus[m_yBonusCount] = *pBonus;
			m_yBonusCount++;

			m_flag.UpdateBit(7, TRUE);
		}
	}

	uint32	GetBufSize(void) const;

};

struct ScriptParam_QuestDengmi
{
	int32	m_nQuestionIndex;
	int32	m_nAnswerTimer;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Reset(void)
	{
		m_nQuestionIndex = -1;
		m_nAnswerTimer = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestDengmi_QuestionIndex(int32 nIndex)
	{
		m_nQuestionIndex = nIndex;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetQuestDengmi_AnswerTimer(int32 nTimer)
	{
		m_nAnswerTimer = nTimer;
	}

	uint32	GetBufSize(void) const;

};
#endif
