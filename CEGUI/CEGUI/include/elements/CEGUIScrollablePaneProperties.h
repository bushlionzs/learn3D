

#ifndef _CEGUIScrollablePaneProperties_h_
#define _CEGUIScrollablePaneProperties_h_

#include "CEGUIProperty.h"


namespace CEGUI
{


namespace ScrollablePaneProperties
{
    
    class ContentPaneAutoSized : public Property
    {
    public:
        ContentPaneAutoSized() : Property(
            "ContentPaneAutoSized",
            "Property to get/set the setting which controls whether the content pane will auto-size itself.  Value is either \"True\" or \"False\".",
            "True")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class ContentArea : public Property
    {
    public:
        ContentArea() : Property(
            "ContentArea",
            "Property to get/set the current content area rectangle of the content pane.  Value is \"l:[float] t:[float] r:[float] b:[float]\" (where l is left, t is top, r is right, and b is bottom).",
            "l:0.000000 t:0.000000 r:0.000000 b:0.000000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class ForceVertScrollbar : public Property
    {
    public:
        ForceVertScrollbar() : Property(
            "ForceVertScrollbar",
            "Property to get/set the setting which controls whether the vertical scroll bar is aways shown.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };


    
    class ForceHorzScrollbar : public Property
    {
    public:
        ForceHorzScrollbar() : Property(
            "ForceHorzScrollbar",
            "Property to get/set the setting which controls whether the horizontal scroll bar is aways shown.  Value is either \"True\" or \"False\".",
            "False")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class HorzStepSize : public Property
    {
    public:
        HorzStepSize() : Property(
            "HorzStepSize",
            "Property to get/set the step size for the horizontal Scrollbar.  Value is a float.",
            "0.100000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class HorzOverlapSize : public Property
    {
    public:
        HorzOverlapSize() : Property(
            "HorzOverlapSize",
            "Property to get/set the overlap size for the horizontal Scrollbar.  Value is a float.",
            "0.010000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class HorzScrollPosition : public Property
    {
    public:
        HorzScrollPosition() : Property(
            "HorzScrollPosition",
            "Property to get/set the scroll position of the horizontal Scrollbar as a fraction.  Value is a float.",
            "0.000000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class VertStepSize : public Property
    {
    public:
        VertStepSize() : Property(
            "VertStepSize",
            "Property to get/set the step size for the vertical Scrollbar.  Value is a float.",
            "0.100000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class VertOverlapSize : public Property
    {
    public:
        VertOverlapSize() : Property(
            "VertOverlapSize",
            "Property to get/set the overlap size for the vertical Scrollbar.  Value is a float.",
            "0.010000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

    
    class VertScrollPosition : public Property
    {
    public:
        VertScrollPosition() : Property(
            "VertScrollPosition",
            "Property to get/set the scroll position of the vertical Scrollbar as a fraction.  Value is a float.",
            "0.000000")
        {}

        String	get(const PropertyReceiver* receiver) const;
        void	set(PropertyReceiver* receiver, const String& value);
    };

} 
} 


#endif	
