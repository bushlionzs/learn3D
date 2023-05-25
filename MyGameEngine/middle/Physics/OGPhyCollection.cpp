#include "OgreHeader.h"
#include "OGPhyCollection.h"
#include "OGPhyActor.h"
#include "OGPhysicsManager.h"
#include "OGPhyWorld.h"

namespace Orphigine
{
	PhyCollection::PhyCollection()
	{
		m_actors.clear();
	}

	PhyCollection::~PhyCollection()
	{
		m_actors.clear();
	}

	void PhyCollection::addActor( PhyActor* actor )
	{
		m_actors.push_back(actor);
	}

	unsigned int PhyCollection::getNumActors() const
	{
		return (unsigned int)m_actors.size();
	}

	const PhyActor* PhyCollection::getActor( unsigned int actorIndex ) const
	{
		assert((unsigned int)m_actors.size() > actorIndex && "Ô½½çPhyCollection::getActor");

		return m_actors[actorIndex];
	}

	void PhyCollection::instantiate()
	{
		PhysicsManager* physicsMgr = PhysicsManager::getSingletonPtr();
		
		PhyWorld* physicsWorld = physicsMgr->getWorld();

		std::vector<PhyActor*>::iterator iter;

		for (iter = m_actors.begin();iter != m_actors.end();iter ++)
		{
			physicsWorld->addActor((*iter));
		}
	}
}