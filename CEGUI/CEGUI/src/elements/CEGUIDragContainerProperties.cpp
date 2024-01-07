

#include "elements/CEGUIDragContainerProperties.h"
#include "elements/CEGUIDragContainer.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace DragContainerProperties
{
    String DraggingEnabled::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::boolToString(static_cast<const DragContainer*>(receiver)->isDraggingEnabled());
    }

    void DraggingEnabled::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<DragContainer*>(receiver)->setDraggingEnabled(PropertyHelper::stringToBool(value));
    }

    
    
    String DragAlpha::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const DragContainer*>(receiver)->getDragAlpha());
    }

    void DragAlpha::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<DragContainer*>(receiver)->setDragAlpha(PropertyHelper::stringToFloat(value));
    }

    

    String DragThreshold::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const DragContainer*>(receiver)->getPixelDragThreshold());
    }

    void DragThreshold::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<DragContainer*>(receiver)->setPixelDragThreshold(PropertyHelper::stringToFloat(value));
    }

    

    String DragCursorImage::get(const PropertyReceiver* receiver) const
    {
        const Image* img = static_cast<const DragContainer*>(receiver)->getDragCursorImage();
        return img ? PropertyHelper::imageToString(img) : String();
    }

    void DragCursorImage::set(PropertyReceiver* receiver, const String& value)
    {
        if (!value.empty())
        {
            static_cast<DragContainer*>(receiver)->setDragCursorImage(PropertyHelper::stringToImage(value));
        }
    }

} 


} 
