#include "OgreHeader.h"
#include "MainMenuWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUIManager.h>
#include <UIManager.h>

MainMenuWindow::MainMenuWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Main.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);

	CEGUI::Window* push_1 = _main_window->getChild("push_1");
	push_1->setUserData((void*)GameUI_SelfEquip);
	push_1->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&MainMenuWindow::handle_ButtonClick, this));

	CEGUI::Window* push_2 = _main_window->getChild("push_2");
	push_2->setUserData((void*)GameUI_Package);
	push_2->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&MainMenuWindow::handle_ButtonClick, this));
}

bool MainMenuWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	uint32_t id = (uint32_t)dd_args.window->getUserData();

	UIManager::GetSingleton().showWindow(id);
	return true;
}

void MainMenuWindow::update()
{

}

