#include "stdafx.h"
#include "GameDataManager.h"
#include "KItemManager.h"
#include "KItem.h"
#include "GameClientUtil.h"

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

void GameDataManager::UserEquip_SetItem(
	PLAYER_EQUIP ptEquip, 
	KItem* pEquipItem, 
	bool bClearOld)
{
	/*
	 * Ϊװ���淨�������� <�������updataʱ> ;
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
		/* modify by huangjin ��ɾ�����ص����ݼ�¼ */
		KItemManager::GetSingleton().DestroyItem((KItem*)m_vUserEquip[ptEquip]);
		m_vUserEquip[ptEquip] = NULL;
	}

	if (pEquipItem)
	{
		/* ����װ����action item �е�λ��. */
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

	/* ����ԭ������ */
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