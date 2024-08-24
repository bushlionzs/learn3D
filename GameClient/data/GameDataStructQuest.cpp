#include "stdafx.h"
#include "Data/Struct/GameDataStructQuest.h"

#include "ScriptCacheMgr.h"
#include "GameDataManager.h"
#include "GameDataCharacter.h"
#include "GameTableManager.h"
#include "KItemManager.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "KItem.h"
#include "KTable.h"
#include "TAB.h"
#include "application_util.h"
#include "OgreResourceManager.h"


const char* szScriptQuestBeginStr = "--MisDescBegin";
const char* szScriptQuestEndStr   = "--MisDescEnd";

/*
=======================================================================================================================
类相关静态变量定义
=======================================================================================================================
*/
_QUEST_INFO*ScriptQuestInterface::g_misInfoPtr = nullptr;
MisInfo		ScriptQuestInterface::g_misInfo;
MisExtInfo	ScriptQuestInterface::g_misExtInfo;

/* 解析标记字符串 */
const char *ScriptQuestInterface::tokens_cp[] =
{
	"g_MissionName",		
	"g_MissionTarget",		
	"g_MissionInfo",		
	"g_ContinueInfo",		
	"g_MissionCompleted",	
	"g_MissionHelp",		
	"g_LevelLess",			
	"g_MissionKind",		
	"g_Target",				
	"g_ExtTarget",			
	"g_ExpBonus",			
	"g_BonusMoney1",		
	"g_BonusMoney2",		
	"g_BonusMoney3",		
	"g_BonusMoney4",		
	"g_BonusMoney5",		
	"g_BonusMoney6",		
	"g_BonusItem",			
	"g_BonusChoiceItem",	
	"g_GroupPoint",			
};

/* 支持解析的函数列表，与上表对应 */
parseLine ScriptQuestInterface::fns_cp[] =
{
	(parseLine)ScriptQuestInterface::parseQuestName_CP,		
	(parseLine)ScriptQuestInterface::parseQuestTarget_CP,	
	(parseLine)ScriptQuestInterface::parseQuestInfo_CP,		
	(parseLine)ScriptQuestInterface::parseQuestContinue_CP,	
	(parseLine)ScriptQuestInterface::parseQuestCompleted_CP,
	(parseLine)ScriptQuestInterface::parseQuestHelp_CP,		
	(parseLine)ScriptQuestInterface::parseLevelLess_CP,		
	(parseLine)ScriptQuestInterface::parseQuestKind_CP,		
	(parseLine)ScriptQuestInterface::parseTarget_CP,		
	(parseLine)ScriptQuestInterface::parseExtTarget_CP,		
	(parseLine)ScriptQuestInterface::parseExpBonus_CP,		
	(parseLine)ScriptQuestInterface::parseBonusMoney1_CP,	
	(parseLine)ScriptQuestInterface::parseBonusMoney2_CP,	
	(parseLine)ScriptQuestInterface::parseBonusMoney3_CP,	
	(parseLine)ScriptQuestInterface::parseBonusMoney4_CP,	
	(parseLine)ScriptQuestInterface::parseBonusMoney5_CP,	
	(parseLine)ScriptQuestInterface::parseBonusMoney6_CP,	
	(parseLine)ScriptQuestInterface::parseBonusItem_CP,		
	(parseLine)ScriptQuestInterface::parseBonusChoiceItem_CP,
	(parseLine)ScriptQuestInterface::parseGroupPoint_CP,	
};

