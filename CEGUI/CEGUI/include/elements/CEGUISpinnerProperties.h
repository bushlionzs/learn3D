

#ifndef _CEGUISpinnerProperties_h_
#define _CEGUISpinnerProperties_h_

#include "CEGUIProperty.h"



namespace CEGUI
{

namespace SpinnerProperties
{
    
    class CurrentValue : public Property
    {
    public:
	    CurrentValue() : Property(
		    "CurrentValue",
		    "Property to get/set the current value of the spinner.  Value is a float.",
		    "0.000000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class StepSize : public Property
    {
    public:
	    StepSize() : Property(
		    "StepSize",
		    "Property to get/set the step size of the spinner.  Value is a float.",
		    "1.000000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class MinimumValue : public Property
    {
    public:
	    MinimumValue() : Property(
		    "MinimumValue",
		    "Property to get/set the minimum value setting of the spinner.  Value is a float.",
		    "-32768.000000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class MaximumValue : public Property
    {
    public:
	    MaximumValue() : Property(
		    "MaximumValue",
		    "Property to get/set the maximum value setting of the spinner.  Value is a float.",
		    "32767.000000")
	    {}

	    String get(const PropertyReceiver* receiver) const;
	    void set(PropertyReceiver* receiver, const String& value);
    };

    
    class TextInputMode : public Property
    {
    public:
	    TextInputMode() : Property(
		    "TextInputMode",
		    "Property to get/set the TextInputMode setting for the spinner.  Value is \"FloatingPoint\", \"Integer\", \"Hexadecimal\", or \"Octal\".",
		    "Integer")
	    {}

	    String	get(const PropertyReceiver* receiver) const;
	    void	set(PropertyReceiver* receiver, const String& value);
    };

} 
} 


#endif	
