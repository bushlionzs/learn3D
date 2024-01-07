

#ifndef _FalTabPane_h_
#define _FalTabPane_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUITabPane.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardTabPane : public TabPane
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardTabPane(const String& type, const String& name);

        
        ~FalagardTabPane();

    protected:
        
        void populateRenderCache();
    };

    
    class FALAGARDBASE_API FalagardTabPaneFactory : public WindowFactory
    {
    public:
        FalagardTabPaneFactory(void) : WindowFactory(FalagardTabPane::WidgetTypeName) { }
        ~FalagardTabPaneFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
