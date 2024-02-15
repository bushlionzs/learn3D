#ifndef MAINMENU_WINDOW_H_
#define MAINMENU_WINDOW_H_

#include <CEGUI/CEGUI.h>
#include "ToolTip.h"
#include "UIDefine.h"

class MainMenuWindow :public UIBase
{
public:
	MainMenuWindow(CEGUI::Window* parent);


	void update();

	bool handle_ButtonClick(const CEGUI::EventArgs& args);

};



#endif // MAINMENU_WINDOW_H_
