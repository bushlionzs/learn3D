#include "stdafx.h"
#include "QuestManager.h"
#include "GameTableData.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "GameDataStructQuest.h"
#include "application_util.h"
#include "string_util.h"
#include "KItem.h"

QuestManager::QuestManager()
{

}

QuestManager::~QuestManager()
{

}

void QuestManager::clearQuest()
{
	mQuestList.clear();
}

void QuestManager::addQuest(const ::base::Quest& quest)
{
	mQuestList.emplace_back(quest);
}

void QuestManager::modifyQuest(const ::base::Quest& quest)
{
	for (uint32_t i = 0; i < mQuestList.size(); i++)
	{
		if (quest.quest_id() == mQuestList[i].quest_id())
		{
			mQuestList[i] = quest;
			break;
		}
	}
}

bool QuestManager::getQuestInfoMemo(uint32_t index, QuestInfoMemo& memo)
{
	const base::Quest& quest = mQuestList[index];

	auto quest_id = quest.quest_id();

	TABLE_DEFINEHANDLE(s_pQuestListDBC, TABLE_QUEST_LIST);

	const _TABLE_QUEST_LIST* pQuestList = 
		(const _TABLE_QUEST_LIST*)s_pQuestListDBC->GetFieldDataByIndex(quest_id);
	if (pQuestList->nQuestType == 0 || pQuestList->nQuestType == 2)
	{
		char	szSubmitNPC[64] = { 0 };

		snprintf(szSubmitNPC, 64, "@npc_%llu", pQuestList->nSubmitNPCGUID);

		/* 先用表格中或是脚本中的数据进行填充 */
		memo.strQuestName = pQuestList->szQuestName;
		memo.strQuestDesc = pQuestList->szQuestDesc;
		memo.strQuestHelp = pQuestList->szQuestHelp;
		memo.strQuestManual = pQuestList->szQuestManual;
		memo.strQuestSubmitNPC = szSubmitNPC;

		/* 检查是否有需要同步处理的服务器端数据 */
		_QUEST_EXT_INFO* pMEI = ScriptQuestInterface::GetQuestExtInfo(pQuestList->nQuestID);

		if (pMEI)
		{
			if (pMEI->m_Flag.IsSetBit(1)) memo.strQuestName = pMEI->m_strQuestName;
			if (pMEI->m_Flag.IsSetBit(5)) memo.strQuestDesc = pMEI->m_strQuestInfo;
			if (pMEI->m_Flag.IsSetBit(6)) memo.strQuestHelp = pMEI->m_strQuestHelp;
			if (pMEI->m_Flag.IsSetBit(4)) memo.strQuestManual = pMEI->m_strQuestManual;
			if (pMEI->m_Flag.IsSetBit(3)) memo.strQuestSubmitNPC = pMEI->m_strQuestSubmitNPC;
		}

		FormatQuestString(memo.strQuestName);


		FormatQuestString(memo.strQuestDesc);


		FormatQuestString(memo.strQuestHelp);

		FormatQuestString(memo.strQuestManual);
		FormatQuestString(memo.strQuestSubmitNPC);

	}

	/* 副本任务的处理 */
	else if (pQuestList->nQuestType == 1)
	{
		_QUEST_INFO& mi = ScriptQuestInterface::GetQuestInfo(pQuestList->nQuestID);
		char			szSubmitNPC[64] = { 0 };

		snprintf(szSubmitNPC, 64, "@npc_%llu", pQuestList->nSubmitNPCGUID);

		/* 先用表格中或是脚本中的数据进行填充 */
		memo.strQuestName = mi.m_misName;
		memo.strQuestDesc = mi.m_misDesc;
		memo.strQuestHelp = mi.m_misHelp;
		memo.strQuestManual = mi.m_misManual;
		memo.strQuestSubmitNPC = szSubmitNPC;

		/* 检查是否有需要同步处理的服务器端数据 */
		_QUEST_EXT_INFO* pMEI = ScriptQuestInterface::GetQuestExtInfo(pQuestList->nQuestID);

		if (pMEI)
		{
			if (pMEI->m_Flag.IsSetBit(1)) memo.strQuestName = pMEI->m_strQuestName;
			if (pMEI->m_Flag.IsSetBit(5)) memo.strQuestDesc = pMEI->m_strQuestInfo;
			if (pMEI->m_Flag.IsSetBit(6)) memo.strQuestHelp = pMEI->m_strQuestHelp;
			if (pMEI->m_Flag.IsSetBit(4)) memo.strQuestManual = pMEI->m_strQuestManual;
			if (pMEI->m_Flag.IsSetBit(3)) memo.strQuestSubmitNPC = pMEI->m_strQuestSubmitNPC;
		}

		FormatQuestString(memo.strQuestName);


		FormatQuestString(memo.strQuestDesc);

		FormatQuestString(memo.strQuestHelp);


		FormatQuestString(memo.strQuestManual);


		FormatQuestString(memo.strQuestSubmitNPC);

	}
	else
	{
		return false;
	}

	return true;
}

