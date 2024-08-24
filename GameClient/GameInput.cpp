#include "stdafx.h"
#include "GameInput.h"

#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "UIManager.h"
#include "KObjectManager.h"
#include "CEGUIManager.h"
#include "kplayer.h"
#include "game_scene_manager.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "game_scene.h"
#include "StructDB.h"
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

	mCampAndStandDataMgr = new CampAndStandDataMgr;

	mCampAndStandDataMgr->InitFromDBMemory(CGameTableManager::GetSingleton().GetTable(TABLE_CAMP_AND_STAND)->GetTableFile());
}

void GameInput::injectMouseMove(int _absx, int _absy, int _absz)
{
	KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
	if (nullptr == pPlayer)
	{
		return;
	}
	Ogre::Vector3 fvMouseHitPlan;
	KObject* pSelectObj = (KObject*)KObjectManager::GetSingleton().GetMouseOverObject(_absx, _absy, fvMouseHitPlan);

	if (pSelectObj != mLastSelectObj)
	{
		if (pSelectObj == nullptr)
		{
			CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Normal);
			mLastSelectObj = nullptr;
		}
		else
		{
			auto* campA = pPlayer->GetCampData();
			auto* campB = pSelectObj->GetCampData();
			auto pCampAndStand = mCampAndStandDataMgr->GetInstanceByID(campA->m_nCampID);
			eRELATION eCampType = RELATION_FRIEND;
			if (pCampAndStand && pCampAndStand->StandByCampID(campB->m_nCampID))
			{
				eCampType = RELATION_ENEMY;
			}

			if (eCampType == RELATION_FRIEND)
			{
				mSelectObjAttack = false;
				CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Speak);
			}
			else
			{
				mSelectObjAttack = true;
				CEGUIManager::getSingleton().ChangeMouseCursor(MouseType_Attack);
			}
			
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

		if (mLastSelectObj)
		{
			if (mSelectObjAttack)
			{

			}
			else
			{
				player->speakTo(mLastSelectObj->getId());
			}
		}
		else
		{
			if (player)
			{
				player->injectMousePress(_absx, _absy, _id);
			}
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