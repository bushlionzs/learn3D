/********************************************************************
	created:	2008/04/07
	created:	7:4:2008   16:40
	file base:	OGAdvancedAnimationSystem
	file ext:	cpp
	author:		姜威
	email:		jiang628@hotmail.com
	purpose:	
*********************************************************************/
#include "OgreHeader.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASNode.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAdvancedAnimationSystemManager.h"
#include "OGAdvancedAnimationSystemSerializer.h"
#include "OGAASNodeFactory.h"
#include "OGSkeletonMeshComponent.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGAASAnimation.h"
#include "OGAASAnimTreeOutputNode.h"
#include "OGAASPort.h"

#include "OgreAnimationState.h"
#include "platform_log.h"
#include "OgreStringConverter.h"
#include "OgreRoot.h"



namespace Orphigine
{
	AdvancedAnimationSystem::AdvancedAnimationSystem(Ogre::ResourceManager* creator, const String& name, 
		Ogre::ResourceHandle handle,const String& group, bool isManual, Ogre::ManualResourceLoader* loader)
		: AdvancedAnimationSystemAbstract(creator,name,handle,group,isManual,loader),
		m_parent(NULL),
		m_animTreeOutputNode(NULL)
	{
		m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.clear();
		m_traverseBranchMaskCollection.m_traverseBranchMaskVec.clear();
		m_traverseBranchMaskCollection.m_traverseFeatherNodeCount = 0;
		m_directionalDegree = 0.0f;
		m_movingDegree = 0.0f;
		m_ridingDegree = 0.0f;
		m_attackDegree = 0.0f;
		m_livingDegree = 0.0f;
		m_weaponDegree = 0.0f;
		m_damageDegree = 0.0f;
		m_postureDegree = 0.0f;
		m_equitationDegree = 0.0f;
		m_guardDegree = 0.0f;
		m_moodDegree = 0.0f;
		m_danceDegree = 0.0f;
		m_walkDegree = 0.0f;

		m_moodAnimName = "";
		m_attackAnimName = "";
		m_weaponTypeName = "";
		m_attackAnimDirty = false;
		m_moodAnimDirty = false;

		m_globalAnimRateScale = 1.0f;
		m_systemTickTag = 0;

		m_animSynchGroups.clear();
		m_nodeNameHash.clear();
		m_tickVec.clear();

		if (createParamDictionary("AAS"))
		{
		}
	}

	AdvancedAnimationSystem::AdvancedAnimationSystem()
		: m_parent(NULL),
		m_animTreeOutputNode(NULL)
	{
		m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.clear();
		m_traverseBranchMaskCollection.m_traverseBranchMaskVec.clear();
		m_traverseBranchMaskCollection.m_traverseFeatherNodeCount = 0;
		m_directionalDegree = 0.0f;
		m_movingDegree = 0.0f;
		m_ridingDegree = 0.0f;
		m_attackDegree = 0.0f;
		m_livingDegree = 0.0f;
		m_weaponDegree = 0.0f;
		m_damageDegree = 0.0f;
		m_postureDegree = 0.0f;
		m_equitationDegree = 0.0f;
		m_guardDegree = 0.0f;
		m_moodDegree = 0.0f;
		m_danceDegree = 0.0f;
		m_walkDegree = 0.0f;

		m_attackAnimName = "";
		m_weaponTypeName = "";
		m_moodAnimName = "";
		m_attackAnimDirty = false;
		m_moodAnimDirty = false;

		m_globalAnimRateScale = 1.0f;
		m_systemTickTag = 0;

		m_animSynchGroups.clear();
		m_nodeNameHash.clear();
		m_tickVec.clear();

		if (createParamDictionary("AAS"))
		{
		}
	}
	AdvancedAnimationSystem::~AdvancedAnimationSystem()
	{
		
		unload();
	}

	void AdvancedAnimationSystem::update( float time )
	{
		tickAnimTree(time);

		tickSkelControl(time);
	}

	void AdvancedAnimationSystem::tickAnimTree( Real deltaSeconds )
	{
		
		{
			_disableNeedUpdateAnimations();
		}
		
		{
			_tickAllAnimNodes(deltaSeconds);

		}
	
	
		{
			_updateNeedUpdateAnimations(deltaSeconds);
		}

	

		
		{
			_accumulateReachedAnimationNodes(deltaSeconds);
		}
		
		
		{
			updateAnimSequenceNodeGroups(deltaSeconds);
		}
		
	}

