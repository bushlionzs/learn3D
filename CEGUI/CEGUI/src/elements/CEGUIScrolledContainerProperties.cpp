

#include "elements/CEGUIScrolledContainerProperties.h"
#include "elements/CEGUIScrolledContainer.h"
#include "CEGUILogger.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace ScrolledContainerProperties
{
    String ContentPaneAutoSized::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const ScrolledContainer*>(receiver)->isContentPaneAutoSized());
    }

    void ContentPaneAutoSized::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrolledContainer*>(receiver)->setContentPaneAutoSized(PropertyHelper::stringToBool(value));
    }

    
    
    String ContentArea::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::rectToString(static_cast<const ScrolledContainer*>(receiver)->getContentArea());
    }

    void ContentArea::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<ScrolledContainer*>(receiver)->setContentArea(PropertyHelper::stringToRect(value));
    }

    

    String ChildExtentsArea::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::rectToString(static_cast<const ScrolledContainer*>(receiver)->getChildExtentsArea());
    }

    void ChildExtentsArea::set(PropertyReceiver* receiver, const String& value)
    {
        Logger::getSingleton().logEvent("ScrolledContainerProperties::ChildExtentsArea property does not support being set.", Errors);        
    }

} 
} 
