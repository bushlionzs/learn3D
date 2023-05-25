#include "OgreHeader.h"
#include "OGPhyCookedTriangleMesh.h"
#include "OGPhyCookedTriangleMeshSerializer.h"
#include "btBulletCollisionCommon.h"

namespace Orphigine
{


	PhyCookedTriangleMesh::PhyCookedTriangleMesh(PhyCookedTriangleMeshManager* creator, const String& name,
		Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader )
		:Resource(nullptr, name, handle, group, isManual, loader)
	{
		/*m_Indices.clear();
		m_vertices.clear();
		m_optimalBVHData = NULL;*/

		m_triangleMeshDesc = NULL;
		m_triangleMesh = NULL;
	}

	PhyCookedTriangleMesh::~PhyCookedTriangleMesh()
	{
		unload();
	}

	void PhyCookedTriangleMesh::loadImpl( void )
	{
		PhyCookedTriangleMeshSerializer tmpSerializer;

	
		Ogre::DataStreamPtr tmpStream = Ogre::ResourceManager::getSingleton().openResource(mName,
			mGroup);

		tmpSerializer.importCookedTriangleMesh(tmpStream,this);

		
	}

	void PhyCookedTriangleMesh::unloadImpl( void )
	{

		if(NULL != m_triangleMesh)
		{
			m_triangleMesh->~btOptimizedBvh();
			btAlignedFree(m_triangleMesh);
		}
	
		if (NULL != m_triangleMeshDesc)
		{
			IndexedMeshArray& indexMeshArray = m_triangleMeshDesc->getIndexedMeshArray();
			for (int i = 0;i < (int)indexMeshArray.size();i ++)
			{
				btIndexedMesh* indexedMesh = &indexMeshArray[i];

				delete indexedMesh->m_triangleIndexBase;
				indexedMesh->m_triangleIndexBase = NULL;

				delete indexedMesh->m_vertexBase;
				indexedMesh->m_vertexBase = NULL;
			}
			indexMeshArray.clear();

			delete m_triangleMeshDesc;
			m_triangleMeshDesc = NULL;
		}
	}

	size_t PhyCookedTriangleMesh::calculateSize( void ) const
	{
		return 0;
	}

	void PhyCookedTriangleMesh::build(int numTriangles,int* triangleIndexBase,int triangleIndexStride,int numVertices,btScalar* vertexBase,int vertexStride)
	{
		m_triangleMeshDesc = new btTriangleIndexVertexArray(
			numTriangles,triangleIndexBase,triangleIndexStride,
			numVertices,vertexBase,vertexStride);

		void* mem = btAlignedAlloc(sizeof(btOptimizedBvh),16);
		m_triangleMesh = new (mem) btOptimizedBvh();

		btVector3 bvhAabbMin,bvhAabbMax;
		m_triangleMeshDesc->calculateAabbBruteForce(bvhAabbMin,bvhAabbMax);

		m_triangleMesh->build(m_triangleMeshDesc,true,bvhAabbMin,bvhAabbMax);
	}

	btTriangleIndexVertexArray* PhyCookedTriangleMesh::getTriangleMeshDesc() const
	{
		return m_triangleMeshDesc;
	}

	btOptimizedBvh* PhyCookedTriangleMesh::getTriangleMesh() const
	{
		return m_triangleMesh;
	}

	void PhyCookedTriangleMesh::setTriangleMeshDesc( btTriangleIndexVertexArray* triangleMeshDesc )
	{
		m_triangleMeshDesc = triangleMeshDesc;
	}

	void PhyCookedTriangleMesh::setTriangleMesh( btOptimizedBvh* triangleMesh )
	{
		m_triangleMesh = triangleMesh;
	}
}