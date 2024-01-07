

#ifndef _FalScrollbarProperties_h_
#define _FalScrollbarProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardScrollbarProperties
{
    
    class VerticalScrollbar : public Property
    {
    public:
        VerticalScrollbar() : Property(
            "VerticalScrollbar",
            "Property to get/set whether the Scrollbar operates in the vertical direction.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

}

} 


#endif  
