#ifndef OGActorProxy_h__
#define OGActorProxy_h__

#include "OGActor.h"
#include "OgreUserDefinedObject.h"

namespace Orphigine
{
	class  ActorProxy: public Ogre::UserDefinedObject
	{
	public:
		ActorProxy(void);
		ActorProxy(const ActorPtr& object);
		virtual ~ActorProxy();

		virtual long getTypeID(void) const;
		virtual const String& getTypeName(void) const;

		void setObject(const ActorPtr& object);
		ActorPtr getObject(void) const;

		static const long msTypeID;

		static const String msTypeName;

	protected:
		ActorWeakPtr mObject;
	};
	ActorPtr _OrphigineExport getObjectFromMovable(Ogre::MoveObject* movable);
}

#endif // OGActorProxy_h__