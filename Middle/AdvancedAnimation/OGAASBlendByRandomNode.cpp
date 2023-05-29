#include "OgreHeader.h"
#include "OGAASBlendByRandomNode.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAASAnimation.h"

#include "OgreMath.h"
#include "OgreAnimationState.h"
#include "OgreStringConverter.h"

namespace Orphigine
{

	AASRandomInfo::CmdChildLoopCount			AASRandomInfo::ms_childLoopCountCmd;

	AASRandomInfo::AASRandomInfo()
		: m_childLoopCount(1)
	{
		if (createParamDictionary("RandomInfoDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();
			
			tmpDict->addParameter(Ogre::ParameterDef("LoopCount",
				"The loop count of random animation",Ogre::PT_UNSIGNED_INT),
				&ms_childLoopCountCmd);
		
		}
	}

	void AASRandomInfo::copyParameters( AASRandomInfo* dest )  const
	{
		dest->m_childLoopCount = m_childLoopCount;
	}

	unsigned int AASRandomInfo::getChildLoopCount() const
	{
		return m_childLoopCount;
	}

	void AASRandomInfo::setChildLoopCount( unsigned int val )
	{
		m_childLoopCount = val;
	}

	Ogre::String AASRandomInfo::CmdChildLoopCount::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const AASRandomInfo*>(target)->getChildLoopCount());
	}

	void AASRandomInfo::CmdChildLoopCount::doSet( void* target, const String& val )
	{
		static_cast<AASRandomInfo*>(target)->setChildLoopCount(
			Ogre::StringConverter::parseUnsignedInt(val));
	}
}

namespace Orphigine
{
	String AASBlendByRandomNode::ms_currentVersion = AdvancedAnimationSystemSerializer::ms_currentVersion;

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	void AASBlendByRandomNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
		AdvancedAnimationSystem* system ,AASBlendByRandomNode* node)
	{
		Real blendTime = 0.0f;
		serializer->readFloats(stream,&blendTime,1);
		node->setBlendTime(blendTime);

		
		unsigned int numPorts = node->getNumPorts();

		for (unsigned int i = 0;i < numPorts;i ++)
		{
			AASRandomInfo* randomInfo = node->getRandomInfo(i);

			unsigned int	childLoopCount = 0;
			serializer->readInts(stream,&childLoopCount,1);

			randomInfo->setChildLoopCount(childLoopCount);
		}
	}

	void AASBlendByRandomNodeSerializerImpl_v1_1::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
		AdvancedAnimationSystem* system ,AASBlendByRandomNode* node)
	{

	}

	void AASBlendByRandomNodeSerializerImpl_v1_2::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASBlendByRandomNode* node )
	{
		
		unsigned int numPorts = node->getNumPorts();

		for (unsigned int i = 0;i < numPorts;i ++)
		{
			AASRandomInfo* randomInfo = node->getRandomInfo(i);

			unsigned int	childLoopCount = 0;
			serializer->readInts(stream,&childLoopCount,1);

			randomInfo->setChildLoopCount(childLoopCount);
		}
	}
}

namespace Orphigine
{

	AASBlendByRandomNode::AASBlendByRandomNodeSerializerImplMap AASBlendByRandomNode::ms_serializersMap;

	AASBlendByRandomNode::AASBlendByRandomNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByRandom",system,handle)
		, m_nextPortIndex(-1)
		, m_currentAnimLoopCountDirty(0)
		, m_randomDirty(true)
	{
		m_randomInfos.clear();

		addPort("Child1");
		addPort("Child2");
		addPort("Child3");
		addPort("Child4");
		addPort("Child5");

		AASPort* tmpDefaultChild = getPort("Child1");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByRandomNode::~AASBlendByRandomNode()
	{
		m_randomInfos.clear();	
	}


	void AASBlendByRandomNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASBlendByRandomNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer, 
		Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{

		AASBlendByRandomNodeSerializerImplMap::iterator iter = ms_serializersMap.find(
			serializer->mVersion);

		if (ms_serializersMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + ms_currentVersion, "AASBlendByRandomNode::readFromBinary");
		}

		iter->second->readFromBinary(serializer,stream,system,this);
	}

	size_t AASBlendByRandomNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASCrossFadeByTimeListNode::calcSize(serializer);

		unsigned int numPorts = getNumPorts();

		for (unsigned int i = 0;i < numPorts;i ++)
		{
			AASRandomInfo* randomInfo = getRandomInfo(i);

			tmpSize += sizeof(int);
		}

