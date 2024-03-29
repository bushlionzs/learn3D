#ifndef EDITOR_WINDOW_H_
#define EDITOR_WINDOW_H_

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"



class SelfEquipWindow :
	public wraps::BaseLayout
{
public:
	SelfEquipWindow();

	void clearView();

	MyGUI::Widget* getView();

	void notifyToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info);

	void onWindowMouseButtonPressed(
		MyGUI::Widget* _sender,
		int _left,
		int _top,
		MyGUI::MouseButton _id);
	void onWindowMouseDrag(
		MyGUI::Widget* _sender,
		int _left,
		int _top,
		MyGUI::MouseButton _id);
	void onWindowMouseButtonReleased(
		MyGUI::Widget* _sender,
		int _left,
		int _top,
		MyGUI::MouseButton _id);
	void setModelTexture(const String& name);
private:
	MyGUI::ImageBox* mImageEquip;
	MyGUI::ImageBox* mImageClose;
	MyGUI::ImageBox* mImageHelp;
	MyGUI::ImageBox* mImageModel;


	bool mDragging = false;
	MyGUI::IntPoint mDragOffset;
};



#endif // EDITOR_WINDOW_H_
