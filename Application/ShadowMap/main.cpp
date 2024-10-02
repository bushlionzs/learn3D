#include "OgreHeader.h"
#include "application_base.h"
#include "ShadowMap.h"
#include "platform_log.h"
#include "SimpleApp.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"

int main()
{
	platform_log_init();

	ShadowMap instance;
	SimpleApp app;
	SimpleApp::AppInfo info;

	info.setup = [&instance](RenderSystem* rs, Ogre::SceneManager* sceneManager, GameCamera* gameCamera) {
		instance.setup(rs, sceneManager, gameCamera);
		};
	info.update = [&instance](float delta) {
		instance.update(delta);
	};
	info.cleanup = [&instance]() {
		};
	app.run(info);
	return 0;
}

