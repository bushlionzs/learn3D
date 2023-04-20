#pragma once

#include "OgreSerializer.h"


class AnimationTrack;
class KeyFrame;


class  OgreSkeletonSerializerImpl : public Ogre::Serializer
{
	const uint32_t SSTREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	const uint32_t HEADER_STREAM_ID_EXT = 0x1000;
	struct LinkedSkeletonAnimationSource;

	/// Skeleton compatibility versions
	enum SkeletonVersion
	{
		/// OGRE version v1.0+
		SKELETON_VERSION_1_0,
		/// OGRE version v1.8+
		SKELETON_VERSION_1_8,

		/// Latest version available
		SKELETON_VERSION_LATEST = 100
	};
public:
	OgreSkeletonSerializerImpl();
	virtual ~OgreSkeletonSerializerImpl();

	void importSkeleton(std::shared_ptr<Ogre::DataStream>& stream, Ogre::Skeleton* skeleton);

	void readBone(
		std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Skeleton* pSkel);


	void readBoneParent(
		std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Skeleton* pSkel);

	void readAnimation(
		std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Skeleton* pSkel);
	void readAnimationTrack(
		std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Animation* anim,
		Ogre::Skeleton* pSkel);
	void readKeyFrame(
		std::shared_ptr<Ogre::DataStream>& stream,
		AnimationTrack* track,
		Ogre::Skeleton* pSkel);
	void readSkeletonAnimationLink(
		std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Skeleton* pSkel);
private:
	size_t calcBoneSize(const Ogre::Skeleton* pSkel, const Ogre::Bone* pBone);
	size_t calcBoneSizeWithoutScale(const Ogre::Skeleton* pSkel, const Ogre::Bone* pBone);
	size_t calcBoneParentSize(const Ogre::Skeleton* pSkel);
	size_t calcAnimationSize(const Ogre::Skeleton* pSkel, const Ogre::Animation* pAnim, SkeletonVersion ver);
	size_t calcAnimationTrackSize(const Ogre::Skeleton* pSkel, const AnimationTrack* pTrack);
	size_t calcKeyFrameSize(const Ogre::Skeleton* pSkel, const KeyFrame* pKey);
	size_t calcKeyFrameSizeWithoutScale(const Ogre::Skeleton* pSkel, const KeyFrame* pKey);
	size_t calcSkeletonAnimationLinkSize(const Ogre::Skeleton* pSkel,
		const LinkedSkeletonAnimationSource& link);
};