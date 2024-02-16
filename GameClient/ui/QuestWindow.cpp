#include "OgreHeader.h"
#include "QuestWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUIManager.h>
#include <UIManager.h>

QuestWindow::QuestWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("quest.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);


}

bool QuestWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	uint32_t id = (uint32_t)dd_args.window->getUserData();

	UIManager::GetSingleton().showWindow(id);
	return true;
}

void QuestWindow::update()
{

}