	void AdvancedAnimationSystem::_tickAllAnimNodes( Real deltaSeconds )
	{
		m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.clear();
		m_systemTickTag ++;

		m_animTreeOutputNode->resetBlendWeightAccumulater();
		m_animTreeOutputNode->increaseBlendWeightAccumulater(1.0f);

		int tickVecSize = (int)m_tickVec.size();
		for (int i = 0;i < tickVecSize;i ++)
		{
			AASNode* node = m_tickVec[i];

			bool isChildNodeWeightValid = (node->getNodeTotalWeight() > 0.00001f);

			node->setBlendWeight(node->getBlendWeightAccumulater());
			node->setNonmaskedBonesWeight(node->getNonmaskedBonesWeightAccumulater());
			node->setMaskedBonesWeight(node->getMaskedBonesWeightAccumulater());

			node->resetBlendWeightAccumulater();
			node->resetMaskedBonesWeightAccumulater();
			node->resetNonmaskedBonesWeightAccumulater();

			node->setJustCeaseActive(false);
			node->setJustBecomeActive(false);

			if (!node->getActive())
			{
				if (isChildNodeWeightValid)
				{
					node->_onBecomeActive();
					node->setJustBecomeActive(true);
					node->setActive(true);
				}
			} 
			else
			{
				if (!isChildNodeWeightValid)
				{
					node->_onCeaseActive();
					node->setJustCeaseActive(true);
					node->setActive(false);
				}
			}

			if(!node->getActive() && !node->getJustCeaseActive())
				continue;															

			node->setTickTag(m_systemTickTag);

			node->tickAnimation(deltaSeconds,m_reachedAnimSequenceNodeCollection);
		}
	}

	void AdvancedAnimationSystem::tickSkelControl( Real deltaSeconds )
	{

	}

	void AdvancedAnimationSystem::_accumulateReachedAnimationNodes( Real elapsedTime )
	{
		AASAnimSequNodeVector::iterator iter;
		AASAnimSequNodeVector::iterator iterEnd = 
			m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.end();

		for (iter = m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.begin();
			iter != iterEnd;iter ++)
		{
			AASAnimSequenceNode* tmpAnimSequenceNode = (*iter);

			int	tmpAnimationID = tmpAnimSequenceNode->getAnimationID();

			if(INVAILD_ANIMATION_ID == tmpAnimationID)
				continue;
			
			AASAnimation* tmpAnimation = getAnimation(tmpAnimationID);

			tmpAnimation->increaseActiveReferencingNodesCount();

			Real	unifyWeight = tmpAnimSequenceNode->getBlendWeight();
			Real	tmpMaskedBoneWeight = tmpAnimSequenceNode->getMaskedBonesWeight();
			Real	tmpNonMaskedBoneWeight = tmpAnimSequenceNode->getNonmaskedBonesWeight();

			bool    isAccumulatedBonesWeightVaild = false;
			isAccumulatedBonesWeightVaild = (0.0001f < tmpAnimation->increaseAccumulatedUnifyWeight(unifyWeight));

			TraverseBranchMaskCollection* tmpTraverseBranchMaskCollection = 
				tmpAnimSequenceNode->getBranchBonesWeightCollectionCache();

			if (tmpTraverseBranchMaskCollection)
			{
				tmpAnimation->increaseTraverseFeatherNodeCount(tmpTraverseBranchMaskCollection->m_traverseFeatherNodeCount);

				if (tmpAnimation->getTraverseFeatherNodeCount() > 0)
				{
					tmpAnimation->setWeight(1.0f);

					tmpAnimation->createOrSetBonesMask(tmpAnimation->getAccumulatedUnifyWeight());

					isAccumulatedBonesWeightVaild = false;

					for (unsigned short i = 0;i < tmpAnimation->getNumBones();i ++)
					{
						bool	isMaskedBone = tmpTraverseBranchMaskCollection->m_traverseBranchMaskVec[i];

						Real accumulatedBoneWeight = 0.0f;
						if(isMaskedBone)
							accumulatedBoneWeight = tmpAnimation->increaseAccumulatedBonesWeight(i,tmpMaskedBoneWeight);
						else
							accumulatedBoneWeight = tmpAnimation->increaseAccumulatedBonesWeight(i,tmpNonMaskedBoneWeight);

						isAccumulatedBonesWeightVaild |= (0.0001f < accumulatedBoneWeight);
					}
				}
				else
				{
					if(tmpAnimation->getCreatedBonesMask())
						tmpAnimation->destroyBonesMask();
				}
			}
			
			tmpAnimation->setEnabled(isAccumulatedBonesWeightVaild);

			if(1 == tmpAnimation->getActiveReferencingNodesCount())
				m_needUpdateAnimationsVec.push_back(tmpAnimation);
		}
	}

