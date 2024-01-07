

#include "FalStaticText.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
    const utf8 FalagardStaticText::WidgetTypeName[] = "Falagard/StaticText";

    FalagardStaticText::FalagardStaticText(const String& type, const String& name) :
        StaticText(type, name)
    {
		d_recalculation = false;
    }

    FalagardStaticText::~FalagardStaticText()
    {
    }

    void FalagardStaticText::populateRenderCache()
    {
        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

		bool is_enabled = !isDisabled();

		d_validSize = 0;

		
        if (d_frameEnabled)
        {
            imagery = &wlf.getStateImagery(is_enabled ? "EnabledFrame" : "DisabledFrame");
            
            imagery->render(*this);
        }

        
        if (d_backgroundEnabled)
        {
            imagery = &wlf.getStateImagery(is_enabled ? "EnabledBackground" : "DisabledBackground");
            
            imagery->render(*this);
        }

        
        imagery = &wlf.getStateImagery(is_enabled ? "Enabled" : "Disabled");
        
        imagery->render(*this);

        
        StaticText::populateRenderCache();
    }

    Scrollbar* FalagardStaticText::createVertScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardStaticText::createHorzScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Rect FalagardStaticText::getTextRenderArea(void) const
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
            String area_name("TextRenderArea");

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

        
        return wlf.getNamedArea("TextRenderArea").getArea().getPixelRect(*this);
    }

    
    
    
    Window* FalagardStaticTextFactory::createWindow(const String& name)
    {
        return new FalagardStaticText(d_type, name);
    }

    void FalagardStaticTextFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
