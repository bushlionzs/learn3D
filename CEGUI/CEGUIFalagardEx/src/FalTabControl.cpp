

#include "FalTabControl.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUITabButton.h"


namespace CEGUI
{
    const utf8 FalagardTabControl::WidgetTypeName[] = "Falagard/TabControl";
    FalagardTabControlProperties::TabButtonType FalagardTabControl::d_tabButtonTypeProperty;


    FalagardTabControl::FalagardTabControl(const String& type, const String& name) :
        TabControl(type, name)
    {
		CEGUI_START_ADD_STATICPROPERTY( FalagardTabControl )
		   CEGUI_ADD_STATICPROPERTY( &d_tabButtonTypeProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    FalagardTabControl::~FalagardTabControl()
    {
    }

    void FalagardTabControl::populateRenderCache()
    {
        const StateImagery* imagery;
        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        
        imagery = &wlf.getStateImagery(isDisabled() ? "Disabled" : "Enabled");
        imagery->render(*this);
    }

    TabPane* FalagardTabControl::createTabContentPane(const String& name) const
    {
        
        return static_cast<TabPane*>(WindowManager::getSingleton().getWindow(name));
    }

    Window* FalagardTabControl::createTabButtonPane(const String& name) const
    {
        try
        {
            
            return static_cast<TabPane*>(WindowManager::getSingleton().getWindow(name));
        }
        
        catch (UnknownObjectException)
        {
            return TabControl::createTabButtonPane(name);
        }
    }

    TabButton* FalagardTabControl::createTabButton(const String& name) const
    {
        if (d_tabButtonType.empty())
        {
            throw InvalidRequestException("FalagardTabControl::createTabButton - d_tabButtonType has not been set!");
        }

        return static_cast<TabButton*>(WindowManager::getSingleton().createWindow(d_tabButtonType, name));
    }

    const String& FalagardTabControl::getTabButtonType() const
    {
        return d_tabButtonType;
    }

    void FalagardTabControl::setTabButtonType(const String& type)
    {
        d_tabButtonType = type;
    }

    
    
    
    Window* FalagardTabControlFactory::createWindow(const String& name)
    {
        return new FalagardTabControl(d_type, name);
    }

    void FalagardTabControlFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
