

#ifndef _FalTabButton_h_
#define _FalTabButton_h_

#include "FalModule.h"
#include "elements/CEGUITabButton.h"
#include "CEGUIWindowFactory.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardTabButton : public TabButton
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardTabButton(const String& type, const String& name);

        
        ~FalagardTabButton();

        
        void drawSelf(float z);

        
        void drawNormal(float z);
        void drawHover(float z);
        void drawPushed(float z);
        void drawDisabled(float z);

    protected:
        void doTabButtonRender(const String& state);
    };

    
    class FALAGARDBASE_API FalagardTabButtonFactory : public WindowFactory
    {
    public:
        FalagardTabButtonFactory(void) : WindowFactory(FalagardTabButton::WidgetTypeName) { }
        ~FalagardTabButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
