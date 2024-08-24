#include "OgreHeader.h"
#include <string_util.h>
#include "QuestLogWindow.h"
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
#include "GameDataManager.h"
#include <string_util.h>

QuestLogWindow::QuestLogWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("questlog.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);
	auto* close = _main_window->getChildRecursive("QuestLog_Close");
	if (close)
	{
		close->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&QuestLogWindow::handle_ButtonClick, this));
	}
	
	CEGUI::Listbox* listbox = (CEGUI::Listbox*)_main_window->getChildRecursive("QuestLog_Listbox");
	listbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&QuestLogWindow::listbox_ListSelectionChangedHandler, this));
	
}

bool QuestLogWindow::listbox_ListSelectionChangedHandler(const CEGUI::EventArgs& args)
{
	const CEGUI::WindowEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	CEGUI::Listbox* listbox = (CEGUI::Listbox*)dd_args.window;
	const CEGUI::ListboxItem* item = listbox->getFirstSelectedItem();
	if (item)
	{
		auto id = item->getID();
		QuestManager* qm = GameDataManager::GetSingleton().getQuestManager();
		QuestManager::QuestInfoMemo memo;
		if (qm->getQuestInfoMemo(id, memo))
		{
			CEGUI::Window* desc = (CEGUI::Listbox*)_main_window->getChildRecursive("QuestLog_Desc");
			std::string content = memo.strQuestName;
			content += "\n";
			content += "任务目标:\n";
			content += memo.strQuestManual + "\n";
			content += "任务回复:\n";
			content += memo.strQuestSubmitNPC + "\n";
			content += "任务攻略:\n";
			content += memo.strQuestHelp + "\n";
			content += "任务描述:\n";
			content += memo.strQuestDesc;
			content += "\n";
			mButtonlist.clear();
			replaceUIDesc(content, mButtonlist);
			uint32_t index = 1;
			std::string strUtf8;
			for (auto& btn : mButtonlist)
			{
				std::string name = "DynamicButton_" + std::to_string(index++);
				CEGUI::Window* link = (CEGUI::Listbox*)desc->getChildRecursive(name);
				strUtf8 = dy::acsi_to_utf8(btn.caption);
				link->setProperty("Text", (CEGUI::utf8*)strUtf8.c_str());
				link->setUserString("link", btn.attachment);
				link->subscribeEvent(
					CEGUI::Window::EventMouseClick,
					CEGUI::Event::Subscriber(&QuestLogWindow::handle_LinkClick, this));
			}
			std::vector<QuestManager::QuestReward> rewardlist;

			const base::Quest& quest = qm->getQuest(id);
			qm->getQuestReward(quest.quest_id(), rewardlist);
			content += "任务奖励:\n";
			index = 1;
			for (uint32_t i = 0; i < rewardlist.size(); i++)
			{
				QuestManager::QuestReward& reward = rewardlist[i];
				if (!reward.rewardDesc.empty())
				{
					content += reward.rewardDesc + "\n";
				}
				else
				{
					ItemData data;
					if (getItemInfo(reward.itemId, data))
					{
						content += "固定物品:\n";
						content += "[window='DynamicImage_" + std::to_string(index) + "']";
						std::string name = "DynamicImage_" + std::to_string(index++);

						CEGUI::Window* image = (CEGUI::Listbox*)desc->getChildRecursive(name);
						const char* fullname = CEGUIManager::getSingleton().getFullIconName(data.icon);
						image->setProperty("Image", fullname);
					}
				}
			}
			strUtf8 = dy::acsi_to_utf8(content);
			desc->setProperty("Text", (CEGUI::utf8*)strUtf8.c_str());
		}
	}
	return true;
}

bool QuestLogWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
	return true;
}

bool QuestLogWindow::handle_LinkClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	CEGUI::Window* link = dd_args.window;
	const auto& data = link->getUserString("link");

	std::string value = data.c_str();
	return true;
}

bool QuestLogWindow::handle_OptionClick(const CEGUI::EventArgs& args)
{
	
	return true;
}

void QuestLogWindow::update()
{
	CEGUI::Listbox* listbox = (CEGUI::Listbox*)_main_window->getChildRecursive("QuestLog_Listbox");

	listbox->resetList();
	QuestManager* qm = GameDataManager::GetSingleton().getQuestManager();

	auto  count = qm->getQuestCount();
	std::string strUtf32;
	uint32_t nIndex = 0;
	QuestManager::QuestInfoMemo memo;
	for (uint32_t i = 0; i < count; i++)
	{
		if (qm->getQuestInfoMemo(i, memo))
		{
			strUtf32 = dy::acsi_to_utf8(memo.strQuestName);
			CEGUI::ListboxTextItem* pItem = new CEGUI::ListboxTextItem((CEGUI::utf8*)strUtf32.c_str(), i);
			listbox->addItem(pItem);
			
		}
	}
}

