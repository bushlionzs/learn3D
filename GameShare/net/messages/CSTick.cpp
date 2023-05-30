#include "stdafx.h"
#include "CSTick.h"
#include "server/map/map_manager.h"
#include "server/map/game_map.h"
#include "server/map/map_info.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Player.h"
#include "server/gameobject/Behavior_Player.h"



CSTick::CSTick()
    :NetPacket(CS_LOGIN)
{

}

CSTick::~CSTick()
{

}

bool CSTick::process()
{
	GameMap* pScene = MapManager::GetSingletonPtr()->getMap(mMapId);
	if (NULL == pScene)
	{
		return false;
	}

	

	Object* pObj = pScene->GetSpecificObjByID(mPlayerId);
	const GLPos* pos = pObj->GetGLPos();
	
	float d2 = (mPlayerPositionX - pos->m_fX) * (mPlayerPositionX - pos->m_fX) +
		(mPlayerPositionZ - pos->m_fZ) * (mPlayerPositionZ - pos->m_fZ);

    return true;
}

void CSTick::setObjId(int32_t id)
{
	mObjId = id;
}


void CSTick::setMapId(int32_t id)
{
	mMapId = id;
}

void CSTick::setPosition(float x, float z)
{
	mPositionX = x;
	mPositionZ = z;
}

void CSTick::setPlayerInfo(int32_t id, float x, float z)
{
	mPlayerId = id;
	mPlayerPositionX = x;
	mPlayerPositionZ = z;
}