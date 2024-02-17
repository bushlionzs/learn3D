#include "OgreHeader.h"
#include "OGActorProxy.h"
#include "OgreMoveObject.h"

namespace Orphigine
{

	const String ActorProxy::msTypeName = "Orphigine::ActorProxy";
	const long ActorProxy::msTypeID = reinterpret_cast<long>(&msTypeName);
	//-----------------------------------------------------------------------
	ActorProxy::ActorProxy(void)
		: mObject()
	{
	}
	//-----------------------------------------------------------------------
	ActorProxy::ActorProxy(const ActorPtr& object)
		: mObject(object)
	{
	}
	//-----------------------------------------------------------------------
	ActorProxy::~ActorProxy()
	{
	}
	//-----------------------------------------------------------------------
	long ActorProxy::getTypeID(void) const
	{
		return msTypeID;
	}
	//-----------------------------------------------------------------------
	const String& ActorProxy::getTypeName(void) const
	{
		return msTypeName;
	}
	//-----------------------------------------------------------------------
	void ActorProxy::setObject(const ActorPtr& object)
	{
		mObject = object;
	}
	//-----------------------------------------------------------------------
	ActorPtr ActorProxy::getObject(void) const
	{
		return mObject.lock();
	}

	ActorPtr getObjectFromMovable(Ogre::MoveObject* movable)
	{
		assert(movable);
		if (movable)
		{
			const Ogre::Any& any = movable->getUserAny();
			
			if (any.has_value())
			{
				Ogre::UserDefinedObject* userObject = Ogre::any_cast<Ogre::UserDefinedObject*>(any);
				if (userObject && userObject->getTypeID() == ActorProxy::msTypeID)
				{
					ActorProxy* proxy = static_cast<ActorProxy*>(userObject);
					return proxy->getObject();
				}
			}
		}

		return ActorPtr();
	}

}
