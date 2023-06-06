#include "stdafx.h"
#include "KNpc.h"
#include "data/GameDataCharacter.h"
#include "GameTableManager.h"
#include "GameTableData.h"
#include "GameTableDefine.h"
#include "KTable.h"

KNpc::KNpc()
{
	mObjectType = ObjectType_Npc;
}

KNpc::~KNpc()
{

}

int32 KNpc::AnalyseCharModel(void)const
{
	// 经过变身
	if (INVALID_ID != m_pCharacterData->Get_ModelID())
	{
		// 直接从模型定义表中读取模型名
		return m_pCharacterData->Get_ModelID();
	}
	else
	{
		if (m_pCreatureInfo != nullptr)
			return m_pCreatureInfo->nModelID;
	}
	return INVALID_ID;
}

void KNpc::UpdateCharBaseData(void)
{
	KCharatcterBaseData* pCharacterData = GetCharacterData();
	if (pCharacterData != NULL && 
		pCharacterData->Get_RaceID() != INVALID_ID)
	{
		
		// 打开生物定义表 mon_attr_ex.tab
		const CGameTable* pCreatureTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CREATURE_ATT);
		if (NULL == pCreatureTable)
		{
			return;
		}

		m_pCreatureInfo = (const _TABLE_CREATURE_ATT*)(pCreatureTable->GetFieldDataByIndex(pCharacterData->Get_RaceID()));
		if (m_pCreatureInfo)
		{
			m_fRunBaseSpeed = m_pCreatureInfo->nRunSpeed * 0.001f;
			m_fWalkBaseSpeed = m_pCreatureInfo->nWalkSpeed * 0.001f;
		}
	
	}
}