std::string QuestManager::getQuestString(uint32_t type, SQuestBonus& bonus)
{
	std::string tmp;
	switch (type)
	{
	case QUEST_BONUS_TYPE_EXP:
		tmp = dy::str_format("经验:%d", bonus.m_uExp);
		break;

	case QUEST_BONUS_TYPE_MONEY:
		assert(false);
		break;

	case QUEST_BONUS_TYPE_MONEY1: /* 金钱 */
		tmp = dy::str_format("银卡:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY2: /* 金钱 */
		tmp = dy::str_format("现银:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY3: /* 金钱 */
		tmp = dy::str_format("金卡:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY4: /* 金钱 */
		tmp = dy::str_format("朝廷声望:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY5: /* 金钱 */
		tmp = dy::str_format("声望:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY6: /* 金钱 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY7: /* 金钱 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY8: /* 金钱 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY9: /* 金钱 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_ITEM:	/* 物品 */
		assert(false);
		break;

	case QUEST_BONUS_TYPE_ITEM_RAND:					/* 随机物品 */
		assert(false);
		break;

	case QUEST_BONUS_TYPE_ITEM_RADIO:					/* 多选1物品 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_VIGOR:						/* 活力 */
		tmp = dy::str_format("活力:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_CHARM:						/* 魅力 */
		tmp = dy::str_format("魅力:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GENIUS:						/* 天赋 */
		tmp = dy::str_format("天赋:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GUILD_EXP:					/* 帮会经验 */
		tmp = dy::str_format("帮会经验:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_FOOD:				/* 国家食材 */
		tmp = dy::str_format("国家食材:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_MONEY:				/* 国家金钱 */
		tmp = dy::str_format("国家金钱:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_WOOD:				/* 国家木材 */
		tmp = dy::str_format("国家木材:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_METAL:				/* 国家金属 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_WEIWANG:					/* 威望 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_INHERENCE_EXP:		/* 天赋经验 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GUILD_MONEY:		/* 帮会金钱 */
		tmp = dy::str_format("荣誉:%d", bonus.m_uMoney);
		break;
	}

	return tmp;
}

bool QuestManager::getQuestReward(uint32_t quest_id, std::vector<QuestReward>& rewardlist)
{
	_QUEST_INFO::QuestRewardItem* pItem = NULL;

	_QUEST_EXT_INFO* pMEI = ScriptQuestInterface::GetQuestExtInfo(quest_id);

	if (pMEI )
	{
		assert(false);
	}
	else
	{
		_QUEST_INFO& info =  ScriptQuestInterface::GetQuestInfo(quest_id);

		for (uint32_t i = 0; i < info.m_QuestRewardItem.size(); i++)
		{
			pItem = &(info.m_QuestRewardItem[i]);

			SQuestBonus* pBonus = &pItem->ItemData;
			rewardlist.emplace_back();
			QuestReward& back = rewardlist.back();

			switch (pBonus->m_nType)
			{
			case QUEST_BONUS_TYPE_EXP:
				back.rewardDesc = dy::str_format("经验:%d", pBonus->m_uExp);
				break;

			case QUEST_BONUS_TYPE_MONEY:
				assert(false);
				break;

			case QUEST_BONUS_TYPE_MONEY1: /* 金钱 */
				back.rewardDesc = dy::str_format("银卡:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY2: /* 金钱 */
				back.rewardDesc = dy::str_format("现银:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY3: /* 金钱 */
				back.rewardDesc = dy::str_format("金卡:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY4: /* 金钱 */
				back.rewardDesc = dy::str_format("朝廷声望:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY5: /* 金钱 */
				back.rewardDesc = dy::str_format("声望:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY6: /* 金钱 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY7: /* 金钱 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY8: /* 金钱 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY9: /* 金钱 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_ITEM:	/* 物品 */
				back.itemId = pItem->pItemImpl->GetIdTable();
				break;

			case QUEST_BONUS_TYPE_ITEM_RAND:					/* 随机物品 */
				back.itemId = pItem->pItemImpl->getId();
				break;

			case QUEST_BONUS_TYPE_ITEM_RADIO:					/* 多选1物品 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_VIGOR:						/* 活力 */
				back.rewardDesc = dy::str_format("活力:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_CHARM:						/* 魅力 */
				back.rewardDesc = dy::str_format("魅力:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GENIUS:						/* 天赋 */
				back.rewardDesc = dy::str_format("天赋:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GUILD_EXP:					/* 帮会经验 */
				back.rewardDesc = dy::str_format("帮会经验:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_FOOD:				/* 国家食材 */
				back.rewardDesc = dy::str_format("国家食材:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_MONEY:				/* 国家金钱 */
				back.rewardDesc = dy::str_format("国家金钱:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_WOOD:				/* 国家木材 */
				back.rewardDesc = dy::str_format("国家木材:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_METAL:				/* 国家金属 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_WEIWANG:					/* 威望 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_INHERENCE_EXP:		/* 天赋经验 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GUILD_MONEY:		/* 帮会金钱 */
				back.rewardDesc = dy::str_format("荣誉:%d", pBonus->m_uMoney);
				break;
			}
		}
		
	}
	return true;
}