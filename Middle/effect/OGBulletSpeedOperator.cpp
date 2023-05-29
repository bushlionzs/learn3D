#include "OgreHeader.h"
#include "OGBulletSpeedOperator.h"
#include "OGBulletEventSystem.h"
#include "OGBulletSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreMath.h"

namespace Orphigine
{

	BulletSpeedOperator::CmdMode BulletSpeedOperator::ms_modeCmd;
	BulletSpeedOperator::CmdDirection BulletSpeedOperator::ms_directionCmd;
	BulletSpeedOperator::CmdSpeed BulletSpeedOperator::ms_speedCmd;

	BulletSpeedOperator::BulletSpeedOperator( BulletEventSystem* eventSystem )
	{
		m_type = "speed";
		m_parent = eventSystem;
		m_mode = "direction";
		m_direction = Ogre::Vector3(0.0f,1.0f,0.0f);
		m_speed = 0.0f;
		m_isOperated = false;

		if(createParamDictionary("SpeedOperatorDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();
			tmpDict->addParameter(Ogre::ParameterDef(
				"mode","Affector speed mode",Ogre::PT_STRING),
				&ms_modeCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"direction","The direction of velocity",Ogre::PT_VECTOR3),
				&ms_directionCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"speed","The lenght of velocity",Ogre::PT_REAL),
				&ms_speedCmd);
		}
	}

	BulletSpeedOperator::~BulletSpeedOperator()
	{

	}

	const String& BulletSpeedOperator::getMode() const
	{
		return m_mode;
	}

	void BulletSpeedOperator::setMode( const String& val )
	{
		m_mode = val;
	}

	const Ogre::Vector3& BulletSpeedOperator::getDirection() const
	{
		return m_direction;
	}

	void BulletSpeedOperator::setDirection( const Ogre::Vector3& val )
	{
		m_direction = val;
	}

	const Real& BulletSpeedOperator::getSpeed() const
	{
		return m_speed;
	}

	void BulletSpeedOperator::setSpeed( const Real& val )
	{
		m_speed = val;
	}

	void BulletSpeedOperator::operateBulletEventSystem(Real timeElapsed)
	{
		/*if(m_isOperated)
			return;*/

		std::vector<BulletSystem*>* tmpActiveBulletSystems = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;
		
		for (iter = tmpActiveBulletSystems->begin();iter != tmpActiveBulletSystems->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);

			Ogre::Radian tmpAngle = Ogre::Radian(0.785f);
			Ogre::Vector3 tmpDir = m_direction.randomDeviant(tmpAngle);

			Ogre::Vector3 tmpVelocity = m_speed * tmpDir;

			tmpBulletSystem->setVelocityWorld(tmpVelocity);
		}

		//m_isOperated = true;
	}

	Ogre::String BulletSpeedOperator::CmdMode::doGet( const void* target ) const
	{
		return static_cast<const BulletSpeedOperator*>(target)->getMode();
	}

	void BulletSpeedOperator::CmdMode::doSet( void* target, const String& val )
	{
		static_cast<BulletSpeedOperator*>(target)->setMode(val);
	}

	Ogre::String BulletSpeedOperator::CmdDirection::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSpeedOperator*>(target)->getDirection());
	}

	void BulletSpeedOperator::CmdDirection::doSet( void* target, const String& val )
	{
		static_cast<BulletSpeedOperator*>(target)->setDirection(
			Ogre::StringConverter::parseVector3(val));
	}

	Ogre::String BulletSpeedOperator::CmdSpeed::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSpeedOperator*>(target)->getSpeed());
	}

	void BulletSpeedOperator::CmdSpeed::doSet( void* target, const String& val )
	{
		static_cast<BulletSpeedOperator*>(target)->setSpeed(
			Ogre::StringConverter::parseReal(val));
	}
}