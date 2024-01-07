

#ifndef _FalMultiLineEditboxProperties_h_
#define _FalMultiLineEditboxProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardMultiLineEditboxProperties
{
    
    class SelectionBrushImage : public Property
    {
    public:
    SelectionBrushImage() : Property(
        "SelectionBrushImage",
        "Property to get/set the selection brush image for the editbox.  Value should be \"set:[imageset name] image:[image name]\".",
        "")
    {}

    String   get(const PropertyReceiver* receiver) const;
    void   set(PropertyReceiver* receiver, const String& value);
    };

}

} 

#endif  
