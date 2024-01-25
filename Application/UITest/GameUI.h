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
class GameUI : public ApplicationBase
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
	void DragDropDemo();
	void subscribeEvents();
	bool handle_ItemDropped(const CEGUI::EventArgs& args);

	void PackageDemo();
private:
	AnimationState* mAnimationState = nullptr;
	Role* mRole;
	CEGUI::GUIContext* mGUIContext = nullptr;
};