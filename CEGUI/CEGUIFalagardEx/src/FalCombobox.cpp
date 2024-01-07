

#include "FalCombobox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIEditbox.h"
#include "elements/CEGUIComboDropList.h"


namespace CEGUI
{
    const utf8 FalagardCombobox::WidgetTypeName[] = "Falagard/Combobox";

    FalagardCombobox::FalagardCombobox(const String& type, const String& name) :
        Combobox(type, name)
    {
    }

    FalagardCombobox::~FalagardCombobox()
    {
    }

    void FalagardCombobox::populateRenderCache()
    {
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        const StateImagery* imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        
        imagery->render(*this);
    }

    Editbox* FalagardCombobox::createEditbox(const String& name) const
    {
        
        return static_cast<Editbox*>(WindowManager::getSingleton().getWindow(name));
    }

    PushButton* FalagardCombobox::createPushButton(const String& name) const
    {
        
        return static_cast<PushButton*>(WindowManager::getSingleton().getWindow(name));
    }

    ComboDropList* FalagardCombobox::createDropList(const String& name) const
    {
        
        return static_cast<ComboDropList*>(WindowManager::getSingleton().getWindow(name));
    }

    
    
    
    Window* FalagardComboboxFactory::createWindow(const String& name)
    {
        return new FalagardCombobox(d_type, name);
    }

    void FalagardComboboxFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
