#ifndef OGPhyCollectionSerializer_h__
#define OGPhyCollectionSerializer_h__


#include "OGPhyCollection.h"

#include "OgreSerializer.h"

namespace Orphigine
{
	class PhyCollection;
	class PhyActor;


	class _OrphigineExport PhyCollectionSerializer : public Ogre::Serializer
	{
	public:
		friend class		PhyShape;
		friend class		PhyStaticConcaveShape;

		PhyCollectionSerializer();
		virtual ~PhyCollectionSerializer();

		void				exportPhyCollection(PhyCollection* PhyCollection,const String& name,Endian endianMode = ENDIAN_NATIVE);

		void				importPhyCollection(Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection);

	protected:
		void				writePhysicsSpace(PhyCollection* PhyCollection);

		void				writePhysicsActors(PhyCollection* PhyCollection,const PhyActor* physicsActor);

		void				writePhysicsShapes(PhyCollection* PhyCollection,PhyShape* physicsShape);


		void				readPhysicsSpace(Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection);

		void				readPhysicsActors(Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection);

		void				readPhysicsShapes(Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection,PhyActor* physicsActor);


		size_t				calcPhysicsSpace(PhyCollection* PhyCollection);

		size_t				calcPhysicsActors(const PhyActor* physicsActor);

		size_t				calcPhysicsShape( PhyShape* physicsSpace);
	};
}
#endif // OGPhyCollectionSerializer_h__
