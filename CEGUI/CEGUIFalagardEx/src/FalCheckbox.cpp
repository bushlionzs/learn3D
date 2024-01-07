

#include "FalCheckbox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardCheckbox::WidgetTypeName[] = "Falagard/Checkbox";

    FalagardCheckbox::FalagardCheckbox(const String& type, const String& name) :
        Checkbox(type, name)
    {
    }

    FalagardCheckbox::~FalagardCheckbox()
    {
    }

    void FalagardCheckbox::drawSelf(float z)
    {
        
        
        

        
        Checkbox::drawSelf(z);

        
        Window::drawSelf(z);
    }

    void FalagardCheckbox::drawNormal(float z)
    {
        doButtonRender(d_selected ? "SelectedNormal" : "Normal");
    }

    void FalagardCheckbox::drawHover(float z)
    {
        doButtonRender(d_selected ? "SelectedHover" : "Hover");
    }

    void FalagardCheckbox::drawPushed(float z)
    {
        doButtonRender(d_selected ? "SelectedPushed" : "Pushed");
    }

    void FalagardCheckbox::drawDisabled(float z)
    {
        doButtonRender(d_selected ? "SelectedDisabled" : "Disabled");
    }

    void FalagardCheckbox::doButtonRender(const String& state)
    {
        
        
        

        
        if (d_needsRedraw)
        {
            const StateImagery* imagery;

            
            d_renderCache.clearCachedImagery();
            
            d_needsRedraw = false;

            try
            {
                
                const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
                
                
                imagery = wlf.isStateImageryPresent(state) ? &wlf.getStateImagery(state) : d_selected ? &wlf.getStateImagery("SelectedNormal") : &wlf.getStateImagery("Normal");
            }
            
            catch (UnknownObjectException)
            {
                
                return;
            }

            
            
            
            imagery->render(*this);
        }
    }


    
    
    
    Window* FalagardCheckboxFactory::createWindow(const String& name)
    {
        return new FalagardCheckbox(d_type, name);
    }

    void FalagardCheckboxFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
