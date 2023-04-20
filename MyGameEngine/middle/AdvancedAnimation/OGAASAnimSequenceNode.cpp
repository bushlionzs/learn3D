#include "OgreHeader.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASAnimation.h"

#include "OgreStringConverter.h"


namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASAnimSequenceNode::CmdRate		AASAnimSequenceNode::ms_rateCmd;
	AASAnimSequenceNode::CmdAnimationName	AASAnimSequenceNode::ms_animationNameCmd;
	AASAnimSequenceNode::CmdIsLooping		AASAnimSequenceNode::ms_isLoopingCmd;
	AASAnimSequenceNode::CmdIsCauseAnimEndEvent		AASAnimSequenceNode::ms_isCauseAnimEndEvent;
	AASAnimSequenceNode::CmdIsCauseAnimPlayEvent    AASAnimSequenceNode::ms_isCauseAnimPlayEvent;
	AASAnimSequenceNode::CmdSynchGroupName			AASAnimSequenceNode::ms_synchGroupNameCmd;
	
	AASAnimSequenceNode::AASAnimSequenceNodeSerializerMap	AASAnimSequenceNode::ms_serializersMap;

	AASAnimSequenceNode::AASAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASNode("AnimSequence",system,handle),
		m_rate(1.0f),
		m_animationName(""),
		m_animationID(-1),
		m_animation(NULL),
		m_isLooping(true),
		m_isCauseAnimEndEvent(false),
		m_isCauseAnimPlayEvent(false),
		m_synchGroupName(""),
		m_refreshAnimNameDirty(false),
		m_isPlaying(false),
		m_currentTime(0.0f)
	{
		initParameter(m_type.c_str());
	}

	AASAnimSequenceNode::AASAnimSequenceNode( const String& typeName,AdvancedAnimationSystem* system,unsigned short handle )
		: AASNode(typeName,system,handle),
		m_rate(1.0f),
		m_animationName(""),
		m_animationID(-1),
		m_animation(NULL),
		m_isLooping(true),
		m_isCauseAnimEndEvent(false),
		m_isCauseAnimPlayEvent(false),
		m_synchGroupName(""),
		m_refreshAnimNameDirty(false),
		m_isPlaying(false),
		m_currentTime(0.0f)
	{
	}
	
	AASAnimSequenceNode::~AASAnimSequenceNode()
	{

	}

	bool AASAnimSequenceNode::initParameter( const String& typeName )
	{
		if (AASNode::initParameter(typeName))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef(
				"Rate","The animation rate",Ogre::PT_REAL),&ms_rateCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"AnimationName","The name of animation",Ogre::PT_STRING),&ms_animationNameCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"IsLooping","Is looping animation",Ogre::PT_BOOL),&ms_isLoopingCmd);

			tmpDict->addParameter(Ogre::ParameterDef(
				"IsCauseEndEvent","Should this node call AnimationEndEvent on its parent when it reach end and stop",Ogre::PT_BOOL),
				&ms_isCauseAnimEndEvent);

			tmpDict->addParameter(Ogre::ParameterDef(
				"IsCausePlayEvent","Should this node call AnimationPlayEvent on its parent when it start",Ogre::PT_BOOL),
				&ms_isCauseAnimPlayEvent);

			tmpDict->addParameter(Ogre::ParameterDef(
				"SynchGroupName","The synch group name",Ogre::PT_STRING),
				&ms_synchGroupNameCmd);

			return true;
		}
		return false;
	}

	void AASAnimSequenceNode::copyParameters( AASNode* dest )
	{
		AASNode::copyParameters(dest);

		AASAnimSequenceNode* destNode = (AASAnimSequenceNode*)dest;
		assert(destNode && "AASAnimSequenceNode::copyParameters");

		destNode->m_rate					=	m_rate;
		destNode->setAnimationName(m_animationName.c_str());
		destNode->m_isLooping				=	m_isLooping;
		destNode->m_isCauseAnimEndEvent		=	m_isCauseAnimEndEvent;
		destNode->m_isCauseAnimPlayEvent	=	m_isCauseAnimPlayEvent;
		destNode->m_synchGroupName			=	m_synchGroupName;
	}

	void AASAnimSequenceNode::initAnim( AASNode* parentNode )
	{
		AASNode::initAnim(parentNode);

		if (!m_synchGroupName.empty())
		{
			AnimSynchGropVector& animSeqSynchGroupVec = m_owner->getAnimSynchGroups();

			AnimSeqSynchGroup* animSeqSynchGroupPtr = NULL;

			AnimSynchGropVector::iterator iter;
			for (iter = animSeqSynchGroupVec.begin();iter != animSeqSynchGroupVec.end();iter ++)
			{
				if((*iter).m_synchGroupName == m_synchGroupName.c_str())
					animSeqSynchGroupPtr = &(*iter);
			}

			if (!animSeqSynchGroupPtr)
			{
				animSeqSynchGroupVec.push_back(AnimSeqSynchGroup());
				int groupIndex = animSeqSynchGroupVec.size();

				animSeqSynchGroupPtr = &animSeqSynchGroupVec[groupIndex - 1];
				animSeqSynchGroupPtr->m_animSeqNodes.push_back(this);
				animSeqSynchGroupPtr->m_synchGroupName = m_synchGroupName.c_str();
			} 
			else
			{
				AASAnimSequNodeVector::iterator animSeqNodesIter = 
					std::find(animSeqSynchGroupPtr->m_animSeqNodes.begin(),animSeqSynchGroupPtr->m_animSeqNodes.end(),this);
				if(animSeqNodesIter == animSeqSynchGroupPtr->m_animSeqNodes.end())
					animSeqSynchGroupPtr->m_animSeqNodes.push_back(this);
				else
				{
					animSeqSynchGroupPtr->m_animSeqNodes.erase(animSeqNodesIter);
					animSeqSynchGroupPtr->m_animSeqNodes.push_back(this);
				}
			}
		}
	}

	void AASAnimSequenceNode::tickAnimation(const float elapsedTime,
		ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		_refreshAnimation();

		if(NULL == m_animation)
			return;

		reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.push_back(this);

		if (!m_isPlaying)
			return;

		
		if (m_synchGroupName.empty())
		{
			Real tickDeltaSeconds = elapsedTime * m_owner->getGlobalAnimRateScale() * m_rate;
			advanceAnimation(tickDeltaSeconds);
		}
	}

	void AASAnimSequenceNode::advanceAnimation( Real deltaSeconds )
	{
		if(!m_animation)
			return;

		m_currentTime += deltaSeconds/* * m_parent->getGlobalAnimRateScale() * m_rate*/;

		Real animLength = m_animation->getLength();

		if (m_currentTime > animLength)
		{
			if (m_isLooping)
			{
				m_currentTime = fmod(m_currentTime, animLength);
				if(m_currentTime < 0.0f)
					m_currentTime += animLength; 
			} 
			else
			{
				m_currentTime = animLength;
				//m_currentTime = 0.f;
				m_isPlaying = false;


				if(m_isCauseAnimEndEvent)
					m_owner->onAnimationEnd(this);
				if (m_isPlaying == true)
					m_currentTime = 0.f;

				/*
				if (m_isPlaying == false)
				{
					setAnimationName("");
					_refreshAnimation();
				}
				*/
			}
		}
	}

	void AASAnimSequenceNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASAnimSequenceNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,
		Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		AASNode::readFromBinary(serializer,stream,system);

		AASAnimSequenceNodeSerializerMap::iterator iter = ms_serializersMap.find(
			serializer->mVersion);

		if (ms_serializersMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + AdvancedAnimationSystemSerializer::ms_currentVersion, "AASAnimSequenceNode::readFromBinary");
		}

		iter->second->readFromBinary(serializer,stream,system,this);
	}

	size_t AASAnimSequenceNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASNode::calcSize(serializer);
		
		tmpSize += m_animationName.length() + 1;

		tmpSize += sizeof(Real);

		tmpSize += sizeof(bool);

		tmpSize += sizeof(bool); 
		
		tmpSize += sizeof(bool); 

		tmpSize += m_synchGroupName.length() + 1;

		return tmpSize;
	}

	Real AASAnimSequenceNode::getRate() const
	{
		return m_rate;
	}

	void AASAnimSequenceNode::setRate( Real val )
	{
		m_rate = val;
	}

	const Ogre::String& AASAnimSequenceNode::getAnimationName() const
	{
		return m_animationName;
	}

	void AASAnimSequenceNode::setAnimationName(const Ogre::String& val)
	{
		m_animationName = val;

		m_refreshAnimNameDirty = true;

	}

	void AASAnimSequenceNode::_refreshAnimation()
	{
		if (m_refreshAnimNameDirty && !m_animationName.empty())
		{
			m_animationID = m_owner->getAnimationIdByName(m_animationName.c_str());
			m_animation = m_owner->getAnimation(m_animationID);
			
			m_refreshAnimNameDirty = false;
		}
		else if (m_refreshAnimNameDirty)
		{
			m_animationID = INVAILD_ANIMATION_ID;
			m_animation = 0;
			m_refreshAnimNameDirty = false;
		}

		if(NULL == m_animation)
			return;

		if(m_isLooping != m_animation->getLoop())
			m_animation->setLoop(m_isLooping);
	}

	bool AASAnimSequenceNode::getLooping() const
	{
		return m_isLooping;
	}

	void AASAnimSequenceNode::setLooping( bool val )
	{
		m_isLooping = val;
	}

	void AASAnimSequenceNode::_disableAnimState()
	{
		if(!m_animation)
			return;

		if(m_animation->getEnabled())
		{
			m_animation->setTimePosition(0.0f);
			m_animation->setEnabled(false);

			/*if(m_isCauseAnimEndEvent)
				m_parent->onAnimationEnd(this);*/
		}
	}

	void AASAnimSequenceNode::_enableAnimState()
	{
		/*if(!m_animState->getEnabled())
			m_animState->setEnabled(true);*/
	}

	bool AASAnimSequenceNode::getCauseAnimEndEvent() const
	{
		return m_isCauseAnimEndEvent;
	}

	void AASAnimSequenceNode::setCauseAnimEndEvent( bool val )
	{
		m_isCauseAnimEndEvent = val;
	}

	bool AASAnimSequenceNode::getCauseAnimPlayEvent() const
	{
		return m_isCauseAnimPlayEvent;
	}

	void AASAnimSequenceNode::setCauseAnimPlayEvent( bool val )
	{
		m_isCauseAnimPlayEvent = val;
	}

	int AASAnimSequenceNode::getAnimationID() const
	{
		return m_animationID;
	}

	void AASAnimSequenceNode::setAnimationID( int val )
	{
		m_animationID = val;
	}

	bool AASAnimSequenceNode::_getRefreshAnimNameDirty() const
	{
		return m_refreshAnimNameDirty;
	}

	void AASAnimSequenceNode::_setRefreshAnimNameDirty( bool val )
	{
		m_refreshAnimNameDirty = val;
	}

	void AASAnimSequenceNode::_onBecomeActive()
	{
		m_isPlaying = true;
		m_currentTime = 0.0f;
	}

	void AASAnimSequenceNode::_onCeaseActive()
	{
		//m_isPlaying = false;
		
	}

	void AASAnimSequenceNode::playAnim( bool isLooping,Real rate, Real startTime )
	{
		m_isPlaying = true;
		m_isLooping = isLooping;
		m_rate = rate;
		m_currentTime = startTime;
		

		if(m_isCauseAnimPlayEvent)
			m_owner->onAnimationPlay(this);
	}

	/*bool AASAnimSequenceNode::getPlaying() const
	{
		return m_isPlaying;
	}*/

	/*void AASAnimSequenceNode::setPlaying( bool val )
	{
		m_isPlaying = val;
	}*/

	void AASAnimSequenceNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASAnimSequenceNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASAnimSequenceNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.20]"]=new AASAnimSequenceNodeSerializerImpl_v1_2;	
		ms_serializersMap["[AASSerializer_v1.30]"]=new AASAnimSequenceNodeSerializerImpl;
	}

	void AASAnimSequenceNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASAnimSequenceNode::_deinitSerializers");

		AASAnimSequenceNodeSerializerMap::iterator iter;
		for(iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}

		ms_serializersMap.clear();
	}

	const Ogre::String& AASAnimSequenceNode::getSynchGroupName() const
	{
		return m_synchGroupName;
	}

	void AASAnimSequenceNode::setSynchGroupName(const Ogre::String& val)
	{
		m_synchGroupName = val;
	}

	Real AASAnimSequenceNode::getCurrentTime() const
	{
		return m_currentTime;
	}

	void AASAnimSequenceNode::setCurrentTime( Real val )
	{
		m_currentTime = val;
	}

	Ogre::Real AASAnimSequenceNode::getTimeLeft() const
	{
		if(!m_animation)
			return 0.0f;
		return m_animation->getLength() - m_currentTime;
	}

	bool AASAnimSequenceNode::isAnimSequenceNode()
	{
		return true;
	}
	
	Ogre::String AASAnimSequenceNode::CmdRate::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const AASAnimSequenceNode*>(target)->getRate());
	}

	void AASAnimSequenceNode::CmdRate::doSet( void* target, const String& val )
	{
		static_cast<AASAnimSequenceNode*>(target)->setRate(
			Ogre::StringConverter::parseReal(val));
	}

	Ogre::String AASAnimSequenceNode::CmdAnimationName::doGet( const void* target ) const
	{
		return static_cast<const AASAnimSequenceNode*>(target)->getAnimationName().c_str();
	}

	void AASAnimSequenceNode::CmdAnimationName::doSet( void* target, const String& val )
	{	
		static_cast<AASAnimSequenceNode*>(target)->setAnimationName(val.c_str());
	}

	Ogre::String AASAnimSequenceNode::CmdIsLooping::doGet( const void* target ) const
	{	
		return Ogre::StringConverter::toString(
			static_cast<const AASAnimSequenceNode*>(target)->getLooping());
	}

	void AASAnimSequenceNode::CmdIsLooping::doSet( void* target, const String& val )
	{
		static_cast<AASAnimSequenceNode*>(target)->setLooping(
			Ogre::StringConverter::parseBool(val));
	}

	Ogre::String AASAnimSequenceNode::CmdIsCauseAnimEndEvent::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const AASAnimSequenceNode*>(target)->getCauseAnimEndEvent());
	}

	void AASAnimSequenceNode::CmdIsCauseAnimEndEvent::doSet( void* target, const String& val )
	{
		static_cast<AASAnimSequenceNode*>(target)->setCauseAnimEndEvent(
			Ogre::StringConverter::parseBool(val));
	}

	Ogre::String AASAnimSequenceNode::CmdIsCauseAnimPlayEvent::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const AASAnimSequenceNode*>(target)->getCauseAnimPlayEvent());
	}

	void AASAnimSequenceNode::CmdIsCauseAnimPlayEvent::doSet( void* target, const String& val )
	{
		static_cast<AASAnimSequenceNode*>(target)->setCauseAnimPlayEvent(
			Ogre::StringConverter::parseBool(val));
	}

	Ogre::String AASAnimSequenceNode::CmdSynchGroupName::doGet( const void* target ) const
	{
		return static_cast<const AASAnimSequenceNode*>(target)->getSynchGroupName().c_str();
	}

	void AASAnimSequenceNode::CmdSynchGroupName::doSet( void* target, const String& val )
	{
		static_cast<AASAnimSequenceNode*>(target)->setSynchGroupName(val.c_str());
	}

	void AASAnimSequenceNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
		AdvancedAnimationSystem* system,AASAnimSequenceNode* node )
	{
		String animationName = serializer->readString(stream);
		node->setAnimationName(animationName.c_str());
		
		Real rate = 0.0f;
		serializer->readFloats(stream,&rate,1);
		node->setRate(rate);

		bool isLooping = false;
		serializer->readBools(stream,&isLooping,1);
		node->setLooping( isLooping);

		bool isCauseAnimEndEvent = false;
		serializer->readBools(stream,&isCauseAnimEndEvent,1);
		node->setCauseAnimEndEvent(isCauseAnimEndEvent);

		bool isCauseAnimPlayEvent = false;
		serializer->readBools(stream,&isCauseAnimPlayEvent,1);
		node->setCauseAnimPlayEvent(isCauseAnimPlayEvent);

		String synchGroupName = serializer->readString(stream);
		node->setSynchGroupName(synchGroupName.c_str());
	}

	void AASAnimSequenceNodeSerializerImpl_v1_2::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
		AdvancedAnimationSystem* system,AASAnimSequenceNode* node )
	{
		String animationName = serializer->readString(stream);
		node->setAnimationName(animationName.c_str());

		Real rate = 0.0f;
		serializer->readFloats(stream,&rate,1);
		node->setRate(rate);

		bool isLooping = false;
		serializer->readBools(stream,&isLooping,1);
		node->setLooping( isLooping);

		bool isCauseAnimEndEvent = false;
		serializer->readBools(stream,&isCauseAnimEndEvent,1);
		node->setCauseAnimEndEvent(isCauseAnimEndEvent);

		bool isCauseAnimPlayEvent = false;
		serializer->readBools(stream,&isCauseAnimPlayEvent,1);
		node->setCauseAnimPlayEvent(isCauseAnimPlayEvent);
	}
}