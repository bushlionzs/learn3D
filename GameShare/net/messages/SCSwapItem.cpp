#include "stdafx.h"
#include "SCSwapItem.h"

SCSwapItem::SCSwapItem()
    :NetPacket(SC_SWAP_ITEM)
{

}

SCSwapItem::~SCSwapItem()
{

}

bool SCSwapItem::process()
{
    //KItem* pItem1 = GAME_DATA_ITEM_PTR->UserBag_GetItem(mSourcePos);
    //KItem* pItem2 = GAME_DATA_ITEM_PTR->UserBag_GetItem(mDestPos);

    //if (!pItem1 && !pItem2)
    //    return false;

    //if (pItem1 && !pItem2)
    //{
    //    GAME_DATA_ITEM_PTR->UserBag_SetItem(mDestPos, pItem1, FALSE);
    //    GAME_DATA_ITEM_PTR->UserBag_SetItem(mSourcePos, NULL, FALSE);
    //}
    //else if (!pItem1 && pItem2)
    //{

    //}

    //ACTION_SYS_PTR->UserBag_Update(mSourcePos);
    //ACTION_SYS_PTR->UserBag_Update(mDestPos);

    ///* 通知界面事件 */
    //COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);

    return true;
}

void SCSwapItem::setResult(int32_t result)
{
    mResult = result;
}

void SCSwapItem::setSourcePos(int32_t pos)
{
    mSourcePos = pos;
}

void SCSwapItem::setDestPos(int32_t pos)
{
    mDestPos = pos;
}