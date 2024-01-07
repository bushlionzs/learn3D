

#include "elements/CEGUISpinnerProperties.h"
#include "elements/CEGUISpinner.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{

namespace SpinnerProperties
{
    String CurrentValue::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Spinner*>(receiver)->getCurrentValue());
    }

    void CurrentValue::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Spinner*>(receiver)->setCurrentValue(PropertyHelper::stringToFloat(value));
    }

    

    String StepSize::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Spinner*>(receiver)->getStepSize());
    }

    void StepSize::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Spinner*>(receiver)->setStepSize(PropertyHelper::stringToFloat(value));
    }

    

    String MinimumValue::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Spinner*>(receiver)->getMinimumValue());
    }

    void MinimumValue::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Spinner*>(receiver)->setMinimumValue(PropertyHelper::stringToFloat(value));
    }

    

    String MaximumValue::get(const PropertyReceiver* receiver) const
    {
        return PropertyHelper::floatToString(static_cast<const Spinner*>(receiver)->getMaximumValue());
    }

    void MaximumValue::set(PropertyReceiver* receiver, const String& value)
    {
        static_cast<Spinner*>(receiver)->setMaximumValue(PropertyHelper::stringToFloat(value));
    }

    
    
    String TextInputMode::get(const PropertyReceiver* receiver) const
    {
        switch(static_cast<const Spinner*>(receiver)->getTextInputMode())
        {
        case Spinner::FloatingPoint:
            return String("FloatingPoint");
            break;
        case Spinner::Hexadecimal:
            return String("Hexadecimal");
            break;
        case Spinner::Octal:
            return String("Octal");
            break;
        default:
            return String("Integer");
        }
    }

    void TextInputMode::set(PropertyReceiver* receiver, const String& value)
    {
        Spinner::TextInputMode mode;

        if (value == "FloatingPoint")
        {
            mode = Spinner::FloatingPoint;
        }
        else if (value == "Hexadecimal")
        {
            mode = Spinner::Hexadecimal;
        }
        else if (value == "Octal")
        {
            mode = Spinner::Octal;
        }
        else
        {
            mode = Spinner::Integer;
        }

        static_cast<Spinner*>(receiver)->setTextInputMode(mode);
    }

} 
} 
