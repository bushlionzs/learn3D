

#ifndef _FalListHeader_h_
#define _FalListHeader_h_

#include "FalModule.h"
#include "CEGUIWindowFactory.h"
#include "elements/CEGUIListHeader.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "FalListHeaderProperties.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{
    
    class FALAGARDBASE_API FalagardListHeader : public ListHeader
    {
    public:
        static const utf8   WidgetTypeName[];       

        
        FalagardListHeader(const String& type, const String& name);

        
        ~FalagardListHeader();

        const String& getSegmentWidgetType() const;
        void setSegmentWidgetType(const String& type);

    protected:
        
        void populateRenderCache();
        ListHeaderSegment* createNewSegment(const String& name) const;
        void destroyListSegment(ListHeaderSegment* segment) const;

        
        static FalagardListHeaderProperties::SegmentWidgetType   d_segmentWidgetTypeProperty;

        
        String  d_segmentWidgetType;
    };

    
    class FALAGARDBASE_API FalagardListHeaderFactory : public WindowFactory
    {
    public:
        FalagardListHeaderFactory(void) : WindowFactory(FalagardListHeader::WidgetTypeName) { }
        ~FalagardListHeaderFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif  
