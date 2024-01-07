

#ifndef _FalSliderProperties_h_
#define _FalSliderProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{

namespace FalagardSliderProperties
{
    
    class VerticalSlider : public Property
    {
    public:
        VerticalSlider() : Property(
            "VerticalSlider",
            "Property to get/set whether the Slider operates in the vertical direction.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class ReversedDirection : public Property
    {
    public:
        ReversedDirection() : Property(
            "ReversedDirection",
            "Property to get/set whether the Slider operates in reversed direction.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };
}

} 


#endif  
