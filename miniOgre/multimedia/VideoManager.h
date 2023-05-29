#pragma once

#include "OgreSingleton.h"

class AVBoard;

class VideoManager : public Ogre::Singleton<VideoManager>
{
public:
	VideoManager();
	~VideoManager();

	bool _playVideoMaterial(
		const String& matName);
private:
	std::unordered_map<String, AVBoard*> mVideoMap;
};