#include "OgreHeader.h"
#include "basic.h"
#include "platform_log.h"
#include "ManualApplication.h"
#include <atomic>
int main2()
{
	platform_log_init();
	ManualApplication app;
	BasicApplication instance(&app);

	AppInfo info;
	info.useSRGB = false;
	info.engineType = EngineType_Vulkan;
	//info.engineType = EngineType_Dx12;
	
	info.userRunCallback = [&instance](AppInfo* info)
		{
			instance.userInit(info);
		};

	info.setup = [&instance, &app](
		RenderContext& context,
		Ogre::RenderWindow* win, 
		Ogre::SceneManager* sceneManager, 
		GameCamera* gameCamera) {
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

