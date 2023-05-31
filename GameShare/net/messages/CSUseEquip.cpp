#include "stdafx.h"
#include "CSUseEquip.h"
#include "item/Item_Base.h"
#include "item/Item_Interface.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "SCUseEquipResult.h"


CSUseEquip::CSUseEquip()
    :NetPacket(CS_USE_EQUIP)
{

}

CSUseEquip::~CSUseEquip()
{

}

bool CSUseEquip::process()
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
    ItemContainer* pBagContainer = sItemInterface.GetBagContainer(pPlayer, mBagIndex);

    if (nullptr == pBagContainer)
    {
        return false;
    }


    Item* pUseItem = pBagContainer->GetItem(pBagContainer->BagIndex2ConIndex(mBagIndex));

    PLAYER_EQUIP clientEquipPoint;

    int32_t itemclass = pUseItem->GetItemClass();
    if (itemclass == ICLASS_EQUIP)
    {
        if (pUseItem->IsLock())
        {
            return false;
        }

        if (pUseItem->IsOverTime())
        {
            return false;
        }

        if (pUseItem->GetRequireLevel() > pPlayer->GetLevel())
        {
            return false;
        }

        if (pUseItem->GetReqJob() != PROFESSION_NONE)
        {
            if (pUseItem->GetReqJob() != pPlayer->GetProfession())
            {
                return false;
            }
        }
        

        PLAYER_EQUIP	equipPoint = (PLAYER_EQUIP)pUseItem->GetEquipPoint();
        ItemContainer* pEquipContainer = pPlayer->GetEquipContain();
        
        if (mEquipPoint == -1)
        {
            clientEquipPoint = equipPoint;
        }
        else
        {
            clientEquipPoint = (PLAYER_EQUIP)mEquipPoint;
        }
        

        if (equipPoint != clientEquipPoint)
        {
            if (equipPoint == HEQUIP_RING1)
            {
                if (clientEquipPoint != HEQUIP_RING2)
                {
                    return false;
                }
            }

            if (equipPoint == HEQUIP_ADORN1)
            {
                if (clientEquipPoint != HEQUIP_ADORN2)
                {
                    return false;
                }
            }
        }

        Item* pEquipItem = pEquipContainer->GetItem((uint32)clientEquipPoint);

        if (nullptr == pEquipItem)
        {
            return false;
        }
        
        if (pEquipItem->IsFree())
        {
            sItemInterface.MoveItemBt2Containers
            (
                nullptr,
                pPlayer,
                pBagContainer,
                pBagContainer->BagIndex2ConIndex(mBagIndex),
                pEquipContainer,
                (uint32)equipPoint
            );
        }
        else
        {
            sItemInterface.ExchangeItem
            (
                pBagContainer,
                pBagContainer->BagIndex2ConIndex(mBagIndex),
                pEquipContainer,
                (uint32)equipPoint
            );
        }
       
    }

    SCUseEquipResult* packet = new SCUseEquipResult;
    packet->setResult(USEEQUIP_SUCCESS);
    packet->setBagIndex(mBagIndex);
    packet->setEquipPoint(clientEquipPoint);

    NetManager::GetSingletonPtr()->sendNetMessage(packet);

    return true;
}

void CSUseEquip::setEquipPoint(int32_t p)
{
    mEquipPoint = p;
}

void CSUseEquip::setBagIndex(int32_t bagIndex)
{
    mBagIndex = bagIndex;
}

void CSUseEquip::setPlayerId(int32_t id)
{
    mPlayerId = id;
}

void CSUseEquip::setMapId(int32_t id)
{
    mMapId = id;
}