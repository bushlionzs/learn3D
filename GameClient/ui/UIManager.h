#pragma once

#include "GameSingleton.h"
#include "UIDefine.h"
class KPlayer;
class UIManager :public GameSingleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	bool showWindow(uint32_t winId);
	void updateWindow(uint32_t winId);

	KPlayer* getUIPlayer()
	{
		return mPlayer;
	}
private:
	UIBase* getWindow(uint32_t winId);
private:
	std::unordered_map<uint32_t, UIBase*> mWindowMap;
	CEGUI::Window* mRoot = nullptr; 
	KPlayer* mPlayer;
};