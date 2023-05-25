#include "OgreHeader.h"
#include "OGPhyShapeSerializersManager.h"

template<> Orphigine::PhyShapeSerializersManager* Ogre::Singleton<Orphigine::PhyShapeSerializersManager>::msSingleton = NULL;

namespace Orphigine
{



	PhyShapeSerializersManager::PhyShapeSerializersManager()
	{

	}

	PhyShapeSerializersManager::~PhyShapeSerializersManager()
	{
 
	}
}