/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OGAASAnimation.h
	Created:    William (jiang628@hotmail.com) 2008:06:29:13:35
	Description :
    Revision :

=============================================================================*/

#ifndef OGAASAnimation_h__
#define OGAASAnimation_h__

#include "OgreAnimationState.h"

namespace Orphigine
{
#define INVAILD_ANIMATION_ID -1
#define INVAILD_MASKED_BONE_ID -1

	class AdvancedAnimationSystem;
	class AASAnimSequenceNode;

	class AASAnimation
	{
	public:
		AASAnimation(AdvancedAnimationSystem* system,Ogre::AnimationState* animState);
		virtual ~AASAnimation();

		Ogre::AnimationState*				getAnimState() const;
		void								setAnimState(Ogre::AnimationState* val);

		Real								getWeight() const ;
		void								setWeight(Real weight);

		bool								getEnabled() const;
		void								setEnabled(bool isEnable);

		bool								getLoop() const;
		void								setLoop(bool isLooping);

		Real								getTimePosition() const;
		void								setTimePosition(Real timePos);

		Real								getLength() const;
		void								setLength(Real length);

		const String&						getAnimationName() const;

		
		int									getActiveReferencingNodesCount() const;
		void								resetActiveReferencingNodesCount();
		void								increaseActiveReferencingNodesCount();
		
		
		Real								getAccumulatedUnifyWeight() const;
		void								resetAccumulatedUnifyWeight();
		Real								increaseAccumulatedUnifyWeight(Real val);


		Real								getAccumulatedBonesWeight(unsigned short boneHandle);
		void								resetAccumulatedBonesWeight();
		Real								increaseAccumulatedBonesWeight(unsigned short boneHandle,Real val);


		Real								getTraverseFeatherNodeCount() const;
		void								resetTraverseFeatherNodeCount();
		void								increaseTraverseFeatherNodeCount(int val);

		void								reset();

		bool								getCreatedBonesMask() const;
		void								setCreatedBonesMask(bool val);

		void								createOrSetBonesMask(Real weight);

		void								destroyBonesMask();

		void								setBonesMaskEntry(unsigned short boneHandle,Real weight);

		unsigned short						getNumBones() const;
		void								setNumBones(unsigned short val);

		int									getAnimLoopNumberDirty() const;
		void								setAnimLoopNumberDirty(int val);
		void								resetAnimLoopNumberDirty();

		void								_makeForceSetTimePosDirty();
	protected:
		Ogre::AnimationState*				m_animState;
		AdvancedAnimationSystem*			m_parent;
		int									m_activeReferencingNodesCount;
		Real								m_accumulatedUnifyWeight;
		int									m_traverseFeatherNodeCount;
		bool								m_isCreatedBonesMask;
		/*bool*								m_maskedBonesArray;
		Real*								m_maskedBonesWeightArray;
		Real*								m_nonmaskedBonesWeightArray;*/
		//Real*								m_bonesWeightArray;
		unsigned short						m_numBones;
	private:
	};
} // Orphigine

#endif // OGAASAnimation_h__