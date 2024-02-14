#include "OgreHeader.h"
#include "PackageWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUI/WindowManager.h>

#define ITEM_WIDTH 32
#define ITEM_HEIGHT 32
#define CELL_WIDTH  46
#define CELL_HEIGHT 45

PackageWindow::PackageWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Package.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);

	auto* close = _main_window->getChildRecursive("Packet_Close");
	close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&PackageWindow::handle_ButtonClick, this));
}


bool PackageWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
	return true;
}

bool PackageWindow::updateItem(
	uint32_t row,
	uint32_t column,
	uint32_t itemId)
{
	
	return true;
}


void PackageWindow::update()
{
	const std::vector<KItem*>&  itemlist = GameDataManager::GetSingleton().getUserBag();

	for (int32_t i = 0; i < itemlist.size(); i++)
	{
		KItem* item = itemlist[i];
		if (item == nullptr)
		{
			continue;
		}
		int row = i / 6;
		int col = i % 6;

		updateItem(row, col, item->GetIdTable());
	}
}

