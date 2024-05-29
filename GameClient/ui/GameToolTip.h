#ifndef TOOL_TIP_H_
#define TOOL_TIP_H_

#include <CEGUI/CEGUI.h>
#include "application_util.h"
#include "UIDefine.h"
#include "KItem.h"
class GameToolTip :public UIBase
{
public:
	GameToolTip();

	void update(KItem* item);
	bool handle_ToolTip(const CEGUI::EventArgs& args);
private:
	CEGUI::Window* _title = nullptr;
	CEGUI::Window* _item_picture = nullptr;
	CEGUI::Window* _item_property = nullptr;
	CEGUI::Window* _item_name = nullptr;
	CEGUI::Window* _item_bind = nullptr;
	CEGUI::Window* _star_picture = nullptr;
	CEGUI::Window* _expand_property = nullptr;
	CEGUI::Window* _item_place = nullptr;
};


#endif // TOOL_TIP_H_
