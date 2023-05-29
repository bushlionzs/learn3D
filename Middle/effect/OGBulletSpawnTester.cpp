#include "OgreHeader.h"
#include "OGBulletSpawnTester.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreSceneNode.h"

namespace Orphigine
{
	BulletSpawnTester::CmdBulletSystemTemplateName BulletSpawnTester::ms_bulletTemplateCmd;
	BulletSpawnTester::CmdIsDeleteSource				 BulletSpawnTester::ms_isDeleteSourceCmd;

	BulletSpawnTester::BulletSpawnTester(BulletEventSystem* eventSystem)
	{
		m_type = "SpawnTester";
		m_parent = eventSystem;

		m_bulletSystemName = "";
		m_isDeleteSource = false;
		m_spawnedTimes = 0;
		m_isOperated = false;

		if (initBaseParamters("SpawnTester"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("bulletsystemname","Bullet system template name",Ogre::PT_STRING),
				&ms_bulletTemplateCmd);
			tmpDict->addParameter(
				Ogre::ParameterDef("isdeletesource","Spawn bullet system times",Ogre::PT_BOOL),
				&ms_isDeleteSourceCmd);
		}
	}

	BulletSpawnTester::~BulletSpawnTester()
	{

	}

	void BulletSpawnTester::operateBulletEventSystem(Real timeElapsed)
	{
		assert(NULL != m_parent && NULL != m_parent->getParent() );
		if(m_isOperated)
			return;

		std::vector<BulletSystem*>* tmpNewTransferredBulletSystemList = m_parent->getNewTransferredBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpNewTransferredBulletSystemList->begin();
			iter != tmpNewTransferredBulletSystemList->end();
			iter ++)
		{
			BulletSystem* tmpSourceBulletSystem = (*iter);

			BulletFlowSystem* tmpFlow = m_parent->getParent();

			BulletSystem* tmpBulletSystem = tmpFlow->addBulletSystem(m_bulletSystemName, tmpSourceBulletSystem->getClusterIndex());

			/*TransformInfo tmpInfo ;
			tmpInfo.mPosition = tmpSourceBulletSystem->getPositionWorld();
			tmpBulletSystem->setTransformInfo(tmpInfo);*/

			const Ogre::Vector3& tmpPosition = tmpSourceBulletSystem->getPositionWorld();
			tmpBulletSystem->setPositionWorld(tmpPosition);

			m_parent->addActiveBulletSystem(tmpBulletSystem);

			if(m_isDeleteSource)
			{
				m_parent->removeActiveBulletSystem(tmpSourceBulletSystem);
				tmpFlow->removeBulletSystem(tmpSourceBulletSystem);
			}	

			m_parent->addTransition(m_outputEventName,tmpBulletSystem);
		}
	}

	const String& BulletSpawnTester::getBulletSystemName() const
	{
		return m_bulletSystemName;
	}

	void BulletSpawnTester::setBulletSystemName( const String& val )
	{
		m_bulletSystemName = val;
	}

	bool BulletSpawnTester::getIsDeleteSource() const
	{
		return m_isDeleteSource;
	}

	void BulletSpawnTester::setIsDeleteSource( bool val )
	{
		m_isDeleteSource = val;
	}
	Ogre::String BulletSpawnTester::CmdBulletSystemTemplateName::doGet( const void* target ) const
	{
		return static_cast<const BulletSpawnTester*>(target)->getBulletSystemName();
	}

	void BulletSpawnTester::CmdBulletSystemTemplateName::doSet( void* target, const String& val )
	{
		static_cast<BulletSpawnTester*>(target)->setBulletSystemName(val);
	}

	Ogre::String BulletSpawnTester::CmdIsDeleteSource::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSpawnTester*>(target)->getIsDeleteSource());
	}

	void BulletSpawnTester::CmdIsDeleteSource::doSet( void* target, const String& val )
	{
		static_cast<BulletSpawnTester*>(target)->setIsDeleteSource(
			Ogre::StringConverter::parseBool(val));
	}
}