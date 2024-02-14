#include "stdafx.h"
#include "UIManager.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"

template<>
UIManager* GameSingleton<UIManager>::m_sSingleton = nullptr;

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

bool UIManager::showWindow(uint32_t winId)
{
	auto itor = mWindowMap.find(winId);
	if (itor != mWindowMap.end())
	{
		CEGUI::Window*  widget = itor->second->getView();
		
		widget->setVisible(!widget->isVisible());
		return true;
	}

	UIBase* base = nullptr;
	switch (winId)
	{
	case GameUI_SelfEquip:
		base = new SelfEquipWindow();
		break;
	case GameUI_Package:
		base= new PackageWindow();
		break;
	default:
		assert(false);
		break;
	}

	mWindowMap[winId] = base;
	return true;
}

void UIManager::updateWindow(uint32_t winId)
{
	auto itor = mWindowMap.find(winId);
	if (itor != mWindowMap.end())
	{
		itor->second->update();
		return;
	}

	UIBase* base = nullptr;
	switch (winId)
	{
	case GameUI_SelfEquip:
		base = new SelfEquipWindow();
		break;
	case GameUI_Package:
		base = new PackageWindow();
		break;
	default:
		assert(false);
		break;
	}

	mWindowMap[winId] = base;
	base->update();
}

