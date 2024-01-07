

#include "FalScrollbarProperties.h"
#include "FalScrollbar.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace FalagardScrollbarProperties
{
    String VerticalScrollbar::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const FalagardScrollbar*>(receiver)->isVertical());
    }

    void VerticalScrollbar::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<FalagardScrollbar*>(receiver)->setVertical(PropertyHelper::stringToBool(value));
    }
}
} 
