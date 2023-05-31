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

uchar GetClassBySerial(uint32 Serial)
{
	return(uchar)(Serial / 1000000);
}

void setImageInfoFromIcon(MyGUI::ImageBox* image, uint32_t item_id)
{

	const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
	_TABLE_ITEM_EQUIP_VISUAL* info = 
		(_TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipTable->GetFieldDataByIndex(item_id);

	CEGUIImage& imageinfo = CEGUIResourceManager::getSingleton().getIconImageInfo(info->szIcon);

	image->setImageInfo(
		imageinfo._imagename,
		imageinfo._coord,
		imageinfo._size);
}