	void AdvancedAnimationSystem::_updateNeedUpdateAnimations( Real elapsedTime )
	{
		AASAnimationVector::iterator iter;
		AASAnimationVector::iterator iterEnd = m_needUpdateAnimationsVec.end();

		for (iter = m_needUpdateAnimationsVec.begin();
			iter != iterEnd;iter ++)
		{
			AASAnimation* tmpAnimation  = (*iter);
			
			tmpAnimation->resetAccumulatedUnifyWeight();
			tmpAnimation->resetAccumulatedBonesWeight();
			tmpAnimation->resetActiveReferencingNodesCount();
			tmpAnimation->resetTraverseFeatherNodeCount();
		}

		m_needUpdateAnimationsVec.clear();
	}

	void AdvancedAnimationSystem::_disableNeedUpdateAnimations()
	{
		AASAnimationVector::iterator iter;
		AASAnimationVector::iterator iterEnd = m_needUpdateAnimationsVec.end();

		for (iter = m_needUpdateAnimationsVec.begin();
			iter != iterEnd;iter ++)
		{
			AASAnimation* tmpAnimation  = (*iter);

			assert(NULL != tmpAnimation && "AASAnimation指针为空 AdvancedAnimationSystem::_updateNeedUpdateAnimations");

			tmpAnimation->setEnabled(false);
		}
	}

	void AdvancedAnimationSystem::_updateGroupMasterNode( AnimSeqSynchGroup& group )
	{
		if(group.m_synchMasterNode)
		{
			if(!group.m_synchMasterNode->getActive())
				group.m_synchMasterNode = NULL;
		}

		if (!group.m_synchMasterNode || (group.m_synchMasterNode && group.m_synchMasterNode->getNodeTotalWeight() < 1.0f))
		{
			Real	 synchMasterNodeWeight = group.m_synchMasterNode ? group.m_synchMasterNode->getNodeTotalWeight() : 0.0f;

			int numNodes = (int)group.m_animSeqNodes.size();
			for (int i = 0;i < numNodes;i ++)
			{
				AASAnimSequenceNode* animSeqNode = group.m_animSeqNodes[i];
				
				if (animSeqNode->getActive() && animSeqNode->getNodeTotalWeight() > synchMasterNodeWeight)
				{
					group.m_synchMasterNode = animSeqNode;
					synchMasterNodeWeight = animSeqNode->getNodeTotalWeight();
				}
			}
		}
	}

