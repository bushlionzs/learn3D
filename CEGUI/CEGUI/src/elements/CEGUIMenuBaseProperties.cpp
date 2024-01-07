

#include "elements/CEGUIMenuBaseProperties.h"
#include "elements/CEGUIMenuBase.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace MenuBaseProperties
{

String ItemSpacing::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const MenuBase*>(receiver)->getItemSpacing());
}

void ItemSpacing::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuBase*>(receiver)->setItemSpacing(PropertyHelper::stringToFloat(value));
}


String HorzPadding::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const MenuBase*>(receiver)->getHorzPadding());
}

void HorzPadding::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuBase*>(receiver)->setHorzPadding(PropertyHelper::stringToFloat(value));
}


String VertPadding::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const MenuBase*>(receiver)->getVertPadding());
}

void VertPadding::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuBase*>(receiver)->setVertPadding(PropertyHelper::stringToFloat(value));
}


String BorderWidth::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const MenuBase*>(receiver)->getBorderWidth());
}

void BorderWidth::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuBase*>(receiver)->setBorderWidth(PropertyHelper::stringToFloat(value));
}


String BackgroundColours::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourRectToString(static_cast<const MenuBase*>(receiver)->getBackgroundColours());
}

void BackgroundColours::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MenuBase*>(receiver)->setBackgroundColours(PropertyHelper::stringToColourRect(value));
}

String AllowMultiplePopups::get(const PropertyReceiver* receiver) const
{
    return PropertyHelper::boolToString(static_cast<const MenuBase*>(receiver)->isMultiplePopupsAllowed());
}

void AllowMultiplePopups::set(PropertyReceiver* receiver, const String& value)
{
    static_cast<MenuBase*>(receiver)->setAllowMultiplePopups(PropertyHelper::stringToBool(value));
}

} 
} 
