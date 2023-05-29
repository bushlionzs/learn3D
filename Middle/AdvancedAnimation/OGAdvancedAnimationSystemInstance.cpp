#include "OgreHeader.h"
#include "OGAdvancedAnimationSystemInstance.h"
#include "OGAASNode.h"
#include "OGAASPort.h"
#include "OgreRoot.h"
#include "OgreTimer.h"

namespace Orphigine
{


	AdvancedAnimationSystemInstance::AdvancedAnimationSystemInstance(const AdvancedAnimationSystemPtr& masterCopy)
		: AdvancedAnimationSystem(),
		m_advancedAnimationSystem(masterCopy)
	{

	}

	AdvancedAnimationSystemInstance::~AdvancedAnimationSystemInstance()
	{
		unload();
	}

	void AdvancedAnimationSystemInstance::loadImpl()
	{
#ifdef _ENABLE_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();	
#endif
		NodeIterator tmpNodeIter = m_advancedAnimationSystem->getNodeIterator();

#ifdef _ENABLE_TIME_LOG_
		unsigned long time1 = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
#endif

		int i=0;
		while(tmpNodeIter.hasMoreElements())
		{
			AASNode* tmpNode = tmpNodeIter.getNext();
			if(tmpNode)
			{
				cloneNode(tmpNode);
				++i;
			}
		}

#ifdef _ENABLE_TIME_LOG_
		unsigned long time2 = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
#endif

		

		tmpNodeIter = m_advancedAnimationSystem->getNodeIterator();

#ifdef _ENABLE_TIME_LOG_
		unsigned long time3 = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
#endif

		while(tmpNodeIter.hasMoreElements())
		{
			AASNode* tmpNode = tmpNodeIter.getNext();
			if(tmpNode)
				cloneConnection(tmpNode);
		}
#ifdef _ENABLE_TIME_LOG_
		unsigned long endTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
		if( endTime > 3 )
		{
			static char buf[512];
			sprintf(buf, "AdvancedAnimationSystemInstance::loadImpl ºÄÊ± [%d:%d:%d:%d] ºÁÃë Elements=%d\n", time1, time2, time3, endTime, i);
			::OutputDebugString(buf);

		}
#endif
	}

	void AdvancedAnimationSystemInstance::unloadImpl( void )
	{
		AdvancedAnimationSystem::unloadImpl();

	}


	void AdvancedAnimationSystemInstance::cloneNode( AASNode* source )
	{
#ifdef _ENABLE_TIME_LOG_
		unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();	
#endif
		AASNode* tmpCurrentNode = addNode(source->getType().c_str(),source->getHandle());

#ifdef _ENABLE_TIME_LOG_
		unsigned long time1 = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
#endif

		source->copyParameters(tmpCurrentNode);

#ifdef _ENABLE_TIME_LOG_
		unsigned long time2 = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
#endif

		if("AnimTree" == tmpCurrentNode->getType())
			setAnimTreeOutputNode(tmpCurrentNode);

#ifdef _ENABLE_TIME_LOG_
		unsigned long endTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()-startTime;
		if( endTime > 3 )
		{
			static char buf[512];
			sprintf(buf, "AdvancedAnimationSystemInstance::cloneNode ºÄÊ± [%d:%d:%d] ºÁÃë Elements=%d\n", time1, time2, endTime);
			::OutputDebugString(buf);

		}
#endif
	}

	void AdvancedAnimationSystemInstance::cloneConnection( AASNode* source )
	{
		AASNode*	tmpCurrentNode = getNode(source->getHandle());
		if(!tmpCurrentNode)
			return;

		AASNode::PortsIterator tmpPortIter = source->getPortsIterator();

		while (tmpPortIter.hasMoreElements())
		{
			AASPort* tmpPortOfSource = tmpPortIter.getNext();
			if(!tmpPortOfSource)
				continue;

			AASNode* tmpPortOfSourceConnectedNode = tmpPortOfSource->getConnectedNode();
			if(!tmpPortOfSourceConnectedNode)
				continue;
			

			AASPort* tmpPortOfCurrent = tmpCurrentNode->getPort(tmpPortOfSource->getName());
			if(!tmpPortOfCurrent)
				continue;

			
			AASNode* tmpPortOfCurrentConnectedNode = getNode(tmpPortOfSourceConnectedNode->getHandle());
			if(!tmpPortOfCurrentConnectedNode)
				continue;

			tmpPortOfCurrent->setConnectedNode(tmpPortOfCurrentConnectedNode);

		}
	}

	void AdvancedAnimationSystemInstance::cloneAnimation()
	{
		AdvancedAnimationSystem::AnimationIndexMapIterator tmpIter = m_advancedAnimationSystem->getAnimationsIndexMapIterator();

		while(tmpIter.hasMoreElements())
		{
			String	tmpAnimationName = tmpIter.peekNextKey();
			int		tmpAnimationIndex = tmpIter.peekNextValue();

			AASAnimation* tmpAnimation = m_advancedAnimationSystem->getAnimation(tmpAnimationIndex);

			m_animations.push_back(tmpAnimation);
			m_animationIndexMap.insert(AnimationIndexMap::value_type(tmpAnimationName,tmpAnimationIndex));

			tmpIter.moveNext();
		}
	}

	void AdvancedAnimationSystemInstance::init()
	{
		_initAnimations();

		m_animTreeOutputNode->initAnim(NULL);

		m_systemTickTag ++;
		m_tickVec.clear();
		m_animTreeOutputNode->setTickTag(m_systemTickTag);
		m_tickVec.push_back(m_animTreeOutputNode);
		m_animTreeOutputNode->buildTickVec(m_tickVec);
	}

	void AdvancedAnimationSystemInstance::initAnimTree()
	{
		m_animTreeOutputNode->initAnim(NULL);
	}
}