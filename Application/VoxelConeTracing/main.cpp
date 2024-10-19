#include "OgreHeader.h"
#include "VoxelConeTracing.h"
#include "platform_log.h"
#include "ManualApplication.h"
int main()
{
	VoxelConeTracingApp instance;

	AppInfo info;

	info.setup = [&instance](RenderSystem* rs, Ogre::RenderWindow* win, Ogre::SceneManager* sceneManager, GameCamera* gameCamera) {
		instance.setup(rs, win, sceneManager, gameCamera);
		};

	info.update = [&instance](float delta) {
		instance.update(delta);
		};
	info.cleanup = [&instance]() {
		};
	
	ManualApplication app;
	info.pass = [&instance, &app](std::vector<PassBase*>& passlist) {
		instance.updatePass(passlist);
		};
	app.run(info);
	

	return 0;
}

