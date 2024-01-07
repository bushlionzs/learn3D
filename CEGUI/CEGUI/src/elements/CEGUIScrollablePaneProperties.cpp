

#include "elements/CEGUIScrollablePaneProperties.h"
#include "elements/CEGUIScrollablePane.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace ScrollablePaneProperties
{
    String ContentPaneAutoSized::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const ScrollablePane*>(receiver)->isContentPaneAutoSized());
    }

    void ContentPaneAutoSized::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setContentPaneAutoSized(PropertyHelper::stringToBool(value));
    }

    

    String ContentArea::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::rectToString(static_cast<const ScrollablePane*>(receiver)->getContentPaneArea());
    }

    void ContentArea::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setContentPaneArea(PropertyHelper::stringToRect(value));
    }

    

    String ForceVertScrollbar::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const ScrollablePane*>(receiver)->isVertScrollbarAlwaysShown());
    }

    void ForceVertScrollbar::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setShowVertScrollbar(PropertyHelper::stringToBool(value));
    }

    

    String ForceHorzScrollbar::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const ScrollablePane*>(receiver)->isHorzScrollbarAlwaysShown());
    }

    void ForceHorzScrollbar::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setShowHorzScrollbar(PropertyHelper::stringToBool(value));
    }

    
    
    String HorzStepSize::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalStepSize());
    }

    void HorzStepSize::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setHorizontalStepSize(PropertyHelper::stringToFloat(value));
    }

    

    String HorzOverlapSize::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalOverlapSize());
    }

    void HorzOverlapSize::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setHorizontalOverlapSize(PropertyHelper::stringToFloat(value));
    }

    

    String HorzScrollPosition::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalScrollPosition());
    }

    void HorzScrollPosition::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setHorizontalScrollPosition(PropertyHelper::stringToFloat(value));
    }

    

    String VertStepSize::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalStepSize());
    }

    void VertStepSize::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setVerticalStepSize(PropertyHelper::stringToFloat(value));
    }

    

    String VertOverlapSize::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalOverlapSize());
    }

    void VertOverlapSize::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setVerticalOverlapSize(PropertyHelper::stringToFloat(value));
    }

    

    String VertScrollPosition::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const ScrollablePane*>(receiver)->getHorizontalScrollPosition());
    }

    void VertScrollPosition::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrollablePane*>(receiver)->setVerticalScrollPosition(PropertyHelper::stringToFloat(value));
    }

} 
} 