	void AdvancedAnimationSystem::updateAnimSequenceNodeGroups(Real deltaSeconds )
	{
		AnimSynchGropVector::iterator iter;
		AnimSynchGropVector::iterator iterEnd = m_animSynchGroups.end();

		for (iter = m_animSynchGroups.begin();iter != iterEnd;iter ++)
		{
			AnimSeqSynchGroup& animSeqSynchGroup = (*iter);

			_updateGroupMasterNode(animSeqSynchGroup);

			const Real	groupDelta = m_globalAnimRateScale * deltaSeconds;

			if (!animSeqSynchGroup.m_synchMasterNode || (animSeqSynchGroup.m_synchMasterNode && !animSeqSynchGroup.m_synchMasterNode->getActive()))
			{
				int numNodes = (int)animSeqSynchGroup.m_animSeqNodes.size();
				for (int i = 0;i < numNodes;i ++)
				{
					AASAnimSequenceNode* animSeqNode = animSeqSynchGroup.m_animSeqNodes[i];

					Real nodeDeltaSeconds = animSeqNode->getRate() * groupDelta;

					if(animSeqNode && animSeqNode->getPlaying())
						animSeqNode->advanceAnimation(nodeDeltaSeconds);
				}
			} 
			else
			{
				AASAnimSequenceNode* synchMasterNode = animSeqSynchGroup.m_synchMasterNode;

				Real masterDeltaSeconds = synchMasterNode->getRate() * groupDelta;
				//if(synchMasterNode->getPlaying())
				//	synchMasterNode->advanceAnimation(masterDeltaSeconds);

				int numNodes = (int)animSeqSynchGroup.m_animSeqNodes.size();
				for (int i = 0;i < numNodes;i ++)
				{
					AASAnimSequenceNode* animSeqNode = animSeqSynchGroup.m_animSeqNodes[i];

					if(animSeqNode && animSeqNode->getPlaying())
						animSeqNode->advanceAnimation(masterDeltaSeconds);

					if(animSeqNode/* && animSeqNode->getActive()*/)
					{
						//animSeqNode->setPlaying(true);

						if (animSeqNode->getAnimationID() == synchMasterNode->getAnimationID())
							animSeqNode->setCurrentTime(synchMasterNode->getCurrentTime());
					}
				}
			}
		}

		AASAnimSequNodeVector::iterator animSeqNodeiter;
		AASAnimSequNodeVector::iterator animSeqNodeiterEnd = 
			m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.end();

		for (animSeqNodeiter = m_reachedAnimSequenceNodeCollection.m_reachedAnimSequenceNodeVec.begin();
			animSeqNodeiter != animSeqNodeiterEnd;animSeqNodeiter ++)
		{
			AASAnimSequenceNode* tmpAnimSequenceNode = (*animSeqNodeiter);

			int	tmpAnimationID = tmpAnimSequenceNode->getAnimationID();

			if(INVAILD_ANIMATION_ID == tmpAnimationID)
				continue;

			AASAnimation* tmpAnimation = getAnimation(tmpAnimationID);
			if(tmpAnimation) {

				tmpAnimation->setTimePosition(tmpAnimSequenceNode->getCurrentTime());
			}
		}
	}

	AASNode* AdvancedAnimationSystem::getAnimTreeOutputNode() const
	{
		return m_animTreeOutputNode;
	}

