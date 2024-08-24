#include "stdafx.h"
#include "message_process.h"
#include <map_manager.h>
#include <game_map.h>
#include <Item_Container.h>
#include <Item_Interface.h>
#include <Player.h>
#include <Monster.h>
#include <game_map.h>
#include <map_info.h>
#include <Behavior_Player.h>
#include <ObjectManager.h>
#include "db/db_manager.h"
#include "db/db_task.h"
#include "client_message.pb.h"
#include "server_message.pb.h"
#include <net_header.h>
#include <net_message_manager.h>
#include <server_manager.h>
#include <LuaSystem.h>
#include <data_manager.h>
#include <TabDefine_Map_Quest.h>
#include <ScriptDef.h>

void cs_user_login(NetHandle h, const char* msg, uint32_t msg_size)
{
	auto id = std::string("1610000022");
	CharDataTask* task = new CharDataTask(id, h);
	DBManager::GetSingletonPtr()->addDbTask(task);
}

void cs_char_move(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgCharMove dummy;
    bool b = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    assert(b);

    auto mapId = dummy.map_id();
    GameMap* pScene = MapManager::GetSingletonPtr()->getMap(mapId);
    if (NULL == pScene)
    {
        return;
    }

    GLPos targetPos(dummy.target_x(), dummy.target_y());
    if (!pScene->GetMapInfo()->IsCanGo(targetPos))
    {
        return;
    }

    ObjectManager* objectManager = pScene->GetObjManager();
    auto objectId = dummy.object_id();
    Object* pObj = objectManager->GetObj(objectId);
    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;
    GLPos worldPos(dummy.world_x(), dummy.world_y());
    OPT_RESULT oResult = pPlayer->GetHumanAI()->PushCmd_Move
    (
        dummy.handle_id(),
        1,
        &targetPos,
        dummy.stop_logic_count(),
        &worldPos,
        objectId
    );

    if (ORT_FAILED(oResult))
    {
        int kk = 0;
    }

}

void cs_char_use_skill(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_event_request(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgEventRequest dummy;
    bool b = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    assert(b);

    auto mapId = dummy.map_id();
    auto playerId = dummy.player_id();
    auto targetId = dummy.target_id();
    auto scriptId = dummy.mid_script();
    auto exIndex = dummy.ex_index();
    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

    Object* pObj = pMap->GetSpecificObjByID(playerId);
    if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;

    pObj = pMap->GetSpecificObjByID(targetId);

    if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
    {
        return;
    }

    Monster* pMonster = (Monster*)pObj;

    ScriptID_t idScript = scriptId;

    int32_t	bVerifyEvent = 0;
    NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    if (pQuest)
    {
        for (int32 i = 0; i < pQuest->m_EventCount; i++)
        {
            if (pQuest->m_EventList[i] == idScript)
            {
                bVerifyEvent = 1;
                break;
            }
        }

        if (bVerifyEvent == 0)
        {
            for (int32 i = 0; i < pQuest->m_QuestCount; i++)
            {
                if (pQuest->m_QuestList[i] == idScript)
                {
                    bVerifyEvent = 2;
                    break;
                }
            }
        }
    }

    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

    if (bVerifyEvent == 1)
    {
        luaSystem->RunScriptFunction
        (
            mapId,
            idScript,
            DEF_PROC_EVENT_ENTRY_FN,
            mapId,
            playerId,
            targetId,
            idScript,
            exIndex
        );

        return;
    }
    else if (bVerifyEvent == 2 || bVerifyEvent == 0)
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(idScript);
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

        if (pData)
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~*/
            BOOL	bRunByScript = FALSE;
            /*~~~~~~~~~~~~~~~~~~~~~~~~~*/

            if (pData->nScriptID >= 100000)
            {
                luaSystem->RunScriptFunction
                (
                    mapId,
                    pData->nScriptID,
                    DEF_PROC_EVENT_ENTRY_FN,
                    mapId,
                    playerId,
                    targetId,
                    idScript,
                    exIndex
                );
                bRunByScript = TRUE;
            }

            if (bRunByScript == FALSE)
            {
                luaSystem->RunScriptFunction
                (
                    mapId,
                    QUEST_SCRIPTID,
                    DEF_PROC_EVENT_ENTRY_FN,
                    mapId,
                    playerId,
                    targetId,
                    idScript,
                    exIndex
                );
            }
        }
    }
}

