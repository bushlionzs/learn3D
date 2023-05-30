/*$T MapServer/Server/Script/LuaFunction_Attr.cpp GC 1.140 10/10/07 10:07:47 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "LuaFunction.h"
#include "LuaMacro.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "gameobject/Monster.h"
#include "item/Item_Interface.h"
#include "gameobject/Beastie.h"
#include "Archive/PlayerDB.h"
#include "horse/HorseManager.h"


int32_t LuaFunction_GetHorseCount(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCount = pPlayer->GetHorseCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, iCount);
	return 1;
}

int32_t LuaFunction_GetHorseLevel(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	iIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	KCheck(iIndex >= 0 && iIndex < PLAYER_PET_MAX_COUNT);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB* pHorseDB = pPlayer->GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pHorseDB)
	{
		LUA_RETURNERROR_1;
	}

	Lua_PushNumber(L, pHorseDB->m_nLevel);

	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetHorseTakeLevel(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	iIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	KCheck(iIndex >= 0 && iIndex < PLAYER_PET_MAX_COUNT);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB* pHorseDB = pPlayer->GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pHorseDB)
	{
		LUA_RETURNERROR_1;
	}

	Lua_PushNumber(L, pHorseDB->m_nTakeLevel);

	return 1;
}

int32_t LuaFunction_GetBeastieItem(Lua_State* L)
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
	ObjID_t beastieId = Lua_ValueToNumber(L, 3);
	int32	itemDataId = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object* pObj = pMap->GetSpecificObjByID(beastieId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pObj || pObj->GetObjType() != Object::OBJECT_CLASS_BEASTIE || !((Character*)pObj)->IsAlive())
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Beastie* pBeastie = (Beastie*)pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pBeastie)
	{
		KCheck(NULL && "Player::CaptureBeastie...pBeastie=NULL...");
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	ret = pBeastie->GetBeastieItem(itemDataId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, ret);
	return 1;
}


int32 LuaFunction_IsHaveHorse(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	iHorseTypeId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB_LIST_LOAD* pPetList = pPlayer->GetDB()->m_dbPetList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		if (pPetList->m_aPetDB[i].m_GUID.IsNull())
		{
			continue;
		}

		if (iHorseTypeId == pPetList->m_aPetDB[i].m_nDataID)
		{
			Lua_PushNumber(L, TRUE);
			return 1;
		}
	}

	Lua_PushNumber(L, FALSE);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_IsHaveMount(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	iHorseTypeId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseGuid	guidPet = pPlayer->GetGUIDOfCallUpHorse();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (guidPet.IsNull())
	{
		Lua_PushNumber(L, FALSE);
		return 1;
	}

	if (INVALID_ID == iHorseTypeId)
	{
		Lua_PushNumber(L, TRUE);
		return 1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item* pPetItem = pPlayer->GetHorseItem(guidPet);
	BOOL	iResult = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pPetItem->GetDataID() == iHorseTypeId)
	{
		iResult = TRUE;
	}

	Lua_PushNumber(L, iResult);
	return 1;
}

int32_t LuaFunction_CreateHorseToPlayer(Lua_State* L)
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
	int32	iDataIndex = Lua_ValueToNumber(L, 3);
	int32	iBagIndex = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	_HORSE_DB			oPetDB;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pMap->GetHorseManager()->InitHorseDB(&oPetDB, iDataIndex))
	{
		LUA_RETURNERROR_1;
	};
	pMap->GetHorseManager()->InitHorseGUID(oPetDB.m_GUID, pPlayer);
	if (!pPlayer->AddHorseToHuman(&oPetDB, nullptr))
	{
		LUA_RETURNERROR_1;
	}

	if (INVALID_ID != iBagIndex)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	ret = FALSE;
		Item* pItem = sItemInterface.GetBagItem(pPlayer, iBagIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pItem == NULL)
		{
			Lua_PushNumber(L, FALSE);
			return 1;
		}

		if (pItem->IsFree())
		{
			Lua_PushNumber(L, FALSE);
			return 1;
		}

		if (pItem->IsCanLay())
		{
			ret = sItemInterface.DecBagItemLayCount(nullptr, pPlayer, iBagIndex, 1);
			if (!ret)
			{
				Lua_PushNumber(L, FALSE);
				return 1;
			}
		}
		else
		{
			ret = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, iBagIndex);
			if (!ret)
			{
				Lua_PushNumber(L, FALSE);
				return 1;
			}
		}
	}
	Lua_PushNumber(L, TRUE);
	return 1;
}

