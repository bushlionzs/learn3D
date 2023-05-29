#include "OgreHeader.h"
#include "OGBulletSystemElement.h"

#include "OgreStringConverter.h"

namespace Orphigine
{

	BulletSystemElement::CmdOffsetPos					BulletSystemElement::ms_offsetPosCmd;
	BulletSystemElement::CmdOffsetRotation				BulletSystemElement::ms_offsetRotationCmd;

	BulletSystemElement::BulletSystemElement(const String& typeName)
		: m_typeName(typeName)
		, m_sceneNode(NULL)
		,m_offsetPosition( Ogre::Vector3::ZERO)
		,m_offsetQuaternion(Ogre::Quaternion::IDENTITY)
	{
	}

	BulletSystemElement::~BulletSystemElement()
	{

	}

	bool BulletSystemElement::_initParameters( const String& typeName )
	{
		if (createParamDictionary(typeName + "Dict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef("OffsetPostion","The offset position of effect",Ogre::PT_VECTOR3),
				&ms_offsetPosCmd);

			tmpDict->addParameter(Ogre::ParameterDef("OffsetRotation","The offset rotation of effect",Ogre::PT_QUATERNION),
				&ms_offsetRotationCmd);

			return true;
		}
		return false;
	}

	const Ogre::Vector3& BulletSystemElement::getOffsetPosition() const
	{
		return m_offsetPosition;
	}

	void BulletSystemElement::setOffsetPosition( const Ogre::Vector3& val )
	{
		m_offsetPosition = val;
	}

	const Ogre::Quaternion& BulletSystemElement::getOffsetQuaternion() const
	{
		return m_offsetQuaternion;
	}

	void BulletSystemElement::setOffsetQuaternion( const Ogre::Quaternion& val )
	{
		m_offsetQuaternion = val;
	}
	
	Ogre::String BulletSystemElement::CmdOffsetPos::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemElement*>(target)->getOffsetPosition());
	}

	void BulletSystemElement::CmdOffsetPos::doSet( void* target, const String& val )
	{
		static_cast<BulletSystemElement*>(target)->setOffsetPosition(
			Ogre::StringConverter::parseVector3(val));
	}

	Ogre::String BulletSystemElement::CmdOffsetRotation::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemElement*>(target)->getOffsetQuaternion());
	}

	void BulletSystemElement::CmdOffsetRotation::doSet( void* target, const String& val )
	{
		static_cast<BulletSystemElement*>(target)->setOffsetQuaternion(
			Ogre::StringConverter::parseQuaternion(val));
	}
}