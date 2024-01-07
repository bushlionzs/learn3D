

#ifndef _FalProgressBar_h_
#define _FalProgressBar_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIProgressBar.h"
#include "FalProgressBarProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardProgressBar : public ProgressBar
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardProgressBar(const String& type, const String& name);

        
        ~FalagardProgressBar();

        bool isVertical() const;
        bool isReversed() const;

        void setVertical(bool setting);
        void setReversed(bool setting);

    protected:
        
        void populateRenderCache();

        
        bool d_vertical;    
        bool d_reversed;    

        
        static FalagardProgressBarProperties::VerticalProgress d_verticalProperty;
        static FalagardProgressBarProperties::ReversedProgress d_reversedProperty;
    };

    
    class FALAGARDBASE_API FalagardProgressBarFactory : public WindowFactory
    {
    public:
        FalagardProgressBarFactory(void) : WindowFactory(FalagardProgressBar::WidgetTypeName) { }
        ~FalagardProgressBarFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
