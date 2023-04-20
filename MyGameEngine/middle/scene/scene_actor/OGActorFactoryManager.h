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

		//�̳���Ogre::Singleton�Ľӿ�(�ⲿ�ɵ���)
		static	ActorFactoryManager&	getSingleton(void);
		static	ActorFactoryManager*	getSingletonPtr(void);
		//�ӿں���
		ActorPtr createInstance(const String& type) const;
		bool init();
		bool destroy();
	};
}

#endif // OGActorFactoryManager_h__