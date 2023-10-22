#include "OgreHeader.h"
#include "imageButton.h"
#include "CEGUIResourceManager.h"

GameButton::GameButton()
{

}

GameButton::~GameButton()
{

}

void GameButton::addImages(
	const String& imageName,
	const String& normalName,
	const String& hoverName,
	const String& pushName)
{
	mImageName = imageName;
	mNormalName = normalName;
	mHoverName = hoverName;
	mPushName = pushName;

	useNormal();
}

void GameButton::useNormal()
{
	useImage(mNormalName);
}

void GameButton::useHover()
{
	useImage(mHoverName);
}
void GameButton::usePush()
{
	useImage(mPushName);
}

void GameButton::useImage(const String& name)
{
	CEGUIImage& imageinfo =
		CEGUIResourceManager::getSingleton().getImageInfo(
			mImageName, name);
	mImageBox->setImageTexture(imageinfo._imagename);
	mImageBox->setImageTile(imageinfo._size);
	mImageBox->setImageCoord(imageinfo._coord);
}
