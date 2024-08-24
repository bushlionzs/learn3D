#pragma once

#include "GameSingleton.h"
#include "UIDefine.h"
#include "server_message.pb.h"
class KPlayer;
class UIManager :public GameSingleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	bool showWindow(uint32_t winId, bool show = true);
	void updateWindow(uint32_t winId);

	KPlayer* getUIPlayer()
	{
		return mPlayer;
	}
	void updateQueryEvent(servermessage::ServerMsgQueryEventResult& msg)
	{
		mLastQueryEvent = msg;
	}

	servermessage::ServerMsgQueryEventResult& getQueryEvent()
	{
		return mLastQueryEvent;
	}
private:
	UIBase* getWindow(uint32_t winId);
private:
	std::unordered_map<uint32_t, UIBase*> mWindowMap;
	CEGUI::Window* mRoot = nullptr; 
	KPlayer* mPlayer;
	servermessage::ServerMsgQueryEventResult mLastQueryEvent;
};