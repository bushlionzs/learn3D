

#include "FalScrollablePane.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
    const utf8 FalagardScrollablePane::WidgetTypeName[] = "Falagard/ScrollablePane";


    FalagardScrollablePane::FalagardScrollablePane(const String& type, const String& name) :
        ScrollablePane(type, name)
    {
    }

    FalagardScrollablePane::~FalagardScrollablePane()
    {
    }

    Rect FalagardScrollablePane::getViewableArea(void) const
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
		bool v_visible = false;
		if( d_vertScrollbar )
			v_visible = d_vertScrollbar->isVisible(true);
        bool h_visible = false;
		if( d_horzScrollbar )
			h_visible = d_horzScrollbar->isVisible(true);

        
        if (v_visible || h_visible)
        {
            String area_name("ViewableArea");

            if (h_visible)
            {
                area_name += "H";
            }
            if (v_visible)
            {
                area_name += "V";
            }
            area_name += "Scroll";

            if (wlf.isNamedAreaDefined(area_name))
            {
                return wlf.getNamedArea(area_name).getArea().getPixelRect(*this);
            }
        }

        
        return wlf.getNamedArea("ViewableArea").getArea().getPixelRect(*this);
    }

    Scrollbar* FalagardScrollablePane::createVerticalScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardScrollablePane::createHorizontalScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardScrollablePane::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }


    
    
    
    Window* FalagardScrollablePaneFactory::createWindow(const String& name)
    {
        return new FalagardScrollablePane(d_type, name);
    }

    void FalagardScrollablePaneFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
