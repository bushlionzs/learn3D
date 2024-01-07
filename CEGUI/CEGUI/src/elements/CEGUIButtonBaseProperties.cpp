

#include "elements/CEGUIButtonBaseProperties.h"
#include "elements/CEGUIButtonBase.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include <cstdlib>
#include <cstdio>



namespace CEGUI
{

namespace ButtonBaseProperties
{

String NormalTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const ButtonBase*>(receiver)->getNormalTextColour());
}


void NormalTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ButtonBase*>(receiver)->setNormalTextColour(PropertyHelper::stringToColour(value));
}


String	HoverTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const ButtonBase*>(receiver)->getHoverTextColour());
}


void	HoverTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ButtonBase*>(receiver)->setHoverTextColour(PropertyHelper::stringToColour(value));
}


String	PushedTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const ButtonBase*>(receiver)->getPushedTextColour());
}


void	PushedTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ButtonBase*>(receiver)->setPushedTextColour(PropertyHelper::stringToColour(value));
}


String DisabledTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const ButtonBase*>(receiver)->getDisabledTextColour());
}


void DisabledTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<ButtonBase*>(receiver)->setDisabledTextColour(PropertyHelper::stringToColour(value));
}


} 

} 
