

#ifndef _FalMenuItem_h_
#define _FalMenuItem_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIMenuItem.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardMenuItem : public MenuItem
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardMenuItem(const String& type, const String& name);

        
        ~FalagardMenuItem();

    protected:
        
        void populateRenderCache();
    };

    
    class FALAGARDBASE_API FalagardMenuItemFactory : public WindowFactory
    {
    public:
        FalagardMenuItemFactory(void) : WindowFactory(FalagardMenuItem::WidgetTypeName) { }
        ~FalagardMenuItemFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
