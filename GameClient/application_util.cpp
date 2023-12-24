#include "OgreHeader.h"
#include "application_util.h"
#include "CEGUIResourceManager.h"
#include "DefineItem.h"
#include "GameTableData.h"
#include "GameTableDefine.h"
#include "GameTableManager.h"
#include "KTable.h"

void setImageInfo(
	MyGUI::ImageBox* image,
	const String& imagesetname,
	const String& imagename)
{
	CEGUIImage& imageinfo =
		CEGUIResourceManager::getSingleton().getImageInfo(imagesetname, imagename);

	image->setImageInfo(
		imageinfo._imagename,
		imageinfo._coord,
		imageinfo._size);
}



const char* getItemIcon(uint32 idTable)
{

	int32 nItemClass = INVALID_ID;
	nItemClass = GetClassBySerial(idTable);

	switch (nItemClass)
	{
		// 武器WEAPON、防具DEFENCE、饰物ADORN
	case ICLASS_EQUIP:
	{
		const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
		_TABLE_ITEM_EQUIP_VISUAL* info =
			(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(idTable);

		if (info == nullptr)
		{
			return nullptr;
		}

		return info->szIcon;

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

		return pMedic->szIcon;
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

		return pTask->szIcon;
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

		return pGem->szIcon;
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

		return pExtraBagMap->szIcon;
	}
	break;

	default:
	{
		return nullptr;
	}
	break;
	};	// switch

	return nullptr;
}


void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id)
{

	const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
	_TABLE_ITEM_EQUIP_VISUAL* info = 
		(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(item_id);


	const char* icon = getItemIcon(item_id);
	CEGUIImage& imageinfo = CEGUIResourceManager::getSingleton().getIconImageInfo(icon);

	image->setImageInfo(
		imageinfo._imagename,
		imageinfo._coord,
		imageinfo._size);
}