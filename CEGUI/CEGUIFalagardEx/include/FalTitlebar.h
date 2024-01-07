

#ifndef _FalTitlebar_h_
#define _FalTitlebar_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUITitlebar.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardTitlebar : public Titlebar
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardTitlebar(const String& type, const String& name);

        
        ~FalagardTitlebar();

        
        Rect getPixelRect(void) const;

    protected:
        
        void populateRenderCache();
    };

    
    class FALAGARDBASE_API FalagardTitlebarFactory : public WindowFactory
    {
    public:
        FalagardTitlebarFactory(void) : WindowFactory(FalagardTitlebar::WidgetTypeName) { }
        ~FalagardTitlebarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
