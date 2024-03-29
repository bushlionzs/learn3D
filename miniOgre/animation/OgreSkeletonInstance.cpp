#include "OgreHeader.h"
#include "OgreSkeletonInstance.h"
#include "OgreSkeleton.h"
#include "OgreBone.h"
#include "OgreAnimation.h"
#include "animation_track.h"
#include "OgreAnimationState.h"
#include "OgreRoot.h"

#define MAX_BONE_NUMBER 200
namespace Ogre {

	SkeletonInstance::SkeletonInstance(std::shared_ptr<Skeleton>& skeleton)
		:mSkeleton(skeleton)
	{
		buildSkeletonInfo();
		mOgre = true;
	}

	

	/*void SkeletonInstance::updateMatrixForM3d(float delta)
	{
		mOgre = false;

		for (int32_t i = 0; i < mBoneTransformsBak.size(); i++)
		{
			AnimationTrack* track = mCurrentAnimation->getAnimationTrack(i);
			track->interpolate(delta, mBoneTransformsBak[i]);
		}

		mBoneTransforms[0] = mBoneTransformsBak[0];

		int32_t numbone = mBoneTransformsBak.size();

		std::vector<bool> visit(numbone, false);

		visit[0] = true;


		Ogre::Matrix4 toRoot;
		for (int32_t i = 1; i < mBoneTransforms.size(); i++)
		{
			Ogre::Matrix4 toParent = mBoneTransformsBak[i];

			uint32_t parentId = mBoneList[i]->getParent()->getBoneId();

			if (!visit[parentId])
			{
				assert(false);
			}


			const Ogre::Matrix4& parentToRoot = mBoneTransforms[parentId];

			toRoot = parentToRoot * toParent;
			mBoneTransforms[i] = toRoot;

			visit[i] = true;
		}

		Ogre::Matrix4 finalTransform;
		for (int32_t i = 0; i < mBoneTransforms.size(); i++)
		{
			const Ogre::Matrix4& offset = mBoneList[i]->getInverseBindMatrix();

			Ogre::Matrix4& toRoot = mBoneTransforms[i];
			finalTransform = toRoot * offset;
			mBoneTransforms[i] = finalTransform.transpose();
		}
	}


	void SkeletonInstance::updateMatrixForOgre(float delta)
	{
		mOgre = true;
		resetBones();
		TransformInfo ti;

		for (int32_t i = 0; i < mBoneCount; i++)
		{
			Bone* b = mBoneList[i];
			uint32_t handle = b->getBoneId();
			AnimationTrack* track = mCurrentAnimation->getAnimationTrack(handle);
			if (track)
			{
				track->interpolate(delta, ti);
				applyBone(b, ti);
				b->_getOffsetTransform(mBoneTransformsOgre[i]);
			}
			else
			{
				ti.scale = Ogre::Vector3::UNIT_SCALE;
				ti.rotate = Ogre::Quaternion::IDENTITY;
				ti.translate = Ogre::Vector3::ZERO;
				applyBone(b, ti);
				b->_getOffsetTransform(mBoneTransformsOgre[i]);
			}
		}


	}*/

	void SkeletonInstance::resetBones()
	{
		for (auto& b : mBoneList)
		{
			b->reset();
		}
	}

	uint32_t SkeletonInstance::getNumBones()
	{
		return mSkeleton->getNumBones();
	}

	Bone* SkeletonInstance::getBone(uint32_t handle)
	{
		return mBoneList[handle];
	}

