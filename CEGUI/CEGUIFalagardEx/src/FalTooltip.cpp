

#include "FalTooltip.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardTooltip::WidgetTypeName[] = "Falagard/Tooltip";

    FalagardTooltip::FalagardTooltip(const String& type, const String& name) :
        Tooltip(type, name)
    {
    }

    FalagardTooltip::~FalagardTooltip()
    {
    }

    void FalagardTooltip::populateRenderCache()
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        const StateImagery* imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    Size FalagardTooltip::getTextSize() const
    {
        Size sz(Tooltip::getTextSize());

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

        Rect textArea(wlf.getNamedArea("TextArea").getArea().getPixelRect(*this));
        Rect wndArea(getAbsoluteRect());

        sz.d_width  += wndArea.getWidth() - textArea.getWidth();
        sz.d_height += wndArea.getHeight() - textArea.getHeight();
        return sz;
    }


    
    
    
    Window* FalagardTooltipFactory::createWindow(const String& name)
    {
        return new FalagardTooltip(d_type, name);
    }

    void FalagardTooltipFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
