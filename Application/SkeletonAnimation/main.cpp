#include "OgreHeader.h"
#include "application_base.h"
#include "SkeletonAnimation.h"
#include "platform_log.h"

int main()
{
	platform_log_init();
	CoInitialize(NULL);
	SkeletonAnimation app;
	app.appInit();
	app.run();

	return 0;
}

