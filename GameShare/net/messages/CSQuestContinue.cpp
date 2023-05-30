#include "stdafx.h"
#include "CSQuestContinue.h"
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

CSQuestContinue::CSQuestContinue() :
	NetPacket(CS_QUEST_CONTINUE)
{

}

CSQuestContinue::~CSQuestContinue()
{

}

bool CSQuestContinue::process()
{
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	pObj = pMap->GetSpecificObjByID(mTargetId);

	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		return false;
	}

	Monster* pMonster = (Monster*)pObj;

	bool	bVerifyEvent = false;

	NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());

	if (pQuest)
	{
		for (int32 i = 0; i < pQuest->m_EventCount; i++)
		{
			if (pQuest->m_EventList[i] == mIdScript)
			{
				// 如果绑定了脚本
				bVerifyEvent = true;
				break;
			}
		}
	}

	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	if (bVerifyEvent)
	{
		if (mIdScript <= 0)
			return true;

		// 调用绑定的脚本
		luaSystem->RunScriptFunction(mMapId, mIdScript,
			"OnContinue", mMapId, mPlayerId, mTargetId);
	}
	else
	{
		if (mIdScript <= 0)
			return true;

		luaSystem->RunScriptFunction(mMapId, mIdScript,
			"OnContinue", mMapId, mPlayerId);
	}

	return true;
}

void CSQuestContinue::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void CSQuestContinue::setMapId(int32_t mapId)
{
	mMapId = mapId;
}

void CSQuestContinue::setTargetId(int32_t objId)
{
	mTargetId = objId;
}

void CSQuestContinue::setIdScript(int32_t idScript)
{
	mIdScript = idScript;
}