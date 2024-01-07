#pragma once

#include "OgreSingleton.h"

class AVBoard;
class CAVPlayer;
class VideoManager : public Ogre::Singleton<VideoManager>
{
public:
	VideoManager();
	~VideoManager();

	bool _playVideoMaterial(
		const String& matName);


	bool playSound(const std::string& name);
private:
	std::unordered_map<String, AVBoard*> mVideoMap;
	std::unordered_map<String, std::shared_ptr<CAVPlayer>> mAudioMap;
};