#include "OgreHeader.h"
#include "OGPhyCookedTriangleMeshSerializer.h"
#include "OGPhyCookedTriangleMeshFileFormat.h"
#include "OGPhyCookedTriangleMesh.h"

#include "OgreException.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	PhyCookedTriangleMeshSerializer::PhyCookedTriangleMeshSerializer()
	{	
		 mVersion = "[Serializer_v1.10]";
	}

	PhyCookedTriangleMeshSerializer::~PhyCookedTriangleMeshSerializer()
	{
		
	}

	void PhyCookedTriangleMeshSerializer::exportCookedTriangleMesh( PhyCookedTriangleMesh* cookedTriangleMesh,const String& name,Endian endianMode /*= ENDIAN_NATIVE*/ )
	{
		// Decide on endian mode
		
	}

	void PhyCookedTriangleMeshSerializer::importCookedTriangleMesh( Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh )
	{
		// Determine endianness (must be the first thing we do!)
		determineEndianness(stream);

		// Check header
		readFileHeader(stream);

		readCookedTriangleMesh(stream,cookedTriangleMesh);
		
	}

	void PhyCookedTriangleMeshSerializer::writeCookedTriangleMesh( PhyCookedTriangleMesh* cookedTriangleMesh )
	{
		btTriangleIndexVertexArray* tmpMeshDesc = cookedTriangleMesh->getTriangleMeshDesc();
		writeTriangleMeshData(cookedTriangleMesh,tmpMeshDesc);

		btOptimizedBvh*	tmpOptimizedMesh = cookedTriangleMesh->getTriangleMesh();
		writeOptimalBVHData(cookedTriangleMesh,tmpOptimizedMesh);
	}

	void PhyCookedTriangleMeshSerializer::readCookedTriangleMesh( Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh )
	{
		unsigned short streamID;
		while(!stream->eof())
		{
			streamID = readChunk(stream);
			switch (streamID)
			{
			case CTM_TRIANGLEMESH_DATA:
				readTriangleMeshData(stream,cookedTriangleMesh);
				break;
			case CTM_OPTIMAL_BVH_DATA:
				readOptimalBVHData(stream,cookedTriangleMesh);
				break;
			}
		}
	}

	void PhyCookedTriangleMeshSerializer::writeTriangleMeshData( PhyCookedTriangleMesh* cookedTriangleMesh,btTriangleIndexVertexArray* triangleMeshDesc )
	{
		
	}

	void PhyCookedTriangleMeshSerializer::writeOptimalBVHData( PhyCookedTriangleMesh* cookedTriangleMesh ,btOptimizedBvh* triangleMesh)
	{
		
	}


	void PhyCookedTriangleMeshSerializer::readTriangleMeshData( Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh )
	{
		unsigned int tmpNumFace = 0;
		readInts(stream,&tmpNumFace,1);

		unsigned int* tmpIndices = new unsigned int[tmpNumFace * 3];

		for (unsigned int i = 0;i < tmpNumFace * 3;i ++)
		{
			unsigned int tmpIndex = 0;
			readInts(stream,&tmpIndex,1);

			tmpIndices[i] = tmpIndex;
		}


		unsigned int tmpNumVertices = 0;
		readInts(stream,&tmpNumVertices,1);

		Ogre::Vector3* tmpVertices = new Ogre::Vector3[tmpNumVertices];

		for (unsigned int i = 0;i < tmpNumVertices;i ++)
		{
			Ogre::Vector3 tmpVertex;
			readObject(stream,tmpVertex);

			tmpVertices[i] = tmpVertex;
		}

		btTriangleIndexVertexArray* triangleMeshDesc = new btTriangleIndexVertexArray(
		tmpNumFace,(int*)tmpIndices,3 * sizeof(int),
		tmpNumVertices,(Real*)&tmpVertices[0].x,sizeof(Ogre::Vector3));

		cookedTriangleMesh->setTriangleMeshDesc(triangleMeshDesc);
	}

	void PhyCookedTriangleMeshSerializer::readOptimalBVHData( Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh )
	{
		unsigned int tmpOptimalBVHDataSize = 0;
		readInts(stream,&tmpOptimalBVHDataSize,1);

		int buffersize = tmpOptimalBVHDataSize + btOptimizedBvh::getAlignmentSerializationPadding();

		void* buffer = btAlignedAlloc(buffersize,16);

		stream->read(buffer,tmpOptimalBVHDataSize);

		/*btOptimizedBvh*	tmpTriangleMesh = NULL;

		tmpTriangleMesh = btOptimizedBvh::deSerializeInPlace(buffer,buffersize,false);

		cookedTriangleMesh->setTriangleMesh(tmpTriangleMesh);*/
	}

	

	size_t PhyCookedTriangleMeshSerializer::calcTriangleMeshData( const PhyCookedTriangleMesh* cookedTriangleMesh,btTriangleIndexVertexArray* triangleMeshDesc )
	{
		size_t tmpSize = STREAM_OVERHEAD_SIZE;

		const unsigned char* vertexBase = NULL;
		int numVerts;
		PHY_ScalarType vertexType;
		int vertexStride;
		const unsigned char* indexBase = NULL;
		int indexStride;
		int numFaces;
		PHY_ScalarType indexType;

		triangleMeshDesc->getLockedReadOnlyVertexIndexBase (&vertexBase, numVerts, vertexType, vertexStride, &indexBase, indexStride, numFaces, indexType);

		tmpSize += sizeof(unsigned int);

		tmpSize += sizeof(unsigned int) * numFaces * 3;

		tmpSize += sizeof(unsigned int);

		tmpSize += sizeof(Ogre::Vector3) * numVerts;

		triangleMeshDesc->unLockReadOnlyVertexBase(0);

		return tmpSize;
	}

	size_t PhyCookedTriangleMeshSerializer::calcOptimalBVHData( const PhyCookedTriangleMesh* cookedTriangleMesh ,btOptimizedBvh* triangleMesh)
	{
		size_t tmpSize = STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(unsigned int);

		unsigned int tmpDataSize = triangleMesh->calculateSerializeBufferSize();

		tmpSize += tmpDataSize;
		
		return tmpSize;
	}

	
	
}