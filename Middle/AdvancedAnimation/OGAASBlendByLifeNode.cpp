#include "OgreHeader.h"
#include "OGAASBlendByLifeNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByLifeNode::AASBlendByLifeNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByLife",system,handle)
	{
		m_livingPort = addPort("Living");
		m_deathPort	= addPort("Death");
		m_corpsePort = addPort("Corpse");
		m_beatBackPort = addPort("BeatBack");

		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByLifeNode::~AASBlendByLifeNode()
	{

	}

	AASPort* AASBlendByLifeNode::getLivingPort() const
	{
		return m_livingPort;
	}

	void AASBlendByLifeNode::setLivingPort( AASPort* val)
	{
		m_livingPort = val;
	}

	AASPort* AASBlendByLifeNode::getDeathPort() const
	{
		return m_deathPort;
	}

	void AASBlendByLifeNode::setDeathPort( AASPort* val )
	{
		m_deathPort = val;
	}

	AASPort* AASBlendByLifeNode::getBeatBackPort() const
	{
		return m_beatBackPort;
	}

	void AASBlendByLifeNode::setBeatBackPort( AASPort* val )
	{
		m_beatBackPort = val;
	}

	AASPort* AASBlendByLifeNode::getCorpsePort() const
	{
		return m_corpsePort;
	}

	void AASBlendByLifeNode::setCorpsePort( AASPort* val )
	{
		m_corpsePort = val;
	}

	void AASBlendByLifeNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
{
		Real tmpLivingDegree = m_owner->getLivingDegree();

		unsigned int portIndex = _generateAveragePortIndexByDegreeAuto(tmpLivingDegree);
		AASPort*   currentPort = getPort(portIndex);

		if(portIndex != m_activeChildIndex)
			setActiveChild(currentPort,m_blendTime);

		AASCrossFadeByTimeListNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);

	}
}