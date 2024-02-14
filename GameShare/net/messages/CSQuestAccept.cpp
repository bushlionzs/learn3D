#include "stdafx.h"
#include "CSQuestAccept.h"

#include "ScriptDef.h"
//#include "map/game_map.h"
//#include "gameobject/Player.h"
//#include "item/ItemInstance.h"
//#include "map/map_manager.h"
//#include "gameobject/ObjectManager.h"
//#include "gameobject/Monster.h"
//#include "item/Item_Interface.h"
//#include "data/data_manager.h"
//#include "Share/tab/TabDefine_Map_Quest.h"
//#include "server_manager.h"
//#include "script/LuaSystem.h"

CSQuestAccept::CSQuestAccept() :
	NetPacket(CS_QUEST_ACCEPT)
{

}

CSQuestAccept::~CSQuestAccept()
{

}

bool CSQuestAccept::process()
{
	//GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	//Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	//if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	//{
	//	return false;
	//}

	//Player* pPlayer = (Player*)pObj;

	//pObj = pMap->GetSpecificObjByID(mTargetId);

	//if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	//{
	//	return false;
	//}

	//Monster* pMonster = (Monster*)pObj;

	//_QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(mIdScript);

	//if (pData)
	//{
	//	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	//	BOOL ret = luaSystem->RunScriptFunction(mMapId,
	//		SCENE_SCRIPTID,
	//		DEF_PROC_MAP_ACCEPTQUESTCHECK_FN,
	//		mMapId,
	//		mPlayerId,
	//		mIdScript
	//	);
	//	if (!ret)
	//	{
	//		return false;
	//	}

	//	if (pData->nScriptID >= 100000)
	//	{
	//		// 如果该任务有脚本
	//		BOOL		bRunByScript = FALSE;

	//		{
	//			luaSystem->RunScriptFunction
	//			(
	//				mMapId,
	//				pData->nScriptID,
	//				DEF_PROC_QUEST_ACCEPT_FN,
	//				mMapId,
	//				mPlayerId,
	//				mTargetId,
	//				mIdScript
	//			);
	//			bRunByScript = TRUE;
	//		}

	//		if (bRunByScript == FALSE)
	//		{
	//			luaSystem->RunScriptFunction
	//			(
	//				mMapId,
	//				pData->nScriptID,
	//				DEF_PROC_QUEST_ACCEPT_FN,
	//				mMapId,
	//				mPlayerId,
	//				mTargetId,
	//				mIdScript
	//			);
	//		}

	//		return OR_OK;
	//	}
	//	else
	//	{
	//		luaSystem->RunScriptFunction
	//		(
	//			mMapId,
	//			QUEST_SCRIPTID,
	//			DEF_PROC_QUEST_ACCEPT_FN,
	//			mMapId,
	//			mPlayerId,
	//			mTargetId,
	//			mIdScript
	//		);

	//		return OR_OK;
	//	}
	//}
	return true;
}

void CSQuestAccept::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void CSQuestAccept::setMapId(int32_t mapId)
{
	mMapId = mapId;
}

void CSQuestAccept::setTargetId(int32_t objId)
{
	mTargetId = objId;
}

void CSQuestAccept::setIdScript(int32_t idScript)
{
	mIdScript = idScript;
}