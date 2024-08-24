#include "stdafx.h"
#include "GameDataManager.h"
#include "KItemManager.h"
#include "KItem.h"
#include "GameClientUtil.h"
#include "KTable.h"
#include "GameTableManager.h"
template<>
GameDataManager* GameSingleton<GameDataManager>::m_sSingleton = nullptr;

GameDataManager::GameDataManager()
{
	m_vUserEquip.resize(20);
	m_vUserBag.resize(200);
}

GameDataManager::~GameDataManager()
{

}

bool GameDataManager::Initialize()
{
	LoadQuestFile();
	return true;
}

void GameDataManager::UserEquip_SetItem(
	PLAYER_EQUIP ptEquip, 
	KItem* pEquipItem, 
	bool bClearOld)
{
	/*
	 * 为装备玩法操作所加 <例如打星updata时> ;
	 * if( m_vUserEquip[ptEquip] ) ;
	 * { ;
	 * if( m_vUserEquip[ptEquip]->IsLocked() ) ;
	 * { ;
	 * if( pEquipItem ) ;
	 * { ;
	 * pEquipItem->SetLock(TRUE);
	 * ;
	 * } ;
	 * } ;
	 * }
	 */
	if (m_vUserEquip[ptEquip] && bClearOld)
	{
		/* modify by huangjin 不删除本地的数据记录 */
		KItemManager::GetSingleton().DestroyItem((KItem*)m_vUserEquip[ptEquip]);
		m_vUserEquip[ptEquip] = NULL;
	}

	if (pEquipItem)
	{
		/* 设置装备在action item 中的位置. */
		pEquipItem->SetPosIndex(ptEquip);
	}

	m_vUserEquip[ptEquip] = pEquipItem;
}

void GameDataManager::UserBag_Clear()
{
	for (int32 i = 0; i < MAX_BAG_SIZE; i++)
	{
		if (m_vUserBag[i])
		{
			KItemManager::GetSingleton().DestroyItem((KItem*)m_vUserBag[i]);
			m_vUserBag[i] = nullptr;

		}
	}
}

void GameDataManager::UserBag_SetItem(
	int32 nBagIndex, 
	KItem* pItem, 
	bool bClearOld, 
	bool reCalulate)
{
	if (nBagIndex < 0 || nBagIndex >= MAX_BAG_SIZE) return;

	/* 销毁原有数据 */
	if (m_vUserBag[nBagIndex] && bClearOld)
	{
		KItem* pItemLog = (KItem*)m_vUserBag[nBagIndex];

		if (pItem && reCalulate)
		{
			int32 iNum = pItem->GetNumber();

			if (pItemLog)
			{
				iNum += pItemLog->GetNumber();
			}

			pItem->SetNumber(iNum);
		}

		

		KItemManager::GetSingleton().DestroyItem((KItem*)m_vUserBag[nBagIndex]);
		m_vUserBag[nBagIndex] = nullptr;

	}

	if (pItem)
	{
		pItem->SetPosIndex(nBagIndex);
	}

	m_vUserBag[nBagIndex] = pItem;
}

KItem* GameDataManager::UserBag_GetItem(int32_t nBagIndex)
{
	return m_vUserBag[nBagIndex];
}

void GameDataManager::SetMyDefaultSkillID(int32_t skillId)
{

}

uint64_t GameDataManager::GetSpecialCoolDown()
{
	return 0;
}


int32_t GameDataManager::GetCommonCoolDown()
{
	return 0;
}

int32 GameDataManager::GetCoolDownGroupTime(int32 nCoolDownID)
{
	if (0 <= nCoolDownID && nCoolDownID < (int32)m_CoolDownGroup.size())
	{
		UINT64 uNowTime = GameClientUtil::GetTimeNow();
		int32 nDeltaTime = uNowTime - m_CoolDownGroup[nCoolDownID].nCreateTime;
		int32 nTime = m_CoolDownGroup[nCoolDownID].nTotalTime - m_CoolDownGroup[nCoolDownID].nTimeElapsed - nDeltaTime;

		if (nTime < 0) nTime = 0;

		return nTime;
	}

	return 0;
}

eRELATION GameDataManager::GetCampType(
	KObject* pObj_A, KObject* pObj_B)
{
	if (pObj_A == NULL || pObj_B == NULL)
	{
		return RELATION_ENEMY;
	}

	if (pObj_A == pObj_B)
	{
		return RELATION_FRIEND;
	}

	int64_t idOwner_A, idOwner_B, idA, idB;

	idA = pObj_A->getId();
	idB = pObj_B->getId();
	
	return RELATION_FRIEND;
}

const std::string& GameDataManager::getQuestFileName(int32_t nID)
{
	const static std::string strEmpty = "";
	std::map<int32_t, std::string>::iterator itFind;

	itFind = m_QuestFileMap.find(nID);
	if (itFind == m_QuestFileMap.end())
	{
		return strEmpty;
	}

	return itFind->second;
}

void GameDataManager::LoadQuestFile()
{
	/* 打开物品规则表 */
	TABLE_DEFINEHANDLE(s_pQuestScript, TABLE_QUEST_SCRIPT);	/* Script.tab */
	if (s_pQuestScript)
	{
		int32_t nRecordsNum = (int32_t)(s_pQuestScript->GetRecordsNum());

		for (int32_t i = 0; i < nRecordsNum; ++i)
		{
			const _TABLE_QUEST_SCRIPT* pQuestScript = (const _TABLE_QUEST_SCRIPT*)
				(s_pQuestScript->GetFieldDataByLine(i));

			if (pQuestScript)
			{
				m_QuestFileMap.insert(std::make_pair(pQuestScript->nIndex, pQuestScript->szQuestLua));
			};
		}
	}
}