void cs_manipulate_pet(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_pick_item(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_player_request_base_attr(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgRequestBaseAttrib dummy;
    bool b = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    assert(b);
    auto mapId = dummy.map_id();
    auto playerId = dummy.player_id();

    auto targetId = dummy.target_id();
    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

    Object* pObj = pMap->GetSpecificObjByID(playerId);
    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;

    pObj = pMap->GetSpecificObjByID(targetId);

    if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
    {
        return;
    }

    Character* pCharacter = (Character*)pObj;

    pCharacter->RequestBaseProperty(pPlayer);
}

void cs_query_event(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgQueryEvent dummy;
    bool b = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    assert(b);

    auto mapId = dummy.map_id();
    auto playerId = dummy.player_id();

    auto objectId = dummy.object_id();

    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

    Object* pObj = pMap->GetSpecificObjByID(playerId);
    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;

    pObj = pMap->GetSpecificObjByID(objectId);

    if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
    {
        return;
    }

    Monster* pMonster = (Monster*)pObj;

    ScriptID_t idScript = pMonster->GetScriptID();

    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

    if (idScript <= 0)
    {
        int32_t guid = pMonster->GetGUID();
        NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(guid);
        if (pQuest != NULL)
        {
            if (pQuest->m_EventCount == 0 && pQuest->m_QuestCount == 0)
            {
                luaSystem->RunScriptFunction(mapId,
                    SCENE_SCRIPTID,
                    DEF_PROC_MAP_NPCDEFAULTDIALOG_FN,
                    mapId,
                    playerId,
                    objectId,
                    guid
                );
            }
            else
            {
                luaSystem->RunScriptFunction(mapId,
                    SCENE_SCRIPTID,
                    DEF_PROC_MAP_NPCDEFAULTQUESTEVENTLIST_FN,
                    mapId,
                    playerId,
                    objectId,
                    guid
                );
            }
        }

        return;
    }
    else
    {

        luaSystem->RunScriptFunction(mapId, idScript, DEF_PROC_EVENT_ENTRY_FN,
            (int32)mapId,
            (int32)playerId,
            (int32)objectId);
    }
}

void cs_quest_abandon(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_accept(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_continue(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_refuse(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_quest_submit(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_swap_item(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_tick(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgTick dummy;
    bool b = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    assert(b);

    auto mapId = dummy.map_id();
    GameMap* pScene = MapManager::GetSingletonPtr()->getMap(mapId);
    if (NULL == pScene)
    {
        return;
    }


    ObjectManager* objectManager = pScene->GetObjManager();
    auto playerId = dummy.player_id();
    Object* pObj = objectManager->GetObj(playerId);

    const GLPos* pos = pObj->GetGLPos();

    auto playerX = dummy.player_pos_x();
    auto playerY = dummy.player_pos_y();

    int kk = 0;
}



void cs_takedown_equip(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgTakeDownEquip dummy;
    bool ret = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    auto equip_point = dummy.equip_point();
    if (equip_point < 0 || equip_point >= HEQUIP_NUMBER)
    {
        return;
    }
    PLAYER_EQUIP	equipPoint = (PLAYER_EQUIP)equip_point;

    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(dummy.map_id());
    if (nullptr == pMap)
    {
        return;
    }

    Object* pObj = pMap->GetSpecificObjByID(dummy.player_id());

    if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;

    Item* pEquipItem = sItemInterface.GetEquip(pPlayer, equipPoint);

    if (pEquipItem == nullptr)
    {
        return;
    }

    if (pEquipItem->IsFree())
    {
        return;
    }

    if (pEquipItem->IsLock())
    {
        return;
    }

    ItemContainer* pEquipContainer = pPlayer->GetEquipContain();

    if (nullptr == pEquipContainer)
    {
        return;
    }

    auto bag_index = dummy.bag_index();

    int32_t move_bag_index = -1;
    if (bag_index >= 0)
    {
        ItemContainer* pBagContainer = sItemInterface.GetBagContainer(pPlayer, bag_index);

        if (nullptr == pBagContainer)
        {
            return;
        }

        Item* pItem = pBagContainer->GetItem(pBagContainer->BagIndex2ConIndex(bag_index));

        if (!pItem->IsFree())
        {
            return;
        }

        move_bag_index = sItemInterface.MoveItemBt2Containers
        (
            nullptr,
            pPlayer,
            pEquipContainer,
            equipPoint,
            pBagContainer,
            pBagContainer->BagIndex2ConIndex(bag_index)
        );
    }
    else
    {
        move_bag_index = sItemInterface.MoveItemToBag(nullptr, pPlayer, pEquipContainer, equipPoint);

        if (move_bag_index < 0)
        {
            return;
        }
    }

    servermessage::ServerMsgTaskDownEquipResult packet;
    packet.set_bag_index(move_bag_index);
    packet.set_equip_point(equip_point);
    packet.set_result(UNEQUIP_SUCCESS);
    NetMessageManager::GetSingleton().sendNetMessage(pPlayer->GetConnector(), servermessage::SC_UNEQUIP_RESULT, &packet);

    /*SCUnEquipResult* packet = new SCUnEquipResult;

    packet->setBagIndex(mBagIndex);
    packet->setEquipPoint(mEquipPoint);
    packet->setResult(UNEQUIP_SUCCESS);

    NetManager::GetSingletonPtr()->sendNetMessage(packet);*/

    return;
}

void cs_use_ability(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void cs_use_equip(NetHandle h, const char* msg, uint32_t msg_size)
{
    clientmessage::MsgUseEquip dummy;

    bool ret = dummy.ParseFromArray(msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(dummy.map_id());
    if (nullptr == pMap)
        return;

    Object* pObj = pMap->GetSpecificObjByID(dummy.player_id());

    if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
    {
        return;
    }

    Player* pPlayer = (Player*)pObj;

    auto bag_index = dummy.bag_index();
    ItemContainer* pBagContainer = sItemInterface.GetBagContainer(pPlayer, bag_index);

    if (nullptr == pBagContainer)
    {
        return;
    }


    Item* pUseItem = pBagContainer->GetItem(pBagContainer->BagIndex2ConIndex(bag_index));

    PLAYER_EQUIP clientEquipPoint;

    int32_t itemclass = pUseItem->GetItemClass();
    if (itemclass == ICLASS_EQUIP)
    {
        if (pUseItem->IsLock())
        {
            return;
        }

        if (pUseItem->IsOverTime())
        {
            return;
        }

        if (pUseItem->GetRequireLevel() > pPlayer->GetLevel())
        {
            return;
        }

        if (pUseItem->GetReqJob() != PROFESSION_NONE)
        {
            if (pUseItem->GetReqJob() != pPlayer->GetProfession())
            {
                return;
            }
        }


        PLAYER_EQUIP	equipPoint = (PLAYER_EQUIP)pUseItem->GetEquipPoint();
        ItemContainer* pEquipContainer = pPlayer->GetEquipContain();

        
        if (dummy.equip_point() == -1)
        {
            clientEquipPoint = equipPoint;
        }
        else
        {
            clientEquipPoint = (PLAYER_EQUIP)dummy.equip_point();
        }


        if (equipPoint != clientEquipPoint)
        {
            if (equipPoint == HEQUIP_RING1)
            {
                if (clientEquipPoint != HEQUIP_RING2)
                {
                    return;
                }
            }

            if (equipPoint == HEQUIP_ADORN1)
            {
                if (clientEquipPoint != HEQUIP_ADORN2)
                {
                    return;
                }
            }
        }

        Item* pEquipItem = pEquipContainer->GetItem((uint32)clientEquipPoint);

        if (nullptr == pEquipItem)
        {
            return;
        }

        if (pEquipItem->IsFree())
        {
            sItemInterface.MoveItemBt2Containers
            (
                nullptr,
                pPlayer,
                pBagContainer,
                pBagContainer->BagIndex2ConIndex(bag_index),
                pEquipContainer,
                (uint32)equipPoint
            );
        }
        else
        {
            sItemInterface.ExchangeItem
            (
                pBagContainer,
                pBagContainer->BagIndex2ConIndex(bag_index),
                pEquipContainer,
                (uint32)equipPoint
            );
        }

    }

    servermessage::ServerMsgUseEquipResult packet;
    packet.set_bag_index(bag_index);
    packet.set_equip_point(clientEquipPoint);
    packet.set_result(USEEQUIP_SUCCESS);
    NetMessageManager::GetSingleton().sendNetMessage(pPlayer->GetConnector(), servermessage::SC_USEEQUIP_RESULT, &packet);

   /* SCUseEquipResult* packet = new SCUseEquipResult;
    packet->setResult(USEEQUIP_SUCCESS);
    packet->setBagIndex(mBagIndex);
    packet->setEquipPoint(clientEquipPoint);

    NetManager::GetSingletonPtr()->sendNetMessage(packet);*/

    return;
}