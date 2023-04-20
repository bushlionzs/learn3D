#include "OgreHeader.h"
#include "OGBulletScaleTester.h"
#include "OGBulletSystem.h"
#include "OGBulletEventSystem.h"

#include "OgreStringConverter.h"

namespace Orphigine
{
	
	BulletScaleTester::CmdMaxScale BulletScaleTester::ms_maxScaleCmd;

	BulletScaleTester::BulletScaleTester( BulletEventSystem* eventSystem )
	{
		m_type = "scale";
		m_parent = eventSystem;

		m_maxScale = 0.0f;

		if (initBaseParamters("scale"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("maxscale",
				"If bulletsystem's scale is greater than this paramter,then transition it to the next eventsystem",
				Ogre::PT_REAL),&ms_maxScaleCmd);
		}
	}

	BulletScaleTester::~BulletScaleTester()
	{

	}

	void BulletScaleTester::operateBulletEventSystem(Real timeElapsed)
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{

		}
	}

	const Real& BulletScaleTester::getMaxScale() const
	{
		return m_maxScale;
	}

	void BulletScaleTester::setMaxScale( const Real& val )
	{
		m_maxScale = val;
	}
	Ogre::String BulletScaleTester::CmdMaxScale::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletScaleTester*>(target)->getMaxScale());
	}

	void BulletScaleTester::CmdMaxScale::doSet( void* target, const String& val )
	{
		static_cast<BulletScaleTester*>(target)->setMaxScale(
			Ogre::StringConverter::parseReal(val));
	}
}