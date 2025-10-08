#include "OgreHeader.h"
#include "ManualApplication.h"
#include "GameUI.h"
#include "platform_log.h"
#include <iostream>
#include <string>
#include <format>
int main()
{
	platform_log_init();
	BasicApplication instance;
	AppInfo info;
	info.useSRGB = false;
	info.engineType = EngineType_Vulkan;
	//info.engineType = EngineType_Dx12;
	ManualApplication app;



	info.setup = [&instance, &app](RenderContext& context, Ogre::RenderWindow* win, Ogre::SceneManager* sceneManager, GameCamera* gameCamera) {
		instance.setup(&app, context, win, sceneManager, gameCamera);
		};

	info.update = [&instance](float delta) {
		instance.update(delta);
		};
	info.cleanup = [&instance]() {
		};

	app.run(&info);

	return 0;
}

