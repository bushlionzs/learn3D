#include "OgreHeader.h"
#include "application_base.h"
#include "basic.h"
#include "platform_log.h"
#include "SimpleApp.h"
#include <filament/Engine.h>

using namespace filament;
using namespace filament::backend;
using namespace CEGUI;
int main()
{
	platform_log_init();

	bool use_filament = true;

	if (use_filament)
	{
		SimpleApp app;
		auto setup = [&app](Engine* engine) {
			engine->getJobSystem();

			};
		auto cleanup = [&app](Engine* engine) {
			};
		app.run(setup, cleanup);
	}
	else
	{
		Basic app;
		app.appInit();
		app.run();
	}
	

	

	
	return 0;
}

