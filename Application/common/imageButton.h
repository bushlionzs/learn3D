#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"

class GameButton
{
public:
	GameButton();
	~GameButton();

	void addImages(
		const String& imageName,
		const String& normalName,
		const String& hoverName,
		const String& pushName);

	void useNormal();
	void useHover();
	void usePush();
private:
	void useImage(const String& name);
public:
	MyGUI::ImageBox* mImageBox;
	String mImageName;
	String mNormalName;
	String mHoverName;
	String mPushName;
};