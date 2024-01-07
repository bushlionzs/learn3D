

#ifndef _FalListHeaderSegment_h_
#define _FalListHeaderSegment_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIListHeaderSegment.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "FalListHeaderSegmentProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardListHeaderSegment : public ListHeaderSegment
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardListHeaderSegment(const String& type, const String& name);

        
        ~FalagardListHeaderSegment();

        const Image* getSizingCursorImage() const;
        void setSizingCursorImage(const Image* image);
        void setSizingCursorImage(const String& imageset, const String& image);

        const Image* getMovingCursorImage() const;
        void setMovingCursorImage(const Image* image);
        void setMovingCursorImage(const String& imageset, const String& image);

    protected:
        
        void populateRenderCache();

        
        static FalagardListHeaderSegmentProperties::SizingCursorImage   d_sizingCursorProperty;
        static FalagardListHeaderSegmentProperties::MovingCursorImage   d_movingCursorProperty;
    };

    
    class FALAGARDBASE_API FalagardListHeaderSegmentFactory : public WindowFactory
    {
    public:
        FalagardListHeaderSegmentFactory(void) : WindowFactory(FalagardListHeaderSegment::WidgetTypeName) { }
        ~FalagardListHeaderSegmentFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
