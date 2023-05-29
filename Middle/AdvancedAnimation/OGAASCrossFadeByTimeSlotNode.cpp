#include "OgreHeader.h"
#include "OGAASCrossFadeByTimeSlotNode.h"
#include "OGAASPort.h"
#include "OGAASAnimSequenceNode.h"

#include "OgreMath.h"

namespace Orphigine
{
	AASCrossFadeByTimeSlotNode::AASCrossFadeByTimeSlotNode( const String& typeName,AdvancedAnimationSystem* system,unsigned short handle )
	: AASCrossFadeNode(typeName,system,handle)
	, m_userDefineChildIndex(0)
	, m_timeLeft(0.0f)
	, m_isPlayingUserDefineAnim(false)
	, m_pendingBlendOutTime(0.0f)
	{
		initParameter("CrossFadeByTimeSlot");
	}

	AASCrossFadeByTimeSlotNode::~AASCrossFadeByTimeSlotNode()
	{

	}

	void AASCrossFadeByTimeSlotNode::initAnim( AASNode* parentNode )
	{
		AASCrossFadeNode::initAnim(parentNode);

		AASPort* port = getPort(0);

		if (0.0001f > getTotalChildrenWeight())
		{
			setActiveChild(port,0.0f);
		}
	}

	void AASCrossFadeByTimeSlotNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		if (m_isPlayingUserDefineAnim)
		{
			AASAnimSequenceNode* customAnimSeqNode = getUserDefineAnimSeqNode();

			if (m_pendingBlendOutTime > 0.0f)
			{
				if (customAnimSeqNode)
				{
					if (customAnimSeqNode->getTimeLeft() <= m_pendingBlendOutTime)
					{
						stopUserDefineAnimation(customAnimSeqNode->getTimeLeft());
					}
				}
			}
		}

		if (m_timeLeft > 0.0f)
		{
			if (m_timeLeft < elapsedTime)
			{
				m_timeLeft = 0.0f;
				for (unsigned int i = 0;i < getNumPorts();i ++)
				{
					AASPort* port = getPort(i);
					port->setBlendWeight(port->getTargetWeight());
				}
			} 
			else
			{
				for (unsigned int i = 0;i < getNumPorts();i ++)
				{	
					AASPort* port = getPort(i);
					
					Real deltaWeight = (elapsedTime / m_timeLeft) * (port->getTargetWeight() - port->getBlendWeight());

					port->setBlendWeight(port->getBlendWeight() + deltaWeight);
				}

				m_timeLeft -= elapsedTime;
			}
		} 	


		AASCrossFadeNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}

	void AASCrossFadeByTimeSlotNode::setActiveChild( AASPort* activePort,Real blendTime )
	{
		AASPort* activeChildPort = activePort;

		if(!activeChildPort)
			activeChildPort = getPort(0);

		if(!activeChildPort)
		{
			assert("Port数目不能为空 AASCrossFadeByTimeListNode::setActiveChild ");
			return;
		}

		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);
			if (port == activeChildPort)
			{
				port->setTargetWeight(1.0f);

				if(Ogre::Math::RealEqual(blendTime,0.0f))
					port->setBlendWeight(1.0f);
			} 
			else
			{
				port->setTargetWeight(0.0f);

				if(Ogre::Math::RealEqual(blendTime,0.0f))
					port->setBlendWeight(0.0f);
			}
		}

		m_timeLeft = blendTime;
	}

	void AASCrossFadeByTimeSlotNode::playUserDefineAnimation( const String& animName,Real blendInTime,
		Real blendOutTime,bool isLooping,Real rate,bool isRestart )
	{
		if(animName.empty())
			return;

		m_userDefineChildIndex = 0xffff;
		//----------------------
		//解决卡的问题
		/*
		int animID = m_owner->getAnimationIdByName(animName.c_str());

		for (unsigned short i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);
			AASAnimSequenceNode* node = (AASAnimSequenceNode*) port->getConnectedNode();
			if (node && node->getAnimationID() == animID)
			{
				
				if (node->getPlaying() && node->getBlendWeight() > 0.00001)
				{		
					return;
				}
				else
					m_userDefineChildIndex = i;
				node->setPlaying(true);

			}
		}*/
		//----------------------
		if (m_userDefineChildIndex == 0xffff)
			m_userDefineChildIndex = findBestUserDefineAnimSeqIndex();

		AASAnimSequenceNode* animSeqNode = getUserDefineAnimSeqNode();
		if (animSeqNode)
		{

			animSeqNode->_disableAnimState();
			animSeqNode->setAnimationName(animName.c_str());

			int animationID = animSeqNode->getAnimationID();
			if(-1 == animationID)
				animSeqNode->_refreshAnimation();

			animSeqNode->playAnim(isLooping,rate,0.0f);
		}
		
		AASPort* port = getPort(m_userDefineChildIndex);

		setActiveChild(port,blendInTime);

		m_isPlayingUserDefineAnim = true;

		m_pendingBlendOutTime = isLooping ? -1.0f : blendOutTime;
	}

	void AASCrossFadeByTimeSlotNode::stopUserDefineAnimation( Real blendOutTime )
	{
		m_isPlayingUserDefineAnim = false;

		AASPort* port = getPort(0);
		assert(port && "AASCrossFadeByTimeSlotNode::stopUserDefineAnimation");

		setActiveChild(port,blendOutTime);
	}

	AASAnimSequenceNode* AASCrossFadeByTimeSlotNode::getUserDefineAnimSeqNode()
	{
		assert(0 < m_userDefineChildIndex  && m_userDefineChildIndex < (int)m_portVec.size() &&
			"AASCrossFadeByTimeSlotNode::getCustomAnimSeqNode");

		if (0 < m_userDefineChildIndex  && m_userDefineChildIndex < (int)m_portVec.size())
		{
			return (AASAnimSequenceNode*)getPort(m_userDefineChildIndex)->getConnectedNode();
		}
		return NULL;
	}

	int AASCrossFadeByTimeSlotNode::findBestUserDefineAnimSeqIndex()
	{
		Real bestWeight = 1.0f;
		int bestIndex = -1;
		//解决卡的问题
		//-------------------------
		//for (unsigned short i = 0;i < getNumPorts();i ++)
		for (unsigned short i = 1;i < getNumPorts();i ++)
		//-------------------------
		{
			AASPort* port = getPort(i);
			AASNode* node = port->getConnectedNode();
			if(!node)
				continue;

			if(-1 == bestIndex  || (node && node->getNodeTotalWeight() < bestWeight))
			{
				bestWeight = node->getNodeTotalWeight();
				bestIndex = i;
			}
		}

		return bestIndex;
	}
}
