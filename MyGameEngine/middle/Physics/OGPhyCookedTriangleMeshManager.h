#ifndef OGPhyCookedTriangleMeshManager_h__
#define OGPhyCookedTriangleMeshManager_h__

#include "OGPhyCookedTriangleMesh.h"

#include "OgreResourceManager.h"
#include "OgreSingleton.h"
#include "OgreResource.h"

namespace Orphigine
{
	class _OrphigineExport PhyCookedTriangleMeshManager :
		public Ogre::Singleton<PhyCookedTriangleMeshManager>, public Ogre::ManualResourceLoader
	{
	public:
		PhyCookedTriangleMeshManager();
		~PhyCookedTriangleMeshManager();

		virtual	std::shared_ptr<PhyCookedTriangleMesh>		createManual(const String& name,const String& groupName,
			Ogre::ManualResourceLoader* loader = 0);

		virtual Ogre::Resource*	createImpl(const String& name, Ogre::ResourceHandle handle, 
			const String& group, bool isManual, Ogre::ManualResourceLoader* loader, 
			const Ogre::NameValuePairList* createParams);

		virtual void loadResource(Ogre::Resource* resource);

	private:
	};
}
#endif // OGPhyCookedTriangleMeshManager_h__
