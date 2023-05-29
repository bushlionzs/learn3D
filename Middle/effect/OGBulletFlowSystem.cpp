#include "OgreHeader.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletSystemManager.h"
#include "OGBulletSystem.h"
#include "OGBulletCallbacks.h"
#include "OgreControllerManager.h"
#include "OgreController.h"
#include "OgreStringConverter.h"
#include "platform_log.h"
#include "engine_manager.h"
#include "OgreSceneManager.h"

namespace Orphigine
{

	BulletFlowSystem::CmdMaxTime			BulletFlowSystem::ms_maxTimeCmd;
	BulletFlowSystem::CmdDefaultHitPoint	BulletFlowSystem::ms_defaultHitPointCmd;
	BulletFlowSystem::CmdIterationInterval	BulletFlowSystem::ms_iterationIntervalCmd;

	//-----------------------------------------------------------------------
	// Local class for updating based on time
	class BulletFlowSystemUpdateValue : public Ogre::ControllerValue<Real>
	{
	protected:
		BulletFlowSystem* mTarget;
	public:
		BulletFlowSystemUpdateValue(BulletFlowSystem* target) : mTarget(target) {}

		Real getValue(void) const { return 0; } // N/A

		void setValue(Real value) { mTarget->update(value); }

	};

	BulletFlowSystem::BulletFlowSystem()
	{
		m_sceneNode = NULL;
		m_bulletEventSystemMap.clear();
		m_bulletSystems.clear();
		m_isCreated = false;
		m_isActiveEventSystemListInitialised = false;
		m_timeController = NULL;
		m_maxTime = 0.0f;
		m_age	= 0.0f;
		m_targetPositionVec.clear();
		m_birthBulletTimesPerCluster = 0;
		m_defaultHitPoint = "";
		m_userData = NULL;
		m_iterationInterval = 0.016f;
		m_updateRemainTime = 0.0f;
		m_Priority = 3;

		Ogre::ControllerValueRealPtr tmpControllerValue = Ogre::ControllerValueRealPtr(
			new BulletFlowSystemUpdateValue(this));

		m_timeController = Ogre::ControllerManager::getSingleton().createFrameTimePassthroughController(
			tmpControllerValue);

		if (createParamDictionary("BulletFlowSystemDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef("maxtime",
				"The max life time of bullet flow system",Ogre::PT_REAL),
				&ms_maxTimeCmd);

			tmpDict->addParameter(Ogre::ParameterDef("hitpoint",
				"The default hit point of bullet flow system",Ogre::PT_STRING),
				&ms_defaultHitPointCmd);

			tmpDict->addParameter(Ogre::ParameterDef("IterationInterval",
				"The iteration interval of bullet flow system",Ogre::PT_REAL),
				&ms_iterationIntervalCmd);
		}

	}

	BulletFlowSystem::~BulletFlowSystem()
	{
		removeAllBulletEventSystem();
		removeAllBulletSystem();

		if (NULL != m_timeController)
		{
			Ogre::ControllerManager::getSingleton().destroyController(m_timeController);
			m_timeController = NULL;
		}
	}

	BulletEventSystem* BulletFlowSystem::addBulletEventSystem( const String& name )
	{
		BulletEventSystem* tmpEventSystem = BulletFlowSystemManager::getSingleton().createBulletEventSystem(name,this);

		m_bulletEventSystemMap.insert(std::map<String,BulletEventSystem*>::value_type(name,tmpEventSystem));

		return tmpEventSystem;
	}

	BulletEventSystem* BulletFlowSystem::getBulletEventSystem( const String& name )
	{
		std::map<String,BulletEventSystem*>::iterator iter = m_bulletEventSystemMap.find(name);
		if (m_bulletEventSystemMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, 
				"BulletEventSystem with name '" + name + "' can not found.", 
				"BulletFlowSystem::getBulletEventSystem");
		}

		return iter->second;
	}

	void BulletFlowSystem::update( Real time )
	{

		if(NULL == m_sceneNode)
			return; 
		if (0 < m_iterationInterval)
		{
			try
			{
				m_updateRemainTime += time;

				while(m_updateRemainTime >= m_iterationInterval)
				{
					std::map<String,BulletEventSystem*>::iterator iter;
					for (iter = m_bulletEventSystemMap.begin();iter != m_bulletEventSystemMap.end();iter ++)
					{
						iter->second->update(m_iterationInterval);
					}

					integrateBulletSystemTransform(m_iterationInterval);

					std::vector<BulletSystem*>::iterator iterBS;
					for (iterBS = m_bulletSystems.begin();iterBS != m_bulletSystems.end();
						iterBS ++)
					{
						(*iterBS)->update(m_iterationInterval);
					}

					m_updateRemainTime -= m_iterationInterval;
				}
			}
			catch(...)
			{
				WARNING_LOG("BulletFlowSystem::update---1 Failed --BulletFlowSystem::update");
				//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"BulletFlowSystem::update Failed!", "BulletFlowSystem::update" );
				throw;
			}
		} 
		else
		{
			try
			{
				std::map<String,BulletEventSystem*>::iterator iter;
				for (iter = m_bulletEventSystemMap.begin();iter != m_bulletEventSystemMap.end();iter ++)
				{
					iter->second->update(time);
				}

				integrateBulletSystemTransform(time);

				std::vector<BulletSystem*>::iterator iterBS;
				for (iterBS = m_bulletSystems.begin();iterBS != m_bulletSystems.end();
					iterBS ++)
				{
					(*iterBS)->update(time);
				}
			}
			catch(...)
			{
				WARNING_LOG("BulletFlowSystem::update---2 Failed --BulletFlowSystem::update");
				//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"BulletFlowSystem::update Failed!", "BulletFlowSystem::update" );
				throw;
			}
		}


		m_age += time;

		/*if (m_age > m_maxTime)
		{
		DestroyBulletFlowCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
		getDestroyBulletFlowCallback();
		if(NULL != tmpCallback)
		tmpCallback->onDestroyBulletFlow(this);
		BulletFlowSystemManager::getSingleton().destroyBulletFlowSystem(this);
		}	
		else if (0 == (int)m_bulletSystems.size())
		{
		DestroyBulletFlowCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
		getDestroyBulletFlowCallback();
		if(NULL != tmpCallback)
		tmpCallback->onDestroyBulletFlow(this);
		BulletFlowSystemManager::getSingleton().destroyBulletFlowSystem(this);
		}*/

	}
	BulletSystem* BulletFlowSystem::addBulletSystem(const String& name, unsigned int clusterIndex)
	{
		BulletSystem* tmpBulletSystem = BulletSystemManager::getSingleton().createBulletSystem(name);

		tmpBulletSystem->setPriority(m_Priority); 

		tmpBulletSystem->createSceneNode();
		tmpBulletSystem->setClusterIndex(clusterIndex);

		m_bulletSystems.push_back(tmpBulletSystem);

		AfterCreatedBulletSystemCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
			getAfterCreatedBulletSystemCallback();
		if(NULL != tmpCallback)
			tmpCallback->onAfterCreatedBulletSystem(this,tmpBulletSystem);

		return tmpBulletSystem;
	}

	BulletSystem* BulletFlowSystem::getBulletSystem( int index ) const
	{
		assert(index < (int)m_bulletSystems.size() && index >= 0);
		return m_bulletSystems[index];
	}

	void BulletFlowSystem::removeBulletSystem( unsigned int index )
	{
		assert(index < m_bulletSystems.size());

		std::vector<BulletSystem*>::iterator iter = m_bulletSystems.begin() + index;

		BeforeDeleteBulletSystemCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
			getBeforeDeleteBulletSystemCallback();
		if(NULL != tmpCallback)
			tmpCallback->onBeforeDeleteBulletSystem((*iter));

		BulletSystemManager::getSingleton().destroyBulletSystem((*iter));

		m_bulletSystems.erase(iter);
	}

	void BulletFlowSystem::removeBulletSystem( BulletSystem* bulletSystem )
	{
		std::vector<BulletSystem*>::iterator iter = std::find(m_bulletSystems.begin(),
			m_bulletSystems.end(),bulletSystem);

		if (iter != m_bulletSystems.end())
		{
			BeforeDeleteBulletSystemCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
				getBeforeDeleteBulletSystemCallback();
			if(NULL != tmpCallback)
				tmpCallback->onBeforeDeleteBulletSystem((*iter));

			BulletSystemManager::getSingleton().destroyBulletSystem((*iter));

			m_bulletSystems.erase(iter);
		}
	}

	void BulletFlowSystem::removeBulletEventSystem( const String& eventSystemName )
	{
		std::map<String,BulletEventSystem*>::iterator iter = m_bulletEventSystemMap.find(eventSystemName);

		BulletFlowSystemManager::getSingleton().destroyBulletEventSystem(iter->second);

		m_bulletEventSystemMap.erase(iter);
	}

	void BulletFlowSystem::removeBulletEventSystem( BulletEventSystem* eventSystem )
	{
		std::map<String,BulletEventSystem*>::iterator iter;

		for (iter = m_bulletEventSystemMap.begin();iter != m_bulletEventSystemMap.end();iter ++)
		{
			if (iter->second == eventSystem)
			{
				BulletFlowSystemManager::getSingleton().destroyBulletEventSystem(iter->second);

				m_bulletEventSystemMap.erase(iter);

				break;
			}
		}
	}

	int BulletFlowSystem::getNumBulletEventSystem() const
	{
		return (int)m_bulletEventSystemMap.size();
	}

	int BulletFlowSystem::getNumBulletSystem() const
	{
		return (int)m_bulletSystems.size();
	}

	BulletFlowSystem& BulletFlowSystem::operator=( const BulletFlowSystem& rhs )
	{
		removeAllBulletEventSystem();
		removeAllBulletSystem();

		const std::map<String,BulletEventSystem*>& tmpBulletEventSystemMap = 
			rhs.getBulletEventSystemsMap();

		std::map<String,BulletEventSystem*>::const_iterator iter;
		for (iter = tmpBulletEventSystemMap.begin();iter != tmpBulletEventSystemMap.end();iter ++)
		{
			BulletEventSystem* tmpEventSystem = iter->second;
			BulletEventSystem* tmpNewEventSystem = addBulletEventSystem(
				tmpEventSystem->getTemplateName());

			*tmpNewEventSystem = *tmpEventSystem;
		}


		m_maxTime = rhs.m_maxTime;
		m_defaultHitPoint = rhs.m_defaultHitPoint;
		m_iterationInterval = rhs.m_iterationInterval;

		return *this;
	}

	const std::map<String,BulletEventSystem*>& BulletFlowSystem::getBulletEventSystemsMap() const 
	{
		return m_bulletEventSystemMap;
	}

	const Ogre::Vector3& BulletFlowSystem::getPosition() const
	{
		return m_sceneNode->getPosition();
	}

	void BulletFlowSystem::setPosition( const Ogre::Vector3& position )
	{
		m_sceneNode->setPosition(position);
	}

	void BulletFlowSystem::integrateBulletSystemTransform( Real time )
	{
		TransformInfo tmpTrans;

		std::vector<BulletSystem*>::iterator iterBS;
		for (iterBS = m_bulletSystems.begin();iterBS != m_bulletSystems.end();iterBS ++)
		{
			Ogre::Vector3 tmpVelocity = (*iterBS)->getVelocityWorld() + 
				(*iterBS)->getAccelerationWorld() * time;

			(*iterBS)->setVelocityWorld(tmpVelocity);

			Ogre::Vector3 tmpPosition = Ogre::Vector3(0.0f,0.0f,0.0f);

			if ((*iterBS)->getAttach())
			{
				unsigned int tmpClusterIndex = (*iterBS)->getClusterIndex();

				tmpPosition = getTargetPosition(tmpClusterIndex);
			} 
			else
			{
				tmpPosition = (*iterBS)->getPositionWorld() + 
					tmpVelocity * time;
			}
			

			(*iterBS)->setPositionWorld(tmpPosition);

			Ogre::Vector3 tmpAngularVelocity = (*iterBS)->getAngularVelocityWorld();

			Ogre::Quaternion tmpRotation = (*iterBS)->getOrientationWorld()/* + 
				tmpAngularVelocity * time*/;

			(*iterBS)->setOrientationWorld(tmpRotation);

			tmpTrans.mPosition = tmpPosition;
			tmpTrans.mRotation = tmpRotation;
			(*iterBS)->setTransformInfo(tmpTrans);
		}
	}


	void BulletFlowSystem::removeAllBulletEventSystem()
	{
		std::map<String,BulletEventSystem*>::iterator iter;
		for (iter = m_bulletEventSystemMap.begin();iter != m_bulletEventSystemMap.end();iter ++)
		{
			BulletFlowSystemManager::getSingleton().destroyBulletEventSystem(iter->second);
		}
		m_bulletEventSystemMap.clear();
	}

	void BulletFlowSystem::removeAllBulletSystem()
	{
		std::vector<BulletSystem*>::iterator iter;
		for (iter = m_bulletSystems.begin();iter != m_bulletSystems.end();iter ++)
		{
			BeforeDeleteBulletSystemCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
				getBeforeDeleteBulletSystemCallback();
			if(NULL != tmpCallback)
				tmpCallback->onBeforeDeleteBulletSystem((*iter));

			BulletSystemManager::getSingleton().destroyBulletSystem((*iter));

		}
		m_bulletSystems.clear();
	}

	void BulletFlowSystem::createSceneNodeFromBase()
	{
		m_sceneNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(BLANKSTRING);
	}

	void BulletFlowSystem::removeSceneNodeFromParent()
	{
		assert(NULL != m_sceneNode);

		//m_sceneNode->getParent()->removeChild(m_sceneNode);
		m_sceneNode->getCreator()->destroySceneNode(m_sceneNode);
		m_sceneNode = NULL;
	}

	Real BulletFlowSystem::getMaxTime() const
	{
		return m_maxTime;
	}

	void BulletFlowSystem::setMaxTime(Real val )
	{
		m_maxTime = val;
	}

	Real BulletFlowSystem::getAge() const
	{
		return m_age;
	}

	void BulletFlowSystem::setAge(Real val )
	{
		m_age = val;
	}

	Ogre::Vector3 BulletFlowSystem::getTargetPosition( unsigned int index ) const
	{
		//assert((unsigned int)m_targetPositionVec.size() > index && "越界BulletFlowSystem::getTargetPosition");
		
		if(0 == (unsigned int)m_targetPositionVec.size())
			return Ogre::Vector3::ZERO;
		else if((unsigned int)m_targetPositionVec.size() - 1 < index)
			index = (unsigned int)m_targetPositionVec.size() - 1;
		
		return m_targetPositionVec[index];
	}

	void BulletFlowSystem::addTargetPosition( const Ogre::Vector3& position )
	{
		m_targetPositionVec.push_back(position);
	}

	void BulletFlowSystem::flushTargetPosition( unsigned int index,const Ogre::Vector3& position )
	{
		assert(index < (unsigned int)m_targetPositionVec.size() && "越界BulletFlowSystem::flushTargetPosition");

		m_targetPositionVec[index] = position;
	}

	int BulletFlowSystem::getNumTargetPosition() const
	{
		return (unsigned int)m_targetPositionVec.size();
		
	}

	int BulletFlowSystem::getBirthBulletTimesPerCluster() const
	{
		return m_birthBulletTimesPerCluster;
	}

	void BulletFlowSystem::setBirthBulletTimesPerCluster( int val )
	{
		m_birthBulletTimesPerCluster = val;
	}

	String BulletFlowSystem::getDefaultHitPoint() const
	{
		return m_defaultHitPoint;
	}

	void BulletFlowSystem::setDefaultHitPoint( const String& val )
	{
		m_defaultHitPoint = val;
	}

	Real BulletFlowSystem::getIterationInterval() const
	{
		return m_iterationInterval;
	}

	void BulletFlowSystem::setIterationInterval(Real val )
	{
		m_iterationInterval = val;

	}

	Ogre::String BulletFlowSystem::CmdMaxTime::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFlowSystem*>(target)->getMaxTime());
	}

	void BulletFlowSystem::CmdMaxTime::doSet( void* target, const String& val )
	{
		static_cast<BulletFlowSystem*>(target)->setMaxTime(
			Ogre::StringConverter::parseReal(val));
	}

	Ogre::String BulletFlowSystem::CmdDefaultHitPoint::doGet( const void* target ) const
	{
		return	static_cast<const BulletFlowSystem*>(target)->getDefaultHitPoint();
	}

	void BulletFlowSystem::CmdDefaultHitPoint::doSet( void* target, const String& val )
	{
		static_cast<BulletFlowSystem*>(target)->setDefaultHitPoint(val);
	}

	Ogre::String BulletFlowSystem::CmdIterationInterval::doGet( const void* target ) const
	{	
		return Ogre::StringConverter::toString(
			static_cast<const BulletFlowSystem*>(target)->getIterationInterval());
	}

	void BulletFlowSystem::CmdIterationInterval::doSet( void* target, const String& val )
	{
		static_cast<BulletFlowSystem*>(target)->setIterationInterval(
			Ogre::StringConverter::parseReal(val));
	}
}