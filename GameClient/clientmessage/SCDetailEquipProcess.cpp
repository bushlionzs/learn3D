#include "OgreHeader.h"
#include "SCDetailEquipList.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "KItem.h"
#include "KItemManager.h"
#include "data/GameDataCharacter.h"

bool SCDetailEquipList::process()
{
	KObject* pObj = KObjectManager::GetSingleton().getObject(mObjectId);

	if (nullptr == pObj)
	{
		return false;
	}

	KPlayer* pPlayer = dynamic_cast<KPlayer*>(pObj);

	if (nullptr == pPlayer)
	{
		return false;
	}
	KCharatcterBaseData* pCharacterData = pPlayer->GetCharacterData();

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

		pCharacterData->Set_Equip((PLAYER_EQUIP)it->first, pItemObj->GetIdTable());

		//GAME_DATA_ITEM_PTR->UserEquip_SetItem((PLAYER_EQUIP)it->first, pItemObj, TRUE);
	}

	//ACTION_SYS_PTR->UserEquip_Update();
	pPlayer->UpdateBodyPartModel();

	return true;
}