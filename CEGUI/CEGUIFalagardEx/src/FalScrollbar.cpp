

#include "FalScrollbar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIThumb.h"
#include "elements/CEGUIPushButton.h"


namespace CEGUI
{
    const utf8 FalagardScrollbar::WidgetTypeName[] = "Falagard/Scrollbar";
    FalagardScrollbarProperties::VerticalScrollbar FalagardScrollbar::d_verticalProperty;


    FalagardScrollbar::FalagardScrollbar(const String& type, const String& name) :
        Scrollbar(type, name),
        d_vertical(false)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardScrollbar )
		   CEGUI_ADD_STATICPROPERTY( &d_verticalProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardScrollbar::~FalagardScrollbar()
    {
    }

    void FalagardScrollbar::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    Thumb* FalagardScrollbar::createThumb(const String& name) const
    {
        
        return static_cast<Thumb*>(WindowManager::getSingleton().getWindow(name));
    }

    PushButton* FalagardScrollbar::createIncreaseButton(const String& name) const
    {
        
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(name));
    }

    PushButton* FalagardScrollbar::createDecreaseButton(const String& name) const
    {
        
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardScrollbar::performChildWindowLayout()
    {
        Scrollbar::performChildWindowLayout();
        updateThumb();
    }

    void FalagardScrollbar::updateThumb(void)
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        Rect area(wlf.getNamedArea("ThumbTrackArea").getArea().getPixelRect(*this));

        Thumb* theThumb = static_cast<Thumb*>(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__"));

        float posExtent = d_documentSize - d_pageSize;
        float slideExtent;

        if (d_vertical)
        {
            slideExtent = area.getHeight() - theThumb->getAbsoluteHeight();
            theThumb->setVertRange(absoluteToRelativeY_impl(this, area.d_top), absoluteToRelativeY_impl(this, area.d_top + slideExtent));
            theThumb->setPosition(Point(absoluteToRelativeX_impl(this, area.d_left), absoluteToRelativeY_impl(this, area.d_top + (d_position * (slideExtent / posExtent)))));
        }
        else
        {
            slideExtent = area.getWidth() - theThumb->getAbsoluteWidth();
            theThumb->setHorzRange(absoluteToRelativeX_impl(this, area.d_left), absoluteToRelativeX_impl(this, area.d_left + slideExtent));
            theThumb->setPosition(Point(absoluteToRelativeX_impl(this, area.d_left + (d_position * (slideExtent / posExtent))), absoluteToRelativeY_impl(this, area.d_top)));
        }
    }

    float FalagardScrollbar::getValueFromThumb(void) const
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        Rect area(wlf.getNamedArea("ThumbTrackArea").getArea().getPixelRect(*this));

        Thumb* theThumb = static_cast<Thumb*>(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__"));
        float posExtent = d_documentSize - d_pageSize;

        if (d_vertical)
        {
            float slideExtent = area.getHeight() - theThumb->getAbsoluteHeight();
            return (theThumb->getAbsoluteYPosition() - area.d_top) / (slideExtent / posExtent);
        }
        else
        {
            float slideExtent = area.getWidth() - theThumb->getAbsoluteWidth();
            return (theThumb->getAbsoluteXPosition() - area.d_left) / (slideExtent / posExtent);
        }
    }

    float FalagardScrollbar::getAdjustDirectionFromPoint(const Point& pt) const
    {
        Rect absrect(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__")->getUnclippedPixelRect());

        if ((d_vertical && (pt.d_y > absrect.d_bottom)) ||
            (!d_vertical && (pt.d_x > absrect.d_right)))
        {
            return 1;
        }
        else if ((d_vertical && (pt.d_y < absrect.d_top)) ||
            (!d_vertical && (pt.d_x < absrect.d_left)))
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    bool FalagardScrollbar::isVertical() const
    {
        return d_vertical;
    }

    void FalagardScrollbar::setVertical(bool setting)
    {
        d_vertical = setting;
    }

    
    
    
    Window* FalagardScrollbarFactory::createWindow(const String& name)
    {
        return new FalagardScrollbar(d_type, name);
    }

    void FalagardScrollbarFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
