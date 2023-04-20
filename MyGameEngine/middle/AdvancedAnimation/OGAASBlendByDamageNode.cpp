#include "OgreHeader.h"
#include "OGAASBlendByDamageNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASFileFormat.h"
#include "OGAASAnimation.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAASPort.h"

#include "OgreMath.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASBlendByDamageNode::AASBlendByDamageNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeWithMaskNode("BlendByDamage",system,handle)
		, m_defaultPort(NULL)
		, m_damagePort(NULL)
	{
		m_defaultPort = addPort("Default");
		m_damagePort = addPort("Damage");

		setSourcePort(m_defaultPort);
		setTargetPort(m_damagePort);

		if (AASCrossFadeByTimeWithMaskNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByDamageNode::~AASBlendByDamageNode()
	{

	}

	AASPort* AASBlendByDamageNode::getDefaultPort() const
	{
		return m_defaultPort;
	}

	void AASBlendByDamageNode::setDefaultPort( AASPort* val )
	{
		m_defaultPort = val;
	}

	AASPort* AASBlendByDamageNode::getDamagePort() const
	{
		return m_damagePort;
	}

	void AASBlendByDamageNode::setDamagePort( AASPort* val )
	{
		m_damagePort = val;
	}

	void AASBlendByDamageNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		Real tmpDamageDegree = AASNode::getParent()->getDamageDegree();

		unsigned int portIndex = _generateAveragePortIndexByDegreeAuto(tmpDamageDegree);
		AASPort*   currentPort = getPort(portIndex);

		AASPort* port1 = getPort(1);
		assert(port1 && "AASBlendByAttackNode::tickAnimation");
		if(port1)
		{
			if(!Ogre::Math::RealEqual(m_child2WeightTarget,tmpDamageDegree))
				setBlendTarget(tmpDamageDegree,m_blendTime);
		}

		AASCrossFadeByTimeWithMaskNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}