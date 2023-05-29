#pragma once

#include "engine_struct.h"
#include "OgreSkeleton.h"

namespace Ogre {
	class SkeletonInstance
	{
	public:
		SkeletonInstance(std::shared_ptr<Skeleton>& skeleton);

		RawData* getShaderConstantData(uint32_t index);

		void resetBones();

		uint32_t getNumBones();
		Bone* getBone(uint32_t handle);
		Bone* getBone(const std::string& name);
		uint32_t getNumAnimations();
		Animation* getAnimation(const std::string& name);
		Animation* getAnimation(uint32_t index);

		void addLinkedSkeletonAnimationSource(const String& skelName,
			Real scale = 1.0f);

		void setAnimationState(const AnimationStateSet& animSet);

		void updateBoneMatrix();
	private:
		void buildSkeletonInfo();

		void updateMatrixForM3d(float delta);
		void updateMatrixForOgre(float delta);
		void applyBone(Bone* b, TransformInfo& ti);
	private:
		std::shared_ptr<Skeleton> mSkeleton;
		std::vector<Ogre::Matrix4> mBoneTransforms;
		std::vector<Ogre::Matrix4> mBoneTransformsBak;


		std::vector<Ogre::Matrix4> mBoneTransformsOgre;
		uint32_t mBoneCount;

		float mAnimationLength = 0.0f;
		float mTimePos = 0.0f;
		std::vector<Bone*> mBoneList;
		std::unordered_map<std::string, Bone*> mBoneMap;
		RawData mRawData;

		bool mOgre = false;

		SkeletonAnimationBlendMode mBlendState = ANIMBLEND_AVERAGE;

		uint64_t mFrameLastUpdated = 0;
	};
}