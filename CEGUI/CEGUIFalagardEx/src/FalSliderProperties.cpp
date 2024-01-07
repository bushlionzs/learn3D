

#include "FalSliderProperties.h"
#include "FalSlider.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace FalagardSliderProperties
{
    String VerticalSlider::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const FalagardSlider*>(receiver)->isVertical());
    }

    void VerticalSlider::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<FalagardSlider*>(receiver)->setVertical(PropertyHelper::stringToBool(value));
    }


    String ReversedDirection::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const FalagardSlider*>(receiver)->isReversedDirection());
    }

    void ReversedDirection::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<FalagardSlider*>(receiver)->setReversedDirection(PropertyHelper::stringToBool(value));
    }

}
} 
