#include "OgreHeader.h"
#include "OGCollisionBuildingManager.h"
#include "OGCollisionBuilding.h"

#include "OgreResourceManager.h"
#include "OgreVector3.h"
#include "OgreRay.h"

#include "btBulletCollisionCommon.h"

template<> Orphigine::CollisionBuildingManager* Ogre::Singleton<Orphigine::CollisionBuildingManager>::msSingleton = NULL;
namespace Orphigine
{
	CollisionBuildingManager::CollisionBuildingManager()
	{
		
	}

	CollisionBuildingManager::~CollisionBuildingManager()
	{
		
	}

	Ogre::Resource* CollisionBuildingManager::createImpl( const String& name, Ogre::ResourceHandle handle, 
		const String& group, bool isManual, Ogre::ManualResourceLoader* loader, const Ogre::NameValuePairList* createParams )
	{
		return OGRE_NEW CollisionBuilding(this,name,handle,group,isManual,loader);
	}

	void CollisionBuildingManager::loadResource( Ogre::Resource* resource )
	{

	}

	Orphigine::CollisionBuildingPtr CollisionBuildingManager::createManual( const String& name,const String& groupName, Ogre::ManualResourceLoader* loader /*= 0*/ )
	{
		CollisionBuilding* res = (CollisionBuilding*)createImpl(name, 0,groupName,true,loader, nullptr);

		Orphigine::CollisionBuildingPtr dummy(res);
		return dummy;
	}
}