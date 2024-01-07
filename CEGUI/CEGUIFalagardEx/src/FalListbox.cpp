

#include "FalListbox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
    const utf8 FalagardListbox::WidgetTypeName[] = "Falagard/Listbox";


    FalagardListbox::FalagardListbox(const String& type, const String& name) :
        Listbox(type, name)
    {
		d_recalculation = false;
    }

    FalagardListbox::~FalagardListbox()
    {
    }

    Rect FalagardListbox::getListRenderArea(void) const
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
		bool h_visible = false;
        bool v_visible = false;
		if(  d_horzScrollbar )
			v_visible= d_vertScrollbar->isVisible(true);
		if(  d_horzScrollbar )
			h_visible = d_horzScrollbar->isVisible(true);

        
        if (v_visible || h_visible)
        {
            String area_name("ItemRenderingArea");

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

        
        return wlf.getNamedArea("ItemRenderingArea").getArea().getPixelRect(*this);
    }

    Scrollbar* FalagardListbox::createVertScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardListbox::createHorzScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardListbox::cacheListboxBaseImagery()
	{
		d_validSize = 0;

        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    
    
    
    Window* FalagardListboxFactory::createWindow(const String& name)
    {
        return new FalagardListbox(d_type, name);
    }

    void FalagardListboxFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
