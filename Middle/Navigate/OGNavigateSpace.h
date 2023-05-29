#ifndef NeSpace_h__
#define NeSpace_h__

#include "OGNavigateUtil.h"

namespace Orphigine 
{


class NeRegion;
class NeVisibilityPoints;
class NeSolver;
class NeSpace;

class NePrecomputePOVCallback
{
public:
	virtual void	onPrecomputePOV(const NeSpace* currentSpace,
		const NeRegion* currentRegion) = 0;
};

class NeSpace
{
public:
	
	virtual NeRegion*		createRegion(int RegionId) = 0;

	virtual bool		removeRegion(NeRegion* region) = 0;

	virtual const NeRegion* getRegionByIndex(int regionIndex) const = 0;

	virtual NeRegion*		getRegionByIndex(int regionIndex) = 0;


	virtual const NeRegion*	getRegionByID(int regionID) const = 0;

	virtual NeRegion*		getRegionByID(int regionID) = 0;

	virtual int				getNumRegions() const = 0;


	virtual const NeSolver*	getSolver() const = 0;


	virtual bool			isCurrentPointInTargetRegionAABB(const NeVisibilityPoints& point,
		const NeRegion& targetRegion) = 0;

	virtual bool			isCurrentPointInTargetRegion(const NeVisibilityPoints& point,
		const NeRegion& targetRegion) = 0;

	virtual bool			isCurrentPointInOtherRegion(const NeVisibilityPoints* pov,
		NeReal extendScalar = 0.3f) = 0;

	virtual void			precomputePointsOfVisibility() = 0;

	//************************************
	// Brief:	  预计算为排除被包含的可视点
	// Method:    precomputeForEliminatingIncludedPoint
	// FullName:  NeSpace::precomputeForEliminatingIncludedPoint
	// Access:    virtual public 
	// Returns:   void
	//************************************
	virtual void			precomputeForEliminatingIncludedPoint() = 0;

	virtual bool			isLineSegmentIntersectAABBOfRegion(const NeVector3& point1,const NeVector3& point2,
								const NeRegion* region) = 0;

	virtual NePrecomputePOVCallback*	getPrecomputePOVCallback() const = 0;

	virtual void						setPrecomputePOVCallback(NePrecomputePOVCallback* callback) = 0;

protected:
	NeSpace(){}
	virtual ~NeSpace(){}
private:
};

} // namespace Orphigine

#endif // NeSpace_h__