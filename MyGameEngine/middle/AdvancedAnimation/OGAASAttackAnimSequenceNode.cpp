#include "OgreHeader.h"
#include "OGAASAttackAnimSequenceNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASAnimation.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);


	AASAttackAnimSequenceNode::AASAttackAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle)
		:AASAnimSequenceNode("AttackAnimSequence",system,handle)
	{
		if(AASAnimSequenceNode::initParameter(m_type.c_str()))
		{

		}
	}

	AASAttackAnimSequenceNode::~AASAttackAnimSequenceNode()
	{
 
	}

	void AASAttackAnimSequenceNode::_refreshAnimation()
	{
		AASAnimSequenceNode::_refreshAnimation();

		String	tmpAttackAnimName = m_owner->getAttackAnimName();

		if(tmpAttackAnimName.empty())
			return;

		if(NULL != m_animation )
		{
			if (m_owner->getAttackAnimDirty())
			{
				_disableAnimState();

				m_animationID = m_owner->getAnimationIdByName(tmpAttackAnimName);
				m_animation = m_owner->getAnimation(m_animationID);
			}
		}
		else
		{
			m_animationID = m_owner->getAnimationIdByName(tmpAttackAnimName);
			m_animation = m_owner->getAnimation(m_animationID);
		}
		
	}
}