/* 解析的数量 */
const int32 ScriptQuestInterface::fns_cp_count = sizeof(ScriptQuestInterface::fns_cp) / sizeof(ScriptQuestInterface::fns_cp[0]);

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::RemoveQuestExtInfoByIndex(int32 nIndex)
{
	const base::Quest & questInfo = GameDataManager::GetSingleton().getQuestManager()->getQuest(nIndex);
	int32					scriptId = questInfo.script_id();
	_QUEST_EXT_INFO	*pMei = GetQuestExtInfo(questInfo.quest_id());

	if(!pMei) return;

	uint32	i = 0;

	for(i = 0; i < pMei->m_QuestRewardItem.size(); i++)
	{
		if(pMei->m_QuestRewardItem[i].pItemImpl)
			KItemManager::GetSingleton().DestroyItem((KItem*)pMei->m_QuestRewardItem[i].pItemImpl);
	}

	pMei->m_QuestRewardItem.clear();

	MisExtInfo::iterator	it = g_misExtInfo.find(questInfo.quest_id());

	if(it != g_misExtInfo.end())
	{
		g_misExtInfo.erase(it);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::RemoveQuestExtInfoByQuestId(int32 nQuestId)
{
	_QUEST_EXT_INFO	*pMei = GetQuestExtInfo(nQuestId);

	if(!pMei) return;

	for(uint32 i = 0; i < pMei->m_QuestRewardItem.size(); i++)
	{
		pMei->m_QuestRewardItem[i].ItemData.Reset();
	}

	pMei->m_QuestRewardItem.clear();

	MisExtInfo::iterator	it = g_misExtInfo.find(nQuestId);

	if(it != g_misExtInfo.end())
	{
		g_misExtInfo.erase(it);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::RemoveQuestInfo(int32 nIndex)
{
	RemoveQuestExtInfoByIndex(nIndex);

	const base::Quest& questInfo = GameDataManager::GetSingleton().getQuestManager()->getQuest(nIndex);

	int32 scriptId = questInfo.script_id();
	int32_t quest_id = questInfo.quest_id();
	uint32	i = 0;

	g_misInfoPtr = &(GetQuestInfo(quest_id));

	/* 需求任务 */
	for(i = 0; i < g_misInfoPtr->m_QuestDemandItem.size(); i++)
	{
		if(g_misInfoPtr->m_QuestDemandItem[i].pDemandItem) delete g_misInfoPtr->m_QuestDemandItem[i].pDemandItem;

		if(g_misInfoPtr->m_QuestDemandItem[i].pItemImpl)
			KItemManager::GetSingleton().DestroyItem((KItem*)(g_misInfoPtr->m_QuestDemandItem[i].pItemImpl));
	}

	g_misInfoPtr->m_QuestDemandItem.clear();

	/* 奖励物品 */
	for(i = 0; i < g_misInfoPtr->m_QuestRewardItem.size(); i++)
	{
		g_misInfoPtr->m_QuestRewardItem[i].ItemData.Reset();
	}

	g_misInfoPtr->m_QuestRewardItem.clear();

	/* 查找NPC */
	for(i = 0; i < g_misInfoPtr->m_vecQuestDemandNPC.size(); ++i)
	{
		_QUEST_INFO::QuestDemandFindNPC & FindNPC = g_misInfoPtr->m_vecQuestDemandNPC[i];
		for(int32 j = 0; j < FindNPC.vecItemInfo.size(); ++j)
		{
			if(FindNPC.vecItemInfo[j].pDemandItem) delete FindNPC.vecItemInfo[j].pDemandItem;

			if(FindNPC.vecItemInfo[j].pItemImpl)
				KItemManager::GetSingleton().DestroyItem((KItem*)(FindNPC.vecItemInfo[j].pItemImpl));
		}
	}

	g_misInfoPtr->m_vecQuestDemandNPC.clear();

	/* 杀怪任务 */
	for(i = 0; i < g_misInfoPtr->m_vecQuestDemandKill.size(); ++i)
	{
		if(g_misInfoPtr->m_vecQuestDemandKill[i].pDemandKill) 
			delete g_misInfoPtr->m_vecQuestDemandKill[i].pDemandKill;
	}

	g_misInfoPtr->m_vecQuestDemandKill.clear();
	g_misInfoPtr->m_vecQuestCustom.clear();
	g_misInfoPtr->m_vecQuestGroupPoint.clear();

	MisInfo::iterator	it = g_misInfo.find(quest_id);

	if(it != g_misInfo.end())
	{
		g_misInfo.erase(it);
	}

	g_misInfoPtr = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::ClearQuest_ScriptId(int32 nScriptId)
{
	MisInfo::iterator	it = g_misInfo.find(nScriptId);

	if(it == g_misInfo.end()) return;

	RemoveQuestExtInfoByQuestId(nScriptId);

	uint32			i = 0;
	_QUEST_INFO	*pQuestInfo = &(it->second);

	/* 采集任务 */
	for(i = 0; i < pQuestInfo->m_QuestDemandItem.size(); i++)
	{
		if(pQuestInfo->m_QuestDemandItem[i].pDemandItem) delete pQuestInfo->m_QuestDemandItem[i].pDemandItem;

		if(pQuestInfo->m_QuestDemandItem[i].pItemImpl)
		{
			KItemManager::GetSingleton().DestroyItem((KItem*)(pQuestInfo->m_QuestDemandItem[i].pItemImpl));
			pQuestInfo->m_QuestDemandItem[i].pItemImpl = 0;
		}
	}

	pQuestInfo->m_QuestDemandItem.clear();

	/* 任务奖励 */
	for(i = 0; i < pQuestInfo->m_QuestRewardItem.size(); i++)
	{
		if(pQuestInfo->m_QuestRewardItem[i].pItemImpl)
		{
			KItemManager::GetSingleton().DestroyItem((KItem*)(pQuestInfo->m_QuestRewardItem[i].pItemImpl));
			pQuestInfo->m_QuestRewardItem[i].pItemImpl = 0;
		}
	}

	pQuestInfo->m_QuestRewardItem.clear();

	/* 送信任务 */
	for(i = 0; i < pQuestInfo->m_vecQuestDemandNPC.size(); ++i)
	{
		_QUEST_INFO::QuestDemandFindNPC & FindNPC = pQuestInfo->m_vecQuestDemandNPC[i];
		for(int32 j = 0; j < FindNPC.vecItemInfo.size(); ++j)
		{
			if(FindNPC.vecItemInfo[j].pDemandItem) delete FindNPC.vecItemInfo[j].pDemandItem;

			if(FindNPC.vecItemInfo[j].pItemImpl)
				KItemManager::GetSingleton().DestroyItem((KItem*)(FindNPC.vecItemInfo[j].pItemImpl));
		}
	}

	pQuestInfo->m_vecQuestDemandNPC.clear();

	/* 杀怪任务 */
	for(i = 0; i < pQuestInfo->m_vecQuestDemandKill.size(); ++i)
	{
		if(pQuestInfo->m_vecQuestDemandKill[i].pDemandKill)
			delete pQuestInfo->m_vecQuestDemandKill[i].pDemandKill;
	}

	pQuestInfo->m_vecQuestDemandKill.clear();

	pQuestInfo->m_vecQuestCustom.clear();
	pQuestInfo->m_vecQuestGroupPoint.clear();

	g_misInfo.erase(it);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::clearAllQuest(void)
{
	while(!g_misInfo.empty())
	{
		ClearQuest_ScriptId(g_misInfo.begin()->first);

		/*
		 * RemoveQuestInfo( ScriptQuestInterface::g_misInfo.begin()->first );
		 */
	}

	g_misInfo.clear();
	g_misExtInfo.clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::FillQuestInfo(int32 nQuestId, int32 nScriptID)
{
	if(nullptr == KObjectManager::GetSingleton().getMySelf()) return;

	KCharatcterBaseData* pData = KObjectManager::GetSingleton().getMySelf()->GetCharacterData();
	if(nullptr == pData) return;

	/*
	 * 查找任务信息 ;
	 */
	TABLE_DEFINEHANDLE(s_pQuestListDBC, TABLE_QUEST_LIST);

	const _TABLE_QUEST_LIST *pQuestList = (const _TABLE_QUEST_LIST *) s_pQuestListDBC->GetFieldDataByIndex(nQuestId);

	if(!pQuestList) return;

	/*
	 * 普通任务的处理 或 循环任务的处理CZG ;
	 */
	if(pQuestList->nQuestType == 0 || pQuestList->nQuestType == 2)
	{
		g_misInfoPtr = &(GetQuestInfo(nQuestId));

		/* 以下为经验和金钱以及声望相关奖励，这部分为动态信息，所在必须即时刷新。 */
		std::vector<_QUEST_INFO::QuestRewardItem>::iterator	it = g_misInfoPtr->m_QuestRewardItem.begin();

		while(it != g_misInfoPtr->m_QuestRewardItem.end())
		{
			_QUEST_INFO::QuestRewardItem & item = *it;

			if
			(
				item.ItemData.m_nType != QUEST_BONUS_TYPE_ITEM
			&&	item.ItemData.m_nType != QUEST_BONUS_TYPE_ITEM_RAND
			&&	item.ItemData.m_nType != QUEST_BONUS_TYPE_ITEM_RADIO
			)
			{
				it = g_misInfoPtr->m_QuestRewardItem.erase(it);
			}
			else
			{
				++it;
			}
		}

		std::vector<_QUEST_INFO::QuestRewardItem> vecNoItemBonus;

		/* 经验奖励无法显示 */
		uint32 uExpReward = 0;

		if(pQuestList->nExpRewardP1 > 0)
		{
			uExpReward += pQuestList->nExpRewardP1;
		}

		if(pQuestList->nExpRewardP2 > 0)
		{
			uExpReward += pQuestList->nExpRewardP2 * KObjectManager::GetSingleton().getMySelf()->GetCharacterData()->Get_Level();
		}

		if(pQuestList->nExpRewardP3 > 0)
		{
			uExpReward += pQuestList->nExpRewardP3 *
				pData->Get_Level() *
				pData->Get_Level();
		}

		if(uExpReward > 0)
		{
			_QUEST_INFO::QuestRewardItem	newRewardItem;

			newRewardItem.ItemData.SetExp(uExpReward);
			newRewardItem.bSelected = FALSE;
			vecNoItemBonus.push_back(newRewardItem);
		}

		uint32 uMoneyReward = 0;

		if(pQuestList->nMoneyRewardP1 > 0)
		{
			uMoneyReward += pQuestList->nMoneyRewardP1;
		}

		if(pQuestList->nMoneyRewardP2 > 0)
		{
			uMoneyReward += pQuestList->nMoneyRewardP2 * pData->Get_Level();
		}

		if(pQuestList->nMoneyRewardP3 > 0)
		{
			uMoneyReward += pQuestList->nMoneyRewardP3 *
				pData->Get_Level() *
				pData->Get_Level();
		}

		if(uMoneyReward > 0)
		{
			/* 非绑定银币 */
			if(pQuestList->nMoneyRewardType == 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney2(uMoneyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 绑定银币 */
			else if(pQuestList->nMoneyRewardType == 1)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney1(uMoneyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 非绑定金币 */
			if(pQuestList->nMoneyRewardType == 2)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney3(uMoneyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
		}

		/* 声望 */
		if(pQuestList->nShengWangType >= 0)
		{
			uint32 nShengWang = 0;

			if(pQuestList->nShengWangRewartP1 > 0) nShengWang += pQuestList->nShengWangRewartP1;

			if(pQuestList->nShengWangRewartP2 > 0)
			{
				nShengWang += pQuestList->nShengWangRewartP2 * pData->Get_Level();
			};

			if(pQuestList->nShengWangRewartP3 > 0)
			{
				nShengWang += pQuestList->nShengWangRewartP3 *
					pData->Get_Level() *
					pData->Get_Level();
			}

			/* 朝廷声望 */
			if(pQuestList->nShengWangType == 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney4(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 江湖声望 */
			else if(pQuestList->nShengWangType == 1)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney5(nShengWang);
				newRewardItem.bSelected = FALSE;
				//g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem); //huangqinqi
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* PK */
			else if(pQuestList->nShengWangType == 2)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney7(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 荣誉 */
			else if(pQuestList->nShengWangType == 3)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney6(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 帮贡 */
			else if(pQuestList->nShengWangType == 4)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney8(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}

			/* 文采 */
			else if(pQuestList->nShengWangType == 5)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetMoney9(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nShengWangType == 6)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetWeiWang(nShengWang);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nShengWangType == 7) // 7 天赋经验
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				assert(false);//todo
				//newRewardItem.ItemData.SetInherenceExp(GAME_DATA_PLAYER_PTR->RefixInherenceExp(nShengWang));
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
		}

		/* 活力 */
		if(pQuestList->nEnergyRewardType >= 0 && pQuestList->nEnergyReward > 0)
		{
			if(pQuestList->nEnergyRewardType == 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.Set_Property_Vigor(pQuestList->nEnergyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 1)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetCharm(pQuestList->nEnergyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 2)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetGenius(pQuestList->nEnergyReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
		}

		/* 帮会奖励 */
		if(pQuestList->nGuildRewardType >= 0 && pQuestList->nGuildReward > 0)
		{
			if(pQuestList->nEnergyRewardType == 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetGuildExp(pQuestList->nGuildReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 1)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetCountryFood(pQuestList->nGuildReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 2)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetCountryMoney(pQuestList->nGuildReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 3)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetCountryWood(pQuestList->nGuildReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
			else if(pQuestList->nEnergyRewardType == 4)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;

				newRewardItem.ItemData.SetCountryMetal(pQuestList->nGuildReward);
				newRewardItem.bSelected = FALSE;
				vecNoItemBonus.push_back(newRewardItem);
			}
		}

		/* 先插入金钱和经验相关奖励 */
		g_misInfoPtr->m_QuestRewardItem.insert
			(
				g_misInfoPtr->m_QuestRewardItem.begin(),
				vecNoItemBonus.begin(),
				vecNoItemBonus.end()
			);

		if(!g_misInfoPtr->m_bFill)
		{
			g_misInfoPtr->m_nQuestID = nQuestId;
			g_misInfoPtr->m_nType = pQuestList->nQuestType;
			g_misInfoPtr->m_nLevel = 1;
			g_misInfoPtr->m_nKind = 1;

			/* 固定奖励 */
			if(pQuestList->nFixItemID1 != -1 && pQuestList->nFixItemNum1 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem *pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nFixItemID1);

				if(pItem)
				{
					newRewardItem.ItemData.SetItem(pQuestList->nFixItemID1, pQuestList->nFixItemNum1);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nFixItemID2 != -1 && pQuestList->nFixItemNum2 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem *pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nFixItemID2);

				if(pItem)
				{
					newRewardItem.ItemData.SetItem(pQuestList->nFixItemID2, pQuestList->nFixItemNum2);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nFixItemID3 != -1 && pQuestList->nFixItemNum3 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nFixItemID3);

				if(pItem)
				{
					newRewardItem.ItemData.SetItem(pQuestList->nFixItemID3, pQuestList->nFixItemNum3);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nFixItemID4 != -1 && pQuestList->nFixItemNum4 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nFixItemID4);

				if(pItem)
				{
					newRewardItem.ItemData.SetItem(pQuestList->nFixItemID4, pQuestList->nFixItemNum4);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			/* 选择奖励物品 */
			std::vector<std::string>	vRet;
			TAB::TABFile::_ConvertStringToVector(pQuestList->szSelItemID1, vRet, "|", TRUE, TRUE);
			if (!vRet.empty())
			{
				if (vRet.size() == 1 && pQuestList->nSelItemNum1 > 0)
				{
					uint32 id = (uint32)atoi(vRet.front().c_str());

					_QUEST_INFO::QuestRewardItem	newRewardItem;
					KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(id);

					if(pItem)
					{
						newRewardItem.ItemData.SetItemRadio(id, pQuestList->nSelItemNum1);
						newRewardItem.bSelected = FALSE;
						pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
						pItem->SetVirtualtExtraInfo();
						newRewardItem.pItemImpl = pItem;
						g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
					}
				}
				else if (pQuestList->nSelItemNum1 == 0)
				{
					for (std::vector<std::string>::iterator it = vRet.begin(); it != vRet.end(); ++it)
					{
						uint32 id = (uint32)atoi(it->c_str());
						_QUEST_INFO::QuestRewardItem	newRewardItem;
						KItem *pItem = KItemManager::GetSingleton().CreateNewItem(id);

						if(pItem)
						{
							newRewardItem.ItemData.SetItemRadio(id, 1);
							newRewardItem.bSelected = FALSE;
							pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
							pItem->SetVirtualtExtraInfo();
							newRewardItem.pItemImpl = pItem;
							g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
						}
					}
				}
				else if (pQuestList->nSelItemNum1 == 1)
				{
					int32 profession = pData->GetProfession();
					if (profession >= 0 && profession <vRet.size())
					{
						uint32 id = (uint32)atoi(vRet[profession].c_str());

						_QUEST_INFO::QuestRewardItem	newRewardItem;
						KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(id);

						if(pItem)
						{
							newRewardItem.ItemData.SetItem(id, 1);
							newRewardItem.bSelected = FALSE;
							pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
							pItem->SetVirtualtExtraInfo();
							newRewardItem.pItemImpl = pItem;
							g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
						}
					}
				}
			}

			if(pQuestList->nSelItemID2 != -1 && pQuestList->nSelItemNum2 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nSelItemID2);

				if(pItem)
				{
					newRewardItem.ItemData.SetItemRadio(pQuestList->nSelItemID2, pQuestList->nSelItemNum2);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nSelItemID3 != -1 && pQuestList->nSelItemNum3 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nSelItemID3);

				if(pItem)
				{
					newRewardItem.ItemData.SetItemRadio(pQuestList->nSelItemID3, pQuestList->nSelItemNum3);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nSelItemID4 != -1 && pQuestList->nSelItemNum4 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nSelItemID4);

				if(pItem)
				{
					newRewardItem.ItemData.SetItemRadio(pQuestList->nSelItemID4, pQuestList->nSelItemNum4);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nSelItemID5 != -1 && pQuestList->nSelItemNum5 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nSelItemID5);

				if(pItem)
				{
					newRewardItem.ItemData.SetItemRadio(pQuestList->nSelItemID5, pQuestList->nSelItemNum5);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			if(pQuestList->nSelItemID6 != -1 && pQuestList->nSelItemNum6 > 0)
			{
				_QUEST_INFO::QuestRewardItem	newRewardItem;
				KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestList->nSelItemID6);

				if(pItem)
				{
					newRewardItem.ItemData.SetItemRadio(pQuestList->nSelItemID6, pQuestList->nSelItemNum6);
					newRewardItem.bSelected = FALSE;
					pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
					pItem->SetVirtualtExtraInfo();
					newRewardItem.pItemImpl = pItem;
					g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
				}
			}

			/* 子任务信息 */
			for(int32 iMisIdx = 0; iMisIdx < 5; iMisIdx++)
			{
				int32 nQuestDest = 0;
				STRING szQuestTarget;

				if(iMisIdx == 0)
				{
					nQuestDest = pQuestList->nQuestDest1;
					szQuestTarget = pQuestList->szQuestTarget1;
				}
				else if(iMisIdx == 1)
				{
					nQuestDest = pQuestList->nQuestDest2;
					szQuestTarget = pQuestList->szQuestTarget2;
				}
				else if(iMisIdx == 2)
				{
					nQuestDest = pQuestList->nQuestDest3;
					szQuestTarget = pQuestList->szQuestTarget3;
				}
				else if(iMisIdx == 3)
				{
					nQuestDest = pQuestList->nQuestDest4;
					szQuestTarget = pQuestList->szQuestTarget4;
				}
				else if(iMisIdx == 4)
				{
					nQuestDest = pQuestList->nQuestDest5;
					szQuestTarget = pQuestList->szQuestTarget5;
				}

				if(nQuestDest >= 10000 && nQuestDest <= 19999)	/* 杀怪任务 */
				{
					TABLE_DEFINEHANDLE(s_pQuestKillMonsterDBC, TABLE_QUEST_KILLMONSTER);

					const _TABLE_QUEST_KILLMONSTER	*pQuestKillMonster =
						(const _TABLE_QUEST_KILLMONSTER *) s_pQuestKillMonsterDBC->GetFieldDataByIndex(nQuestDest);

					if(pQuestKillMonster == NULL)
					{
						return;
					}

					_QUEST_INFO::QuestDemandKill	newDemandKill;

					newDemandKill.pDemandKill = new SQuestDemandKill;
					newDemandKill.pDemandKill->m_uNPCID = pQuestKillMonster->nMonsterType;	/* 这里-1行么？ */
					newDemandKill.pDemandKill->m_yCount = pQuestKillMonster->nKillNum;
					newDemandKill.pDemandKill->m_yIndex = iMisIdx;
					newDemandKill.pDemandKill->m_LevelMin = pQuestKillMonster->nMonsterLevelMin;
					newDemandKill.pDemandKill->m_LevelMax = pQuestKillMonster->nMonsterLevelMax;
					newDemandKill.szNPCName = pQuestKillMonster->szMonsterName;

					newDemandKill.szInfo = szQuestTarget;
					g_misInfoPtr->m_vecQuestDemandKill.push_back(newDemandKill);
				}
				else if(nQuestDest >= 20000 && nQuestDest <= 29999) /* 送信任务 */
				{
					TABLE_DEFINEHANDLE(s_pQuestDeliveryDBC, TABLE_QUEST_DELIVERY);

					const _TABLE_QUEST_DELIVERY *pQuestDelivery =
						(const _TABLE_QUEST_DELIVERY *) s_pQuestDeliveryDBC->GetFieldDataByIndex(nQuestDest);

					if(pQuestDelivery == NULL)
					{
						return;
					}

					bool bCustom = true;
					_QUEST_INFO::QuestDemandFindNPC	newDemandFindNPC;

					newDemandFindNPC.strInfo = szQuestTarget;
					if(pQuestDelivery->nDeliveryItemID1 != -1 && pQuestDelivery->nDeliveryItemNum1 > 0)
					{
						bCustom = false;

						KItem					*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestDelivery->nDeliveryItemID1);
						_QUEST_INFO::ItemInfo item;

						item.pDemandItem = new SQuestBonusItem;
						item.pDemandItem->m_uItemID = pQuestDelivery->nDeliveryItemID1;
						item.pDemandItem->m_yCount = pQuestDelivery->nDeliveryItemNum1;
						item.pDemandItem->m_yIndex = iMisIdx;
						pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
						pItem->SetVirtualtExtraInfo();
						item.pItemImpl = pItem;
						newDemandFindNPC.vecItemInfo.push_back(item);
					}

					if(pQuestDelivery->nDeliveryItemID2 != -1 && pQuestDelivery->nDeliveryItemNum2 > 0)
					{
						bCustom = false;

						KItem					*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestDelivery->nDeliveryItemID2);
						_QUEST_INFO::ItemInfo item;

						item.pDemandItem = new SQuestBonusItem;
						item.pDemandItem->m_uItemID = pQuestDelivery->nDeliveryItemID1;
						item.pDemandItem->m_yCount = pQuestDelivery->nDeliveryItemNum1;
						item.pDemandItem->m_yIndex = iMisIdx;
						pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
						pItem->SetVirtualtExtraInfo();
						item.pItemImpl = pItem;
						newDemandFindNPC.vecItemInfo.push_back(item);
					}

					if(pQuestDelivery->nDeliveryItemID3 != -1 && pQuestDelivery->nDeliveryItemNum3 > 0)
					{
						bCustom = false;

						KItem					*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestDelivery->nDeliveryItemID3);
						_QUEST_INFO::ItemInfo item;

						item.pDemandItem = new SQuestBonusItem;
						item.pDemandItem->m_uItemID = pQuestDelivery->nDeliveryItemID1;
						item.pDemandItem->m_yCount = pQuestDelivery->nDeliveryItemNum1;
						item.pDemandItem->m_yIndex = iMisIdx;
						pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
						pItem->SetVirtualtExtraInfo();
						item.pItemImpl = pItem;
						newDemandFindNPC.vecItemInfo.push_back(item);
					}

					if(bCustom)
					{
						_QUEST_INFO::QuestCustom	qust;

						qust.szCustomString = szQuestTarget;
						qust.nCount = 1;
						g_misInfoPtr->m_vecQuestCustom.push_back(qust);
					}
					else
					{
						g_misInfoPtr->m_vecQuestDemandNPC.push_back(newDemandFindNPC);
					}
				}
				else if(nQuestDest >= 40000 && nQuestDest <= 49999) /* 探索任务 */
				{
					TABLE_DEFINEHANDLE(s_pQuestEnterAreaDBC, TABLE_QUEST_ENTERAREA);

					const _TABLE_QUEST_ENTERAREA	*pQuestEnterArea =
						(const _TABLE_QUEST_ENTERAREA *) s_pQuestEnterAreaDBC->GetFieldDataByIndex(nQuestDest);

					if(pQuestEnterArea == NULL)
					{
						return;
					}

					_QUEST_INFO::QuestCustom	quest;

					quest.szCustomString = szQuestTarget;
					quest.nCount = 1;

					g_misInfoPtr->m_vecQuestCustom.push_back(quest);
				}
				else if(nQuestDest >= 50000 && nQuestDest <= 59999) /* 收集任务 */
				{
					TABLE_DEFINEHANDLE(s_pQuestLookItemDBC, TABLE_QUEST_LOOTITEM);

					const _TABLE_QUEST_LOOTITEM *pQuestLookItem =
						(const _TABLE_QUEST_LOOTITEM *) s_pQuestLookItemDBC->GetFieldDataByIndex(nQuestDest);

					if(pQuestLookItem == NULL)
					{
						return;
					}

					if(pQuestLookItem->nItemID1 != -1 && pQuestLookItem->nItemNum1 > 0)
					{
						KItem							*pItem = KItemManager::GetSingleton().CreateNewItem(pQuestLookItem->nItemID1);
						_QUEST_INFO::QuestDemandItem	newDemandItem;

						newDemandItem.pDemandItem = new SQuestBonusItem;
						newDemandItem.pDemandItem->m_uItemID = pQuestLookItem->nItemID1;
						newDemandItem.pDemandItem->m_yCount = pQuestLookItem->nItemNum1;
						newDemandItem.pDemandItem->m_yIndex = (BYTE) iMisIdx;
						pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
						pItem->SetVirtualtExtraInfo();
						newDemandItem.pItemImpl = pItem;
						newDemandItem.szInfo = szQuestTarget;
						g_misInfoPtr->m_QuestDemandItem.push_back(newDemandItem);
					}
				}
				else if(nQuestDest >= 60000 && nQuestDest <= 69999) /* 定点使用物品 */
				{
					TABLE_DEFINEHANDLE(s_pQuestUseItemDBC, TABLE_QUEST_USEITEM);

					const _TABLE_QUEST_USEITEM	*pQuestUseItem =
						(const _TABLE_QUEST_USEITEM *) s_pQuestUseItemDBC->GetFieldDataByIndex(nQuestDest);

					if(pQuestUseItem == NULL)
					{
						return;
					}

					_QUEST_INFO::QuestCustom	quest;

					quest.szCustomString = szQuestTarget;
					quest.nCount = 1;
					g_misInfoPtr->m_vecQuestCustom.push_back(quest);
				}
			}

			/* 标示任务描述加载完毕 */
			g_misInfoPtr->m_bFill = TRUE;
		}

		/* 如果有些为空，则使用任务列表里的信息CZG */
		if(g_misInfoPtr->m_misName.empty())
		{
			g_misInfoPtr->m_misName = pQuestList->szQuestDisp;
			FormatQuestString(g_misInfoPtr->m_misName);
		}

		if(g_misInfoPtr->m_misDesc.empty())
		{
			g_misInfoPtr->m_misDesc = pQuestList->szQuestDesc;
			FormatQuestString(g_misInfoPtr->m_misDesc);
		}

		if(g_misInfoPtr->m_misManual.empty())
		{
			g_misInfoPtr->m_misManual = pQuestList->szQuestManual;
			FormatQuestString(g_misInfoPtr->m_misManual);
		}
	}

	/*
	 * 副本任务的处理 CZG ;
	 */
	else if(pQuestList->nQuestType == 1)
	{
		g_misInfoPtr = &(GetQuestInfo(nQuestId));

		/*
		 * 未解析文件，则先解析 ;
		 */
		if(!g_misInfoPtr->m_bFill)
		{
			g_misInfoPtr->m_nQuestID = nQuestId;
			g_misInfoPtr->m_nType = 1;	/* 标记为副本任务 */
			g_misInfoPtr->m_nLevel = 1;	
			g_misInfoPtr->m_nKind = 1;


			String strFileName = GameDataManager::GetSingleton().getQuestFileName(pQuestList->nScriptID);

			if(strFileName.empty())
			{
				assert(false);
				return;
			}

			auto pos = strFileName.find_last_of("\\");
			if (pos != String::npos)
			{
				strFileName = strFileName.substr(pos + 1, strFileName.length());
			}
			const char	*lpAddress = NULL;

			std::shared_ptr<DataStream> stream = ResourceManager::getSingleton().openResource(strFileName);
			lpAddress = stream->getStreamData();
			uint32_t dwSize = stream->getStreamLength();

			if(dwSize > 0)
			{
				/* 判断起始和结束标记 */
				const char	*pTagBegin = strstr(lpAddress, szScriptQuestBeginStr);
				const char	*pTagEnd = strstr(lpAddress, szScriptQuestEndStr);

				if(NULL == pTagBegin || NULL == pTagEnd)
				{
					return;
				}

				char	*bufTarget = NULL;
				char	*line = NULL;
				int32 nTagBeginLen = (int32)strlen(szScriptQuestBeginStr);
				int32 nTagEndLen = (int32)strlen(szScriptQuestEndStr);

				if (g_bDebugPackRes)
				{
					DWORD dwBytesTar = pTagEnd - pTagBegin - nTagBeginLen;

					bufTarget = new char[dwBytesTar + nTagEndLen + 1];
					memset(bufTarget, 0, dwBytesTar + nTagEndLen + 1);

					gUtil.LuaFileConversion(lpAddress + nTagBeginLen, bufTarget, dwBytesTar);
					memcpy(bufTarget + dwBytesTar, szScriptQuestEndStr, nTagEndLen);

					line = strtok(bufTarget, "\r\n");
				}
				else
				{
					line = strtok((char*)lpAddress, "\r\n");
				}

				while(line)
				{
					if(strstr(line, "MisDescEnd")) break;

					if(strlen(line) >= 2 && (line[0] != '-' || line[1] != '-'))
					{
						for(int32 j = 0; j < fns_cp_count; j++)
						{
							if(strstr(line, tokens_cp[j]))
							{
								char szDesc[QUEST_INFO_MAXLEN] = { 0 };

								fns_cp[j](szDesc, line, j);
							}
						}
					}

					line = strtok(nullptr, "\r\n");
				}

				delete bufTarget;
			}
			else
			{
				/*
				 * KLAssert( FALSE );
				 */
				KLThrow("Invalid script file: %s", szFileName);
			}

			/* 标示任务描述加载完毕 */
			g_misInfoPtr->m_bFill = TRUE;
		}
	}

	/*
	 * 其他，无效的类型 CZG ;
	 */
	else
	{
		KLThrow
		(
			" 无效的任务类型（有效值为:0,1,2）,QuestID:%d QuestType:%d",
			nQuestId,
			pQuestList->nQuestType
		);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_INFO &ScriptQuestInterface::GetQuestInfo(uint32 QuestId)
{
	/*
	 * KCheck(QuestId != UINT_MAX);
	 */
	MisInfo::iterator	it = g_misInfo.find(QuestId);

	if(it == g_misInfo.end())
	{
		/* 添加新项 */
		_QUEST_INFO tMisInfo;

		tMisInfo.m_bFill = FALSE;
		tMisInfo.m_nQuestID = -1;
		tMisInfo.m_nType = 0;
		tMisInfo.m_nFlag = 0;
		tMisInfo.m_nLevel = -1;
		tMisInfo.m_nKind = -1;
		tMisInfo.m_nIsAutoSpeak = -1;
		tMisInfo.m_nNPCPosX = -1;
		tMisInfo.m_nNPCPosZ = -1;

		tMisInfo.m_bPlayedSound = FALSE;

		memset(tMisInfo.m_bSubPlayedSound, 0, sizeof(tMisInfo.m_bSubPlayedSound));

		g_misInfo.insert(MisInfo::value_type(QuestId, tMisInfo));
	}

	return g_misInfo[QuestId];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_QUEST_EXT_INFO *ScriptQuestInterface::GetQuestExtInfo(uint32 nQuestId)
{
	KCheck(nQuestId != UINT_MAX);

	MisExtInfo::iterator	it = g_misExtInfo.find(nQuestId);

	if(it != g_misExtInfo.end())
	{
		return &it->second;
	}

	return NULL;
}

void ScriptQuestInterface::parseQuestName_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;

	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misName = pDest;

	FormatQuestString(g_misInfoPtr->m_misName);
}

void ScriptQuestInterface::parseQuestTarget_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;

	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misManual = pDest;

	FormatQuestString(g_misInfoPtr->m_misManual);
}

void ScriptQuestInterface::parseQuestInfo_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;
	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misDesc = pDest;

	FormatQuestString(g_misInfoPtr->m_misDesc);
}

void ScriptQuestInterface::parseQuestContinue_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;

	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misContinue = pDest;

	FormatQuestString(g_misInfoPtr->m_misContinue);
}

void ScriptQuestInterface::parseQuestCompleted_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;

	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misCompleted = pDest;

	FormatQuestString(g_misInfoPtr->m_misCompleted);
}

void ScriptQuestInterface::parseQuestHelp_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '"');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	char	*pEnd = pCur + 1;

	pEnd = strrchr(pCur, '"');

	if(pEnd - pCur - 1 <= 0) return;

	int32 nLen = pEnd - pCur - 1;

	if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;

	strncat(pDest, pCur + 1, nLen);

	/* 填充 */
	g_misInfoPtr->m_misHelp = pDest;
	FormatQuestString(g_misInfoPtr->m_misHelp);
}

void ScriptQuestInterface::parseLevelLess_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	g_misInfoPtr->m_nLevel = atoi(pCur);
}

void ScriptQuestInterface::parseQuestKind_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	g_misInfoPtr->m_nKind = atoi(pCur);
}

/*
 =======================================================================================================================
    解析副本任务的目标 g_Target = {{type=0,target=22,num=2,reserve=-1},{type=1,target=33,num=3,reserve=-1}}
 =======================================================================================================================
 */
void ScriptQuestInterface::parseTarget_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	strcpy(pDest, tokens_cp[j]);

	int32 count = 0;
	int32 digit = 1;
	int32 misType = -1;
	int32 misTget = -1;
	int32 misNum = -1;
	int32 misReserve = -1;
	bool bParseInfo = false;
	char info[QUEST_INFO_MAXLEN] = { 0 };

	while(pCur++)
	{
		if(*pCur == '{')
		{
			digit = 1;
			count++;
		}
		else if(*pCur == '}')
		{
			digit = 1;
			count--;
			if(count == 0) break;
		}

		if(digit == 1 && isdigit(*pCur))
		{
			digit = 2;
			misType = atoi(pCur);
		}
		else if(digit == 3 && bParseInfo)
		{
			/* 解析出字符串 */
			char	*beg = strchr(pCur, '"');

			++beg;

			char	*end = strchr(beg, '"');
			int32 nLen = end - beg;

			if(nLen > QUEST_INFO_MAXLEN) nLen = QUEST_INFO_MAXLEN;
			strncpy(info, beg, nLen);

			pCur = end;
			bParseInfo = false;

			if(misType == 0)		/* 杀怪 */
			{
				TABLE_DEFINEHANDLE(s_pCreatureDBC, TABLE_CREATURE_ATT);

				/* 从TAB中查找定义 */
				const _TABLE_CREATURE_ATT			*pQuestNpc =
					(const _TABLE_CREATURE_ATT *) s_pCreatureDBC->GetFieldDataByIndex(misTget);
				_QUEST_INFO::QuestDemandKill	newDemandKill;

				newDemandKill.pDemandKill = new SQuestDemandKill;
				newDemandKill.pDemandKill->m_uNPCID = misTget;
				newDemandKill.pDemandKill->m_yCount = misNum;
				newDemandKill.pDemandKill->m_yIndex = (BYTE) g_misInfoPtr->m_vecQuestDemandKill.size();
				if(!pQuestNpc)
					newDemandKill.szNPCName = "???";
				else
					newDemandKill.szNPCName = (STRING) pQuestNpc->pName;
				g_misInfoPtr->m_vecQuestDemandKill.push_back(newDemandKill);
			}
			else if(misType == 1)	/* 采集 */
			{
				KItem	*pItem = KItemManager::GetSingleton().CreateNewItem(misTget);

				if(!pItem)
				{
					return;
					;//KLThrow("parseTarget_CP::非法的物品ID:%d", misTget);
				}

				pItem->SetVirtualtExtraInfo();

				_QUEST_INFO::QuestDemandItem	newDemandItem;

				newDemandItem.pDemandItem = new SQuestBonusItem;
				newDemandItem.pDemandItem->m_uItemID = misTget;
				newDemandItem.pDemandItem->m_yCount = misNum;
				newDemandItem.pDemandItem->m_yIndex = (BYTE) (g_misInfoPtr->m_vecQuestDemandKill.size() + g_misInfoPtr->m_QuestDemandItem.size());
				pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
				newDemandItem.pItemImpl = pItem;
				g_misInfoPtr->m_QuestDemandItem.push_back(newDemandItem);
			}

			misType = -1;
			misTget = -1;
			misNum = -1;
			misReserve = -1;
			memset(info, 0, sizeof(info));
		}
		else if(digit == 3 && isdigit(*pCur))
		{
			digit = 4;

			if(misTget != -1 && misNum == -1)
			{
				misNum = atoi(pCur);
				bParseInfo = true;
			}

			if(misTget == -1) misTget = atoi(pCur);
		}
		else if(digit && (*pCur == ','))
		{
			digit = 3;
		}
	}
}

/*
 =======================================================================================================================
    解析指定目标　_g_TargetExt = {{type=20,n=1,target="给某某送信"},{type=20,n=3,target="采集某某"}}
 =======================================================================================================================
 */
void ScriptQuestInterface::parseExtTarget_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	strcpy(pDest, tokens_cp[j]);

	int32 count = 0;
	int32 digit = 1;
	int32 misType = -1;
	char misTarget[QUEST_INFO_MAXLEN] = { 0 };
	int32 misNum = -1;
	bool bParseInfo = false;
	bool bFill = false;

	while(pCur++)
	{
		if(*pCur == '{')
		{
			digit = 1;
			count++;
		}
		else if(*pCur == '}')
		{
			digit = 1;
			count--;
			if(count == 0) break;
		}

		if(digit == 1 && isdigit(*pCur))
		{
			digit = 2;
			misType = atoi(pCur);
		}
		else if(digit == 3 && bParseInfo)
		{
			/* 解析出字符串 */
			char	*beg = strchr(pCur, '"');

			++beg;

			char	*end = strchr(beg, '"');
			int32 len = end - beg;

			if(len > QUEST_INFO_MAXLEN) len = QUEST_INFO_MAXLEN;
			strncpy(misTarget, beg, len);

			pCur = end;

			_QUEST_INFO::QuestCustom	qc;

			qc.szCustomString = misTarget;
			qc.nCount = misNum;

			g_misInfoPtr->m_vecQuestCustom.push_back(qc);

			misType = -1;
			misNum = -1;
			bParseInfo = false;
			memset(misTarget, 0, sizeof(misTarget));
		}
		else if(digit == 3 && isdigit(*pCur))
		{
			digit = 4;

			if(misType != -1 && misNum == -1)
			{
				misNum = atoi(pCur);
				bParseInfo = true;
			}
		}
		else if(digit && (*pCur == ','))
		{
			digit = 3;
		}
	}
}

/*
 =======================================================================================================================
    解析副本任务的经验奖励 g_ExpBonus = 1000
 =======================================================================================================================
 */
void ScriptQuestInterface::parseExpBonus_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetExp(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
    解析副本任务的金钱奖励1 g_BonusMoney1 = 1000
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney1_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney1(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
    解析副本任务的金钱奖励2 g_BonusMoney2 = 1000
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney2_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney2(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
    解析副本任务的金钱奖励3 g_BonusMoney3 = 1000
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney3_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney3(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney4_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney4(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney5_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney5(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusMoney6_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	pCur++;

	sprintf(pDest, "%d", atoi(pCur));

	int32 nValue = atoi(pCur);

	if(nValue <= 0) return;

	_QUEST_INFO::QuestRewardItem	newRewardItem;

	newRewardItem.ItemData.SetMoney6(atoi(pCur));
	newRewardItem.bSelected = FALSE;
	g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
}

/*
 =======================================================================================================================
    解析副本任务的固定奖励物品 g_BonusItem = {{ item = 5,num = 2},{item=6,num =4}}
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusItem_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	strcpy(pDest, tokens_cp[j]);

	int32 count = 0;
	int32 digit = 1;
	int32 itemId = 0;
	int32 itemCount = 0;

	while(pCur++)
	{
		if(*pCur == '{')
		{
			digit = 1;
			count++;
		}
		else if(*pCur == '}')
		{
			count--;
			if(count == 0) break;
		}

		if(digit == 1 && isdigit(*pCur))
		{
			itemId = atoi(pCur);

			digit = 2;
		}
		else if(digit == 3 && isdigit(*pCur))
		{
			digit = 4;
			itemCount = atoi(pCur);

			_QUEST_INFO::QuestRewardItem	newRewardItem;

			newRewardItem.ItemData.SetItem(itemId, itemCount);
			newRewardItem.bSelected = FALSE;

			KItem	*pItem = KItemManager::GetSingleton().CreateNewItem(newRewardItem.ItemData.m_ItemBonus.m_uItemID);

			if(!pItem)
			{
				return;
				;//KLThrow("parseBonusItem_CP::非法的物品ID:%d", newRewardItem.ItemData.m_ItemBonus.m_uItemID);
			}

			pItem->SetVirtualtExtraInfo();

			pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
			newRewardItem.pItemImpl = pItem;
			g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
		}
		else if(digit && (*pCur == ','))
		{
			digit = 3;
		}
	}
}

/*
 =======================================================================================================================
    解析副本任务的可选择奖励物品 g_BonusChoiceItem = {{ item = 5,num = 2},{item=6,num =4}}
 =======================================================================================================================
 */
void ScriptQuestInterface::parseBonusChoiceItem_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	strcpy(pDest, tokens_cp[j]);

	int32 count = 0;
	int32 digit = 1;
	int32 itemId = 0;
	int32 itemCount = 0;

	while(pCur++)
	{
		if(*pCur == '{')
		{
			digit = 1;
			count++;
		}
		else if(*pCur == '}')
		{
			count--;
			if(count == 0) break;
		}

		if(digit == 1 && isdigit(*pCur))
		{
			itemId = atoi(pCur);

			digit = 2;
		}
		else if(digit == 3 && isdigit(*pCur))
		{
			digit = 4;
			itemCount = atoi(pCur);

			KItem	*pItem = KItemManager::GetSingleton().CreateNewItem(itemId);

			if(!pItem)
			{
				return;
				;//KLThrow("parseBonusChoiceItem_CP::非法的物品ID:%d", itemId);
			}

			pItem->SetVirtualtExtraInfo();

			_QUEST_INFO::QuestRewardItem	newRewardItem;

			newRewardItem.ItemData.SetItemRadio(itemId, itemCount);
			pItem->SetTypeOwner(IO_QUESTVIRTUALITEM);
			newRewardItem.pItemImpl = pItem;
			newRewardItem.bSelected = FALSE;
			g_misInfoPtr->m_QuestRewardItem.push_back(newRewardItem);
		}
		else if(digit && (*pCur == ','))
		{
			digit = 3;
		}
	}
}

/*
 =======================================================================================================================
    解析指定目标　_g_GroupPoint={ {type=10,id =30,target = "采集说明"} }
 =======================================================================================================================
 */
void ScriptQuestInterface::parseGroupPoint_CP(char *pDest, char *pSrc, int32 j)
{
	char	*pCur = strchr(pSrc, '=');

	if(!pCur) return ;//KLThrow("任务数据表格错误:%s", pSrc);

	strcpy(pDest, tokens_cp[j]);

	int32 count = 0;
	int32 digit = 1;
	int32 nType = -1;
	char szTarget[QUEST_INFO_MAXLEN] = { 0 };
	int32 nId = -1;
	bool bParseInfo = false;
	bool bFill = false;

	while(pCur++)
	{
		if(*pCur == '{')
		{
			digit = 1;
			count++;
		}
		else if(*pCur == '}')
		{
			digit = 1;
			count--;
			if(count == 0) break;
		}

		if(digit == 1 && isdigit(*pCur))
		{
			digit = 2;
			nType = atoi(pCur);
		}
		else if(digit == 3 && bParseInfo)
		{
			/* 解析出字符串 */
			char	*beg = strchr(pCur, '"');

			++beg;

			char	*end = strchr(beg, '"');
			int32 len = end - beg;

			if(len > QUEST_INFO_MAXLEN) len = QUEST_INFO_MAXLEN;
			strncpy(szTarget, beg, len);

			pCur = end;

			_QUEST_INFO::QuestGroupPoint	qgp;

			qgp.szTarget = szTarget;
			qgp.nID = nId;

			g_misInfoPtr->m_vecQuestGroupPoint.push_back(qgp);

			nType = -1;
			nId = -1;
			bParseInfo = false;
			memset(szTarget, 0, sizeof(szTarget));
		}
		else if(digit == 3 && isdigit(*pCur))
		{
			digit = 4;

			if(nType != -1 && nId == -1)
			{
				nId = atoi(pCur);
				bParseInfo = true;
			}
		}
		else if(digit && (*pCur == ','))
		{
			digit = 3;
		}
	}
}
