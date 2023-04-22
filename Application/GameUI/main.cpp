#include "OgreHeader.h"
#include "application_base.h"
#include "GameUI.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	GameUI app;
	app.appInit();
	app.run();

	return 0;
}

