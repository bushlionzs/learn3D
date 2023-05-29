
#ifndef OGCollisionBuildingZonePageSerializer_h__
#define OGCollisionBuildingZonePageSerializer_h__

#include "OGCollisionBuilding.h"

#include "OgreSerializer.h"

namespace Orphigine
{
	class CollisionBuilding;
	class PhyActor;

	
	class CollisionBuildingSerializer : public Ogre::Serializer
	{
	public:
		friend class		PhyShape;
		friend class		PhyStaticConcaveShape;

		CollisionBuildingSerializer();
		virtual ~CollisionBuildingSerializer();

		void				exportCollisionBuilding(CollisionBuilding* collisionBuilding,const String& name,Endian endianMode = ENDIAN_NATIVE);

		void				importCollisionBuilding(Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding);

	protected:
		void				writePhysicsSpace(CollisionBuilding* collisionBuilding);

		void				writePhysicsActors(CollisionBuilding* collisionBuilding,PhyActor* physicsActor);

		void				writePhysicsShapes(CollisionBuilding* collisionBuilding,PhyShape* physicsShape);


		void				readPhysicsSpace(Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding);

		void				readPhysicsActors(Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding);

		void				readPhysicsShapes(Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding,PhyActor* physicsActor);


		size_t				calcPhysicsSpace(CollisionBuilding* collisionBuilding);

		size_t				calcPhysicsActors(PhyActor* physicsActor);

		size_t				calcPhysicsShape( PhyShape* physicsSpace);
	};
}
#endif // OGCollisionBuildingZonePageSerializer_h__
