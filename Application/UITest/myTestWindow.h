#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
class MyTestWindow :
	public wraps::BaseLayout
{
public:
	MyTestWindow();
	~MyTestWindow();
	void show(uint32_t id);
	void onWindowMouseButtonPressed(
		MyGUI::Widget* _sender,
		int _left,
		int _top,
		MyGUI::MouseButton _id);
	MyGUI::Widget* getView();
private:
	MyGUI::TextBox* mTextName;
	MyGUI::TextBox* mTextDesc;
	MyGUI::ImageBox* mImageInfo;
	MyGUI::Button* mLeftButton;
	MyGUI::Button* mRightButton;

	MyGUI::EditBox* mEditBox;
};