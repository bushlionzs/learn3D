

#include "FalTitlebar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardTitlebar::WidgetTypeName[] = "Falagard/Titlebar";

    FalagardTitlebar::FalagardTitlebar(const String& type, const String& name) :
        Titlebar(type, name)
    {
    }

    FalagardTitlebar::~FalagardTitlebar()
    {
    }

    void FalagardTitlebar::populateRenderCache()
    {
        const StateImagery* imagery;

        try
        {
            
            const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
            
            if (!isDisabled())
                imagery = &wlf.getStateImagery((d_parent && d_parent->isActive()) ? "Active" : "Inactive");
            else
                imagery = &wlf.getStateImagery("Disabled");
        }
        catch (UnknownObjectException)
        {
            
            return;
        }

        
        imagery->render(*this);
    }

    Rect FalagardTitlebar::getPixelRect(void) const
    {
        
        if (d_parent && d_parent->getParent() && isClippedByParent())
        {
            return d_parent->getParent()->getInnerRect().getIntersection(getUnclippedPixelRect());
        }
        
        else
        {
            return System::getSingleton().getRenderer()->getRect().getIntersection(getUnclippedPixelRect());
        }
    }


    
    
    
    Window* FalagardTitlebarFactory::createWindow(const String& name)
    {
        return new FalagardTitlebar(d_type, name);
    }

    void FalagardTitlebarFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
