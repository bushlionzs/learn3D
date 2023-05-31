#include "stdafx.h"
#include "CSUnEquip.h"
#include "item/Item_Base.h"
#include "item/Item_Interface.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "SCUnEquipResult.h"

CSUnEquip::CSUnEquip()
    :NetPacket(CS_UNEQUIP)
{

}

CSUnEquip::~CSUnEquip()
{

}

bool CSUnEquip::process()
{
    if (mEquipPoint < 0 || mEquipPoint >= HEQUIP_NUMBER)
    {
        return false;
    }
    PLAYER_EQUIP	equipPoint = (PLAYER_EQUIP)mEquipPoint;

    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);
    if (nullptr == pMap)
        return false;

    Object* pObj = pMap->GetSpecificObjByID(mPlayerId);

    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return false;
    }

    Player* pPlayer = (Player*)pObj;

    Item* pEquipItem = sItemInterface.GetEquip(pPlayer, equipPoint);

    if (pEquipItem == nullptr)
    {
        return false;
    }

    if (pEquipItem->IsFree())
    {
        return false;
    }

    if (pEquipItem->IsLock())
    {
        return false;
    }

    ItemContainer* pEquipContainer = pPlayer->GetEquipContain();

    if (nullptr == pEquipContainer)
    {
        return false;
    }

    if (mBagIndex >= 0)
    {
        ItemContainer* pBagContainer = sItemInterface.GetBagContainer(pPlayer, mBagIndex);

        if (nullptr == pBagContainer)
        {
            return false;
        }

        Item* pItem = pBagContainer->GetItem(pBagContainer->BagIndex2ConIndex(mBagIndex));

        if (!pItem->IsFree())
        {
            return false;
        }

        int32_t bagIndex = sItemInterface.MoveItemBt2Containers
        (
            nullptr,
            pPlayer,
            pEquipContainer,
            equipPoint,
            pBagContainer,
            pBagContainer->BagIndex2ConIndex(mBagIndex)
        );
    }
    else
    {
        mBagIndex = sItemInterface.MoveItemToBag(nullptr, pPlayer, pEquipContainer, equipPoint);

        if (mBagIndex < 0)
        {
            return false;
        }
    }
   

    SCUnEquipResult* packet = new SCUnEquipResult;

    packet->setBagIndex(mBagIndex);
    packet->setEquipPoint(mEquipPoint);
    packet->setResult(UNEQUIP_SUCCESS);

    NetManager::GetSingletonPtr()->sendNetMessage(packet);

    return true;
}


void CSUnEquip::setPlayerId(int32_t id)
{
    mPlayerId = id;
}


void CSUnEquip::setMapId(int32_t id)
{
    mMapId = id;
}

void CSUnEquip::setEquipPoint(int32_t p)
{
    mEquipPoint = p;
}

void CSUnEquip::setBagIndex(int32_t bagIndex)
{
    mBagIndex = bagIndex;
}