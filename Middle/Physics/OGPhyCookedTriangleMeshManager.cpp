#include "OgreHeader.h"
#include "OGPhyCookedTriangleMeshManager.h"
#include "OGPhyCookedTriangleMesh.h"
#include "OgreVector3.h"
#include "btBulletCollisionCommon.h"

template<> Orphigine::PhyCookedTriangleMeshManager* Ogre::Singleton<Orphigine::PhyCookedTriangleMeshManager>::msSingleton = NULL;
namespace Orphigine
{
	PhyCookedTriangleMeshManager::PhyCookedTriangleMeshManager()
	{
		
	}

	PhyCookedTriangleMeshManager::~PhyCookedTriangleMeshManager()
	{
		
	}

	Ogre::Resource* PhyCookedTriangleMeshManager::createImpl( const String& name, Ogre::ResourceHandle handle, const String& group, bool isManual, Ogre::ManualResourceLoader* loader, const Ogre::NameValuePairList* createParams )
	{
		Ogre::Resource * res =  OGRE_NEW PhyCookedTriangleMesh(
			this,name,handle,group,isManual,loader);

		res->load();
		return res;
	}

	void PhyCookedTriangleMeshManager::loadResource( Ogre::Resource* resource )
	{

	}

	std::shared_ptr<PhyCookedTriangleMesh> PhyCookedTriangleMeshManager::createManual( const String& name,const String& groupName, Ogre::ManualResourceLoader* loader /*= 0*/ )
	{
		PhyCookedTriangleMesh* res = (PhyCookedTriangleMesh*)createImpl(name, 0, groupName,true,loader, nullptr);

		std::shared_ptr<PhyCookedTriangleMesh> dummy(res);
		return dummy;
	}
}




