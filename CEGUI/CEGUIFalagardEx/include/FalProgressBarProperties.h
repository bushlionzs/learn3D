

#ifndef _FalProgressBarProperties_h_
#define _FalProgressBarProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{


namespace FalagardProgressBarProperties
{
    
    class VerticalProgress : public Property
    {
    public:
        VerticalProgress() : Property(
            "VerticalProgress",
            "Property to get/set whether the ProgressBar operates in the vertical direction.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class ReversedProgress : public Property
    {
    public:
        ReversedProgress() : Property(
            "ReversedProgress",
            "Property to get/set whether the ProgressBar operates in reversed direction.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

}

} 


#endif  
