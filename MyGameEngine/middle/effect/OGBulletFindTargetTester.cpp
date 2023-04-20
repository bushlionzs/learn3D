#include "OgreHeader.h"
#include "OGBulletFindTargetTester.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSystem.h"
#include "OGBulletCallbacks.h"
#include "OGBulletFlowSystemManager.h"

#include "OgreStringConverter.h"

namespace Orphigine
{
	BulletFindTargetTester::CmdPursuitType				BulletFindTargetTester::ms_pursuitTypeCmd;
	BulletFindTargetTester::CmdPursuitSpeed				BulletFindTargetTester::ms_pursuitSpeedCmd;
	BulletFindTargetTester::CmdArriveDistance			BulletFindTargetTester::ms_arriveDistanceCmd;
	BulletFindTargetTester::CmdTargetOffset				BulletFindTargetTester::ms_targetOffsetCmd;
	BulletFindTargetTester::CmdForceSourceIndex			BulletFindTargetTester::ms_forceSourceIndexCmd;
	BulletFindTargetTester::CmdForceTargetIndex			BulletFindTargetTester::ms_forceTargetIndexCmd;

	BulletFindTargetTester::BulletFindTargetTester(BulletEventSystem* eventSystem)
	{
		m_type = "findtarget";
		m_parent = eventSystem;

		m_pursuitSpeed = 300.0f;
		m_pursuitType = PT_BEELINE;
		m_arriveDistance = 20.0f;
		m_beforePursuitVelocityCache = Ogre::Vector3(0.0f,0.0f,0.0f);
		m_isInit = false;
		m_targetOffset = Ogre::Vector3::ZERO;
		m_forceSourceIndex = -1;
		m_forceTargetIndex = -1;

		if (initBaseParamters("findtarget"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("pursuittype",
				"The type of pursuit",
				Ogre::PT_STRING),&ms_pursuitTypeCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("pursuitspeed",
				"The speed of pursuit",
				Ogre::PT_REAL),&ms_pursuitSpeedCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("arrivedistance",
				"If test true if distance less than this  paramter",
				Ogre::PT_REAL),&ms_arriveDistanceCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("TargetOffset",
				"The offset of the target",
				Ogre::PT_VECTOR3),&ms_targetOffsetCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("ForceSourceIndex",
				"Force apply this index for Beam source,only used in beam pursuit type",
				Ogre::PT_INT),&ms_forceSourceIndexCmd);

			tmpDict->addParameter(
				Ogre::ParameterDef("ForceTargetIndex",
				"Force apply this index for Beam target,only used in beam pursuit type",
				Ogre::PT_INT),&ms_forceTargetIndexCmd);
		}
	}

	BulletFindTargetTester::~BulletFindTargetTester()
	{

	}

	void BulletFindTargetTester::operateBulletEventSystem(Real timeElapsed)
	{
		switch (m_pursuitType)
		{
		case PT_POINTING:
			{
				pursuitTargetAsPointingType();
				break;
			}
		case PT_BEELINE:
			{
				pursuitTargetAsBeelineType();
				break;
			}
		case PT_BIZZARD:
			{
				pursuitTargetAsBizzardType();
				break;
			}
		case PT_BEAM:
			{
				pursuitTargetAsBeamType();
				break;
			}
		}
	}

	const Orphigine::BulletFindTargetTester::PursuitType& BulletFindTargetTester::getPursuitType() const
	{
		return m_pursuitType;
	}

	void BulletFindTargetTester::setPursuitType( const PursuitType& val )
	{
		m_pursuitType = val;
	}

