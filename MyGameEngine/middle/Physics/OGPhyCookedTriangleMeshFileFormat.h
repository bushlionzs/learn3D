#ifndef OGPhyCookedTriangleMeshFileFormat_h__
#define OGPhyCookedTriangleMeshFileFormat_h__

namespace Orphigine
{
	enum PhyCookedTriangleMeshFileFormat
	{
		CTM_FILEHEADER = 0x1000,// ÎÄ¼þÍ· [9/9/2008 JiangWei]
		CTM_INDICES_DATA = 0x2000,
		CTM_VERTICES_DATA = 0x3000,
		CTM_TRIANGLEMESH_DATA = 0x4000,
		CTM_OPTIMAL_BVH_DATA = 0x5000
	};
}
#endif // OGPhyCookedTriangleMeshFileFormat_h__
