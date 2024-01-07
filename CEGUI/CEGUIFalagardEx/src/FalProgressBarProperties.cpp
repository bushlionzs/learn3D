

#include "FalProgressBarProperties.h"
#include "FalProgressBar.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace FalagardProgressBarProperties
{
    String VerticalProgress::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const FalagardProgressBar*>(receiver)->isVertical());
    }

    void VerticalProgress::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<FalagardProgressBar*>(receiver)->setVertical(PropertyHelper::stringToBool(value));
    }

    String ReversedProgress::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const FalagardProgressBar*>(receiver)->isReversed());
    }

    void ReversedProgress::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<FalagardProgressBar*>(receiver)->setReversed(PropertyHelper::stringToBool(value));
    }
}

} 
