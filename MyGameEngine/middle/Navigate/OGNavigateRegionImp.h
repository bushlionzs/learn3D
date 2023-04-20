#ifndef NeRegionImp_h__
#define NeRegionImp_h__

#include "OGNavigateRegion.h"
#include "OGNavigateAxisAlignedBoundingBox.h"
#include <vector>

namespace Orphigine 
{

class NeSpace;

class NeRegionImp : public NeRegion
{
public:
	NeRegionImp(NeSpace* parent);
	virtual ~NeRegionImp();

	NeSpace*									getParent() const;

	void										setParent(NeSpace* val);

	virtual  const NeVector3&					getPosition() const; 
	
	virtual	 int								getID() const;

	virtual	 void								setID(int id);

	virtual  void								addPointOfVisibility(const NeVector3& position);

	virtual	 const NeVisibilityPoints*			getPointOfVisibility(int index) const;

	virtual	 NeVisibilityPoints*				getPointOfVisibility(int index);

	virtual int									getNumPointsOfVisibility() const;

	virtual const NeAxisAlignedBoundingBox&		getLocalAABB() const;
	
	virtual void								updateAABB();

	virtual void								extending(NeReal scale);

	virtual void								computeSurfaceNormal();

	virtual void								computeVerticesNormal();

	virtual void								computeConvexVertices();

protected:
	NeSpace*									m_parent;
	std::vector<NeVisibilityPoints*>			m_vfPoints;
	int											m_ID;
	NeAxisAlignedBoundingBox					m_localAABB;
	NeVector3									m_position;
	NeVector3									m_normal;
private:
};

} // namespace Orphigine

#endif // NeRegionImp_h__