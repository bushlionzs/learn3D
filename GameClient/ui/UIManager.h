#pragma once

#include "GameSingleton.h"
#include "UIDefine.h"
#include "BaseLayout/BaseLayout.h"

class UIManager :public GameSingleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	bool showWindow(uint32_t winId, bool show);

private:
	std::unordered_map<uint32_t, UIBase*> mWindowMap;
};