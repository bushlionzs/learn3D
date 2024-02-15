#ifndef EDITOR_WINDOW_H_
#define EDITOR_WINDOW_H_

#include <CEGUI/CEGUI.h>
#include "ToolTip.h"
#include "UIDefine.h"

class SelfEquipWindow :public UIBase
{
public:
	SelfEquipWindow(CEGUI::Window* parent);

	void clearView();



	
	void setModelTexture(const String& name);

	void update();

	bool handle_ButtonClick(const CEGUI::EventArgs& args);
private:
	bool updateItem(
		uint32_t index,
		uint32_t itemId);
private:
	std::vector<CEGUI::Window*> _equips;
};



#endif // EDITOR_WINDOW_H_
