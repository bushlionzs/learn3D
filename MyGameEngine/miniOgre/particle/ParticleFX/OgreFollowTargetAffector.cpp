
#include "OgreHeader.h"
#include "OgreFollowTargetAffector.h"
#include "OgreStringConverter.h"
#include "OgreParticle.h"
#include "OgreParticleSystem.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

namespace Ogre
{
	FollowTargetAffector::CmdDistanceConstraint FollowTargetAffector::ms_distanceCmd;
	FollowTargetAffector::CmdDelayTime FollowTargetAffector::ms_delayTime;
	FollowTargetAffector::CmdTargetNodeName FollowTargetAffector::ms_targetNodeName;

	FollowTargetAffector::FollowTargetAffector( ParticleSystem* particleSystem )
		:ParticleAffector(particleSystem)
	{
		mType = "FollowTarget";

		m_distanceConstraint = 0.0f;
		m_delayTime = 0.0f;
		m_targetNodeName = "";

		if (createParamDictionary("FollowTargetAffectorDictionary"))
		{
			ParamDictionary* tmpDictionary = getParamDictionary();

			tmpDictionary->addParameter(
				ParameterDef("distance","The distance from Per particle to target",PT_REAL),&ms_distanceCmd);

			tmpDictionary->addParameter(
				ParameterDef("delaytime","When to follow target",PT_REAL),&ms_delayTime);

			tmpDictionary->addParameter(
				ParameterDef("target","The target node name",PT_STRING),&ms_targetNodeName);
		}
	}

	void FollowTargetAffector::_affectParticles( ParticleSystem* pSystem, Real timeElapsed )
	{
		Particle* tmpParticle = NULL;

		SceneManager* tmpManager = Root::getSingleton().getSceneManager("OrphigineMainScene");
		if("" == m_targetNodeName)
			return;

		SceneNode* tmpTargetNode = tmpManager->getSceneNode(m_targetNodeName);
		
		const std::vector<Particle*>& particles = pSystem->_getActiveParticles();

		for (auto it = particles.begin(); it != particles.end(); it++)
		{
			tmpParticle = *it;

			Real tmpPassedTime = tmpParticle->mTotalTimeToLive - tmpParticle->mTimeToLive;

			if (tmpPassedTime > m_delayTime)
			{
				Vector3 tmpDir = tmpTargetNode->_getDerivedPosition() - tmpParticle->mPosition;

				if (tmpDir.length() < m_distanceConstraint)
					tmpParticle->mDirection = Vector3::ZERO;
				else
					tmpParticle->mDirection = tmpDir;
			}
			
		}
	}   

	Ogre::Real FollowTargetAffector::getDistanceContraint() const
	{
		return m_distanceConstraint;
	}

	void FollowTargetAffector::setDistanceConstraint( Ogre::Real val )
	{
		m_distanceConstraint = val;
	}

	Ogre::Real FollowTargetAffector::getDelayTime() const
	{
		return m_delayTime;
	}

	void FollowTargetAffector::setDelayTime( Ogre::Real val )
	{
		m_delayTime = val;
	}

	Ogre::String FollowTargetAffector::getTargetNodeName() const
	{
		return m_targetNodeName;
	}

	void FollowTargetAffector::setTargetNodeName( Ogre::String val )
	{
		m_targetNodeName = val;
	}
	bool FollowTargetAffector::loadFromStream(Serializer* pSerializer,DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_FOLLOW_TARGET_AFFECTOR)
			{
				pSerializer->skipChunk(stream);
				return false;
			}			
			//ÊôÐÔ
			pSerializer->readData(stream,&m_distanceConstraint,1,sizeof(m_distanceConstraint));
			pSerializer->readData(stream,&m_delayTime,1,sizeof(m_delayTime));
			m_targetNodeName=pSerializer->readStringBin(stream);
			return true;
		}
		return false;
	}
	bool FollowTargetAffector::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	FollowTargetAffector::calcSerializedSize()
	{
		return 0;
	}

	Ogre::String FollowTargetAffector::CmdDistanceConstraint::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const FollowTargetAffector*>(target)->getDistanceContraint());
	}

	void FollowTargetAffector::CmdDistanceConstraint::doSet( void* target, const String& val )
	{
		static_cast<FollowTargetAffector*>(target)->setDistanceConstraint(
			Ogre::StringConverter::parseReal(val));

	}

	Ogre::String FollowTargetAffector::CmdDelayTime::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const FollowTargetAffector*>(target)->getDelayTime());
	}

	void FollowTargetAffector::CmdDelayTime::doSet( void* target, const String& val )
	{
		static_cast<FollowTargetAffector*>(target)->setDelayTime(
			Ogre::StringConverter::parseReal(val));
	}

	Ogre::String FollowTargetAffector::CmdTargetNodeName::doGet( const void* target ) const
	{
		return static_cast<const FollowTargetAffector*>(target)->getTargetNodeName();
	}

	void FollowTargetAffector::CmdTargetNodeName::doSet( void* target, const String& val )
	{
		static_cast<FollowTargetAffector*>(target)->setTargetNodeName(val);
	}
}