	Bone* SkeletonInstance::getBone(const std::string& name)
	{
		auto itor = mBoneMap.find(name);
		if (itor != mBoneMap.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	uint32_t SkeletonInstance::getNumAnimations()
	{
		return mSkeleton->getNumAnimations();
	}

	Animation* SkeletonInstance::getAnimation(const std::string& name)
	{
		return mSkeleton->getAnimation(name);
	}

	Animation* SkeletonInstance::getAnimation(uint32_t index)
	{
		return mSkeleton->getAnimation(index);
	}

	void SkeletonInstance::addLinkedSkeletonAnimationSource(const String& skelName, Real scale)
	{
		mSkeleton->addLinkedSkeletonAnimationSource(skelName, scale);
	}


	void SkeletonInstance::setAnimationState(const AnimationStateSet& animSet)
	{
		Root& root = Root::getSingleton();
		auto currentFrame = root.getNextFrameNumber();
		if (mFrameLastUpdated == currentFrame)
		{
			return;
		}
		mFrameLastUpdated = currentFrame;
		resetBones();

		Real weightFactor = 1.0f;
		if (mBlendState == ANIMBLEND_AVERAGE)
		{
			// Derive total weights so we can rebalance if > 1.0f
			Real totalWeights = 0.0f;
			EnabledAnimationStateList::const_iterator animIt;
			for (animIt = animSet.getEnabledAnimationStates().begin(); animIt != animSet.getEnabledAnimationStates().end(); ++animIt)
			{
				const AnimationState* animState = *animIt;
				// Make sure we have an anim to match implementation
				const LinkedSkeletonAnimationSource* linked = 0;
				if (mSkeleton->_getAnimationImpl(animState->getAnimationName(), &linked))
				{
					totalWeights += animState->getWeight();
				}
			}

			// Allow < 1.0f, allows fade out of all anims if required 
			if (totalWeights > 1.0f)
			{
				weightFactor = 1.0f / totalWeights;
			}
		}

		// Per enabled animation state
		EnabledAnimationStateList::const_iterator animIt;
		for (animIt = animSet.getEnabledAnimationStates().begin(); animIt != animSet.getEnabledAnimationStates().end(); ++animIt)
		{
			const AnimationState* animState = *animIt;
			const LinkedSkeletonAnimationSource* linked = 0;
			Animation* anim = mSkeleton->_getAnimationImpl(animState->getAnimationName(), &linked);
			// tolerate state entries for animations we're not aware of
			if (anim)
			{
				if (animState->hasBlendMask())
				{
					anim->apply(this, animState->getTimePosition(), animState->getWeight() * weightFactor,
						animState->getBlendMask(), linked ? linked->scale : 1.0f);
				}
				else
				{
					anim->apply(this, animState->getTimePosition(), animState->getWeight() * weightFactor,
						 linked ? linked->scale : 1.0f);
				}
			}
		}

		updateBoneMatrix();
	}

	void SkeletonInstance::updateBoneMatrix()
	{
		for (uint32_t i = 0; i < mBoneCount; i++)
		{
			Bone* b = mBoneList[i];
			b->_getOffsetTransform(mBoneTransformsOgre[i]);
			
			mBoneTransformsOgre[i] = mBoneTransformsOgre[i].transpose();
		}
	}

	void SkeletonInstance::applyBone(Bone* b, TransformInfo& ti)
	{
		b->translate(ti.translate);
		b->rotate(ti.rotate);
		b->scale(ti.scale);
	}

	RawData* SkeletonInstance::getSkinnedData(uint32_t dummy)
	{
		if (mOgre)
			mRawData.mData = (const char*)mBoneTransformsOgre.data();
		else
			mRawData.mData = (const char*)mBoneTransforms.data();
		mRawData.mDataSize = (uint32_t)mBoneTransforms.size() * sizeof(Ogre::Matrix4);
		return &mRawData;
	}

	void SkeletonInstance::buildSkeletonInfo()
	{
		mBoneCount = mSkeleton->getNumBones();
		assert(mBoneCount <= MAX_BONE_NUMBER);
		mBoneTransforms.resize(mBoneCount);
		mBoneTransformsBak.resize(mBoneCount);
		mBoneTransformsOgre.resize(mBoneCount);
		mBoneList = mSkeleton->getCloneList();

		for (auto b : mBoneList)
		{
			mBoneMap[b->getName()] = b;
		}

		for (uint32_t i = 0; i < mBoneCount; i++)
		{
			mBoneTransforms[i] = Ogre::Matrix4::IDENTITY;
			mBoneTransformsOgre[i] = Ogre::Matrix4::IDENTITY;
		}

	}
}