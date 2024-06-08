#include "OgreHeader.h"
#include "application_base.h"
#include "fulldemo.h"
#include "platform_log.h"
#include "platform_util.h"

int main()
{
	platform_log_init(nullptr, "GameClient");
	platform_timer_init();
	CoInitialize(NULL);
	FullDemo app;
	app.appInit();
	app.run();

	return 0;
}

