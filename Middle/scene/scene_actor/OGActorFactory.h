#ifndef OGActorFactory_h__
#define OGActorFactory_h__


#include "OGFactory.h"

namespace Orphigine
{
	class Actor;

	class ActorFactory : public Factory<Actor>
	{
	public:
		void destroyInstance(Actor* object);
	};

}

#endif // OGActorFactory_h__