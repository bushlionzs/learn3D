

#include "FalProgressBar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardProgressBar::WidgetTypeName[] = "Falagard/ProgressBar";
    FalagardProgressBarProperties::VerticalProgress FalagardProgressBar::d_verticalProperty;
    FalagardProgressBarProperties::ReversedProgress FalagardProgressBar::d_reversedProperty;


    FalagardProgressBar::FalagardProgressBar(const String& type, const String& name) :
        ProgressBar(type, name),
        d_vertical(false),
        d_reversed(false)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardProgressBar )
		   CEGUI_ADD_STATICPROPERTY( &d_verticalProperty );
           CEGUI_ADD_STATICPROPERTY( &d_reversedProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardProgressBar::~FalagardProgressBar()
    {
    }

    void FalagardProgressBar::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);

        
        imagery = &wlf.getStateImagery(d_enabled ? "EnabledProgress" : "DisabledProgress");

        
        Rect progressRect(wlf.getNamedArea("ProgressArea").getArea().getPixelRect(*this));

        
        Rect progressClipper(progressRect);

        if (d_vertical)
        {
            float height = progressRect.getHeight() * d_progress;

            if (d_reversed)
            {
                progressRect.setHeight(height);
            }
            else
            {
                progressClipper.d_top = progressClipper.d_bottom - height;
            }
        }
        else
        {
            float width = progressRect.getWidth() * d_progress;

            if (d_reversed)
            {
                progressClipper.d_left = progressClipper.d_right - width;
            }
            else
            {
                progressRect.setWidth(width);
            }
        }

        
        imagery->render(*this, progressRect, 0, &progressClipper);
    }

    bool FalagardProgressBar::isVertical() const
    {
        return d_vertical;
    }

    bool FalagardProgressBar::isReversed() const
    {
        return d_reversed;
    }

    void FalagardProgressBar::setVertical(bool setting)
    {
        d_vertical = setting;
    }

    void FalagardProgressBar::setReversed(bool setting)
    {
        d_reversed = setting;
    }

    
    
    
    Window* FalagardProgressBarFactory::createWindow(const String& name)
    {
        return new FalagardProgressBar(d_type, name);
    }

    void FalagardProgressBarFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
