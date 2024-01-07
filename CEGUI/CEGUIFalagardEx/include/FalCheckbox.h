

#ifndef _FalCheckbox_h_
#define _FalCheckbox_h_

#include "FalModule.h"
#include "elements/CEGUICheckbox.h"
#include "CEGUIWindowFactory.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardCheckbox : public Checkbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardCheckbox(const String& type, const String& name);

        
        ~FalagardCheckbox();

        
        void drawSelf(float z);

        
        void drawNormal(float z);
        void drawHover(float z);
        void drawPushed(float z);
        void drawDisabled(float z);

    protected:
        void doButtonRender(const String& state);
    };

    
    class FALAGARDBASE_API FalagardCheckboxFactory : public WindowFactory
    {
    public:
        FalagardCheckboxFactory(void) : WindowFactory(FalagardCheckbox::WidgetTypeName) { }
        ~FalagardCheckboxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
