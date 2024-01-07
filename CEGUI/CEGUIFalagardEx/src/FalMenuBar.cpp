

#include "FalMenuBar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardMenubar::WidgetTypeName[] = "Falagard/Menubar";

    FalagardMenubar::FalagardMenubar(const String& type, const String& name) :
        Menubar(type, name)
    {
    }

    FalagardMenubar::~FalagardMenubar()
    {
    }

    void FalagardMenubar::populateRenderCache()
    {
        const StateImagery* imagery;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    void FalagardMenubar::sizeToContent_impl(void)
    {
        Rect renderArea(getItemRenderArea());
        Rect wndArea(getAbsoluteRect());

        
        Size sz(getContentSize());

        
        sz.d_width  += wndArea.getWidth() - renderArea.getWidth();
        sz.d_height += wndArea.getHeight() - renderArea.getHeight();
        setSize(Absolute,sz);
    }

    Rect FalagardMenubar::getItemRenderArea(void) const
    {
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        return wlf.getNamedArea("ItemRenderArea").getArea().getPixelRect(*this);
    }


    
    
    
    Window* FalagardMenubarFactory::createWindow(const String& name)
    {
        return new FalagardMenubar(d_type, name);
    }

    void FalagardMenubarFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
