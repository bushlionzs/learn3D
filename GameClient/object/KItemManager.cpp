#include "OgreHeader.h"
#include "KItemManager.h"
#include "Struct.h"
#include "GameTableData.h"
#include "GameTableDefine.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "KItemEquip.h"
#include "KItemMedicine.h"
#include "KItemGem.h"
#include "KItemBag.h"
#include "KItemTask.h"

template<>
KItemManager* GameSingleton<KItemManager>::m_sSingleton = nullptr;

KItemManager::KItemManager()
{

}

KItemManager::~KItemManager()
{

}

KItem* KItemManager::CreateNewItem(uint32 idTable)
{
	KItem* pNewItem = NULL;

	int32 nItemClass = INVALID_ID;
	nItemClass = GetClassBySerial(idTable);

	switch (nItemClass)
	{
		// 武器WEAPON、防具DEFENCE、饰物ADORN
	case ICLASS_EQUIP:
	{
		const _TABLE_ITEM_EQUIP* pGEquip = nullptr;

			// 打开数据表 equip_algo.tab 装备的属性
//			TABLE_DEFINEHANDLE( s_pItem_Equip, TABLE_ITEM_EQUIP );
        const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP);
		if (nullptr == pItem_EquipTable)
		{
			return nullptr;
		}

		pGEquip = (const _TABLE_ITEM_EQUIP*)pItem_EquipTable->GetFieldDataByIndex(idTable);
		if (nullptr == pGEquip)
			return nullptr;

		int32 nItemEquipId = AllotID();
		pNewItem = new KItemEquip(nItemEquipId);
		if (nullptr == pNewItem)
			return nullptr;

		((KItemEquip*)pNewItem)->AsEquip(pGEquip);

		// 物品规则
		pNewItem->setRule(pGEquip->nRule);

	}
	break;

	// 原料
	case ICLASS_MATERIAL:
		// 药品
	case ICLASS_COMITEM:
	{
		const _TABLE_ITEM_MEDIC* pMedic = NULL;

			// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Medic, TABLE_ITEM_MEDIC );
        const CGameTable* pItem_MedicTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_MEDIC);
		if (NULL == pItem_MedicTable)
		{
			return NULL;
		}

		pMedic = (const _TABLE_ITEM_MEDIC*)pItem_MedicTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pMedic)
			return NULL;

		pNewItem = new KItemMedicine(AllotID());
		//((KItemMedicine*)pNewItem)->AsMedicine(pMedic);

		//物品规则
		pNewItem->setRule(pMedic->nRule);
	}
	break;

	// 任务物品
	case ICLASS_TASKITEM:
	{
		const _TABLE_ITEM_TASK* pTask = NULL;

			// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Task, TABLE_ITEM_TASK );
        const CGameTable* pItem_TaskTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_TASK);
		if (NULL == pItem_TaskTable)
		{
			return NULL;
		}

		pTask = (const _TABLE_ITEM_TASK*)pItem_TaskTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pTask)
			return NULL;

		pNewItem = new KItemTask(AllotID());
		//((KItemTask*)pNewItem)->AsTask(pTask);

		// 物品规则
		pNewItem->setRule(pTask->nRule);
	}
	break;

	// 宝石
	case ICLASS_GEM:
	{
		const _TABLE_ITEM_GEM* pGem = NULL;

			//打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_Gem, TABLE_ITEM_GEM );
        const CGameTable* pItem_GemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_GEM);
		if (NULL == pItem_GemTable)
		{
			return NULL;
		}

		//搜索纪录
		pGem = (const _TABLE_ITEM_GEM*)pItem_GemTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pGem)
			return NULL;

		pNewItem = new KItemGem(AllotID());
		//((KItemGem*)pNewItem)->AsGem(pGem);

		// 物品规则
		pNewItem->setRule(pGem->nRule);
	}
	break;

	case ICLASS_EXTRABAG:
	{
		const _TABLE_ITEM_EXTBAG* pExtraBagMap = NULL;


			// 打开数据表
//			TABLE_DEFINEHANDLE( s_pItem_ExtraBage_Map, TABLE_ITEM_EXTBAG );
        const CGameTable* pItem_ExtraBage_MapTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EXTBAG);
		if (NULL == pItem_ExtraBage_MapTable)
		{
			return NULL;
		}

		pExtraBagMap = (const _TABLE_ITEM_EXTBAG*)pItem_ExtraBage_MapTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pExtraBagMap)
			return NULL;

		pNewItem = new KItemBag(AllotID());
		//((KItemBag*)pNewItem)->AsExtBag(pExtraBagMap);
		// 物品规则
		pNewItem->setRule(pExtraBagMap->nRule);
	}
	break;

	default:
	{
		return nullptr;
	}
	break;
	};	// switch

	if (nullptr == pNewItem)
		return nullptr;

	pNewItem->setIdTable(idTable);
	mObjectMap[pNewItem->getId()] = pNewItem;

	return pNewItem;
}

void KItemManager::DestroyItem(KItem* pItem)
{
	if (pItem)
	{
		auto it = mObjectMap.find(pItem->getId());
		if (it != mObjectMap.end())
		{
			mObjectMap.erase(it);
		}
		delete pItem;
	}
}

uint64_t KItemManager::AllotID(void)
{
	static uint64_t s_ID = 1;
	return s_ID++;
}