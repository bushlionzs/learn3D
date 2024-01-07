

#include "elements/CEGUIMenuItemProperties.h"
#include "elements/CEGUIMenuItem.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace MenuItemProperties
{


String HoverColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MenuItem*>(receiver)->getHoverColour());
}

void HoverColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuItem*>(receiver)->setHoverColour(PropertyHelper::stringToColour(value));
}




String PushedColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MenuItem*>(receiver)->getPushedColour());
}

void PushedColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuItem*>(receiver)->setPushedColour(PropertyHelper::stringToColour(value));
}




String OpenedColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MenuItem*>(receiver)->getOpenedColour());
}

void OpenedColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuItem*>(receiver)->setOpenedColour(PropertyHelper::stringToColour(value));
}




String NormalTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MenuItem*>(receiver)->getNormalTextColour());
}

void NormalTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuItem*>(receiver)->setNormalTextColour(PropertyHelper::stringToColour(value));
}




String DisabledTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MenuItem*>(receiver)->getDisabledTextColour());
}

void DisabledTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuItem*>(receiver)->setDisabledTextColour(PropertyHelper::stringToColour(value));
}


} 
} 
