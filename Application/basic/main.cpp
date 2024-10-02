#include "OgreHeader.h"
#include "application_base.h"
#include "basic.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	Basic app;
	app.appInit();
	app.run();
	

	return 0;
}

