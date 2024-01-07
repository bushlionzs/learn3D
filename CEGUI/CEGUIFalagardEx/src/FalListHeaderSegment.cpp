

#include "FalListHeaderSegment.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"


namespace CEGUI
{
    const utf8 FalagardListHeaderSegment::WidgetTypeName[] = "Falagard/ListHeaderSegment";

    
    FalagardListHeaderSegmentProperties::SizingCursorImage   FalagardListHeaderSegment::d_sizingCursorProperty;
    FalagardListHeaderSegmentProperties::MovingCursorImage   FalagardListHeaderSegment::d_movingCursorProperty;


    FalagardListHeaderSegment::FalagardListHeaderSegment(const String& type, const String& name) :
        ListHeaderSegment(type, name)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardListHeaderSegment )
		   CEGUI_ADD_STATICPROPERTY( &d_sizingCursorProperty );
           CEGUI_ADD_STATICPROPERTY( &d_movingCursorProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardListHeaderSegment::~FalagardListHeaderSegment()
    {
    }

    const Image* FalagardListHeaderSegment::getSizingCursorImage() const
    {
        return d_sizingMouseCursor;
    }

    void FalagardListHeaderSegment::setSizingCursorImage(const Image* image)
    {
        d_sizingMouseCursor = image;
    }

    void FalagardListHeaderSegment::setSizingCursorImage(const String& imageset, const String& image)
    {
        d_sizingMouseCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
    }

    const Image* FalagardListHeaderSegment::getMovingCursorImage() const
    {
        return d_movingMouseCursor;
    }

    void FalagardListHeaderSegment::setMovingCursorImage(const Image* image)
    {
        d_movingMouseCursor = image;
    }

    void FalagardListHeaderSegment::setMovingCursorImage(const String& imageset, const String& image)
    {
        d_movingMouseCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image);
    }

    void FalagardListHeaderSegment::populateRenderCache()
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

        const StateImagery* imagery;

        
        if (isDisabled())
        {
            imagery = &wlf.getStateImagery("Disabled");
        }
        else if ((d_segmentHover != d_segmentPushed) && !d_splitterHover && isClickable())
        {
            imagery = &wlf.getStateImagery("Hover");
        }
        else if (d_splitterHover)
        {
            imagery = &wlf.getStateImagery("SplitterHover");
        }
        else
        {
            imagery = &wlf.getStateImagery("Normal");
        }

        
        imagery->render(*this);

        
        
        
        
        
        
        
        
        
        
        

        
        if (d_dragMoving)
        {
            Rect targetArea(0, 0, getAbsoluteWidth(), getAbsoluteHeight());
            targetArea.offset(d_dragPosition);
            imagery = &wlf.getStateImagery("DragGhost");
            imagery->render(*this, targetArea);

            
            if (d_sortDir == Ascending)
            {
                imagery = &wlf.getStateImagery("GhostAscendingSortIcon");
                imagery->render(*this, targetArea);
            }
            else if (d_sortDir == Descending)
            {
                imagery = &wlf.getStateImagery("GhostDescendingSortIcon");
                imagery->render(*this, targetArea);
            }
        }
    }


    
    
    
    Window* FalagardListHeaderSegmentFactory::createWindow(const String& name)
    {
        return new FalagardListHeaderSegment(d_type, name);
    }

    void FalagardListHeaderSegmentFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
