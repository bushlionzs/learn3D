#pragma once
#include "application_base.h"
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
class Role;
class GameUI : public ApplicationBase, public InputListener
{
public:
	GameUI();
	~GameUI();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
	virtual bool isUseMyGUI()
	{
		return false;
	}

	virtual bool isUseCEGUI()
	{
		return true;
	}
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
private:
	AnimationState* mAnimationState = nullptr;
	Role* mRole;
	CEGUI::GUIContext* mGUIContext = nullptr;

	CEGUI::Window* mRoot = nullptr;
	CEGUI::Tooltip* mToolTip = nullptr;
	CEGUI::Window* mSelfEquip = nullptr;

	GameCamera* mUICamera = nullptr;
};