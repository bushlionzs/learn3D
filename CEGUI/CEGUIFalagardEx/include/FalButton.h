

#ifndef _FalButton_h_
#define _FalButton_h_

#include "FalModule.h"
#include "elements/CEGUIPushButton.h"
#include "CEGUIWindowFactory.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardButton : public PushButton
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardButton(const String& type, const String& name);

        
        ~FalagardButton();

        
        void drawSelf(float z);

        
        void drawNormal(float z);
        void drawHover(float z);
        void drawPushed(float z);
        void drawDisabled(float z);

		virtual Size getRenderSize();

    protected:
        void doButtonRender(const String& state);
    };

    
    class FALAGARDBASE_API FalagardButtonFactory : public WindowFactory
    {
    public:
        FalagardButtonFactory(void) : WindowFactory(FalagardButton::WidgetTypeName) { }
        ~FalagardButtonFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
