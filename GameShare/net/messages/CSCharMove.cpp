#include "stdafx.h"
#include "CSCharMove.h"
#include "server/server_manager.h"
#include "server/map/map_manager.h"
#include "server/map/game_map.h"
#include "server/map/map_info.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Player.h"
#include "server/gameobject/Behavior_Player.h"

CSCharMove::CSCharMove():
	NetPacket(CS_CHAR_MOVE)
{

}

CSCharMove::~CSCharMove()
{

}

bool CSCharMove::process()
{
	GameMap* pScene = MapManager::GetSingletonPtr()->getMap(mMapID);
	if (NULL == pScene)
	{
		return false;
	}

	if (!pScene->GetMapInfo()->IsCanGo(mTargetPos))
	{
		return false;
	}

	ObjectManager* objectManager = pScene->GetObjManager();
	Object* pObj = objectManager->GetObj(mObjectId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	OPT_RESULT oResult = pPlayer->GetHumanAI()->PushCmd_Move
	(
		mHandleID,
		1,
		&mTargetPos,
		mStopLogicCount,
		&mWorldPos,
		mObjectId
	);

	printf("move to:x:%.2f,z:%.2f\n", mTargetPos.m_fX, mTargetPos.m_fZ);


	if (ORT_FAILED(oResult))
	{
		int kk = 0;
	}

	
	return true;
}

void CSCharMove::setObjectId(int32_t id)
{
	mObjectId = id;
}

void CSCharMove::setMapID(int32_t id)
{
	mMapID = id;
}

void CSCharMove::setHandleID(int32_t handle)
{
	mHandleID = handle;
}

void CSCharMove::setTargetPos(const GLPos* pos)
{
	mTargetPos = *pos;
}

void CSCharMove::setStopLogicCount(int32_t count)
{
	mStopLogicCount = count;
}

void CSCharMove::setWorldPos(const GLPos& pos)
{
	mWorldPos = pos;
}