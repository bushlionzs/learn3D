#include "OgreHeader.h"
#include "OGBulletCameraShakeOperator.h"
#include "OGBulletSystem.h"
#include "OGBulletEventSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreMath.h"
#include "OgreCamera.h"
#include "engine_manager.h"

namespace Orphigine
{

	BulletCameraShakeOperator::CmdAmplitude	BulletCameraShakeOperator::ms_amplitudeCmd;
	BulletCameraShakeOperator::CmdDuration	BulletCameraShakeOperator::ms_durationCmd;

	BulletCameraShakeOperator::BulletCameraShakeOperator( BulletEventSystem* eventSystem )
	{
		m_type = "camerashake";
		m_parent = eventSystem;

		m_amplitude = 0.0f;
		m_duration = 0.0f;
		m_age = 0.0f;
		m_isStart = false;

		if (createParamDictionary("CameraShakeDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("amplitude",
				"The amplitude of camera shake",
				Ogre::PT_REAL),
				&ms_amplitudeCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("duration",
				"The duration of camera shake",
				Ogre::PT_REAL),
				&ms_durationCmd);
		}
	}

	BulletCameraShakeOperator::~BulletCameraShakeOperator()
	{

	}

	void BulletCameraShakeOperator::operateBulletEventSystem(Real timeElapsed)
	{
		std::vector<BulletSystem*>* tmpNewTransferredBulletSystemList = m_parent->getNewTransferredBulletSystem();
		if(0 < (int)tmpNewTransferredBulletSystemList->size())
		{
			m_age = 0.0f; 
			m_isStart = true;
		}
		if (m_isStart)
		{
			if (m_age < m_duration)
			{
				Real tmpRandomAmplitude = Ogre::Math::RangeRandom(0.0f,m_amplitude);

				Ogre::Camera* tmpCamera = EngineManager::getSingletonPtr()->getMainCamera();

				Ogre::Vector3 tmpCameraEyePosition = tmpCamera->getDerivedPosition();
				tmpCameraEyePosition += Ogre::Vector3(tmpRandomAmplitude,tmpRandomAmplitude,tmpRandomAmplitude);

				EngineManager::getSingletonPtr()->setCameraPosition(tmpCameraEyePosition);

				m_amplitude = - m_amplitude;
			}
			else
				m_isStart = false;

			m_age += timeElapsed;
		}
		
	}

	Real Orphigine::BulletCameraShakeOperator::getAmplitude() const
	{
		return m_amplitude;
	}

	void BulletCameraShakeOperator::setAmplitude( const Real val )
	{
		m_amplitude = val;
	}

	Real BulletCameraShakeOperator::getDuration() const
	{
		return m_duration;
	}

	void BulletCameraShakeOperator::setDuration( const Real val )
	{
		m_duration = val;
	}

	
	Ogre::String BulletCameraShakeOperator::CmdAmplitude::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletCameraShakeOperator*>(target)->getAmplitude());
	}

	void BulletCameraShakeOperator::CmdAmplitude::doSet( void* target, const String& val )
	{
		static_cast<BulletCameraShakeOperator*>(target)->setAmplitude(
			Ogre::StringConverter::parseReal(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletCameraShakeOperator::CmdAmplitude::doCopy( void* target, const void* source )
	{
		static_cast<BulletCameraShakeOperator*>(target)->setAmplitude(
			static_cast<const BulletCameraShakeOperator*>(source)->getAmplitude());
	}
#endif

	Ogre::String BulletCameraShakeOperator::CmdDuration::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletCameraShakeOperator*>(target)->getDuration());
	}

	void BulletCameraShakeOperator::CmdDuration::doSet( void* target, const String& val )
	{
		static_cast<BulletCameraShakeOperator*>(target)->setDuration(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletCameraShakeOperator::CmdDuration::doCopy( void* target, const void* source )
	{
		static_cast<BulletCameraShakeOperator*>(target)->setDuration(
			static_cast<const BulletCameraShakeOperator*>(source)->getDuration());
	}
#endif
}
