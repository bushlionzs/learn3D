#include "OgreHeader.h"
#include "application_base.h"
#include "RenderToTexture.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	RenderToTexture app;
	app.appInit();
	app.run();

	return 0;
}

