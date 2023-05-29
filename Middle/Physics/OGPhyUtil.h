/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OGPhyUtil.h
	Created:   ½ªÍþ 2008/09/25
	Description :	
    Revision :

=============================================================================*/

#ifndef OGPhyUtil_h__
#define OGPhyUtil_h__

#include "OgreVector3.h"
#include "OgreQuaternion.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{
	inline Ogre::Vector3 bulletToOgreVector3(const btVector3& source)
	{
		return Ogre::Vector3(source.x(),source.y(),source.z());
	}

	inline btVector3 ogreToBulletVector3(const Ogre::Vector3& source)
	{
		return btVector3(source.x,source.y,source.z);
	}

	inline Ogre::Quaternion bulletToOgreQuaternion(const btQuaternion& source)
	{
		return Ogre::Quaternion(source.w(),source.x(),source.y(),source.z());
	}

	inline btQuaternion ogreToBulletQuaternion(const Ogre::Quaternion& source)
	{
		return btQuaternion(source.x,source.y,source.z,source.w);
	}
}
#endif // OGPhyUtil_h__
