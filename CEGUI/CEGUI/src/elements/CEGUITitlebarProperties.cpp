

#include "elements/CEGUITitlebarProperties.h"
#include "elements/CEGUITitlebar.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace TitlebarProperties
{
String DraggingEnabled::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Titlebar*>(receiver)->isDraggingEnabled());
}


void DraggingEnabled::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Titlebar*>(receiver)->setDraggingEnabled(PropertyHelper::stringToBool(value));
}


String CaptionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const Titlebar*>(receiver)->getCaptionColour());
}

void CaptionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Titlebar*>(receiver)->setCaptionColour(PropertyHelper::stringToColour(value));
}

} 

} 
