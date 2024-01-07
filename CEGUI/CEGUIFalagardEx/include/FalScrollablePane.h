

#ifndef _FalScrollablePane_h_
#define _FalScrollablePane_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIScrollablePane.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardScrollablePane : public ScrollablePane
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardScrollablePane(const String& type, const String& name);

        
        ~FalagardScrollablePane();

    protected:
        
        void populateRenderCache();
        Scrollbar* createVerticalScrollbar(const String& name) const;
        Scrollbar* createHorizontalScrollbar(const String& name) const;
        Rect getViewableArea(void) const;
    };

    
    class FALAGARDBASE_API FalagardScrollablePaneFactory : public WindowFactory
    {
    public:
        FalagardScrollablePaneFactory(void) : WindowFactory(FalagardScrollablePane::WidgetTypeName) { }
        ~FalagardScrollablePaneFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 

#endif
