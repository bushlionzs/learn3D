#include "OgreHeader.h"
#include "OGActor.h"
#include "renderSystem.h"
#include "OgreRoot.h"
namespace Orphigine
{
	Actor::Actor(void)
		: mName()
		, mData(0)
	{

		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager(std::string("main"));
	}
	//-----------------------------------------------------------------------
	Actor::~Actor()
	{
	}
	//-----------------------------------------------------------------------
	void Actor::setName(const String& name)
	{
		mName = name;		
	}
	//-----------------------------------------------------------------------
	void Actor::setData(uint64_t data)
	{
		mData = data;
	}

	void Actor::setSceneManager(SceneManager* sceneManager)
	{
		if (mSceneManager != sceneManager)
		{
			mSceneManager = sceneManager;
			OnSceneManagerChagned();
		}
		
	}

	//-----------------------------------------------------------------------
	void Actor::queryReferenceResources(ResourceCollection* resourceCollection)
	{
	}
	//-----------------------------------------------------------------------
	void Actor::queryBakableEntities(EntityList& entities)
	{
	}

}
