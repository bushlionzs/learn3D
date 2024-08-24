#ifndef QUEST_WINDOW_H_
#define QUEST_WINDOW_H_

#include <CEGUI/CEGUI.h>
#include "ToolTip.h"
#include "UIDefine.h"

class QuestWindow :public UIBase
{
public:
	QuestWindow(CEGUI::Window* parent);


	void update();

	bool handle_ButtonClick(const CEGUI::EventArgs& args);

	bool handle_OptionClick(const CEGUI::EventArgs& args);
};



#endif // QUEST_WINDOW_H_
