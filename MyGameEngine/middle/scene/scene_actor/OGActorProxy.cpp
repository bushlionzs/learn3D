#include "OgreHeader.h"
#include "OGActorProxy.h"


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

	

}
