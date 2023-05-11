#include "OgreHeader.h"
#include "application_base.h"
#include "particle_demo.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	//return m2_test();
	CoInitialize(NULL);
	ParticleDemo app;
	app.appInit();
	app.run();

	return 0;
}

