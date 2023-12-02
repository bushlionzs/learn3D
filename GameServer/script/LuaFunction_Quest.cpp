#include "stdafx.h"
#include "LuaFunction_Quest.h"
#include "net/messages/SCQueryEventResult.h"
#include "net/net_message_manager.h"
#include "LuaMacro.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "gameobject/Monster.h"
#include "quest/quest_manager.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "data/data_manager.h"
#include "ScriptDef.h"
#include "net/messages/SCCommand.h"
#include "net/messages/SCScriptCommand.h"
#include "net/messages/CSQuestAccept.h"
#include "item/Item_Interface.h"
#include "item/Item_Helper.h"

enum 
{ 
	EA_Number, 
	EA_State, 
	EA_Index, 
	EA_Count
};

int32_t LuaFunction_BeginQuestEvent(Lua_State* L)
{
	LuaStack args(L);

	int32_t args_count = args.Count();

	if (!args[1].IsNumber())
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = args[1].GetNumber();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	pMap->m_QuestBuffer.Reset();

	return 0;
}

int32_t LuaFunction_DispatchQuestEventList(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);

	SCQueryEventResult* packet = new SCQueryEventResult();
	packet->mParamEventList.Reset();
	packet->mParamEventList.m_idNPC = targetId;

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	for (int32 i = 0; i < pMap->m_QuestBuffer.mUseNum; i++)
	{
		if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Str)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~*/
			SScriptEventItem itemEvent;
			SScriptString	scriptStr;
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			scriptStr = pMap->m_QuestBuffer.Buff[i].buf;
			itemEvent.SetText(&scriptStr);
			packet->mParamEventList.AddItem(&itemEvent);
		}
		else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Int)
		{
		}
		else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_IntStr)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32		number = *(int32*)
				(pMap->m_QuestBuffer.Buff[i].buf + EA_Number * sizeof(int32));
			int32		state = *(int32*)(pMap->m_QuestBuffer.Buff[i].buf + EA_State * sizeof(int32));
			int32		index = *(int32*)(pMap->m_QuestBuffer.Buff[i].buf + EA_Index * sizeof(int32));
			SScriptString	scriptStr;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			scriptStr = pMap->m_QuestBuffer.Buff[i].buf + EA_Count * sizeof(int32);

			/*~~~~~~~~~~~~~~~~~~~~~~*/
			SScriptEventItem itemEvent;
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			itemEvent.SetScriptID(index, state, number, &scriptStr);
			packet->mParamEventList.AddItem(&itemEvent);
		}
	}

	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	lua_pushnumber(L, 1);
	return 1;
}

int32_t LuaFunction_EndQuestEvent(Lua_State* L)
{
	return 0;
}

int32_t LuaFunction_AddQuestText(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	const char* msg = Lua_ValueToString(L, 2);

	int32_t	nLen = (int32_t)strlen(msg);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (nLen > 0 && pMap->m_QuestBuffer.mUseNum < SQuestBuffer::QUESTBUFLEN)
	{
		Q_strncpyz
		(
			pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf,
			msg,
			SQuestBuffer::QUESTCHARBUFLEN
		);
		pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Str;
	}

	return 0;
}

int32_t LuaFunction_OnNPCClickedQuest(Lua_State* L)
{
	LuaStack args(L);
	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	GUID_t	targetGUID = Lua_ValueToNumber(L, 4);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pSelfObj = (Object*)(pMap->GetSpecificObjByID(selfId));
	Object* pTargetObj = (Object*)(pMap->GetSpecificObjByID(targetId));

	if (pSelfObj && pTargetObj)
	{
		if (pSelfObj->GetObjType() == Object::OBJECT_CLASS_PLAYER &&
			pTargetObj->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			Player* pPlayer = (Player*)pSelfObj;
			Monster* pMonster = (Monster*)pTargetObj;

			if (pPlayer && pMonster && pMonster->GetGUID() == targetGUID)
			{
				QuestManager::GetSingletonPtr()->OnNPCClicked(pPlayer, mapId, targetId, targetGUID);
			}
		}
	}

	return 0;
}

