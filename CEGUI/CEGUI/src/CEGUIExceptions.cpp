

#include "CEGUIExceptions.h"
#include "CEGUILogger.h"


namespace CEGUI
{

Exception::Exception(const String& message) :
	d_message(message)
{
	Logger::getSingleton().logEvent((utf8*)"Exception: " + message, Errors);
}

Exception::~Exception(void)
{
}

} 
