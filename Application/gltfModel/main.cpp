#include "OgreHeader.h"
#include "application_base.h"
#include "gltfModel.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	gltfModel app;
	app.appInit();
	app.run();

	return 0;
}

