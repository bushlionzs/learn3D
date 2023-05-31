#include "stdafx.h"
#include "SCDetailEquipList.h"


SCDetailEquipList::SCDetailEquipList() :
	NetPacket(SC_DELETE_OBJECT)
{

}

SCDetailEquipList::~SCDetailEquipList()
{

}

bool SCDetailEquipList::process()
{
	/*KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectId);

	if (nullptr == pObj || FALSE == pObj->CheckClassType(GET_CLASS(KCharacter)))
	{
		return false;
	}

	KCharatcterBaseData* pCharacterData = ((KCharacter*)pObj)->GetCharacterData();

	for (auto it = mItemMap.begin(); it != mItemMap.end(); it++)
	{
		SItem& item = it->second;
		KItem* pItemObj = ITEM_MANAGER_PTR->CreateNewItem(item.m_ItemIndex);
		pItemObj->SetGUID(
			item.m_ItemGUID.m_World,
			item.m_ItemGUID.m_Server,
			item.m_ItemGUID.m_Serial
		);

		pItemObj->SetExtraInfo(&item);
		pItemObj->SetTypeOwner(IO_MYSELF_EQUIP);
		pItemObj->SetPosIndex(it->first);

		pCharacterData->Set_Equip((PLAYER_EQUIP)it->first, pItemObj->GetIdTable());

		GAME_DATA_ITEM_PTR->UserEquip_SetItem((PLAYER_EQUIP)it->first, pItemObj, TRUE);
	}

	ACTION_SYS_PTR->UserEquip_Update();*/
	

	return true;
}

void SCDetailEquipList::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailEquipList::addItem(int32_t part, SItem& item)
{
	mItemMap[part] = item;
}


