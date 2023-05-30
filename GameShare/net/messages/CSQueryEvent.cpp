#include "stdafx.h"
#include "CSQueryEvent.h"
#include "server/server_manager.h"
#include "server/script/LuaSystem.h"
#include "Share/Core/ScriptDef.h"
#include "server/map/game_map.h"
#include "server/gameobject/Player.h"
#include "server/item/ItemInstance.h"
#include "server/map/map_manager.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Monster.h"
#include "server/item/Item_Interface.h"
#include "server/data/data_manager.h"
#include "Share/tab/TabDefine_Map_Quest.h"

CSQueryEvent::CSQueryEvent():
	NetPacket(CS_QUERY_EVENT)
{

}

CSQueryEvent::~CSQueryEvent()
{

}

bool CSQueryEvent::process()
{
	//LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	//luaSystem->RunScriptFunction(mMapId, SCENE_SCRIPTID, DEF_PROC_MAP_NPCDEFAULTQUESTEVENTLIST_FN);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	pObj = pMap->GetSpecificObjByID(mObjectId);

	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		return false;
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
				luaSystem->RunScriptFunction(mMapId,
					SCENE_SCRIPTID,
					DEF_PROC_MAP_NPCDEFAULTDIALOG_FN,
					mMapId,
					mPlayerId,
					mObjectId,
					guid
				);
			}
			else
			{
				luaSystem->RunScriptFunction(mMapId,
					SCENE_SCRIPTID,
					DEF_PROC_MAP_NPCDEFAULTQUESTEVENTLIST_FN,
					mMapId,
					mPlayerId,
					mObjectId,
					guid
				);
			}
		}

		return true;
	}
	else
	{
		
		luaSystem->RunScriptFunction(mMapId, idScript, DEF_PROC_EVENT_ENTRY_FN,
			(int32)mMapId,
			(int32)mPlayerId,
			(int32)mObjectId);
	}

	return true;
}

void CSQueryEvent::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void CSQueryEvent::setMapId(int32_t mapId)
{
	mMapId = mapId;
}

void CSQueryEvent::setObjectId(int32_t id)
{
	mObjectId = id;
}

uint32_t CSQueryEvent::getObjectID()
{
	return mObjectId;
}