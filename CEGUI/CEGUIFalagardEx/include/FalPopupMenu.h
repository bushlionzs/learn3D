

#ifndef _FalPopupMenu_h_
#define _FalPopupMenu_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIPopupMenu.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardPopupMenu : public PopupMenu
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardPopupMenu(const String& type, const String& name);

        
        ~FalagardPopupMenu();

    protected:
        
        void populateRenderCache();
        void sizeToContent_impl(void);
        Rect getItemRenderArea(void) const;

		virtual void onSized(WindowEventArgs& e);
    };

    
    class FALAGARDBASE_API FalagardPopupMenuFactory : public WindowFactory
    {
    public:
        FalagardPopupMenuFactory(void) : WindowFactory(FalagardPopupMenu::WidgetTypeName) { }
        ~FalagardPopupMenuFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 

#endif  
