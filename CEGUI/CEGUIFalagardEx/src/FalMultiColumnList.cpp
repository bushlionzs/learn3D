

#include "FalMultiColumnList.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"
#include "elements/CEGUIListHeader.h"



namespace CEGUI
{
    const utf8 FalagardMultiColumnList::WidgetTypeName[] = "Falagard/MultiColumnList";


    FalagardMultiColumnList::FalagardMultiColumnList(const String& type, const String& name) :
        MultiColumnList(type, name)
    {
		d_recalculation = false;
    }

    FalagardMultiColumnList::~FalagardMultiColumnList()
    {
    }

    Rect FalagardMultiColumnList::getListRenderArea(void) const
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

    ListHeader* FalagardMultiColumnList::createListHeader(const String& name) const
    {
        
        return static_cast<ListHeader*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardMultiColumnList::createVertScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    Scrollbar* FalagardMultiColumnList::createHorzScrollbar(const String& name) const
    {
        
        return static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(name));
    }

    void FalagardMultiColumnList::cacheListboxBaseImagery()
    {
		d_validSize = 0;

		const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    
    
    
    Window* FalagardMultiColumnListFactory::createWindow(const String& name)
    {
        return new FalagardMultiColumnList(d_type, name);
    }

    void FalagardMultiColumnListFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
