#include "stdafx.h"
#include "CSSwapItem.h"
#include "item/Item_Base.h"
#include "item/Item_Interface.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "SCSwapItem.h"

CSSwapItem::CSSwapItem():
    NetPacket(CS_SWAP_ITEM)
{

}

CSSwapItem::~CSSwapItem()
{

}

bool CSSwapItem::process()
{
    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);
    if (nullptr == pMap)
        return false;

    Object* pObj = pMap->GetSpecificObjByID(mPlayerId);

    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return false;
    }

    Player* pPlayer = (Player*)pObj;

    Item* pItem1 = sItemInterface.GetBagItem(pPlayer, mSourcePos);
    Item* pItem2 = sItemInterface.GetBagItem(pPlayer, mDestPos);

    if ((pItem1 == nullptr) || (pItem2 == nullptr))
    {
        return false;
    }

    ItemContainer* pBagContainer = sItemInterface.GetBagContainer(pPlayer, mSourcePos);

    if (!pBagContainer->IsCanUse())
    {
        return false;
    }

    int32_t	index_container1 = pBagContainer->BagIndex2ConIndex(mSourcePos);
    int32_t	index_container2 = pBagContainer->BagIndex2ConIndex(mDestPos);
    bool bSucc = false;
    if (!(pItem1->IsFree()) && pItem2->IsFree())
    {
        bSucc = sItemInterface.MoveItemInSameContainer
        (
            nullptr,
            pPlayer,
            pBagContainer,
            index_container1,
            index_container2
        ) >= 0;

        SCSwapItem* packet = new SCSwapItem;
        packet->setResult(SWITCHITEM_SUCCESS);
        packet->setSourcePos(mSourcePos);
        packet->setDestPos(mDestPos);
        NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);

    }
    return true;
}

void CSSwapItem::setPlayerId(int32_t id)
{
    mPlayerId = id;
}

void CSSwapItem::setMapId(int32_t id)
{
    mMapId = id;
}

void CSSwapItem::setObjId(int32_t id)
{
    mObjId = id;
}

void CSSwapItem::setSourcePos(int32_t pos)
{
    mSourcePos = pos;
}

void CSSwapItem::setDestPos(int32_t pos)
{
    mDestPos = pos;
}