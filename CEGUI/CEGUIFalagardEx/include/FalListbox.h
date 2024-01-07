

#ifndef _FalListbox_h_
#define _FalListbox_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIListbox.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardListbox : public Listbox
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardListbox(const String& type, const String& name);

        
        ~FalagardListbox();

    protected:
        
        Rect getListRenderArea(void) const;
        Scrollbar* createVertScrollbar(const String& name) const;
        Scrollbar* createHorzScrollbar(const String& name) const;
        void cacheListboxBaseImagery();
    };

    
    class FALAGARDBASE_API FalagardListboxFactory : public WindowFactory
    {
    public:
        FalagardListboxFactory(void) : WindowFactory(FalagardListbox::WidgetTypeName) { }
        ~FalagardListboxFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
