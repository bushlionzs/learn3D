

#include "FalMenuItem.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardMenuItem::WidgetTypeName[] = "Falagard/MenuItem";

    FalagardMenuItem::FalagardMenuItem(const String& type, const String& name) :
        MenuItem(type, name)
    {
    }

    FalagardMenuItem::~FalagardMenuItem()
    {
    }

    void FalagardMenuItem::populateRenderCache()
    {
        
        String stateName(isDisabled() ? "Disabled" : "Enabled");

        if (d_opened)
            stateName += "PopupOpen";
        else if (d_pushed)
            stateName += "Pushed";
        else if (d_hovering)
            stateName += "Hover";
        else
            stateName += "Normal";

        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(stateName);
        
        imagery->render(*this);

		
		Window* parent_window = getParent();
		bool not_menubar = (parent_window==NULL) ? true : !parent_window->testClassName("Menubar");
        if (d_popup && not_menubar)
        {
            
            imagery = &wlf.getStateImagery(d_opened ? "PopupOpenIcon" : "PopupClosedIcon");
            
            imagery->render(*this);
        }
    }

    
    
    
    Window* FalagardMenuItemFactory::createWindow(const String& name)
    {
        return new FalagardMenuItem(d_type, name);
    }

    void FalagardMenuItemFactory::destroyWindow(Window* window)
    {
        delete window;
    }

}
