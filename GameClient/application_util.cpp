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
		// ����WEAPON������DEFENCE������ADORN
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

	// ԭ��
	case ICLASS_MATERIAL:
		// ҩƷ
	case ICLASS_COMITEM:
	{
		const _TABLE_ITEM_MEDIC* pMedic = NULL;

		// �����ݱ�
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

	// ������Ʒ
	case ICLASS_TASKITEM:
	{
		const _TABLE_ITEM_TASK* pTask = NULL;

		// �����ݱ�
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

	// ��ʯ
	case ICLASS_GEM:
	{
		const _TABLE_ITEM_GEM* pGem = NULL;

		//�����ݱ�
//			TABLE_DEFINEHANDLE( s_pItem_Gem, TABLE_ITEM_GEM );
		const CGameTable* pItem_GemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_GEM);
		if (NULL == pItem_GemTable)
		{
			return NULL;
		}

		//������¼
		pGem = (const _TABLE_ITEM_GEM*)pItem_GemTable->GetFieldDataByIndex((uint32)idTable);
		if (NULL == pGem)
			return NULL;

		return pGem->szIcon;
	}
	break;

	case ICLASS_EXTRABAG:
	{
		const _TABLE_ITEM_EXTBAG* pExtraBagMap = NULL;


		// �����ݱ�
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

bool getItemInfo(uint32_t id, ItemData& data)
{
	int32 nItemClass = INVALID_ID;
	nItemClass = GetClassBySerial(id);

	switch (nItemClass)
	{
		// ����WEAPON������DEFENCE������ADORN
	case ICLASS_EQUIP:
	{
		const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
		_TABLE_ITEM_EQUIP_VISUAL* info =
			(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(id);

		if (info == nullptr)
		{
			return false;
		}

		data.icon = info->szIcon;
		data.title = info->szName;
		data.desc = info->szDes;
		data.type = info->szType;
		return true;
	}
	break;

	// ԭ��
	case ICLASS_MATERIAL:
		// ҩƷ
	case ICLASS_COMITEM:
	{
		const _TABLE_ITEM_MEDIC* pMedic = NULL;

		// �����ݱ�
//			TABLE_DEFINEHANDLE( s_pItem_Medic, TABLE_ITEM_MEDIC );
		const CGameTable* pItem_MedicTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_MEDIC);
		if (NULL == pItem_MedicTable)
		{
			return NULL;
		}

		pMedic = (const _TABLE_ITEM_MEDIC*)pItem_MedicTable->GetFieldDataByIndex(id);
		if (NULL == pMedic)
			return NULL;

		data.icon = pMedic->szIcon;
		data.title = pMedic->szName;
		data.desc = pMedic->szDesc;
		return true;
	}
	break;

	// ������Ʒ
	case ICLASS_TASKITEM:
	{
		const _TABLE_ITEM_TASK* pTask = NULL;

		// �����ݱ�
//			TABLE_DEFINEHANDLE( s_pItem_Task, TABLE_ITEM_TASK );
		const CGameTable* pItem_TaskTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_TASK);
		if (NULL == pItem_TaskTable)
		{
			return NULL;
		}

		pTask = (const _TABLE_ITEM_TASK*)pItem_TaskTable->GetFieldDataByIndex(id);
		if (NULL == pTask)
			return NULL;

		data.icon = pTask->szIcon;
		data.title = pTask->szName;
		data.desc = pTask->szDesc;
		return true;
	}
	break;

	// ��ʯ
	case ICLASS_GEM:
	{
		const _TABLE_ITEM_GEM* pGem = NULL;

		//�����ݱ�
//			TABLE_DEFINEHANDLE( s_pItem_Gem, TABLE_ITEM_GEM );
		const CGameTable* pItem_GemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_GEM);
		if (NULL == pItem_GemTable)
		{
			return NULL;
		}

		//������¼
		pGem = (const _TABLE_ITEM_GEM*)pItem_GemTable->GetFieldDataByIndex(id);
		if (NULL == pGem)
			return NULL;

		data.icon = pGem->szIcon;
		data.title = pGem->szName;
		data.desc = pGem->szDesc;
		return true;
	}
	break;

	case ICLASS_EXTRABAG:
	{
		const _TABLE_ITEM_EXTBAG* pExtraBagMap = NULL;


		// �����ݱ�
//			TABLE_DEFINEHANDLE( s_pItem_ExtraBage_Map, TABLE_ITEM_EXTBAG );
		const CGameTable* pItem_ExtraBage_MapTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EXTBAG);
		if (NULL == pItem_ExtraBage_MapTable)
		{
			return NULL;
		}

		pExtraBagMap = (const _TABLE_ITEM_EXTBAG*)pItem_ExtraBage_MapTable->GetFieldDataByIndex(id);
		if (NULL == pExtraBagMap)
			return NULL;

		data.icon = pExtraBagMap->szIcon;
		data.title = pExtraBagMap->szName;
		data.desc = pExtraBagMap->szDesc;
		return true;
	}
	break;

	default:

	break;
	};	// switch

	return false;
}

void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id)
{
	if (image == nullptr)
	{
		return;
	}

	const char* icon = getItemIcon(item_id);
	if (icon)
	{
		CEGUIImage& imageinfo = CEGUIResourceManager::getSingleton().getIconImageInfo(icon);
		image->deleteAllItems();
		image->setImageInfo(
			imageinfo._imagename,
			imageinfo._coord,
			imageinfo._size);
		image->setItemSelect(0);
	}
	else
	{
		CEGUIImage& imageinfo = CEGUIResourceManager::getSingleton().getIconImageInfo("");

		image->setImageInfo(
			imageinfo._imagename,
			imageinfo._coord,
			imageinfo._size);
	}
}