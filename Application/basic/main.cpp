#include "OgreHeader.h"
#include "application_base.h"
#include "basic.h"
#include "platform_log.h"
#include "SimpleApp.h"
#include <backend/Engine.h>

using namespace filament;
using namespace filament::backend;

int main()
{
	platform_log_init();

	CoInitialize(NULL);
	/*Basic app;
	app.appInit();
	app.run();*/

	SimpleApp app;

	auto setup = [&app](Engine* engine) {
		};
	auto cleanup = [&app](Engine* engine) {
		};
	app.run(setup, cleanup);
	return 0;
}

