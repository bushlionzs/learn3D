

#ifndef _FalStaticText_h_
#define _FalStaticText_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIStaticText.h"


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardStaticText : public StaticText
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardStaticText(const String& type, const String& name);

        
        ~FalagardStaticText();

    protected:
        
        void populateRenderCache();
        Scrollbar* createVertScrollbar(const String& name) const;
        Scrollbar* createHorzScrollbar(const String& name) const;
        Rect getTextRenderArea(void) const;
    };

    
    class FALAGARDBASE_API FalagardStaticTextFactory : public WindowFactory
    {
    public:
        FalagardStaticTextFactory(void) : WindowFactory(FalagardStaticText::WidgetTypeName) { }
        ~FalagardStaticTextFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#endif  
