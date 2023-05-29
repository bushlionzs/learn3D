#include "OgreHeader.h"
#include "OGAASBlendByAttackNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASPort.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAASAnimation.h"

#include "OgreStringConverter.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByAttackNode::AASBlendByAttackNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeWithMaskNode("BlendByAttack",system,handle)
		, m_nonattackPort(NULL)
		, m_attackPort(NULL)
	{
		m_nonattackPort = addPort("Nonattack");
		m_attackPort = addPort("Attack");

		setSourcePort(m_nonattackPort);
		setTargetPort(m_attackPort);

		if (AASCrossFadeByTimeWithMaskNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByAttackNode::~AASBlendByAttackNode()
	{

	}

	AASPort* AASBlendByAttackNode::getAttackPort() const
	{
		return m_attackPort;
	}

	void AASBlendByAttackNode::setAttackPort( AASPort* val )
	{
		m_attackPort = val;
	}

	AASPort* AASBlendByAttackNode::getNonattackPort() const
	{
		return m_nonattackPort;
	}

	void AASBlendByAttackNode::setNonattackPort( AASPort* val )
	{
		m_nonattackPort = val;
	}
	
	void AASBlendByAttackNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
{
		Real tmpAttackDegree = AASNode::getParent()->getAttackDegree();

		unsigned int portIndex = _generateAveragePortIndexByDegreeAuto(tmpAttackDegree);
		AASPort*   currentPort = getPort(portIndex);

		AASPort* port1 = getPort(1);
		assert(port1 && "AASBlendByAttackNode::tickAnimation");
		if(port1)
		{
			if(!Ogre::Math::RealEqual(m_child2WeightTarget,tmpAttackDegree))
				setBlendTarget(tmpAttackDegree,m_blendTime);
		}

		AASCrossFadeByTimeWithMaskNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}