#include "OgreHeader.h"
#include "OGAASBlendByRidingNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByRidingNode::AASBlendByRidingNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByRiding",system,handle)
	{
		m_nonridingPort = addPort("Nonriding");
		m_ridingPort = addPort("Riding");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByRidingNode::~AASBlendByRidingNode()
	{

	}

	AASPort* AASBlendByRidingNode::getRidingPort() const
	{
		return m_ridingPort;
	}

	void AASBlendByRidingNode::setRidingPort( AASPort* val )
	{
		m_ridingPort = val;
	}

	AASPort* AASBlendByRidingNode::getNonridingPort() const
	{
		return m_nonridingPort;
	}

	void AASBlendByRidingNode::setNonridingPort( AASPort* val )
	{
		m_nonridingPort = val;
	}

	void AASBlendByRidingNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		Real tmpRidingDegree = m_owner->getRidingDegree();

		if (0.5f > tmpRidingDegree && m_nonridingPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_nonridingPort,m_blendTime);
		else if(0.5 <= tmpRidingDegree && m_ridingPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_ridingPort,m_blendTime);

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}