int32_t LuaFunction_GetFrontQuestIdNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	_QUEST_DATA_t* pMisData = QuestManager::GetSingletonPtr()->GetQuestData(misIndex);

	KCheck(pMisData);

	Lua_PushNumber(L, pMisData->nPreQuestID1);
	Lua_PushNumber(L, pMisData->nPreQuestID2);
	Lua_PushNumber(L, pMisData->nPreQuestID3);
	return 3;
}

int32_t LuaFunction_IsQuestHaveDoneNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}


	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	int32_t v = pPlayer->IsQuestHaveDone(misIndex);
	Lua_PushNumber(L, v);

	return 1;

}

int32_t LuaFunction_QuestCheckAcceptNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	char	assetmsg[1024] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DATA_t* pData = QuestManager::GetSingletonPtr()->GetQuestData(misIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sprintf(assetmsg, "表格中没有相关数据%d", misIndex);
	KCheckEx(pData, assetmsg);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	ret = pPlayer->IfCanRecvQuest(pData, targetId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, ret);
	return 1;
}

/*
 添加一个任务按钮，这个函数与LuaFunction_AddQuestText功能完全不同，后者用来添加文本，与之类似的接口是LuaFunction_AddQuestNumText
 */
int32_t LuaFunction_AddQuestTextNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	char	assetmsg[1024] = { 0 };
	int32	state = -1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (args.Count() < 5)
		state = -1;
	else
	{
		if (!args[5].IsNumber())
		{
			LUA_ASSERT(false);
			LUA_RETURNERROR_1;
		}

		state = Lua_ValueToNumber(L, 5);
	}

	/*~~~~~~~~~~~~~~~*/
	int32	index = -1;
	/*~~~~~~~~~~~~~~~*/

	if (args.Count() < 6)
		index = -1;
	else
	{
		if (!args[6].IsNumber())
		{
			LUA_ASSERT(false);
			LUA_RETURNERROR_1;
		}

		index = Lua_ValueToNumber(L, 6);
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;*/

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_QUEST_DATA_t* pData = QuestManager::GetSingletonPtr()->GetQuestData(misIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sprintf(assetmsg, "表格中没有相关数据%d", misIndex);
	KCheckEx(pData, assetmsg);
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32* pNumber = (int32*)
			(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Number * sizeof(int32));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		*pNumber = misIndex;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32* pState = (int32*)
			(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_State * sizeof(int32));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		*pState = state;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32* pIndex = (int32*)
			(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Index * sizeof(int32));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		*pIndex = index;

		Q_strncpyz
		(
			pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Count * sizeof(int32),
			pData->szQuestName,
			SQuestBuffer::QUESTCHARBUFLEN - EA_Count * sizeof(int32)
		);
		pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_IntStr;
	}

	return 0;
}

int32_t LuaFunction_IsHaveQuestNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, pPlayer->IsHaveQuest(misIndex));
	return 1;
}

int32_t LuaFunction_ShowNpcQuestEventList(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object* pSelfObj = (Object*)(pMap->GetSpecificObjByID(selfId));
	Object* pTargetObj = (Object*)(pMap->GetSpecificObjByID(targetId));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pSelfObj && pTargetObj)
	{
		if
			(
				pSelfObj->GetObjType() == Object::OBJECT_CLASS_PLAYER
				&& pTargetObj->GetObjType() == Object::OBJECT_CLASS_MONSTER
				)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster* pMonster = (Monster*)pTargetObj;
			NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
			if (pQuest != NULL)
			{
				for (int i = 0; i < pQuest->m_EventCount; i++)
				{
					luaSystem->RunScriptFunction
					(mapId,
						pQuest->m_EventList[i],
						DEF_PROC_ENUM_EVENT_FN,
						mapId,
						selfId,
						targetId,
						-1
					);
				}

				QuestManager::GetSingletonPtr()->ShowNpcQuestList(pMap, pQuest->m_QuestList, pQuest->m_QuestCount, selfId, targetId);
			}
		}
	}
	return 0;
}

int32_t LuaFunction_GetQuestStateNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t npcId = Lua_ValueToNumber(L, 3);
	int32	nQuestID = Lua_ValueToNumber(L, 4);


	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	int state = QuestManager::GetSingletonPtr()->GetQuestState(pPlayer, nQuestID);
	Lua_PushNumber(L, state);

	return 1;
}

