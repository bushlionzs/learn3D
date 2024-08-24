#include "stdafx.h"
#include "quest_manager.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "data/data_manager.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "item/Item_Interface.h"
#include "FileDef.h"
#include "server_manager.h"
#include "ScriptCacheMgr.h"
#include "item/Item_Interface.h"
#include "item/Item_Helper.h"
#include "Archive/PlayerDB.h"
#include "net/messages/SCScriptCommand.h"
#include "net_message_manager.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"

template<>
QuestManager* GameSingleton<QuestManager>::m_sSingleton = NULL;

QuestManager::QuestManager()
{

}

QuestManager::~QuestManager()
{

}

KHAN_RETURN_RESULT  QuestManager::Initialize()
{
    LoadDeliveryTable();
    LoadQuestLootItemTable();
    LoadQuestKillMonsterTable();
    initFlagMDClientFilter();
    return KRR_SUCCEED;
}

_QUEST_DATA_t* QuestManager::GetQuestData(int32_t questId)
{
    return DataManager::GetSingletonPtr()->getQuestByID(questId);
}

void QuestManager::OnNPCClicked(Player* pPlayer, MapID_t uSceneID, ObjID_t uNPCID, GUID_t uNPCGUID)
{
    uint32 i;

    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
    int32_t mapId = pPlayer->GetMap()->MapID();
    for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
    {
        const OWN_QUEST* pQuest = pPlayer->GetQuest(i);

        if (!pQuest->IsActiveQuest() || !pQuest->IsFlags_ClickNPC())
            continue;

        if (pQuest->m_idScript >= 100000)
        {
            luaSystem->RunScriptFunction(mapId, pQuest->m_idScript, DEF_PROC_QUEST_ATTACH_FN,
                mapId,
                pPlayer->GetID(),
                uNPCID,
                uNPCGUID,
                i,
                -1);
        }
        else
        {
            _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(pQuest->m_idQuest);
            if (pData == NULL)
            {
                //如果pData为空,加上日志记录,以备检查
                QLogSystem::QUICK_LOG(QUICK_LOG_ERROR, "[Error]QuestManager::OnNPCClicked Error Quest.mapId=%d,npcId=%d,npcGUID=%d questId=%d playerName=%s playerGUID=%X",
                    uSceneID,
                    uNPCID,
                    uNPCGUID,
                    pQuest->m_idQuest,
                    pPlayer->GetName(),
                    pPlayer->GetGUID());
            }

            KCheck(pData);
            if (pData->nSubmitNPCGUID != uNPCGUID)
                continue;
            if (pData->nSubmitNPCMapID != INVALID_ID)
            {
                if (pData->nSubmitNPCMapID != uSceneID)
                    continue;
            }
            {
                
                    luaSystem->RunScriptFunction(mapId, QUEST_SCRIPTID, DEF_PROC_QUEST_ATTACH_FN,
                        mapId,
                        (int32)pPlayer->GetID(),
                        (int32)uNPCID,
                        (int32)uNPCGUID,
                        (int32)i,
                        pQuest->m_idScript);
            }
        }
    }
}


