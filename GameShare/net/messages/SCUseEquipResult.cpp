#include "stdafx.h"
#include "SCUseEquipResult.h"

SCUseEquipResult::SCUseEquipResult()
    :NetPacket(SC_USEEQUIP_RESULT)
{

}

SCUseEquipResult::~SCUseEquipResult()
{

}

bool SCUseEquipResult::process()
{

    KItem* pItemAtBag = GAME_DATA_ITEM_PTR->UserBag_GetItem(mBagIndex);
    if (!pItemAtBag)
    {
        return false;
    }

    if (pItemAtBag->GetItemClass() != ICLASS_EQUIP)
    {
        return false;
    }

    KItem* pItemAtUser = GAME_DATA_ITEM_PTR->UserEquip_GetItem((PLAYER_EQUIP)mEquipPoint);

    

    OBJECT_MANAGER_PTR->GetMySelf()->GetCharacterData()->Set_Equip
    (
        PLAYER_EQUIP(mEquipPoint),
        pItemAtBag->GetIdTable()
    );

    if (pItemAtUser)
    {
        /*pItemAtUser->SetGUID
        (
            pPacket->GetItemID()->m_World,
            pPacket->GetItemID()->m_Server,
            pPacket->GetItemID()->m_Serial
        );*/
    }

    GAME_DATA_ITEM_PTR->UserBag_SetItem(mBagIndex, (KItem*)pItemAtUser, FALSE);

    /* 刷新数据池 */
    GAME_DATA_ITEM_PTR->UserEquip_SetItem(
        PLAYER_EQUIP(mEquipPoint),
        (KItem*)pItemAtBag,
        FALSE
    );

  
    ACTION_SYS_PTR->UserBag_Update();

    /* 产生事件 */
    COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);


    ACTION_SYS_PTR->UserEquip_Update();
    COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_EQUIP);
    

   

    return true;
}

void SCUseEquipResult::setResult(int32_t result)
{
    mResult = result;
}

void SCUseEquipResult::setEquipPoint(int32_t p)
{
    mEquipPoint = p;
}

void SCUseEquipResult::setBagIndex(int32_t bagIndex)
{
    mBagIndex = bagIndex;
}