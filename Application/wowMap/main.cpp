#include "OgreHeader.h"
#include "application_base.h"
#include "wowMap.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	//return m2_test();
	CoInitialize(NULL);
	WowMap app;
	app.appInit();
	app.run();

	return 0;
}

