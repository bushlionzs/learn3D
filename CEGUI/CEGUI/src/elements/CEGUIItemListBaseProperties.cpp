

#include "elements/CEGUIItemListBaseProperties.h"
#include "elements/CEGUIItemListBase.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace ItemListBaseProperties
{
    String AutoResizeEnabled::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const ItemListBase*>(receiver)->isAutoResizeEnabled());
    }

    void AutoResizeEnabled::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ItemListBase*>(receiver)->setAutoResizeEnabled(PropertyHelper::stringToBool(value));
    }

} 


} 
