#include "stdafx.h"
#include "CSEventRequest.h"


#include "ScriptDef.h"
//#include "script/LuaSystem.h"
//#include "server_manager.h"
//#include "map/game_map.h"
//#include "gameobject/Player.h"
//#include "item/ItemInstance.h"
//#include "map/map_manager.h"
//#include "gameobject/ObjectManager.h"
//#include "gameobject/Monster.h"
//#include "item/Item_Interface.h"
//#include "data/data_manager.h"
//#include "Share/tab/TabDefine_Map_Quest.h"

CSEventRequest::CSEventRequest():
	NetPacket(CS_EVENT_REQUEST)
{

}

CSEventRequest::~CSEventRequest()
{

}

bool CSEventRequest::process()
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

	//ScriptID_t idScript = midScript;

	//int32_t	bVerifyEvent = 0;
	//NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if (pQuest)
	//{
	//	for (int32 i = 0; i < pQuest->m_EventCount; i++)
	//	{
	//		if (pQuest->m_EventList[i] == idScript)
	//		{
	//			bVerifyEvent = 1;
	//			break;
	//		}
	//	}

	//	if (bVerifyEvent == 0)
	//	{
	//		for (int32 i = 0; i < pQuest->m_QuestCount; i++)
	//		{
	//			if (pQuest->m_QuestList[i] == idScript)
	//			{
	//				bVerifyEvent = 2;
	//				break;
	//			}
	//		}
	//	}
	//}

	//LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	//if (bVerifyEvent == 1)
	//{
	//	luaSystem->RunScriptFunction
	//	(
	//		mMapId,
	//		midScript,
	//		DEF_PROC_EVENT_ENTRY_FN,
	//		mMapId,
	//		mPlayerId,
	//		mTargetId,
	//		midScript,
	//		mExindex
	//	);

	//	return OR_OK;
	//}
	//else if (bVerifyEvent == 2 || bVerifyEvent == 0)
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	_QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(midScript);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if (pData)
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		BOOL	bRunByScript = FALSE;
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if (pData->nScriptID >= 100000)
	//		{
	//			luaSystem->RunScriptFunction
	//			(
	//				mMapId,
	//				pData->nScriptID,
	//				DEF_PROC_EVENT_ENTRY_FN,
	//				mMapId,
	//				mPlayerId,
	//				mTargetId,
	//				midScript,
	//				mExindex
	//			);
	//			bRunByScript = TRUE;
	//		}

	//		if (bRunByScript == FALSE)
	//		{
	//			luaSystem->RunScriptFunction
	//			(
	//				mMapId,
	//				QUEST_SCRIPTID,
	//				DEF_PROC_EVENT_ENTRY_FN,
	//				mMapId,
	//				mPlayerId,
	//				mTargetId,
	//				midScript,
	//				mExindex
	//			);
	//		}
	//	}

	//	return OR_OK;
	//}

	return true;
}

void CSEventRequest::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void CSEventRequest::setMapId(int32_t mapId)
{
	mMapId = mapId;
}

void CSEventRequest::setidExIndex(int32_t exIndex)
{
	mExindex = exIndex;
}

void CSEventRequest::setidScript(int32_t idScript)
{
	midScript = idScript;
}

void CSEventRequest::setTargetId(int32_t targetId)
{
	mTargetId = targetId;
}
