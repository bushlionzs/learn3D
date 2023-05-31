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
#include "gameobject/Behavior_Player.h"
#include "item/Item_Interface.h"
#include "Archive/PlayerDB.h"

int32_t LuaFunction_GetLevel(Lua_State *L)
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

	Lua_PushNumber(L, pPlayer->GetLevel());
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetLevel(Lua_State *L)
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
	int32	level = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	KCheckEx(level > 0 && level <= DEFAULT_WASHPOINT_LEVEL, "level wrong");
	if(level <= 0 || level > DEFAULT_WASHPOINT_LEVEL)
	{
		LUA_RETURNERROR_1;
	}


	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->SetLevel(level);

	Lua_PushNumber(L, 1);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_CanLevelUp(Lua_State *L)
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

	/*if(pPlayer->GetPlayerExp() >= g_LevelupExpTab.Get(pPlayer->GetLevel() - 1))
	{
		Lua_PushNumber(L, TRUE);
	}
	else
	{
		Lua_PushNumber(L, FALSE);
	}*/
	Lua_PushNumber(L, FALSE);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetItemTableIndexByIndex(Lua_State *L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	uint32	itemIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = sItemInterface.GetBagItem(pPlayer, itemIndex);
	if( !pItem )
	{
		LUA_RETURNERROR_1;
	}
	else
	{
		int32	itemType = pItem->GetItemTableIndex();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Lua_PushNumber(L, itemType);
		return 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetItemCountInBagPos(Lua_State *L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	uint32	uBagPos = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = sItemInterface.GetBagItem(pPlayer, uBagPos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItem != NULL)
	{
		Lua_PushNumber(L, pItem->GetLayedNum());
		return 1;
	}

	return 0;
}

int32_t LuaFunction_GetZhiye(Lua_State* L)
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

	Lua_PushNumber(L, pPlayer->GetProfession());
	return 1;
}

int32_t LuaFunction_AddExp(Lua_State* L)
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
	uint64	exp = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->SetAlterPlayerExp(exp);
	return 0;
}

int32_t LuaFunction_AddMoney(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	argc = Lua_GetTopIndex(L);
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	uchar	moneyType = Lua_ValueToNumber(L, 3);
	int32	profit = Lua_ValueToNumber(L, 4);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (argc == 5)
	{
		if (!args[5].IsNumber())
		{
			LUA_ASSERT(false);
			LUA_RETURNERROR_1;
		}
	}


	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	if (profit < 0)
	{
		Lua_PushNumber(L, -1);
		return 1;
	}


	switch (moneyType)
	{
	case CU_SILLER: { pPlayer->IncreaseMoney(CU_SILLER, profit); }break;
	case CU_BINDSILLER: { pPlayer->IncreaseMoney(CU_BINDSILLER, profit); }break;
	case CU_BINDGOLD: { pPlayer->IncreaseMoney(CU_BINDGOLD, profit); }break;
	default: { Lua_PushNumber(L, -1); return 1; }
	}

	Lua_PushNumber(L, 1);
	return 1;

}

int32_t LuaFunction_GetRongYu(Lua_State* L)
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

	Lua_PushNumber(L, pPlayer->GetRongYu());
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetRongYu(Lua_State* L)
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
	int32	valud = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->SetRongYu(valud);

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetShengWang(Lua_State* L)
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

	Lua_PushNumber(L, pPlayer->GetShengWang());
	return 1;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetShengWang(Lua_State* L)
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
	int32	valud = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	pPlayer->SetShengWang(valud);

	return 0;
}

int32_t LuaFunction_GetItemCount(Lua_State* L)
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
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	itemTypeSn = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Object* pObj = pMap->GetSpecificObjByID(selfId);

	if (pObj == nullptr || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		LUA_RETURNERROR_1;
	}
	Player* pPlayer = (Player*)pObj;

	/*~~~~~~~~~~~~~~*/
	int32	count = 0;
	/*~~~~~~~~~~~~~~*/

	count = sItemInterface.CalcEquipItemCount(pPlayer, itemTypeSn);

	count += sItemInterface.CalcInventoryItemCount(pPlayer, itemTypeSn);

	Lua_PushNumber(L, count);
	return 1;
}

int32_t LuaFunction_HaveItem(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	itemTypeSn = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	
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

	for (int32 i = 0; i < HEQUIP_NUMBER; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pItem = sItemInterface.GetEquip(pPlayer, (PLAYER_EQUIP)i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pItem == NULL) continue;
		if (!pItem->IsFree())
		{
			if (pItem->GetItemTableIndex() == itemTypeSn)
			{
				++nCount;
			}
		}
	}

	nCount += sItemInterface.CalcInventoryItemCount(pPlayer, itemTypeSn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer* pContainer = pPlayer->GetBankContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);
	for (int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pItem = pContainer->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if (!pItem->IsFree())
		{
			if (pItem->GetItemTableIndex() == itemTypeSn)
			{
				nCount += pItem->GetLayedNum();
			}
		}
	}

	if (nCount > 0)
	{
		Lua_PushNumber(L, nCount);
		return 1;
	}

	Lua_PushNumber(L, -1);
	return 1;
}

int32 LuaFunction_AddSkill(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	skillId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Player* pPlayer = pMap->getPlayer(selfId);

	if (pPlayer == nullptr)
	{
		Lua_PushNumber(L, -1);
		return 1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = pPlayer->SpellModify(skillId, 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, bRet);

	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaFunction_DelSkill(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	skillId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Player* pPlayer = pMap->getPlayer(selfId);

	if (pPlayer == nullptr)
	{
		Lua_PushNumber(L, -1);
		return 1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = pPlayer->SpellModify(skillId, -1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, bRet);

	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaFunction_HaveSkill(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	skillId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);

	Player* pPlayer = pMap->getPlayer(selfId);

	if (pPlayer == nullptr)
	{
		Lua_PushNumber(L, -1);
		return 1;
	}
	PlayerArchive* pPA = pPlayer->GetDB();
	if (pPA == NULL)
	{
		Lua_PushNumber(L, -1);
		return 1;
	}

	//遍历技能列表
	int nSpellCount = pPA->GetSkillCount();
	for (int i = 0; i < nSpellCount; ++i)
	{
		_PLAYER_SPELL& ps = pPA->GetSkillID((uchar)i);
		if (ps.m_eState == _PLAYER_SPELL::OWN_SKILL_CAN_USE && ps.m_nSkillID == skillId)
		{
			Lua_PushNumber(L, 1);
			return 1;
		}
	}

	Lua_PushNumber(L, -1);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 LuaFunction_UseSkill(Lua_State* L)
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	skillId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	Behavior_Player* pHumanAI = (Behavior_Player*)pPlayer->GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pHumanAI->PushCmd_UseSpell
	(
		skillId,
		INVALID_ID,
		pPlayer->GetGLPos()->m_fX,
		pPlayer->GetGLPos()->m_fZ,
		pPlayer->GetDir(),
		INVALID_ID,
		0
	);

	Lua_PushNumber(L, TRUE);

	return 1;
}


int32_t LuaFunction_DelItem(Lua_State* L)
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

	if (!args[4].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	uint32	itemIndex = Lua_ValueToNumber(L, 3);
	int32	delCount = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}


	if (sItemInterface.EraseBagItemByIndex(nullptr, pPlayer, itemIndex, delCount) == TRUE)
	{
		Lua_PushNumber(L, 1);
		return 1;
	}
	else
	{
		Lua_PushNumber(L, 0);
		return 1;
	}
}