int32_t LuaFunction_BeginUICommand(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	pMap->m_XParam.Clear();

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_EndUICommand(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return 0;
}

int32_t LuaFunction_UICommand_AddInt(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	nValue = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	pMap->m_XParam.AppendIntValue(nValue);


	return 0;
}

int32_t LuaFunction_DispatchUICommand(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	nUIIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	SCCommand* packet = new SCCommand;
	packet->setParam(pMap->m_XParam);
	packet->setUIIndex(nUIIndex);

	//NetManager::GetSingletonPtr()->sendNetMessage(packet);

	return 0;
}

int32_t LuaFunction_IsHaveQuest(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	if (misId == -1)
		Lua_PushNumber(L, 0);
	else
		Lua_PushNumber(L, pPlayer->IsHaveQuest(misId));
	return 1;
}

int32_t LuaFunction_IsQuestHaveDone(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, pPlayer->IsQuestHaveDone(misId));
	return 1;
}

int32_t LuaFunction_AddQuestExpBonus(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Exp;

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus1(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money1;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus2(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money2;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus3(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money3;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus4(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money4;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus5(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money5;
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus6(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money6;

	return 0;
}



int32_t LuaFunction_AddQuestMoneyBonus7(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money7;

	return 0;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddQuestMoneyBonus8(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	count = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = count;
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Money8;

	return 0;
}


template<typename T>
void SetDispatchQuest(T& paramEventList, GameMap* pMap, int32 i)
{
	if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Item)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetItem(number[0], number[1]);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_RandItem)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		/*~~~~~~~~~~~~~~~~~~*/

		bonus.SetItemRand();
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_RadioItem)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetItemRadio(number[0], number[1]);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money1)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney1(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money2)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney2(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money3)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney3(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money4)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney4(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money5)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney5(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money6)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney6(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money7)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney7(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money8)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney8(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Money9)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetMoney9(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Exp)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetExp(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Vigor)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.Set_Property_Vigor(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Charm)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetCharm(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Genius)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetGenius(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_GuildExp)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetGuildExp(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_CountryFood)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetCountryFood(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_CountryMoney)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetCountryMoney(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_CountryWood)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetCountryWood(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_CountryMetal)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetCountryMetal(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_WeiWang)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetWeiWang(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_InherenceExp)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetInherenceExp(*number);
		paramEventList.AddBonus(&bonus);
	}
	else if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_GuildMoney)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SQuestBonus	bonus;
		int32* number = (int32*)(pMap->m_QuestBuffer.Buff[i].buf);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		bonus.SetGuildMoney(*number);
		paramEventList.AddBonus(&bonus);
	}
}

int32 LuaFunction_DispatchQuestContinueInfoNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	ObjID_t		targetId = Lua_ValueToNumber(L, 3);
	ScriptID_t	scriptId = Lua_ValueToNumber(L, 4);
	QuestID_t	misId = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptParam_QuestContinueInfo	paramEventList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	paramEventList.Reset();
	paramEventList.m_idNPC = targetId;
	paramEventList.m_idScript = misId;
	paramEventList.m_idQuest = misId;

	for (int32 i = 0; i < pMap->m_QuestBuffer.mUseNum; i++)
	{
		if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Str)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~*/
			SScriptString	scriptStr;
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			scriptStr = pMap->m_QuestBuffer.Buff[i].buf;
			paramEventList.AddText(&scriptStr);
		}
		else
		{
			SetDispatchQuest(paramEventList, pMap, i);
		}
	}

	pPlayer->SetRuntimeData(RT_EVENT_REQUEST_NPCID, targetId);
	if (misId > 0)
		pPlayer->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, misId);
	else
		pPlayer->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, scriptId);

	SCScriptCommand* packet = new SCScriptCommand;
	packet->setCmdId(SCRIPT_COMMAND_QUEST_CONTINUE_RESPONSE);
	packet->setParam(paramEventList);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet);

	return 0;
}

int32_t LuaFunction_AddQuestItemBonus(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	itemTypeSn = Lua_ValueToNumber(L, 2);
	int32	count = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber++ = itemTypeSn;
	*pNumber = count;

	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_Item;

	return 0;
}

int32 LuaFunction_AddQuestRadioItemBonus(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	itemTypeSn = Lua_ValueToNumber(L, 2);
	int32	count = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber++ = itemTypeSn;
	*pNumber = count;

	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_RadioItem;

	return 0;
}

