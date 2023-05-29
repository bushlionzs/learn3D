#include "OgreHeader.h"
#include "OGAASBlendByPostureNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByPostureNode::AASBlendByPostureNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByPosture",system,handle)
	{
		m_standPort = addPort("Stand");
		m_sitPort = addPort("Sit");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByPostureNode::~AASBlendByPostureNode()
	{

	}

	AASPort* AASBlendByPostureNode::getStandPort() const
	{
		return m_standPort;
	}

	void AASBlendByPostureNode::setStandPort( AASPort* val )
	{
		m_standPort = val;
	}

	AASPort* AASBlendByPostureNode::getSitPort() const
	{
		return m_sitPort;
	}

	void AASBlendByPostureNode::setSitPort( AASPort* val )
	{
		m_sitPort = val;
	}

	void AASBlendByPostureNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
{
		Real tmpPostureDegree = m_owner->getPostureDegree();

		if (0.5f > tmpPostureDegree && m_standPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_standPort,m_blendTime);
		else if(0.5 <= tmpPostureDegree && m_sitPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_sitPort,m_blendTime);

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);

	}
}