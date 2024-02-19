#include "OgreHeader.h"
#include "PackageWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUI/WindowManager.h>
#include <CEGUIManager.h>
#include "client_message.pb.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "net_message_manager.h"

#define ITEM_COUNT 36
PackageWindow::PackageWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Package.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);

	auto* close = _main_window->getChildRecursive("Packet_Close");
	close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&PackageWindow::handle_ButtonClick, this));
	_package_item_list.resize(ITEM_COUNT);

	CEGUI::Window* Packet_Background_Cover = _main_window->getChild("Packet_Background_Cover");
	for (uint32_t i = 0; i < ITEM_COUNT; i++)
	{
		_package_item_list[i]._item_id = 0;
		_package_item_list[i]._item_pos = i;
		CEGUI::String name = "DragContainer" + std::to_string(i);
		
		CEGUI::Window* drag = Packet_Background_Cover->getChild(name);
		_package_item_list[i]._item_image = drag->getChild("Image");
		_package_item_list[i]._item_image->setUserData((void*)i);
		_package_item_list[i]._item_image->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&PackageWindow::handle_PackageClick, this));
	}
}


bool PackageWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
	return true;
}

bool PackageWindow::handle_PackageClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);

	uint32_t index = (uint32_t)dd_args.window->getUserData();

	if (_package_item_list[index]._item_id > 0)
	{
		clientmessage::MsgUseEquip msg;

		KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
		msg.set_player_id(pPlayer->getId());
		msg.set_map_id(GameSceneManager::getSingleton().getActiveSceneId());
		msg.set_bag_index(index);
		msg.set_equip_point(-1);

		NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_USE_EQUIP, &msg);
	}

	return true;
}

bool PackageWindow::updateItem(
	uint32_t index,
	uint32_t itemId)
{
	ItemData itemInfo;

	if (getItemInfo(itemId, itemInfo))
	{
		const char* fullname = CEGUIManager::getSingleton().getFullIconName(itemInfo.icon);

		_package_item_list[index]._item_image->setProperty("Image", fullname);
	}
	else
	{
		_package_item_list[index]._item_image->setProperty("Image", "");
	}
	
	return true;
}


void PackageWindow::update()
{
	const std::vector<KItem*>&  itemlist = GameDataManager::GetSingleton().getUserBag();

	for (int32_t i = 0; i < ITEM_COUNT; i++)
	{
		KItem* item = itemlist[i];
		uint32_t item_id = 0;
		if (item != nullptr)
		{
			item_id = item->GetIdTable();
		}
		updateItem(i, item_id);
	}
}

