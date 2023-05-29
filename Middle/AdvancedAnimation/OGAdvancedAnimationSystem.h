#ifndef OGAdvancedAnimationSystem_h__
#define OGAdvancedAnimationSystem_h__

#include "OGAdvancedAnimationSystemAbstract.h"

#include "OgreResource.h"
#include "OgreResourceManager.h"
#include "OgreIteratorWrapper.h"

#include <vector>

namespace Orphigine
{
	class AASAnimSequenceNode;
	class AASNode;
	class SkeletonMeshComponent;
	class AASAnimation;

	struct	ReachedAnimSequenceNodeCollection
	{
		ReachedAnimSequenceNodeCollection()
		{
			m_reachedAnimSequenceNodeVec.clear();
		}
		AASAnimSequNodeVector m_reachedAnimSequenceNodeVec;		
	};

	struct  TraverseBranchMaskCollection
	{
		TraverseBranchMaskCollection()
		{
			m_traverseBranchMaskVec.clear();
			m_traverseFeatherNodeCount = 0;
		}

		TraverseBranchMaskCollection&	operator = (const TraverseBranchMaskCollection& rhs)
		{
			m_traverseBranchMaskVec = rhs.m_traverseBranchMaskVec;
			m_traverseFeatherNodeCount = rhs.m_traverseFeatherNodeCount;

			return *this;
		}
		
		std::vector<bool>			m_traverseBranchMaskVec;
		
		unsigned int				m_traverseFeatherNodeCount;
	};

	struct AnimSeqSynchGroup 
	{
		AnimSeqSynchGroup()
		{
			m_synchGroupName = "";
			m_synchMasterNode = NULL;
			m_animSeqNodes.clear();
		}
		String								m_synchGroupName;
		AASAnimSequenceNode*				m_synchMasterNode;
		AASAnimSequNodeVector				m_animSeqNodes;
	};
#define  MAX_NUM_AAS_NODE 300

	class _OrphigineExport AdvancedAnimationSystem : public AdvancedAnimationSystemAbstract
	{
	public:
		AdvancedAnimationSystem(Ogre::ResourceManager* creator, const String& name, Ogre::ResourceHandle handle,
			const String& group, bool isManual = false, Ogre::ManualResourceLoader* loader = 0);

		virtual					~AdvancedAnimationSystem();

		//************************************
		// Brief:	  AdvancedAnimationSystem主更新函数
		// Method:    update
		// FullName:  Orphigine::AdvancedAnimationSystem::update
		// Access:    public 
		// Returns:   void
		// Parameter: float time
		//************************************
		void					update(float time);

		void					tickAnimTree(Real deltaSeconds);

		void					_tickAllAnimNodes(Real deltaSeconds);

		void					tickSkelControl(Real deltaSeconds);
		//************************************
		// Brief:	  得到动画树根节点
		// Method:    getAnimTreeOutputNode
		// FullName:  Orphigine::AdvancedAnimationSystem::getAnimTreeOutputNode
		// Access:    public 
		// Returns:   AASNode*
		//************************************
		AASNode*				getAnimTreeOutputNode() const;
		//************************************
		// Brief:	  设置动画树根节点
		// Method:    setAnimTreeOutputNode
		// FullName:  Orphigine::AdvancedAnimationSystem::setAnimTreeOutputNode
		// Access:    public 
		// Returns:   void
		// Parameter: AASNode * val
		//************************************
		void					setAnimTreeOutputNode(AASNode* val);

		typedef Ogre::VectorIterator< AASNodeVector >	NodeIterator;

