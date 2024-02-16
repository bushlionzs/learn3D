#pragma once
#include <CEGUI/CEGUI.h>
enum
{
	GameUI_SelfEquip = 0,
	GameUI_Package,
	GameUI_MainMenu,
	GameUI_Quest,
};

class UIBase
{
public:
	UIBase()
	{
		_main_window = nullptr;
	}
	virtual ~UIBase()
	{

	}
	virtual CEGUI::Window* getView()
	{
		return _main_window;
	}
	virtual void update() {}
protected:
	CEGUI::Window* _main_window;
};