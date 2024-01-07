

#include "elements/CEGUIListboxProperties.h"
#include "elements/CEGUIListbox.h"
#include "CEGUIPropertyHelper.h"



namespace CEGUI
{


namespace ListboxProperties
{
String	Sort::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Listbox*>(receiver)->isSortEnabled());
}


void	Sort::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setSortingEnabled(PropertyHelper::stringToBool(value));
}


String	MultiSelect::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Listbox*>(receiver)->isMultiselectEnabled());
}


void	MultiSelect::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setMultiselectEnabled(PropertyHelper::stringToBool(value));
}


String	ForceVertScrollbar::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Listbox*>(receiver)->isVertScrollbarAlwaysShown());
}


void	ForceVertScrollbar::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setShowVertScrollbar(PropertyHelper::stringToBool(value));
}


String	ForceHorzScrollbar::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Listbox*>(receiver)->isHorzScrollbarAlwaysShown());
}


void	ForceHorzScrollbar::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setShowHorzScrollbar(PropertyHelper::stringToBool(value));
}

String	ItemTooltips::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Listbox*>(receiver)->isItemTooltipsEnabled());
}


void	ItemTooltips::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setItemTooltipsEnabled(PropertyHelper::stringToBool(value));
}

String	SelectionColour::get(const PropertyReceiver* receiver) const
{
	return "";
}


void	SelectionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Listbox*>(receiver)->setSelectionColur(PropertyHelper::stringToColour(value));
}

} 

} 
