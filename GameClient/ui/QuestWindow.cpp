#include "OgreHeader.h"
#include <string_util.h>
#include "QuestWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KObjectManager.h"
#include "game_scene_manager.h"
#include "kcharacter.h"
#include "KItem.h"
#include <CEGUIManager.h>
#include <UIManager.h>
#include <CEGUI/FontManager.h>
#include <kcharacter.h>
#include <kplayer.h>
#include <GameDataCharacter.h>
#include "client_message.pb.h"
#include "net_message_manager.h"

QuestWindow::QuestWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("quest.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);
	auto* close = _main_window->getChildRecursive("Quest_Close");
	close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&QuestWindow::handle_ButtonClick, this));

}

bool QuestWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
	return true;
}

bool QuestWindow::handle_OptionClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	void* userData = dd_args.window->getUserData();

	uint32_t i = (uint32_t)userData;

	servermessage::ServerMsgQueryEventResult& dummy =
		UIManager::GetSingleton().getQueryEvent();
	const servermessage::EventItem& item = dummy.eventlist(i);

	clientmessage::MsgEventRequest msg;

	auto playId = KObjectManager::GetSingleton().getMySelf()->getId();
	auto mapId = GameSceneManager::getSingleton().getActiveSceneId();
	auto targetId = dummy.object_id();
	auto scriptid = item.scriptid();
	auto index = item.item_index();
	msg.set_map_id(mapId);
	msg.set_player_id(playId);
	msg.set_target_id(targetId);
	msg.set_mid_script(scriptid);
	msg.set_ex_index(index);

	NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_EVENT_REQUEST, &msg);
	return true;
}

void QuestWindow::update()
{
	servermessage::ServerMsgQueryEventResult& dummy = 
		UIManager::GetSingleton().getQueryEvent();

	auto objectId = dummy.object_id();

	

	KObject* pObject = KObjectManager::GetSingleton().getObject(objectId);

	KCharacter* pCharacter = (KCharacter*)pObject;

	auto portrait = pCharacter->GetPortrait();

	if (portrait != nullptr)
	{
		auto* touxiang = _main_window->getChildRecursive("Quest_touxiang");
		std::string name = transformImageName(portrait);
		touxiang->setProperty("Image", name.c_str());
	}

	auto* npcName = _main_window->getChildRecursive("Quest_NPCname");

	auto* name = pCharacter->GetCharacterData()->Get_Utf8Name();
	
	npcName->setProperty("Text", (CEGUI::utf8*)name);
	
	CEGUI::FontManager& fontManager(CEGUI::FontManager::getSingleton());
	CEGUI::Font& font(fontManager.createFromFile("simhei8.font"));

	uint32_t count = dummy.eventlist_size();
	auto* desc = _main_window->getChildRecursive("QuestDesc");

	//std::wstring aa = L"任务描述\n任务描述";
	//std::string bb = dy::unicode_to_utf8(aa);
	//desc->setProperty("Text", (CEGUI::utf8*)bb.c_str());
	EventData tmp;

	std::string source;
	for (uint32_t i = 0; i < count; i++)
	{
		const servermessage::EventItem& item = dummy.eventlist(i);
		getEventItemInfo(&item, tmp);

		if (tmp.type == EVENT_ITEM_TYPE_TEXT)
		{
			std::string utf8 = dy::acsi_to_utf8(tmp.desc);
			source += utf8.c_str();
			
		}
		else if (tmp.type == EVENT_ITEM_TYPE_SCRIPT_ID)
		{
			std::string utf8 = dy::acsi_to_utf8(tmp.desc);
			source += "\n";
			source += "[window = 'Quest_Option']";

			auto* option = desc->getChildRecursive("Quest_Option");
			option->setProperty("Text", (CEGUI::utf8*)utf8.c_str());
			option->setFont(&font);

			option->subscribeEvent(
				CEGUI::Window::EventMouseClick,
				CEGUI::Event::Subscriber(&QuestWindow::handle_OptionClick, this));

			option->setUserData((void*)i);
		}
	}
	
	desc->setProperty("Text", (CEGUI::utf8*)source.c_str());
	desc->setFont(&font);
}

