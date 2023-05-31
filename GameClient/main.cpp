#include "OgreHeader.h"
#include "application_base.h"
#include "fulldemo.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	FullDemo app;
	app.appInit();
	app.run();

	return 0;
}

