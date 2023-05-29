#ifndef OGPhyCookedTriangleMesh_h__
#define OGPhyCookedTriangleMesh_h__


#include "OgreResourceManager.h"
#include "OgreResource.h"
#include "OgreVector3.h"
#include "OgreScriptLoader.h"
//#include "btBulletCollisionCommon.h"

class btTriangleIndexVertexArray;
class btOptimizedBvh;

namespace Orphigine
{
	class PhyCookedTriangleMeshManager;
	class PhyCookedTriangleMeshLoader : public Ogre::ManualResourceLoader
	{
	public:
		void loadResource(Ogre::Resource* resource)
		{

		}
	};

	class _OrphigineExport PhyCookedTriangleMesh : public Ogre::Resource
	{
	public:
		PhyCookedTriangleMesh(PhyCookedTriangleMeshManager* creator, const String& name,
			Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader);
		virtual ~PhyCookedTriangleMesh();

		virtual void			loadImpl(void);

		virtual void			unloadImpl(void);

		virtual size_t			calculateSize(void) const;

		void					build(int numTriangles,int* triangleIndexBase,int triangleIndexStride,int numVertices,Real* vertexBase,int vertexStride);

		btTriangleIndexVertexArray*		getTriangleMeshDesc() const;
		void							setTriangleMeshDesc(btTriangleIndexVertexArray* triangleMeshDesc);

		btOptimizedBvh*					getTriangleMesh() const;
		void							setTriangleMesh(btOptimizedBvh* triangleMesh);
	protected:
		btTriangleIndexVertexArray*			m_triangleMeshDesc;
		btOptimizedBvh*						m_triangleMesh;
	protected:
		PhyCookedTriangleMeshLoader			m_meshLoader;
		
		
	private:
	};

}
#endif // OGPhyCookedTriangleMesh_h__
