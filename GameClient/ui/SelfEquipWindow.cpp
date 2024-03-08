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

SelfEquipWindow::SelfEquipWindow(CEGUI::Window* parent)
{
	_main_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("SelfEquip.xml");
	parent->addChild(_main_window);
	_main_window->setVisible(false);
	auto* close = _main_window->getChildRecursive("Packet_Close");
	close->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&SelfEquipWindow::handle_ButtonClick, this));

	CEGUI::Window* SelfEquip_Board_Background = _main_window->getChild("SelfEquip_Board_Background");

	_equips.resize(HEQUIP_NUMBER);

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
			equip->setUserData((void*)i);
			equip->subscribeEvent(
				CEGUI::Window::EventMouseClick,
				CEGUI::Event::Subscriber(&SelfEquipWindow::handle_EquipClick, this));
		}
	}

	SceneManager* sceneMgr = Ogre::Root::getSingletonPtr()->createSceneManger(std::string("SelfEquip"));
	Ogre::Camera* cam = sceneMgr->createCamera("SelfEquip");
	auto mRole = new Role(sceneMgr);
	mRole->createRoleData();
	auto rolepos = Ogre::Vector3(0.0, -100.0f, 0.0f);
	mRole->setPosition(rolepos);
	mRole->walk();

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

	auto camera = new GameCamera(cam, sceneMgr);
	camera->setDistance(270);

	camera->update(0.0f);
	//DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Gold;
	rv->setBackgroundColour(texProperty._backgroudColor);



	CEGUI::ImageManager::getSingleton().addRenderTarget("RenderToTexture");
	backgroud->setProperty("Image", "RenderToTexture");
}

bool SelfEquipWindow::handle_ButtonClick(const CEGUI::EventArgs& args)
{
	_main_window->hide();
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

void SelfEquipWindow::update()
{
	auto& equips = GameDataManager::GetSingleton().getUserEquip();


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

bool SelfEquipWindow::updateItem(
	uint32_t index,
	uint32_t itemId)
{
	ItemData itemInfo;

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