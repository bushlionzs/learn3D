#include "OgreHeader.h"
#include "application_base.h"
#include "AnimTexture.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	AnimTexture app;
	app.appInit();
	app.run();

	return 0;
}

