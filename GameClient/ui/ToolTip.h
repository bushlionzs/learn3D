#ifndef TOOL_TIP_H_
#define TOOL_TIP_H_

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
struct ItemData
{
	String _itemname;
};

class ToolTip :
	public wraps::BaseLayout
{
public:
	ToolTip();

	void show(ItemData* _data);
	void hide();
	void move(const MyGUI::IntPoint& _point);

private:
	MyGUI::TextBox* mTextName;
	MyGUI::TextBox* mTextLevel;
	MyGUI::ImageBox* mImageInfo;

	int mOffsetHeight;
};


#endif // TOOL_TIP_H_
