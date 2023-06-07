#include "stdafx.h"
#include "GameClientUtil.h"
#include "OgreRoot.h"
namespace GameClientUtil
{
	uint64_t GetTimeNow()
	{
		return Ogre::Root::getSingleton().getTimer()->getMicroseconds();
	}
}