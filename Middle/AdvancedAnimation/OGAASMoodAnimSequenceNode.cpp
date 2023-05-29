#include "OgreHeader.h"
#include "OGAASMoodAnimSequenceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASAnimation.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);


	AASMoodAnimSequenceNode::AASMoodAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle)
		:AASAnimSequenceNode("MoodAnimSequence",system,handle)
	{
		if(AASAnimSequenceNode::initParameter(m_type.c_str()))
		{
		}
	}

	AASMoodAnimSequenceNode::~AASMoodAnimSequenceNode()
	{

	}

	void AASMoodAnimSequenceNode::_refreshAnimation()
	{
		AASAnimSequenceNode::_refreshAnimation();

		String	tmpMoodAnimName = m_owner->getMoodAnimName();

		if(tmpMoodAnimName.empty())
			return;

		if(NULL != m_animation )
		{
			if (m_owner->getMoodAnimDirty())
			{
				_disableAnimState();

				m_animationID = m_owner->getAnimationIdByName(tmpMoodAnimName);
				m_animation = m_owner->getAnimation(m_animationID);
			}
		}
		else
		{
			m_animationID = m_owner->getAnimationIdByName(tmpMoodAnimName);
			m_animation = m_owner->getAnimation(m_animationID);
			
		}
	}
}
