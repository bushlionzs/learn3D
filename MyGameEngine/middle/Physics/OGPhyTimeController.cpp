#include "OgreHeader.h"
#include "OGPhyTimeController.h"
#include "OGPhyWorld.h"
#include "OgreRoot.h"

namespace Orphigine
{


	PhyDefaultTimeController::PhyDefaultTimeController( PhyWorld* world )
		: m_world(world)
	{
		Ogre::Root::getSingleton().addFrameListener(this);
	}

	PhyDefaultTimeController::~PhyDefaultTimeController()
	{
		Ogre::Root::getSingleton().removeFrameListener(this);

		m_world = NULL;
	}

	bool PhyDefaultTimeController::frameStarted( const Ogre::FrameEvent& evt )
	{
		m_world->simulate(evt.timeSinceLastFrame);

		return true;
	} 
}