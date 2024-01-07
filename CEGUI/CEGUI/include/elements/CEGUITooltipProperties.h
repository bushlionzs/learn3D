

#ifndef _CEGUITooltipProperties_h_
#define _CEGUITooltipProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{


namespace TooltipProperties
{
    
    class HoverTime : public Property
    {
    public:
        HoverTime() : Property(
            "HoverTime",
            "Property to get/set the hover timeout value in seconds.  Value is a float.",
            "0.400000")
        {}

        String  get(const PropertyReceiver* receiver) const;
        void    set(PropertyReceiver* receiver, const String& value);
    };

    
    class DisplayTime : public Property
    {
    public:
        DisplayTime() : Property(
            "DisplayTime",
            "Property to get/set the display timeout value in seconds.  Value is a float.",
            "7.500000")
        {}

        String  get(const PropertyReceiver* receiver) const;
        void    set(PropertyReceiver* receiver, const String& value);
    };

    
    class FadeTime : public Property
    {
    public:
        FadeTime() : Property(
            "FadeTime",
            "Property to get/set duration of the fade effect in seconds.  Value is a float.",
            "0.330000")
        {}

        String  get(const PropertyReceiver* receiver) const;
        void    set(PropertyReceiver* receiver, const String& value);
    };

    
    class MaxWidth : public Property
    {
    public:
        MaxWidth() : Property(
            "MaxWidth",
            "",
            "200")
        {}

        String  get(const PropertyReceiver* receiver) const;
        void    set(PropertyReceiver* receiver, const String& value);
    };
} 
} 


#endif	
