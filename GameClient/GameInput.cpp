#include "stdafx.h"
#include "GameInput.h"

#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "UIManager.h"
#include "KObjectManager.h"
#include "CEGUIManager.h"
#include "kplayer.h"
#include "game_scene_manager.h"
#include "game_scene.h"
template<>
GameInput* GameSingleton<GameInput>::m_sSingleton = nullptr;

GameInput::GameInput()
{

}

GameInput::~GameInput()
{

}

void GameInput::init()
{
	InputManager::getSingleton().addListener(this);
}

void GameInput::injectMouseMove(int _absx, int _absy, int _absz)
{
	KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
	if (nullptr == pPlayer)
	{
		return;
	}
	/*_absx = 166;
	_absy = 351;*/
	Ogre::Vector3 fvMouseHitPlan;
	KObject* pSelectObj = (KObject*)KObjectManager::GetSingleton().GetMouseOverObject(_absx, _absy, fvMouseHitPlan);

	if (pSelectObj != mLastSelectObj)
	{
		if (pSelectObj == nullptr)
		{
			CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Normal);
		}
		else
		{
			CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Speak);
		}

		mLastSelectObj = pSelectObj;
	}
}

void GameInput::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (CEGUIManager::getSingleton().isMouseInGUI())
	{
		return;
	}
	if (_id == OIS::MB_Left)
	{
		auto player = KObjectManager::GetSingleton().getMySelf();

		if (player)
		{
			player->injectMousePress(_absx, _absy, _id);
		}
			
	}

	if (_id == OIS::MB_Right)
	{
		auto scene = GameSceneManager::getSingleton().GetActiveScene();

		std::vector<Orphigine::ActorPtr> objects;
		scene->getIntersectObject(_absx, _absy, objects);
		if (!objects.empty())
		{
			int kk = 0;
		}
	}
}

void GameInput::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{

}

void GameInput::injectKeyPress(KeyCode _key, uint32_t _text)
{
	auto player = KObjectManager::GetSingleton().getMySelf();
	if (player)
	{
		player->input(_key);
	}
	

	input(_key);
}

void GameInput::injectKeyRelease(KeyCode _key)
{

}

void GameInput::injectMouseWheel(int _absz)
{

}

void GameInput::injectMouseCursor()
{

}

void GameInput::input(KeyCode _key)
{
	if (_key == KeyCode::C)
	{
		UIManager::GetSingleton().showWindow(GameUI_SelfEquip);
	}
	else if (_key == KeyCode::B)
	{
		UIManager::GetSingleton().showWindow(GameUI_Package);
	}
	else if (_key == KeyCode::V)
	{
		UIManager::GetSingleton().showWindow(GameUI_Quest);
	}
}