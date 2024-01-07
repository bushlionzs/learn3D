#ifndef TOOL_TIP_H_
#define TOOL_TIP_H_

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include "application_util.h"

class ToolTip :
	public wraps::BaseLayout
{
public:
	ToolTip();

	void show(uint32_t id, MyGUI::Widget* parent = nullptr);
	void hide();
	void move(const MyGUI::IntPoint& _point);

private:
	MyGUI::TextBox* mTextName;
	MyGUI::TextBox* mTextDesc;
	MyGUI::ImageBox* mImageInfo;

	int mOffsetHeight;

	GameItemData mItemData;
};


#endif // TOOL_TIP_H_
