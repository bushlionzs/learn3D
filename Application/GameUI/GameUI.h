#pragma once
#include "OgreAnimationState.h"
#include <CEGUI/WindowManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
//#include <CEGUI/ImagesetManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/ImageManager.h>
#include <DefaultWindow.h>
#include <FrameWindow.h>
#include <CEGUIManager.h>

#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
class Role;
class GameUI : public InputListener
{
public:
	GameUI();
	~GameUI();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	
	virtual bool isUseCEGUI()
	{
		return true;
	}

	void setup(
		RenderPipeline* renderPipeline,
		RenderContext& context,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
private:
	void helloDemo();
	virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	void HelloDemo1();
	void TooltipDemo();
	void DragDropDemo();
	void subscribeEvents();
	bool handle_ItemDropped(const CEGUI::EventArgs& args);
	bool handle_PackageItemDropped(const CEGUI::EventArgs& args);
	bool handle_ToolTip(const CEGUI::EventArgs& args);
	bool handle_MouseEnter(const CEGUI::EventArgs& args);
	bool handle_MouseLeave(const CEGUI::EventArgs& args);
	bool handle_ButtonClick(const CEGUI::EventArgs& args);
	virtual void injectKeyRelease(KeyCode _key);
	void SelfEquipDemo();
	void PackageDemo();
	void MultiDemo();
	void ToolTipDemo();
	void MainMenuDemo();
	void QuestDemo();
	void PbrDemo();
private:
	Ogre::AnimationState* mAnimationState = nullptr;
	Role* mRole;
	CEGUI::GUIContext* mGUIContext = nullptr;

	CEGUI::Window* mRoot = nullptr;
	CEGUI::Tooltip* mToolTip = nullptr;
	CEGUI::Window* mSelfEquip = nullptr;

	GameCamera* mUICamera = nullptr;
};