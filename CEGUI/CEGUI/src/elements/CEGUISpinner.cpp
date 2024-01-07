

#include "elements/CEGUISpinner.h"
#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIEditbox.h"
#include "CEGUIExceptions.h"
#include <stdio.h>
#include <sstream>
#include <iomanip>


namespace CEGUI
{
    
    
    const String Spinner::EventNamespace("Spinner");
    const String Spinner::EventValueChanged("ValueChanged");
    const String Spinner::EventStepChanged("StepChanged");
    const String Spinner::EventMaximumValueChanged("MaximumValueChanged");
    const String Spinner::EventMinimumValueChanged("MinimumValueChanged");
    const String Spinner::EventTextInputModeChanged("TextInputModeChanged");
    
    const String Spinner::FloatValidator("-?\\d*\\.?\\d*");
    const String Spinner::IntegerValidator("-?\\d*");
    const String Spinner::HexValidator("[0-9a-fA-F]*");
    const String Spinner::OctalValidator("[0-7]*");
    
    SpinnerProperties::CurrentValue  Spinner::d_currentValueProperty;
    SpinnerProperties::StepSize      Spinner::d_stepSizeProperty;
    SpinnerProperties::MaximumValue  Spinner::d_maxValueProperty;
    SpinnerProperties::MinimumValue  Spinner::d_minValueProperty;
    SpinnerProperties::TextInputMode Spinner::d_textInputModeProperty;
    
    
    Spinner::Spinner(const String& type, const String& name) :
        Window(type, name),
        d_increaseButton(0),
        d_decreaseButton(0),
        d_editbox(0),
        d_stepSize(1.0f),
        d_currentValue(1.0f),
        d_maxValue(32767.0f),
        d_minValue(-32768.0f),
        d_inputMode((TextInputMode)-1)
    {
        addSpinnerProperties();
    }

    Spinner::~Spinner(void)
    {
        
    }

    void Spinner::initialise(void)
    {
        Window::initialise();

        
        d_increaseButton = createIncreaseButton(getName() + "__auto_incbtn__");
        addChildWindow(d_increaseButton);
        d_decreaseButton = createDecreaseButton(getName() + "__auto_decbtn__");
        addChildWindow(d_decreaseButton);
        d_editbox = createEditbox(getName() + "__auto_editbox__");
        addChildWindow(d_editbox);

        
        d_increaseButton->setWantsMultiClickEvents(false);
        d_increaseButton->setMouseAutoRepeatEnabled(true);
        d_decreaseButton->setWantsMultiClickEvents(false);
        d_decreaseButton->setMouseAutoRepeatEnabled(true);

        
        d_increaseButton->subscribeEvent(Window::EventMouseButtonDown, Event::Subscriber(&Spinner::handleIncreaseButton, this));
        d_decreaseButton->subscribeEvent(Window::EventMouseButtonDown, Event::Subscriber(&Spinner::handleDecreaseButton, this));
        d_editbox->subscribeEvent(Window::EventTextChanged, Event::Subscriber(&Spinner::handleEditTextChange, this));

        
        setTextInputMode(Integer);
        setCurrentValue(0.0f);
        performChildWindowLayout();
    }

    float Spinner::getCurrentValue(void) const
    {
        return d_currentValue;
    }

    float Spinner::getStepSize(void) const
    {
        return d_stepSize;
    }

    float Spinner::getMaximumValue(void) const
    {
        return d_maxValue;
    }

    float Spinner::getMinimumValue(void) const
    {
        return d_minValue;
    }

    Spinner::TextInputMode Spinner::getTextInputMode(void) const
    {
        return d_inputMode;
    }

    void Spinner::setCurrentValue(float value)
    {
        if (value != d_currentValue)
        {
            
            value = std::max(std::min(value, d_maxValue), d_minValue);

            d_currentValue = value;

            WindowEventArgs args(this);
            onValueChanged(args);
        }
    }

    void Spinner::setStepSize(float step)
    {
        if (step != d_stepSize)
        {
            d_stepSize = step;
            
            WindowEventArgs args(this);
            onStepChanged(args);
        }
    }

    void Spinner::setMaximumValue(float maxValue)
    {
        if (maxValue != d_maxValue)
        {
            d_maxValue = maxValue;

            WindowEventArgs args(this);
            onMaximumValueChanged(args);
        }
    }

    void Spinner::setMinimumValue(float minVaue)
    {
        if (minVaue != d_minValue)
        {
            d_minValue = minVaue;

            WindowEventArgs args(this);
            onMinimumValueChanged(args);
        }
    }

    void Spinner::setTextInputMode(TextInputMode mode)
    {
        if (mode != d_inputMode)
        {
            switch (mode)
            {
            case FloatingPoint:
                d_editbox->setValidationString(FloatValidator);
                break;
            case Integer:
                d_editbox->setValidationString(IntegerValidator);
                break;
            case Hexadecimal:
                d_editbox->setValidationString(HexValidator);
                break;
            case Octal:
                d_editbox->setValidationString(OctalValidator);
                break;
            default:
                throw InvalidRequestException("Spinner::setTextInputMode - An unknown TextInputMode was specified.");
            }

            d_inputMode = mode;

            WindowEventArgs args(this);
            onTextInputModeChanged(args);
        }
    }

