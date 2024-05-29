#include "string_util.h"
#include "OgreHeader.h"
#include "GameToolTip.h"
#include "application_util.h"
#include "CEGUIManager.h"

GameToolTip::GameToolTip()
{

	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ToolTip.xml");
	
	_title = _main_window->getChild("Title");
	_item_picture = _main_window->getChild("ItemPicture");
	_item_property = _main_window->getChild("ItemProperty");
	_item_name = _main_window->getChild("ItemName");
	_item_bind = _main_window->getChild("ItemBind");
	_star_picture = _main_window->getChild("StarProperty");
	_expand_property = _main_window->getChild("ExpandProperty");
	_item_place = _main_window->getChild("ItemPlace");

	_main_window->subscribeEvent(CEGUI::Tooltip::EventTooltipActive, &GameToolTip::handle_ToolTip, this);
}

void GameToolTip::update(KItem* item)
{
	if (item == nullptr)
	{
		return;
	}
	ItemData itemInfo;

	auto id = item->GetIdTable();
	if (getItemInfo(id, itemInfo))
	{
		_title->setProperty("Text", (CEGUI::utf8*)dy::acsi_to_utf8(itemInfo.title).c_str());
		_item_place->setProperty("Text", (CEGUI::utf8*)dy::acsi_to_utf8(itemInfo.desc).c_str());
		_item_name->setProperty("Text", (CEGUI::utf8*)dy::acsi_to_utf8(itemInfo.type).c_str());
		const char* fullname = CEGUIManager::getSingleton().getFullIconName(itemInfo.icon);
		_item_picture->setProperty("Image", fullname);
		_item_property->setProperty("Text", (CEGUI::utf8*)dy::acsi_to_utf8(item->getBasePropertyString()).c_str());
	}
}


bool GameToolTip::handle_ToolTip(const CEGUI::EventArgs& args)
{
	_main_window->setSize(CEGUI::USize(cegui_absdim(300), cegui_absdim(400)));
	return true;
}



