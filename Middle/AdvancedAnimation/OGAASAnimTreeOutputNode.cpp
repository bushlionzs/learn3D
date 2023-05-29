#include "OgreHeader.h"
#include "OGAASAnimTreeOutputNode.h"
#include "OGAASPort.h"
#include "OGAASFileFormat.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASAnimTreeOutputNode::AASAnimTreeOutputNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeNode("AnimTree",system,handle)
	{
		m_inPort = addPort("Animation");

		
	}

	AASAnimTreeOutputNode::~AASAnimTreeOutputNode()
	{

	}

	AASPort* AASAnimTreeOutputNode::getInPort() const
	{
		return m_inPort;
	}

	void AASAnimTreeOutputNode::setInPort(AASPort* val )
	{
		m_inPort = val;
	}

	void AASAnimTreeOutputNode::initAnim( AASNode* parentNode )
	{
		AASCrossFadeNode::initAnim(parentNode);

		setBlendWeight(1.0f);
		m_blendWeightAccumulater = 1.0f;
		setNodeTotalWeight(1.0f);
		m_inPort->setBlendWeight(1.0f);
		setActive(true);
	}
	/*void AASAnimTreeOutputNode::tickAnimation(const float elapsedTime,
		ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection)
	{
		AASNode* childNode = m_inPort->getConnectedNode();
		if (childNode)
			childNode->setBlendWeight(getBlendWeight());

	}*/
}