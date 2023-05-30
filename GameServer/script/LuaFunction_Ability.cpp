#include "stdafx.h"
#include "LuaFunction.h"
#include "LuaMacro.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "gameobject/Monster.h"
#include "gameobject/Behavior_Player.h"
#include "item/Item_Interface.h"
#include "Archive/PlayerDB.h"
#include "map/game_map.h"
#include "item/ItemBoxManager.h"
#include "item/ItemBox.h"




int32 LuaFunction_ItemBoxEnterScene(Lua_State* L)
{


	/*~~~~~~~~~~~~~~~~*/
	GLPos	pos;
	/*~~~~~~~~~~~~~~~~*/

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

	pos.m_fX = Lua_ValueToNumber(L, 1);
	pos.m_fZ = Lua_ValueToNumber(L, 2);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iBoxType = Lua_ValueToNumber(L, 3);
	MapID_t mapId = Lua_ValueToNumber(L, 4);
	int32	iBoxItemCount = Lua_ValueToNumber(L, 5);
	int32	iItemType = Lua_ValueToNumber(L, 6);
	int32	iCycleTime;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Lua_GetTopIndex(L) < 7)
		iCycleTime = 3600000000;
	else
	{
		if (!args[7].IsNumber())
		{
			LUA_ASSERT(false);
			LUA_RETURNERROR_1;
		}

		iCycleTime = Lua_ValueToNumber(L, 7);
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemBox* pIB = pMap->GetItemBoxManager()->CreateGatherPointItemBox(iBoxType, iCycleTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pIB)
	{
		pMap->ObjectEnterMap(pIB);
		pIB->SetGLPos(&pos);
		pIB->SetActiveFlag(TRUE);
		Lua_PushNumber(L, pIB->GetID());
		return 1;
	}
	else
	{
		LUA_RETURNERROR_1;
	}
}