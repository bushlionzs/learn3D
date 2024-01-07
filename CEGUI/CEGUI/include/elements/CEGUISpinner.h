

#ifndef _CEGUISpinner_h_
#define _CEGUISpinner_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUISpinnerProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{
    
    class CEGUIEXPORT Spinner : public Window
    {
    public:
        
        enum TextInputMode
        {
            FloatingPoint,  
            Integer,        
            Hexadecimal,    
            Octal           
        };

        
        static const String EventNamespace;                 
        static const String EventValueChanged;              
        static const String EventStepChanged;               
        static const String EventMaximumValueChanged;       
        static const String EventMinimumValueChanged;       
        static const String EventTextInputModeChanged;      

        
        
        Spinner(const String& type, const String& name);

        
        virtual ~Spinner(void);

	    
        void initialise(void);


        
        
        float getCurrentValue(void) const;

        
        float getStepSize(void) const;

        
        float getMaximumValue(void) const;

        
        float getMinimumValue(void) const;

        
        TextInputMode getTextInputMode(void) const;

        
        
        void setCurrentValue(float value);

        
        void setStepSize(float step);

        
        void setMaximumValue(float maxValue);

        
        void setMinimumValue(float minVaue);

        
        void setTextInputMode(TextInputMode mode);

    protected:
        
        static const String FloatValidator;      
        static const String IntegerValidator;    
        static const String HexValidator;        
        static const String OctalValidator;      

        
        
        virtual float getValueFromText(void) const;

        
        virtual String getTextFromValue(void) const;


		
		virtual bool	testClassName_impl(const String& class_name) const
		{
			if (class_name==(const utf8*)"Spinner")	return true;
			return Window::testClassName_impl(class_name);
		}


        
        
        virtual PushButton* createIncreaseButton(const String& name) const = 0;

        
        virtual PushButton* createDecreaseButton(const String& name) const = 0;

        
        virtual Editbox* createEditbox(const String& name) const = 0;

        
        virtual	void onFontChanged(WindowEventArgs& e);
        virtual void onTextChanged(WindowEventArgs& e);
        virtual void onActivated(ActivationEventArgs& e);

        
        
        virtual void onValueChanged(WindowEventArgs& e);

        
        virtual void onStepChanged(WindowEventArgs& e);

        
        virtual void onMaximumValueChanged(WindowEventArgs& e);

        
        virtual void onMinimumValueChanged(WindowEventArgs& e);

        
        virtual void onTextInputModeChanged(WindowEventArgs& e);

        
        bool handleIncreaseButton(const EventArgs& e);
        bool handleDecreaseButton(const EventArgs& e);
        bool handleEditTextChange(const EventArgs& e);


        
        PushButton* d_increaseButton;   
        PushButton* d_decreaseButton;   
        Editbox*    d_editbox;          

        float   d_stepSize;     
        float   d_currentValue; 
        float   d_maxValue;     
        float   d_minValue;     
        TextInputMode   d_inputMode;    

    private:
        
        static SpinnerProperties::CurrentValue  d_currentValueProperty;
        static SpinnerProperties::StepSize      d_stepSizeProperty;
        static SpinnerProperties::MaximumValue  d_maxValueProperty;
        static SpinnerProperties::MinimumValue  d_minValueProperty;
        static SpinnerProperties::TextInputMode d_textInputModeProperty;

        
        
        void    addSpinnerProperties(void);
    };

} 


#endif	
