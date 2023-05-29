#include "OgreHeader.h"
#include "OGBulletSpawnOperator.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreSceneNode.h"

namespace Orphigine
{
	BulletSpawnOperator::CmdBulletSystemTemplateName BulletSpawnOperator::ms_bulletTemplateCmd;
	BulletSpawnOperator::CmdIsDeleteSource				 BulletSpawnOperator::ms_isDeleteSourceCmd;

	BulletSpawnOperator::BulletSpawnOperator(BulletEventSystem* eventSystem)
	{
		m_type = "spawn";
		m_parent = eventSystem;
		m_bulletSystemName = "";
		m_isDeleteSource = false;
		m_spawnedTimes = 0;
		m_isOperated = false;

		if (createParamDictionary("SpawnOperatorDict"))
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

	BulletSpawnOperator::~BulletSpawnOperator()
	{

	}

	void BulletSpawnOperator::operateBulletEventSystem(Real timeElapsed)
	{
		assert(NULL != m_parent && NULL != m_parent->getParent());
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
		}
	}

	const String& BulletSpawnOperator::getBulletSystemName() const
	{
		return m_bulletSystemName;
	}

	void BulletSpawnOperator::setBulletSystemName( const String& val )
	{
		m_bulletSystemName = val;
	}

	bool BulletSpawnOperator::getIsDeleteSource() const
	{
		return m_isDeleteSource;
	}

	void BulletSpawnOperator::setIsDeleteSource( bool val )
	{
		m_isDeleteSource = val;
	}
	Ogre::String BulletSpawnOperator::CmdBulletSystemTemplateName::doGet( const void* target ) const
	{
		return static_cast<const BulletSpawnOperator*>(target)->getBulletSystemName();
	}

	void BulletSpawnOperator::CmdBulletSystemTemplateName::doSet( void* target, const String& val )
	{
		static_cast<BulletSpawnOperator*>(target)->setBulletSystemName(val);
	}

	Ogre::String BulletSpawnOperator::CmdIsDeleteSource::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSpawnOperator*>(target)->getIsDeleteSource());
	}

	void BulletSpawnOperator::CmdIsDeleteSource::doSet( void* target, const String& val )
	{
		static_cast<BulletSpawnOperator*>(target)->setIsDeleteSource(
			Ogre::StringConverter::parseBool(val));
	}
}