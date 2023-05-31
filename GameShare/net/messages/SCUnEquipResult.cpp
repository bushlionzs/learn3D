#include "stdafx.h"
#include "SCUnEquipResult.h"

SCUnEquipResult::SCUnEquipResult()
    :NetPacket(SC_UNEQUIP_RESULT)
{

}

SCUnEquipResult::~SCUnEquipResult()
{

}

bool SCUnEquipResult::process()
{
    //if (mEquipPoint < 0 || mEquipPoint >= HEQUIP_NUMBER)
    //{
    //    return false;
    //}
    //PLAYER_EQUIP	equipPoint = (PLAYER_EQUIP)mEquipPoint;

    //KItem* pItem = GAME_DATA_ITEM_PTR->UserEquip_GetItem(equipPoint);
    //if (!pItem)
    //{
    //    return false;
    //}

    //GAME_DATA_ITEM_PTR->UserBag_SetItem(mBagIndex, pItem, TRUE);

    //GAME_DATA_ITEM_PTR->UserEquip_SetItem(equipPoint, NULL, FALSE);

    ///* 逻辑层 */
    //KCharacter_Me* pMySelf = OBJECT_MANAGER_PTR->GetMySelf();

    ///*
    // * pMySelf->UnEquipItem( (PLAYER_EQUIP)pPacket->getEquipPoint() );
    // * 刷新角色属性
    // */
    //OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Set_Equip(
    //    equipPoint,
    //    -1
    //);

    //ACTION_SYS_PTR->UserEquip_Update();
    //ACTION_SYS_PTR->UserBag_Update();

    ///* 通知界面事件 */
    //COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_EQUIP);
    //COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);

    //GAME_DATA_ITEM_PTR->UpdateEquipDurTip();

    return true;
}

void SCUnEquipResult::setResult(int32_t result)
{
    mResult = result;
}

void SCUnEquipResult::setPlayerId(int32_t id)
{
    mPlayerId = id;
}


void SCUnEquipResult::setMapId(int32_t id)
{
    mMapId = id;
}

void SCUnEquipResult::setEquipPoint(int32_t p)
{
    mEquipPoint = p;
}

void SCUnEquipResult::setBagIndex(int32_t bagIndex)
{
    mBagIndex = bagIndex;
}