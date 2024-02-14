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


private:
	
};



#endif // EDITOR_WINDOW_H_
