#ifndef NeRegion_h__
#define NeRegion_h__

#include "OGNavigateUtil.h"
#include <vector>

namespace Orphigine 
{

class NeVisibilityPoints //  临时结构，暴露实现，需替换成抽象类
{
public:
	NeVisibilityPoints()
	{
		m_position = NeVector3(0.0f,0.0f,0.0f);
		m_vertexNormal = NeVector3(0.0f,0.0f,0.0f);
		m_belongRegionID = -1;
		m_ID = -1;
		m_globalHandle = -1;
		m_visibilityPointsList.clear();
		m_isConvex = true;
	}

	virtual ~NeVisibilityPoints()
	{
		m_visibilityPointsList.clear();
	}

	NeVisibilityPoints& operator = (const NeVisibilityPoints& rhs)
	{
		m_position = rhs.m_position;
		m_vertexNormal = rhs.m_vertexNormal;
		m_belongRegionID = rhs.m_belongRegionID;
		m_ID = rhs.m_ID;
		m_globalHandle = rhs.m_globalHandle;
		m_visibilityPointsList = rhs.m_visibilityPointsList;
		m_isConvex = rhs.m_isConvex;
	}

	NeVector3								m_position;
	NeVector3								m_vertexNormal;
	NeInt									m_belongRegionID;
	NeInt									m_ID;
	NeUInt									m_globalHandle;
	std::vector<const NeVisibilityPoints*>	m_visibilityPointsList;
	NeBool									m_isConvex;
protected:

};

class NeAxisAlignedBoundingBox;

class NeRegion
{
public:
	//************************************
	// Brief:	  得到位置信息
	// Method:    getPosition
	// FullName:  NeRegion::getPosition
	// Access:    virtual public 
	// Returns:   const NeVector3&
	//************************************
	virtual  const NeVector3&					getPosition() const = 0; 

	//************************************
	// Brief:	  得到ID
	// Method:    getID
	// FullName:  NeRegion::getID
	// Access:    virtual public 
	// Returns:   int
	//************************************
	virtual	 int								getID() const = 0;

	//************************************
	// Brief:	  设置ID
	// Method:    setID
	// FullName:  NeRegion::setID
	// Access:    virtual public 
	// Returns:   void
	// Parameter: int id
	//************************************
	virtual	 void								setID(int id) = 0;

	//************************************
	// Brief:	  包裹可视点
	// Method:    addPointOfVisibility
	// FullName:  NeRegion::addPointOfVisibility
	// Access:    virtual public 
	// Returns:   void
	// Parameter: const NeVisibilityPoints & point
	//************************************
	
	virtual  void								addPointOfVisibility(const NeVector3& position) = 0;
	//************************************
	// Brief:	  得到被包裹的可视点（不可修改版)
	// Method:    getPointOfVisibility
	// FullName:  NeRegion::getPointOfVisibility
	// Access:    virtual public 
	// Returns:   const NeVisibilityPoints*
	// Parameter: int index
	//************************************
	virtual	 const NeVisibilityPoints*			getPointOfVisibility(int index) const = 0;
	//************************************
	// Brief:	  得到被包裹的可视点(可修改版)
	// Method:    getPointOfVisibility
	// FullName:  NeRegion::getPointOfVisibility
	// Access:    virtual public 
	// Returns:   NeVisibilityPoints*
	// Parameter: int index
	//************************************
	virtual	 NeVisibilityPoints*				getPointOfVisibility(int index) = 0;

	//************************************
	// Brief:	  得到可视点数目
	// Method:    getNumPointsOfVisibility
	// FullName:  NeRegion::getNumPointsOfVisibility
	// Access:    virtual public 
	// Returns:   int
	//************************************
	virtual int									getNumPointsOfVisibility() const = 0;

	//************************************
	// Brief:	  得到局部坐标系轴向对齐包围盒
	// Method:    getLocalAABB
	// FullName:  NeRegion::getLocalAABB
	// Access:    virtual public 
	// Returns:   const NeAxisAlignedBoundingBox&
	//************************************
	virtual const NeAxisAlignedBoundingBox&		getLocalAABB() const = 0;

	//************************************
	// Brief:	  更新坐标系轴向对齐包围盒
	// Method:    updateAABB
	// FullName:  NeRegion::updateAABB
	// Access:    virtual public 
	// Returns:   void
	//************************************
	virtual void								updateAABB() = 0;

	virtual void								extending(NeReal scale) = 0;

	virtual void								computeSurfaceNormal() = 0;

	virtual void								computeVerticesNormal() = 0;

	virtual void								computeConvexVertices() = 0;
protected:
	NeRegion() {}
	virtual ~NeRegion() {}
};

} // namespace Orphigine

#endif // NeRegion_h__