BOOL QuestManager::IsQuestCompleted(const Player* const pPlayer, uint32 uIndexQuest)
{
    // 检查任务索引有效性
    if (uIndexQuest >= MAX_CHAR_QUEST_NUM)
    {
        return FALSE;
    }// if

    // 检查任务激活状态
    const OWN_QUEST* pOwnQuest = pPlayer->GetQuest(uIndexQuest);
    if (pOwnQuest->IsActiveQuest() == FALSE)
    {
        return FALSE;
    }// if

    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(pOwnQuest->m_idQuest);

    KCheck(pData);

    if (pData->nQuestType == 0 || pData->nQuestType == 2)
    {
        BOOL	bProcess = FALSE;
        BOOL	bFinish = TRUE;
        int32	i = 0;

        for (i = 0; i < 5; i++)
        {
            int32	nQuestDest = pData->nQuestDest[i];

            if (nQuestDest >= 10000 && nQuestDest <= 19999)
            {
                bProcess = TRUE;

                _QUEST_KILLMONSTER_t* pMK = (_QUEST_KILLMONSTER_t*)(m_QuestKillMonsterTable.Get(nQuestDest));

                KCheck(pMK);

                int32 nKillNum = pPlayer->GetQuestParam(uIndexQuest, i);

                if (nKillNum < pMK->nKillNum)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// if
            else if (nQuestDest >= 20000 && nQuestDest <= 29999)
            {
                bProcess = TRUE;

                _QUEST_DELIVERY_t* pMD = (_QUEST_DELIVERY_t*)(m_QuestDeliveryTable.Get(nQuestDest));

                KCheck(pMD);

                BOOL bNeedCheck = TRUE;

                if (pMD->nDeliveryItemID1 != -1 && pMD->nDeliveryItemNum1 > 0)
                {
                    bNeedCheck = FALSE;

                    int32	nItemCount = 0;

                    nItemCount += sItemInterface.CalcEquipItemCount((Player*)pPlayer, pMD->nDeliveryItemID1);
                    nItemCount += sItemInterface.CalcInventoryItemCount((Player*)pPlayer, pMD->nDeliveryItemID1);
                    if (nItemCount < pMD->nDeliveryItemNum1)
                    {
                        bFinish = FALSE;
                        break;
                    }// if
                }// if

                if (pMD->nDeliveryItemID2 != -1 && pMD->nDeliveryItemNum2 > 0)
                {
                    bNeedCheck = FALSE;

                    int32	nItemCount = 0;

                    nItemCount += sItemInterface.CalcEquipItemCount((Player*)pPlayer, pMD->nDeliveryItemID2);
                    nItemCount += sItemInterface.CalcInventoryItemCount((Player*)pPlayer, pMD->nDeliveryItemID2);
                    if (nItemCount < pMD->nDeliveryItemNum2)
                    {
                        bFinish = FALSE;
                        break;
                    }// if
                }// if

                if (pMD->nDeliveryItemID3 != -1 && pMD->nDeliveryItemNum3 > 0)
                {
                    bNeedCheck = FALSE;

                    int32 nItemCount = 0;

                    nItemCount += sItemInterface.CalcEquipItemCount((Player*)pPlayer, pMD->nDeliveryItemID3);
                    nItemCount += sItemInterface.CalcInventoryItemCount((Player*)pPlayer, pMD->nDeliveryItemID3);
                    if (nItemCount < pMD->nDeliveryItemNum3)
                    {
                        bFinish = FALSE;
                        break;
                    }// if
                }// if

                if (bNeedCheck)
                {
                    if (pPlayer->GetQuestParam(uIndexQuest, i) == 0)
                    {
                        bFinish = FALSE;
                        break;
                    }// if
                }// if
            }// else if
            else if (nQuestDest >= 30000 && nQuestDest <= 39999)
            {
                bProcess = TRUE;
                if (pPlayer->GetQuestParam(uIndexQuest, i) == 0)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// else if
            else if (nQuestDest >= 40000 && nQuestDest <= 49999)
            {
                bProcess = TRUE;
                if (pPlayer->GetQuestParam(uIndexQuest, i) == 0)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// else if
            else if (nQuestDest >= 50000 && nQuestDest <= 59999)
            {
                bProcess = TRUE;

                _QUEST_LOOKITEM_t* pML = (_QUEST_LOOKITEM_t*)(m_QuestLookItemTable.Get(nQuestDest));

                KCheck(pML);

                if (pML->nItemID1 != -1 && pML->nItemNum1 > 0)
                {
                    int32 nItemCount = 0;

                    nItemCount += sItemInterface.CalcEquipItemCount((Player*)pPlayer, pML->nItemID1);
                    nItemCount += sItemInterface.CalcInventoryItemCount((Player*)pPlayer, pML->nItemID1);
                    if (nItemCount < pML->nItemNum1)
                    {
                        bFinish = FALSE;
                        break;
                    }// if
                }// if
            }// else if
            else if (nQuestDest >= 60000 && nQuestDest <= 69999)
            {
                bProcess = TRUE;
                if (pPlayer->GetQuestParam(uIndexQuest, i) == 0)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// else if
        }// for

        if (bProcess == FALSE)
        {
            if (pPlayer->GetQuestParam(uIndexQuest, 7) == 1)
                bFinish = TRUE;
            else
                bFinish = FALSE;
        }// if

        return bFinish;
    }// if
    else
    {
        if (pPlayer->GetQuestParam(uIndexQuest, 7) == 1)
            return TRUE;

        return FALSE;
    }// else

    return FALSE;
}
extern ScriptCache* GetScriptFileData(ScriptID_t scriptid);
void QuestManager::ShowNpcQuestList(GameMap* pMap, int32* iQuestList, int32 iCount, ObjID_t selfId, ObjID_t targetId)
{
    int32_t mapId = pMap->MapID();
    for (int i = 0; i < iCount; i++)
    {
        _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iQuestList[i]);

        if (pData)
        {
            LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
            bool bRunByScript = false;
            if (pData->nScriptID >= 100000)
            {
                
                ScriptCache* pSFileData = GetScriptFileData(pData->nScriptID);

                if (pSFileData)
                {
                    luaSystem->RunScriptFunction(mapId,
                        pData->nScriptID, DEF_PROC_ENUM_EVENT_FN,
                        mapId,
                        selfId,
                        targetId,
                        iQuestList[i]);
                    bRunByScript = true;
                }
            }

            if (!bRunByScript)
            {
                luaSystem->RunScriptFunction(mapId,
                    QUEST_SCRIPTID, DEF_PROC_ENUM_EVENT_FN,
                    mapId,
                    selfId,
                    targetId,
                    iQuestList[i]);
            }
            
           
        }
    }
}

int32_t QuestManager::GetQuestState(Player* pPlayer, int32 iMissionID)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[64] = { 0 };
    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    if (!pPlayer->IsQuestHaveDone(iMissionID))
    {
        //没有做过这个任务,不一定就是循环任务也不一定是循环任务
        if (pData->nAcceptFlag == 0)
        {
            //普通任务的处理
            if (pPlayer->IsHaveQuest(iMissionID))
            {
                uint32	iMisIdx = pPlayer->GetQuestIndexByID(iMissionID);

                if (pPlayer->IsQuestCompleted(iMisIdx))
                {
                    return 7;
                }// if
                else
                {
                    return 6;
                }// else
            }// if
            else
            {
                return 5;
            }// else
        }// if
        else if (pData->nAcceptFlag == 1)
        {
            //循环任务的处理
            if (pPlayer->IsHaveQuest(iMissionID))
            {
                uint32	iMisIdx = pPlayer->GetQuestIndexByID(iMissionID);

                if (pPlayer->IsQuestCompleted(iMisIdx))
                {
                    return 7;
                }// if
                else
                {
                    return 6;
                }// else
            }// if
            else
            {
                return 8;
            }// else
        }// else if
        else if (pData->nAcceptFlag == 2)
        {
            //传送点任务的处理
            if (pPlayer->IsHaveQuest(iMissionID))
            {
                uint32	iMisIdx = pPlayer->GetQuestIndexByID(iMissionID);

                if (pPlayer->IsQuestCompleted(iMisIdx))
                {
                    return 7;
                }// if
                else
                {
                    return 6;
                }// else
            }// if
            else
            {
                return 17;
            }// else
        }// else if
        else
        {
            //其他情况,默认处理
            if (pPlayer->IsHaveQuest(iMissionID))
            {
                uint32 iMisIdx = pPlayer->GetQuestIndexByID(iMissionID);
                if (pPlayer->IsQuestCompleted(iMisIdx))
                {
                    return 7;
                }// if
                else
                {
                    return 6;
                }// else
            }// if
            else
            {
                return 5;
            }// else
        }// else
    }// if
    else
    {
        //如果玩家已经做过这个任务,一次性任务
        if (pData->nQuestType == 0)
        {
            return 13;
        }// if
        else
        {
            if (pPlayer->IsHaveQuest(iMissionID))
            {
                uint32	iMisIdx = pPlayer->GetQuestIndexByID(iMissionID);
                if (pPlayer->IsQuestCompleted(iMisIdx))
                {
                    return 7;
                }// if
                else
                {
                    return 6;
                }// else
            }// if
            else
            {
                return 5;
            }// else
        }// else
    }// else

    return 13;
}

//! 玩家背包物品发生变化的任务处理
void QuestManager::OnEvent_ItemChanged(Player* pPlayer, uint32 uItemDataID, int32 nChangeType)
{
    int32 i;
    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
    int32_t mapId = pPlayer->GetMap()->MapID();
    int32_t playerId = pPlayer->GetID();
    for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
    {
        const OWN_QUEST* pQuest = pPlayer->GetQuest(i);

        if (!pQuest->IsActiveQuest() )
            continue;
        if (!pQuest->IsFlags_ItemChanged())
            continue;
        if (pQuest->m_idScript >= 100000)
        {
            luaSystem->RunScriptFunction(mapId, pQuest->m_idScript, DEF_PROC_QUEST_ITEM_CHANGED_FN,
                mapId,
                playerId,
                (int32)uItemDataID,
                nChangeType);
        }// if
        else
        {
            _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(pQuest->m_idScript);

            if (pData)
            {
                BOOL bRunByScript = FALSE;

                if (pData->nScriptID >= 100000)
                {
                    ScriptCache* pSFileData = GetScriptFileData(pData->nScriptID);

                    if (pSFileData)
                    {
                        luaSystem->RunScriptFunction(mapId, pData->nScriptID, DEF_PROC_QUEST_ITEM_CHANGED_FN,
                            mapId,
                            playerId,
                            (int32)uItemDataID,
                            pQuest->m_idScript,
                            nChangeType);
                    }

                    bRunByScript = TRUE;
                }

                if (bRunByScript == FALSE)
                {
                    luaSystem->RunScriptFunction(mapId, QUEST_SCRIPTID, DEF_PROC_QUEST_ITEM_CHANGED_FN,
                        mapId,
                        playerId,
                        (int32)uItemDataID,
                        pQuest->m_idScript,
                        nChangeType);
                }
            }
        }
    }
}

int32_t QuestManager::GetNeedItemNum(int32 iMissionID, Lua_State* L, int32 itemId)
{
    char assetmsg[1024];
    _QUEST_DATA_t* pData = GetQuestData(iMissionID);

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    int32	i = 0;

    for (i = 0; i < 5; i++)
    {
        int32	nQuestDest = pData->nQuestDest[i];

        if (nQuestDest >= 50000 && nQuestDest <= 59999)
        {
            _QUEST_LOOKITEM_t* pML = (_QUEST_LOOKITEM_t*)(m_QuestLookItemTable.Get(nQuestDest));

            KCheck(pML);

            if (pML->nItemID1 == itemId)
            {
                Lua_PushNumber(L, pML->nItemNum1);
                Lua_PushNumber(L, i);
                return 2;
            }
        }
    }

    Lua_PushNumber(L, -1);
    Lua_PushNumber(L, -1);
    return 2;
}

BOOL QuestManager::QuestCheckSubmit(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 InstIndex)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[1024] = { 0 };

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    if (pData->nSubmitNPCMapID != INVALID_ID)
    {
        if (pData->nSubmitNPCMapID != pPlayer->GetMap()->MapID())
        {
            return FALSE;
        }// if
    }// if

    BOOL bFinish = TRUE;
    int32 i = 0;

    for (i = 0; i < 5; i++)
    {
        int32	nQuestDest = pData->nQuestDest[i];

        if (nQuestDest >= 10000 && nQuestDest <= 19999)
        {
            _QUEST_KILLMONSTER_t* pMK = (_QUEST_KILLMONSTER_t*)(m_QuestKillMonsterTable.Get(nQuestDest));

            KCheck(pMK);

            int32 nKillNum = pPlayer->GetQuestParam(InstIndex, i);

            if (nKillNum < pMK->nKillNum)
            {
                bFinish = FALSE;
                break;
            }// if
        }// if
        else if (nQuestDest >= 20000 && nQuestDest <= 29999)
        {
            _QUEST_DELIVERY_t* pMD = (_QUEST_DELIVERY_t*)(m_QuestDeliveryTable.Get(nQuestDest));

            KCheck(pMD);

            if (pMD->nDeliveryItemID1 != -1 && pMD->nDeliveryItemNum1 > 0)
            {
                int32	nItemCount = 0;

                nItemCount += sItemInterface.CalcEquipItemCount(pPlayer, pMD->nDeliveryItemID1);
                nItemCount += sItemInterface.CalcInventoryItemCount(pPlayer, pMD->nDeliveryItemID1);
                if (nItemCount < pMD->nDeliveryItemNum1)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// if

            if (pMD->nDeliveryItemID2 != -1 && pMD->nDeliveryItemNum2 > 0)
            {
                int32	nItemCount = 0;

                nItemCount += sItemInterface.CalcEquipItemCount(pPlayer, pMD->nDeliveryItemID2);
                nItemCount += sItemInterface.CalcInventoryItemCount(pPlayer, pMD->nDeliveryItemID2);
                if (nItemCount < pMD->nDeliveryItemNum2)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// if

            if (pMD->nDeliveryItemID3 != -1 && pMD->nDeliveryItemNum3 > 0)
            {
                int32	nItemCount = 0;

                nItemCount += sItemInterface.CalcEquipItemCount(pPlayer, pMD->nDeliveryItemID3);
                nItemCount += sItemInterface.CalcInventoryItemCount(pPlayer, pMD->nDeliveryItemID3);
                if (nItemCount < pMD->nDeliveryItemNum3)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// if
        }// else if
        else if (nQuestDest >= 30000 && nQuestDest <= 39999)
        {
            if (pPlayer->GetQuestParam(InstIndex, i) == 0)
            {
                bFinish = FALSE;
                break;
            }// if
        }// else if
        else if (nQuestDest >= 40000 && nQuestDest <= 49999)
        {
            if (pPlayer->GetQuestParam(InstIndex, i) == 0)
            {
                bFinish = FALSE;
                break;
            }// if
        }// else if
        else if (nQuestDest >= 50000 && nQuestDest <= 59999)
        {
            _QUEST_LOOKITEM_t* pML = (_QUEST_LOOKITEM_t*)(m_QuestLookItemTable.Get(nQuestDest));

            KCheck(pML);

            if (pML->nItemID1 != -1 && pML->nItemNum1 > 0)
            {
                int32	nItemCount = 0;

                nItemCount += sItemInterface.CalcEquipItemCount(pPlayer, pML->nItemID1);
                nItemCount += sItemInterface.CalcInventoryItemCount(pPlayer, pML->nItemID1);
                if (nItemCount < pML->nItemNum1)
                {
                    bFinish = FALSE;
                    break;
                }// if
            }// if
        }// else if
        else if (nQuestDest >= 60000 && nQuestDest <= 69999)
        {
            if (pPlayer->GetQuestParam(InstIndex, i) == 0)
            {
                bFinish = FALSE;
                break;
            }// if
        }// else if
    }// for

    return bFinish;
}

int32_t QuestManager::QuestComplate(Player* pPlayer, GameMap* pMap, int32 iMissionID, ObjID_t targetId, int32 selId)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[1024];

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    pMap->mItemList.Init();
    {
        if (pData->nFixItemID1 != -1 && pData->nFixItemNum1 > 0)
        {
            STSerialHelper	help(pData->nFixItemID1);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum1);
            }
        }

        if (pData->nFixItemID2 != -1 && pData->nFixItemNum2 > 0)
        {
            STSerialHelper	help(pData->nFixItemID2);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum2);
            }
        }

        if (pData->nFixItemID3 != -1 && pData->nFixItemNum3 > 0)
        {
            STSerialHelper	help(pData->nFixItemID3);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum3);
            }
        }

        if (pData->nFixItemID4 != -1 && pData->nFixItemNum4 > 0)
        {
            STSerialHelper	help(pData->nFixItemID4);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum4);
            }
        }

        if (selId > 0)
        {
            BOOL	bFind = FALSE;

            if (CHOOSE_BY_OLDTYPE == pData->nChooseType)
            {
                if (pData->nSelItemID1 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID1);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum1);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID2 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID2);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum2);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID3 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID3);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum3);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID4 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID4);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum4);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID5 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID5);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum5);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID6 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID6);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum6);
                        bFind = TRUE;
                    }
                }

            }// if
            else
            {
                if (CHOOSE_BY_SELECT == pData->nChooseType)
                {
                    for (int32 i = 0; i < pData->nSelItemCount; ++i)
                    {
                        if (pData->nSelItemsID[i] == selId)
                        {
                            STSerialHelper	help(pData->nSelItemsID[i]);
                            SItemType	itemType = help.GetItemTypeStruct();

                            if (!itemType.isNull())
                            {
                                pMap->mItemList.AddType(itemType, 1);
                                bFind = TRUE;
                            }// if
                        }// if
                    }// for
                }// if
                else
                {
                    // 根据角色的职业自动添加对应的物品
                    if (pData->nSelItemsID[pPlayer->GetDB()->GetProfession()] == selId)
                    {
                        STSerialHelper	help(pData->nSelItemsID[pPlayer->GetDB()->GetProfession()]);
                        SItemType	itemType = help.GetItemTypeStruct();

                        if (!itemType.isNull())
                        {
                            pMap->mItemList.AddType(itemType, 1);
                            bFind = TRUE;
                        }// if
                    }// if
                }// else
            }// else
            if (bFind == FALSE)
            {
                return -2;
            }
        }
        else if (CHOOSE_BY_PROFESSION == pData->nChooseType)
        {
            // 根据角色的职业自动添加对应的物品
            STSerialHelper	help(pData->nSelItemsID[pPlayer->GetDB()->GetProfession()]);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, 1);
            }
            else
            {
                return -2;
            }// if
        }

        if (pMap->mItemList.m_ListCount > 0)
        {
            if (sItemInterface.CanBagReceiveItemList(pPlayer, pMap->mItemList) == FALSE)
            {
                return -3;
            }
        }
    }

    pMap->mItemList.Init();
    {
        int32 i = 0;

        for (i = 0; i < 5; i++)
        {
            int32	nQuestDest = pData->nQuestDest[i];

            if (nQuestDest >= 20000 && nQuestDest <= 29999)
            {
                _QUEST_DELIVERY_t* pMD = (_QUEST_DELIVERY_t*)
                    (m_QuestDeliveryTable.Get(nQuestDest));

                KCheck(pMD);

                if (pMD->nDeliveryItemID1 != -1 && pMD->nDeliveryItemNum1 > 0)
                {
                    STSerialHelper	help(pMD->nDeliveryItemID1);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pMD->nDeliveryItemNum1);
                    }
                }

                if (pMD->nDeliveryItemID2 != -1 && pMD->nDeliveryItemNum2 > 0)
                {
                    STSerialHelper	help(pMD->nDeliveryItemID2);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pMD->nDeliveryItemNum2);
                    }
                }

                if (pMD->nDeliveryItemID3 != -1 && pMD->nDeliveryItemNum3 > 0)
                {
                    STSerialHelper	help(pMD->nDeliveryItemID3);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pMD->nDeliveryItemNum3);
                    }
                }
            }
            else if (nQuestDest >= 50000 && nQuestDest <= 59999)
            {
                _QUEST_LOOKITEM_t* pML = (_QUEST_LOOKITEM_t*)(m_QuestLookItemTable.Get(nQuestDest));

                KCheck(pML);

                STSerialHelper help(pML->nItemID1);
                SItemType itemType = help.GetItemTypeStruct();

                if (!itemType.isNull())
                {
                    pMap->mItemList.AddType(itemType, pML->nItemNum1);
                }
            }
        }

        if (sItemInterface.CanBagEraseItemList(pPlayer, pMap->mItemList) == 0)
        {
            return -4;
        }

        sItemInterface.EraseBagItemByItemList(nullptr, pPlayer, pMap->mItemList);
    }

    pPlayer->DelQuest(iMissionID);

    pPlayer->SetQuestHaveDone(iMissionID, TRUE);

    return 1;
}

