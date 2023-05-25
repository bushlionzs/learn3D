#include "OgreHeader.h"
#include "OGPhysicsManager.h"
#include "OGPhyWorld.h"

template<> Orphigine::PhysicsManager* Ogre::Singleton<Orphigine::PhysicsManager>::msSingleton = NULL;

namespace Orphigine
{
	 

	PhysicsManager::PhysicsManager()
		:m_world(NULL)
	{
		m_world = new PhyWorld(-980.0f);
	}

	PhysicsManager::~PhysicsManager()
	{
		delete m_world;
		m_world = NULL; 
	}

	PhyWorld* PhysicsManager::getWorld() const
	{
		return m_world;
	}
	
}
