#ifndef OGCollisionBuilding_h__
#define OGCollisionBuilding_h__

#include "OGPhyCookedTriangleMesh.h"

#include "OgreResourceManager.h"
#include "OgreResource.h"

class btCollisionWorld;
class btCollisionDispatcher;
class btCollisionConfiguration;
class btAxisSweep3;

namespace Orphigine
{

	class CollisionBuildingLoader : public Ogre::ManualResourceLoader
	{
	public:
		void loadResource(Ogre::Resource* resource)
		{

		}
	};

	class PhyActor;
	class CollisionBuildingManager;
	class CollisionBuilding : public Ogre::Resource
	{
	public:
		CollisionBuilding(CollisionBuildingManager* creator, const String& name,
			Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader);
		virtual ~CollisionBuilding();

		virtual void				loadImpl(void);

		virtual void				unloadImpl(void);

		virtual size_t				calculateSize(void) const;

		bool						intersectBuildingMesh(const Ogre::Vector3& rayOrgin,
				const Ogre::Vector3& rayDir,Ogre::Vector3& outPosition);


		void						addCollisionActor(PhyActor* phyActor);

		unsigned int				getNumCollisionActor() const;

		PhyActor*					getPhysicsActor(unsigned int index);

	protected:
		CollisionBuildingLoader					m_meshLoader;

		std::vector<PhyActor*>					m_collisionActors;
		btCollisionWorld*						m_collisionWorld;
		btCollisionDispatcher*					m_collisionDispatcher;
		btCollisionConfiguration*				m_collisionConfiguration;
		btAxisSweep3*							m_broadphase;
	private:
	};


	class CollisionBuildingPtr : public std::shared_ptr<CollisionBuilding> 
	{
	public:
		CollisionBuildingPtr() : std::shared_ptr<CollisionBuilding>() {}
		explicit CollisionBuildingPtr(CollisionBuilding* rep) : std::shared_ptr<CollisionBuilding>(rep) {}
		CollisionBuildingPtr(const CollisionBuildingPtr& r) : std::shared_ptr<CollisionBuilding>(r) {}
		CollisionBuildingPtr(const Ogre::ResourcePtr& r) : std::shared_ptr<CollisionBuilding>()
		{
			assert(false);
		}

		/// Operator used to convert a ResourcePtr to a CollisionBuildingPtr
		CollisionBuildingPtr& operator=(const Ogre::ResourcePtr& r)
		{
			assert(false);
			return *this;
		}
	};
}
#endif // OGCollisionBuilding_h__
