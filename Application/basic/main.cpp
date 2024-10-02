#include "OgreHeader.h"
#include "application_base.h"
#include "basic.h"
#include "platform_log.h"
#include "SimpleApp.h"

int main()
{
	platform_log_init();
	bool usefilament = false;

	
	Basic app;
	app.appInit();
	app.run();
	
	
	

	return 0;
}

