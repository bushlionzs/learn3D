

#include "FalComboDropList.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"


namespace CEGUI
{
    const utf8 FalagardComboDropList::WidgetTypeName[] = "Falagard/ComboDropList";

    FalagardComboDropList::FalagardComboDropList(const String& type, const String& name) :
        ComboDropList(type, name)
    {
		setClippedByParent(false);
		d_recalculation = false;
    }

    FalagardComboDropList::~FalagardComboDropList()
    {
    }

    Rect FalagardComboDropList::getListRenderArea(void) const
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        bool v_visible = false;
        bool h_visible = false;
		if( d_vertScrollbar	)
			v_visible = d_vertScrollbar->isVisible(true);
		if( d_horzScrollbar )
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

    Scrollbar* FalagardComboDropList::createVertScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardComboDropList::createHorzScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardComboDropList::cacheListboxBaseImagery()
	{
		d_validSize = 0;

        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }
    
    Window* FalagardComboDropListFactory::createWindow(const String& name)
    {
        return new FalagardComboDropList(d_type, name);
    }

    void FalagardComboDropListFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