		//************************************
		// Brief:	  添加节点
		// Method:    addNode
		// FullName:  Orphigine::AdvancedAnimationSystem::addNode
		// Access:    public 
		// Returns:   AASNode*
		// Parameter: const String & name
		// Parameter: unsigned short handle
		//************************************
		AASNode*				addNode(const String& name,unsigned short handle);
		//************************************
		// Brief:	  得到节点
		// Method:    getNode
		// FullName:  Orphigine::AdvancedAnimationSystem::getNode
		// Access:    public 
		// Returns:   AASNode*
		// Parameter: unsigned short handle
		//************************************
		AASNode*				getNode(unsigned short handle) const;
		//************************************
		// Brief:	  得到节点迭代器
		// Method:    getNodeIterator
		// FullName:  Orphigine::AdvancedAnimationSystem::getNodeIterator
		// Access:    public 
		// Returns:   Orphigine::AdvancedAnimationSystem::NodeIterator
		//************************************
		NodeIterator			getNodeIterator();
		//************************************
		// Brief:	  移除节点
		// Method:    removeNode
		// FullName:  Orphigine::AdvancedAnimationSystem::removeNode
		// Access:    public 
		// Returns:   void
		// Parameter: unsigned short handle
		//************************************
		void					removeNode(unsigned short handle);
		//************************************
		// Brief:	  移除全部节点
		// Method:    removeAllNodes
		// FullName:  Orphigine::AdvancedAnimationSystem::removeAllNodes
		// Access:    public 
		// Returns:   void
		//************************************
		void					removeAllNodes();
		//************************************
		// Brief:	  得到节点数目
		// Method:    getNumNodes
		// FullName:  Orphigine::AdvancedAnimationSystem::getNumNodes
		// Access:    public 
		// Returns:   unsigned short
		//************************************
		unsigned short			getNumNodes() const;

		//************************************
		// Brief:	  得到父
		// Method:    getParent
		// FullName:  Orphigine::AdvancedAnimationSystem::getParent
		// Access:    public 
		// Returns:   SkeletonMeshComponent*
		//************************************
		SkeletonMeshComponent*				getParent() const;
		//************************************
		// Brief:	  设置父
		// Method:    setParent
		// FullName:  Orphigine::AdvancedAnimationSystem::setParent
		// Access:    public 
		// Returns:   void
		// Parameter: SkeletonMeshComponent * val
		//************************************
		void					setParent(SkeletonMeshComponent* val);

		//************************************
		// Brief:	  响应动画结束
		// Method:    onAnimationEnd
		// FullName:  Orphigine::AdvancedAnimationSystem::onAnimationEnd
		// Access:    public 
		// Returns:   void
		// Parameter: AASAnimSequenceNode * animSequenceNode
		//************************************
		void					onAnimationEnd(AASAnimSequenceNode* animSequenceNode);

		//************************************
		// Brief:	  响应动画开始播放
		// Method:    onAnimationPlay
		// FullName:  Orphigine::AdvancedAnimationSystem::onAnimationPlay
		// Access:    public 
		// Returns:   void
		// Parameter: AASAnimSequenceNode * animSequenceNode
		//************************************
		void					onAnimationPlay(AASAnimSequenceNode* animSequenceNode);

		//************************************
		// Brief:	  得到Ogre::AnimationState指针
		// Method:    getAnimationState
		// FullName:  Orphigine::AdvancedAnimationSystem::getAnimationState
		// Access:    public 
		// Returns:   Ogre::AnimationState*
		// Parameter: const String & name
		//************************************
		Ogre::AnimationState*	getAnimationState(const String&	name);

		//************************************
		// Brief:	  根据动画名得到相应动画ID
		// Method:    getAnimationIdByName
		// FullName:  Orphigine::AdvancedAnimationSystem::getAnimationIdByName
		// Access:    public 
		// Returns:   int
		// Parameter: const String & name
		//************************************
		int						getAnimationIdByName(const String& name);

		//************************************
		// Brief:	  根据ID得到AASAnimation
		// Method:    getAnimation
		// FullName:  Orphigine::AdvancedAnimationSystem::getAnimation
		// Access:    public 
		// Returns:   AASAnimation*
		// Parameter: int animationID
		//************************************
		AASAnimation*			getAnimation(int animationID);

		//************************************
		// Brief:	  得到骨头数
		// Method:    getNumBones
		// FullName:  Orphigine::AdvancedAnimationSystem::getNumBones
		// Access:    public 
		// Returns:   unsigned short
		//************************************
		unsigned short			getNumBones() const;

		//************************************
		// Brief:	  初始化所有动画
		// Method:    _initAnimations
		// FullName:  Orphigine::AdvancedAnimationSystem::_initAnimations
		// Access:    public 
		// Returns:   void
		//************************************
		void					_initAnimations();


		void					_removeAllAnimations();
	protected:
								AdvancedAnimationSystem();

