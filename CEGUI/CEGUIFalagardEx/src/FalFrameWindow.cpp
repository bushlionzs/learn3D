

#include "FalFrameWindow.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUITitlebar.h"
#include "elements/CEGUIPushButton.h"


namespace CEGUI
{
    const utf8 FalagardFrameWindow::WidgetTypeName[] = "Falagard/FrameWindow";

    FalagardFrameWindow::FalagardFrameWindow(const String& type, const String& name) :
        FrameWindow(type, name)
    {
    }

    FalagardFrameWindow::~FalagardFrameWindow()
    {
    }

    void FalagardFrameWindow::populateRenderCache()
    {
        
        if (d_rolledup)
            return;

        
        String stateName(isDisabled() ? "Disabled" : (isActive() ? "Active" : "Inactive"));
        stateName += d_titlebar->isVisible() ? "WithTitle" : "NoTitle";
        stateName += d_frameEnabled ? "WithFrame" : "NoFrame";

        const StateImagery* imagery;

        try
        {
            
            const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
            
            imagery = &wlf.getStateImagery(stateName);
        }
        catch (UnknownObjectException)
        {
            
            return;
        }

        
        imagery->render(*this);
    }

    Rect FalagardFrameWindow::getUnclippedInnerRect(void) const
    {
        if (d_rolledup)
            return Rect(0,0,0,0);

        
        String areaName("Client");
        areaName += d_titlebar->isVisible() ? "WithTitle" : "NoTitle";
        areaName += d_frameEnabled ? "WithFrame" : "NoFrame";

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        return wlf.getNamedArea(areaName).getArea().getPixelRect(*this, getUnclippedPixelRect());
    }

    Titlebar* FalagardFrameWindow::createTitlebar(const String& name) const
    {
        return static_cast<Titlebar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_titlebar__"));
    }

    PushButton* FalagardFrameWindow::createCloseButton(const String& name) const
    {
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(getName() + "__auto_closebutton__"));
    }

    
    
    
    Window* FalagardFrameWindowFactory::createWindow(const String& name)
    {
        return new FalagardFrameWindow(d_type, name);
    }

    void FalagardFrameWindowFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
