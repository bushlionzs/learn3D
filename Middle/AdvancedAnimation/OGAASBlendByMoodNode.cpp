#include "OgreHeader.h"
#include "OGAASBlendByMoodNode.h"
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

	AASBlendByMoodNode::CmdBranchBoneName		AASBlendByMoodNode::ms_branchBoneNameCmd;

	AASBlendByMoodNode::AASBlendByMoodNode(AdvancedAnimationSystem* system,unsigned short handle)
		: AASCrossFadeByTimeWithMaskNode("BlendByMood",system,handle)
		, m_nonmoodPort(NULL)
		, m_moodPort(NULL)
	{
		m_nonmoodPort = addPort("Nonmood");
		m_moodPort = addPort("Mood");

		setSourcePort(m_nonmoodPort);
		setTargetPort(m_moodPort);

		if (AASCrossFadeByTimeWithMaskNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASBlendByMoodNode::~AASBlendByMoodNode()
	{

	}

	AASPort* AASBlendByMoodNode::getMoodPort() const
	{
		return m_moodPort;
	}

	void AASBlendByMoodNode::setMoodPort( AASPort* val )
	{
		m_moodPort = val;
	}

	AASPort* AASBlendByMoodNode::getNonmoodPort() const
	{
		return m_nonmoodPort;
	}

	void AASBlendByMoodNode::setNonmoodPort( AASPort* val )
	{
		m_nonmoodPort = val;
	}

	void AASBlendByMoodNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		Real tmpMoodDegree = AASNode::getParent()->getMoodDegree();

		unsigned int portIndex = _generateAveragePortIndexByDegreeAuto(tmpMoodDegree);

		AASPort*   currentPort = getPort(portIndex);

		AASPort* port1 = getPort(1);
		assert(port1 && "AASBlendByAttackNode::tickAnimation");
		if(port1)
		{
			if(!Ogre::Math::RealEqual(m_child2WeightTarget,tmpMoodDegree))
				setBlendTarget(tmpMoodDegree,m_blendTime);
		}

		AASCrossFadeByTimeWithMaskNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}
}