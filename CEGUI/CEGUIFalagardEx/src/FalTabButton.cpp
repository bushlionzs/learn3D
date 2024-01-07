

#include "FalTabButton.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardTabButton::WidgetTypeName[] = "Falagard/TabButton";

    FalagardTabButton::FalagardTabButton(const String& type, const String& name) :
        TabButton(type, name)
    {
    }

    FalagardTabButton::~FalagardTabButton()
    {
    }

    void FalagardTabButton::drawSelf(float z)
    {
        
        
        

        
        if (d_needsRedraw)
        {
            
            d_renderCache.clearCachedImagery();
            
            d_needsRedraw = false;
            
            TabButton::drawSelf(z);
        }

        
        Window::drawSelf(z);
    }

    void FalagardTabButton::drawNormal(float z)
    {
        doTabButtonRender("Normal");
    }

    void FalagardTabButton::drawHover(float z)
    {
        doTabButtonRender("Hover");
    }

    void FalagardTabButton::drawPushed(float z)
    {
        doTabButtonRender("Selected");
    }

    void FalagardTabButton::drawDisabled(float z)
    {
        doTabButtonRender("Disabled");
    }

    void FalagardTabButton::doTabButtonRender(const String& state)
    {
        
        
        

        const StateImagery* imagery;

        try
        {
            
            const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
            
            
            imagery = wlf.isStateImageryPresent(state) ? &wlf.getStateImagery(state) : &wlf.getStateImagery("Normal");
        }
        
        catch (UnknownObjectException)
        {
            
            return;
        }

        
        
        
        imagery->render(*this);
    }


    
    
    
    Window* FalagardTabButtonFactory::createWindow(const String& name)
    {
        return new FalagardTabButton(d_type, name);
    }

    void FalagardTabButtonFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
