#include "OgreHeader.h"
#include "OGActorFactory.h"
#include "OGActor.h"

namespace Orphigine
{

	void ActorFactory::destroyInstance(Actor* object)
	{
		delete object;
	}

}
