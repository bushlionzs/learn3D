

#include "elements/CEGUIRadioButtonProperties.h"
#include "elements/CEGUIRadioButton.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{


namespace RadioButtonProperties
{
String Selected::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const RadioButton*>(receiver)->isSelected());
}


void Selected::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<RadioButton*>(receiver)->setSelected(PropertyHelper::stringToBool(value));
}


String GroupID::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<const RadioButton*>(receiver)->getGroupID());
}


void GroupID::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<RadioButton*>(receiver)->setGroupID(PropertyHelper::stringToUint(value));
}


} 

} 
