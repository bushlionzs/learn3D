#include "OgreHeader.h"
#include "OGBulletAgeTester.h"
#include "OGBulletSystem.h"
#include "OGBulletEventSystem.h"

#include "OgreStringConverter.h"

namespace Orphigine
{
	BulletAgeTester::CmdMaxTime				BulletAgeTester::ms_maxTimeCmd;
	BulletAgeTester::CmdIsUseEventAge		BulletAgeTester::ms_isUseEventAgeCmd;

	BulletAgeTester::BulletAgeTester( BulletEventSystem* eventSystem )
	{
		m_type = "age";
		m_parent = eventSystem;

		m_maxTime = 0.0f;
		m_isUseEventAge = true;

		if (initBaseParamters("age"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("maxtime",
				"If bulletsystem's age is greater than this paramter,then transition it to the next eventsystem",
				Ogre::PT_REAL),&ms_maxTimeCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("IsUseEventAge",
				"If false,this tester will use bulletsystem age",
				Ogre::PT_BOOL),&ms_isUseEventAgeCmd);
		}

	}

	BulletAgeTester::~BulletAgeTester()
	{

	}

	void BulletAgeTester::operateBulletEventSystem(Real timeElapsed)
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);

			if (m_isUseEventAge)
			{
				if(tmpBulletSystem->getEventAge() > m_maxTime)
					m_parent->addTransition(m_outputEventName,tmpBulletSystem);

			}
			else
			{
				if(tmpBulletSystem->getAge() > m_maxTime)
					m_parent->addTransition(m_outputEventName,tmpBulletSystem);
			}

		}
	}

	Real BulletAgeTester::getMaxTime() const
	{
		return m_maxTime;
	}

	void BulletAgeTester::setMaxTime( Real val )
	{
		m_maxTime = val;
	}

	bool BulletAgeTester::getUseEventAge() const
	{
		return m_isUseEventAge;
	}

	void BulletAgeTester::setUseEventAge( bool val )
	{
		m_isUseEventAge = val;
	}

	Ogre::String BulletAgeTester::CmdMaxTime::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletAgeTester*>(target)->getMaxTime());
	}

	void BulletAgeTester::CmdMaxTime::doSet( void* target, const String& val )
	{
		static_cast<BulletAgeTester*>(target)->setMaxTime(
			Ogre::StringConverter::parseReal(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletAgeTester::CmdMaxTime::doCopy( void* target, const void* source )
	{
		static_cast<BulletAgeTester*>(target)->setMaxTime(
			static_cast<const BulletAgeTester*>(source)->getMaxTime());
	}
#endif

	Ogre::String BulletAgeTester::CmdIsUseEventAge::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletAgeTester*>(target)->getUseEventAge());
	}

	void BulletAgeTester::CmdIsUseEventAge::doSet( void* target, const String& val )
	{
		static_cast<BulletAgeTester*>(target)->setUseEventAge(
			Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletAgeTester::CmdIsUseEventAge::doCopy( void* target, const void* source )
	{
		static_cast<BulletAgeTester*>(target)->setUseEventAge(
			static_cast<const BulletAgeTester*>(source)->getUseEventAge());
	}
#endif
}