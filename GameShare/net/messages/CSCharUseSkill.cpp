#pragma once
#include "stdafx.h"
#include "CSCharUseSkill.h"
#include "server/map/map_manager.h"
#include "server/map/game_map.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Player.h"
#include "server/gameobject/Behavior_Player.h"

CSCharUseSkill::CSCharUseSkill():
	NetPacket(CS_USE_SKILL)
{

}

CSCharUseSkill::~CSCharUseSkill()
{

}

bool CSCharUseSkill::process()
{
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mMapID);

	if (pMap == nullptr)
	{
		return false;
	}

	ObjectManager* objectManager = pMap->GetObjManager();

	Object* pObj = objectManager->GetObj(mPlayerId);

	if (pObj == nullptr)
		return false;
	if (pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return false;
	}

	Player* pPlayer = (Player*)pObj;

	OPT_RESULT oResult = pPlayer->GetHumanAI()->PushCmd_UseSpell(
		mSkillID, mTargetID, mTargetPos.m_fX, mTargetPos.m_fZ, mDir, mGuidTarget, mHurtDelayTime);

	if (ORT_FAILED(oResult))
	{
		return false;
	}

	


	return true;
}

void CSCharUseSkill::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void CSCharUseSkill::setSkillID(int32_t id)
{
	mSkillID = id;
}

void CSCharUseSkill::setTargetID(int32_t id)
{
	mTargetID = id;
}

void CSCharUseSkill::setTargetPos(float x, float z)
{
	mTargetPos.m_fX = x;
	mTargetPos.m_fZ = z;
}

void CSCharUseSkill::setCharDir(float dir)
{
	mDir = dir;
}

void CSCharUseSkill::setGuidTarget(GUID_t guidtarget)
{
	mGuidTarget = guidtarget;
}

void CSCharUseSkill::setMapID(int32_t id)
{
	mMapID = id;
}