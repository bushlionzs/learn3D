#include "stdafx.h"
#include "CSPickItem.h"
#include "server/map/game_map.h"
#include "server/gameobject/Player.h"
#include "server/item/ItemInstance.h"
#include "server/map/map_manager.h"
#include "server/gameobject/ObjectManager.h"
#include "server/item/Item_Interface.h"
#include "SCPickItemResult.h"
#include "SCItemInfo.h"

CSPickItem::CSPickItem()
    :NetPacket(CS_PICK_ITEM)
{

}

CSPickItem::~CSPickItem()
{

}

bool CSPickItem::process()
{
    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);
    if (nullptr == pMap)
        return false;
    ObjectManager* objectManager = pMap->GetObjManager();
    Object* pObj = objectManager->GetObj(mPlayerId);
    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return false;
    }

    Player* pPlayer = (Player*)pObj;

    if (pPlayer->GetMap() != pMap)
    {
        return false;
    }

    Object* pItem = objectManager->GetObj(mObjId);

    if (pItem->GetMap() != pMap)
    {
        return false;
    }

    if (pItem->GetObjType() != Object::OBJECT_CLASS_DROP_ITEM)
    {
        return false;
    }
    ItemInstance* pObj_Item = (ItemInstance*)pItem;
    SItem* itemInfo = pObj_Item->GetObj_Item();

    if (pPlayer->IsInValidRadius(pItem->GetGLPos(), MAX_DROP_ITEM_OP_DISTANCE * 2) == FALSE)
    {
        return false;
    }

    if (!pPlayer->IsAlive())
    {
        return false;
    }

    int32_t	outLen = 0;
    char	pOut[MAX_ITEM_STRING_ASCII_BUFFER] = { '\0' };
    char	pInfo[MAX_CHAT_SIZE] = { '\0' };
    char	pInfoSelf[MAX_CHAT_SIZE] = { '\0' };

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    Item2String(itemInfo, pOut, outLen, MAX_ITEM_STRING_ASCII_BUFFER);


    char	strBegin[10] = "$B";
    char	strEnd[10] = "$E";
    /*~~~~~~~~~~~~~~~~~~~~~~~~*/

    tsnprintf_s(pInfo, MAX_CHAT_SIZE, "%s拾取了$B%s$E", pPlayer->GetName(), pOut);
    tsnprintf_s(pInfoSelf, MAX_CHAT_SIZE, "#W你拾取了$B%s$E", pOut);

    ePICK_RESULT_CODE		resultCode = PICK_INVALID_ITEM;

    SCPickItemResult* Msg = new SCPickItemResult;

    if (pObj_Item->GetType() == ITYPE_MONSTERDROP_OBJ_ITEM)
    {
        GUID_t pickerId = pPlayer->GetGUID();
        int32_t humanId = pPlayer->GetID();
        resultCode = pObj_Item->CanPick(pickerId, humanId, itemInfo);

        uint32_t	uBagIndex = INVALID_ID;

        if (PICK_SUCCESS == resultCode)
        {
            if (sItemInterface.RecieveItemToInventory(nullptr, pPlayer, itemInfo))
            {
                resultCode = PICK_SUCCESS;
                Msg->setObjId(mObjId);
            }
            else
                resultCode = PICK_BAG_FULL;
        }

        Msg->setResult(resultCode);

        if (resultCode == PICK_SUCCESS)
        {
            pObj_Item->Recycle();
        }
    }
    return true;
}

void CSPickItem::setObjId(int32_t id)
{
    mObjId = id;
}

void CSPickItem::setMapId(int32_t id)
{
    mMapId = id;
}

void CSPickItem::setPlayerId(int32_t id)
{
    mPlayerId = id;
}