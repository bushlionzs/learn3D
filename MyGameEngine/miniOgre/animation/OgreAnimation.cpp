#include "OgreHeader.h"
#include "OgreAnimation.h"
#include "animation_track.h"
#include "OgreSkeletonInstance.h"
#include "OgreBone.h"

namespace Ogre {
	Animation::Animation(const std::string& name)
	{
		mName = name;
	}

	Animation::~Animation()
	{

	}

	AnimationTrack* Animation::createNodeTrack(uint32_t boneId, Bone* targetNode)
	{
		if (mNodeTrackList.count(boneId))
		{
			assert(false);
		}

		AnimationTrack* track = new AnimationTrack();

		mNodeTrackList[boneId] = track;
		return track;
	}

	AnimationTrack* Animation::getAnimationTrack(uint32_t boneId)
	{
		auto itor = mNodeTrackList.find(boneId);
		if (itor != mNodeTrackList.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	Animation::NodeTrackList& Animation::_getNodeTrackList()
	{
		return mNodeTrackList;
	}

	float Animation::getAnimationLength()
	{
		if (mNodeTrackList.empty())
		{
			return 0.0f;
		}
		auto itor = mNodeTrackList.begin();

		return itor->second->getAnimationLength();
	}

	void Animation::setUseBaseKeyFrame(
		bool useBaseKeyFrame,
		Real keyframeTime,
		const String& baseAnimName)
	{
		mUseBaseKeyFrame = useBaseKeyFrame;
		mUseBaseKeyFrame = keyframeTime;
		mBaseKeyFrameAnimationName = baseAnimName;
	}

	bool Animation::getUseBaseKeyFrame() const
	{
		return mUseBaseKeyFrame;
	}

	/** If a base keyframe is being used, the time of that keyframe. */
	Real Animation::getBaseKeyFrameTime() const
	{
		return mBaseKeyFrameTime;
	}
	/** If a base keyframe is being used, the Animation that provides that keyframe. */
	const String& Animation::getBaseKeyFrameAnimationName() const
	{
		return mBaseKeyFrameAnimationName;
	}

	const std::string& Animation::getName() const
	{
		return mName;
	}

	const Animation::NodeTrackList& Animation::getNodeTrackList() const
	{
		return mNodeTrackList;
	}

	void Animation::apply(SkeletonInstance* skel, Real timePos, Real weight,
		Real scale)
	{
		TransformInfo ti;
		for (auto i = mNodeTrackList.begin(); i != mNodeTrackList.end(); ++i)
		{
			// get bone to apply to 
			Bone* b = skel->getBone(i->first);
			i->second->interpolate(timePos, ti);
			b->translate(ti.translate * weight * scale);

			Quaternion rotate = Quaternion::nlerp(weight,
				Quaternion::IDENTITY,
				ti.rotate, false);
			b->rotate(rotate);
			b->scale(ti.scale);
		}
	}

	void Animation::apply(SkeletonInstance* skel, Real timePos, Real weight,
		const AnimationState::BoneBlendMask* blendMask, Real scale)
	{
		//TimeIndex timeIndex = _getTimeIndex(timePos);

		NodeTrackList::iterator i;
		TransformInfo ti;
		for (i = mNodeTrackList.begin(); i != mNodeTrackList.end(); ++i)
		{
			// get bone to apply to 
			Bone* b = skel->getBone(i->first);
			i->second->interpolate(timePos, ti);

			float cw = (*blendMask)[b->getBoneId()] * weight;
			b->translate(ti.translate * cw * scale);

			Quaternion rotate = Quaternion::nlerp(cw,
				Quaternion::IDENTITY, 
				ti.rotate, false);
			b->rotate(rotate);
			b->scale(ti.scale);
		}
	}
}
