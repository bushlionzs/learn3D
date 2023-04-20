#pragma once

#include "OgreResource.h"

namespace Ogre {

	enum SkeletonAnimationBlendMode : uint8_t {
		/// Animations are applied by calculating a weighted average of all animations
		ANIMBLEND_AVERAGE = 0,
		/// Animations are applied by calculating a weighted cumulative total
		ANIMBLEND_CUMULATIVE = 1
	};

	struct LinkedSkeletonAnimationSource
	{
		String skeletonName;
		SkeletonPtr pSkeleton;
		Real scale;
		LinkedSkeletonAnimationSource(const String& skelName, Real scl)
			: skeletonName(skelName), scale(scl) {}
		LinkedSkeletonAnimationSource(const String& skelName, Real scl,
			SkeletonPtr skelPtr)
			: skeletonName(skelName), pSkeleton(skelPtr), scale(scl) {}
	};

	class Skeleton: public Resource
	{
	public:
		typedef std::map<std::string, Animation*> AnimationList;
		typedef std::map<std::string, Bone*> NameBoneList;
		typedef std::map<uint32_t, Bone*> HandleBoneList;
		
		Skeleton(const std::string& name);
		~Skeleton();

		Bone* createBone(const std::string& name, uint32_t handle);

		Bone* getBone(uint32_t handle);
		Animation* createAnimation(const std::string& name, float length);
		Animation* getAnimation(const std::string& name);
		Animation* getAnimation(uint32_t index);
		uint32_t getNumBones();
		uint32_t getNumAnimations();
		std::vector<Bone*> getCloneList();

		//for ogre

		void setBindingPose(void);
		void addLinkedSkeletonAnimationSource(
			const String& skelName,
			Real scale);

		virtual void loadImpl(void) {}
		/** Internal implementation of the 'unload' action; called regardless of
			whether this resource is being loaded from a ManualResourceLoader.
		*/
		virtual void unloadImpl(void) {}

		void reset();
		virtual void _initAnimationState(AnimationStateSet* animSet);
		void _refreshAnimationState(AnimationStateSet* animSet);
		virtual void setAnimationState(const AnimationStateSet& animSet);

		virtual Animation* _getAnimationImpl(
			const String& name,
			const LinkedSkeletonAnimationSource** linker) const;
	protected:
		Skeleton();
		typedef std::vector<LinkedSkeletonAnimationSource>
			LinkedSkeletonAnimSourceList;
		AnimationList mAnimationList;
		NameBoneList mNameBoneList;
		HandleBoneList mHandleBoneList;
		std::vector<Bone*> mBoneList;

		mutable LinkedSkeletonAnimSourceList mLinkedSkeletonAnimSourceList;
	};
}