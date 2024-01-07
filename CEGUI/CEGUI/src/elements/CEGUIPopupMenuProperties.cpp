

#include "elements/CEGUIPopupMenuProperties.h"
#include "elements/CEGUIPopupMenu.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace PopupMenuProperties
{

String FadeInTime::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const PopupMenu*>(receiver)->getFadeInTime());
}

void FadeInTime::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<PopupMenu*>(receiver)->setFadeInTime(PropertyHelper::stringToFloat(value));
}



String FadeOutTime::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::floatToString(static_cast<const PopupMenu*>(receiver)->getFadeOutTime());
}

void FadeOutTime::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<PopupMenu*>(receiver)->setFadeOutTime(PropertyHelper::stringToFloat(value));
}

} 
} 
