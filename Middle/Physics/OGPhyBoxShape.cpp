#include "OgreHeader.h"
#include "OGPhyBoxShape.h"
#include "OgreStringConverter.h"

namespace Orphigine
{

	PhyBoxShape::CmdSize				PhyBoxShape::ms_size;

	PhyBoxShape::PhyBoxShape( const Ogre::Vector3& size )
		: PhyShape("BoxShape")
		, m_size(size)
	{
		if (_initBaseAttribute("PhyBoxShape"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("Size","The size of box shape",Ogre::PT_VECTOR3),
				&ms_size);
		}
	}

	PhyBoxShape::~PhyBoxShape()
	{
		
	}

	const Ogre::Vector3& PhyBoxShape::getSize() const
	{
		return m_size;
	}

	void PhyBoxShape::setSize( const Ogre::Vector3& val )
	{
		m_size = val;
	}

	Ogre::String PhyBoxShape::CmdSize::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const PhyBoxShape*>(target)->getSize());
	}

	void PhyBoxShape::CmdSize::doSet( void* target, const String& val )
	{
		static_cast<PhyBoxShape*>(target)->setSize(
			Ogre::StringConverter::parseVector3(val));
	}
}