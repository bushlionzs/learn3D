#pragma once
#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include "ToolTip.h"
#include "UIDefine.h"

struct PackageItemInfo
{
	int32_t _item_pos;
	uint32_t _item_id;
	MyGUI::ImageBox* _item_image;
};
class PackageWindow :public UIBase,
	public wraps::BaseLayout
{
public:
	PackageWindow();

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

	void notifyMouseMove(MyGUI::Widget* _sender, int _left, int _top);
	void notifySetFocus(MyGUI::Widget* current, MyGUI::Widget* last);


	virtual void update() override;
private:
	bool updateItem(
		uint32_t row,
		uint32_t column,
		uint32_t itemId);
	void setItemFocus(
		uint32_t row,
		uint32_t column);
private:
	MyGUI::ImageBox* mImageBackgroud;
	MyGUI::ImageBox* mImageBackgroudCover;
	std::vector<PackageItemInfo> mItemList;
	ToolTip* mToolTip;
	bool mDragging = false;
	MyGUI::IntPoint mDragOffset;

	uint32_t _row;
	uint32_t _column;

	std::vector<MyGUI::ImageBox*> _imageboxs;

	MyGUI::ImageBox* _focus_box;
};