	void BulletFindTargetTester::pursuitTargetAsPointingType()
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);
			BulletFlowSystem* tmpFlowSystem = m_parent->getParent();

			unsigned int tmpClusterIndex = tmpBulletSystem->getClusterIndex();

			/*TransformInfo tmpTransInfo;
			tmpTransInfo.mPosition = tmpFlowSystem->getTargetPosition(tmpClusterIndex);
			tmpBulletSystem->setTransformInfo(tmpTransInfo);*/

			Ogre::Vector3 tmpPosition = tmpFlowSystem->getTargetPosition(tmpClusterIndex);
			Ogre::Vector3 tmpFinalPos = tmpPosition + m_targetOffset;

			tmpBulletSystem->setPositionWorld(tmpFinalPos);

			m_parent->addTransition(m_outputEventName,tmpBulletSystem);

			BulletSystemHitTargetCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
				getBulletSystemHitTargetCallback();
			if(NULL != tmpCallback)
				tmpCallback->onHitTargetCallback(tmpFlowSystem,tmpBulletSystem);
		}
	}

	void BulletFindTargetTester::pursuitTargetAsBeelineType( )
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		BulletFlowSystem* tmpFlowSystem = m_parent->getParent();

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);
			
			if (!m_isInit)
			{
				m_beforePursuitVelocityCache = tmpBulletSystem->getVelocityWorld();
				m_isInit = true;
			}

			Ogre::Vector3 tmpBulletCurrentPosition = tmpBulletSystem->getPositionWorld();

			unsigned int tmpClusterIndex = tmpBulletSystem->getClusterIndex();

			Ogre::Vector3 tmpTargetPosition = tmpFlowSystem->getTargetPosition(tmpClusterIndex);

			Ogre::Vector3 tmpDirection = tmpTargetPosition - tmpBulletCurrentPosition;
			
			Ogre::Real	tmpDistance = tmpDirection.normalise();
			
			Ogre::Vector3 tmpVelocityOfPursuit = m_pursuitSpeed * tmpDirection;

			Ogre::Vector3 tmpFinalVelocity = tmpVelocityOfPursuit + m_beforePursuitVelocityCache;

			tmpBulletSystem->setVelocityWorld(tmpFinalVelocity);

			Ogre::Quaternion tmpRotation = Ogre::Vector3::UNIT_Z.getRotationTo(tmpFinalVelocity);
			tmpBulletSystem->setOrientationWorld(tmpRotation);

			if (m_arriveDistance > tmpDistance)
			{
				m_parent->addTransition(m_outputEventName,tmpBulletSystem);

				BulletSystemHitTargetCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
					getBulletSystemHitTargetCallback();
				if(NULL != tmpCallback)
					tmpCallback->onHitTargetCallback(tmpFlowSystem,tmpBulletSystem);
			}
		}

	}

	void BulletFindTargetTester::pursuitTargetAsBizzardType()
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);
			BulletFlowSystem* tmpFlowSystem = m_parent->getParent();

			unsigned int tmpClusterIndex = tmpBulletSystem->getClusterIndex();

			/*TransformInfo tmpTransInfo;
			tmpTransInfo.mPosition = tmpFlowSystem->getTargetPosition(tmpClusterIndex);
			tmpTransInfo.mPosition.y += 100.0f;

			tmpBulletSystem->setTransformInfo(tmpTransInfo);*/

			Ogre::Vector3 tmpPosition = tmpFlowSystem->getTargetPosition(tmpClusterIndex);
			tmpPosition.y += 100.0f;
			tmpBulletSystem->setPositionWorld(tmpPosition);

			m_parent->addTransition(m_outputEventName,tmpBulletSystem);

			BulletSystemHitTargetCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
				getBulletSystemHitTargetCallback();
			if(NULL != tmpCallback)
				tmpCallback->onHitTargetCallback(tmpFlowSystem,tmpBulletSystem);
		}
	}

	void BulletFindTargetTester::pursuitTargetAsBeamType()
	{
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			BulletSystem* tmpBulletSystem = (*iter);
			BulletFlowSystem* tmpFlowSystem = m_parent->getParent();

			unsigned int tmpClusterIndex = tmpBulletSystem->getClusterIndex();

			Ogre::Vector3	tmpSourcePosition;
			if(-1 == m_forceSourceIndex || tmpFlowSystem->getNumTargetPosition() <= m_forceSourceIndex)
				tmpSourcePosition = tmpFlowSystem->getPosition();
			else
				tmpSourcePosition = tmpFlowSystem->getTargetPosition(m_forceSourceIndex);

			Ogre::Vector3 tmpDestPosition;
			if(-1 == m_forceTargetIndex || tmpFlowSystem->getNumTargetPosition() <= m_forceTargetIndex)
				tmpDestPosition = tmpFlowSystem->getPosition();
			else
				tmpDestPosition = tmpFlowSystem->getTargetPosition(m_forceTargetIndex);

			tmpBulletSystem->setSourcePosition(tmpSourcePosition);
			tmpBulletSystem->setDestPosition(tmpDestPosition);

			//tmpBulletSystem->setPositionWorld(tmpDestPosition);

			m_parent->addTransition(m_outputEventName,tmpBulletSystem);

			BulletSystemHitTargetCallback* tmpCallback = BulletFlowSystemManager::getSingleton().
				getBulletSystemHitTargetCallback();
			if(NULL != tmpCallback)
				tmpCallback->onHitTargetCallback(tmpFlowSystem,tmpBulletSystem);
		}
	}

	const Real& BulletFindTargetTester::getPursuitSpeed() const
	{
		return m_pursuitSpeed;
	}

	void BulletFindTargetTester::setPursuitSpeed( const Real& val )
	{
		m_pursuitSpeed = val;
	}

	const Real& BulletFindTargetTester::getArriveDistance() const
	{
		return m_arriveDistance;
	}

	void BulletFindTargetTester::setArriveDistance( const Real& val )
	{
		m_arriveDistance = val;
	}

	const Ogre::Vector3& BulletFindTargetTester::getTargetOffset() const
	{
		return m_targetOffset;
	}

	void BulletFindTargetTester::setTargetOffset( const Ogre::Vector3& val )
	{
		m_targetOffset = val;
	}

	int BulletFindTargetTester::getForceTargetIndex() const
	{
		return m_forceTargetIndex;
	}

	void BulletFindTargetTester::setForceTargetIndex( int val )
	{
		m_forceTargetIndex = val;
	}

	int BulletFindTargetTester::getForceSourceIndex() const
	{
		return m_forceSourceIndex;
	}

	void BulletFindTargetTester::setForceSourceIndex( int val )
	{
		m_forceSourceIndex = val;
	}

	Ogre::String BulletFindTargetTester::CmdPursuitType::doGet( const void* target ) const
	{
		PursuitType tmpPT = static_cast<const BulletFindTargetTester*>(target)->getPursuitType();
		
		if (PT_POINTING == tmpPT)
			return "pointing";
		else if (PT_BEELINE == tmpPT)
			return "beeline";
		else if(PT_BIZZARD == tmpPT)
			return "bizzard";
		else
			return "beam";
	}

	void BulletFindTargetTester::CmdPursuitType::doSet( void* target, const String& val )
	{
		if ("pointing" == val)
		{
			static_cast<BulletFindTargetTester*>(target)->setPursuitType(PT_POINTING);
		}
		else if ("beeline" == val)
		{
			static_cast<BulletFindTargetTester*>(target)->setPursuitType(PT_BEELINE);
		}
		else if("bizzard" == val)
		{
			static_cast<BulletFindTargetTester*>(target)->setPursuitType(PT_BIZZARD);
		}
		else
		{
			static_cast<BulletFindTargetTester*>(target)->setPursuitType(PT_BEAM);
		}
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdPursuitType::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setPursuitType(
			static_cast<const BulletFindTargetTester*>(source)->getPursuitType());
	}