int32_t LuaFunction_GetQuestIndexByID(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, pPlayer->GetQuestIndexByID(misId));
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetQuestParam(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	int32	paramIndex = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	if (misIndex >= 0)
	{
		int32_t param = pPlayer->GetQuestParam(misIndex, paramIndex);
		Lua_PushNumber(L, param);
		return 1;
	}
	else
	{
		Lua_PushNumber(L, 0);
		return 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetQuestParam(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	questId = Lua_ValueToNumber(L, 3);
	int32	paramIndex = Lua_ValueToNumber(L, 4);
	int32	value = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nIndex = pPlayer->GetQuestIndexByID(questId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nIndex != UINT_MAX)
	{
		pPlayer->SetQuestParam(nIndex, paramIndex, value);
		Lua_PushNumber(L, 1);
		return 1;
	}
	else
	{
		Lua_PushNumber(L, 0);
		return 1;
	}
}

int32_t LuaFunction_AddQuestNumText(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	int32		id = Lua_ValueToNumber(L, 2);
	const char* msg = Lua_ValueToString(L, 3);
	int32		state = -1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 4)
		state = -1;
	else if (FALSE == LuaSystem::IsParamNumber(L, 4, "LuaFunction_AddQuestNumText"))
		LUA_RETURNERROR_1;

	state = Lua_ValueToNumber(L, 4);

	/*~~~~~~~~~~~~~~~*/
	int32	index = -1;
	/*~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 5)
		index = -1;
	else if (FALSE == LuaSystem::IsParamNumber(L, 5, "LuaFunction_AddQuestNumText"))
		LUA_RETURNERROR_1;

	index = Lua_ValueToNumber(L, 5);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	if (pMap->m_QuestBuffer.mUseNum >= SQuestBuffer::QUESTBUFLEN) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pNumber = (int32*)
		(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Number * sizeof(int32));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pNumber = id;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pState = (int32*)
		(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_State * sizeof(int32));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pState = state;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32* pIndex = (int32*)
		(pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Index * sizeof(int32));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pIndex = index;

	Q_strncpyz
	(
		pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum].buf + EA_Count * sizeof(int32),
		msg,
		SQuestBuffer::QUESTCHARBUFLEN - EA_Count * sizeof(int32)
	);
	pMap->m_QuestBuffer.Buff[pMap->m_QuestBuffer.mUseNum++].mType = SQuestBuffer::_QuestItemBuf::BufType_IntStr;

	return 0;
}

int32_t LuaFunction_SetQuestByIndex(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	int32	paramIndex = Lua_ValueToNumber(L, 4);
	int32	value = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	if (misIndex >= 0)
	{
		pPlayer->SetQuestParam(misIndex, paramIndex, value);
		return 0;
	}



	return 0;
}

int32_t LuaFunction_DispatchQuestInfoNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	ObjID_t		targetId = Lua_ValueToNumber(L, 3);
	ScriptID_t	scriptId = Lua_ValueToNumber(L, 4);
	QuestID_t	misId = Lua_ValueToNumber(L, 5);
	int32		bDontShowOK = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) > 5)
	{
		if (FALSE == LuaSystem::IsParamNumber(L, 6, "LuaFunction_DispatchQuestInfoNM"))
		{
			LUA_RETURNERROR_1;
		}

		bDontShowOK = Lua_ValueToNumber(L, 6);
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptParam_QuestInfo	paramEventList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	paramEventList.Reset();
	paramEventList.m_idNPC = targetId;
	paramEventList.m_idQuest = misId;
	paramEventList.m_idScript = misId;
	if (bDontShowOK) paramEventList.SetFlag(1);

	for (int32 i = 0; i < pMap->m_QuestBuffer.mUseNum; i++)
	{
		if (pMap->m_QuestBuffer.Buff[i].mType == SQuestBuffer::_QuestItemBuf::BufType_Str)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~*/
			SScriptString	scriptStr;
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			scriptStr = pMap->m_QuestBuffer.Buff[i].buf;
			paramEventList.AddText(&scriptStr);
		}
		else
		{
			SetDispatchQuest(paramEventList, pMap, i);
		}
	}

	pPlayer->SetRuntimeData(RT_EVENT_REQUEST_NPCID, targetId);
	pPlayer->SetRuntimeData(RT_EVENT_REQUEST_QUEST_SCRIPT_ID, misId);


	SCScriptCommand* packet = new SCScriptCommand;
	packet->setCmdId(SCRIPT_COMMAND_QUEST_RESPONSE);
	packet->setQuestInfo(paramEventList);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet);

	return 0;
}

