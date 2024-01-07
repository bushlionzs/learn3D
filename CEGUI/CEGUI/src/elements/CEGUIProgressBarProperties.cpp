

#include "elements/CEGUIProgressBarProperties.h"
#include "elements/CEGUIProgressBar.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace ProgressBarProperties
{
String CurrentProgress::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const ProgressBar*>(receiver)->getProgress());
}


void CurrentProgress::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ProgressBar*>(receiver)->setProgress(PropertyHelper::stringToFloat(value));
}


String StepSize::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const ProgressBar*>(receiver)->getStep());
}


void StepSize::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ProgressBar*>(receiver)->setStepSize(PropertyHelper::stringToFloat(value));
}

} 

} 
