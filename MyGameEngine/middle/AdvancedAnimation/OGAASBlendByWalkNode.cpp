#include "OgreHeader.h"
#include "OGAASBlendByWalkNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByWalkNode::AASBlendByWalkNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByWalk",system,handle)
	{
		m_runPort = addPort("Run");
		m_walkPort = addPort("Walk");

		setActiveChild(m_runPort,0.0f);

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByWalkNode::~AASBlendByWalkNode()
	{

	}

	AASPort* AASBlendByWalkNode::getWalkPort() const
	{
		return m_walkPort;
	}

	void AASBlendByWalkNode::setWalkPort( AASPort* val )
	{
		m_walkPort = val;
	}

	AASPort* AASBlendByWalkNode::getRunPort() const
	{
		return m_runPort;
	}

	void AASBlendByWalkNode::setRunPort( AASPort* val )
	{
		m_runPort = val;
	}

	void AASBlendByWalkNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
{
		Real tmpWalkDegree = m_owner->getWalkDegree();

		unsigned int portIndex = _generateAveragePortIndexByDegreeAuto(tmpWalkDegree);
		AASPort*   currentPort = getPort(portIndex);
		
		if(portIndex != m_activeChildIndex)
			setActiveChild(currentPort,m_blendTime);

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}
