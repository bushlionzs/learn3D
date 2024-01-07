

#ifndef _FalSlider_h_
#define _FalSlider_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUISlider.h"
#include "FalSliderProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardSlider : public Slider
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardSlider(const String& type, const String& name);

        
        ~FalagardSlider();

        bool isVertical() const;
        void setVertical(bool setting);

        bool isReversedDirection() const;
        void setReversedDirection(bool setting);

    protected:
        
        bool    d_vertical;     
        bool    d_reversed;     

        
        void populateRenderCache();
        Thumb* createThumb(const String& name) const;
        void performChildWindowLayout();
        void updateThumb(void);
        float getValueFromThumb(void) const;
        float getAdjustDirectionFromPoint(const Point& pt) const;

        
        static FalagardSliderProperties::VerticalSlider d_verticalProperty;
        static FalagardSliderProperties::ReversedDirection d_reversedProperty;
    };

    
    class FALAGARDBASE_API FalagardSliderFactory : public WindowFactory
    {
    public:
        FalagardSliderFactory(void) : WindowFactory(FalagardSlider::WidgetTypeName) { }
        ~FalagardSliderFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
