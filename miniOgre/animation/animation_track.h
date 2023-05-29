#pragma once
class KeyFrame;

#include "engine_struct.h"
class AnimationTrack
{
public:
	AnimationTrack();
	~AnimationTrack();

	KeyFrame* createKeyFrame(Real timePos);

	void interpolate(Real t, Ogre::Matrix4& m);
	void interpolate(Real t, TransformInfo& ti);

	float getAnimationLength();

	//for ogre
	uint32_t getNumKeyFrames() const;

	KeyFrame* getNodeKeyFrame(uint32_t index) const;
private:
	std::vector<KeyFrame*> mKeyFrames;
};