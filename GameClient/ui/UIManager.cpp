#include "stdafx.h"
#include "UIManager.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "MainMenuWindow.h"
#include "QuestWindow.h"
#include "QuestLogWindow.h"
#include <CEGUIManager.h>
#include "kplayer.h"
#include "GameToolTip.h"

template<>
UIManager* GameSingleton<UIManager>::m_sSingleton = nullptr;

UIManager::UIManager()
{
	mRoot = CEGUIManager::getSingleton().getRootWindow();

	mPlayer = nullptr;
	
}

UIManager::~UIManager()
{

}

bool UIManager::showWindow(uint32_t winId, bool show)
{
	auto* tip = CEGUIManager::getSingleton().getToolTip();
	if (tip == nullptr)
	{
		tip = new GameToolTip();
		CEGUIManager::getSingleton().setToolTip(tip);
	}
	UIBase* base = getWindow(winId);
	CEGUI::Window* widget = base->getView();
	widget->setVisible(show);
	return true;
}

void UIManager::updateWindow(uint32_t winId)
{
	UIBase* base = getWindow(winId);
	base->update();
	
}

UIBase* UIManager::getWindow(uint32_t winId)
{
	if (mPlayer == nullptr)
	{
		mPlayer = new KPlayer();
		mPlayer->initialize();
	}
	
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
	case GameUI_QuestLog:
		base = new QuestLogWindow(mRoot);
		break;
	default:
		assert(false);
		break;
	}

	mWindowMap[winId] = base;

	return base;
}

