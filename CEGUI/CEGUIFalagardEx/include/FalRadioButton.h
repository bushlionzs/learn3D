

#ifndef _FalRadioButton_h_
#define _FalRadioButton_h_

#include "FalModule.h"
#include "elements/CEGUIRadioButton.h"
#include "CEGUIWindowFactory.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardRadioButton : public RadioButton
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardRadioButton(const String& type, const String& name);

        
        ~FalagardRadioButton();

        
        void drawSelf(float z);

        
        void drawNormal(float z);
        void drawHover(float z);
        void drawPushed(float z);
        void drawDisabled(float z);

    protected:
        void doButtonRender(const String& state);
    };

    
    class FALAGARDBASE_API FalagardRadioButtonFactory : public WindowFactory
    {
    public:
        FalagardRadioButtonFactory(void) : WindowFactory(FalagardRadioButton::WidgetTypeName) { }
        ~FalagardRadioButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
