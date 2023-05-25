#include "OgreHeader.h"
#include "OGPhyStaticConcaveShape.h"
#include "OGPhyUtil.h"
#include "OGPhyCollectionSerializer.h"
#include "OGPhyCollectionFileFormat.h"
#include "OGPhyCollection.h"
#include "OGPhyCookedTriangleMeshManager.h"

#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h"

namespace Orphigine
{
	
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	PhyStaticConcaveShape::PhyStaticConcaveShape(const String& cookedTriangleMeshResourceName,const Ogre::Vector3& localScaling)
		: PhyShape("StaticConcaveShape")
		,m_cookedTriangleMesh(NULL)
		, m_localScaling(localScaling)
	{
		if (_initBaseAttribute("PhyStaticConcaveShape"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			
		}
		_createStaticConcaveShapeImpl(cookedTriangleMeshResourceName,localScaling);
	}

	PhyStaticConcaveShape::~PhyStaticConcaveShape()
	{
		_destroyStaticConcaveShapeImpl();
	}

	const Ogre::Vector3& PhyStaticConcaveShape::getLocalScaling() const
	{
		return m_localScaling;
	}

	void PhyStaticConcaveShape::setLocalScaling( const Ogre::Vector3& val )
	{
		m_localScaling = val;
	}

	std::shared_ptr<PhyCookedTriangleMesh> PhyStaticConcaveShape::getCookedTriangleMesh() const
	{
		return m_cookedTriangleMesh;
	}

	void PhyStaticConcaveShape::_createStaticConcaveShapeImpl( const String& cookedTriangleMeshResourceName, const Ogre::Vector3& localScaling )
	{
		auto res = PhyCookedTriangleMeshManager::getSingleton().
			createImpl(cookedTriangleMeshResourceName, 
				0, "Bootstrap", false, nullptr, nullptr);
		m_cookedTriangleMesh =
			std::dynamic_pointer_cast<PhyCookedTriangleMesh>(std::shared_ptr<Ogre::Resource>(res));

		btTriangleIndexVertexArray* triangleArray = m_cookedTriangleMesh->getTriangleMeshDesc();

		btOptimizedBvh*	optimizedBvh = m_cookedTriangleMesh->getTriangleMesh();

		m_bvhTriangleMeshShapeCache = new btBvhTriangleMeshShape(triangleArray,true,false);

		m_bvhTriangleMeshShapeCache->setOptimizedBvh(optimizedBvh);

		m_shape = new btScaledBvhTriangleMeshShape(m_bvhTriangleMeshShapeCache,ogreToBulletVector3(m_localScaling));
	}

	void PhyStaticConcaveShape::_destroyStaticConcaveShapeImpl()
	{

		delete m_bvhTriangleMeshShapeCache;
		m_bvhTriangleMeshShapeCache = NULL;
	}

	void PhyStaticConcaveShape::writeToBinary( PhyCollectionSerializer* serializer, PhyCollection* system )
	{
	}

	void PhyStaticConcaveShape::readFromBinary( PhyCollectionSerializer* serializer,Ogre::DataStreamPtr& stream, PhyCollection* system )
	{
		

	}

	size_t PhyStaticConcaveShape::calcSize()
	{
		return 0;
	}

}