#include "OgreHeader.h"
#include "OGAASAnimation.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGSkeletonMeshComponent.h"
#include "OGAASAnimSequenceNode.h"

namespace Orphigine
{
	AASAnimation::AASAnimation( AdvancedAnimationSystem* system,Ogre::AnimationState* animState )
		: m_parent(system),
		m_animState(animState),
		m_activeReferencingNodesCount(0),
		m_accumulatedUnifyWeight(0.0f),
		m_isCreatedBonesMask(false),
		m_traverseFeatherNodeCount(0),
		/*m_maskedBonesArray(NULL),
		m_maskedBonesWeightArray(NULL),
		m_nonmaskedBonesWeightArray(NULL),*/
		m_numBones(0)
	{
		m_numBones = system->getNumBones();

	/*	m_maskedBonesArray = new bool[m_numBones];
		m_maskedBonesWeightArray = new Real[m_numBones];
		m_nonmaskedBonesWeightArray = new Real[m_numBones];*/
		//m_bonesWeightArray = new Real[m_numBones];

		//for (int i = 0;i < m_numBones;i ++)
		//{
		//	/*m_maskedBonesArray[i] = false;
		//	m_maskedBonesWeightArray[i] = 0.0f;
		//	m_nonmaskedBonesWeightArray[i] = 0.0f;*/
		//	m_bonesWeightArray[i] = 0.0f;
		//}
	}

	AASAnimation::~AASAnimation()
	{
		/*delete []m_maskedBonesArray;
		m_maskedBonesArray = NULL;

		delete []m_maskedBonesWeightArray;
		m_maskedBonesWeightArray = NULL;

		delete []m_nonmaskedBonesWeightArray;
		m_nonmaskedBonesWeightArray = NULL;*/

		/*delete []m_bonesWeightArray;
		m_bonesWeightArray = NULL;*/
	}

	Ogre::AnimationState* AASAnimation::getAnimState() const
	{
		return m_animState;
	}

	void AASAnimation::setAnimState( Ogre::AnimationState* val )
	{
		m_animState = val;
	}

	Ogre::Real AASAnimation::getWeight() const
	{
		return m_animState->getWeight();
	}

	void AASAnimation::setWeight( Real weight )
	{
		m_animState->setWeight(weight);
	}

	bool AASAnimation::getEnabled() const
	{
		return m_animState->getEnabled();
	}

	void AASAnimation::setEnabled( bool isEnable )
	{
		m_animState->setEnabled(isEnable);
	}

	bool AASAnimation::getLoop() const
	{
		return m_animState->getLoop();
	}

	void AASAnimation::setLoop( bool isLooping )
	{
		m_animState->setLoop(isLooping);
	}

	int AASAnimation::getActiveReferencingNodesCount() const
	{
		return m_activeReferencingNodesCount;
	}

	void AASAnimation::resetActiveReferencingNodesCount()
	{
		m_activeReferencingNodesCount = 0;
	}

	void AASAnimation::increaseActiveReferencingNodesCount()
	{
		m_activeReferencingNodesCount ++;
	}

	Real AASAnimation::getAccumulatedUnifyWeight() const
	{
		return m_accumulatedUnifyWeight;
	}

	void AASAnimation::resetAccumulatedUnifyWeight()
	{
		m_accumulatedUnifyWeight = 0.0f;
	}

	Real AASAnimation::increaseAccumulatedUnifyWeight( Real val )
	{
		assert(m_animState && "AASAnimation::increaseAccumulatedUnifyWeight");

		m_accumulatedUnifyWeight += val;
		if(1.0f < m_accumulatedUnifyWeight)
			m_accumulatedUnifyWeight = 1.0f;

		if(m_animState)
			m_animState->setWeight(m_accumulatedUnifyWeight);

		return m_accumulatedUnifyWeight;
	}

	void AASAnimation::reset()
	{
		m_animState->setTimePosition(0.0f);
	}

	bool AASAnimation::getCreatedBonesMask() const
	{
		return m_isCreatedBonesMask;
	}

	void AASAnimation::setCreatedBonesMask( bool val )
	{
		m_isCreatedBonesMask = val;
	}

	void AASAnimation::createOrSetBonesMask( Real weight )
	{
		if (!m_isCreatedBonesMask)
		{
			m_animState->createBlendMask(m_numBones,weight);
			m_isCreatedBonesMask = true;
		}
	}

	void AASAnimation::setBonesMaskEntry( unsigned short boneHandle,Real weight )
	{
		m_animState->setBlendMaskEntry(boneHandle,weight);
	}

	Ogre::Real AASAnimation::getAccumulatedBonesWeight( unsigned short boneHandle )
	{
		assert(boneHandle < m_numBones && "AASAnimation::getAccumulatedBonesWeight");
		assert(m_animState && m_animState->getBlendMask() && "AASAnimation::getAccumulatedBonesWeight");

		if (m_animState->getBlendMask())
			return m_animState->getBlendMaskEntry(boneHandle);

		return 0.0f;
	}

	void AASAnimation::resetAccumulatedBonesWeight()
	{
		assert(m_animState && "AASAnimation::resetAccumulatedBonesWeight");

		for (unsigned short i = 0;i < m_numBones;i ++)
		{
			if (m_animState->getBlendMask())
				m_animState->setBlendMaskEntry( i , 0.0f );
		}
	}

	Real AASAnimation::increaseAccumulatedBonesWeight( unsigned short boneHandle,Real val )
	{
		assert(boneHandle < m_numBones && "AASAnimation::increaseAccumulatedBonesWeight");
		assert(m_animState && m_animState->getBlendMask() && "AASAnimation::increaseAccumulatedBonesWeight");

		Real boneWeight = 0.0f;
		if (m_animState && m_animState->getBlendMask())
		{
			boneWeight = m_animState->getBlendMaskEntry(boneHandle);
			boneWeight += val;
			if(boneWeight > 1.0f)
				boneWeight = 1.0f;
			m_animState->setBlendMaskEntry(boneHandle,boneWeight);
			/*m_bonesWeightArray[boneHandle] += val;
			if(m_bonesWeightArray[boneHandle] > 1.0f)
				m_bonesWeightArray[boneHandle] = 1.0f;*/
		}

		return boneWeight;
	}

	Ogre::Real AASAnimation::getTraverseFeatherNodeCount() const
	{
		return m_traverseFeatherNodeCount;
	}

	void AASAnimation::resetTraverseFeatherNodeCount()
	{
		m_traverseFeatherNodeCount = 0;
	}

	void AASAnimation::increaseTraverseFeatherNodeCount(int val)
	{
		m_traverseFeatherNodeCount += val;
	}

	void AASAnimation::destroyBonesMask()
	{
		if (m_isCreatedBonesMask)
		{
			m_animState->destroyBlendMask();
			m_isCreatedBonesMask = false;
		}
	}

	unsigned short AASAnimation::getNumBones() const
	{
		return m_numBones;
	}

	void AASAnimation::setNumBones( unsigned short val )
	{
		m_numBones = val;
	}

	const String& AASAnimation::getAnimationName() const
	{
		return m_animState->getAnimationName();
	}

	Ogre::Real AASAnimation::getTimePosition() const
	{
		return m_animState->getTimePosition();
	}

	void AASAnimation::setTimePosition( Real timePos )
	{
		m_animState->setTimePosition(timePos);
	}

	Ogre::Real AASAnimation::getLength() const
	{
		return	m_animState->getLength();
	}

	void AASAnimation::setLength( Real length )
	{
		m_animState->setLength(length);
	}
}
