

#include "FalSpinner.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIEditbox.h"


namespace CEGUI
{
    const utf8 FalagardSpinner::WidgetTypeName[] = "Falagard/Spinner";

    FalagardSpinner::FalagardSpinner(const String& type, const String& name) :
        Spinner(type, name)
    {
    }

    FalagardSpinner::~FalagardSpinner()
    {
    }

    void FalagardSpinner::populateRenderCache()
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        const StateImagery* imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    PushButton* FalagardSpinner::createIncreaseButton(const String& name) const
    {
        
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(name));
    }

    PushButton* FalagardSpinner::createDecreaseButton(const String& name) const
    {
        
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(name));
    }

    Editbox* FalagardSpinner::createEditbox(const String& name) const
    {
        
        return static_cast<Editbox*>(WindowManager::getSingleton().getWindow(name));
    }

    
    
    
    Window* FalagardSpinnerFactory::createWindow(const String& name)
    {
        return new FalagardSpinner(d_type, name);
    }

    void FalagardSpinnerFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
