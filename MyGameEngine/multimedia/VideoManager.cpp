#include "OgreHeader.h"
#include "VideoManager.h"
#include "AVBoard.h"
#include "OgreMaterialManager.h"
#include "FFmpegInitializer.h"

template<> VideoManager* Ogre::Singleton<VideoManager>::msSingleton = 0;

VideoManager::VideoManager()
{

}

VideoManager::~VideoManager()
{

}

bool VideoManager::_playVideoMaterial(
	const String& matName)
{
	AVBoard* pAVBoard = nullptr;
	auto itor = mVideoMap.find(matName);

	if (itor != mVideoMap.end())
	{
		pAVBoard = itor->second;
	}
	else
	{
		pAVBoard = new AVBoard;
	}
	
	
	mVideoMap.emplace(matName, pAVBoard);
	
	auto mat = MaterialManager::getSingleton().getByName(matName);

	if (!mat || !mat->_isVideo())
	{
		return false;
	}

	String videoName = mat->getVideoName();
	pAVBoard->setupAVBoard(matName, videoName);
	return true;
}