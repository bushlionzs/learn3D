

#include "FalSlider.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIThumb.h"


namespace CEGUI
{
    const utf8 FalagardSlider::WidgetTypeName[] = "Falagard/Slider";
    FalagardSliderProperties::VerticalSlider FalagardSlider::d_verticalProperty;
    FalagardSliderProperties::ReversedDirection FalagardSlider::d_reversedProperty;


    FalagardSlider::FalagardSlider(const String& type, const String& name) :
        Slider(type, name),
        d_vertical(false),
        d_reversed(false)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardSlider )
		   CEGUI_ADD_STATICPROPERTY( &d_verticalProperty );
           CEGUI_ADD_STATICPROPERTY( &d_reversedProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardSlider::~FalagardSlider()
    {
    }

    void FalagardSlider::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    Thumb* FalagardSlider::createThumb(const String& name) const
    {
        
        return static_cast<Thumb*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardSlider::performChildWindowLayout()
    {
        Slider::performChildWindowLayout();
        updateThumb();
    }

    void FalagardSlider::updateThumb(void)
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        Rect area(wlf.getNamedArea("ThumbTrackArea").getArea().getPixelRect(*this));
        
        Thumb* theThumb = static_cast<Thumb*>(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__"));

        
        Point thumbPosition(area.d_left, area.d_top);

        
        if (d_vertical)
        {
            
            float slideExtent = area.getHeight() - theThumb->getAbsoluteHeight();
            
            theThumb->setVertRange(absoluteToRelativeY_impl(this, area.d_top), absoluteToRelativeY_impl(this, area.d_top + slideExtent));

            
            float thumbOffset = d_value * (slideExtent / d_maxValue);
            thumbPosition.d_y += d_reversed ? thumbOffset : slideExtent - thumbOffset;
        }
        
        else
        {
            
            float slideExtent = area.getWidth() - theThumb->getAbsoluteWidth();
            
            theThumb->setHorzRange(absoluteToRelativeX_impl(this, area.d_left), absoluteToRelativeX_impl(this, area.d_left + slideExtent));

            
            float thumbOffset = d_value * (slideExtent / d_maxValue);
            thumbPosition.d_x += d_reversed ? slideExtent - thumbOffset : thumbOffset;
        }

        
        theThumb->setPosition(absoluteToRelative_impl(this, thumbPosition));
    }

    float FalagardSlider::getValueFromThumb(void) const
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        Rect area(wlf.getNamedArea("ThumbTrackArea").getArea().getPixelRect(*this));
        
        Thumb* theThumb = static_cast<Thumb*>(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__"));

        
        if (d_vertical)
        {
            
            float slideExtent = area.getHeight() - theThumb->getAbsoluteHeight();
            
            float thumbValue = (theThumb->getAbsoluteYPosition() - area.d_top) / (slideExtent / d_maxValue);
            
            return d_reversed ? thumbValue : d_maxValue - thumbValue;
        }
        
        else
        {
            
            float slideExtent = area.getWidth() - theThumb->getAbsoluteWidth();
            
            float thumbValue = (theThumb->getAbsoluteXPosition() - area.d_left) / (slideExtent / d_maxValue);
            
            return d_reversed ? d_maxValue - thumbValue : thumbValue;
        }
    }

    float FalagardSlider::getAdjustDirectionFromPoint(const Point& pt) const
    {
        Rect absrect(WindowManager::getSingleton().getWindow(getName() + "__auto_thumb__")->getUnclippedPixelRect());

        if ((d_vertical && (pt.d_y < absrect.d_top)) ||
            (!d_vertical && (pt.d_x > absrect.d_right)))
        {
            return d_reversed ? -1.0f : 1.0f;
        }
        else if ((d_vertical && (pt.d_y > absrect.d_bottom)) ||
            (!d_vertical && (pt.d_x < absrect.d_left)))
        {
            return d_reversed ? 1.0f : -1.0f;
        }
        else
        {
            return 0;
        }
    }

    bool FalagardSlider::isVertical() const
    {
        return d_vertical;
    }

    void FalagardSlider::setVertical(bool setting)
    {
        d_vertical = setting;
    }

    bool FalagardSlider::isReversedDirection() const
    {
        return d_reversed;
    }

    void FalagardSlider::setReversedDirection(bool setting)
    {
        d_reversed = setting;
    }

    
    
    
    Window* FalagardSliderFactory::createWindow(const String& name)
    {
        return new FalagardSlider(d_type, name);
    }

    void FalagardSliderFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
