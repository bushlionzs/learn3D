

#include "FalTabPane.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardTabPane::WidgetTypeName[] = "Falagard/TabPane";

    FalagardTabPane::FalagardTabPane(const String& type, const String& name) :
        TabPane(type, name)
    {
    }

    FalagardTabPane::~FalagardTabPane()
    {
    }

    void FalagardTabPane::populateRenderCache()
    {
        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        imagery->render(*this);
    }

    
    
    
    Window* FalagardTabPaneFactory::createWindow(const String& name)
    {
        return new FalagardTabPane(d_type, name);
    }

    void FalagardTabPaneFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
