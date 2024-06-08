#include "OgreHeader.h"
#include "KObject.h"
#include "GameEntity.h"
#include "Basics.h"

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

void KObject::setPosition(const Ogre::Vector3& pos)
{
	mPosition = pos;
}

const Ogre::Vector3& KObject::getPosition()
{
	return mPosition;
}

void KObject::setOrientation(const Ogre::Vector3& dir)
{
	mOrientation = dir;
}

const Ogre::Vector3& KObject::getOrientation()
{
	return mOrientation;
}

GameEntity* KObject::createGameEntity(int32_t entityType)
{
	return new GameEntity(this);
}