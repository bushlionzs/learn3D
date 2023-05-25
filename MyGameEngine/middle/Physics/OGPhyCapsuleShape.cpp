#include "OgreHeader.h"
#include "OGPhyCapsuleShape.h"

namespace Orphigine
{
	PhyCapsuleShape::PhyCapsuleShape( Real radius ,Real height)
		: PhyShape("CapsuleShape")
		, m_radius(radius)
		, m_height(height)
	{
		if (_initBaseAttribute("PhyCapsuleShape"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();


		}
	}

	PhyCapsuleShape::~PhyCapsuleShape()
	{

	}

	Real PhyCapsuleShape::getRadius() const
	{
		return m_radius;
	}

	void PhyCapsuleShape::setRadius(Real val )
	{
		m_radius = val;
	}

	Real PhyCapsuleShape::getHeight() const
	{
		return m_height;
	}

	void PhyCapsuleShape::setHeight(Real val )
	{
		m_height = val;
	}

}