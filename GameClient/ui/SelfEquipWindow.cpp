#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"

SelfEquipWindow::SelfEquipWindow()
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
}

void SelfEquipWindow::update()
{

}