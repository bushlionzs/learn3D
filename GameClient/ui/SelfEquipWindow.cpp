#include "OgreHeader.h"
#include "SelfEquipWindow.h"
#include "application_util.h"
#include "GameDataManager.h"
#include "KItem.h"
#include <CEGUIManager.h>
#include "client_message.pb.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "net_message_manager.h"
#include "role.h"
#include <OgreRoot.h>
#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"
#include "OgreRenderTexture.h"
#include <OgreTexture.h>
#include <OgreRenderTarget.h>
#include <OgreViewport.h>
#include <CEGUI/InputEvent.h>
#include <CEGUI/widgets/DragContainer.h>
#include <CEGUI/CEGUI.h>
#include "game_camera.h"
#include <CEGUI/ImageManager.h>
#include "GameDataCharacter.h"
#include "UIManager.h"
#include "GameToolTip.h"


SelfEquipWindow::SelfEquipWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);
	_close = _main_window->getChildRecursive("Packet_Close");
	_close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&SelfEquipWindow::handle_ButtonClick, this));

	CEGUI::Window* SelfEquip_Board_Background = _main_window->getChild("SelfEquip_Board_Background");

	_turn_left = SelfEquip_Board_Background->getChild("SelfEquip_Model_TurnLeft");
	_turn_right = SelfEquip_Board_Background->getChild("SelfEquip_Model_TurnRight");

	_turn_left->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&SelfEquipWindow::handle_ButtonClick, this));

	_turn_right->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&SelfEquipWindow::handle_ButtonClick, this));

	_equips.resize(HEQUIP_NUMBER);

	auto* tip = CEGUIManager::getSingleton().getToolTip();
	for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
	{
		CEGUI::Window* equip = nullptr;
		try
		{
			CEGUI::String name = "SelfEquip_" + std::to_string(i);
			equip = SelfEquip_Board_Background->getChild(name);
		}
		catch (...)
		{

		}
		_equips[i] = equip;

		if (equip)
		{
			equip->setTooltip((CEGUI::Tooltip*)tip->getView());
			equip->setUserData((void*)(i+1));
			equip->subscribeEvent(
				CEGUI::Window::EventMouseClick,
				CEGUI::Event::Subscriber(&SelfEquipWindow::handle_EquipClick, this));

			equip->subscribeEvent(
				CEGUI::Window::EventMouseEntersArea,
				CEGUI::Event::Subscriber(&SelfEquipWindow::handle_MouseEnter, this));

			equip->subscribeEvent(
				CEGUI::Window::EventMouseLeavesArea,
				CEGUI::Event::Subscriber(&SelfEquipWindow::handle_MouseLeave, this));

		}
	}

	
	_sceneMgr = Ogre::Root::getSingletonPtr()->createSceneManger(std::string("SelfEquip"));
	Ogre::Camera* cam = _sceneMgr->createCamera("SelfEquip");



	CEGUI::Window* backgroud = SelfEquip_Board_Background->getChildRecursive("background");
	float width = 206;
	float height = 300;

	TextureProperty texProperty;
	texProperty._tex_usage = TU_RENDERTARGET;
	texProperty._width = width;
	texProperty._height = height;


	texProperty._backgroudColor.a = 0.0f;
	TexturePtr renderTexture =
		TextureManager::getSingleton().createManual("RenderToTexture", texProperty);

	Ogre::RenderTarget* textureTarget = renderTexture->getBuffer()->getRenderTarget(0);

	Viewport* rv = textureTarget->addViewport(cam);

	cam->setAspectRatio(width / height);

	auto camera = new GameCamera(cam, _sceneMgr);
	camera->setDistance(270);

	camera->update(0.0f);
	//DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Gold;
	rv->setBackgroundColour(texProperty._backgroudColor);



	CEGUI::ImageManager::getSingleton().addRenderTarget("RenderToTexture");
	backgroud->setProperty("Image", "RenderToTexture");
}

bool SelfEquipWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);

	CEGUI::Window* current = dd_args.window;
	if (current == _close)
	{
		_main_window->hide();
	}
	else if (current == _turn_left)
	{
		mDir -= 0.1f;
		KPlayer* player = UIManager::GetSingleton().getUIPlayer();
		player->getMainEntity()->setDirection(mDir);


	}
	else if (current == _turn_right)
	{
		mDir += 0.1f;
		KPlayer* player = UIManager::GetSingleton().getUIPlayer();
		player->getMainEntity()->setDirection(mDir);
	}
	return true;
}

bool SelfEquipWindow::handle_EquipClick(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);

	uint32_t index = (uint32_t)dd_args.window->getUserData();

	if (_equips[index])
	{
		clientmessage::MsgTakeDownEquip msg;

		KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();
		msg.set_player_id(pPlayer->getId());
		msg.set_map_id(GameSceneManager::getSingleton().getActiveSceneId());
		msg.set_equip_point(index);
		msg.set_bag_index(-1);

		NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_UNEQUIP, &msg);
	}
	return true;
}

bool SelfEquipWindow::handle_MouseEnter(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& dd_args =
		static_cast<const CEGUI::MouseEventArgs&>(args);
	int32_t value = (int32_t)dd_args.window->getUserData();
	value -= 1;

	if (value >= 0)
	{
		GameToolTip* tip = CEGUIManager::getSingleton().getToolTip();
		auto& equips = GameDataManager::GetSingleton().getUserEquip();
		tip->update(equips[value]);
	}
	return true;
}

bool SelfEquipWindow::handle_MouseLeave(const CEGUI::EventArgs& args)
{

	return true;
}

void SelfEquipWindow::update()
{
	auto& equips = GameDataManager::GetSingleton().getUserEquip();

	KPlayer* myself = KObjectManager::GetSingleton().getMySelf();
	if (myself)
	{
		KCharatcterBaseData* pMyselfData = myself->GetCharacterData();

		for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
		{
			KItem* item = equips[i];
			uint32_t item_id = 0;
			if (item)
			{
				item_id = item->GetIdTable();
			}

			
			updateItem(i, item_id);

		}
	}
	KPlayer* uiPlayer = UIManager::GetSingleton().getUIPlayer();
	GameEntity* main = uiPlayer->getMainEntity();
	Orphigine::SkeletonMeshActor* actor = main->getSkeletonMeshActor();
	Ogre::Vector3 pos = Ogre::Vector3(10.0, -100.0f, 0.0f);
	actor->setPosition(pos);
	actor->setSceneManager(_sceneMgr);
}

bool SelfEquipWindow::updateItem(
	uint32_t index,
	uint32_t itemId)
{
	ItemData itemInfo;
	if (index == 0)
	{
		//item_id = 10010010;
		itemId = itemId;
	}
	if (getItemInfo(itemId, itemInfo))
	{
		const char* fullname = CEGUIManager::getSingleton().getFullIconName(itemInfo.icon);

		_equips[index]->setProperty("Image", fullname);
	}
	else
	{
		if(_equips[index])
		_equips[index]->setProperty("Image", "");
	}

	



	return true;
}