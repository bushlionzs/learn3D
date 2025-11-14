#include "OgreHeader.h"
#include "ManualApplication.h"
#include "videoTexture.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	VideoTextureApplication instance;
	AppInfo info;
	info.useSRGB = false;
	info.engineType = EngineType_Vulkan;
	info.engineType = EngineType_Dx12;
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

