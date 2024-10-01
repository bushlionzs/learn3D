#include "OgreHeader.h"
#include "application_base.h"
#include "basic.h"
#include "platform_log.h"

int main()
{
	printf("1\n");
	platform_log_init();
	printf("2\n");
	Basic app;
	app.appInit();
	app.run();
	

	return 0;
}

