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

		/* ���ñ���л��ǽű��е����ݽ������ */
		memo.strQuestName = pQuestList->szQuestName;
		memo.strQuestDesc = pQuestList->szQuestDesc;
		memo.strQuestHelp = pQuestList->szQuestHelp;
		memo.strQuestManual = pQuestList->szQuestManual;
		memo.strQuestSubmitNPC = szSubmitNPC;

		/* ����Ƿ�����Ҫͬ������ķ����������� */
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

	/* ��������Ĵ��� */
	else if (pQuestList->nQuestType == 1)
	{
		_QUEST_INFO& mi = ScriptQuestInterface::GetQuestInfo(pQuestList->nQuestID);
		char			szSubmitNPC[64] = { 0 };

		snprintf(szSubmitNPC, 64, "@npc_%llu", pQuestList->nSubmitNPCGUID);

		/* ���ñ���л��ǽű��е����ݽ������ */
		memo.strQuestName = mi.m_misName;
		memo.strQuestDesc = mi.m_misDesc;
		memo.strQuestHelp = mi.m_misHelp;
		memo.strQuestManual = mi.m_misManual;
		memo.strQuestSubmitNPC = szSubmitNPC;

		/* ����Ƿ�����Ҫͬ������ķ����������� */
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
		tmp = dy::str_format("����:%d", bonus.m_uExp);
		break;

	case QUEST_BONUS_TYPE_MONEY:
		assert(false);
		break;

	case QUEST_BONUS_TYPE_MONEY1: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY2: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY3: /* ��Ǯ */
		tmp = dy::str_format("��:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY4: /* ��Ǯ */
		tmp = dy::str_format("��͢����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY5: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY6: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY7: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY8: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_MONEY9: /* ��Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_ITEM:	/* ��Ʒ */
		assert(false);
		break;

	case QUEST_BONUS_TYPE_ITEM_RAND:					/* �����Ʒ */
		assert(false);
		break;

	case QUEST_BONUS_TYPE_ITEM_RADIO:					/* ��ѡ1��Ʒ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_VIGOR:						/* ���� */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_CHARM:						/* ���� */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GENIUS:						/* �츳 */
		tmp = dy::str_format("�츳:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GUILD_EXP:					/* ��ᾭ�� */
		tmp = dy::str_format("��ᾭ��:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_FOOD:				/* ����ʳ�� */
		tmp = dy::str_format("����ʳ��:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_MONEY:				/* ���ҽ�Ǯ */
		tmp = dy::str_format("���ҽ�Ǯ:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_WOOD:				/* ����ľ�� */
		tmp = dy::str_format("����ľ��:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_COUNTRY_METAL:				/* ���ҽ��� */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_WEIWANG:					/* ���� */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_INHERENCE_EXP:		/* �츳���� */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
		break;

	case QUEST_BONUS_TYPE_GUILD_MONEY:		/* ����Ǯ */
		tmp = dy::str_format("����:%d", bonus.m_uMoney);
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
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uExp);
				break;

			case QUEST_BONUS_TYPE_MONEY:
				assert(false);
				break;

			case QUEST_BONUS_TYPE_MONEY1: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY2: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY3: /* ��Ǯ */
				back.rewardDesc = dy::str_format("��:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY4: /* ��Ǯ */
				back.rewardDesc = dy::str_format("��͢����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY5: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY6: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY7: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY8: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_MONEY9: /* ��Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_ITEM:	/* ��Ʒ */
				back.itemId = pItem->pItemImpl->GetIdTable();
				break;

			case QUEST_BONUS_TYPE_ITEM_RAND:					/* �����Ʒ */
				back.itemId = pItem->pItemImpl->getId();
				break;

			case QUEST_BONUS_TYPE_ITEM_RADIO:					/* ��ѡ1��Ʒ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_VIGOR:						/* ���� */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_CHARM:						/* ���� */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GENIUS:						/* �츳 */
				back.rewardDesc = dy::str_format("�츳:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GUILD_EXP:					/* ��ᾭ�� */
				back.rewardDesc = dy::str_format("��ᾭ��:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_FOOD:				/* ����ʳ�� */
				back.rewardDesc = dy::str_format("����ʳ��:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_MONEY:				/* ���ҽ�Ǯ */
				back.rewardDesc = dy::str_format("���ҽ�Ǯ:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_WOOD:				/* ����ľ�� */
				back.rewardDesc = dy::str_format("����ľ��:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_COUNTRY_METAL:				/* ���ҽ��� */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_WEIWANG:					/* ���� */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_INHERENCE_EXP:		/* �츳���� */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;

			case QUEST_BONUS_TYPE_GUILD_MONEY:		/* ����Ǯ */
				back.rewardDesc = dy::str_format("����:%d", pBonus->m_uMoney);
				break;
			}
		}
		
	}
	return true;
}