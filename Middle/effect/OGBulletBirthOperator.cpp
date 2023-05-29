#include "OgreHeader.h"
#include "OGBulletBirthOperator.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSystem.h"
#include "OGBulletCallbacks.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreSceneNode.h"

namespace Orphigine
{
	BulletBirthOperator::CmdBulletSystemTemplateName BulletBirthOperator::ms_bulletTemplateCmd;
	BulletBirthOperator::CmdBirthTimes				 BulletBirthOperator::ms_birthTimesCmd;
	BulletBirthOperator::CmdIsDynamicAdapter		 BulletBirthOperator::ms_isDynamicAdapterCmd;

	BulletBirthOperator::BulletBirthOperator(BulletEventSystem* eventSystem)
	{
		m_type = "birth";
		m_parent = eventSystem;
		m_bulletSystemName = "";
		m_birthTimes = 1;
		m_birthedTimes = 0;
		m_isOperated = false;
		m_isDynamicAdapter = true;

		if (createParamDictionary("BirthOperatorDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("bulletsystemname","Bullet system template name",Ogre::PT_STRING),
				&ms_bulletTemplateCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("birthtimes","Birth bullet system times",Ogre::PT_INT),
				&ms_birthTimesCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("IsDynamicAdapter","Is dynamic adapt number bulletsystem for birthing",Ogre::PT_BOOL),
				&ms_isDynamicAdapterCmd);
		}
	}

	BulletBirthOperator::~BulletBirthOperator()
	{

	}

	void BulletBirthOperator::operateBulletEventSystem(Real timeElapsed)
	{
		assert(NULL != m_parent && NULL != m_parent->getParent());

		if(m_isOperated)
			return;

		m_parent->getParent()->setBirthBulletTimesPerCluster(m_birthTimes);

		unsigned int tmpBirthBulletTimesPerCluster = m_birthTimes;
		unsigned int tmpClusterIndex = 0;
		unsigned int tmpIndex = 0;

		int totalTimes = 0;
		if(m_isDynamicAdapter)
			totalTimes = m_birthTimes * m_parent->getParent()->getNumTargetPosition();
		else
			totalTimes = m_birthTimes;

		for (int i = 0;i < totalTimes;i ++)
		{
			if(tmpIndex < tmpBirthBulletTimesPerCluster)
				tmpIndex ++;
			else
			{
				tmpClusterIndex ++;
				tmpIndex = 1;
			}

			BulletFlowSystem* tmpFlow = m_parent->getParent();

			BulletSystem* tmpBulletSystem = tmpFlow->addBulletSystem(m_bulletSystemName, tmpClusterIndex);

			const Ogre::Vector3& tmpPosition = tmpFlow->getPosition();

			//tmpBulletSystem->setTransformInfo(tmpInfo);
			tmpBulletSystem->setPositionWorld(tmpPosition);

			m_parent->addActiveBulletSystem(tmpBulletSystem);
		}
		
		m_isOperated = true;
	}

	const String& BulletBirthOperator::getBulletSystemName() const
	{
		return m_bulletSystemName;
	}

	void BulletBirthOperator::setBulletSystemName( const String& val )
	{
		m_bulletSystemName = val;
	}

	int BulletBirthOperator::getBirthTimes() const
	{
		return m_birthTimes;
	}

	void BulletBirthOperator::setBirthTimes( int val )
	{
		m_birthTimes = val;
	}

	bool BulletBirthOperator::getDynamicAdapter() const
	{
		return m_isDynamicAdapter;
	}

	void BulletBirthOperator::setDynamicAdapter( bool val )
	{
		m_isDynamicAdapter = val;
	}

	Ogre::String BulletBirthOperator::CmdBulletSystemTemplateName::doGet( const void* target ) const
	{
		return static_cast<const BulletBirthOperator*>(target)->getBulletSystemName();
	}

	void BulletBirthOperator::CmdBulletSystemTemplateName::doSet( void* target, const String& val )
	{
		static_cast<BulletBirthOperator*>(target)->setBulletSystemName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletBirthOperator::CmdBulletSystemTemplateName::doCopy( void* target, const void* source )
	{
		static_cast<BulletBirthOperator*>(target)->setBulletSystemName(
			static_cast<const BulletBirthOperator*>(source)->getBulletSystemName());
	}
#endif
	
	Ogre::String BulletBirthOperator::CmdBirthTimes::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletBirthOperator*>(target)->getBirthTimes());
	}

	void BulletBirthOperator::CmdBirthTimes::doSet( void* target, const String& val )
	{
		static_cast<BulletBirthOperator*>(target)->setBirthTimes(
			Ogre::StringConverter::parseInt(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletBirthOperator::CmdBirthTimes::doCopy( void* target, const void* source )
	{
		static_cast<BulletBirthOperator*>(target)->setBirthTimes(
			static_cast<const BulletBirthOperator*>(source)->getBirthTimes());
	}
#endif

	Ogre::String BulletBirthOperator::CmdIsDynamicAdapter::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletBirthOperator*>(target)->getDynamicAdapter());
	}

	void BulletBirthOperator::CmdIsDynamicAdapter::doSet( void* target, const String& val )
	{
		static_cast<BulletBirthOperator*>(target)->setDynamicAdapter(
			Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletBirthOperator::CmdIsDynamicAdapter::doCopy( void* target, const void* source )
	{	
		static_cast<BulletBirthOperator*>(target)->setDynamicAdapter(
			static_cast<const BulletBirthOperator*>(source)->getDynamicAdapter());
	}
#endif
}