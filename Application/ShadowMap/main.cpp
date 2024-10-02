#include "OgreHeader.h"
#include "application_base.h"
#include "ShadowMap.h"
#include "platform_log.h"
#include "SimpleApp.h"

int main()
{
	platform_log_init();
	bool usefilament = true;

	if (usefilament)
	{
		SimpleApp app;
		auto setup = [&app](Engine* engine) {
			};
		auto cleanup = [&app](Engine* engine) {
			};
		app.run(setup, cleanup);
	}
	else
	{
		ShadowMap app;
		app.appInit();
		app.run();
	}

	return 0;
}

