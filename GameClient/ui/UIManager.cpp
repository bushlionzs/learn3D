#include "stdafx.h"
#include "UIManager.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "MainMenuWindow.h"
#include "QuestWindow.h"
#include <CEGUIManager.h>

template<>
UIManager* GameSingleton<UIManager>::m_sSingleton = nullptr;

UIManager::UIManager()
{
	mRoot = CEGUIManager::getSingleton().getRootWindow();

	CEGUI::FontManager& fontManager(CEGUI::FontManager::getSingleton());
	CEGUI::Font& font(fontManager.createFromFile("simhei12.font"));
	CEGUIManager::getSingleton().getGUIContext()->setDefaultFont(&font);
}

UIManager::~UIManager()
{

}

bool UIManager::showWindow(uint32_t winId)
{
	UIBase* base = getWindow(winId);
	CEGUI::Window* widget = base->getView();
	widget->setVisible(!widget->isVisible());
	return true;
}

void UIManager::updateWindow(uint32_t winId)
{
	UIBase* base = getWindow(winId);
	base->update();
	
}

UIBase* UIManager::getWindow(uint32_t winId)
{
	auto itor = mWindowMap.find(winId);
	if (itor != mWindowMap.end())
	{
		return itor->second;
	}
	UIBase* base = nullptr;
	switch (winId)
	{
	case GameUI_SelfEquip:
		base = new SelfEquipWindow(mRoot);
		break;
	case GameUI_Package:
		base = new PackageWindow(mRoot);
		break;
	case GameUI_MainMenu:
		base = new MainMenuWindow(mRoot);
		break;
	case GameUI_Quest:
		base = new QuestWindow(mRoot);
		break;
	default:
		assert(false);
		break;
	}

	mWindowMap[winId] = base;

	return base;
}