void QuestManager::QuestBonusNotItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, ScriptID_t nScriptId)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[1024] = { 0 };

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    pMap->mItemList.Init();
    if (pData->nMoneyRewardP1 > 0)
    {
        uint32_t	nBounMoney = 0;

        if (pData->nMoneyRewardP1 > 0)
        {
            nBounMoney += pData->nMoneyRewardP1;
        }

        if (pData->nMoneyRewardP2 > 0)
        {
            nBounMoney += pData->nMoneyRewardP2 * pPlayer->GetLevel();
        }

        if (pData->nMoneyRewardP3 > 0)
        {
            nBounMoney += pData->nMoneyRewardP3 * pPlayer->GetLevel() * pPlayer->GetLevel();
        }

        switch (pData->nMoneyRewardType)
        {
        case CU_SILLER:
        {
            pPlayer->IncreaseMoney(CU_SILLER, nBounMoney);
        }
        break;

        case CU_BINDSILLER:
        {
            pPlayer->IncreaseMoney(CU_BINDSILLER, nBounMoney);
        }
        break;

        case CU_GOLD:
        {
            pPlayer->IncreaseMoney(CU_GOLD, nBounMoney);
        }
        break;

        case CU_BINDGOLD:
        {
            pPlayer->IncreaseMoney(CU_BINDGOLD, nBounMoney);
        }
        break;
        }
    }

    int32 nBounExp = 0;

    if (pPlayer->GetLevel() < MAX_PLAYER_EXP_LEVEL)
    {
        if (pData->nExpRewardP1 > 0)
        {
            nBounExp += pData->nExpRewardP1;
        }

        if (pData->nExpRewardP2 > 0)
        {
            nBounExp += pData->nExpRewardP2 * pPlayer->GetLevel();
        }

        if (pData->nExpRewardP3 > 0)
        {
            nBounExp += pData->nExpRewardP3 * pPlayer->GetLevel() * pPlayer->GetLevel();
        }
    }

    if (nBounExp > 0)
    {
        pPlayer->SetAlterPlayerExp(nBounExp);
    }

    if (pData->nShengWangType >= 0)
    {
        int32	nShengWang = 0;

        nShengWang += pData->nShengWangRewartP1;
        nShengWang += pData->nShengWangRewartP2 * pPlayer->GetLevel();
        nShengWang += pData->nShengWangRewartP3 * pPlayer->GetLevel() * pPlayer->GetLevel();

        if (nShengWang > 0)
        {
            switch (pData->nShengWangType)
            {
            case 0:		pPlayer->SetRongYu(pPlayer->GetRongYu() + nShengWang); 
                break;
            case 1:		pPlayer->SetShengWang(pPlayer->GetShengWang() + nShengWang); 
                break;
            case 2:		
                //pPlayer->SetPKValue(pPlayer->GetPKValue() + nShengWang); 
                break;
            case 3:		
                pPlayer->SetHonor(pPlayer->GetHonor() + nShengWang); 
                break;
            case 4:
            {
                //pPlayer->AddGuildPoint(nShengWang);
                break;
            }
            case 5:		
                pPlayer->SetWenCai(pPlayer->GetWenCai() + nShengWang); 
                break;
            case 6:		
                pPlayer->Set_Property_GoodBadValue(pPlayer->Get_Property_GoodBadValue() + nShengWang); 
                break;
            case 7:
            {
                pPlayer->SetCurInherenceExp(pPlayer->GetCurInherenceExp() +
                pPlayer->RefixInherenceExp(nShengWang));
            }
            break; // 7 天赋经验
            default:	break;
            }
        }
    }

    if (pData->nEnergyRewardType >= 0 && pData->nEnergyReward > 0)
    {
        if (pData->nEnergyRewardType == 0)
        {
            pPlayer->Set_Property_Vigor(pPlayer->Get_Property_Vigor() + pData->nEnergyReward);
        }
        else if (pData->nEnergyRewardType == 1)
        {
            pPlayer->SetHotValue(pPlayer->GetHotValue() + pData->nEnergyReward);
        }
        else if (pData->nEnergyRewardType == 2)
        {
            pPlayer->SetCurInherenceExp(pPlayer->GetCurInherenceExp() + pPlayer->RefixInherenceExp(pData->nEnergyReward));
        }
    }

    if (pData->nGuildRewardType >= 0 && pData->nGuildReward > 0)
    {
        if (pData->nGuildRewardType == 0)
        {
        }
        else if (pData->nGuildRewardType == 1)
        {
        }
        else if (pData->nGuildRewardType == 2)
        {
        }
        else if (pData->nGuildRewardType == 3)
        {
        }
        else if (pData->nGuildRewardType == 4)
        {
        }
    }
}

