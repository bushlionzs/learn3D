#include "stdafx.h"
#include "CSPlayerRequestBaseAttrib.h"
#include "server_manager.h"
#include "map/game_map.h"
#include "map/map_manager.h"
#include "gameobject/Player.h"

CSPlayerRequestBaseAttrib::CSPlayerRequestBaseAttrib():
	NetPacket(CS_REQUEST_BASEATTR)
{

}

CSPlayerRequestBaseAttrib::~CSPlayerRequestBaseAttrib()
{

}

bool CSPlayerRequestBaseAttrib::process()
{
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapId);

	Object* pObj = pMap->GetSpecificObjByID(mPlayerId);
	if (pObj == NULL || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	pObj = pMap->GetSpecificObjByID(mTargetId);

	Character* pCharacter = (Character*)pObj;

	pCharacter->RequestBaseProperty(pPlayer);
	
	return true;
}

void CSPlayerRequestBaseAttrib::setTargetId(int32_t id)
{
	mTargetId = id;
}

void CSPlayerRequestBaseAttrib::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void CSPlayerRequestBaseAttrib::setMapId(int32_t id)
{
	mMapId = id;
}

