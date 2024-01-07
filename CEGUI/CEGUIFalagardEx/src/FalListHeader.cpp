

#include "FalListHeader.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{
    const utf8 FalagardListHeader::WidgetTypeName[] = "Falagard/ListHeader";

    
    FalagardListHeaderProperties::SegmentWidgetType FalagardListHeader::d_segmentWidgetTypeProperty;


    FalagardListHeader::FalagardListHeader(const String& type, const String& name) :
        ListHeader(type, name)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardListHeader )
		   CEGUI_ADD_STATICPROPERTY( &d_segmentWidgetTypeProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardListHeader::~FalagardListHeader()
    {
    }

    void FalagardListHeader::populateRenderCache()
    {
        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        imagery->render(*this);
    }

    const String& FalagardListHeader::getSegmentWidgetType() const
    {
        return d_segmentWidgetType;
    }

    void FalagardListHeader::setSegmentWidgetType(const String& type)
    {
        d_segmentWidgetType = type;
    }

    ListHeaderSegment* FalagardListHeader::createNewSegment(const String& name) const
    {
        
        if (d_segmentWidgetType.empty())
        {
            InvalidRequestException("FalagardListHeader::createNewSegment - Segment widget type has not been set!");
        }

        return static_cast<ListHeaderSegment*>(WindowManager::getSingleton().createWindow(d_segmentWidgetType, name));
    }

    void FalagardListHeader::destroyListSegment(ListHeaderSegment* segment) const
    {
        
        WindowManager::getSingleton().destroyWindow(segment);
    }


    
    
    
    Window* FalagardListHeaderFactory::createWindow(const String& name)
    {
        return new FalagardListHeader(d_type, name);
    }

    void FalagardListHeaderFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
