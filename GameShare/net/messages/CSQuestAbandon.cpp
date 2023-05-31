#include "stdafx.h"
#include "CSQuestAbandon.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "map/game_map.h"
#include "gameobject/Player.h"
#include "item/ItemInstance.h"
#include "map/map_manager.h"
#include "gameobject/ObjectManager.h"
#include "gameobject/Monster.h"
#include "item/Item_Interface.h"
#include "data/data_manager.h"
#include "Share/tab/TabDefine_Map_Quest.h"

CSQuestAbandon::CSQuestAbandon() :
	NetPacket(CS_QUEST_ABANDON)
{

}

CSQuestAbandon::~CSQuestAbandon()
{

}

bool CSQuestAbandon::process()
{
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	if (mIdScript >= 100000)
	{
		luaSystem->RunScriptFunction
		(
			mMapId,
			mIdScript,
			DEF_PROC_QUEST_ABANDON_FN,
			mMapId,
			mPlayerId,
			-1
		);
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(mIdScript);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pData)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRunByScript = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (pData->nScriptID >= 100000)
			{
				
				{
					luaSystem->RunScriptFunction
					(
						mMapId,
						pData->nScriptID,
						DEF_PROC_QUEST_ABANDON_FN,
						mMapId,
						mPlayerId,
						mIdScript
					);
					bRunByScript = TRUE;
				}
			}

			if (bRunByScript == FALSE)
			{
				luaSystem->RunScriptFunction
				(
					mMapId,
					QUEST_SCRIPTID,
					DEF_PROC_QUEST_ABANDON_FN,
					mMapId,
					mPlayerId,
					mIdScript
				);
			}
		}
	}
	return true;
}

void CSQuestAbandon::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void CSQuestAbandon::setMapId(int32_t mapId)
{
	mMapId = mapId;
}

void CSQuestAbandon::setTargetId(int32_t objId)
{
	mTargetId = objId;
}

void CSQuestAbandon::setIdScript(int32_t idScript)
{
	mIdScript = idScript;
}