int32_t QuestManager::QuestBonusItem(Player* pPlayer, GameMap* pMap, int32 iMissionID, int32 selId)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[1024] = { 0 };

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);


    pMap->mItemList.Init();
    {
        if (pData->nFixItemID1 != -1 && pData->nFixItemNum1 > 0)
        {
            STSerialHelper	help(pData->nFixItemID1);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum1);
            }
        }

        if (pData->nFixItemID2 != -1 && pData->nFixItemNum2 > 0)
        {
            STSerialHelper	help(pData->nFixItemID2);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum2);
            }
        }

        if (pData->nFixItemID3 != -1 && pData->nFixItemNum3 > 0)
        {
            STSerialHelper	help(pData->nFixItemID3);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum3);
            }
        }

        if (pData->nFixItemID4 != -1 && pData->nFixItemNum4 > 0)
        {
            STSerialHelper	help(pData->nFixItemID4);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, pData->nFixItemNum4);
            }
        }

        if (selId > 0)
        {
            BOOL	bFind = FALSE;

            if (CHOOSE_BY_OLDTYPE == pData->nChooseType)
            {
                if (pData->nSelItemID1 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID1);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum1);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID2 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID2);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum2);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID3 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID3);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum3);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID4 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID4);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum4);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID5 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID5);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum5);
                        bFind = TRUE;
                    }
                }
                else if (pData->nSelItemID6 == selId)
                {
                    STSerialHelper	help(pData->nSelItemID6);
                    SItemType	itemType = help.GetItemTypeStruct();

                    if (!itemType.isNull())
                    {
                        pMap->mItemList.AddType(itemType, pData->nSelItemNum6);
                        bFind = TRUE;
                    }
                }

            }// if
            else
            {
                if (CHOOSE_BY_SELECT == pData->nChooseType)
                {
                    for (int32 i = 0; i < pData->nSelItemCount; ++i)
                    {
                        if (pData->nSelItemsID[i] == selId)
                        {
                            STSerialHelper	help(pData->nSelItemsID[i]);
                            SItemType	itemType = help.GetItemTypeStruct();

                            if (!itemType.isNull())
                            {
                                pMap->mItemList.AddType(itemType, 1);
                                bFind = TRUE;
                            }// if
                        }// if
                    }// for
                }// if
                else
                {
                    // 根据角色的职业自动添加对应的物品
                    if (pData->nSelItemsID[pPlayer->GetDB()->GetProfession()] == selId)
                    {
                        STSerialHelper	help(pData->nSelItemsID[pPlayer->GetDB()->GetProfession()]);
                        SItemType	itemType = help.GetItemTypeStruct();

                        if (!itemType.isNull())
                        {
                            pMap->mItemList.AddType(itemType, 1);
                            bFind = TRUE;
                        }// if
                    }// if
                }// else
            }// else
            if (bFind == FALSE)
            {
                return -2;
            }
        }
        else if (CHOOSE_BY_PROFESSION == pData->nChooseType)
        {
            // 根据角色的职业自动添加对应的物品
            STSerialHelper	help(pData->nSelItemsID[pPlayer->GetDB()->GetProfession()]);
            SItemType	itemType = help.GetItemTypeStruct();

            if (!itemType.isNull())
            {
                pMap->mItemList.AddType(itemType, 1);
            }
            else
            {
                return -2;
            }// if
        }

        if (pMap->mItemList.m_ListCount > 0)
        {
            if (sItemInterface.CanBagReceiveItemList(pPlayer, pMap->mItemList) == FALSE)
            {
                return -3;
            }

            sItemInterface.ReceiveBagItemList(nullptr, pPlayer, pMap->mItemList);
        }
    }

    return 1;
}


