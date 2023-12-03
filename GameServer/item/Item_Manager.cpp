/*$T MapServer/Server/Item/ItemManager.cpp GC 1.140 10/10/07 10:07:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_Manager.h"
#include "Item_Ruler.h"
#include "Item_Helper.h"
#include "TypeDefine.h"
#include "BaseTool.h"
#include "TabDefine_Map_Item.h"
#include "FileDef.h"
#include "server_settting.h"

ItemManager	*g_pItemMgr = NULL;


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateGemFromTable_i(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(pInit->m_nItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	CreateItemRuler::CreateGemProperty(help.GetItemTypeStruct(), item);

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateMedicFromTable_i(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(pInit->m_nItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	CreateItemRuler::CreateMedicProperty(help.GetItemTypeStruct(), item);
	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateQuestFromTable_i(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(pInit->m_nItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	CreateItemRuler::CreateTaskItemProperty(help.GetItemTypeStruct(), item);
	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateExtraBagFromTable_i(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(pInit->m_nItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	CreateItemRuler::CreateExtraBagProperty(help.GetItemTypeStruct(), item);
	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateItem(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pInit->m_nItemIndex != 0);

	switch(GetClassBySerial(pInit->m_nItemIndex))
	{
	case ICLASS_EQUIP:	return CreateEquipFromTable_i(item, pInit); break;
	case ICLASS_MATERIAL:	return CreateMedicFromTable_i(item, pInit); break;
	case ICLASS_COMITEM:	return CreateMedicFromTable_i(item, pInit); break;
	case ICLASS_TASKITEM:	return CreateQuestFromTable_i(item, pInit); break;
	case ICLASS_GEM:	return CreateGemFromTable_i(item, pInit); break;
	case ICLASS_EXTRABAG:	return CreateExtraBagFromTable_i(item, pInit); break;
	default:		KCheck(FALSE); return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateItem(uint32 ItemSerial, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(ItemSerial);
	BOOL			bRet = CreateItem(help.GetItemTypeStruct(), item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemManager::CreateItem(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(it.isNull() == FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(it.m_Class)
	{
	case ICLASS_EQUIP:	return CreateEquipFromTable_i(it, item); break;
	case ICLASS_MATERIAL:	return CreateMedicFromTable_i(it, item); break;
	case ICLASS_COMITEM:	return CreateMedicFromTable_i(it, item); break;
	case ICLASS_TASKITEM:	return CreateQuestFromTable_i(it, item); break;
	case ICLASS_GEM:	return CreateGemFromTable_i(it, item); break;
	case ICLASS_EXTRABAG:	return CreateExtraBagFromTable_i(it, item); break;
	default:		KCheck(FALSE); return FALSE;
	}

	KCheck(item.IsNullType() == FALSE);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL ItemManager::Init()
{
	
	Configer	SerialFile(FILE_ITEM_SERIAL);

	m_nLastGenItemSerial = SerialFile.Get_Property_Int("ItemConfig", "ItemSerial");
	m_pSerialMK = NULL;

	

	m_WorldId = g_Config.m_WorldInfo.m_WorldID;


	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemManager::GenItemSN()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iSerialId = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	do
	{
		std::lock_guard<FastLock> autolock(m_Lock);

		iSerialId = ++m_nLastGenItemSerial;
	} while(0);

	if(m_pSerialMK)
	{
		m_pSerialMK->SetSerial(SM_S_WRITE, iSerialId);
	}

	return iSerialId;
	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::GenItemGuid(SItemGuid &ig)
{
	__GUARD__ ig.m_Server = (uchar) m_ServerId;
	ig.m_World = (uchar) m_WorldId;
	ig.m_Serial = GenItemSN();

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateEquipFromTable_i(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateEquipProperty(it, -1, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(g_pItemMgr->GenItemGuid(item.m_ItemGUID))
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateGemFromTable_i(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateGemProperty(it, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateGemFromTable_i(uint32 TableIndex, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateGemProperty(TableIndex, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateMedicFromTable_i(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateMedicProperty(it, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateQuestFromTable_i(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateTaskItemProperty(it, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateExtraBagFromTable_i(SItemType it, SItem &item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CreateItemRuler::	CreateExtraBagProperty(it, item);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return g_pItemMgr->GenItemGuid(item.m_ItemGUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemManager::CreateEquipFromTable_i(SItem &item, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ STSerialHelper help(pInit->m_nItemIndex);
	int32			qulity = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(pInit->m_nEquipFromType)
	{
	case ITEM_DROP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_PLAYER_EQUIPDROP_INIT	*pDropInit = (_PLAYER_EQUIPDROP_INIT *) pInit;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			item.GetEquipData()->m_EquipType = ITEM_DROP;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	Ret = CreateItemRuler::CreateEquipProperty
				(
					help.GetItemTypeStruct(),
					-1,
					item,
					pDropInit->m_nMonsterLevel,
					pDropInit->m_nMonsterType
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(Ret);
		}
		break;

	case ITEM_CREATE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_PLAYER_EQUIPCREATE_INIT	*pCreateInit = (_PLAYER_EQUIPCREATE_INIT *) pInit;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			item.GetEquipData()->m_EquipType = ITEM_CREATE;
			item.GetEquipData()->m_EquipScore = pCreateInit->m_nEquipScore;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	Ret = CreateItemRuler::CreateEquipProperty
				(
					help.GetItemTypeStruct(),
					pCreateInit->m_nPlayerJob,
					item,
					qulity
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(Ret);
		}
		break;

	default:
		item.GetEquipData()->m_EquipType = pInit->m_nEquipFromType;
		break;
	}

	if(g_pItemMgr->GenItemGuid(item.m_ItemGUID))
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}
