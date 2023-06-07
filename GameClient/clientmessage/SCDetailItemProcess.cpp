#include "stdafx.h"
#include "SCDetailItemList.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "KItem.h"
#include "KItemManager.h"
#include "data/GameDataCharacter.h"
#include "data/GameDataManager.h"

bool SCDetailItemList::process()
{
	KObject* pObj = KObjectManager::GetSingleton().getObject(mObjectId);

	
	KPlayer* pPlayer = dynamic_cast<KPlayer*>(pObj);


	GameDataManager::GetSingleton().UserBag_Clear();


	for (auto it = mItemMap.begin(); it != mItemMap.end(); it++)
	{
		SItem& item = it->second;
		KItem* pItemObj = KItemManager::GetSingleton().CreateNewItem(item.m_ItemIndex);
		pItemObj->SetGUID(
			item.m_ItemGUID.m_World,
			item.m_ItemGUID.m_Server,
			item.m_ItemGUID.m_Serial
		);

		pItemObj->SetExtraInfo(&item);
		pItemObj->SetPosIndex(it->first);

		GameDataManager::GetSingleton().UserBag_SetItem(it->first, pItemObj);
	}


	return true;
}