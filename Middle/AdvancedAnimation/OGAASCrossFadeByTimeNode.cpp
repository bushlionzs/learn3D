#include "OgreHeader.h"
#include "OGAASCrossFadeByTimeNode.h"
#include "OGAASPort.h"

#include "OgreMath.h"
#include "OgreStringConverter.h"

namespace Orphigine
{

	AASCrossFadeByTimeNode::CmdBlendTime	AASCrossFadeByTimeNode::ms_blendTimeCmd;
	AASCrossFadeByTimeNode::AASCrossFadeByTimeNodeSerializerMap AASCrossFadeByTimeNode::ms_serializersMap;

	AASCrossFadeByTimeNode::AASCrossFadeByTimeNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeNode(typeName,system,handle)
		, m_timeLeft(0.0f)
		, m_blendTime(0.25f)
		, m_child2WeightTarget(0.0f)
	{
	}

	AASCrossFadeByTimeNode::~AASCrossFadeByTimeNode()
	{

	}

	void AASCrossFadeByTimeNode::initAnim( AASNode* parentNode )
	{
		AASCrossFadeNode::initAnim(parentNode);

		if (0.0001f > getTotalChildrenWeight())
		{
			setBlendTarget(0.0f,0.0f);
		}
	}

	void AASCrossFadeByTimeNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		if (m_timeLeft > 0.0f)
		{
			AASPort* port0 = getPort(0);
			assert(port0 && "AASCrossFadeByTimeNode::setBlendTarget");

			AASPort* port1 = getPort(1);
			assert(port1 && "AASCrossFadeByTimeNode::setBlendTarget");

			if (m_timeLeft < elapsedTime)
			{
				m_timeLeft = 0.0f;
				
				if(port0)
					port0->setBlendWeight(1 - m_child2WeightTarget);
				
				if(port1)
					port1->setBlendWeight(m_child2WeightTarget);
			} 
			else
			{
				if(port1)
				{
					Real deltaWeight = (elapsedTime / m_timeLeft) * (m_child2WeightTarget - port1->getBlendWeight());

					port1->setBlendWeight(port1->getBlendWeight() + deltaWeight);
				}

				if(port0)
				{
					port0->setBlendWeight(1.0f - port1->getBlendWeight());
				}

				m_timeLeft -= elapsedTime;
			}
		} 

		AASCrossFadeNode::tickAnimation(elapsedTime,
			reachedAnimSequenceNodeCollection);
	}

	void AASCrossFadeByTimeNode::setBlendTarget( Real blendTarget,Real blendTime )
	{
		if (0.0f > blendTarget)
		{
			assert("AASCrossFadeByTimeNode::setBlendTarget");
			blendTarget = 0.0f;
		}
		if (1.0f < blendTarget)
		{
			assert("AASCrossFadeByTimeNode::setBlendTarget");
			blendTarget = 1.0f;
		}

		m_child2WeightTarget = blendTarget;

		if (Ogre::Math::RealEqual(blendTime,0.0f))
		{
			AASPort* port0 = getPort(0);
			assert(port0 && "AASCrossFadeByTimeNode::setBlendTarget");
			if(port0)
				port0->setBlendWeight(1.0f - m_child2WeightTarget);

			AASPort* port1 = getPort(1);
			assert(port1 && "AASCrossFadeByTimeNode::setBlendTarget");
			if(port1)
				port1->setBlendWeight(m_child2WeightTarget);
		}
		m_timeLeft = blendTime;
	}

	Real AASCrossFadeByTimeNode::getTimeLeft() const
	{
		return m_timeLeft;
	}

	void AASCrossFadeByTimeNode::setTimeLeft( const Real val )
	{
		m_timeLeft = val;
	}

	Real AASCrossFadeByTimeNode::getBlendTime() const
	{
		return m_blendTime;
	}

	void AASCrossFadeByTimeNode::setBlendTime( const Real val )
	{
		m_blendTime = val;
	}

	bool AASCrossFadeByTimeNode::initParameter( const String& typeName )
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

	void AASCrossFadeByTimeNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASCrossFadeByTimeNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system )
	{
		AASCrossFadeNode::readFromBinary(serializer,stream,system);

		serializer->readFloats(stream,&m_blendTime,1);
	}

	size_t AASCrossFadeByTimeNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASCrossFadeNode::calcSize(serializer);

		tmpSize += sizeof(float);
	
		return tmpSize;
	}

	void AASCrossFadeByTimeNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASCrossFadeByTimeNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASCrossFadeByTimeNodeSerializerImpl;
		ms_serializersMap["[AASSerializer_v1.20]"]=new AASCrossFadeByTimeNodeSerializerImpl;	
		ms_serializersMap["[AASSerializer_v1.30]"]=new AASCrossFadeByTimeNodeSerializerImpl;
	}

	void AASCrossFadeByTimeNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASCrossFadeByTimeNode::_deinitSerializers");
		
		AASCrossFadeByTimeNodeSerializerMap::iterator iter;
		for(iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}

		ms_serializersMap.clear();
	}

	void AASCrossFadeByTimeNode::copyParameters( AASNode* dest )
	{
		AASCrossFadeNode::copyParameters(dest);

		AASCrossFadeByTimeNode* destNode = (AASCrossFadeByTimeNode*)dest;
		assert(destNode && "AASCrossFadeByTimeNode::copyParameters");

		destNode->m_blendTime = m_blendTime;
	}

	Ogre::String AASCrossFadeByTimeNode::CmdBlendTime::doGet( const void* target ) const
	{
		return	Ogre::StringConverter::toString(static_cast<const AASCrossFadeByTimeNode*>(target)->
			getBlendTime());
	}

	void AASCrossFadeByTimeNode::CmdBlendTime::doSet( void* target, const String& val )
	{
		static_cast<AASCrossFadeByTimeNode*>(target)->setBlendTime(Ogre::StringConverter::parseReal(
			val));
	}

	void AASCrossFadeByTimeNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASCrossFadeByTimeNode* node )
	{

	}
}