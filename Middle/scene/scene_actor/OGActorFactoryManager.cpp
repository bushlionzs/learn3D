#include "OgreHeader.h"
#include "OGActorFactoryManager.h"
#include "OGLightActor.h"
#include "OGStaticMeshActor.h"
#include "OGModelActor.h"
#include "OGParticleSystemActor.h"
#include "OGSkyActor.h"
#include "OGEnviromentActor.h"
#include "OGTerrainLiquidActor.h"
#include "OGEffectActor.h"
#include "OGSkeletonMeshActor.h"
#include "OGDetailActor.h"
#include "OGSkyLayerActor.h"

//单件方法
template<> Orphigine::ActorFactoryManager* Ogre::Singleton<Orphigine::ActorFactoryManager>::msSingleton = 0;

namespace Orphigine
{
	//-----------------------------------------------------------------------
	ActorFactoryManager* ActorFactoryManager::getSingletonPtr(void)
	{
		//assert(ms_Singleton);  
		return	(msSingleton);
	}
	ActorFactoryManager& ActorFactoryManager::getSingleton(void)
	{  
		assert(msSingleton);
		return (*msSingleton);
	}
	//-----------------------------------------------------------------------
	ActorFactoryManager::ActorFactoryManager()
	{
		init();
	}
	//-----------------------------------------------------------------------
	ActorFactoryManager::~ActorFactoryManager()
	{
		destroy();
	}
	//-----------------------------------------------------------------------
	ActorPtr ActorFactoryManager::createInstance(const String& type) const
	{
		Factory<Actor>* factory = findFactory(type);
		Actor* object = factory->createInstance();
		assert(object->getType() == type);
		return ActorPtr(object, Factory<Actor>::Deleter(factory));
	}
	bool ActorFactoryManager::init()
	{

		// TODO: register object factories here
		registerFactory((Orphigine::Factory<Actor>*)LightActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)StaticMeshActor::getFactory());
		//registerFactory((Orphigine::Factory<Actor>*)ActorObject::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)ModelActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)ParticleSystemActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)SkyBoxActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)SkyDomeActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)SkyPlaneActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)EnviromentActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)TerrainLiquidActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)EffectActor::getFactory());
		registerFactory((Orphigine::Factory<Actor>*)SkeletonMeshActor::getFactory());
		///	hdf added new object
		registerFactory((Orphigine::Factory<Actor>*)DetailActor::getFactory());

		registerFactory((Orphigine::Factory<Actor>*)SkyLayerActor::getFactory());
	
		return true;
	}
	bool ActorFactoryManager::destroy()
	{
		unregisterFactory((Orphigine::Factory<Actor>*)LightActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)StaticMeshActor::getFactory());
		//unregisterFactory((Orphigine::Factory<Actor>*)ActorObject::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)ModelActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)ParticleSystemActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)SkyBoxActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)SkyDomeActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)SkyPlaneActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)EnviromentActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)TerrainLiquidActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)EffectActor::getFactory());
		unregisterFactory((Orphigine::Factory<Actor>*)SkeletonMeshActor::getFactory());
		///	hdf added new object
		unregisterFactory((Orphigine::Factory<Actor>*)DetailActor::getFactory());

		unregisterFactory((Orphigine::Factory<Actor>*)SkyLayerActor::getFactory());
		//end
		return true;
	}

}
