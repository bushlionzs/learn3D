

#ifndef _FalMultiColumnList_h_
#define _FalMultiColumnList_h_

#include "FalModule.h"
#include "elements/CEGUIMultiColumnList.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowFactory.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardMultiColumnList : public MultiColumnList
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardMultiColumnList(const String& type, const String& name);

        
        ~FalagardMultiColumnList();

    protected:
        
        Rect getListRenderArea(void) const;
        ListHeader* createListHeader(const String& name) const;
        Scrollbar* createVertScrollbar(const String& name) const;
        Scrollbar* createHorzScrollbar(const String& name) const;
        void cacheListboxBaseImagery();
    };

    
    class FALAGARDBASE_API FalagardMultiColumnListFactory : public WindowFactory
    {
    public:
        FalagardMultiColumnListFactory(void) : WindowFactory(FalagardMultiColumnList::WidgetTypeName) { }
        ~FalagardMultiColumnListFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
