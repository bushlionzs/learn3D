#include "OgreHeader.h"
#include "KObject.h"
#include "GameEntity.h"
#include "Basics.h"
#include "engine_manager.h"

KObject::KObject()
{
	mObjectType = ObjectType_None;
	m_nBaseLogicCount = INVALID_ID;
	m_nActionLogicCount = INVALID_ID;
}

KObject::~KObject()
{

}

uint32_t KObject::getObjectType()
{
	return mObjectType;
}

void KObject::setId(int64_t id)
{
	mServerId = id;
}

int64_t KObject::getId()
{
	return mServerId;
}

void KObject::setPosition(const Ogre::Vector3& pos, bool useTerrainHeight)
{
	mPosition = pos;
	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, mPosition,
		GAT_ENGINE, mEnginePosition, useTerrainHeight);

	if (mMainEntity)
		mMainEntity->setEntityPosition(mEnginePosition);

	if (mHorseEntity)
	{
		mHorseEntity->setEntityPosition(mEnginePosition);
	}
}

const Ogre::Vector3& KObject::getPosition()
{
	return mPosition;
}

const Ogre::Vector3& KObject::getEnginePosition()
{
	return mEnginePosition;
}

void KObject::setDirection(float dir)
{
	mDir = dir;

	mMainEntity->setDirection(dir);
	if (mHorseEntity)
	{
		mHorseEntity->setDirection(dir);
	}
}

float KObject::getDirection()
{
	return mDir;
}

GameEntity* KObject::createGameEntity(int32_t entityType)
{
	return new GameEntity(this);
}