    void Spinner::addSpinnerProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( Spinner );
           CEGUI_ADD_STATICPROPERTY( &d_currentValueProperty );
           CEGUI_ADD_STATICPROPERTY( &d_stepSizeProperty );
           CEGUI_ADD_STATICPROPERTY( &d_maxValueProperty );
           CEGUI_ADD_STATICPROPERTY( &d_minValueProperty );
           CEGUI_ADD_STATICPROPERTY( &d_textInputModeProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    float Spinner::getValueFromText(void) const
    {
        
        if (d_editbox->getText().empty())
        {
            return 0.0f;
        }

        int res, tmp;
        uint utmp;
        float val;

        switch (d_inputMode)
        {
        case FloatingPoint:
            res = sscanf(d_editbox->getText().c_str(), "%f", &val);
            break;
        case Integer:
            res = sscanf(d_editbox->getText().c_str(), "%d", &tmp);
            val = static_cast<float>(tmp);
            break;
        case Hexadecimal:
            res = sscanf(d_editbox->getText().c_str(), "%x", &utmp);
            val = static_cast<float>(utmp);
            break;
        case Octal:
            res = sscanf(d_editbox->getText().c_str(), "%o", &utmp);
            val = static_cast<float>(utmp);
            break;
        default:
            throw InvalidRequestException("Spinner::getValueFromText - An unknown TextInputMode was encountered.");
        }

        if (res)
        {
            return val;            
        }

        throw InvalidRequestException("Spinner::getValueFromText - The string '" + d_editbox->getText() + "' ca not be converted to numerical representation.");
    }

    String Spinner::getTextFromValue(void) const
    {
        std::stringstream tmp;

        switch (d_inputMode)
        {
        case FloatingPoint:
            tmp << d_currentValue;
            break;
        case Integer:
            tmp << static_cast<int>(d_currentValue);
            break;
        case Hexadecimal:
            tmp << std::hex << std::uppercase << static_cast<int>(d_currentValue);
            break;
        case Octal:
            tmp << std::oct << static_cast<int>(d_currentValue);
            break;
        default:
            throw InvalidRequestException("Spinner::getValueFromText - An unknown TextInputMode was encountered.");
        }

        return String(tmp.str());
    }

    void Spinner::onFontChanged(WindowEventArgs& e)
    {
        
        d_editbox->setFont(getFont());
        
        Window::onFontChanged(e);
    }

    void Spinner::onTextChanged(WindowEventArgs& e)
    {
        
        if (d_editbox->getText() != d_text)
        {
            
            
            d_editbox->setText(d_text);
            e.handled = true;

            Window::onTextChanged(e);
        }
    }

    void Spinner::onActivated(ActivationEventArgs& e)
    {
        if (!isActive())
        {
            Window::onActivated(e);

            if (!d_editbox->isActive())
            {
                d_editbox->activate();
            }
        }
    }

    void Spinner::onValueChanged(WindowEventArgs& e)
    {
        
        bool wasMuted = d_editbox->isMuted();
        d_editbox->setMutedState(true);

        
        
        if (!(d_currentValue == 0 && d_editbox->getText().empty()))
        {
            d_editbox->setText(getTextFromValue());
        }
        
        d_editbox->setMutedState(wasMuted);

        fireEvent(EventValueChanged, e, EventNamespace);
    }

    void Spinner::onStepChanged(WindowEventArgs& e)
    {
        fireEvent(EventStepChanged, e, EventNamespace);
    }

    void Spinner::onMaximumValueChanged(WindowEventArgs& e)
    {
        fireEvent(EventMaximumValueChanged, e, EventNamespace);

        if (d_currentValue > d_maxValue)
        {
            setCurrentValue(d_maxValue);
        }
    }

    void Spinner::onMinimumValueChanged(WindowEventArgs& e)
    {
        fireEvent(EventMinimumValueChanged, e, EventNamespace);

        if (d_currentValue < d_minValue)
        {
            setCurrentValue(d_minValue);
        }
    }

    void Spinner::onTextInputModeChanged(WindowEventArgs& e)
    {
        
        
        bool wasMuted = d_editbox->isMuted();
        d_editbox->setMutedState(true);
        
        d_editbox->setText(getTextFromValue());
        
        d_editbox->setMutedState(wasMuted);

        fireEvent(EventTextInputModeChanged, e, EventNamespace);
    }

    bool Spinner::handleIncreaseButton(const EventArgs& e)
    {
        if (((const MouseEventArgs&)e).button == LeftButton)
        {
            setCurrentValue(d_currentValue + d_stepSize);
            return true;
        }
        
        return false;
    }

    bool Spinner::handleDecreaseButton(const EventArgs& e)
    {
        if (((const MouseEventArgs&)e).button == LeftButton)
        {
            setCurrentValue(d_currentValue - d_stepSize);
            return true;
        }

        return false;
    }

    bool Spinner::handleEditTextChange(const EventArgs& e)
    {
        
        setText(d_editbox->getText());
        
        setCurrentValue(getValueFromText());
        return true;
    }

} 