int32_t LuaFunction_IsQuestFullNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~*/
	int32	nCount = 0;
	/*~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < MAX_CHAR_QUEST_NUM; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const OWN_QUEST* pOwnQuest = pPlayer->GetQuest(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pOwnQuest->IsActiveQuest())
		{
			++nCount;
		}
	}

	if (nCount == MAX_CHAR_QUEST_NUM)
	{
		Lua_PushNumber(L, 1);
	}
	else
	{
		Lua_PushNumber(L, 0);
	}

	return 1;
}


int32_t LuaFunction_AddQuest(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[6].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[7].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	ScriptID_t	scriptId = Lua_ValueToNumber(L, 4);
	BOOL		killObjEvent = Lua_ValueToNumber(L, 5) > 0 ? 1 : 0;
	BOOL		enterAreaEvent = Lua_ValueToNumber(L, 6) > 0 ? 1 : 0;
	BOOL		itemChangedEvent = Lua_ValueToNumber(L, 7) > 0 ? 1 : 0;
	BOOL		npcClickedEvent;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 8)
		npcClickedEvent = FALSE;
	else
	{
		if (FALSE == LuaSystem::IsParamNumber(L, 8, "LuaFunction_AddQuest"))
		{
			LUA_RETURNERROR_1;
		}

		npcClickedEvent = Lua_ValueToNumber(L, 8) > 0 ? TRUE : 0;
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	ret = pPlayer->AddQuest
	(
		misId,
		scriptId,
		killObjEvent,
		enterAreaEvent,
		itemChangedEvent,
		npcClickedEvent
	);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ret = ((ret == OR_OK) ? TRUE : FALSE);

	Lua_PushNumber(L, ret);
	return 1;
}

int32 LuaFunction_BeginAddItem(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	pMap->mItemList.Init();
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddItem(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	itemTypeSn = Lua_ValueToNumber(L, 2);
	int32	count = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	STSerialHelper	help(itemTypeSn);
	SItemType	itemType = help.GetItemTypeStruct();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!itemType.isNull())
	{
		pMap->mItemList.AddType(itemType, count);

		return 0;
	}

	return 0;
}

int32_t LuaFunction_AddBindItem(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	int32	itemTypeSn = Lua_ValueToNumber(L, 2);
	int32	count = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	STSerialHelper	help(itemTypeSn);
	SItemType	itemType = help.GetItemTypeStruct();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!itemType.isNull())
	{
		pMap->mItemList.AddType(itemType, count, 1);

		return 0;
	}
	return 0;
}

int32_t LuaFunction_EndAddItem(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;
	BOOL ret = sItemInterface.CanBagReceiveItemList(pPlayer, pMap->mItemList);
	Lua_PushNumber(L, ret);
	return 1;
}

int32_t LuaFunction_DelQuest(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->DelQuest(misId);

	Lua_PushNumber(L, 1);
	return 1;
}

int32_t LuaFunction_QuestCom(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->SetQuestHaveDone(misId, TRUE);

	return 0;
}

int32_t LuaFunction_DispatchQuestTips(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptParam_QuestTips	paramQuestTips;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	paramQuestTips.Reset();
	if (pMap->m_QuestBuffer.Buff[0].mType == SQuestBuffer::_QuestItemBuf::BufType_Str)
	{
		paramQuestTips.m_strText = pMap->m_QuestBuffer.Buff[0].buf;
	}

	SCScriptCommand* packet = new SCScriptCommand;
	packet->setCmdId(SCRIPT_COMMAND_QUEST_TIPS);
	packet->setQuestTips(paramQuestTips);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	return 0;
}

int32_t LuaFunction_AddItemListToPlayer(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = sItemInterface.ReceiveBagItemList(nullptr, pPlayer, pMap->mItemList);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return 0;
}

int32 LuaFunction_GetNeedItemNumNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	int32	itemId = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	return QuestManager::GetSingletonPtr()->GetNeedItemNum(misIndex, L, itemId);

}

int32 LuaFunction_QuestCheckSubmitNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	int32	misOjbIndex = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, QuestManager::GetSingletonPtr()->QuestCheckSubmit(pPlayer, misIndex, targetId, misOjbIndex));
	return 1;
}

int32_t LuaFunction_QuestComplateNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	int32	selId = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, QuestManager::GetSingletonPtr()->QuestComplate(pPlayer, pMap, misIndex, targetId, selId));
	return 1;

}

int32 LuaFunction_QuestBonusNotItemNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	QuestManager::GetSingletonPtr()->QuestBonusNotItem(pPlayer, pMap, misIndex, LuaSystem::GetScriptStepId(L));

	return 0;
}

int32 LuaFunction_QuestBonusItemNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	misIndex = Lua_ValueToNumber(L, 3);
	int32	selId = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	Lua_PushNumber(L, QuestManager::GetSingletonPtr()->QuestBonusItem(pPlayer, pMap, misIndex, selId));

	return 0;
}

int32_t LuaFunction_PushAfterQuestNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	CSQuestAccept msg;
	msg.setPlayerId(selfId);
	msg.setMapId(mapId);
	msg.setTargetId(targetId);
	msg.setIdScript(misIndex);
	msg.process();
	Lua_PushNumber(L, 1);
	return 1;
}

int32_t LuaFunction_IsNpcHaveQuestNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object* pTargetObj = (Object*)(pMap->GetSpecificObjByID(targetId));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pTargetObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster* pMonster = (Monster*)pTargetObj;
	NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pQuest)
	{
		LUA_RETURNERROR_1;
	}

	for (int i = 0; i < pQuest->m_QuestCount; i++)
	{
		if (pQuest->m_QuestList[i] == misIndex)
		{
			Lua_PushNumber(L, 1);
			return 1;
		}
	}

	LUA_RETURNERROR_1;
}

int32_t LuaFunction_AddDispatchQuestInfoNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	misIndex = Lua_ValueToNumber(L, 4);
	int32	state = -1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 5)
	{
		state = -1;
	}
	else
	{
		if (FALSE == LuaSystem::IsParamNumber(L, 5, "LuaFunction_AddDispatchQuestInfoNM"))
		{
			LUA_RETURNERROR_1;
		}

		state = Lua_ValueToNumber(L, 5);
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	QuestManager::GetSingletonPtr()->AddDispatchQuestInfo(pPlayer, misIndex, targetId, state);

	return 0;
}

int32_t LuaFunction_SetQuestEvent(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	QuestID_t	misId = Lua_ValueToNumber(L, 3);
	int32		eventId = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32_t	ret = pPlayer->SetQuestEvent(misId, eventId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ret = ((ret == OR_OK) ? TRUE : FALSE);

	Lua_PushNumber(L, ret);
	return 1;
}

int32_t LuaFunction_GetMonsterOwnerCount(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t MonsterID = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(MonsterID);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		LUA_RETURNERROR_1;
	}

	Monster* pMonster = (Monster*)pObj;

	Lua_PushNumber(L, pMonster->GetOwnerList().OwnerCount);
	return 1;
}

int32_t LuaFunction_GetMonsterOwnerID(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t MonsterID = Lua_ValueToNumber(L, 2);
	uint32	OwnerOffSet = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Monster* pMonster = pMap->getMonster(MonsterID);

	if (pMonster == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	KCheck(OwnerOffSet < pMonster->GetOwnerList().OwnerCount);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player* _pHuman = pMap->getPlayer(pMonster->GetOwnerList().OwnerDropList[OwnerOffSet].m_ObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (_pHuman)
	{
		Lua_PushNumber(L, pMonster->GetOwnerList().OwnerDropList[OwnerOffSet].m_ObjID);
		return 1;
	}

	Lua_PushNumber(L, -1);
	return 1;
}

int32_t LuaFunction_GetItemIdInItemBoxNM(Lua_State* L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	ObjID_t targetId = Lua_ValueToNumber(L, 3);
	int32	gpType = Lua_ValueToNumber(L, 4);
	int32	itemId = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);

	return QuestManager::GetSingletonPtr()->GetItemIdInItemBox(L, gpType, pPlayer, itemId);

	return 3;
}