

#ifndef _FalScrollbar_h_
#define _FalScrollbar_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIScrollbar.h"
#include "FalScrollbarProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardScrollbar : public Scrollbar
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardScrollbar(const String& type, const String& name);

        
        ~FalagardScrollbar();

        bool isVertical() const;
        void setVertical(bool setting);

    protected:
        
        bool    d_vertical;     

        
        void populateRenderCache();
        Thumb* createThumb(const String& name) const;
        PushButton* createIncreaseButton(const String& name) const;
        PushButton* createDecreaseButton(const String& name) const;
        void performChildWindowLayout();
        void updateThumb(void);
        float getValueFromThumb(void) const;
        float getAdjustDirectionFromPoint(const Point& pt) const;

        
        static FalagardScrollbarProperties::VerticalScrollbar d_verticalProperty;
    };

    
    class FALAGARDBASE_API FalagardScrollbarFactory : public WindowFactory
    {
    public:
        FalagardScrollbarFactory(void) : WindowFactory(FalagardScrollbar::WidgetTypeName) { }
        ~FalagardScrollbarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
