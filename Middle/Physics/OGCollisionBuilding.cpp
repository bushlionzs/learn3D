#include "OgreHeader.h"
#include "OGCollisionBuilding.h"
#include "OGCollisionBuildingSerializer.h"
#include "OGPhyCookedTriangleMeshManager.h"
#include "OGPhyActor.h"

#include "OgreVector3.h"
#include "OgreQuaternion.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{

	CollisionBuilding::CollisionBuilding(
		CollisionBuildingManager* creator, 
		const String& name,
		Ogre::ResourceHandle handle,
		const String& group, 
		bool isManual, 
		Ogre::ManualResourceLoader* loader )
	{
		m_collisionActors.clear();
		
		btDefaultCollisionConstructionInfo collisioinConstructionInfo;
		collisioinConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = 16;
		collisioinConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 16;

		m_collisionConfiguration = new btDefaultCollisionConfiguration(collisioinConstructionInfo);
		m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfiguration);
		btVector3	worldAabbMin(-10000,-10000,-10000);
		btVector3	worldAabbMax(10000,10000,10000);

		m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax);

		m_collisionWorld = new btCollisionWorld(m_collisionDispatcher,m_broadphase,m_collisionConfiguration);
	}

	CollisionBuilding::~CollisionBuilding()
	{
		unload();
	}

	void CollisionBuilding::loadImpl( void )
	{
		CollisionBuildingSerializer tmpSerializer;

		//Ogre::LogManager::getSingleton().logMessage("Collision Building loading :" + mName,Ogre::LML_TRIVIAL);

		Ogre::DataStreamPtr tmpStream = Ogre::ResourceManager::getSingleton().openResource(mName,
			mGroup);

		tmpSerializer.importCollisionBuilding(tmpStream,this);

		//Ogre::LogManager::getSingleton().logMessage(mName + "Collision Building loaded !",Ogre::LML_TRIVIAL);
	}

	void CollisionBuilding::unloadImpl( void )
	{
		std::vector<PhyActor*>::iterator iter;
		for ( iter = m_collisionActors.begin();iter != m_collisionActors.end();iter ++)
		{
			PhyActor* phyActor = (*iter);

			btCollisionObject* collObject = phyActor->getBtActor( );

			m_collisionWorld->removeCollisionObject(collObject);

			delete (*iter);
			(*iter) = NULL;
		}
		m_collisionActors.clear();

		delete m_collisionWorld;
		m_collisionWorld = NULL;

		delete m_collisionConfiguration;
		m_collisionConfiguration = NULL;

		delete m_collisionDispatcher;
		m_collisionDispatcher = NULL;

		delete m_broadphase;
		m_broadphase = NULL;
	}

	size_t CollisionBuilding::calculateSize( void ) const
	{
		return 0;
	}

	bool CollisionBuilding::intersectBuildingMesh( const Ogre::Vector3& rayOrgin, const Ogre::Vector3& rayDir,Ogre::Vector3& outPosition )
	{
		btVector3 tmpRayFrom = btVector3(rayOrgin.x,rayOrgin.y,rayOrgin.z);
		btVector3 tmpRayTo = tmpRayFrom + btVector3(rayDir.x,rayDir.y,rayDir.z);

		btCollisionWorld::ClosestRayResultCallback cb(tmpRayFrom, tmpRayTo);

		m_collisionWorld->rayTest (tmpRayFrom, tmpRayTo, cb);
		if (cb.hasHit ())
		{
			outPosition.x = cb.m_hitPointWorld.x();
			outPosition.y = cb.m_hitPointWorld.y();
			outPosition.z = cb.m_hitPointWorld.z();

			return true;
		} 

		outPosition = Ogre::Vector3::ZERO;

		return false;
	}

	void CollisionBuilding::addCollisionActor( PhyActor* phyActor )
	{
		m_collisionActors.push_back(phyActor);

		m_collisionWorld->addCollisionObject(phyActor->getBtActor());
	}

	unsigned int CollisionBuilding::getNumCollisionActor() const
	{
		return (unsigned int)m_collisionActors.size();
	}

	PhyActor* CollisionBuilding::getPhysicsActor( unsigned int index )
	{
		assert(index < (unsigned int)m_collisionActors.size() && "CollisionBuilding::getPhysicsActor");

		return m_collisionActors[index];
	}
}