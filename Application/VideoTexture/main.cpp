#include "OgreHeader.h"
#include "application_base.h"
#include "videoTexture.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	VideoTexture app;
	app.appInit();
	app.run();

	return 0;
}

