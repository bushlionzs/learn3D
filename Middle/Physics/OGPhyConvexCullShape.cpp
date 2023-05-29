#include "OgreHeader.h"
#include "OGPhyConvexCullShape.h"
#include "OGPhyUtil.h"

#include "btBulletCollisionCommon.h"
#include "LinearMath/btGeometryUtil.h"

namespace Orphigine
{


	PhyConvexHullShape::PhyConvexHullShape( const std::vector<Ogre::Vector3>& planes )
		: PhyShape("ConvexHull")
	{
		_createConvexHullShapeImpl(planes);
	}

	PhyConvexHullShape::~PhyConvexHullShape()
	{
		
	}

	void PhyConvexHullShape::_createConvexHullShapeImpl( const std::vector<Ogre::Vector3>& planes )
	{
		btAlignedObjectArray<btVector3>	bulletPlanes;

		for (int i = 0;i < (int)planes.size();i ++)
		{
			btVector3	bulletPlane = ogreToBulletVector3(planes[i]);

			bulletPlanes.push_back(bulletPlane);
		}

		btAlignedObjectArray<btVector3>	bulletOutVertices;

		btGeometryUtil::getVerticesFromPlaneEquations(bulletPlanes,bulletOutVertices);

		m_shape = new btConvexHullShape(&bulletOutVertices[0].getX(),bulletOutVertices.size());
	}
}