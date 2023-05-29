#ifndef NeSpaceImp_h__
#define NeSpaceImp_h__

#include "OGNavigateSpace.h"
#include "OGNavigateRegion.h"

#include <vector>
#include <map>

namespace Orphigine 
{

class NeSolver;
class NeAxisAlignedBoundingBox;
class NePrecomputePOVCallback;

class NeSpaceImp : public NeSpace
{
public:
	NeSpaceImp();
	virtual ~NeSpaceImp();
/*
 *	接口实现
 */

	/*
	*	创建一个Region
	*/
	virtual NeRegion*		createRegion(int RegionId);
	/*
	*	删除一个Region
	*/
	virtual bool			removeRegion(NeRegion* region);

	/*
	*	得到不可修改版本Region
	*/
	virtual const NeRegion* getRegionByIndex(int regionIndex) const;
	/*
	*	得到可修改版本Region
	*/
	virtual NeRegion*		getRegionByIndex(int regionIndex);

	virtual const NeRegion*	getRegionByID(int regionID) const;

	virtual NeRegion*		getRegionByID(int regionID);

	virtual int				getNumRegions() const;

	virtual const NeSolver*	getSolver()  const;


	virtual bool			checkCrossForPrecomputePOV(const NeVisibilityPoints* startPoint,
							const NeVisibilityPoints* targetPoint);
	/*
	*	完全版可视点连接算法
	*/
	virtual void			linkPointsOfVisibilityComplete(NeVisibilityPoints& currentPoint,
							NeRegion& targetRegion); 

	/*
	*	优化版可视点连接算法
	*/
	virtual void			linkPointsOfVisibilityOptimal(NeVisibilityPoints& currentPoint,
							NeRegion& targetRegion);

	//linkPointsOfVisibilityOptimal

	virtual bool			isCurrentPointInTargetRegionAABB(const NeVisibilityPoints& point,
							const NeRegion& targetRegion);

	virtual bool			isCurrentPointInTargetRegion(const NeVisibilityPoints& point,
							const NeRegion& targetRegion);

	virtual bool			isCurrentPointInOtherRegion(const NeVisibilityPoints* pov,
							NeReal extendScalar = 0.3f);

	virtual bool			isPointInOtherRegion(const NeVisibilityPoints* point);

	virtual void			precomputePointsOfVisibility();

	virtual void			precomputeForEliminatingIncludedPoint();

	virtual NeVisibilityPoints*			createPathNode(NeRegion* region,const NeVector3& position);

	virtual NePrecomputePOVCallback*	getPrecomputePOVCallback() const;

	virtual void			setPrecomputePOVCallback(NePrecomputePOVCallback* callback);

	virtual bool			isLineSegmentIntersectAABBOfRegion(const NeVector3& point1,const NeVector3& point2,
								const NeRegion* region);
/*
*	非接口实现
*/
protected:
	void					linkRegionEdge(NeRegion& region);

	void					linkPOVSelf(NeRegion* region);

	bool					CheckCross(const NeVector3& fvMS, const NeVector3& fvME,const NeVector3& fvNS, const NeVector3& fvNE);

	bool					fvEuqual(const NeVector3& fv1, const NeVector3& fv2);

	NeVector3				fvSub(const NeVector3& fv1, const NeVector3& fv2);

	float					fvMulti(const NeVector3& fv1, const NeVector3& fv2);

	bool					verifyPOVValidity(const NeVisibilityPoints* point);
protected:
	//为提高载入速度，另外保存一个Map用于载入
	std::map<int,NeRegion*> 				m_RegionMap;
	std::vector<NeRegion*>					m_regions;
	std::vector<const NeVisibilityPoints*>	m_includedPoint;
	NeSolver*								m_solver;
	unsigned int							m_currentPathNodeGlobalHandle;
	NePrecomputePOVCallback*				m_precomputePOVCallback;
};

} // namespace Orphigine

#endif // NeSpaceImp_h__