#endif

	Ogre::String BulletFindTargetTester::CmdPursuitSpeed::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFindTargetTester*>(target)->getPursuitSpeed());
	}

	void BulletFindTargetTester::CmdPursuitSpeed::doSet( void* target, const String& val )
	{
		static_cast<BulletFindTargetTester*>(target)->setPursuitSpeed(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdPursuitSpeed::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setPursuitSpeed(
			static_cast<const BulletFindTargetTester*>(source)->getPursuitSpeed());
	}
#endif

	Ogre::String BulletFindTargetTester::CmdArriveDistance::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFindTargetTester*>(target)->getArriveDistance());
	}

	void BulletFindTargetTester::CmdArriveDistance::doSet( void* target, const String& val )
	{
		static_cast<BulletFindTargetTester*>(target)->setArriveDistance(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdArriveDistance::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setArriveDistance(
			static_cast<const BulletFindTargetTester*>(source)->getArriveDistance());
	}
#endif

	Ogre::String BulletFindTargetTester::CmdTargetOffset::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFindTargetTester*>(target)->getTargetOffset());
	}

	void BulletFindTargetTester::CmdTargetOffset::doSet( void* target, const String& val )
	{
		static_cast<BulletFindTargetTester*>(target)->setTargetOffset(
			Ogre::StringConverter::parseVector3(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdTargetOffset::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setTargetOffset(
			static_cast<const BulletFindTargetTester*>(source)->getTargetOffset());
	}
#endif

	Ogre::String BulletFindTargetTester::CmdForceTargetIndex::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFindTargetTester*>(target)->getForceTargetIndex());
	}

	void BulletFindTargetTester::CmdForceTargetIndex::doSet( void* target, const String& val )
	{
		static_cast<BulletFindTargetTester*>(target)->setForceTargetIndex(
			Ogre::StringConverter::parseInt(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdForceTargetIndex::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setForceTargetIndex(
			static_cast<const BulletFindTargetTester*>(source)->getForceTargetIndex());
	}
#endif


	Ogre::String BulletFindTargetTester::CmdForceSourceIndex::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletFindTargetTester*>(target)->getForceSourceIndex());
	}

	void BulletFindTargetTester::CmdForceSourceIndex::doSet( void* target, const String& val )
	{
		static_cast<BulletFindTargetTester*>(target)->setForceSourceIndex(
			Ogre::StringConverter::parseInt(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void BulletFindTargetTester::CmdForceSourceIndex::doCopy( void* target, const void* source )
	{
		static_cast<BulletFindTargetTester*>(target)->setForceSourceIndex(
			static_cast<const BulletFindTargetTester*>(source)->getForceSourceIndex()); 
	}
#endif
}