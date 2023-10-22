#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
class TestWindow :
	public wraps::BaseLayout
{
public:
	TestWindow();
	~TestWindow();

	MyGUI::Widget* getView();
private:
	MyGUI::TextBox* mTextBox;
	MyGUI::ImageBox* mImageTest;
	MyGUI::Widget* mItemBox;
};