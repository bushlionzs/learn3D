#include "OgreHeader.h"
#include "application_base.h"
#include "PbrMaterial.h"
#include "platform_log.h"
#include <iostream>
#include <string>
#include <format>
int main()
{
	platform_log_init();
	CoInitialize(NULL);
	PbrMaterial app;
	app.appInit();
	app.run();

	return 0;
}

