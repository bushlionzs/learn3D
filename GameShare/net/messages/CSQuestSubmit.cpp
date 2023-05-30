#include "stdafx.h"
#include "CSQuestSubmit.h"
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

CSQuestSubmit::CSQuestSubmit()
    :NetPacket(CS_QUEST_SUBMIT)
{

}

CSQuestSubmit::~CSQuestSubmit()
{

}

bool CSQuestSubmit::process()
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

	const SArchiveLoader_Quest* quest = pPlayer->GetQuestList();

	quest->m_Count;

	Monster* pMonster = (Monster*)pObj;

	NPC_QUEST* pQuest = DataManager::GetSingletonPtr()->getNpcQuest(pMonster->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	int32_t	bVerifyEvent = 0;

	if (pQuest)
	{
		for (int32 i = 0; i < pQuest->m_EventCount; i++)
		{
			if (pQuest->m_EventList[i] == mScriptId)
			{
				bVerifyEvent = 1;
				break;
			}
		}

		if (bVerifyEvent == 0)
		{
			for (int32 i = 0; i < pQuest->m_QuestCount; i++)
			{
				if (pQuest->m_QuestList[i] == mScriptId)
				{
					bVerifyEvent = 2;
					break;
				}
			}
		}
	}

	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	if (bVerifyEvent == 1)
	{
		if (mScriptId <= 0)
			return OR_OK;

		luaSystem->RunScriptFunction
		(
			mMapId,
			mScriptId,
			DEF_PROC_QUEST_SUBMIT_FN,
			mMapId,
			mPlayerId,
			mTargetId,
			mRadioId,
			-1
		);
		return OR_OK;
	}
	else if (bVerifyEvent == 2 || bVerifyEvent == 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_QUEST_DATA_t* pData = DataManager::GetSingletonPtr()->getQuestByID(mScriptId);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pData)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRunByScript = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (pData->nScriptID >= 100000)
			{
				luaSystem->RunScriptFunction
					(
						mMapId,
						pData->nScriptID,
						DEF_PROC_QUEST_SUBMIT_FN,
						mMapId,
						mPlayerId,
						mTargetId,
						mRadioId,
						mScriptId
					);
					bRunByScript = TRUE;

			}

			if (bRunByScript == FALSE)
			{
				luaSystem->RunScriptFunction
				(
					mMapId,
					QUEST_SCRIPTID,
					DEF_PROC_QUEST_SUBMIT_FN,
					mMapId,
					mPlayerId,
					mTargetId,
					mRadioId,
					mScriptId
				);
			}

			return OR_OK;
		}
	}

    return true;
}

void CSQuestSubmit::setPlayerId(int32_t playerId)
{
    mPlayerId = playerId;
}

void CSQuestSubmit::setMapId(int32_t mapId)
{
    mMapId = mapId;
}

void CSQuestSubmit::setScriptId(int32_t scriptId)
{
    mScriptId = scriptId;
}

void CSQuestSubmit::setTargetId(int32_t targetId)
{
    mTargetId = targetId;
}

void CSQuestSubmit::setSelectRadioId(int32_t radioId)
{
    mRadioId = radioId;
}
