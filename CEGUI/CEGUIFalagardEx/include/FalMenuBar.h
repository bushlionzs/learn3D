

#ifndef _FalMenubar_h_
#define _FalMenubar_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIMenubar.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardMenubar : public Menubar
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardMenubar(const String& type, const String& name);

        
        ~FalagardMenubar();

    protected:
        
        void populateRenderCache();
        void sizeToContent_impl(void);
        Rect getItemRenderArea(void) const;
    };

    
    class FALAGARDBASE_API FalagardMenubarFactory : public WindowFactory
    {
    public:
        FalagardMenubarFactory(void) : WindowFactory(FalagardMenubar::WidgetTypeName) { }
        ~FalagardMenubarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 

#endif  
