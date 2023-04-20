#include "OgreHeader.h"
#include "OGAASCrossFadeByTimeListNode.h"
#include "OGAASPort.h"
#include "OGAASAnimSequenceNode.h"

#include "OgreMath.h"
#include "OgreStringConverter.h"

namespace Orphigine
{

	AASCrossFadeByTimeListNode::CmdBlendTime	AASCrossFadeByTimeListNode::ms_blendTimeCmd;
	AASCrossFadeByTimeListNode::AASCrossFadeByTimeListNodeSerializerMap AASCrossFadeByTimeListNode::ms_serializersMap;

	AASCrossFadeByTimeListNode::AASCrossFadeByTimeListNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeNode(typeName,system,handle)
		, m_activeChildIndex(0)
		, m_timeLeft(0.0f)
		, m_blendTime(0.25f)
	{
		initParameter("CrossFadeByTimeList");
	}

	AASCrossFadeByTimeListNode::~AASCrossFadeByTimeListNode()
	{
		
	}

	void AASCrossFadeByTimeListNode::initAnim( AASNode* parentNode )
	{
		AASCrossFadeNode::initAnim(parentNode);

		AASPort* port = getPort(0);
	
		if (0.0001f > getTotalChildrenWeight())
		{
			setActiveChild(port,0.0f);
		}
	}

	void AASCrossFadeByTimeListNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		if (m_timeLeft > 0.0f)
		{
			if (m_timeLeft < elapsedTime)
			{
				m_timeLeft = 0.0f;
				for (unsigned int i = 0;i < getNumPorts();i ++)
				{
					AASPort* port = getPort(i);
					port->setBlendWeight(port->getTargetWeight());
				}
			} 
			else
			{
				for (unsigned int i = 0;i < getNumPorts();i ++)
				{	
					AASPort* port = getPort(i);
			
					Real deltaWeight = (elapsedTime / m_timeLeft) * (port->getTargetWeight() - port->getBlendWeight());

					port->setBlendWeight(port->getBlendWeight() + deltaWeight);
				}

				m_timeLeft -= elapsedTime;
			}
		} 

		AASCrossFadeNode::tickAnimation(elapsedTime,
			reachedAnimSequenceNodeCollection);
	}

	void AASCrossFadeByTimeListNode::setActiveChild( AASPort* activePort ,Real	blendTime)
	{
		AASPort* activeChildPort = activePort;
		if(!activeChildPort)
			activeChildPort = getPort(0);

		if(!activeChildPort)
		{
			assert("Port数目不能为空 AASCrossFadeByTimeListNode::setActiveChild ");
			return;
		}

		setActiveChild(activeChildPort->getHandle(),blendTime);
	}

	void AASCrossFadeByTimeListNode::setActiveChild( unsigned short childIndex,Real blendTime )
	{
		AASPort* activeChildPort = getPort(childIndex);

		if(!activeChildPort)
			activeChildPort = getPort(0);

		if(!activeChildPort)
		{
			assert("Port数目不能为空 AASCrossFadeByTimeListNode::setActiveChild ");
			return;
		}

		m_activeChildIndex = activeChildPort->getHandle();

		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);
			if (port == activeChildPort)
			{
				port->setTargetWeight(1.0f);

				if(Ogre::Math::RealEqual(blendTime,0.0f))
					port->setBlendWeight(1.0f);
			} 
			else
			{
				port->setTargetWeight(0.0f);

				if(Ogre::Math::RealEqual(blendTime,0.0f))
					port->setBlendWeight(0.0f);
			}
		}

		m_timeLeft = blendTime;

		AASNode* activeChildNode = activeChildPort->getConnectedNode();
		if(activeChildNode && activeChildNode->isAnimSequenceNode())
		{
			AASAnimSequenceNode* animSeqNode = (AASAnimSequenceNode*)activeChildNode;
			animSeqNode->playAnim(animSeqNode->getLooping(),animSeqNode->getRate());
		}
	}

	Real AASCrossFadeByTimeListNode::getTimeLeft() const
	{
		return m_timeLeft;
	}

	void AASCrossFadeByTimeListNode::setTimeLeft( const Real val )
	{
		m_timeLeft = val;
	}

	Real AASCrossFadeByTimeListNode::getBlendTime() const
	{
		return m_blendTime;
	}

	void AASCrossFadeByTimeListNode::setBlendTime( const Real val )
	{
		m_blendTime = val;
	}

	bool AASCrossFadeByTimeListNode::initParameter( const String& typeName )
	{
		if (AASCrossFadeNode::initParameter(typeName))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();
			
			tmpDict->addParameter(Ogre::ParameterDef("blendtime","The duration of blend",Ogre::PT_REAL),
				&ms_blendTimeCmd);

			return true;
		}

		return false;
	}

	void AASCrossFadeByTimeListNode::copyParameters( AASNode* dest )
	{
		AASCrossFadeNode::copyParameters(dest);

		AASCrossFadeByTimeListNode* destNode = (AASCrossFadeByTimeListNode*)dest;
		assert(destNode && "AASCrossFadeByTimeListNode::copyParameters");

		destNode->m_blendTime = m_blendTime;
	}

	void AASCrossFadeByTimeListNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASCrossFadeByTimeListNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system )
	{
		AASCrossFadeNode::readFromBinary(serializer,stream,system);

		
		serializer->readFloats(stream,&m_blendTime,1);
	}

	size_t AASCrossFadeByTimeListNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = 0.0f;

		tmpSize += AASCrossFadeNode::calcSize(serializer);

		tmpSize += sizeof(float);

		return tmpSize;
	}

	void AASCrossFadeByTimeListNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASCrossFadeByTimeListNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASCrossFadeByTimeListNodeSerializerImpl;
		ms_serializersMap["[AASSerializer_v1.20]"] = new AASCrossFadeByTimeListNodeSerializerImpl;
		ms_serializersMap["[AASSerializer_v1.30]"] = new AASCrossFadeByTimeListNodeSerializerImpl;
	}

	void AASCrossFadeByTimeListNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASCrossFadeByTimeListNode::_deinitSerializers");
		
		AASCrossFadeByTimeListNodeSerializerMap::iterator iter;
		for(iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}

		ms_serializersMap.clear();
	}

	Ogre::String AASCrossFadeByTimeListNode::CmdBlendTime::doGet( const void* target ) const
	{
		return	Ogre::StringConverter::toString(static_cast<const AASCrossFadeByTimeListNode*>(target)->
			getBlendTime());
	}

	void AASCrossFadeByTimeListNode::CmdBlendTime::doSet( void* target, const String& val )
	{
		static_cast<AASCrossFadeByTimeListNode*>(target)->setBlendTime(Ogre::StringConverter::parseReal(
			val));
	}

	void AASCrossFadeByTimeListNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASCrossFadeByTimeListNode* node )
	{

	}
}