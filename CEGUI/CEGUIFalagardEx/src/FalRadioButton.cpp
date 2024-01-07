

#include "FalRadioButton.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"


namespace CEGUI
{
    const utf8 FalagardRadioButton::WidgetTypeName[] = "Falagard/RadioButton";

    FalagardRadioButton::FalagardRadioButton(const String& type, const String& name) :
        RadioButton(type, name)
    {
    }

    FalagardRadioButton::~FalagardRadioButton()
    {
    }

    void FalagardRadioButton::drawSelf(float z)
    {
        
        
        

        
        RadioButton::drawSelf(z);

        
        Window::drawSelf(z);
    }

    void FalagardRadioButton::drawNormal(float z)
    {
        doButtonRender(d_selected ? "SelectedNormal" : "Normal");
    }

    void FalagardRadioButton::drawHover(float z)
    {
        doButtonRender(d_selected ? "SelectedHover" : "Hover");
    }

    void FalagardRadioButton::drawPushed(float z)
    {
        doButtonRender(d_selected ? "SelectedPushed" : "Pushed");
    }

    void FalagardRadioButton::drawDisabled(float z)
    {
        doButtonRender(d_selected ? "SelectedDisabled" : "Disabled");
    }

    void FalagardRadioButton::doButtonRender(const String& state)
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


    
    
    
    Window* FalagardRadioButtonFactory::createWindow(const String& name)
    {
        return new FalagardRadioButton(d_type, name);
    }

    void FalagardRadioButtonFactory::destroyWindow(Window* window)
    {
        delete window;
    }

} 
