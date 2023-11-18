#include "stdafx.h"
#include "GameInput.h"

#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "UIManager.h"
template<>
GameInput* GameSingleton<GameInput>::m_sSingleton = nullptr;

GameInput::GameInput()
{

}

GameInput::~GameInput()
{

}

void GameInput::input(KeyCode _key)
{
	if (_key == KeyCode::C)
	{
		UIManager::GetSingleton().showWindow(GameUI_SelfEquip, true);
	}
	else if (_key == KeyCode::B)
	{
		UIManager::GetSingleton().showWindow(GameUI_Package, true);
	}
}