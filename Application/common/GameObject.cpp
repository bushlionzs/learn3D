#include "OgreHeader.h"
#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::setPosition(const Ogre::Vector3& pos)
{
	mPosition = pos;
}

const Ogre::Vector3& GameObject::getPosition()
{
	return mPosition;
}

void GameObject::setOrientation(const Ogre::Vector3& dir)
{
	mOrientation = dir;
}

const Ogre::Vector3& GameObject::getOrientation()
{
	return mOrientation;
}