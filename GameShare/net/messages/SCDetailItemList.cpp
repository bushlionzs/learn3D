#include "stdafx.h"
#include "SCDetailItemList.h"


SCDetailItemList::SCDetailItemList() :
	NetPacket(SC_DELETE_OBJECT)
{

}

SCDetailItemList::~SCDetailItemList()
{

}

bool SCDetailItemList::process()
{
	/*KObject* pObj = (KObject*)OBJECT_MANAGER_PTR->FindServerObject(mObjectId);

	if (nullptr == pObj || FALSE == pObj->CheckClassType(GET_CLASS(KCharacter)))
	{
		return false;
	}

	GAME_DATA_ITEM_PTR->UserBag_Clear();


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
		pItemObj->SetPosIndex(it->first);

		GAME_DATA_ITEM_PTR->UserBag_SetItem(it->first, pItemObj);
	}
	
	if (!mItemMap.empty())
	{
		ACTION_SYS_PTR->UserBag_Update();
		COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	}*/

	return true;
}

void SCDetailItemList::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCDetailItemList::addItem(int32_t part, SItem& item)
{
	mItemMap[part] = item;
}