		void					_updateNeedUpdateAnimations(Real elapsedTime);

		
		void					_disableNeedUpdateAnimations();

		
		void					_accumulateReachedAnimationNodes(Real	elapsedTime);

		
		void					_addAnimation(const String& animName);

		
		virtual void			loadImpl(void);
		
		
		virtual void			unloadImpl(void);
		
		virtual size_t			calculateSize(void) const;

	protected:
		AASNode*							m_animTreeOutputNode;
		ReachedAnimSequenceNodeCollection	m_reachedAnimSequenceNodeCollection;
		TraverseBranchMaskCollection		m_traverseBranchMaskCollection;
		AASNodeVector						m_nodeList;
		SkeletonMeshComponent*							m_parent;
		AASAnimationVector					m_needUpdateAnimationsVec;
	public:
		
		Real				getDirectionalDegree() const;
		
		void					setDirectionalDegree(const Real val);
		
		
		Real				getMovingDegree() const;
		
		void					setMovingDegree(const Real val);

		
		Real				getRidingDegree() const;
		
		void					setRidingDegree(const Real val);

		
		Real				getAttackDegree() const;
		
		void					setAttackDegree(const Real val);

		
		Real				getLivingDegree() const;
		
		void					setLivingDegree(const Real val);

		
		Real				getWeaponDegree() const;
		
		void					setWeaponDegree(const Real val);

		
		Real				getDamageDegree() const;
		
		void					setDamageDegree(Real val);

		
		Real				getPostureDegree() const;
		
		void					setPostureDegree(Real val);
		 
		
		Real				getEquitationDegree() const;
		
		void					setEquitationDegree(Real val);

		
		Real				getGuardDegree() const;
		
		void					setGuardDegree(Real val);

		
		String			getAttackAnimName() const;
		
		void					setAttackAnimName(const String& val);

		
		const String&	getWeaponTypeName() const;
		
		void					setWeaponTypeName(const String& val);

		
		Real				getMoodDegree() const;
		
		void					setMoodDegree(Real val);

		
		Real				getDanceDegree() const;
		
		void					setDanceDegree(Real val);

		
		Real				getWalkDegree() const;
		
		void					setWalkDegree(Real val);

		
		const String&	getMoodAnimName() const;
		
		void					setMoodAnimName(const String& val);

		
		bool					getAttackAnimDirty() const;

		
		void					makeAttackAnimDirty();

		
		void					resetAttackAnimDirty();

		
		bool					getMoodAnimDirty() const;

		
		void					makeMoodAnimDirty();

		
		void					resetMoodAnimDirty();

		bool					getDamageAnimDirty() const;

		void					makeDamageAnimDirty();

		void					resetDamageAnimDirty();

		AASNode*				findAASNode(const String& nodeName);

		void					updateAnimSequenceNodeGroups(Real deltaSeconds);

		void					_updateGroupMasterNode(AnimSeqSynchGroup& group);

		AnimSynchGropVector&	getAnimSynchGroups();

		Real					getGlobalAnimRateScale() const;
		void					setGlobalAnimRateScale(Real val);

		int						getSystemTickTag() const;
		void					setSystemTickTag(int val);

	protected:
		Real			m_directionalDegree;
		Real			m_movingDegree;
		Real			m_ridingDegree;
		Real			m_attackDegree;
		Real			m_livingDegree;
		Real			m_weaponDegree;
		Real			m_damageDegree;
		Real			m_postureDegree;
		Real			m_equitationDegree;
		Real			m_guardDegree;
		Real			m_moodDegree;
		Real			m_danceDegree;
		Real			m_walkDegree;

		String			m_attackAnimName;
		String			m_weaponTypeName;
		String			m_moodAnimName;

		mutable bool	m_attackAnimDirty;
		mutable bool	m_moodAnimDirty;
		mutable bool	m_damageAnimDirty;

		Real			m_globalAnimRateScale;
		int				m_systemTickTag;

		AnimSynchGropVector	m_animSynchGroups;
		NodeNameMap			m_nodeNameHash;
		AASNodeVector		m_tickVec;
	};

	typedef std::shared_ptr<AdvancedAnimationSystem> AdvancedAnimationSystemPtr;

}
#endif // OGAdvancedAnimationSystem_h__