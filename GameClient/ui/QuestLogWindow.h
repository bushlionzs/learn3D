#ifndef QUESTLOG_WINDOW_H_
#define QUESTLOG_WINDOW_H_

#include <CEGUI/CEGUI.h>
#include "ToolTip.h"
#include "UIDefine.h"
#include "application_util.h"

class QuestLogWindow :public UIBase
{
public:
	QuestLogWindow(CEGUI::Window* parent);


	void update();

	bool handle_ButtonClick(const CEGUI::EventArgs& args);

	bool handle_LinkClick(const CEGUI::EventArgs& args);

	bool listbox_ListSelectionChangedHandler(const CEGUI::EventArgs& args);

	bool handle_OptionClick(const CEGUI::EventArgs& args);

private:
	std::vector<UIDesc> mButtonlist;
};



#endif // QUESTLOG_WINDOW_H_
