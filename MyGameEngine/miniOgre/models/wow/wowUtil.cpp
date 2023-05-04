#include "OgreHeader.h"
#include "wowUtil.h"

Ogre::Vector3 fixCoordSystem(Ogre::Vector3 v)
{
	return Ogre::Vector3(v.x, v.z, -v.y);
}

Ogre::Vector3 fixCoordSystem2(Ogre::Vector3 v)
{
	return Ogre::Vector3(v.x, v.z, v.y);
}

Ogre::Quaternion fixCoordSystemQuat(Ogre::Quaternion v)
{
	return Ogre::Quaternion(-v.x, -v.z, v.y, v.w);
}