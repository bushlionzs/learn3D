#ifndef OGPhyCookedTriangleMeshSerializer_h__
#define OGPhyCookedTriangleMeshSerializer_h__


#include "OgreSerializer.h"

class btTriangleIndexVertexArray;
class btOptimizedBvh;

namespace Orphigine
{
	class PhyCookedTriangleMesh;
	
	class _OrphigineExport PhyCookedTriangleMeshSerializer : public Ogre::Serializer
	{
	public:
		PhyCookedTriangleMeshSerializer();
		virtual ~PhyCookedTriangleMeshSerializer();

		void				exportCookedTriangleMesh(PhyCookedTriangleMesh* cookedTriangleMesh,const String& name,Endian endianMode = ENDIAN_NATIVE);

		void				importCookedTriangleMesh(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

	protected:
		void				writeCookedTriangleMesh(PhyCookedTriangleMesh* cookedTriangleMesh);

		void				writeIndicesData(PhyCookedTriangleMesh* cookedTriangleMesh);

		void				writeVerticesData(PhyCookedTriangleMesh* cookedTriangleMesh);

		void				writeTriangleMeshData(PhyCookedTriangleMesh* cookedTriangleMesh,btTriangleIndexVertexArray* triangleMeshDesc);

		void				writeOptimalBVHData(PhyCookedTriangleMesh* cookedTriangleMesh,btOptimizedBvh* triangleMesh);

		void				readCookedTriangleMesh(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

		void				readIndicesData(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

		void				readVerticesData(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

		void				readTriangleMeshData(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

		void				readOptimalBVHData(Ogre::DataStreamPtr& stream,PhyCookedTriangleMesh* cookedTriangleMesh);

		size_t				calcIndicesData(const PhyCookedTriangleMesh* cookedTriangleMesh);

		size_t				calcVerticesData(const PhyCookedTriangleMesh* cookedTriangleMesh);

		size_t				calcTriangleMeshData(const PhyCookedTriangleMesh* cookedTriangleMesh,btTriangleIndexVertexArray* triangleMeshDesc);

		size_t				calcOptimalBVHData(const PhyCookedTriangleMesh*	cookedTriangleMesh,btOptimizedBvh* triangleMesh);
	};
}
#endif // OGPhyCookedTriangleMeshSerializer_h__
