#include "OgreHeader.h"
#include "OGAASBlendByDanceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByDanceNode::AASBlendByDanceNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeListNode("BlendByDance",system,handle)
	{
		m_defaultPort  = addPort("Default");
		m_dancing1Port = addPort("Dancing1");
		m_dancing2Port = addPort("Dancing2");
		m_dancing3Port = addPort("Dancing3");
		m_dancing4Port = addPort("Dancing4");
		m_dancing5Port = addPort("Dancing5");
		m_dancing6Port = addPort("Dancing6");
		m_dancing7Port = addPort("Dancing7");
		m_dancing8Port = addPort("Dancing8");
		m_dancing9Port = addPort("Dancing9");
		m_dancing10Port = addPort("Dancing10");



		if (AASCrossFadeByTimeListNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByDanceNode::~AASBlendByDanceNode()
	{

	}
}