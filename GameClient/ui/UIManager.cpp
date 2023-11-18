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

bool UIManager::showWindow(uint32_t winId, bool show)
{
	auto itor = mWindowMap.find(winId);
	if (itor != mWindowMap.end())
	{
		MyGUI::Widget*  widget = itor->second->getView();
		widget->setVisible(show);
		return true;
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
	return true;
}