	void AdvancedAnimationSystem::setAnimTreeOutputNode( AASNode* val )
	{
		m_animTreeOutputNode = val;
	}
	AASNode* AdvancedAnimationSystem::addNode( const String& name ,unsigned short handle)
	{
		if (MAX_NUM_AAS_NODE < handle)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "Exceeded the maximum number of nodes per system. name:"+name+"handle="+Ogre::StringConverter::toString(handle),
				"AdvancedAnimationSystem::addNode");
		}
		if (m_nodeList.size() > handle && NULL != m_nodeList[handle])
		{
			OGRE_EXCEPT(
				Ogre::Exception::ERR_DUPLICATE_ITEM,
				"A node with the handle " + Ogre::StringConverter::toString(handle) + " already exists,name:"+name,
				"AdvancedAnimationSystem::addNode" );
		}

		AASNode* tmpNode = AdvancedAnimationSystemManager::getSingleton().createNode(name,handle,this);
		
		size_t oldSize = m_nodeList.size();
		if (m_nodeList.size() <= handle)
		{
			m_nodeList.resize(handle + 1);
			for (unsigned short i=oldSize; i<handle + 1; i++)
			{
				m_nodeList[i] = 0;
			}
		}
		//end

		m_nodeList[handle] = tmpNode;

		return tmpNode;
	}

	AdvancedAnimationSystem::NodeIterator AdvancedAnimationSystem::getNodeIterator()
	{
		return AdvancedAnimationSystem::NodeIterator(m_nodeList.begin(),m_nodeList.end());
	}

	AASNode* AdvancedAnimationSystem::getNode( unsigned short handle )  const
	{
		assert((unsigned short)m_nodeList.size() > handle && "越界AdvancedAnimationSystem::getNode");

		return m_nodeList[handle];
	}

	void AdvancedAnimationSystem::removeNode( unsigned short handle )
	{
		assert(handle < (unsigned short)m_nodeList.size() && "Node索引越界 AdvancedAnimationSystem::removeNode");
		AASNodeVector::iterator iter = m_nodeList.begin() + handle;

		AdvancedAnimationSystemManager::getSingleton().destroyNode((*iter));

		(*iter) = NULL;
		m_nodeList.erase(iter);
	}

	Real AdvancedAnimationSystem::getDirectionalDegree() const
	{
		return m_directionalDegree;
	}

	void AdvancedAnimationSystem::setDirectionalDegree( const Real val )
	{
		m_directionalDegree = val;
	}

	Real AdvancedAnimationSystem::getMovingDegree() const
	{
		return m_movingDegree;
	}

	void AdvancedAnimationSystem::setMovingDegree( const Real val )
	{
		m_movingDegree = val;
	}

	Real AdvancedAnimationSystem::getRidingDegree() const
	{
		return m_ridingDegree;
	}

	void AdvancedAnimationSystem::setRidingDegree( const Real val )
	{
		m_ridingDegree = val;
	}

	Real AdvancedAnimationSystem::getAttackDegree() const
	{
		return m_attackDegree;
	}

	void AdvancedAnimationSystem::setAttackDegree( const Real val )
	{
		m_attackDegree = val;
		makeAttackAnimDirty();

	}

	Real AdvancedAnimationSystem::getLivingDegree() const
	{
		return m_livingDegree;
	}

	void AdvancedAnimationSystem::setLivingDegree( const Real val )
	{
		m_livingDegree = val;
	}

	Real AdvancedAnimationSystem::getWeaponDegree() const
	{
		return m_weaponDegree;
	}

	void AdvancedAnimationSystem::setWeaponDegree( const Real val )
	{
		m_weaponDegree = val;
	}

	void AdvancedAnimationSystem::loadImpl( void )
	{
		AdvancedAnimationSystemSerializer tmpSerializer;

		Ogre::StringStream msg;
		msg<<"AdvancedAnimationSystem loading :"<<mName;

		DataStreamPtr tmpStream = Ogre::ResourceManager::getSingleton().openResource(mName, mGroup);
		//所有前台加载的资源写log			

		NOTICE_LOG("Main Thread Load Resource from hardware.ResName=%s", mName.c_str());
		
		//dscky edit 添加后台加载的兼容代码/////////////////////////////////////////////////////////////////

		tmpSerializer.importAdvancedAnimationSystem(tmpStream,this);

		msg.flush();
		msg<<mName<<"AdvancedAnimationSystem loaded !";

	}

	void AdvancedAnimationSystem::unloadImpl( void )
	{
		removeAllNodes();

		m_animTreeOutputNode = NULL;

		_removeAllAnimations();
	}

	size_t AdvancedAnimationSystem::calculateSize( void ) const
	{
		return 0;
	}

	unsigned short AdvancedAnimationSystem::getNumNodes() const
	{
		return (unsigned short)m_nodeList.size();
	}

	SkeletonMeshComponent* AdvancedAnimationSystem::getParent() const
	{
		return m_parent;
	}

	void AdvancedAnimationSystem::setParent( SkeletonMeshComponent* val )
	{
		m_parent = val;
	}

	Real AdvancedAnimationSystem::getDamageDegree() const
	{
		return m_damageDegree;
	}

	void AdvancedAnimationSystem::setDamageDegree( Real val )
	{
		m_damageDegree = val;
		makeDamageAnimDirty();
	}

	String AdvancedAnimationSystem::getAttackAnimName() const
	{
		return m_attackAnimName;
	}

	void AdvancedAnimationSystem::setAttackAnimName( const String& val )
	{
		m_attackAnimName = val;

		makeAttackAnimDirty();
	}

	Real AdvancedAnimationSystem::getPostureDegree() const
	{
		return m_postureDegree;
	}

	void AdvancedAnimationSystem::setPostureDegree( Real val )
	{
		m_postureDegree = val;
	}

	Real AdvancedAnimationSystem::getEquitationDegree() const
	{
		return m_equitationDegree;
	}

	void AdvancedAnimationSystem::setEquitationDegree( Real val )
	{
		m_equitationDegree = val;
	}

	Real AdvancedAnimationSystem::getGuardDegree() const
	{
		return m_guardDegree;
	}

	void AdvancedAnimationSystem::setGuardDegree( Real val )
	{
		m_guardDegree = val;
	}

	const String& AdvancedAnimationSystem::getWeaponTypeName() const
	{
		return m_weaponTypeName;
	}

	void AdvancedAnimationSystem::setWeaponTypeName( const String& val )
	{
		m_weaponTypeName = val;
	}

	void AdvancedAnimationSystem::onAnimationEnd( AASAnimSequenceNode* animSequenceNode )
	{
		assert(animSequenceNode && "AdvancedAnimationSystem::onAnimationEnd");

		AASNode* tmpInputNode = animSequenceNode->getInputNode();

		int tmpAnimationID = animSequenceNode->getAnimationID();
		AASAnimation* tmpAnimation = getAnimation(tmpAnimationID);

		if(tmpInputNode && tmpAnimation)
			m_parent->handleAASAnimEndEvent(tmpAnimation->getAnimationName().c_str(),tmpInputNode->getType().c_str(),tmpInputNode->getName().c_str());
		
	}

	void AdvancedAnimationSystem::onAnimationPlay( AASAnimSequenceNode* animSequenceNode )
	{
		assert(animSequenceNode && "AdvancedAnimationSystem::onAnimationPlay");

		AASNode* tmpInputNode = animSequenceNode->getInputNode();

		animSequenceNode->_refreshAnimation();
		int tmpAnimationID = animSequenceNode->getAnimationID();
		AASAnimation* tmpAnimation = getAnimation(tmpAnimationID);

		if(tmpInputNode && tmpAnimation)
			m_parent->handleAASAnimPlayEvent(tmpAnimation->getAnimationName().c_str(),tmpInputNode->getType().c_str(),animSequenceNode->getHandle());
	}

	Ogre::AnimationState* AdvancedAnimationSystem::getAnimationState( const String& name )
	{

		SkeletonMeshComponent* tmpLogicModel = m_parent;

		assert(NULL != tmpLogicModel && "LogicModel对象为空 AdvancedAnimationSystem::getAnimationState");

		assert(!name.empty() && "AnimationState名称不能为空 AdvancedAnimationSystem::getAnimationState");

		Ogre::AnimationState* tmpAnimState = NULL;
		try
		{
			tmpAnimState = tmpLogicModel->_getAnimationState(name);
		}
		
		catch (...)
		{
			
		}
		return tmpAnimState;
	}

	void AdvancedAnimationSystem::_initAnimations()
	{
		unsigned int numAnimationState = m_parent->getSkeletonAnimationCount();

		for (unsigned int i = 0;i < numAnimationState;i ++)
		{
			Ogre::Animation* animation = m_parent->getSkeletonAnimation(i);
			_addAnimation(animation->getName());
		}
	}

	void AdvancedAnimationSystem::_addAnimation( const String& animName )
	{
		if (NULL == m_parent)
			return;

		Ogre::AnimationState* tmpAnimState = NULL;

		tmpAnimState = getAnimationState(animName);


		assert(NULL != tmpAnimState && "动画状态不能为NULL AdvancedAnimationSystem::_addAnimation");

		AASAnimation* tmpAnimation = OGRE_NEW AASAnimation(this,tmpAnimState);

		int tmpIndex = (int)m_animations.size();
		m_animations.push_back(tmpAnimation);

		m_animationIndexMap.insert(AnimationIndexMap::value_type(animName,tmpIndex));
	}

	int AdvancedAnimationSystem::getAnimationIdByName( const String& name )
	{
		AnimationIndexMap::iterator iter = m_animationIndexMap.find(name);

		if (m_animationIndexMap.end() != iter)
			return iter->second;
		else
		{
			_addAnimation( name );

			AnimationIndexMap::iterator iter = m_animationIndexMap.find(name);

			if (m_animationIndexMap.end() != iter)
				return iter->second;
		}
		return -1;
	}

	AASAnimation* AdvancedAnimationSystem::getAnimation( int animationID )
	{
		if(0 <= animationID && (int)m_animations.size() > animationID)
			return m_animations[animationID];
		else
			return NULL;
	}

	unsigned short AdvancedAnimationSystem::getNumBones() const
	{
		assert(NULL != m_parent && "LogicModel指针为空 AdvancedAnimationSystem::getNumBones()");
		return m_parent->getNumBones();
	}

	void AdvancedAnimationSystem::removeAllNodes()
	{
		AASNodeVector::iterator iter;
		for (iter = m_nodeList.begin();iter != m_nodeList.end();iter ++)
		{			
			AASNode * node = *iter;
			if (node != NULL)
			{
				AdvancedAnimationSystemManager::getSingleton().destroyNode(node);
				//OGRE_DELETE (*iter);
				(*iter) = NULL;
			}
		}
		m_nodeList.clear();
	}

	void AdvancedAnimationSystem::_removeAllAnimations()
	{
		AASAnimationVector::iterator iter;
		for (iter = m_animations.begin();iter != m_animations.end();iter ++)
		{
			OGRE_DELETE (*iter);
			(*iter) = NULL;
		}

		m_animations.clear();
	}

	Real AdvancedAnimationSystem::getMoodDegree() const
	{
		return m_moodDegree;
	}

	void AdvancedAnimationSystem::setMoodDegree( Real val )
	{
		m_moodDegree = val;
		makeMoodAnimDirty();

	}

	Real AdvancedAnimationSystem::getDanceDegree() const
	{
		return m_danceDegree;
	}

	void AdvancedAnimationSystem::setDanceDegree( Real val )
	{
		m_danceDegree = val;
	}

	Real AdvancedAnimationSystem::getWalkDegree() const
	{
		return m_walkDegree;
	}

	void AdvancedAnimationSystem::setWalkDegree( Real val )
	{
		m_walkDegree = val;
	}

	const String& AdvancedAnimationSystem::getMoodAnimName() const
	{
		return m_moodAnimName;
	}

	void AdvancedAnimationSystem::setMoodAnimName( const String& val )
	{
		m_moodAnimName = val;

		makeMoodAnimDirty();
	}

	bool AdvancedAnimationSystem::getAttackAnimDirty() const
	{
		return m_attackAnimDirty;
	}

	void AdvancedAnimationSystem::makeAttackAnimDirty()
	{
		m_attackAnimDirty = true;
	}

	void AdvancedAnimationSystem::resetAttackAnimDirty()
	{
		m_attackAnimDirty = false;
	}

	bool AdvancedAnimationSystem::getMoodAnimDirty() const
	{
		return m_moodAnimDirty;
	}

	void AdvancedAnimationSystem::makeMoodAnimDirty()
	{
		m_moodAnimDirty = true;
	}

	void AdvancedAnimationSystem::resetMoodAnimDirty()
	{
		m_moodAnimDirty = false;
	}

	bool AdvancedAnimationSystem::getDamageAnimDirty() const
	{
		return m_damageAnimDirty;
	}

	void AdvancedAnimationSystem::makeDamageAnimDirty()
	{
		m_damageAnimDirty = true;
	}

	void AdvancedAnimationSystem::resetDamageAnimDirty()
	{
		m_damageAnimDirty = false;
	}

	AASNode* AdvancedAnimationSystem::findAASNode( const String& nodeName )
	{
		if (m_animTreeOutputNode)
			return m_animTreeOutputNode->findAASNode(nodeName);
		
		return NULL;
	}

	AnimSynchGropVector& AdvancedAnimationSystem::getAnimSynchGroups()
	{
		return m_animSynchGroups;
	}

	Real AdvancedAnimationSystem::getGlobalAnimRateScale() const
	{
		return m_globalAnimRateScale;
	}

	void AdvancedAnimationSystem::setGlobalAnimRateScale( Real val )
	{
		m_globalAnimRateScale = val;
	}

	int AdvancedAnimationSystem::getSystemTickTag() const
	{
		return m_systemTickTag;
	}

	void AdvancedAnimationSystem::setSystemTickTag( int val )
	{
		m_systemTickTag = val;
	}
	
	void	AASNodeFactory::destroyNode(AASNode* node)
	{
		AASNodeVector::iterator iter;
		for (iter = m_nodes.begin();iter != m_nodes.end();iter ++)
		{
			if ((*iter) == node)
			{
				m_nodes.erase(iter);
				OGRE_DELETE node;
				break;
			}
		}
	}
}