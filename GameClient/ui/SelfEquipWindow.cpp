#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUIManager.h>

SelfEquipWindow::SelfEquipWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);
	auto* close = _main_window->getChildRecursive("Packet_Close");
	close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&SelfEquipWindow::handle_ButtonClick, this));

	CEGUI::Window* SelfEquip_Board_Background = _main_window->getChild("SelfEquip_Board_Background");

	_equips.resize(HEQUIP_NUMBER);

	for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
	{
		CEGUI::Window* equip = nullptr;
		try
		{
			CEGUI::String name = "SelfEquip_" + std::to_string(i);
			equip = SelfEquip_Board_Background->getChild(name);
		}
		catch (...)
		{

		}
		_equips[i] = equip;
	}
}

bool SelfEquipWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
	return true;
}

void SelfEquipWindow::update()
{
	auto& equips = GameDataManager::GetSingleton().getUserEquip();


	for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
	{
		KItem* item = equips[i];
		uint32_t item_id = 0;
		if (item)
		{
			item_id = item->GetIdTable();
		}
		updateItem(i, item_id);
	}
}

bool SelfEquipWindow::updateItem(
	uint32_t index,
	uint32_t itemId)
{
	ItemData itemInfo;

	if (getItemInfo(itemId, itemInfo))
	{
		const char* fullname = CEGUIManager::getSingleton().getFullIconName(itemInfo.icon);

		_equips[index]->setProperty("Image", fullname);
	}
	else
	{
		if(_equips[index])
		_equips[index]->setProperty("Image", "");
	}

	return true;
}