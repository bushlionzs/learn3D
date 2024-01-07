

#include "elements/CEGUITooltipProperties.h"
#include "elements/CEGUITooltip.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace TooltipProperties
{
    String HoverTime::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Tooltip*>(receiver)->getHoverTime());
    }

    void HoverTime::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Tooltip*>(receiver)->setHoverTime(PropertyHelper::stringToFloat(value));
    }

    

    String DisplayTime::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Tooltip*>(receiver)->getDisplayTime());
    }

    void DisplayTime::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Tooltip*>(receiver)->setDisplayTime(PropertyHelper::stringToFloat(value));
    }

    

    String FadeTime::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Tooltip*>(receiver)->getFadeTime());
    }

    void FadeTime::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Tooltip*>(receiver)->setFadeTime(PropertyHelper::stringToFloat(value));
    }

    

    String MaxWidth::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::intToString(static_cast<const Tooltip*>(receiver)->getMaxWidth());
    }

    void MaxWidth::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Tooltip*>(receiver)->setMaxWidth(PropertyHelper::stringToInt(value));
    }

} 
} 
