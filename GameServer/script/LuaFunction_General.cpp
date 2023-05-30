#include "stdafx.h"
#include "LuaFunction_General.h"
#include "LuaFunction_Quest.h"
#include "basetool.h"
#include "LuaSystem.h"
#include "LuaMacro.h"
#include "StructCommandScript.h"
#include "net/messages/SCQueryEventResult.h"
#include "net/net_message_manager.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "gameobject/Monster.h"
#include "quest/quest_manager.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "net/messages/SCChat.h"


int32 LuaFunction_GetMonsterDataID(Lua_State* L)
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

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		LUA_RETURNERROR_1;
	}
	Monster* pMonster = (Monster*)pObj;

	Lua_PushNumber(L, pMonster->GetDataID());
	return 1;
}

int32_t LuaFunction_Msg2Player(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	char* msg = const_cast<char*>(Lua_ValueToString(L, 3));
	int32	Size = (int32)strlen(msg);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(Size < MAX_CHAT_SIZE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	eCHAT_TYPE	type = CHAT_TYPE_NEAR;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 4)
		type = CHAT_TYPE_NEAR;
	else
	{
		if (FALSE == LuaSystem::IsParamNumber(L, 4, "LuaFunction_Msg2Player"))
		{
			LUA_RETURNERROR_1;
		}

		type = (eCHAT_TYPE)((int32)(Lua_ValueToNumber(L, 4)));
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ENUM_SYSTEM_CHAR_SHOW_POS	ShowPos = CHAT_MAIN_WINDOW;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 5)
	{
		ShowPos = CHAT_MAIN_WINDOW;
	}
	else
	{
		if (FALSE == LuaSystem::IsParamNumber(L, 5, "LuaFunction_Msg2Player"))
		{
			LUA_RETURNERROR_1;
		}

		ShowPos = (ENUM_SYSTEM_CHAR_SHOW_POS)((int32)(Lua_ValueToNumber(L, 5)));
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	switch (type)
	{
	default:
	{
		SCChat* packet = new SCChat;
		packet->setChatType(type);
		packet->setChatMsg(msg);
		packet->setChatShowPos(ShowPos);
		NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}
	break;
	}

	Lua_PushNumber(L, 1);
	return 1;
}
