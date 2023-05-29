#include "OgreHeader.h"
#include <algorithm>
#include <map>
#include <assert.h>
#include "OGNavigateSpaceImp.h"
#include "OGNavigateRegionImp.h"
#include "OGNavigateAStarSolverImp.h"
#include "OGNavigateAStarNodeImp.h"

namespace Orphigine 
{

NeSpaceImp::NeSpaceImp()
: m_solver(NULL)
, m_currentPathNodeGlobalHandle(0)
, m_precomputePOVCallback(NULL)
{
	m_regions.clear();
	m_RegionMap.clear();
	m_includedPoint.clear();

	m_solver = new NeAStarSolverImp();

	m_solver->setSpace(this);
}

NeSpaceImp::~NeSpaceImp()
{
	for (int i = 0;i < (int)m_regions.size();i ++)
	{
		delete (NeRegionImp*)m_regions[i];
		m_regions[i] = NULL;
	}
	m_RegionMap.clear();

	delete (NeAStarSolverImp*)m_solver;
	m_solver = NULL;

	m_precomputePOVCallback = NULL;
}

NeRegion* NeSpaceImp::createRegion(int RegionId)
{
	NeRegion* tmpRegion = new NeRegionImp(this);
	assert(tmpRegion);
	if(tmpRegion)
	{
		tmpRegion->setID(RegionId);
		m_regions.push_back(tmpRegion);
		m_RegionMap.insert(std::make_pair(RegionId,tmpRegion));
		return tmpRegion;
	}
	return NULL;
}

bool NeSpaceImp::removeRegion( NeRegion* region )
{
	if(region)
	{
		std::vector<NeRegion*>::iterator iter;
		iter = find(m_regions.begin(),m_regions.end(),region);
        if(m_regions.end() != iter)
		{
			delete (NeRegionImp*)(*iter);
			(*iter) = NULL;
			m_regions.erase(iter);
			return true;
		}
	}
	return false;
}

const NeRegion* NeSpaceImp::getRegionByIndex(int regionIndex) const
{
	assert((int)m_regions.size() > regionIndex && "Region 索引有误");

	return m_regions[regionIndex];
}

NeRegion* NeSpaceImp::getRegionByIndex(int regionIndex)
{
	assert((int)m_regions.size() > regionIndex && "Region 索引有误");

	return m_regions[regionIndex];
}

const NeRegion* NeSpaceImp::getRegionByID( int regionID ) const
{
	std::map<int,NeRegion*>::const_iterator iter=m_RegionMap.find(regionID);
	if(iter != m_RegionMap.end())
	{
		return iter->second;
	}
	return NULL;	
}

NeRegion* NeSpaceImp::getRegionByID( int regionID )
{
	std::map<int,NeRegion*>::iterator iter=m_RegionMap.find(regionID);
	if(iter != m_RegionMap.end())
	{
		return iter->second;
	}
	return NULL;
}

int NeSpaceImp::getNumRegions() const
{
	return (int)m_regions.size();
}




void NeSpaceImp::precomputePointsOfVisibility()
{
	/*
	*	以下做可视点预处理的主迭代
	*/
	for (int i = 0;i < (int)m_regions.size();i ++)
	{
		NeRegion* tmpRegion = m_regions[i];

		if(NULL != m_precomputePOVCallback)
			m_precomputePOVCallback->onPrecomputePOV(this,tmpRegion);

		linkRegionEdge(*tmpRegion);

		linkPOVSelf(tmpRegion);

		for (int j = 0;j < (int)tmpRegion->getNumPointsOfVisibility();j ++)
		{

			NeVisibilityPoints* tmpCurrentVP = tmpRegion->getPointOfVisibility(j);


			if(!verifyPOVValidity(tmpCurrentVP))
				continue;

			for (int m = 0;m < (int)m_regions.size();m ++)
			{
				NeRegion* tmpTargetRegion = m_regions[m];

				if (tmpTargetRegion->getID() != tmpRegion->getID())
				{

					if(isCurrentPointInTargetRegionAABB(*tmpCurrentVP,*tmpTargetRegion))
						linkPointsOfVisibilityComplete(*tmpCurrentVP,*tmpTargetRegion);
					else
						linkPointsOfVisibilityOptimal(*tmpCurrentVP,*tmpTargetRegion);
				}
			}
		}
	}
}

bool NeSpaceImp::checkCrossForPrecomputePOV(const NeVisibilityPoints* startPoint,
										const NeVisibilityPoints* targetPoint )
{
	bool isCross = false;

	for (int i = 0;i < (int)m_regions.size();i ++)
	{
		NeRegion* tmpRegion = m_regions[i];
		
		assert (NULL!=tmpRegion && "Region为空");
		
		NeVector3 fvmStart = startPoint->m_position;
		NeVector3 fvmEnd   = targetPoint->m_position;

		if(!isLineSegmentIntersectAABBOfRegion(fvmStart,fvmEnd,tmpRegion))
			continue;

		for(int i = 0;i < tmpRegion->getNumPointsOfVisibility();i ++)
		{	
			int tmpIndex = i;

			tmpIndex = tmpIndex % tmpRegion->getNumPointsOfVisibility();
			const NeVisibilityPoints* fv0 = tmpRegion->getPointOfVisibility(tmpIndex);

			++ tmpIndex;

			tmpIndex = tmpIndex % tmpRegion->getNumPointsOfVisibility();
			const NeVisibilityPoints* fv1 = tmpRegion->getPointOfVisibility(tmpIndex);

			if(!(startPoint == fv0 || startPoint == fv1 || targetPoint == fv0 || targetPoint == fv1))
			{
				if(CheckCross(fvmStart,fvmEnd,fv0->m_position,fv1->m_position))
				{
					return true;
				}
			}
		}
	}
	return isCross;
}

void NeSpaceImp::linkPointsOfVisibilityComplete( NeVisibilityPoints& currentPoint, 
											NeRegion& targetRegion )
{
	for (int n = 0;n < (int)targetRegion.getNumPointsOfVisibility();n ++)
	{
		NeVisibilityPoints* tmpTargetVP = targetRegion.getPointOfVisibility(n);


		if(!verifyPOVValidity(tmpTargetVP))
			continue;

		if(!checkCrossForPrecomputePOV(&currentPoint,tmpTargetVP))
			currentPoint.m_visibilityPointsList.push_back(tmpTargetVP);
	}
}

void NeSpaceImp::linkPointsOfVisibilityOptimal( NeVisibilityPoints& currentPoint,
										   NeRegion& targetRegion )
{
	if(0 == targetRegion.getNumPointsOfVisibility())
		return;

	const NeVisibilityPoints* tmpBeginSP = NULL;
	for (int i = 0;i < (int)targetRegion.getNumPointsOfVisibility();i ++)
	{
		const NeVisibilityPoints* tmpSP = targetRegion.getPointOfVisibility(i);
		if(/*!isPointInOtherRegion(tmpSP)*/verifyPOVValidity(tmpSP) && 
			!checkCrossForPrecomputePOV(&currentPoint,tmpSP))
		{
			tmpBeginSP = tmpSP;
			break;
		}
	}

	if(NULL == tmpBeginSP)
		return;

	const NeVisibilityPoints* tmpLeftSP = tmpBeginSP;
	const NeVisibilityPoints* tmpRightSP =tmpBeginSP;
	//float	tmpLeftAngle = 0.0f;
	//float   tmpRightAngle = 0.0f;
	std::map<float,const NeVisibilityPoints*> tmpLeftSPList;
	std::map<float,const NeVisibilityPoints*> tmpRightSPList;

	NeVector3 tmpStartPoint= NeVector3(currentPoint.m_position.getX(),0.0f,currentPoint.m_position.getZ());
	NeVector3 tmpTargetPoint = NeVector3(tmpBeginSP->m_position.getX(),0.0f,tmpBeginSP->m_position.getZ());
	NeVector3 tmpVec = tmpTargetPoint - tmpStartPoint;
	tmpVec = normalize(tmpVec);

	NeVector3 tmpYVec = NeVector3(0.0f,1.0f,0.0f);

	for (int i = 0;i < targetRegion.getNumPointsOfVisibility();i ++)
	{
		const NeVisibilityPoints* tmpVP = targetRegion.getPointOfVisibility(i);

		if(!verifyPOVValidity(tmpVP))
			continue;

		if(tmpBeginSP != tmpVP)
		{
			NeVector3 tmpVerifyingPoint = NeVector3(tmpVP->m_position.getX(),0.0f,tmpVP->m_position.getZ());
			NeVector3 tmpVerifyingVec = tmpVerifyingPoint - tmpStartPoint;
			tmpVerifyingVec = normalize(tmpVerifyingVec);
			float tmpAngle = acosf(dot(tmpVerifyingVec,tmpVec));

			NeVector3 tmpCrossVec = cross(tmpVec,tmpVerifyingVec);

			float tmpScale = dot(tmpCrossVec,tmpYVec);


			if (tmpScale > 0.0f)
				tmpLeftSPList.insert(std::map<float,const NeVisibilityPoints*>::value_type(tmpAngle,tmpVP));
			else
				tmpRightSPList.insert(std::map<float,const NeVisibilityPoints*>::value_type(tmpAngle,tmpVP));
		}
	}

	std::map<float,const NeVisibilityPoints*>::reverse_iterator riter;

	for (riter = tmpLeftSPList.rbegin();riter != tmpLeftSPList.rend();riter ++)
	{
		const NeVisibilityPoints* tmpSP = riter->second;

		if(/*!isPointInOtherRegion(tmpSP) && */!checkCrossForPrecomputePOV(&currentPoint,tmpSP))
		{
			tmpLeftSP = tmpSP;
			break;
		}
	}
	for (riter = tmpRightSPList.rbegin();riter != tmpRightSPList.rend();riter ++)
	{
		const NeVisibilityPoints* tmpSP = riter->second;

		if(/*!isPointInOtherRegion(tmpSP) && */!checkCrossForPrecomputePOV(&currentPoint,tmpSP))
		{
			tmpRightSP = tmpSP;
			break;
		}
	}


	if(NULL != tmpLeftSP)
		currentPoint.m_visibilityPointsList.push_back(tmpLeftSP);

	if (NULL != tmpRightSP)
		currentPoint.m_visibilityPointsList.push_back(tmpRightSP);

}

bool NeSpaceImp::isCurrentPointInTargetRegionAABB( const NeVisibilityPoints& point,const NeRegion& targetRegion )
{
	const NeAxisAlignedBoundingBox& tmpAABB = targetRegion.getLocalAABB();
	NeVector3 tmpMin = tmpAABB.getMinimum();
	NeVector3 tmpMax = tmpAABB.getMaximum();
	NeVector3 tmpRegionPos =  targetRegion.getPosition();
	float tmpX = point.m_position.getX() - tmpRegionPos.getX();
	float tmpZ = point.m_position.getZ() - tmpRegionPos.getZ();

	if((tmpX < tmpMax.getX()) && (tmpZ < tmpMax.getZ()) && (tmpX > tmpMin.getX()) && (tmpZ > tmpMin.getZ()))
		return true;

	return false;
}

bool NeSpaceImp::isCurrentPointInTargetRegion( const NeVisibilityPoints& point, const NeRegion& targetRegion )
{
	int iRegionPointSize = 0;

	int iInterSectCount  = 0;	// 射线和直线的相交个数。

	NeVector3 f1s; 
	NeVector3 f1e; 

	NeVector3 f2s; 
	NeVector3 f2e; 

	f2s = /*fvTarget*/point.m_position;
	f2e.setZ(f2s.getZ());
	f2e.setX(1512.0f);

	const NeRegion &cr = targetRegion;

	iInterSectCount = 0;
	// 从区域中找到一条直线.
	iRegionPointSize = (int)cr.getNumPointsOfVisibility();
	for(int j = 0; j < iRegionPointSize; j++)
	{
		if((iRegionPointSize - 1) == j)
		{
			f1s = cr.getPointOfVisibility(j)->m_position;
			f1e = cr.getPointOfVisibility(0)->m_position;
		}
		else
		{
			f1s = cr.getPointOfVisibility(j)->m_position;
			f1e = cr.getPointOfVisibility(j + 1)->m_position;
		}

		// 检测直线是否与当前的路线相交.
		if(CheckCross(f2s, f2e, f1s, f1e))
		{
			iInterSectCount++;
		}
	}

	if(iInterSectCount % 2)
		return true;

	return false;

}

void NeSpaceImp::linkRegionEdge(NeRegion& region )
{
	for(int i = 0;i < (int)region.getNumPointsOfVisibility();i ++)
	{
		NeVisibilityPoints* tmpCurrentVP = region.getPointOfVisibility(i);

		//bool isIncluded = isPointInOtherRegion(tmpCurrentVP);
		if(/*isIncluded*/!verifyPOVValidity(tmpCurrentVP))
			continue;

		NeVisibilityPoints* tmpUponVP1 = NULL;
		NeVisibilityPoints* tmpUponVP2 = NULL;

		if (0 == i)
		{
			tmpUponVP1 = region.getPointOfVisibility(region.getNumPointsOfVisibility() - 1);
			tmpUponVP2 = region.getPointOfVisibility(i + 1);
		} 
		else if (region.getNumPointsOfVisibility() - 1 == i)
		{
			tmpUponVP1 = region.getPointOfVisibility(i - 1);
			tmpUponVP2 = region.getPointOfVisibility(0);
		}
		else
		{
			tmpUponVP1 = region.getPointOfVisibility(i - 1);
			tmpUponVP2 = region.getPointOfVisibility(i + 1);
		}

		//bool isIncluded1 = isPointInOtherRegion(tmpUponVP1);
		//bool isIncluded2 = isPointInOtherRegion(tmpUponVP2);
		bool isCross1 = false;
		bool isCross2 = false;

		if(/*!isIncluded1*/verifyPOVValidity(tmpUponVP1))
		{
			isCross1 = checkCrossForPrecomputePOV(tmpCurrentVP,tmpUponVP1);
			if(!isCross1)
				tmpCurrentVP->m_visibilityPointsList.push_back(tmpUponVP1);
		}
		if(/*!isIncluded2*/verifyPOVValidity(tmpUponVP2))
		{		
			isCross2 = checkCrossForPrecomputePOV(tmpCurrentVP,tmpUponVP2);
			if(!isCross2)
				tmpCurrentVP->m_visibilityPointsList.push_back(tmpUponVP2);
		}
	}
}

bool NeSpaceImp::isPointInOtherRegion(const NeVisibilityPoints* point )
{
	std::vector<const NeVisibilityPoints*>::iterator iter;
	iter = std::find(m_includedPoint.begin(),m_includedPoint.end(),point);
	if(m_includedPoint.end() != iter)
		return true;

	return false;
}

void NeSpaceImp::precomputeForEliminatingIncludedPoint()
{
	for (int i = 0;i < (int)m_regions.size();i ++)
	{
		NeRegion* tmpRegion = m_regions[i];

		for (int j = 0;j < (int)tmpRegion->getNumPointsOfVisibility();j ++)
		{
			NeVisibilityPoints* tmpCurrentVP = tmpRegion->getPointOfVisibility(j);

			for (int m = 0;m < (int)m_regions.size();m ++)
			{
				NeRegion* tmpTargetRegion = m_regions[m];

				if (tmpTargetRegion->getID() == tmpRegion->getID())
					continue;
				if(!isCurrentPointInTargetRegionAABB(*tmpCurrentVP,*tmpTargetRegion))
					continue;
				if(isCurrentPointInTargetRegion(*tmpCurrentVP,*tmpTargetRegion))
					m_includedPoint.push_back(tmpCurrentVP);
			}
		}
	}
}


bool NeSpaceImp::CheckCross( const NeVector3& fvMS, const NeVector3& fvME,const NeVector3& fvNS, const NeVector3& fvNE )
{
	if ( max(fvMS.getX(),fvME.getX()) <= min(fvNS.getX(),fvNE.getX()) )
	{
		return false;
	}
	if ( min(fvMS.getX(),fvME.getX()) >= max(fvNS.getX(),fvNE.getX()) )
	{
		return false;
	}
	if ( max(fvMS.getZ(),fvME.getZ()) <= min(fvNS.getZ(),fvNE.getZ()) )
	{
		return false;
	}
	if ( min(fvMS.getZ(),fvME.getZ()) >= max(fvNS.getZ(),fvNE.getZ()) )
	{
		return false;
	}

	float temp1 = fvMulti(fvSub(fvMS,fvNS),fvSub(fvNE,fvNS)) * fvMulti( fvSub(fvNE,fvNS),fvSub(fvME,fvNS));
	float temp2 = fvMulti(fvSub(fvNS,fvMS),fvSub(fvME,fvMS)) * fvMulti( fvSub(fvME,fvMS),fvSub(fvNE,fvMS));

	if((temp1>=0)&&(temp2>=0))
	{
		return true;
	}
	return false;	
}

bool NeSpaceImp::fvEuqual( const NeVector3& fv1, const NeVector3& fv2 )
{
	if ((abs(fv1.getX()-fv2.getX())<1e-10) &&(abs(fv1.getZ()-fv2.getZ())<1e-10))
	{
		return true;
	}
	return false;
}

NeVector3 NeSpaceImp::fvSub( const NeVector3& fv1, const NeVector3& fv2 )
{
	NeVector3 fvResult = NeVector3(fv1.getX()-fv2.getX(),0.0f,fv1.getZ()-fv2.getZ());
	return fvResult;
}

float NeSpaceImp::fvMulti( const NeVector3& fv1, const NeVector3& fv2 )
{
	return (fv1.getX()*fv2.getZ() - fv1.getZ()*fv2.getX());

}

const NeSolver* NeSpaceImp::getSolver() const
{
	return m_solver;
}

/*
 *	采用分离轴理论进行线段与轴向对齐包围盒的相交检测
 */
bool NeSpaceImp::isLineSegmentIntersectAABBOfRegion( const NeVector3& point1,const NeVector3& point2, 
													const NeRegion* region )
{
	NeAxisAlignedBoundingBox tmpAABB = region->getLocalAABB();
	const NeVector3& tmpExtents = tmpAABB.getMaximum();
	float hX = tmpExtents.getX();
	float hZ = tmpExtents.getZ();

	NeVector3 tmpPoint1Local = point1 - region->getPosition(); 
	NeVector3 tmpPoint2Local = point2 - region->getPosition();

	float p1X = tmpPoint1Local.getX();
	float p1Z = tmpPoint1Local.getZ();
	float p2X = tmpPoint2Local.getX();
	float p2Z = tmpPoint2Local.getZ();

	float minX = p1X < p2X ? p1X : p2X;
	float minZ = p1Z < p2Z ? p1Z : p2Z;
	float maxX = p1X < p2X ? p2X : p1X;
	float maxZ = p1Z < p2Z ? p2Z : p1Z;

	float tmpXDifferenceHalf = (maxX - minX) * 0.5f;
	float tmpZDifferenceHalf = (maxZ - minZ) * 0.5f;

	NeVector3 tmpC = NeVector3(minX + tmpXDifferenceHalf,0.0f,minZ + tmpZDifferenceHalf);

	if(abs(tmpC.getX()) > abs(hX) + abs(tmpXDifferenceHalf))
		return false;
	if(abs(tmpC.getZ()) > abs(hZ) + abs(tmpZDifferenceHalf))
		return false;

	/*
	 *	线段方向矢量与Y轴叉积得到的矢量A,如果|原点到线段中点的矢量 点积 A| > 原点到(hx,hy,hz)的矢量 点积 
	 *	(|A.x|,|A.y|,|A.z|)  则不相交
	 */
	NeVector3 tmpW = NeMath::normalize(tmpPoint1Local - tmpPoint2Local);

	NeVector3 tmpA = NeMath::normalize(NeMath::cross(tmpW,NeVector3::yAxis()));

	float tmpScalar1 = abs(NeMath::dot(tmpC,tmpA));

	tmpA = NeVector3(abs(tmpA.getX()),0.0f,abs(tmpA.getZ()));

	NeVector3 tmpBoxVec = NeVector3(hX,0.0f,hZ);

	float tmpScalar2 = abs(NeMath::dot(tmpBoxVec,tmpA));

	if(tmpScalar1 > tmpScalar2)
		return false;

	return true;
}

NeVisibilityPoints* NeSpaceImp::createPathNode( NeRegion* region,const NeVector3& position )
{
	NeVisibilityPoints* povPathNode = new NeAStarNodeImp();

	povPathNode->m_position = position;
	povPathNode->m_belongRegionID = region->getID();
	povPathNode->m_ID = region->getNumPointsOfVisibility();
	povPathNode->m_globalHandle = m_currentPathNodeGlobalHandle;

	m_currentPathNodeGlobalHandle ++;

	return povPathNode;
}

void NeSpaceImp::linkPOVSelf( NeRegion* region )
{
	NeInt numPovs = region->getNumPointsOfVisibility();

	if(0 == numPovs)
		return;

	NeVisibilityPoints* povISubOne = NULL;
	NeVisibilityPoints* povI = NULL;
	NeVisibilityPoints* povIAddOne = NULL;

	for (int i = 1;i <= numPovs;i ++)
	{
		int povIndex = i - 1;

		povIndex = povIndex % numPovs;

		povISubOne = region->getPointOfVisibility(povIndex);

		povIndex = i % numPovs;

		povI = region->getPointOfVisibility(povIndex);

		povIndex = i + 1;

		povIndex = povIndex % numPovs;

		povIAddOne = region->getPointOfVisibility(povIndex);


		/*bool isIncluded = isPointInOtherRegion(povI);
		if(isIncluded)
			continue;

		if(!povI->m_isConvex)
			continue;*/

		if(!verifyPOVValidity(povI))
			continue;

		for (int j = 0;j < numPovs;j ++)
		{
			NeVisibilityPoints* targetPathNode = region->getPointOfVisibility(j);

			if( (povI == targetPathNode) ||  
				!verifyPOVValidity(targetPathNode) ||
				(targetPathNode == povISubOne) || 
				(targetPathNode == povIAddOne) 
			   )
				continue;
			
			NeVisibilityPoints currentPathNodeModify;

			currentPathNodeModify.m_position = povI->m_position + 
				povI->m_vertexNormal * 0.1f;

			NeVisibilityPoints targetPathNodeModify;
		
			targetPathNodeModify.m_position = targetPathNode->m_position +
				targetPathNode->m_vertexNormal * 0.1f;

			if(!checkCrossForPrecomputePOV(&currentPathNodeModify,&targetPathNodeModify))
				povI->m_visibilityPointsList.push_back(targetPathNode);

		}
	}
}

bool NeSpaceImp::verifyPOVValidity( const NeVisibilityPoints* point )
{
	if (isPointInOtherRegion(point) ||
		!point->m_isConvex)
		return false;

	return true;
}

bool NeSpaceImp::isCurrentPointInOtherRegion( const NeVisibilityPoints* pov, NeReal extendScalar /*= 0.3f*/ )
{
	for (int m = 0;m < (int)m_regions.size();m ++)
	{
		NeRegion* tmpTargetRegion = m_regions[m];

		
		if(!isCurrentPointInTargetRegionAABB(*pov,*tmpTargetRegion))
			continue;
		if(isCurrentPointInTargetRegion(*pov,*tmpTargetRegion))
			return true;
	}

	return false;
}

NePrecomputePOVCallback* NeSpaceImp::getPrecomputePOVCallback() const
{
	return m_precomputePOVCallback;
}

void NeSpaceImp::setPrecomputePOVCallback( NePrecomputePOVCallback* callback )
{
	m_precomputePOVCallback = callback;
}

} // namespace Orphigine