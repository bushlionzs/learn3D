

#ifndef _FalComboDropList_h_
#define _FalComboDropList_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIComboDropList.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardComboDropList : public ComboDropList
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardComboDropList(const String& type, const String& name);

        
        ~FalagardComboDropList();

    protected:
        
        Rect getListRenderArea(void) const;
        Scrollbar* createVertScrollbar(const String& name) const;
        Scrollbar* createHorzScrollbar(const String& name) const;
        void cacheListboxBaseImagery();
    };

    
    class FALAGARDBASE_API FalagardComboDropListFactory : public WindowFactory
    {
    public:
        FalagardComboDropListFactory(void) : WindowFactory(FalagardComboDropList::WidgetTypeName) { }
        ~FalagardComboDropListFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
