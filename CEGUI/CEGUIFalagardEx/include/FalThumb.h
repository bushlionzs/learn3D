

#ifndef _FalThumb_h_
#define _FalThumb_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIThumb.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardThumb : public Thumb
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardThumb(const String& type, const String& name);

        
        ~FalagardThumb();

    protected:
        
        void drawSelf(float z);

        
        void drawNormal(float z);
        void drawHover(float z);
        void drawPushed(float z);
        void drawDisabled(float z);

        void doThumbRender(const String& state);

    };

    
    class FALAGARDBASE_API FalagardThumbFactory : public WindowFactory
    {
    public:
        FalagardThumbFactory(void) : WindowFactory(FalagardThumb::WidgetTypeName) { }
        ~FalagardThumbFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