		return tmpSize;
	}

	void AASBlendByRandomNode::_notifyAddPort( AASPort* port )
	{
		AASRandomInfo randomInfo;
		m_randomInfos.push_back(randomInfo);
	}

	const	AASRandomInfo* AASBlendByRandomNode::getRandomInfo( unsigned int index ) const
	{
		assert(index < (unsigned int)m_randomInfos.size() && "AASBlendByRandomNode::getRandomInfo");

		return &m_randomInfos[index];
	}

	AASRandomInfo* AASBlendByRandomNode::getRandomInfo( unsigned int index )
	{
		assert(index < (unsigned int)m_randomInfos.size() && "AASBlendByRandomNode::getRandomInfo");

		return &m_randomInfos[index];
	}

	unsigned int AASBlendByRandomNode::getNumRandomInfos() const
	{
		return (unsigned int)m_randomInfos.size();
	}

	void AASBlendByRandomNode::_notifyDisconnectPort( AASPort* port )
	{
		m_randomDirty = true;
	}

	void AASBlendByRandomNode::addRandomInfo( const AASRandomInfo& randomInfo )
	{
		m_randomInfos.push_back(randomInfo);
	}

	void AASBlendByRandomNode::copyParameters( AASNode* dest )
	{
		AASCrossFadeByTimeListNode::copyParameters(dest);

		AASBlendByRandomNode* destRandomNode = (AASBlendByRandomNode*)dest;
		assert(destRandomNode && "AASBlendByRandomNode::copyParametersTo");

		unsigned int numRandomInfos = getNumRandomInfos();
		assert(numRandomInfos == destRandomNode->getNumRandomInfos() && 
			"AASBlendByRandomNode::copyParametersTo");

		for (unsigned int i = 0;i < numRandomInfos;i ++)
		{
			const AASRandomInfo* sourceRandomInfo = getRandomInfo(i);
			AASRandomInfo* targetRandomInfo = destRandomNode->getRandomInfo(i);
			sourceRandomInfo->copyParameters(targetRandomInfo);
		}
	}

	void AASBlendByRandomNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		assert(m_activeChildIndex >= 0 && m_activeChildIndex < (int)getNumPorts() && "AASBlendByRandomNode::tickAnimation");

		AASPort* activePort = getPort(m_activeChildIndex);
		if(!activePort)
			return;

		AASNode* activeNode = activePort->getConnectedNode();
		if (activeNode && activeNode->isAnimSequenceNode())
		{
			AASAnimSequenceNode* tmpAnimSequenceNode = (AASAnimSequenceNode*)activeNode;
			
			if (tmpAnimSequenceNode->getTimeLeft() <= m_blendTime)
				playNextAnimation(elapsedTime,tmpAnimSequenceNode->getTimeLeft(),tmpAnimSequenceNode->getTimeLeft());
		}
		
		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}

	void AASBlendByRandomNode::playNextAnimation( Real deltaSeconds,Real timeLeft,Real blendTime /*= 0.0f*/,Real startTime /*= 0.0f*/)
	{	
		if(m_nextPortIndex < 0 || m_nextPortIndex > (int)getNumPorts())
		{
			decidingNextChildPort();
		}
		if(m_nextPortIndex < 0 || m_nextPortIndex > (int)getNumPorts())
			m_nextPortIndex = 0;

		AASRandomInfo* randomInfo  = getRandomInfo(m_activeChildIndex);
		if(m_currentAnimLoopCountDirty >= randomInfo->getChildLoopCount() - 1)
		{
			m_currentAnimLoopCountDirty = 0;
			setActiveChild(m_nextPortIndex,blendTime);
			decidingNextChildPort();
		}
		else if(timeLeft <= deltaSeconds)
		{
			m_currentAnimLoopCountDirty ++;
			setActiveChild(m_activeChildIndex,blendTime);
		}
	}

	void AASBlendByRandomNode::decidingNextChildPort()
	{
		unsigned int	tmpNumPorts = getNumPorts();
		AASNode*		tmpConnectedNode = NULL;
		AASPort*		tmpPort = NULL;
		unsigned int	tmpMaxIteration = 0;
		AASPort*		activePort	 = getPort(m_activeChildIndex);

		m_nextPortIndex = m_activeChildIndex;
		while(m_activeChildIndex == m_nextPortIndex && 5 > tmpMaxIteration)
		{
			float	tmpRandom = Ogre::Math::RangeRandom(0.0f,0.99f);

			unsigned int	tmpIndex = (unsigned int)(tmpRandom * tmpNumPorts);
			assert(0 <= tmpIndex && tmpIndex < tmpNumPorts && "AASBlendByRandomNode::tickAnimation()");

			tmpPort = getPort(tmpIndex);

			tmpConnectedNode = tmpPort->getConnectedNode();

			if (NULL == tmpConnectedNode)
			{
				tmpMaxIteration ++;
				continue;
			}

			if (!tmpConnectedNode->isAnimSequenceNode())
			{
				tmpMaxIteration ++;
				continue;
			}

			AASAnimSequenceNode* tmpAnimSequenceNode = (AASAnimSequenceNode*)tmpConnectedNode;
			tmpAnimSequenceNode->_refreshAnimation();
			int animID = tmpAnimSequenceNode->getAnimationID();
			AASAnimation*	animation = m_owner->getAnimation(animID);
			if (!animation)
			{
				tmpMaxIteration ++;
				continue;
			}

			m_nextPortIndex = tmpPort->getHandle();
		}
	}
	void AASBlendByRandomNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASBlendByRandomNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASBlendByRandomNodeSerializerImpl_v1_1;
		ms_serializersMap["[AASSerializer_v1.20]"] = new AASBlendByRandomNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.30]"] = new AASBlendByRandomNodeSerializerImpl;
	}

	void AASBlendByRandomNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASBlendByRandomNode::_deinitSerializers");

		AASBlendByRandomNodeSerializerImplMap::iterator iter;
		for (iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		ms_serializersMap.clear();
	}

	void AASBlendByRandomNode::_onBecomeActive()
	{
		decidingNextChildPort();
		playNextAnimation(m_blendTime,0.0f);
	}
}