#include "OgreHeader.h"
#include "application_base.h"
#include "fulldemo.h"
#include "platform_log.h"
#include "SimpleApp.h"

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
		FullDemo app;
		app.appInit();
		app.run();
	}
	

	return 0;
}

