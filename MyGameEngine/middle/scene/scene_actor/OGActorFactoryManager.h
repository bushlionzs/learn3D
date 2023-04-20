#ifndef OGActorFactoryManager_h__
#define OGActorFactoryManager_h__


#include "OGActor.h"
#include "OGFactory.h"
#include "OgreSingleton.h"

namespace Orphigine
{
	class  ActorFactoryManager : public FactoryManager<Actor>, public Ogre::Singleton<ActorFactoryManager>
	{
	public:
		ActorFactoryManager();
		~ActorFactoryManager();

		//继承自Ogre::Singleton的接口(外部可调用)
		static	ActorFactoryManager&	getSingleton(void);
		static	ActorFactoryManager*	getSingletonPtr(void);
		//接口函数
		ActorPtr createInstance(const String& type) const;
		bool init();
		bool destroy();
	};
}

#endif // OGActorFactoryManager_h__