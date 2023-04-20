#include "OgreHeader.h"
#include "OGAASBlendByGuardNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	Orphigine::AASBlendByGuardNode::AASBlendByGuardNode( AdvancedAnimationSystem* system,unsigned short handle )
		: AASCrossFadeByTimeListNode("BlendByGuard",system,handle)
	{		
		m_nonguardedPort	= addPort("Nonguarded");
		m_guardPort			= addPort("Guard");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByGuardNode::~AASBlendByGuardNode()
	{

	}

	AASPort* Orphigine::AASBlendByGuardNode::getNonguardedPort() const
	{
		return m_nonguardedPort;
	}

	void Orphigine::AASBlendByGuardNode::setNonguardedPort( AASPort* val )
	{
		m_nonguardedPort = val;
	}

	AASPort* Orphigine::AASBlendByGuardNode::getGuardPort() const
	{
		return m_guardPort;
	}

	void Orphigine::AASBlendByGuardNode::setGuardPort( AASPort* val )
	{
		m_guardPort = val;
	}


	void AASBlendByGuardNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		Real tmpGuardDegree = m_owner->getGuardDegree();

		if (0.5f > tmpGuardDegree && m_nonguardedPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_nonguardedPort,m_blendTime);
		else if(0.5f < tmpGuardDegree && m_guardPort->getHandle() != m_activeChildIndex)
			setActiveChild(m_guardPort,m_blendTime);

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);

	}
}

