#include "OgreHeader.h"
#include "OGAASBlendByEquitationNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	Orphigine::AASBlendByEquitationNode::AASBlendByEquitationNode( AdvancedAnimationSystem* system,unsigned short handle )
		: AASCrossFadeByTimeListNode("BlendByEquitation",system,handle)
	{
		m_defaultPort	= addPort("Default");
		m_hoofUpPort	= addPort("HoofUp");
		m_jumpPort		= addPort("Jump");

		setActiveChild(m_defaultPort,0.0f);

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	Orphigine::AASBlendByEquitationNode::~AASBlendByEquitationNode()
	{

	}

	void AASBlendByEquitationNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		Real tmpEquitationDegree = m_owner->getEquitationDegree();

		if (0.33f > tmpEquitationDegree)
		{
			if (m_defaultPort->getHandle() != m_activeChildIndex)
			{
				setActiveChild(m_defaultPort,m_blendTime);
			}
		}
		else if(0.33f <= tmpEquitationDegree && 0.66f > tmpEquitationDegree)
		{
			if (m_hoofUpPort->getHandle() != m_activeChildIndex)
			{
				setActiveChild(m_hoofUpPort,m_blendTime);
			}
		}
		else
		{
			if (m_jumpPort->getHandle() != m_activeChildIndex)
			{
				setActiveChild(m_jumpPort,m_blendTime);
			}
		}

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}

	AASPort* Orphigine::AASBlendByEquitationNode::getDefaultPort() const
	{
		return m_defaultPort;
	}

	void Orphigine::AASBlendByEquitationNode::setDefaultPort( AASPort* val )
	{
		m_defaultPort = val;
	}

	AASPort* Orphigine::AASBlendByEquitationNode::getHoofUpPort() const
	{
		return m_hoofUpPort;
	}

	void Orphigine::AASBlendByEquitationNode::setHoofUpPort( AASPort* val )
	{
		m_hoofUpPort = val;
	}

	AASPort* Orphigine::AASBlendByEquitationNode::getJumpPort() const
	{
		return m_jumpPort;
	}

	void Orphigine::AASBlendByEquitationNode::setJumpPort( AASPort* val )
	{
		m_jumpPort = val;
	}
}

