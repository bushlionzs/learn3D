#include "OgreHeader.h"
#include "basic.h"
#include "platform_log.h"
#include "ManualApplication.h"
#include <time_util.h>
int main()
{
	static const char _compute_code[] = {
R"<!>(abc)<!>"
	};
	printf("%s\n", _compute_code);
	platform_log_init();
	BasicApplication instance;
	AppInfo info;
	info.useSRGB = false;
	info.engineType = EngineType_Vulkan;
	info.engineType = EngineType_Dx12;
	ManualApplication app;
	
	

	info.setup = [&instance, &app](RenderSystem* rs, Ogre::RenderWindow* win, Ogre::SceneManager* sceneManager, GameCamera* gameCamera) {
		instance.setup(&app, rs, win, sceneManager, gameCamera);
		};

	info.update = [&instance](float delta) {
		instance.update(delta);
		};
	info.cleanup = [&instance]() {
		};

	app.run(info);

	return 0;
}

