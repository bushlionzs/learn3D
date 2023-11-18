#pragma once
#include <MyGUI.h>
enum
{
	GameUI_SelfEquip = 0,
	GameUI_Package,
};

class UIBase
{
public:
	virtual MyGUI::Widget* getView() = 0;
};