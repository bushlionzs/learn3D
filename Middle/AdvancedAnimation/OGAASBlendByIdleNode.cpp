#include "OgreHeader.h"
#include "OGAASBlendByIdleNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByIdleNode::AASBlendByIdleNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByIdle",system,handle)
	{
		m_idlePort = addPort("Idle");
		m_movingPort = addPort("Moving");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}

	}

	AASBlendByIdleNode::~AASBlendByIdleNode()
	{

	}

	AASPort* AASBlendByIdleNode::getIdlePort() const
	{
		return m_idlePort;
	}

	void AASBlendByIdleNode::setIdlePort( AASPort* val )
	{
		m_idlePort = val;
	}

	AASPort* AASBlendByIdleNode::getMovingPort() const
	{
		return m_movingPort;
	}

	void AASBlendByIdleNode::setMovingPort( AASPort* val )
	{
		m_movingPort = val;
	}

	void AASBlendByIdleNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		Real tmpMovingDegree = m_owner->getMovingDegree();

		if (0.5f > tmpMovingDegree && m_idlePort->getHandle() != m_activeChildIndex)
			setActiveChild(m_idlePort,m_blendTime);
		else if (0.5 < tmpMovingDegree )
		{
			if (m_movingPort->getHandle() != m_activeChildIndex)
			{
				setActiveChild(m_movingPort, m_blendTime);
			}
				
		}
			

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}