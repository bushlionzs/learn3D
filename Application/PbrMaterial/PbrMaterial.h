#pragma once
#include "OgreAnimationState.h"
#include <engine_struct.h>
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
#include "pass.h"

class Role;
class PbrMaterial : public InputListener
{
public:
	PbrMaterial();
	~PbrMaterial();

	void setup(
		RenderPipeline* renderPipeline,
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);


	EngineType getEngineType();

	virtual bool isUseCEGUI()
	{
		return true;
	}

	void uiInit();
	void updateRenderMode(uint32_t mode);
	void updateMaterialType(uint32_t type);
	void updateLightDirection(const Ogre::Vector3& dir);
private:
	CEGUI::GUIContext* mGUIContext = nullptr;
	CEGUI::Window* mRoot = nullptr;
	std::vector<Ogre::Entity*> matBallList;

	SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	RenderWindow* mRenderWindow;
};