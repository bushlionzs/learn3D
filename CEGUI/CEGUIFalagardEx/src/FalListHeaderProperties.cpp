

#include "FalListHeaderProperties.h"
#include "FalListHeader.h"


namespace CEGUI
{
namespace FalagardListHeaderProperties
{
String SegmentWidgetType::get(const PropertyReceiver* receiver) const
{
    return static_cast<const FalagardListHeader*>(receiver)->getSegmentWidgetType();
}

void SegmentWidgetType::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FalagardListHeader*>(receiver)->setSegmentWidgetType(value);
}

}

} 
