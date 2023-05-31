#include "stdafx.h"
#include "SCNotifyEquip.h"

SCNotifyEquip::SCNotifyEquip():
	NetPacket(SC_NOTIFY_EQUIP)
{

}

SCNotifyEquip::~SCNotifyEquip()
{

}

bool SCNotifyEquip::process()
{
	//SItem* pItem = &mItem;

	//KItem* pOldItem = GAME_DATA_ITEM_PTR->UserBag_GetItem(mBagIndex);

	//int32		iCount = pItem->GetItemCount();
	//if (pOldItem)
	//{
	//	iCount -= pOldItem->GetNumber();
	//}

	//KItem* pItemObj = ITEM_MANAGER_PTR->CreateNewItem(pItem->m_ItemIndex);
	//if (!pItemObj) return MP_CONTINUE;

	//pItemObj->SetGUID(pItem->m_ItemGUID.m_World, pItem->m_ItemGUID.m_Server, pItem->m_ItemGUID.m_Serial);

	///*
	// * pItemObj->SetNumber(pItem->GetItemCount());
	// */
	//pItemObj->SetExtraInfo(pItem);


	///* ·Åµ½±³°ü */
	//GAME_DATA_ITEM_PTR->UserBag_SetItem(mBagIndex, pItemObj);
	//ACTION_SYS_PTR->UserBag_Update();

	///* UI */
	//COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	//GAME_DATA_ITEM_PTR->OutPutMsg_GetItem(pItemObj, iCount);
    return true;
}

SItem* SCNotifyEquip::getItem()
{
    return &mItem;
}

void SCNotifyEquip::setBagIndex(int32_t index)
{
    mBagIndex = index;
}