#include "OgreHeader.h"
#include "OGPhySphereShape.h"
#include "OgreStringConverter.h"

namespace Orphigine
{
	PhySphereShape::CmdRadius			PhySphereShape::ms_radiusCmd;

	PhySphereShape::PhySphereShape( Real radius )
		: PhyShape("SphereShape")
		, m_radius(radius)
	{
		if (_initBaseAttribute("PhySphereShape"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("Radius","The radius of sphere shape",Ogre::PT_REAL),
				&ms_radiusCmd);
		}
	}

	PhySphereShape::~PhySphereShape()
	{
		
	}

	Real PhySphereShape::getRadius() const
	{
		return m_radius;
	}

	void PhySphereShape::setRadius(Real val )
	{
		m_radius = val;
	}
	

	Ogre::String PhySphereShape::CmdRadius::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const PhySphereShape*>(target)->getRadius());
	}

	void PhySphereShape::CmdRadius::doSet( void* target, const String& val )
	{
		static_cast<PhySphereShape*>(target)->setRadius(
			Ogre::StringConverter::parseReal(val));
	}
}