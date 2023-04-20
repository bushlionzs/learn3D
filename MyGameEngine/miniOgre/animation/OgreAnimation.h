#pragma once
#include "OgreAnimationState.h"
class AnimationTrack;
namespace Ogre {
	class SkeletonInstance;
	class Animation
	{
	public:
		typedef std::map<uint32_t, AnimationTrack*> NodeTrackList;
		enum InterpolationMode : uint8_t
		{
			/** Values are interpolated along straight lines. */
			IM_LINEAR,
			/** Values are interpolated along a spline, resulting in smoother changes in direction. */
			IM_SPLINE
		};
	public:
		Animation(const std::string& name);
		~Animation();

		AnimationTrack* createNodeTrack(uint32_t boneId, Bone* targetNode);
		AnimationTrack* getAnimationTrack(uint32_t boneId);
		NodeTrackList& _getNodeTrackList();
		float getAnimationLength();

		//for ogre
		void setUseBaseKeyFrame(
			bool useBaseKeyFrame,
			Real keyframeTime,
			const String& baseAnimName);
		/** Whether a base keyframe is being used for this Animation. */
		bool getUseBaseKeyFrame() const;
		/** If a base keyframe is being used, the time of that keyframe. */
		Real getBaseKeyFrameTime() const;
		/** If a base keyframe is being used, the Animation that provides that keyframe. */
		const String& getBaseKeyFrameAnimationName() const;
		const std::string& getName() const;
		const NodeTrackList& getNodeTrackList() const;

		void apply(SkeletonInstance* skel, Real timePos, Real weight,
			 Real scale);
		void apply(SkeletonInstance* skel, Real timePos, Real weight,
			const AnimationState::BoneBlendMask* blendMask, Real scale);
	private:
		NodeTrackList mNodeTrackList;
		std::string mName;
		bool mUseBaseKeyFrame = false;

		Real mBaseKeyFrameTime;
		String mBaseKeyFrameAnimationName;
	};
}