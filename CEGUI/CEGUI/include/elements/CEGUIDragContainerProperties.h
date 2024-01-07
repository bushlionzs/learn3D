

#ifndef _CEGUIDragContainerProperties_h_
#define _CEGUIDragContainerProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace DragContainerProperties
{
    
    class DraggingEnabled : public Property
    {
    public:
	    DraggingEnabled() : Property(
		    "DraggingEnabled",
		    "Property to get/set the state of the dragging enabled setting for the DragContainer.  Value is either \"True\" or \"False\".",
		    "True")
	    {}

	    String	get(const PropertyReceiver* receiver) const;
	    void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class DragAlpha : public Property
    {
    public:
	    DragAlpha() : Property(
		    "DragAlpha",
		    "Property to get/set the dragging alpha value.  Value is a float.",
		    "0.500000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class DragThreshold : public Property
    {
    public:
	    DragThreshold() : Property(
		    "DragThreshold",
		    "Property to get/set the dragging threshold value.  Value is a float.",
		    "8.000000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class DragCursorImage : public Property
    {
    public:
	    DragCursorImage() : Property(
		    "DragCursorImage",
		    "Property to get/set the mouse cursor image used when dragging.  Value should be \"set:<imageset name> image:<image name>\".",
		    "")
	    {}

	    String	get(const PropertyReceiver* receiver) const;
	    void	set(PropertyReceiver* receiver, const String& value);
    };

} 
} 

#endif	