void QuestManager::OnEvent_PetChanged(Player* pPlayer, uint32 uPetDataID)
{
    uint32 i;
    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
    for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
    {
        const OWN_QUEST* pQuest = pPlayer->GetQuest(i);

        if (!pQuest->IsActiveQuest() || !pQuest->IsFlags_PetChanged())
            continue;

        int32 iScriptID = pQuest->m_idScript;

        if (pQuest->m_idScript < 100000)
        {
            _QUEST_DATA_t* pData = GetQuestData((int32)pQuest->m_idQuest);

            KCheck(pData);
            iScriptID = pData->nScriptID;
        }// if

        luaSystem->RunScriptFunction(pPlayer->GetMap()->MapID(), iScriptID, DEF_PROC_HORSE_CHANGED_FN,
            (int32)pPlayer->GetMap()->MapID(),
            (int32)pPlayer->GetID(),
            (int32)uPetDataID,
            (int32)pQuest->m_idQuest);
    }// for
}

//! 向客户端发送XCScriptCommand消息，从表格读取任务信息并发送。
void QuestManager::AddDispatchQuestInfo(Player* pPlayer, int32 iMissionID, ObjID_t targetId, int32 state)
{
    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(iMissionID);
    char assetmsg[1024] = { 0 };

    sprintf(assetmsg, "表格中没有相关数据%d", iMissionID);
    KCheckEx(pData, assetmsg);

    ScriptParam_QuestInfo	paramEventList;

    paramEventList.Reset();
    paramEventList.m_idNPC = targetId;
    paramEventList.m_idQuest = iMissionID;
    paramEventList.m_idScript = iMissionID;
    paramEventList.SetFlag(state);

    char strName[256] = { 0 };

    sprintf(strName, "#Y%s", pData->szQuestName);

    SScriptString	scriptStr;

    scriptStr = strName;
    paramEventList.AddText(&scriptStr);

    scriptStr = pData->szQuestDesc;
    paramEventList.AddText(&scriptStr);

    scriptStr = "#Y任务目标:";
    paramEventList.AddText(&scriptStr);
    if (strlen(pData->szQuestTarget1) > 0)
    {
        scriptStr = pData->szQuestTarget1;
        paramEventList.AddText(&scriptStr);
    }// if

    if (strlen(pData->szQuestTarget2) > 0)
    {
        scriptStr = pData->szQuestTarget2;
        paramEventList.AddText(&scriptStr);
    }// if

    if (strlen(pData->szQuestTarget3) > 0)
    {
        scriptStr = pData->szQuestTarget3;
        paramEventList.AddText(&scriptStr);
    }// if

    if (strlen(pData->szQuestTarget4) > 0)
    {
        scriptStr = pData->szQuestTarget4;
        paramEventList.AddText(&scriptStr);
    }// if

    if (strlen(pData->szQuestTarget5) > 0)
    {
        scriptStr = pData->szQuestTarget5;
        paramEventList.AddText(&scriptStr);
    }// if

    if (strlen(pData->szQuestHelp) > 0)
    {
        scriptStr = " ";
        paramEventList.AddText(&scriptStr);

        scriptStr = "#c00FF00小提示:";
        paramEventList.AddText(&scriptStr);

        char	strTemp[256] = { 0 };

        tsnprintf_s(strTemp, 256, "#c00FF00%s", pData->szQuestHelp);
        scriptStr = strTemp;

        paramEventList.AddText(&scriptStr);
    }// if

    SQuestBonus	bonus;
    uint32 nBonusExp = 0;

    if (pData->nExpRewardP1 > 0)
    {
        nBonusExp += pData->nExpRewardP1;
    }// if

    if (pData->nExpRewardP2 > 0)
    {
        nBonusExp += pData->nExpRewardP2 * pPlayer->GetLevel();
    }// if

    if (pData->nExpRewardP3 > 0)
    {
        nBonusExp += pData->nExpRewardP3 * pPlayer->GetLevel();
    }// if

    if (nBonusExp > 0)
    {
        bonus.SetExp(nBonusExp);
        paramEventList.AddBonus(&bonus);
        bonus.Reset();
    }// if

    if (pData->nMoneyRewardType >= 0)
    {
        uint32	nBounMoney = 0;

        if (pData->nMoneyRewardP1 > 0) nBounMoney += pData->nMoneyRewardP1;
        if (pData->nMoneyRewardP2 > 0) nBounMoney += pData->nMoneyRewardP2 * pPlayer->GetLevel();

        if (pData->nMoneyRewardP3 > 0)
            nBounMoney += pData->nMoneyRewardP3 * pPlayer->GetLevel() * pPlayer->GetLevel();

        if (nBounMoney > 0)
        {
            if (pData->nMoneyRewardType == 0)
            {
                bonus.SetMoney2(nBounMoney);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// if
            else if (pData->nMoneyRewardType == 1)
            {
                bonus.SetMoney1(nBounMoney);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nMoneyRewardType == 2)
            {
                bonus.SetMoney3(nBounMoney);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
        }// if
    }// if

    if (pData->nShengWangType >= 0)
    {
        int32	nShengWang = 0;

        if (pData->nShengWangRewartP1 > 0) nShengWang += pData->nShengWangRewartP1;
        if (pData->nShengWangRewartP2 > 0)
            nShengWang += pData->nShengWangRewartP2 * pPlayer->GetLevel();

        if (pData->nShengWangRewartP3 > 0)
            nShengWang += pData->nShengWangRewartP3 * pPlayer->GetLevel() * pPlayer->GetLevel();

        if (nShengWang > 0)
        {
            if (pData->nShengWangType == 0)
            {
                bonus.SetMoney4(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// if
            else if (pData->nShengWangType == 1)
            {
                bonus.SetMoney5(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 2)
            {
                bonus.SetMoney7(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 3)
            {
                bonus.SetMoney6(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 4)
            {
                bonus.SetMoney8(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 5)
            {
                bonus.SetMoney9(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 6)
            {
                bonus.SetWeiWang(nShengWang);
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
            else if (pData->nShengWangType == 7) // 7 天赋经验
            {
                bonus.SetInherenceExp(pPlayer->RefixInherenceExp(nShengWang));
                paramEventList.AddBonus(&bonus);
                bonus.Reset();
            }// else if
        }// if
    }// if

    if (pData->nEnergyRewardType >= 0 && pData->nEnergyReward > 0)
    {
        if (pData->nEnergyRewardType == 0)
        {
            bonus.Set_Property_Vigor(pData->nEnergyReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }
        else if (pData->nEnergyRewardType == 1)
        {
            bonus.SetCharm(pData->nEnergyReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
        else if (pData->nEnergyRewardType == 2)
        {
            bonus.SetGenius(pData->nEnergyReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
    }// if

    if (pData->nGuildRewardType >= 0 && pData->nGuildReward > 0)
    {
        if (pData->nGuildRewardType == 0)
        {
            bonus.SetGuildExp(pData->nGuildReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if
        else if (pData->nGuildRewardType == 1)
        {
            bonus.SetCountryFood(pData->nGuildReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
        else if (pData->nGuildRewardType == 2)
        {
            bonus.SetCountryMoney(pData->nGuildReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
        else if (pData->nGuildRewardType == 3)
        {
            bonus.SetCountryWood(pData->nGuildReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
        else if (pData->nGuildRewardType == 4)
        {
            bonus.SetCountryMetal(pData->nGuildReward);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else if
    }// if

    if (pData->nFixItemID1 != -1 && pData->nFixItemNum1 > 0)
    {
        bonus.SetItem(pData->nFixItemID1, (uchar)pData->nFixItemNum1);
        paramEventList.AddBonus(&bonus);
        bonus.Reset();
    }// if

    if (pData->nFixItemID2 != -1 && pData->nFixItemNum2 > 0)
    {
        bonus.SetItem(pData->nFixItemID2, (uchar)pData->nFixItemNum2);
        paramEventList.AddBonus(&bonus);
        bonus.Reset();
    }// if

    if (pData->nFixItemID3 != -1 && pData->nFixItemNum3 > 0)
    {
        bonus.SetItem(pData->nFixItemID3, (uchar)pData->nFixItemNum3);
        paramEventList.AddBonus(&bonus);
        bonus.Reset();
    }// if

    if (pData->nFixItemID4 != -1 && pData->nFixItemNum4 > 0)
    {
        bonus.SetItem(pData->nFixItemID4, (uchar)pData->nFixItemNum4);
        paramEventList.AddBonus(&bonus);
        bonus.Reset();
    }// if

    if (CHOOSE_BY_OLDTYPE == pData->nChooseType)
    {
        if (pData->nSelItemID1 != -1 && pData->nSelItemNum1 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID1, (uchar)pData->nSelItemNum1);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if

        if (pData->nSelItemID2 != -1 && pData->nSelItemNum2 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID2, (uchar)pData->nSelItemNum2);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if

        if (pData->nSelItemID3 != -1 && pData->nSelItemNum3 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID3, (uchar)pData->nSelItemNum3);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if

        if (pData->nSelItemID4 != -1 && pData->nSelItemNum4 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID4, (uchar)pData->nSelItemNum4);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if

        if (pData->nSelItemID5 != -1 && pData->nSelItemNum5 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID5, (uchar)pData->nSelItemNum5);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if

        if (pData->nSelItemID6 != -1 && pData->nSelItemNum6 > 0)
        {
            bonus.SetItemRadio(pData->nSelItemID6, (uchar)pData->nSelItemNum6);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// if
    }// if
    else
    {
        if (CHOOSE_BY_SELECT == pData->nChooseType)
        {
            for (int32 i = 0; i < pData->nSelItemCount; ++i)
            {
                if (pData->nSelItemsID[i] != 0)
                {
                    bonus.SetItemRadio(pData->nSelItemsID[i], 1);
                    paramEventList.AddBonus(&bonus);
                    bonus.Reset();
                }// if
            }// for
        }// if
        else
        {
            // 根据角色的职业自动添加对应的物品
            bonus.SetItem(pData->nSelItemsID[pPlayer->GetDB()->GetProfession()], 1);
            paramEventList.AddBonus(&bonus);
            bonus.Reset();
        }// else
    }// else
    pPlayer->SetRuntimeData(RT_EVENT_REQUEST_NPCID, targetId);
    pPlayer->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, iMissionID);

    SCScriptCommand* packet = new SCScriptCommand;
    packet->setCmdId(SCRIPT_COMMAND_QUEST_RESPONSE);
    packet->setQuestInfo(paramEventList);
    NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
}


void QuestManager::OnEvent_KillObject(Player* pPlayer, Character* pObj)
{
    if (pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
        return;

    Monster* pMonster = (Monster*)pObj;
    uint32	i, uDataID;

    LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

    int32_t mapId = pPlayer->GetMap()->MapID();

    uDataID = pObj->GetDataID();
    for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
    {
        const OWN_QUEST* pQuest = pPlayer->GetQuest(i);

        if (!pQuest->IsActiveQuest() || !pQuest->IsFlags_KillObject())
            continue;

        int32	nQuest = pQuest->m_idQuest;
        BOOL	bToggle = FALSE;

        for (int32 j = 0; j < pMonster->m_nKillCount; j++)
        {
            if (pMonster->m_sKillObj[j].m_nQuestId == nQuest)
            {
                bToggle = TRUE;
                break;
            }// if
        }// for

        if (!bToggle)
        {
            if (pMonster->m_nKillCount < Monster::BEKILL_QUEST_NUM)
            {
                pMonster->m_sKillObj[pMonster->m_nKillCount++].m_nQuestId = nQuest;

                BOOL bRunByScript = FALSE;

                if (pQuest->m_idScript >= 100000)
                {
                    luaSystem->RunScriptFunction(mapId, pQuest->m_idScript, DEF_PROC_QUEST_OBJECT_KILLED_FN,
                        mapId,
                        (int32)pPlayer->GetID(),
                        (int32)uDataID,
                        (int32)pObj->GetID_i(),
                        -1);
                }// if
                else
                {
                    _QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(pQuest->m_idScript);

                    if (pData)
                    {
                        BOOL bRunByScript = FALSE;

                        if (pData->nScriptID >= 100000)
                        {
                            ScriptCache* pSFileData = GetScriptFileData(pData->nScriptID);

                            if (pSFileData)
                            {
                                luaSystem->RunScriptFunction(mapId, pData->nScriptID, DEF_PROC_QUEST_OBJECT_KILLED_FN,
                                    mapId,
                                    (int32)pPlayer->GetID(),
                                    (int32)uDataID,
                                    (int32)pObj->GetID_i(),
                                    (int32)pQuest->m_idQuest);
                                bRunByScript = TRUE;
                            }// if
                        }// if

                        if (bRunByScript == FALSE)
                        {
                            luaSystem->RunScriptFunction(mapId, QUEST_SCRIPTID, DEF_PROC_QUEST_OBJECT_KILLED_FN,
                                mapId,
                                (int32)pPlayer->GetID(),
                                (int32)uDataID,
                                (int32)pObj->GetID_i(),
                                pQuest->m_idScript);
                        }// if
                    }// if
                }// else
            }// if
            else
            {
                KCheckEx(pMonster->m_nKillCount < Monster::BEKILL_QUEST_NUM, "overflow exception");
                pMonster->m_nKillCount--;
                break;
            }// else
        }// if
    }// for
}


int32 QuestManager::GetItemIdInItemBox(Lua_State* L, int32 gpType, Player* pPlayer, int32 itemId)
{
    int32 i = 0;
    char assetmsg[1024];

    for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
    {
        const OWN_QUEST* pQuest = pPlayer->GetQuest(i);

        if (pQuest->m_idQuest == INVALID_ID) continue;

        _QUEST_DATA_t* pData = GetQuestData(pQuest->m_idQuest);

        sprintf(assetmsg, "表格中没有相关数据%d", pQuest->m_idQuest);
        KCheckEx(pData, assetmsg);

        int32 j = 0;

        for (j = 0; j < 5; j++)
        {
            int32	nQuestDest = pData->nQuestDest[j];

            if (nQuestDest >= 50000 && nQuestDest <= 59999)
            {
                _QUEST_LOOKITEM_t* pML = (_QUEST_LOOKITEM_t*)(m_QuestLookItemTable.Get(nQuestDest));

                KCheck(pML);

                if (pML->nLookItemType == 2 && pML->nItemID1 == itemId && pML->nGrowPointType == gpType)
                {
                    Lua_PushNumber(L, pQuest->m_idQuest);
                    Lua_PushNumber(L, pML->nItemNum1);
                    Lua_PushNumber(L, pML->nCollectNum);
                    return 3;
                }
            }
        }
    }

    Lua_PushNumber(L, -1);
    Lua_PushNumber(L, -1);
    Lua_PushNumber(L, -1);
    return 3;
}

void QuestManager::LoadQuestList()
{

}


void QuestManager::LoadDeliveryTable()
{
    enum
    {
        Delivery_QuestIndex,
        Delivery_DeliveryItemID1,
        Delivery_DeliveryItemNum1,
        Delivery_DeliveryItemID2,
        Delivery_DeliveryItemNum2,
        Delivery_DeliveryItemID3,
        Delivery_DeliveryItemNum3,
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_DELIVERY);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 7);
    KCheck(iTableCount > 0);

    m_QuestDeliveryTable.m_QuestDelivery = new _QUEST_DELIVERY_t[iTableCount];
    m_QuestDeliveryTable.m_nQuestDeliveryCount = iTableCount;

    memset(m_QuestDeliveryTable.m_QuestDelivery, 0, sizeof(_QUEST_DELIVERY_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestDeliveryTable.m_QuestDelivery[i].nQuestIndex = ThirdFile.Search_Posistion(i, Delivery_QuestIndex)->iValue;;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemID1 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemID1)->iValue;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemNum1 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemNum1)->iValue;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemID2 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemID2)->iValue;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemNum2 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemNum2)->iValue;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemID3 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemID3)->iValue;
        m_QuestDeliveryTable.m_QuestDelivery[i].nDeliveryItemNum3 = ThirdFile.Search_Posistion(i, Delivery_DeliveryItemNum3)->iValue;
    }
}


void QuestManager::LoadEscortTable()
{
    enum THS
    {
        HuSongIdx_QuestIndex = 0,
        HuSongIdx_HuSongType,
        HuSongIdx_BusAI,
        HuSongIdx_AIScript,
        HuSongIdx_EventScript,
        HuSongIdx_ImpactID,
        HuSongIdx_BusVisual,
        HuSongIdx_NPCName,
        HuSongIdx_NPCTitle,
        HuSongIdx_EmptyTime,
        HuSongIdx_BusLife,
        HuSongIdx_PatrolID,
    };
    TABFile ThirdFile(0);
    BOOL	ret = ThirdFile.OpenFromTXT(FILE_QUEST_HUSONG);
    int32	iTableCount = ThirdFile.GetRecordsNum();
    int32	iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 12);
    KCheck(iTableCount > 0);

    m_QuestEscortTable.m_QuestHuSong = new _QUEST_HUSONG_t[iTableCount];
    m_QuestEscortTable.m_nQuestHuSongCount = iTableCount;

    memset(m_QuestEscortTable.m_QuestHuSong, 0, sizeof(_QUEST_HUSONG_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestEscortTable.m_QuestHuSong[i].nQuestIndex = ThirdFile.Search_Posistion(i, HuSongIdx_QuestIndex)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nHuSongType = ThirdFile.Search_Posistion(i, HuSongIdx_HuSongType)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nBusAI = ThirdFile.Search_Posistion(i, HuSongIdx_BusAI)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nAIScript = ThirdFile.Search_Posistion(i, HuSongIdx_AIScript)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nEventScript = ThirdFile.Search_Posistion(i, HuSongIdx_EventScript)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nEffectID = ThirdFile.Search_Posistion(i, HuSongIdx_ImpactID)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nBusVisual = ThirdFile.Search_Posistion(i, HuSongIdx_BusVisual)->iValue;
        strncpy(m_QuestEscortTable.m_QuestHuSong[i].szNPCName, ThirdFile.Search_Posistion(i, HuSongIdx_NPCName)->pString, NPC_NAME_LEN - 1);
        strncpy(m_QuestEscortTable.m_QuestHuSong[i].szNPCTitle, ThirdFile.Search_Posistion(i, HuSongIdx_NPCTitle)->pString, NPC_NAME_LEN - 1);
        m_QuestEscortTable.m_QuestHuSong[i].nEmptyTime = ThirdFile.Search_Posistion(i, HuSongIdx_EmptyTime)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nBusLife = ThirdFile.Search_Posistion(i, HuSongIdx_BusLife)->iValue;
        m_QuestEscortTable.m_QuestHuSong[i].nPatrolID = ThirdFile.Search_Posistion(i, HuSongIdx_PatrolID)->iValue;
    }
}


void QuestManager::LoadUseItemTable()
{
    enum
    {
        UseItem_QuestIndex,
        UseItem_UseItemType,
        UseItem_ItemID1,
        UseItem_SceneID,
        UseItem_PosX,
        UseItem_PosZ,
        UseItem_Radius,
        UseItem_SkillID,
        UseItem_UseItemDesc,
        UseItem_UseDialog,
        UseItem_UseItemDialog,
        UseItem_UseItemErrorDialog,
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_USEITEM);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 12);
    KCheck(iTableCount > 0);

    m_QuestUseItemTable.m_QuestUseItem = new _QUEST_USEITEM_t[iTableCount];
    m_QuestUseItemTable.m_nQuestUseItemCount = iTableCount;

    memset(m_QuestUseItemTable.m_QuestUseItem, 0, sizeof(_QUEST_USEITEM_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestUseItemTable.m_QuestUseItem[i].nQuestIndex = ThirdFile.Search_Posistion(i, UseItem_QuestIndex)->iValue;
        m_QuestUseItemTable.m_QuestUseItem[i].nUseItemType = ThirdFile.Search_Posistion(i, UseItem_UseItemType)->iValue;
        m_QuestUseItemTable.m_QuestUseItem[i].nItemID1 = ThirdFile.Search_Posistion(i, UseItem_ItemID1)->iValue;
        strncpy(m_QuestUseItemTable.m_QuestUseItem[i].szSceneID, ThirdFile.Search_Posistion(i, UseItem_SceneID)->pString, 128);
        m_QuestUseItemTable.m_QuestUseItem[i].nPosX = ThirdFile.Search_Posistion(i, UseItem_PosX)->iValue;
        m_QuestUseItemTable.m_QuestUseItem[i].nPosZ = ThirdFile.Search_Posistion(i, UseItem_PosZ)->iValue;
        m_QuestUseItemTable.m_QuestUseItem[i].nRadius = ThirdFile.Search_Posistion(i, UseItem_Radius)->iValue;
        m_QuestUseItemTable.m_QuestUseItem[i].nSkillID = ThirdFile.Search_Posistion(i, UseItem_SkillID)->iValue;
        strncpy(m_QuestUseItemTable.m_QuestUseItem[i].szUseItemDesc, ThirdFile.Search_Posistion(i, UseItem_UseItemDesc)->pString, 512);
        m_QuestUseItemTable.m_QuestUseItem[i].nUseDialog = ThirdFile.Search_Posistion(i, UseItem_UseDialog)->iValue;
        strncpy(m_QuestUseItemTable.m_QuestUseItem[i].szUseItemDialog, ThirdFile.Search_Posistion(i, UseItem_UseItemDialog)->pString, 512);
        strncpy(m_QuestUseItemTable.m_QuestUseItem[i].szUseItemErrorDialog, ThirdFile.Search_Posistion(i, UseItem_UseItemErrorDialog)->pString, 60);
    }
}


void QuestManager::LoadQuestLootItemTable()
{
    enum
    {
        LootItemIdx_QuestIndex,
        LootItemIdx_LookItemType,
        LootItemIdx_ItemID1,
        LootItemIdx_ItemNum1,
        LootItemIdx_GrowPointType,
        LootItemIdx_CollectNum,
        LootItemIdx_MonsterSceneID,
        LootItemIdx_MonsterName,
        LootItemIdx_MonsterTitle,
        LootItemIdx_MonsterType,
        LootItemIdx_MonsterLevelMin,
        LootItemIdx_MonsterLevelMax,
        LootItemIdx_CourseIndex,
        LootItemIdx_DropRand,
        LootItemIdx_MaxDropNum,
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_LOOTITEM);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 15);
    KCheck(iTableCount > 0);

    m_QuestLookItemTable.m_QuestLookItem = new _QUEST_LOOKITEM_t[iTableCount];
    m_QuestLookItemTable.m_nQuestLookItemCount = iTableCount;

    memset(m_QuestLookItemTable.m_QuestLookItem, 0, sizeof(_QUEST_LOOKITEM_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestLookItemTable.m_QuestLookItem[i].nQuestIndex = ThirdFile.Search_Posistion(i, LootItemIdx_QuestIndex)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nLookItemType = ThirdFile.Search_Posistion(i, LootItemIdx_LookItemType)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nItemID1 = ThirdFile.Search_Posistion(i, LootItemIdx_ItemID1)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nItemNum1 = ThirdFile.Search_Posistion(i, LootItemIdx_ItemNum1)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nGrowPointType = ThirdFile.Search_Posistion(i, LootItemIdx_GrowPointType)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nCollectNum = ThirdFile.Search_Posistion(i, LootItemIdx_CollectNum)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nMonsterSceneID = ThirdFile.Search_Posistion(i, LootItemIdx_MonsterSceneID)->iValue;
        strncpy(m_QuestLookItemTable.m_QuestLookItem[i].szMonsterName, ThirdFile.Search_Posistion(i, LootItemIdx_MonsterName)->pString, NPC_NAME_LEN);
        strncpy(m_QuestLookItemTable.m_QuestLookItem[i].szMonsterTitle, ThirdFile.Search_Posistion(i, LootItemIdx_MonsterTitle)->pString, NPC_NAME_LEN);
        m_QuestLookItemTable.m_QuestLookItem[i].nMonsterType = ThirdFile.Search_Posistion(i, LootItemIdx_MonsterType)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nMonsterLevelMin = ThirdFile.Search_Posistion(i, LootItemIdx_MonsterLevelMin)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nMonsterLevelMax = ThirdFile.Search_Posistion(i, LootItemIdx_MonsterLevelMax)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nCourseIndex = ThirdFile.Search_Posistion(i, LootItemIdx_CourseIndex)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nDropRand = ThirdFile.Search_Posistion(i, LootItemIdx_DropRand)->iValue;
        m_QuestLookItemTable.m_QuestLookItem[i].nMaxDropNum = ThirdFile.Search_Posistion(i, LootItemIdx_MaxDropNum)->iValue;
    }
}


void QuestManager::LoadQuestKillMonsterTable()
{
    enum
    {
        KillMonsterIdx_QuestIndex,
        KillMonsterIdx_MonsterSceneID,
        KillMonsterIdx_MonsterName,
        KillMonsterIdx_MonsterTitle,
        KillMonsterIdx_MonsterType,
        KillMonsterIdx_MonsterLevelMin,
        KillMonsterIdx_MonsterLevelMax,
        KillMonsterIdx_CourseIndex,
        KillMonsterIdx_KillNum,
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_KILLMONSTER);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 9);
    KCheck(iTableCount > 0);

    m_QuestKillMonsterTable.m_QuestKillMonster = new _QUEST_KILLMONSTER_t[iTableCount];
    m_QuestKillMonsterTable.m_nQuestKillMonsterCount = iTableCount;

    memset(m_QuestKillMonsterTable.m_QuestKillMonster, 0, sizeof(_QUEST_KILLMONSTER_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nQuestIndex = ThirdFile.Search_Posistion(i, KillMonsterIdx_QuestIndex)->iValue;
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nMonsterSceneID = ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterSceneID)->iValue;
        strncpy(m_QuestKillMonsterTable.m_QuestKillMonster[i].szMonsterName, ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterName)->pString, NPC_NAME_LEN);
        strncpy(m_QuestKillMonsterTable.m_QuestKillMonster[i].szMonsterTitle, ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterTitle)->pString, NPC_NAME_LEN);
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nMonsterType = ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterType)->iValue;
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nMonsterLevelMin = ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterLevelMin)->iValue;
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nMonsterLevelMax = ThirdFile.Search_Posistion(i, KillMonsterIdx_MonsterLevelMax)->iValue;
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nCourseIndex = ThirdFile.Search_Posistion(i, KillMonsterIdx_CourseIndex)->iValue;
        m_QuestKillMonsterTable.m_QuestKillMonster[i].nKillNum = ThirdFile.Search_Posistion(i, KillMonsterIdx_KillNum)->iValue;
    }// for
}


void QuestManager::LoadQuestEnterAreaTable()
{
    enum
    {
        EnterAreaIdx_QuestIndex,
        EnterAreaIdx_AreaName,
        EnterAreaIdx_AreaSceneID,
        EnterAreaIdx_AreaID,
        EnterAreaIdx_AreaIndex,
        EnterAreaIdx_EnterArea,
        EnterAreaIdx_IfHaveDialog,
        EnterAreaIdx_EnterAreaDialog,
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_QUEST_ENTERAREA);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn == 8);
    KCheck(iTableCount > 0);

    m_QuestEnterAreaTable.m_QuestEnterArea = new _QUEST_ENTERAREA_t[iTableCount];
    m_QuestEnterAreaTable.m_nQuestEnterAreaCount = iTableCount;

    memset(m_QuestEnterAreaTable.m_QuestEnterArea, 0, sizeof(_QUEST_ENTERAREA_t) * iTableCount);

    for (int32 i = 0; i < iTableCount; ++i)
    {
        m_QuestEnterAreaTable.m_QuestEnterArea[i].nQuestIndex = ThirdFile.Search_Posistion(i, EnterAreaIdx_QuestIndex)->iValue;
        strncpy(m_QuestEnterAreaTable.m_QuestEnterArea[i].szAreaName, ThirdFile.Search_Posistion(i, EnterAreaIdx_AreaName)->pString, 128);
        strncpy(m_QuestEnterAreaTable.m_QuestEnterArea[i].szAreaSceneID, ThirdFile.Search_Posistion(i, EnterAreaIdx_AreaSceneID)->pString, 128);
        m_QuestEnterAreaTable.m_QuestEnterArea[i].nAreaID = ThirdFile.Search_Posistion(i, EnterAreaIdx_AreaID)->iValue;
        m_QuestEnterAreaTable.m_QuestEnterArea[i].nAreaIndex = ThirdFile.Search_Posistion(i, EnterAreaIdx_AreaIndex)->iValue;
        strncpy(m_QuestEnterAreaTable.m_QuestEnterArea[i].szEnterArea, ThirdFile.Search_Posistion(i, EnterAreaIdx_EnterArea)->pString, 256);
        m_QuestEnterAreaTable.m_QuestEnterArea[i].nIfHaveDialog = ThirdFile.Search_Posistion(i, EnterAreaIdx_IfHaveDialog)->iValue;
        strncpy(m_QuestEnterAreaTable.m_QuestEnterArea[i].szEnterAreaDialog, ThirdFile.Search_Posistion(i, EnterAreaIdx_EnterAreaDialog)->pString, 256);
    }
}

void QuestManager::initFlagMDClientFilter()
{
    enum
    {
        DataIdx_MisPos = 15,/* 个人全局时间，循环任务的任务已做参数 */
    };

    TABFile ThirdFile(0);
    BOOL ret = ThirdFile.OpenFromTXT(FILE_DAY_TIPS);

    int32 iTableCount = ThirdFile.GetRecordsNum();
    int32 iTableColumn = ThirdFile.GetFieldsNum();

    KCheck(iTableColumn >= DataIdx_MisPos);
    KCheck(iTableCount);

    const int32 ITEMLIST_LENGTH = 32;
    char chItemIDList[ITEMLIST_LENGTH] = { 0 };
    int32 iLength = 0, iItemLength = 0;

    SplitStringLevelOne* pSplitL1 = new SplitStringLevelOne;
    SplitStringLevelTwo* pSplitL2 = new SplitStringLevelTwo;


    for (int32 i = 0; i < iTableCount; ++i)
    {
        strncpy(chItemIDList, ThirdFile.Search_Posistion(i, DataIdx_MisPos)->pString, ITEMLIST_LENGTH);
        iLength = (int32)strlen(chItemIDList);
        KCheckEx(iLength < ITEMLIST_LENGTH, "iLength超过长度!");


        pSplitL1->Init('|', pSplitL2);
        pSplitL2->Init('~', NULL);
        pSplitL1->DoSplit(chItemIDList);

        int32 iLineCount = pSplitL2->GetResultLineCount();

        if (6 != iLineCount)
        {
            continue;
        }
        int32 iMDIndex1 = atoi(pSplitL2->GetResultLine(0));
        int32 iMDIndex2 = atoi(pSplitL2->GetResultLine(3));

        if (!m_FlagMDClientFilter.IsSetBit(iMDIndex1))
        {
            m_FlagMDClientFilter.UpdateBit(iMDIndex1, TRUE);
        }

        if (iMDIndex1 != iMDIndex2 && !m_FlagMDClientFilter.IsSetBit(iMDIndex2))
        {
            m_FlagMDClientFilter.UpdateBit(iMDIndex2, TRUE);
        }

    }// for

    delete pSplitL1;
    delete pSplitL2;
}