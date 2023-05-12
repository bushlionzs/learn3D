#include "OgreHeader.h"
#include "animation_track.h"
#include "keyframe.h"

AnimationTrack::AnimationTrack()
{

}

AnimationTrack::~AnimationTrack()
{

}

KeyFrame* AnimationTrack::createKeyFrame(Real timePos)
{
	KeyFrame* frame = new KeyFrame(timePos);
	mKeyFrames.push_back(frame);
	return frame;
}


void AnimationTrack::interpolate(Real t, TransformInfo& ti)
{
	if (t <= mKeyFrames.front()->mTimePos)
	{
		ti.translate = mKeyFrames.front()->mTranslation;
		ti.scale = mKeyFrames.front()->mScale;
		ti.rotate = mKeyFrames.front()->mRotationQuat;
	}
	else if (t >= mKeyFrames.back()->mTimePos)
	{
		ti.translate = mKeyFrames.back()->mTranslation;
		ti.scale = mKeyFrames.back()->mScale;
		ti.rotate = mKeyFrames.back()->mRotationQuat;
	}
	else
	{
		for (UINT i = 0; i < mKeyFrames.size() - 1; ++i)
		{
			if (t >= mKeyFrames[i]->mTimePos && t <= mKeyFrames[i + 1]->mTimePos)
			{
				float lerpPercent =
					(t - mKeyFrames[i]->mTimePos) / (mKeyFrames[i + 1]->mTimePos - mKeyFrames[i]->mTimePos);

				Ogre::Vector3 s0 = mKeyFrames[i]->mScale;
				Ogre::Vector3 s1 = mKeyFrames[i + 1]->mScale;

				Ogre::Vector3 p0 = mKeyFrames[i]->mTranslation;
				Ogre::Vector3 p1 = mKeyFrames[i + 1]->mTranslation;

				Ogre::Quaternion q0 = mKeyFrames[i]->mRotationQuat;
				Ogre::Quaternion q1 = mKeyFrames[i + 1]->mRotationQuat;

				ti.rotate = Ogre::Quaternion::nlerp(lerpPercent, q0, q1, true);

				ti.translate = p0 + (p1 - p0) * lerpPercent;
				ti.scale = s0 + (s1 - s0) * lerpPercent;
			
				break;
			}
		}
	}

}

void AnimationTrack::interpolate(Real t, Ogre::Matrix4& m)
{
	
}

float AnimationTrack::getAnimationLength()
{
	if (mKeyFrames.empty())
	{
		return 0.0f;
	}
	return mKeyFrames.back()->mTimePos;
}

uint32_t AnimationTrack::getNumKeyFrames() const
{
	return (uint32_t)mKeyFrames.size();
}

KeyFrame* AnimationTrack::getNodeKeyFrame(uint32_t index) const
{
	return mKeyFrames[index];
}