#ifndef AxisAlignedBoundingBox_h__
#define AxisAlignedBoundingBox_h__

#include "OGNavigateutil.h"
 
namespace Orphigine 
{


class NeAxisAlignedBoundingBox
{
public:
	NeAxisAlignedBoundingBox()
	{
		setExtents(- 0.6f,- 0.6f,- 0.6f,0.6f,0.6f,0.6f);
	}

	NeAxisAlignedBoundingBox(const NeAxisAlignedBoundingBox& rhsBox)
	{
		m_minimum = rhsBox.m_minimum;
		m_maximum = rhsBox.m_maximum;
	}

	NeAxisAlignedBoundingBox(const NeVector3& min,
		const NeVector3& max)
	{
		setExtents(min,max);
	}

	const NeVector3&	getMinimum() const
	{
		return m_minimum;
	}

	void				setMinimum(const NeVector3& val)
	{
		m_minimum = val;
	}
	void				setMinimum(float minX,float minY,float minZ)
	{
		m_minimum.setX(minX);
		m_minimum.setY(minY);
		m_minimum.setZ(minZ);
	}

	const NeVector3&	getMaximum() const
	{
		return m_maximum;
	}
	void				setMaximum(const NeVector3& val)
	{
		m_maximum = val;
	}
	void				setMaximum(float maxX,float maxY,float maxZ)
	{
		m_maximum.setX(maxX);
		m_maximum.setY(maxY);
		m_maximum.setZ(maxZ);
	}

	void				setExtents(const NeVector3&  min,const NeVector3& max)
	{
		m_minimum = min;
		m_maximum = max;
	}

	void				setExtents(float minX,float minY,float minZ,float maxX,float maxY,float maxZ)
	{
		m_minimum.setX(minX);
		m_minimum.setY(minY);
		m_minimum.setZ(minZ);

		m_maximum.setX(maxX);
		m_maximum.setY(maxY);
		m_maximum.setZ(maxZ);
	}

	NeVector3			getCenter() const
	{
		NeVector3 tmpCenter;

		tmpCenter.setX((m_maximum.getX() - m_minimum.getX()) * 0.5f);
		tmpCenter.setY((m_maximum.getY() - m_minimum.getY()) * 0.5f);
		tmpCenter.setZ((m_maximum.getZ() - m_minimum.getZ()) * 0.5f);

		return tmpCenter;
	}

protected:
	NeVector3 m_minimum;
	NeVector3 m_maximum;

};

} // namespace Orphigine

#endif // AxisAlignedBoundingBox_h__