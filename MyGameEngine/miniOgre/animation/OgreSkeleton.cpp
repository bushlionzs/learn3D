#include "OgreHeader.h"
#include "OgreSkeleton.h"
#include "OgreAnimation.h"
#include "OgreBone.h"
#include "OgreSkeletonManager.h"
#include "OgreAnimationState.h"

namespace Ogre {
	Skeleton::Skeleton()
	{

	}
	Skeleton::Skeleton(const std::string& name)
	{
		mName = name;
	}

	Skeleton::~Skeleton()
	{

	}

	Bone* Skeleton::createBone(const std::string& name, uint32_t handle)
	{
		if (mNameBoneList.count(name))
		{
			assert(false);
		}

		if (mHandleBoneList.count(handle))
		{
			assert(false);
		}

		Bone* bone = new Bone(name, handle);
		mNameBoneList[name] = bone;
		mHandleBoneList[handle] = bone;
		return bone;
	}

	Bone* Skeleton::getBone(uint32_t handle)
	{
		auto itor = mHandleBoneList.find(handle);

		if (itor != mHandleBoneList.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	Animation* Skeleton::createAnimation(const std::string& name, float length)
	{
		if (mAnimationList.count(name))
		{
			assert(false);
		}
		Animation* ani = new Animation(name);
		mAnimationList[name] = ani;
		return ani;
	}

	Animation* Skeleton::getAnimation(const std::string& name)
	{
		auto itor = mAnimationList.find(name);

		if (itor != mAnimationList.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	Animation* Skeleton::getAnimation(uint32_t index)
	{
		auto i = mAnimationList.begin();

		std::advance(i, index);

		return i->second;
	}

	uint32_t Skeleton::getNumBones()
	{
		return (uint32_t)mHandleBoneList.size();
	}

	uint32_t Skeleton::getNumAnimations()
	{
		return (uint32_t)mAnimationList.size();
	}

	std::vector<Bone*> Skeleton::getCloneList()
	{
		auto boneCount = mBoneList.size();
		std::vector<Bone*> blist(boneCount);

		for (int32_t i = 0; i < boneCount; i++)
		{
			blist[i] = new Bone(*mBoneList[i]);
			blist[i]->updateParent(nullptr);
		}


		for (int32_t i = 0; i < boneCount; i++)
		{
			Bone* parent = mBoneList[i]->getParent();
			if (parent)
			{
				uint32_t parentId = parent->getBoneId();
				blist[i]->updateParent(blist[parentId]);
			}
		}
		return blist;
	}

	void Skeleton::setBindingPose(void)
	{
		mBoneList.resize(mHandleBoneList.size());
		for (auto itor : mHandleBoneList)
		{
			mBoneList[itor.first] = itor.second;
		}

		for (auto* b : mBoneList)
		{
			b->_updateFromParent();
		}


		for (auto* b : mBoneList)
		{
			b->setBindingPose();
		}
	}

	void Skeleton::addLinkedSkeletonAnimationSource(
		const String& skelName,
		Real scale)
	{
		for (auto i = mLinkedSkeletonAnimSourceList.begin();
			i != mLinkedSkeletonAnimSourceList.end(); ++i)
		{
			if (skelName == i->skeletonName)
				return; // don't bother
		}


		std::shared_ptr<Skeleton> skeleton = SkeletonManager::getSingleton().load(skelName);

		mLinkedSkeletonAnimSourceList.push_back(
			LinkedSkeletonAnimationSource(skelName, scale, skeleton));

		
	}

	void Skeleton::reset()
	{

	}
	void Skeleton::_initAnimationState(AnimationStateSet* animSet)
	{
		animSet->removeAllAnimationStates();

		AnimationList::iterator i;
		for (i = mAnimationList.begin(); i != mAnimationList.end(); ++i)
		{
			Animation* anim = i->second;
			// Create animation at time index 0, default params mean this has weight 1 and is disabled
			const String& animName = anim->getName();
			animSet->createAnimationState(animName, 0.0, anim->getAnimationLength());
		}

		// Also iterate over linked animation
		LinkedSkeletonAnimSourceList::iterator li;
		for (li = mLinkedSkeletonAnimSourceList.begin();
			li != mLinkedSkeletonAnimSourceList.end(); ++li)
		{
			if (li->pSkeleton)
			{
				li->pSkeleton->_refreshAnimationState(animSet);
			}
		}
	}


	void Skeleton::_refreshAnimationState(AnimationStateSet* animSet)
	{
		// Merge in any new animations
		AnimationList::iterator i;
		for (i = mAnimationList.begin(); i != mAnimationList.end(); ++i)
		{
			Animation* anim = i->second;
			// Create animation at time index 0, default params mean this has weight 1 and is disabled
			const String& animName = anim->getName();
			if (!animSet->hasAnimationState(animName))
			{
				animSet->createAnimationState(animName, 0.0, anim->getAnimationLength());
			}
			else
			{
				// Update length incase changed
				AnimationState* animState = animSet->getAnimationState(animName);
				animState->setLength(anim->getAnimationLength());
				animState->setTimePosition(std::min(anim->getAnimationLength(), animState->getTimePosition()));
			}
		}
		// Also iterate over linked animation
		LinkedSkeletonAnimSourceList::iterator li;
		for (li = mLinkedSkeletonAnimSourceList.begin();
			li != mLinkedSkeletonAnimSourceList.end(); ++li)
		{
			if (li->pSkeleton)
			{
				li->pSkeleton->_refreshAnimationState(animSet);
			}
		}
	}

	void Skeleton::setAnimationState(const AnimationStateSet& animSet)
	{

	}

	Animation* Skeleton::_getAnimationImpl(
		const String& name,
		const LinkedSkeletonAnimationSource** linker) const
	{
		Animation* ret = 0;
		AnimationList::const_iterator i = mAnimationList.find(name);

		if (i == mAnimationList.end())
		{
			LinkedSkeletonAnimSourceList::const_iterator it;
			for (it = mLinkedSkeletonAnimSourceList.begin();
				it != mLinkedSkeletonAnimSourceList.end() && !ret; ++it)
			{
				if (it->pSkeleton)
				{
					ret = it->pSkeleton->_getAnimationImpl(name, linker);
					if (ret && linker)
					{
						*linker = &(*it);
					}

				}
			}

		}
		else
		{
			if (linker)
				*linker = 0;
			ret = i->second;
		}

		return ret;
	}
}