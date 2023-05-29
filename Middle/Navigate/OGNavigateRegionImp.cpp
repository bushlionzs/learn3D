#include "OgreHeader.h"
#include "OGNavigateRegionImp.h"
#include "OGNavigateSpaceImp.h"
#include "OGNavigateAStarNodeImp.h"
#include <limits>

namespace Orphigine 
{

NeRegionImp::NeRegionImp(NeSpace* parent)
: m_parent(parent)
{
	m_vfPoints.clear();
	m_ID = -1;
	m_localAABB = NeAxisAlignedBoundingBox();
	m_position = NeVector3(0.0f,0.0f,0.0f);
	m_normal = NeVector3(0.0f,0.0f,0.0f);
}

NeRegionImp::~NeRegionImp()
{
	std::vector<NeVisibilityPoints*>::iterator iter;
	for (iter = m_vfPoints.begin();iter != m_vfPoints.end();iter ++)
	{
		delete *iter;
		*iter = NULL;
	}

	m_vfPoints.clear();
}

const NeVector3& NeRegionImp::getPosition() const
{
	return m_position;
}

int NeRegionImp::getID() const
{
	return m_ID;
}

void NeRegionImp::setID( int id )
{
	m_ID = id;
}

const NeVisibilityPoints* NeRegionImp::getPointOfVisibility( int index ) const
{
	if(0 <= index && index < (int)m_vfPoints.size())
		return m_vfPoints[index];
	else
		return NULL;
}

NeVisibilityPoints* NeRegionImp::getPointOfVisibility( int index )
{
	if(0 <= index && index < (int)m_vfPoints.size())
		return m_vfPoints[index];
	else
		return NULL;
}

void NeRegionImp::addPointOfVisibility(const NeVector3& position)
{
	NeVisibilityPoints* povPathNode = ((NeSpaceImp*)m_parent)->createPathNode(this,position);

	m_vfPoints.push_back(povPathNode);
}

int NeRegionImp::getNumPointsOfVisibility() const
{
	return (int)m_vfPoints.size();
}

const NeAxisAlignedBoundingBox& NeRegionImp::getLocalAABB() const
{
	return m_localAABB;
}

void NeRegionImp::updateAABB()
{
	float minX = std::numeric_limits<float>::infinity();
	float minZ = std::numeric_limits<float>::infinity();
	float maxX = -std::numeric_limits<float>::infinity();
	float maxZ = -std::numeric_limits<float>::infinity();

	for (int i = 0;i < (int)m_vfPoints.size();i ++)
	{
		NeVector3 tmpPos = m_vfPoints[i]->m_position;

		if(tmpPos.getX() < minX)
			minX = tmpPos.getX();
		if(tmpPos.getZ() < minZ)
			minZ = tmpPos.getZ();
		if(tmpPos.getX() > maxX)
			maxX = tmpPos.getX();
		if(tmpPos.getZ() > maxZ)
			maxZ = tmpPos.getZ();
	}

	float tmpXDifferenceHalf = (maxX - minX) * 0.5f;
	float tmpZDifferenceHalf = (maxZ - minZ) * 0.5f;

	m_position = NeVector3(minX + tmpXDifferenceHalf,0.0f,minZ + tmpZDifferenceHalf);

	m_localAABB.setMinimum(minX - m_position.getX(),0.0f,minZ - m_position.getZ());
	m_localAABB.setMaximum(maxX - m_position.getX(),0.0f,maxZ - m_position.getZ());
}

void NeRegionImp::extending( NeReal scale )
{
	//NeBool isClockWise = (m_normal.getY() > 0) 
	for (int i = 0;i < (int)m_vfPoints.size();i ++)
	{
		NeAStarNodeImp* pathNode = (NeAStarNodeImp*)m_vfPoints[i];

		NeVector3 pathNodePos = pathNode->getPosition() + 
			pathNode->m_vertexNormal * (scale - 1.0f) ;

		pathNode->setPosition(pathNodePos);
	}

	updateAABB();
}

NeSpace* NeRegionImp::getParent() const
{
	return m_parent;
}

void NeRegionImp::setParent( NeSpace* val )
{
	m_parent = val;
}

void NeRegionImp::computeSurfaceNormal()
{
	NeInt numPovs = getNumPointsOfVisibility();

	if(0 == numPovs)
		return;

	NeVisibilityPoints* povI = getPointOfVisibility(numPovs - 1);

	for (int i = 0;i < numPovs;++ i)
	{
		NeVisibilityPoints* povIAddOne = getPointOfVisibility(i);

		NeReal x = (povI->m_position.getZ() + povIAddOne->m_position.getZ()) * 
			(povI->m_position.getY() - povIAddOne->m_position.getY());

		m_normal.setX(m_normal.getX() + x);

		NeReal y = (povI->m_position.getX() + povIAddOne->m_position.getX()) * 
			(povI->m_position.getZ() - povIAddOne->m_position.getZ());

		m_normal.setY(m_normal.getY() + y);

		NeReal z = (povI->m_position.getY() + povIAddOne->m_position.getY()) * 
			(povI->m_position.getX() - povIAddOne->m_position.getX());

		m_normal.setZ(m_normal.getZ() + z);

		povI = povIAddOne;
	}

	m_normal = NeMath::normalize(m_normal);
}

void NeRegionImp::computeVerticesNormal()
{
	NeInt numPovs = getNumPointsOfVisibility();

	if(0 == numPovs)
		return;

	NeVector3* edgeNormal = new NeVector3[numPovs];

	NeVisibilityPoints* povI = getPointOfVisibility(numPovs - 1);

	for (int i = 0;i < numPovs;i ++)
	{
		NeVisibilityPoints* povIAddOne = getPointOfVisibility(i);

		NeVector3 edge = povIAddOne->m_position - povI->m_position;

		edgeNormal[i] = NeMath::normalize(NeMath::cross(edge,m_normal));
		
		povI = povIAddOne;
	}

	for (int i = 0;i < numPovs;i ++)
	{
		NeVisibilityPoints* povI = getPointOfVisibility(i);
		
		const NeVector3& tmpEdgeNormal1 = edgeNormal[i];

		if (i != numPovs - 1)
		{
			const NeVector3& tmpEdgeNormal2 = edgeNormal[i + 1];
			
			povI->m_vertexNormal = NeMath::normalize(tmpEdgeNormal1 + tmpEdgeNormal2);
		} 
		else
		{
			const NeVector3& tmpEdgeNormal2 = edgeNormal[0];

			povI->m_vertexNormal = NeMath::normalize(tmpEdgeNormal1 + tmpEdgeNormal2);
		}
	}

	delete []edgeNormal;
}

void NeRegionImp::computeConvexVertices()
{
	NeInt numPovs = getNumPointsOfVisibility();

	if(0 == numPovs)
		return;

	NeVisibilityPoints* povISubOne = NULL;
	NeVisibilityPoints* povI = NULL;
	NeVisibilityPoints* povIAddOne = NULL;

	for (int i = 1;i <= numPovs;i ++)
	{
		int povIndex = i - 1;

		povIndex = povIndex % numPovs;

		povISubOne = getPointOfVisibility(povIndex);


		povIndex = i % numPovs;

		povI = getPointOfVisibility(povIndex);
		povIndex = i + 1;

		povIndex = povIndex % numPovs;

		povIAddOne = getPointOfVisibility(povIndex);
		

		NeVector3 edge1 = povI->m_position - povISubOne->m_position;
		NeVector3 edge2 = povIAddOne->m_position - povI->m_position;

		NeVector3 vec = NeMath::cross(edge1,edge2);

		NeReal sclar = NeMath::dot(vec,m_normal);

		if (0.0f < sclar)
			povI->m_isConvex = true;
		else
			povI->m_isConvex = false;
	}

}

} // namespace Orphigine
