#ifndef OGPhyStaticConcaveShape_h__
#define OGPhyStaticConcaveShape_h__


#include "OGPhyCookedTriangleMesh.h"
#include "OGPhyShape.h"

#include "OgreVector3.h"

class btBvhTriangleMeshShape;

namespace Orphigine
{
	class PhyCollection;
	class PhyCollectionSerializer;

	class _OrphigineExport PhyStaticConcaveShape : public PhyShape
	{
	public:
		PhyStaticConcaveShape(const String& cookedTriangleMeshResourceName,const Ogre::Vector3& localScaling);
		virtual ~PhyStaticConcaveShape();
		
		const Ogre::Vector3&					getLocalScaling() const;
		void									setLocalScaling(const Ogre::Vector3& val);

		std::shared_ptr<PhyCookedTriangleMesh>				getCookedTriangleMesh() const;

		virtual size_t							calcSize();

		virtual void							writeToBinary(PhyCollectionSerializer* serializer,
			PhyCollection* system);

		virtual void							readFromBinary(PhyCollectionSerializer* serializer,Ogre::DataStreamPtr& stream,
			PhyCollection* system);
	protected:
		void									_createStaticConcaveShapeImpl(const String& cookedTriangleMeshResourceName,
			const Ogre::Vector3& localScaling);

		void									_destroyStaticConcaveShapeImpl();
	protected:
		Ogre::Vector3							m_localScaling;
		std::shared_ptr<PhyCookedTriangleMesh>				m_cookedTriangleMesh;
		btBvhTriangleMeshShape*					m_bvhTriangleMeshShapeCache;		
	private:
	};
}
#endif // OGPhyStaticConcaveShape_h__
