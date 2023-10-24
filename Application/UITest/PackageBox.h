#pragma once

#include <MyGUI.h>
#include "BaseLayout/BaseLayout.h"
#include <limits>


class PackageBox :
	public wraps::BaseLayout
{
public:
	PackageBox(MyGUI::Widget* _parent = nullptr);
	~PackageBox();

public:
	void init(uint32_t row, uint32_t column, MyGUI::IntCoord& pos);
	bool updateItem(
		uint32_t row, 
		uint32_t column, 
		uint32_t itemId);
	void setItemFocus(
		uint32_t row,
		uint32_t column);
	void notifyMouseButtonPressed(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void notifyMouseDrag(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void notifyMouseMove(MyGUI::Widget* _sender, int _left, int _top);
	void notifySetFocus(MyGUI::Widget* current, MyGUI::Widget* last);
public:

private:

	uint32_t _row;
	uint32_t _column;

	std::vector<MyGUI::ImageBox*> _imageboxs;

	MyGUI::ImageBox* _background;
	MyGUI::ImageBox* _focus_box;
};


