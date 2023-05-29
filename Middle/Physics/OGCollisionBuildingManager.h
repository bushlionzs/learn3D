
#ifndef OGCollisionBuildingManager_h__
#define OGCollisionBuildingManager_h__

#include "OGCollisionBuilding.h"

#include "OgreResourceManager.h"
#include "OgreSingleton.h"
#include "OgreResource.h"
#include "OgreScriptLoader.h"

namespace Orphigine
{
	class CollisionBuildingManager : public Ogre::ScriptLoader, 
		public Ogre::Singleton<CollisionBuildingManager>, public Ogre::ManualResourceLoader
	{
	public:
		CollisionBuildingManager();
		~CollisionBuildingManager();

		virtual Ogre::Resource*					createImpl(const String& name, Ogre::ResourceHandle handle, 
			const String& group, bool isManual, Ogre::ManualResourceLoader* loader, 
			const Ogre::NameValuePairList* createParams);

		virtual	CollisionBuildingPtr		createManual(const String& name,const String& groupName,
			Ogre::ManualResourceLoader* loader = 0);

		virtual void							loadResource(Ogre::Resource* resource);

	protected:
	private:
	};
}
#endif // OGCollisionBuildingManager_h__